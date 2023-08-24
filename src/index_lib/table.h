#pragma once

#include "index/index.h"
#include "index_lib/store/fixed_store.h"
#include "meta.h"
#include "schema/schema.h"
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

namespace index_lib {

/*
 * todo:
 * 1. index独立，并发安全hashtable、可dump
 * 2. schema，多字段管理，char* 反射到具体类型
 * 3. fixed data segment, 每片固定大小，对应一个file，可不断增加
 */
class Table {
public:
  Table(const TableConf &conf) : conf_(conf), invert_index_(conf.index_path){};
  ~Table(){};

  bool Init() {
    if (auto code = loadIndex(conf_.index_path); code != 0) {
      std::cerr << "load index fail, errno=" << code << std::endl;
      return false;
    }
    if (auto code = loadFixedData(conf_.fixed_data_path); code != 0) {
      std::cerr << "load fixed data fail, errno=" << code << std::endl;
      return false;
    }
    return true;
  };
  // todo: mget接口或整行获取接口
  template <typename T> T *Get(uint64_t item_id, std::string field) {
    uint32_t doc_id = invert_index_.GetDocId(item_id);
    // todo: 支持变长字段
    auto row = fixed_mem_store_.GetFixedRow(doc_id);
    return schema_.GetValue<T>(row, field);
  };

  template <typename T> T *Get(uint64_t item_id, uint16_t field_id) {
    uint32_t doc_id = invert_index_.GetDocId(item_id);
    // todo: 支持变长字段
    auto row = fixed_mem_store_.GetFixedRow(doc_id);
    return schema_.GetValue<T>(row, field_id);
  };

  // todo: 整行set接口
  template <typename T>
  bool Set(uint64_t item_id, std::string field, const T &value) {
    uint32_t doc_id = invert_index_.GetDocId(item_id);
    // todo: 支持变长字段
    auto row = fixed_mem_store_.GetMutableFixedRow(doc_id);
    return schema_.SetValue<T>(row, field, value);
  }

  template <typename T>
  bool Set(uint64_t item_id, uint16_t field_id, const T &value) {
    uint32_t doc_id = invert_index_.GetDocId(item_id);
    // todo: 支持变长字段
    auto row = fixed_mem_store_.GetMutableFixedRow(doc_id);
    return schema_.SetValue<T>(row, field_id, value);
  }

private:
  int loadIndex(const std::string &path) { invert_index_.Load(); };
  int loadFixedData(const std::string &path){};

private:
  TableConf conf_;
  Schema schema_;
  InvertIndex invert_index_;
  FixedMemStore fixed_mem_store_;
};

} // namespace index_lib