#pragma once

#include "gflags/gflags.h"
#include "index/index.h"
#include "index_lib/store/fixed_mem_store.h"
#include "meta.h"
#include "schema/schema.h"
#include <atomic>
#include <cstdint>
#include <glog/logging.h>
#include <iostream>
#include <mutex>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

DEFINE_string(index_mode, "normal", "build: only write, normal: read & update");

namespace index_lib {

/*
 * todo:
 * 1. index独立，并发安全hashtable、可dump
 * 2. schema，多字段管理，char* 反射到具体类型
 * 3. fixed data segment, 每片固定大小，对应一个file，可不断增加
 * 4. mget接口或整行获取接口，mset或者整行设置接口
 * 5. 支持变长字段
 */

static const uint32_t kInvalidDocId = static_cast<uint32_t>(-1);

class Table {
public:
  Table(const TableConf &conf)
      : conf_(conf), schema_(conf.schema_path), invert_index_(conf.index_path),
        fixed_mem_store_(conf.fixed_data_path, conf.fixed_file_size,
                         conf.fixed_row_size),
        max_doc_id_(conf.max_doc_id){};
  ~Table(){};

  bool Load() {
    if (auto code = schema_.Load(); code != 0) {
      LOG(ERROR) << "load schema fail, path=" << conf_.schema_path
                 << ", errno=" << code;
      return false;
    }
    if (auto ok = invert_index_.Load(); !ok) {
      LOG(ERROR) << "load index fail, path=" << conf_.index_path;
      return false;
    }
    if (auto code = fixed_mem_store_.Load(); code != 0) {
      LOG(ERROR) << "load fixed data fail, path=" << conf_.fixed_data_path
                 << ", errno=" << code;
      return false;
    }
    return true;
  };

  bool Dump() {
    if (auto ok = invert_index_.Dump(); !ok) {
      LOG(ERROR) << "dump index fail, path=" << conf_.index_path;
      return false;
    }
    if (auto code = fixed_mem_store_.Dump(); code != 0) {
      LOG(ERROR) << "dump fixed data fail, path=" << conf_.fixed_data_path
                 << ", errno=" << code;
      return false;
    }
    return true;
  };

  // get
  // 1. 自旋等待version变为偶数，然后执行2
  // 2. copy数据并检查version是否变化，如果version有变化，则跳回1

  // set
  // 1. 自旋等待version变为偶数
  // 2. 然后cas+1(不能fetch_add)，cas失败则跳回1
  // 3. 写数据后cas+1，理论上不会失败，失败报错

  template <typename T>
  std::optional<T> Get(uint64_t item_id, const std::string &field_name) {
    auto doc = invert_index_.GetDoc(item_id);
    if (doc == nullptr) {
      return std::nullopt;
    }
    auto row = fixed_mem_store_.GetFixedRow(doc->doc_id);
    return {schema_.GetValue<T>(row, field_name)};
  };

  template <typename T>
  std::optional<T> Get(uint64_t item_id, uint16_t field_id) {
    auto doc = invert_index_.GetDoc(item_id);
    if (doc == nullptr) {
      return std::nullopt;
    }

    uint32_t ver1, ver2;
    std::optional<T> ret;
    int count = 10;
    while (count > 0) {
      ver1 = spinWaitWriting(doc, 10); // 自旋10次
      if (ver1 & 1) {
        LOG(ERROR) << "spinWaitWriting in get handler timeout, item_id="
                   << item_id;
        return std::nullopt;
      }
      auto row = fixed_mem_store_.GetFixedRow(doc->doc_id);
      ret = schema_.GetValue<T>(row, field_id);
      ver2 = doc->version.load(std::memory_order_acquire);
      if (ver1 == ver2) {
        return ret;
      }
      count--;
    };
    return std::nullopt;
  };

  template <typename T>
  bool Set(uint64_t item_id, const std::string &field_name, const T &value) {
    DocInfo *doc = getOrCreateDoc(item_id);
    if (doc == nullptr) {
      LOG_EVERY_N(ERROR, 100) << "getOrCreateDoc fail, table_size_limit: "
                              << conf_.table_size_limit;
      return false;
    }
    auto row = fixed_mem_store_.GetMutableFixedRow(doc->doc_id);
    return schema_.SetValue<T>(row, field_name, value);
  }

  template <typename T>
  bool Set(uint64_t item_id, uint16_t field_id, const T &value) {
    DocInfo *doc = getOrCreateDoc(item_id);
    if (doc == nullptr) {
      LOG_EVERY_N(ERROR, 100) << "getOrCreateDoc fail, table_size_limit: "
                              << conf_.table_size_limit;
      return false;
    }
    auto row = fixed_mem_store_.GetMutableFixedRow(doc->doc_id);
    return schema_.SetValue<T>(row, field_id, value);
  }

private:
  DocInfo *getOrCreateDoc(uint64_t item_id) {
    auto doc = invert_index_.GetDoc(item_id);
    if (doc != nullptr) {
      return doc;
    }
    // 用table_size_limit来保证无rehash，从而避免读时加锁
    if (max_doc_id_ >= conf_.table_size_limit) {
      return nullptr;
    }
    // todo: 增加新doc的时候，整行重置默认值
    std::lock_guard<std::mutex> lg(index_mutex_);
    max_doc_id_++;
    return invert_index_.AddDoc(item_id, max_doc_id_, 0, 1);
  }

  uint32_t spinWaitWriting(DocInfo *doc, int count) {
    uint32_t ver;
    do {
      ver = doc->version.load(std::memory_order_acquire);
      count--;
    } while (ver & 1 && count > 0);
    return ver;
  }

private:
  TableConf conf_;
  Schema schema_;
  InvertIndex invert_index_;
  FixedMemStore fixed_mem_store_;
  uint32_t max_doc_id_;
  std::mutex index_mutex_;
};

} // namespace index_lib
