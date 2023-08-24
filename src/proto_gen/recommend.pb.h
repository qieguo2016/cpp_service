// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: recommend.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_recommend_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_recommend_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3016000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3016000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/service.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_recommend_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_recommend_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_recommend_2eproto;
namespace recommend {
class RecommendRequest;
struct RecommendRequestDefaultTypeInternal;
extern RecommendRequestDefaultTypeInternal _RecommendRequest_default_instance_;
class RecommendResponse;
struct RecommendResponseDefaultTypeInternal;
extern RecommendResponseDefaultTypeInternal _RecommendResponse_default_instance_;
}  // namespace recommend
PROTOBUF_NAMESPACE_OPEN
template<> ::recommend::RecommendRequest* Arena::CreateMaybeMessage<::recommend::RecommendRequest>(Arena*);
template<> ::recommend::RecommendResponse* Arena::CreateMaybeMessage<::recommend::RecommendResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace recommend {

// ===================================================================

class RecommendRequest PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:recommend.RecommendRequest) */ {
 public:
  inline RecommendRequest() : RecommendRequest(nullptr) {}
  ~RecommendRequest() override;
  explicit constexpr RecommendRequest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  RecommendRequest(const RecommendRequest& from);
  RecommendRequest(RecommendRequest&& from) noexcept
    : RecommendRequest() {
    *this = ::std::move(from);
  }

  inline RecommendRequest& operator=(const RecommendRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline RecommendRequest& operator=(RecommendRequest&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const RecommendRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const RecommendRequest* internal_default_instance() {
    return reinterpret_cast<const RecommendRequest*>(
               &_RecommendRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(RecommendRequest& a, RecommendRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(RecommendRequest* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RecommendRequest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline RecommendRequest* New() const final {
    return CreateMaybeMessage<RecommendRequest>(nullptr);
  }

  RecommendRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<RecommendRequest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const RecommendRequest& from);
  void MergeFrom(const RecommendRequest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RecommendRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "recommend.RecommendRequest";
  }
  protected:
  explicit RecommendRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kUserIdFieldNumber = 1,
  };
  // int64 user_id = 1;
  bool has_user_id() const;
  private:
  bool _internal_has_user_id() const;
  public:
  void clear_user_id();
  ::PROTOBUF_NAMESPACE_ID::int64 user_id() const;
  void set_user_id(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_user_id() const;
  void _internal_set_user_id(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // @@protoc_insertion_point(class_scope:recommend.RecommendRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::int64 user_id_;
  friend struct ::TableStruct_recommend_2eproto;
};
// -------------------------------------------------------------------

class RecommendResponse PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:recommend.RecommendResponse) */ {
 public:
  inline RecommendResponse() : RecommendResponse(nullptr) {}
  ~RecommendResponse() override;
  explicit constexpr RecommendResponse(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  RecommendResponse(const RecommendResponse& from);
  RecommendResponse(RecommendResponse&& from) noexcept
    : RecommendResponse() {
    *this = ::std::move(from);
  }

  inline RecommendResponse& operator=(const RecommendResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline RecommendResponse& operator=(RecommendResponse&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const RecommendResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const RecommendResponse* internal_default_instance() {
    return reinterpret_cast<const RecommendResponse*>(
               &_RecommendResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(RecommendResponse& a, RecommendResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(RecommendResponse* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RecommendResponse* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline RecommendResponse* New() const final {
    return CreateMaybeMessage<RecommendResponse>(nullptr);
  }

  RecommendResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<RecommendResponse>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const RecommendResponse& from);
  void MergeFrom(const RecommendResponse& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RecommendResponse* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "recommend.RecommendResponse";
  }
  protected:
  explicit RecommendResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMessageFieldNumber = 2,
    kCodeFieldNumber = 1,
  };
  // string message = 2;
  bool has_message() const;
  private:
  bool _internal_has_message() const;
  public:
  void clear_message();
  const std::string& message() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_message(ArgT0&& arg0, ArgT... args);
  std::string* mutable_message();
  std::string* release_message();
  void set_allocated_message(std::string* message);
  private:
  const std::string& _internal_message() const;
  void _internal_set_message(const std::string& value);
  std::string* _internal_mutable_message();
  public:

  // int32 code = 1;
  bool has_code() const;
  private:
  bool _internal_has_code() const;
  public:
  void clear_code();
  ::PROTOBUF_NAMESPACE_ID::int32 code() const;
  void set_code(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_code() const;
  void _internal_set_code(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:recommend.RecommendResponse)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr message_;
  ::PROTOBUF_NAMESPACE_ID::int32 code_;
  friend struct ::TableStruct_recommend_2eproto;
};
// ===================================================================

class RecommendService_Stub;

class RecommendService : public ::PROTOBUF_NAMESPACE_ID::Service {
 protected:
  // This class should be treated as an abstract interface.
  inline RecommendService() {};
 public:
  virtual ~RecommendService();

  typedef RecommendService_Stub Stub;

  static const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* descriptor();

  virtual void Recommend(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::recommend::RecommendRequest* request,
                       ::recommend::RecommendResponse* response,
                       ::google::protobuf::Closure* done);

  // implements Service ----------------------------------------------

  const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor* GetDescriptor();
  void CallMethod(const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method,
                  ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                  const ::PROTOBUF_NAMESPACE_ID::Message* request,
                  ::PROTOBUF_NAMESPACE_ID::Message* response,
                  ::google::protobuf::Closure* done);
  const ::PROTOBUF_NAMESPACE_ID::Message& GetRequestPrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const;
  const ::PROTOBUF_NAMESPACE_ID::Message& GetResponsePrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RecommendService);
};

class RecommendService_Stub : public RecommendService {
 public:
  RecommendService_Stub(::PROTOBUF_NAMESPACE_ID::RpcChannel* channel);
  RecommendService_Stub(::PROTOBUF_NAMESPACE_ID::RpcChannel* channel,
                   ::PROTOBUF_NAMESPACE_ID::Service::ChannelOwnership ownership);
  ~RecommendService_Stub();

  inline ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel() { return channel_; }

  // implements RecommendService ------------------------------------------

  void Recommend(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                       const ::recommend::RecommendRequest* request,
                       ::recommend::RecommendResponse* response,
                       ::google::protobuf::Closure* done);
 private:
  ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel_;
  bool owns_channel_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RecommendService_Stub);
};


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RecommendRequest

// int64 user_id = 1;
inline bool RecommendRequest::_internal_has_user_id() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool RecommendRequest::has_user_id() const {
  return _internal_has_user_id();
}
inline void RecommendRequest::clear_user_id() {
  user_id_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 RecommendRequest::_internal_user_id() const {
  return user_id_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 RecommendRequest::user_id() const {
  // @@protoc_insertion_point(field_get:recommend.RecommendRequest.user_id)
  return _internal_user_id();
}
inline void RecommendRequest::_internal_set_user_id(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _has_bits_[0] |= 0x00000001u;
  user_id_ = value;
}
inline void RecommendRequest::set_user_id(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_user_id(value);
  // @@protoc_insertion_point(field_set:recommend.RecommendRequest.user_id)
}

// -------------------------------------------------------------------

// RecommendResponse

// int32 code = 1;
inline bool RecommendResponse::_internal_has_code() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool RecommendResponse::has_code() const {
  return _internal_has_code();
}
inline void RecommendResponse::clear_code() {
  code_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 RecommendResponse::_internal_code() const {
  return code_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 RecommendResponse::code() const {
  // @@protoc_insertion_point(field_get:recommend.RecommendResponse.code)
  return _internal_code();
}
inline void RecommendResponse::_internal_set_code(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  code_ = value;
}
inline void RecommendResponse::set_code(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_code(value);
  // @@protoc_insertion_point(field_set:recommend.RecommendResponse.code)
}

// string message = 2;
inline bool RecommendResponse::_internal_has_message() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool RecommendResponse::has_message() const {
  return _internal_has_message();
}
inline void RecommendResponse::clear_message() {
  message_.ClearToEmpty();
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& RecommendResponse::message() const {
  // @@protoc_insertion_point(field_get:recommend.RecommendResponse.message)
  return _internal_message();
}
template <typename ArgT0, typename... ArgT>
PROTOBUF_ALWAYS_INLINE
inline void RecommendResponse::set_message(ArgT0&& arg0, ArgT... args) {
 _has_bits_[0] |= 0x00000001u;
 message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArena());
  // @@protoc_insertion_point(field_set:recommend.RecommendResponse.message)
}
inline std::string* RecommendResponse::mutable_message() {
  // @@protoc_insertion_point(field_mutable:recommend.RecommendResponse.message)
  return _internal_mutable_message();
}
inline const std::string& RecommendResponse::_internal_message() const {
  return message_.Get();
}
inline void RecommendResponse::_internal_set_message(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline std::string* RecommendResponse::_internal_mutable_message() {
  _has_bits_[0] |= 0x00000001u;
  return message_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* RecommendResponse::release_message() {
  // @@protoc_insertion_point(field_release:recommend.RecommendResponse.message)
  if (!_internal_has_message()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return message_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void RecommendResponse::set_allocated_message(std::string* message) {
  if (message != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  message_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), message,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:recommend.RecommendResponse.message)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace recommend

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_recommend_2eproto