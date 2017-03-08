// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: coprocessor.proto

#ifndef PROTOBUF_coprocessor_2eproto__INCLUDED
#define PROTOBUF_coprocessor_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3001000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3001000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "errorpb.pb.h"
#include "kvrpcpb.pb.h"
// @@protoc_insertion_point(includes)

namespace coprocessor {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_coprocessor_2eproto();
void protobuf_InitDefaults_coprocessor_2eproto();
void protobuf_AssignDesc_coprocessor_2eproto();
void protobuf_ShutdownFile_coprocessor_2eproto();

class KeyRange;
class Request;
class Response;

// ===================================================================

class KeyRange : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:coprocessor.KeyRange) */ {
 public:
  KeyRange();
  virtual ~KeyRange();

  KeyRange(const KeyRange& from);

  inline KeyRange& operator=(const KeyRange& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const KeyRange& default_instance();

  static const KeyRange* internal_default_instance();

  void Swap(KeyRange* other);

  // implements Message ----------------------------------------------

  inline KeyRange* New() const { return New(NULL); }

  KeyRange* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const KeyRange& from);
  void MergeFrom(const KeyRange& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(KeyRange* other);
  void UnsafeMergeFrom(const KeyRange& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional bytes start = 1;
  bool has_start() const;
  void clear_start();
  static const int kStartFieldNumber = 1;
  const ::std::string& start() const;
  void set_start(const ::std::string& value);
  void set_start(const char* value);
  void set_start(const void* value, size_t size);
  ::std::string* mutable_start();
  ::std::string* release_start();
  void set_allocated_start(::std::string* start);

  // optional bytes end = 2;
  bool has_end() const;
  void clear_end();
  static const int kEndFieldNumber = 2;
  const ::std::string& end() const;
  void set_end(const ::std::string& value);
  void set_end(const char* value);
  void set_end(const void* value, size_t size);
  ::std::string* mutable_end();
  ::std::string* release_end();
  void set_allocated_end(::std::string* end);

  // @@protoc_insertion_point(class_scope:coprocessor.KeyRange)
 private:
  inline void set_has_start();
  inline void clear_has_start();
  inline void set_has_end();
  inline void clear_has_end();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr start_;
  ::google::protobuf::internal::ArenaStringPtr end_;
  friend void  protobuf_InitDefaults_coprocessor_2eproto_impl();
  friend void  protobuf_AddDesc_coprocessor_2eproto_impl();
  friend void protobuf_AssignDesc_coprocessor_2eproto();
  friend void protobuf_ShutdownFile_coprocessor_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<KeyRange> KeyRange_default_instance_;

// -------------------------------------------------------------------

class Request : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:coprocessor.Request) */ {
 public:
  Request();
  virtual ~Request();

  Request(const Request& from);

  inline Request& operator=(const Request& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Request& default_instance();

  static const Request* internal_default_instance();

  void Swap(Request* other);

  // implements Message ----------------------------------------------

  inline Request* New() const { return New(NULL); }

  Request* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Request& from);
  void MergeFrom(const Request& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Request* other);
  void UnsafeMergeFrom(const Request& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .kvrpcpb.Context context = 1;
  bool has_context() const;
  void clear_context();
  static const int kContextFieldNumber = 1;
  const ::kvrpcpb::Context& context() const;
  ::kvrpcpb::Context* mutable_context();
  ::kvrpcpb::Context* release_context();
  void set_allocated_context(::kvrpcpb::Context* context);

  // optional int64 tp = 2;
  bool has_tp() const;
  void clear_tp();
  static const int kTpFieldNumber = 2;
  ::google::protobuf::int64 tp() const;
  void set_tp(::google::protobuf::int64 value);

  // optional bytes data = 3;
  bool has_data() const;
  void clear_data();
  static const int kDataFieldNumber = 3;
  const ::std::string& data() const;
  void set_data(const ::std::string& value);
  void set_data(const char* value);
  void set_data(const void* value, size_t size);
  ::std::string* mutable_data();
  ::std::string* release_data();
  void set_allocated_data(::std::string* data);

  // repeated .coprocessor.KeyRange ranges = 4;
  int ranges_size() const;
  void clear_ranges();
  static const int kRangesFieldNumber = 4;
  const ::coprocessor::KeyRange& ranges(int index) const;
  ::coprocessor::KeyRange* mutable_ranges(int index);
  ::coprocessor::KeyRange* add_ranges();
  ::google::protobuf::RepeatedPtrField< ::coprocessor::KeyRange >*
      mutable_ranges();
  const ::google::protobuf::RepeatedPtrField< ::coprocessor::KeyRange >&
      ranges() const;

  // @@protoc_insertion_point(class_scope:coprocessor.Request)
 private:
  inline void set_has_context();
  inline void clear_has_context();
  inline void set_has_tp();
  inline void clear_has_tp();
  inline void set_has_data();
  inline void clear_has_data();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::coprocessor::KeyRange > ranges_;
  ::google::protobuf::internal::ArenaStringPtr data_;
  ::kvrpcpb::Context* context_;
  ::google::protobuf::int64 tp_;
  friend void  protobuf_InitDefaults_coprocessor_2eproto_impl();
  friend void  protobuf_AddDesc_coprocessor_2eproto_impl();
  friend void protobuf_AssignDesc_coprocessor_2eproto();
  friend void protobuf_ShutdownFile_coprocessor_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<Request> Request_default_instance_;

// -------------------------------------------------------------------

class Response : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:coprocessor.Response) */ {
 public:
  Response();
  virtual ~Response();

  Response(const Response& from);

  inline Response& operator=(const Response& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Response& default_instance();

  static const Response* internal_default_instance();

  void Swap(Response* other);

  // implements Message ----------------------------------------------

  inline Response* New() const { return New(NULL); }

  Response* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Response& from);
  void MergeFrom(const Response& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Response* other);
  void UnsafeMergeFrom(const Response& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional bytes data = 1;
  bool has_data() const;
  void clear_data();
  static const int kDataFieldNumber = 1;
  const ::std::string& data() const;
  void set_data(const ::std::string& value);
  void set_data(const char* value);
  void set_data(const void* value, size_t size);
  ::std::string* mutable_data();
  ::std::string* release_data();
  void set_allocated_data(::std::string* data);

  // optional .errorpb.Error region_error = 2;
  bool has_region_error() const;
  void clear_region_error();
  static const int kRegionErrorFieldNumber = 2;
  const ::errorpb::Error& region_error() const;
  ::errorpb::Error* mutable_region_error();
  ::errorpb::Error* release_region_error();
  void set_allocated_region_error(::errorpb::Error* region_error);

  // optional .kvrpcpb.LockInfo locked = 3;
  bool has_locked() const;
  void clear_locked();
  static const int kLockedFieldNumber = 3;
  const ::kvrpcpb::LockInfo& locked() const;
  ::kvrpcpb::LockInfo* mutable_locked();
  ::kvrpcpb::LockInfo* release_locked();
  void set_allocated_locked(::kvrpcpb::LockInfo* locked);

  // optional string other_error = 4;
  bool has_other_error() const;
  void clear_other_error();
  static const int kOtherErrorFieldNumber = 4;
  const ::std::string& other_error() const;
  void set_other_error(const ::std::string& value);
  void set_other_error(const char* value);
  void set_other_error(const char* value, size_t size);
  ::std::string* mutable_other_error();
  ::std::string* release_other_error();
  void set_allocated_other_error(::std::string* other_error);

  // @@protoc_insertion_point(class_scope:coprocessor.Response)
 private:
  inline void set_has_data();
  inline void clear_has_data();
  inline void set_has_region_error();
  inline void clear_has_region_error();
  inline void set_has_locked();
  inline void clear_has_locked();
  inline void set_has_other_error();
  inline void clear_has_other_error();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr data_;
  ::google::protobuf::internal::ArenaStringPtr other_error_;
  ::errorpb::Error* region_error_;
  ::kvrpcpb::LockInfo* locked_;
  friend void  protobuf_InitDefaults_coprocessor_2eproto_impl();
  friend void  protobuf_AddDesc_coprocessor_2eproto_impl();
  friend void protobuf_AssignDesc_coprocessor_2eproto();
  friend void protobuf_ShutdownFile_coprocessor_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<Response> Response_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// KeyRange

// optional bytes start = 1;
inline bool KeyRange::has_start() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void KeyRange::set_has_start() {
  _has_bits_[0] |= 0x00000001u;
}
inline void KeyRange::clear_has_start() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void KeyRange::clear_start() {
  start_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_start();
}
inline const ::std::string& KeyRange::start() const {
  // @@protoc_insertion_point(field_get:coprocessor.KeyRange.start)
  return start_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void KeyRange::set_start(const ::std::string& value) {
  set_has_start();
  start_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:coprocessor.KeyRange.start)
}
inline void KeyRange::set_start(const char* value) {
  set_has_start();
  start_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:coprocessor.KeyRange.start)
}
inline void KeyRange::set_start(const void* value, size_t size) {
  set_has_start();
  start_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:coprocessor.KeyRange.start)
}
inline ::std::string* KeyRange::mutable_start() {
  set_has_start();
  // @@protoc_insertion_point(field_mutable:coprocessor.KeyRange.start)
  return start_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* KeyRange::release_start() {
  // @@protoc_insertion_point(field_release:coprocessor.KeyRange.start)
  clear_has_start();
  return start_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void KeyRange::set_allocated_start(::std::string* start) {
  if (start != NULL) {
    set_has_start();
  } else {
    clear_has_start();
  }
  start_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), start);
  // @@protoc_insertion_point(field_set_allocated:coprocessor.KeyRange.start)
}

// optional bytes end = 2;
inline bool KeyRange::has_end() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void KeyRange::set_has_end() {
  _has_bits_[0] |= 0x00000002u;
}
inline void KeyRange::clear_has_end() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void KeyRange::clear_end() {
  end_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_end();
}
inline const ::std::string& KeyRange::end() const {
  // @@protoc_insertion_point(field_get:coprocessor.KeyRange.end)
  return end_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void KeyRange::set_end(const ::std::string& value) {
  set_has_end();
  end_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:coprocessor.KeyRange.end)
}
inline void KeyRange::set_end(const char* value) {
  set_has_end();
  end_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:coprocessor.KeyRange.end)
}
inline void KeyRange::set_end(const void* value, size_t size) {
  set_has_end();
  end_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:coprocessor.KeyRange.end)
}
inline ::std::string* KeyRange::mutable_end() {
  set_has_end();
  // @@protoc_insertion_point(field_mutable:coprocessor.KeyRange.end)
  return end_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* KeyRange::release_end() {
  // @@protoc_insertion_point(field_release:coprocessor.KeyRange.end)
  clear_has_end();
  return end_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void KeyRange::set_allocated_end(::std::string* end) {
  if (end != NULL) {
    set_has_end();
  } else {
    clear_has_end();
  }
  end_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), end);
  // @@protoc_insertion_point(field_set_allocated:coprocessor.KeyRange.end)
}

inline const KeyRange* KeyRange::internal_default_instance() {
  return &KeyRange_default_instance_.get();
}
// -------------------------------------------------------------------

// Request

// optional .kvrpcpb.Context context = 1;
inline bool Request::has_context() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Request::set_has_context() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Request::clear_has_context() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Request::clear_context() {
  if (context_ != NULL) context_->::kvrpcpb::Context::Clear();
  clear_has_context();
}
inline const ::kvrpcpb::Context& Request::context() const {
  // @@protoc_insertion_point(field_get:coprocessor.Request.context)
  return context_ != NULL ? *context_
                         : *::kvrpcpb::Context::internal_default_instance();
}
inline ::kvrpcpb::Context* Request::mutable_context() {
  set_has_context();
  if (context_ == NULL) {
    context_ = new ::kvrpcpb::Context;
  }
  // @@protoc_insertion_point(field_mutable:coprocessor.Request.context)
  return context_;
}
inline ::kvrpcpb::Context* Request::release_context() {
  // @@protoc_insertion_point(field_release:coprocessor.Request.context)
  clear_has_context();
  ::kvrpcpb::Context* temp = context_;
  context_ = NULL;
  return temp;
}
inline void Request::set_allocated_context(::kvrpcpb::Context* context) {
  delete context_;
  context_ = context;
  if (context) {
    set_has_context();
  } else {
    clear_has_context();
  }
  // @@protoc_insertion_point(field_set_allocated:coprocessor.Request.context)
}

// optional int64 tp = 2;
inline bool Request::has_tp() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Request::set_has_tp() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Request::clear_has_tp() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Request::clear_tp() {
  tp_ = GOOGLE_LONGLONG(0);
  clear_has_tp();
}
inline ::google::protobuf::int64 Request::tp() const {
  // @@protoc_insertion_point(field_get:coprocessor.Request.tp)
  return tp_;
}
inline void Request::set_tp(::google::protobuf::int64 value) {
  set_has_tp();
  tp_ = value;
  // @@protoc_insertion_point(field_set:coprocessor.Request.tp)
}

// optional bytes data = 3;
inline bool Request::has_data() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Request::set_has_data() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Request::clear_has_data() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Request::clear_data() {
  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_data();
}
inline const ::std::string& Request::data() const {
  // @@protoc_insertion_point(field_get:coprocessor.Request.data)
  return data_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Request::set_data(const ::std::string& value) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:coprocessor.Request.data)
}
inline void Request::set_data(const char* value) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:coprocessor.Request.data)
}
inline void Request::set_data(const void* value, size_t size) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:coprocessor.Request.data)
}
inline ::std::string* Request::mutable_data() {
  set_has_data();
  // @@protoc_insertion_point(field_mutable:coprocessor.Request.data)
  return data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Request::release_data() {
  // @@protoc_insertion_point(field_release:coprocessor.Request.data)
  clear_has_data();
  return data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Request::set_allocated_data(::std::string* data) {
  if (data != NULL) {
    set_has_data();
  } else {
    clear_has_data();
  }
  data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), data);
  // @@protoc_insertion_point(field_set_allocated:coprocessor.Request.data)
}

// repeated .coprocessor.KeyRange ranges = 4;
inline int Request::ranges_size() const {
  return ranges_.size();
}
inline void Request::clear_ranges() {
  ranges_.Clear();
}
inline const ::coprocessor::KeyRange& Request::ranges(int index) const {
  // @@protoc_insertion_point(field_get:coprocessor.Request.ranges)
  return ranges_.Get(index);
}
inline ::coprocessor::KeyRange* Request::mutable_ranges(int index) {
  // @@protoc_insertion_point(field_mutable:coprocessor.Request.ranges)
  return ranges_.Mutable(index);
}
inline ::coprocessor::KeyRange* Request::add_ranges() {
  // @@protoc_insertion_point(field_add:coprocessor.Request.ranges)
  return ranges_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::coprocessor::KeyRange >*
Request::mutable_ranges() {
  // @@protoc_insertion_point(field_mutable_list:coprocessor.Request.ranges)
  return &ranges_;
}
inline const ::google::protobuf::RepeatedPtrField< ::coprocessor::KeyRange >&
Request::ranges() const {
  // @@protoc_insertion_point(field_list:coprocessor.Request.ranges)
  return ranges_;
}

inline const Request* Request::internal_default_instance() {
  return &Request_default_instance_.get();
}
// -------------------------------------------------------------------

// Response

// optional bytes data = 1;
inline bool Response::has_data() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Response::set_has_data() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Response::clear_has_data() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Response::clear_data() {
  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_data();
}
inline const ::std::string& Response::data() const {
  // @@protoc_insertion_point(field_get:coprocessor.Response.data)
  return data_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Response::set_data(const ::std::string& value) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:coprocessor.Response.data)
}
inline void Response::set_data(const char* value) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:coprocessor.Response.data)
}
inline void Response::set_data(const void* value, size_t size) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:coprocessor.Response.data)
}
inline ::std::string* Response::mutable_data() {
  set_has_data();
  // @@protoc_insertion_point(field_mutable:coprocessor.Response.data)
  return data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Response::release_data() {
  // @@protoc_insertion_point(field_release:coprocessor.Response.data)
  clear_has_data();
  return data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Response::set_allocated_data(::std::string* data) {
  if (data != NULL) {
    set_has_data();
  } else {
    clear_has_data();
  }
  data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), data);
  // @@protoc_insertion_point(field_set_allocated:coprocessor.Response.data)
}

// optional .errorpb.Error region_error = 2;
inline bool Response::has_region_error() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Response::set_has_region_error() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Response::clear_has_region_error() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Response::clear_region_error() {
  if (region_error_ != NULL) region_error_->::errorpb::Error::Clear();
  clear_has_region_error();
}
inline const ::errorpb::Error& Response::region_error() const {
  // @@protoc_insertion_point(field_get:coprocessor.Response.region_error)
  return region_error_ != NULL ? *region_error_
                         : *::errorpb::Error::internal_default_instance();
}
inline ::errorpb::Error* Response::mutable_region_error() {
  set_has_region_error();
  if (region_error_ == NULL) {
    region_error_ = new ::errorpb::Error;
  }
  // @@protoc_insertion_point(field_mutable:coprocessor.Response.region_error)
  return region_error_;
}
inline ::errorpb::Error* Response::release_region_error() {
  // @@protoc_insertion_point(field_release:coprocessor.Response.region_error)
  clear_has_region_error();
  ::errorpb::Error* temp = region_error_;
  region_error_ = NULL;
  return temp;
}
inline void Response::set_allocated_region_error(::errorpb::Error* region_error) {
  delete region_error_;
  region_error_ = region_error;
  if (region_error) {
    set_has_region_error();
  } else {
    clear_has_region_error();
  }
  // @@protoc_insertion_point(field_set_allocated:coprocessor.Response.region_error)
}

// optional .kvrpcpb.LockInfo locked = 3;
inline bool Response::has_locked() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Response::set_has_locked() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Response::clear_has_locked() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Response::clear_locked() {
  if (locked_ != NULL) locked_->::kvrpcpb::LockInfo::Clear();
  clear_has_locked();
}
inline const ::kvrpcpb::LockInfo& Response::locked() const {
  // @@protoc_insertion_point(field_get:coprocessor.Response.locked)
  return locked_ != NULL ? *locked_
                         : *::kvrpcpb::LockInfo::internal_default_instance();
}
inline ::kvrpcpb::LockInfo* Response::mutable_locked() {
  set_has_locked();
  if (locked_ == NULL) {
    locked_ = new ::kvrpcpb::LockInfo;
  }
  // @@protoc_insertion_point(field_mutable:coprocessor.Response.locked)
  return locked_;
}
inline ::kvrpcpb::LockInfo* Response::release_locked() {
  // @@protoc_insertion_point(field_release:coprocessor.Response.locked)
  clear_has_locked();
  ::kvrpcpb::LockInfo* temp = locked_;
  locked_ = NULL;
  return temp;
}
inline void Response::set_allocated_locked(::kvrpcpb::LockInfo* locked) {
  delete locked_;
  locked_ = locked;
  if (locked) {
    set_has_locked();
  } else {
    clear_has_locked();
  }
  // @@protoc_insertion_point(field_set_allocated:coprocessor.Response.locked)
}

// optional string other_error = 4;
inline bool Response::has_other_error() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Response::set_has_other_error() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Response::clear_has_other_error() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Response::clear_other_error() {
  other_error_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_other_error();
}
inline const ::std::string& Response::other_error() const {
  // @@protoc_insertion_point(field_get:coprocessor.Response.other_error)
  return other_error_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Response::set_other_error(const ::std::string& value) {
  set_has_other_error();
  other_error_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:coprocessor.Response.other_error)
}
inline void Response::set_other_error(const char* value) {
  set_has_other_error();
  other_error_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:coprocessor.Response.other_error)
}
inline void Response::set_other_error(const char* value, size_t size) {
  set_has_other_error();
  other_error_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:coprocessor.Response.other_error)
}
inline ::std::string* Response::mutable_other_error() {
  set_has_other_error();
  // @@protoc_insertion_point(field_mutable:coprocessor.Response.other_error)
  return other_error_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Response::release_other_error() {
  // @@protoc_insertion_point(field_release:coprocessor.Response.other_error)
  clear_has_other_error();
  return other_error_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Response::set_allocated_other_error(::std::string* other_error) {
  if (other_error != NULL) {
    set_has_other_error();
  } else {
    clear_has_other_error();
  }
  other_error_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), other_error);
  // @@protoc_insertion_point(field_set_allocated:coprocessor.Response.other_error)
}

inline const Response* Response::internal_default_instance() {
  return &Response_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace coprocessor

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_coprocessor_2eproto__INCLUDED
