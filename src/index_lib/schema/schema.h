#pragma once

#include "index_lib/schema/data_type.h"
#include "third_party/parallel_hashmap/phmap.h"
#include <cstdint>
#include <string>
#include <vector>

namespace index_lib {

struct Field {
  int16_t id;
  std::string name;
  DataType type;
  MultiType mtype;
  int16_t byte_offset;
  int16_t byte_len;
};

class Schema {
public:
  template <typename T>
  T *GetValue(const char *data, const std::string &field) {
    return nullptr;
  };

  template <typename T> T *GetValue(const char *data, uint16_t field_id) {
    if (field_id >= field_vec_.size()) {
      return nullptr;
    }
    field_vec_[field_id].type;
    return nullptr;
  };

  template <typename T>
  bool SetValue(const char *data, const std::string &field, const T &value) {
    return true;
  };

  template <typename T>
  bool SetValue(const char *data, int16_t field_id, const T &value) {
    return true;
  };

private:
  phmap::flat_hash_map<std::string, Field *> field_map_;
  std::vector<Field> field_vec_;
};
} // namespace index_lib