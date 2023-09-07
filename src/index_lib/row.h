#pragma once

#include "index_lib/schema/schema.h"
#include <cstddef>
#include <cstring>
namespace index_lib {

class Row {
public:
  Row(Schema schema, size_t n) : schema_(schema), data_(new char[n]){};
  Row(Schema schema, const char *data, size_t n) : schema_(schema) {
    data_ = new char[n];
    memcpy(data_, data, n);
  };
  Row(Row &&) = default;
  Row(const Row &) = delete;
  Row &operator=(Row &&) = default;
  Row &operator=(const Row &) = default;
  ~Row() {
    if (data_) {
      delete[] data_;
      data_ = nullptr;
    }
  };

  template <typename T>
  std::optional<T> GetField(const std::string &field_name) {
    return schema_.GetValue<T>(data_, field_name);
  };

  template <typename T>
  std::optional<T> GetField(uint64_t item_id, uint16_t field_id) {
    return schema_.GetValue<T>(data_, field_id);
  };

  template <typename T>
  bool Set(const std::string &field_name, const T &value) {
    return schema_.SetValue<T>(data_, field_name, value);
  };

  template <typename T> bool Set(uint16_t field_id, const T &value) {
    return schema_.SetValue<T>(data_, field_id, value);
  };

  inline const char *GetData() const { return data_; };

private:
  Schema schema_;
  char *data_;
};

} // namespace index_lib