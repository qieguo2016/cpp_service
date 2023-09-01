#pragma once

#include "index_lib/schema/data_type.h"
#include "index_lib/schema/reflection.h"
#include "third_party/parallel_hashmap/phmap.h"
#include <cstdint>
#include <glog/logging.h>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace index_lib {

struct FieldDescriptor {
  uint16_t id;
  std::string name;
  DataType dtype;
  FieldType ftype;
  uint16_t byte_offset;
  uint16_t byte_len;

  FieldDescriptor(uint16_t id, std::string name, DataType dtype,
                  FieldType ftype, uint16_t byte_offset, uint16_t byte_len)
      : id(id), name(name), dtype(dtype), ftype(ftype),
        byte_offset(byte_offset), byte_len(byte_len) {}
};

class Schema {
public:
  Schema(const std::string &path) : path_(path){};
  ~Schema(){};

  int Load() {
    field_vec_.emplace_back(0, "item_id", DT_UINT64, BASIC, 0, 8);
    field_map_.emplace(field_vec_.back().name, &field_vec_.back());
    field_vec_.emplace_back(1, "title", DT_STRING, ARRAY, 8, 10);
    field_map_.emplace(field_vec_.back().name, &field_vec_.back());
    return 0;
  };

  template <typename T>
  std::optional<T> GetValue(const char *data, const std::string &field_name) {
    auto it = field_map_.find(field_name);
    if (it == field_map_.end()) {
      LOG(ERROR) << "invalid field_name: " << field_name;
      return std::nullopt;
    }
    FieldDescriptor *field = it->second;
    if (checkType<T>(field->ftype, field->dtype)) {
      LOG(ERROR) << "field type unmatch, field_name: " << field_name
                 << ", template_type: " << typeid(T).name();
      return std::nullopt;
    }
    return {Reflection::get<T>(data + field->byte_offset)};
  };

  template <typename T>
  std::optional<T> GetValue(const char *data, uint16_t field_id) {
    if (field_id >= field_vec_.size()) {
      LOG(ERROR) << "invalid field_id: " << field_id;
      return std::nullopt;
    }
    FieldDescriptor &field = field_vec_[field_id];
    if (checkType<T>(field.ftype, field.dtype)) {
      LOG(ERROR) << "field type unmatch, field_id: " << field_id
                 << ", template_type: " << typeid(T).name();
      return std::nullopt;
    }
    return {Reflection::get<T>(data + field.byte_offset)};
  };

  template <typename T>
  bool SetValue(char *data, const std::string &field_name, const T &value) {
    auto it = field_map_.find(field_name);
    if (it == field_map_.end()) {
      LOG(ERROR) << "invalid field_name: " << field_name;
      return false;
    }
    FieldDescriptor *field = it->second;
    if (checkType<T>(field->ftype, field->dtype)) {
      LOG(ERROR) << "field type unmatch, field_name: " << field_name
                 << ", template_type: " << typeid(T).name();
      return false;
    }
    return Reflection::set(data + field->byte_offset, value);
  };

  template <typename T>
  bool SetValue(char *data, uint16_t field_id, const T &value) {
    if (field_id >= field_vec_.size()) {
      LOG(ERROR) << "invalid field_id: " << field_id;
      return false;
    }
    FieldDescriptor &field = field_vec_[field_id];
    if (checkType<T>(field.ftype, field.dtype)) {
      LOG(ERROR) << "field type unmatch, field_id: " << field_id
                 << ", template_type: " << typeid(T).name();
      return false;
    }
    return Reflection::set(data + field.byte_offset, value);
  };

private:
  template <typename T>
  inline bool checkType(FieldType ftype, DataType dtype) const {
    if (IsVectorType<T>::value) {
      if (ftype != FieldType::ARRAY && ftype != FieldType::VECTOR) {
        return false;
      }
      return DataTypeTraits<typename T::value_type>::data_type == dtype;
    }
    return DataTypeTraits<T>::data_type == dtype;
  }

private:
  std::string path_;
  phmap::flat_hash_map<std::string, FieldDescriptor *> field_map_;
  std::vector<FieldDescriptor> field_vec_;
};
} // namespace index_lib
