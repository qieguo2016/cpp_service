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

namespace index_lib {

/*
 * todo:
 * 1. index独立，并发安全hashtable、可dump
 * 2. schema，多字段管理，char* 反射到具体类型
 * 3. fixed data segment, 每片固定大小，对应一个file，可不断增加
 * 4. mget接口或整行获取接口，mset或者整行设置接口
 * 5. 支持变长字段
 */

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

  template <typename T>
  std::optional<T> Get(uint64_t item_id, const std::string &field_name) {
    uint32_t doc_id = invert_index_.GetDocId(item_id);
    if (doc_id == kInvalidDocId) {
      return std::nullopt;
    }
    auto row = fixed_mem_store_.GetFixedRow(doc_id);
    return {schema_.GetValue<T>(row, field_name)};
  };

  template <typename T>
  std::optional<T> Get(uint64_t item_id, uint16_t field_id) {
    uint32_t doc_id = invert_index_.GetDocId(item_id);
    if (doc_id == kInvalidDocId) {
      return std::nullopt;
    }
    auto row = fixed_mem_store_.GetFixedRow(doc_id);
    return {schema_.GetValue<T>(row, field_id)};
  };

  template <typename T>
  bool Set(uint64_t item_id, const std::string &field_name, const T &value) {
    uint32_t doc_id = getOrCreateDocId(item_id);
    if (doc_id == kInvalidDocId) {
      LOG_EVERY_N(ERROR, 100)
          << "add_doc_id fail, table_size_limit: " << conf_.table_size_limit;
      return false;
    }
    auto row = fixed_mem_store_.GetMutableFixedRow(doc_id);
    return schema_.SetValue<T>(row, field_name, value);
  }

  template <typename T>
  bool Set(uint64_t item_id, uint16_t field_id, const T &value) {
    uint32_t doc_id = getOrCreateDocId(item_id);
    if (doc_id == kInvalidDocId) {
      LOG_EVERY_N(ERROR, 100)
          << "add_doc_id fail, table_size_limit: " << conf_.table_size_limit;
      return false;
    }
    auto row = fixed_mem_store_.GetMutableFixedRow(doc_id);
    return schema_.SetValue<T>(row, field_id, value);
  }

private:
  uint32_t getOrCreateDocId(uint64_t item_id) {
    uint32_t doc_id = invert_index_.GetDocId(item_id);
    if (doc_id != kInvalidDocId) {
      return doc_id;
    }
    if (max_doc_id_ >= conf_.table_size_limit) {
      return kInvalidDocId;
    }
    {
      // add new
      // todo: 增加新doc的时候，整行重置默认值
      std::lock_guard<std::mutex> lg(doc_id_mutex_);
      max_doc_id_++;
      doc_id = max_doc_id_;
    }
    invert_index_.SetDocId(item_id, doc_id);
    return doc_id;
  }

private:
  TableConf conf_;
  Schema schema_;
  InvertIndex invert_index_;
  FixedMemStore fixed_mem_store_;
  uint32_t max_doc_id_;
  std::mutex doc_id_mutex_;
};

} // namespace index_lib
