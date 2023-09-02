#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace index_lib {
enum DataType {
  DT_UNKNOWN = 0,
  DT_INT8 = 1,
  DT_UINT8 = 2,
  DT_INT16 = 3,
  DT_UINT64 = 4,
  DT_INT64 = 5,
  DT_STRING = 6
};

enum FieldType {
  BASIC = 0,
  ARRAY = 1,
  VECTOR = 2,
};

template <typename C> struct is_vector : std::false_type {};
template <typename T, typename A>
struct is_vector<std::vector<T, A>> : std::true_type {};
template <typename C> inline constexpr bool is_vector_v = is_vector<C>::value;

template <typename T>
inline constexpr bool is_number_v =
    std::is_integral<T>::value || std::is_floating_point<T>::value;

template <typename T> struct DataTypeTraits {
  static_assert(true, "Specified Data Type not supported");
};

template <> struct DataTypeTraits<int8_t> {
  static const DataType data_type = DT_INT8;
};

template <> struct DataTypeTraits<uint8_t> {
  static const DataType data_type = DT_UINT8;
};

template <> struct DataTypeTraits<int16_t> {
  static const DataType data_type = DT_INT16;
};

template <> struct DataTypeTraits<uint64_t> {
  static const DataType data_type = DT_UINT64;
};

template <> struct DataTypeTraits<int64_t> {
  static const DataType data_type = DT_INT64;
};

template <> struct DataTypeTraits<std::string> {
  static const DataType data_type = DT_STRING;
};

} // namespace index_lib