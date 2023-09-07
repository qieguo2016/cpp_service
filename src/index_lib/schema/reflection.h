#pragma once

#include "index_lib/schema/data_type.h"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace index_lib {

// #ifndef PROTOBUF_LITTLE_ENDIAN
//     tmp = bswap_64(tmp);
// #endif

/*
 * Reflection
 * 1. 列表最大长度为255(uint8)
 * 2. 写入不保证原子性，尤其是列表写入
 * 3. bool占1个byte，上层可用多个bool组合成一个byte
 */
class Reflection {
public:
  template <typename T>
  inline static typename std::enable_if<is_number_v<T>, T>::type
  get(const char *data) {
    T tmp;
    memcpy(&tmp, data, sizeof(T));
    return tmp;
  }

  template <typename T>
  inline static typename std::enable_if<is_number_v<T>, bool>::type
  set(char *data, const T &value) {
    memcpy(data, &value, sizeof(value));
    return true;
  }

  template <typename T>
  inline static
      typename std::enable_if<std::is_same<T, std::string>::value, T>::type
      get(const char *data) {
    uint8_t num = get<uint8_t>(data);
    return std::string(data + 1, num);
  }

  template <typename T>
  inline static
      typename std::enable_if<std::is_same<T, std::string>::value, bool>::type
      set(char *data, const T &value) {
    uint8_t num = value.size();
    if (!set<uint8_t>(data, num)) {
      return false;
    }
    memcpy(data + 1, value.c_str(), num);
    return true;
  }

  template <typename T>
  inline static typename std::enable_if<
      is_vector_v<T> && is_number_v<typename T::value_type>, T>::type
  get(const char *data) {
    uint8_t num = get<uint8_t>(data);
    using ET = typename T::value_type;
    std::vector<ET> ret(num);
    memcpy(ret.data(), data + 1, num * sizeof(ET));
    return ret;
  }

  template <typename T>
  inline static typename std::enable_if<
      is_vector_v<T> && is_number_v<typename T::value_type>, bool>::type
  set(char *data, const T &value) {
    uint8_t num = value.size();
    if (!set<uint8_t>(data, num)) {
      return false;
    }
    using ET = typename T::value_type;
    memcpy(data + 1, value.data(), num * sizeof(ET));
    return true;
  }

  template <typename T>
  inline static typename std::enable_if<
      is_vector_v<T> &&
          std::is_same<typename T::value_type, std::string>::value,
      T>::type
  get(const char *data) {
    uint8_t num = get<uint8_t>(data);
    std::vector<std::string> ret(num);
    uint32_t offset = 1; // 1 byte for num
    for (int i = 0; i < num; i++) {
      ret[i] = get<std::string>(data + offset);
      offset += ret[i].size() + 1;
    }
    return ret;
  }

  template <typename T>
  inline static typename std::enable_if<
      is_vector_v<T> &&
          std::is_same<typename T::value_type, std::string>::value,
      bool>::type
  set(char *data, const T &value) {
    uint8_t num = value.size();
    if (!set<uint8_t>(data, num)) {
      return false;
    }
    uint32_t offset = 1; // 1 byte for num
    for (int i = 0; i < num; i++) {
      if (!set<std::string>(data + offset, value[i])) {
        return false;
      }
      offset += value[i].size() + 1;
    }
    return true;
  }
};
} // namespace index_lib
