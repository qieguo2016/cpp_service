#pragma once

#include "index_lib/schema/data_type.h"
#include "third_party/parallel_hashmap/phmap.h"
#include <cstdint>
#include <google/protobuf/descriptor.h>
#include <string>
#include <vector>

namespace index_lib {

// template <int>
// struct EndianHelper;

// template <>
// struct EndianHelper<1> {
//   static uint8_t Load(const void* p) { return *static_cast<const
//   uint8_t*>(p); }
// };

// template <>
// struct EndianHelper<2> {
//   static uint16_t Load(const void* p) {
//     uint16_t tmp;
//     std::memcpy(&tmp, p, 2);
// #ifndef PROTOBUF_LITTLE_ENDIAN
//     tmp = bswap_16(tmp);
// #endif
//     return tmp;
//   }
// };

// template <>
// struct EndianHelper<4> {
//   static uint32_t Load(const void* p) {
//     uint32_t tmp;
//     std::memcpy(&tmp, p, 4);
// #ifndef PROTOBUF_LITTLE_ENDIAN
//     tmp = bswap_32(tmp);
// #endif
//     return tmp;
//   }
// };

// template <>
// struct EndianHelper<8> {
//   static uint64_t Load(const void* p) {
//     uint64_t tmp;
//     std::memcpy(&tmp, p, 8);
// #ifndef PROTOBUF_LITTLE_ENDIAN
//     tmp = bswap_64(tmp);
// #endif
//     return tmp;
//   }
// };

// //   uint64 value = UnalignedLoad<uint64>(ptr);
// template <typename T>
// T UnalignedLoad(const char* p) {
//   auto tmp = EndianHelper<sizeof(T)>::Load(p);
//   T res;
//   memcpy(&res, &tmp, sizeof(T));
//   return res;
// }

struct FieldDescriptor {
  uint16_t id;
  std::string name;
  DataType dtype;
  RepeatType rtype;
  uint16_t byte_offset;
  uint16_t byte_len;
};

inline uint16_t UNALIGNED_LOAD16(const void *p) {
  uint16_t t;
  memcpy(&t, p, sizeof t);
  return t;
}

inline uint32_t UNALIGNED_LOAD32(const void *p) {
  uint32_t t;
  memcpy(&t, p, sizeof t);
  return t;
}

inline uint64_t UNALIGNED_LOAD64(const void *p) {
  uint64_t t;
  memcpy(&t, p, sizeof t);
  return t;
}

inline void UNALIGNED_STORE16(void *p, uint16_t v) { memcpy(p, &v, sizeof v); }

inline void UNALIGNED_STORE32(void *p, uint32_t v) { memcpy(p, &v, sizeof v); }

inline void UNALIGNED_STORE64(void *p, uint64_t v) { memcpy(p, &v, sizeof v); }

template <typename T>
struct RefTypeTraits<
    T, typename std::enable_if<is_proto_enum<T>::value>::type> {
  typedef RepeatedFieldRefIterator<T> iterator;
  typedef RepeatedFieldAccessor AccessorType;
  // We use int32 for repeated enums in RepeatedFieldAccessor.
  typedef int32 AccessorValueType;
  typedef T IteratorValueType;
  typedef int32* IteratorPointerType;
  static constexpr FieldDescriptor::CppType cpp_type =
      FieldDescriptor::CPPTYPE_ENUM;
  static const Descriptor* GetMessageFieldDescriptor() { return NULL; }
};

template <typename T>
struct RefTypeTraits<
    T, typename std::enable_if<std::is_same<std::string, T>::value>::type> {
  typedef RepeatedFieldRefIterator<T> iterator;
  typedef RepeatedFieldAccessor AccessorType;
  typedef std::string AccessorValueType;
  typedef const std::string IteratorValueType;
  typedef const std::string* IteratorPointerType;
  static constexpr FieldDescriptor::CppType cpp_type =
      FieldDescriptor::CPPTYPE_STRING;
  static const Descriptor* GetMessageFieldDescriptor() { return NULL; }
};

class Schema {
public:
  Schema(const std::vector<FieldDescriptor> &field_descriptors)
      : field_vec_(field_descriptors){};
  ~Schema(){};

  template <typename T>
  T *GetValue(const char *data, const std::string &field) {
    return nullptr;
  };

  // todo: checktype
  template <typename T> T *GetValue(const char *data, uint16_t field_id) {
    if (field_id >= field_vec_.size()) {
      return nullptr;
    }
    return (T *)(data + field_vec_[field_id].byte_offset);
  };

  template <typename T>
  bool SetValue(const char *data, const std::string &field, const T &value) {
    return true;
  };

  template <typename T>
  bool SetValue(const char *data, int16_t field_id, const T &value) {
    if (field_id >= field_vec_.size()) {
      return false;
    }
    *(T *)(data + field_vec_[field_id].byte_offset) = value;
    return true;
  };

private:
  // inline uint64_t ReadVarint64(const char **p) {
  //   uint64_t tmp;
  //   *p = VarintParse(*p, &tmp);
  //   return tmp;
  // }

  // inline uint8_t ReadUint8(const char **p) {
  //   uint8_t res = static_cast<uint8_t>(p[0]);
  //   if (res < 128) {
  //     *pp = p + 1;
  //     return res;
  //   }
  // }

private:
  phmap::flat_hash_map<std::string, FieldDescriptor *> field_map_;
  std::vector<FieldDescriptor> field_vec_;
};
} // namespace index_lib