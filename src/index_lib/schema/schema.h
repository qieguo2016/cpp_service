#pragma once

#include "index_lib/schema/data_type.h"
#include "index_lib/schema/reflection.h"
#include "third_party/parallel_hashmap/phmap.h"
#include <cstdint>
#include <exception>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace index_lib {

struct FieldDescriptor {
  uint16_t id;
  std::string name;
  DataType dtype;
  FieldType ftype;
  uint16_t byte_offset;
  uint16_t byte_len;
};

template <uint16_t, uint16_t, typename T = void> struct RefTypeTraits {
  typedef T type;
  // using type = T;
};

template <> struct RefTypeTraits<1, 2> {
  typedef uint16_t type;
};

template <> struct RefTypeTraits<1, 3> {
  typedef std::vector<uint16_t> type;
};

// template <typename T, typename... Types> struct IsVectorType {
//   static const bool value = false;
// };

// template <typename T, typename... Types>
// struct IsVectorType<std::vector<T, Types...>> {
//   static const bool value = true;
// };

// template <typename T>
// struct RefTypeTraits<T,
//                      typename std::enable_if<is_proto_enum<T>::value>::type>
//                      {
//   typedef RepeatedFieldRefIterator<T> iterator;
//   typedef RepeatedFieldAccessor AccessorType;
//   // We use int32 for repeated enums in RepeatedFieldAccessor.
//   typedef int32 AccessorValueType;
//   typedef T IteratorValueType;
//   typedef int32 *IteratorPointerType;
//   static constexpr FieldDescriptor::CppType cpp_type =
//       FieldDescriptor::CPPTYPE_ENUM;
//   static const Descriptor *GetMessageFieldDescriptor() { return NULL; }
// };

// template <typename T>
// struct RefTypeTraits<
//     T, typename std::enable_if<std::is_same<std::string, T>::value>::type> {
//   typedef RepeatedFieldRefIterator<T> iterator;
//   typedef RepeatedFieldAccessor AccessorType;
//   typedef std::string AccessorValueType;
//   typedef const std::string IteratorValueType;
//   typedef const std::string *IteratorPointerType;
//   static constexpr FieldDescriptor::CppType cpp_type =
//       FieldDescriptor::CPPTYPE_STRING;
//   static const Descriptor *GetMessageFieldDescriptor() { return NULL; }
// };

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

    uint16_t ftype = field_vec_[field_id].ftype;
    uint16_t dtype = field_vec_[field_id].dtype;

    using ET = decltype(typeTrait<ftype, dtype>());
    // RefTypeTraits<ftype, dtype>::type return nullptr;
    // field_vec_[field_id].dtype;
    // field_vec_[field_id].ftype;
    // return reflection_.get<T>(data);
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
  template <uint16_t, uint16_t, typename T = void> T typeTrait() {
    throw std::invalid_argument("not support field type or data type");
  };

  template <> int8_t typeTrait<1, 2>() { return 0; };

private:
  phmap::flat_hash_map<std::string, FieldDescriptor *> field_map_;
  std::vector<FieldDescriptor> field_vec_;
};
} // namespace index_lib
