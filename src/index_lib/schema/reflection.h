#pragma once

#include "index_lib/schema/data_type.h"
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace index_lib {

template <int> struct EndianHelper;

template <> struct EndianHelper<1> {
  static uint8_t Load(const void *p) {
    return *static_cast<const uint8_t *>(p);
  }
  static bool Store(void *p, uint8_t v) {
    auto tmp = memcpy(p, &v, sizeof v);
    return tmp != nullptr;
  }
};

template <> struct EndianHelper<2> {
  static uint16_t Load(const void *p) {
    uint16_t tmp;
    std::memcpy(&tmp, p, 2);
    // #ifndef PROTOBUF_LITTLE_ENDIAN
    //     tmp = bswap_16(tmp);
    // #endif
    return tmp;
  }
  static bool Store(void *p, uint16_t v) {
    auto tmp = memcpy(p, &v, sizeof v);
    return tmp != nullptr;
  }
};

template <> struct EndianHelper<4> {
  static uint32_t Load(const void *p) {
    uint32_t tmp;
    std::memcpy(&tmp, p, 4);
    // #ifndef PROTOBUF_LITTLE_ENDIAN
    //     tmp = bswap_32(tmp);
    // #endif
    return tmp;
  }
  static bool Store(void *p, uint32_t v) {
    auto tmp = memcpy(p, &v, sizeof v);
    return tmp != nullptr;
  }
};

template <> struct EndianHelper<8> {
  static uint64_t Load(const void *p) {
    uint64_t tmp;
    std::memcpy(&tmp, p, 8);
    // #ifndef PROTOBUF_LITTLE_ENDIAN
    //     tmp = bswap_64(tmp);
    // #endif
    return tmp;
  }
  static bool Store(void *p, uint64_t v) {
    auto tmp = memcpy(p, &v, sizeof v);
    return tmp != nullptr;
  }
};

// inline void UnalignedStore8(void *p, uint8_t v) { memcpy(p, &v, sizeof v); }

// inline void UnalignedStore16(void *p, uint16_t v) { memcpy(p, &v, sizeof v);
// }

// inline void UnalignedStore32(void *p, uint32_t v) { memcpy(p, &v, sizeof v);
// }

// inline void UnalignedStore64(void *p, uint64_t v) { memcpy(p, &v, sizeof v);
// }

// template <typename T> T UnalignedLoad(const char *p) {
//   return EndianHelper<sizeof(T)>::Load(p);
//   // T res;
//   // memcpy(&res, &tmp, sizeof(T));
//   // return res;
// }

// inline uint8_t UnalignedLoad8(const void *p) {
//   return *static_cast<const uint8_t *>(p);
// }

// inline uint16_t UnalignedLoad16(const void *p) {
//   uint16_t t;
//   memcpy(&t, p, sizeof t);
//   return t;
// }

// inline uint32_t UnalignedLoad32(const void *p) {
//   uint32_t t;
//   memcpy(&t, p, sizeof t);
//   return t;
// }

// inline uint64_t UnalignedLoad64(const void *p) {
//   uint64_t t;
//   memcpy(&t, p, sizeof t);
//   return t;
// }

class Reflection {
public:
  // todo: 需要区分signed和unsigned
  template <typename T>
  typename std::enable_if<std::is_integral<T>::value, T>::type
  get(const char *data) const {
    return EndianHelper<sizeof(T)>::Load(data);
  }

  template <typename T>
  typename std::enable_if<std::is_integral<T>::value, bool>::type
  set(char *data, const T &value) const {
    return EndianHelper<sizeof(T)>::Store(data, value);
  }

  template <typename T>
  typename std::enable_if<std::is_floating_point<T>::value &&
                              std::is_same<T, float>::value,
                          T>::type
  get(const char *data) const {
    uint32_t tmp = EndianHelper<sizeof(uint32_t)>::Load(data);
    return (*(float *)(&tmp));
  }

  template <typename T>
  typename std::enable_if<std::is_floating_point<T>::value &&
                              std::is_same<T, float>::value,
                          bool>::type
  set(char *data, const T &value) const {
    uint32_t tmp = (*(uint32_t *)(&value));
    return EndianHelper<sizeof(uint32_t)>::Store(data, tmp);
  }

  template <typename T>
  typename std::enable_if<std::is_floating_point<T>::value &&
                              std::is_same<T, double>::value,
                          T>::type
  get(const char *data) const {
    uint64_t tmp = EndianHelper<sizeof(uint64_t)>::Load(data);
    return (*(double *)(&tmp));
  }

  template <typename T>
  typename std::enable_if<std::is_floating_point<T>::value &&
                              std::is_same<T, double>::value,
                          bool>::type
  set(char *data, const T &value) const {
    uint64_t tmp = (*(uint64_t *)(&value));
    return EndianHelper<sizeof(uint64_t)>::Store(data, tmp);
  }

private:
  // template <typename T>
  // T _get(const char *data, const uint16_t bytes_offset) const {
  //   throw std::invalid_argument("unsupported type");
  // }

  // template <>
  // std::string _get<std::string>(const char *data,
  //                               const uint16_t bytes_offset) const {
  //   std::string d;
  //   uint8_t string_size = UnalignedLoad8(data);

  //   d.reserve(string_size);
  //   uint8_t c;
  //   for (size_t i = 0; i < string_size; ++i) {
  //     c = _get<uint8_t>(data, 8, bytes_offset + i + 1);
  //     d.push_back(c);
  //   }
  //   return d;
  // }

  // template <typename T>
  //     typename std::enable_if < std::is_integral<T>::value,
  //     T >> _get<T, bool>(const char *data, const uint16_t bytes_offset) const
  //     {
  //   std::string d;
  //   uint8_t string_size = UnalignedLoad8(data);

  //   d.reserve(string_size);
  //   uint8_t c;
  //   for (size_t i = 0; i < string_size; ++i) {
  //     c = _get<uint8_t>(data, 8, bytes_offset + i + 1);
  //     d.push_back(c);
  //   }
  //   return d;
  // }
};
} // namespace index_lib
