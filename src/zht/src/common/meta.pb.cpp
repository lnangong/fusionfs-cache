// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "../../inc/meta.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* Package_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Package_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_meta_2eproto() {
  protobuf_AddDesc_meta_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "meta.proto");
  GOOGLE_CHECK(file != NULL);
  Package_descriptor_ = file->message_type(0);
  static const int Package_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Package, virtualpath_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Package, num_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Package, realfullpath_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Package, isdir_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Package, listitem_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Package, openmode_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Package, mode_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Package, operation_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Package, replicano_),
  };
  Package_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Package_descriptor_,
      Package::default_instance_,
      Package_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Package, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Package, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Package));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_meta_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Package_descriptor_, &Package::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_meta_2eproto() {
  delete Package::default_instance_;
  delete Package_reflection_;
}

void protobuf_AddDesc_meta_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\nmeta.proto\"\250\001\n\007Package\022\023\n\013virtualPath\030"
    "\001 \001(\014\022\013\n\003num\030\002 \001(\005\022\024\n\014realFullPath\030\003 \001(\014"
    "\022\r\n\005isDir\030\004 \001(\010\022\020\n\010listItem\030\005 \003(\014\022\020\n\010ope"
    "nMode\030\006 \001(\005\022\014\n\004mode\030\007 \001(\005\022\021\n\tOperation\030\010"
    " \001(\005\022\021\n\treplicaNo\030\t \001(\005", 183);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "meta.proto", &protobuf_RegisterTypes);
  Package::default_instance_ = new Package();
  Package::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_meta_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_meta_2eproto {
  StaticDescriptorInitializer_meta_2eproto() {
    protobuf_AddDesc_meta_2eproto();
  }
} static_descriptor_initializer_meta_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int Package::kVirtualPathFieldNumber;
const int Package::kNumFieldNumber;
const int Package::kRealFullPathFieldNumber;
const int Package::kIsDirFieldNumber;
const int Package::kListItemFieldNumber;
const int Package::kOpenModeFieldNumber;
const int Package::kModeFieldNumber;
const int Package::kOperationFieldNumber;
const int Package::kReplicaNoFieldNumber;
#endif  // !_MSC_VER

Package::Package()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Package::InitAsDefaultInstance() {
}

Package::Package(const Package& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Package::SharedCtor() {
  _cached_size_ = 0;
  virtualpath_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  num_ = 0;
  realfullpath_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  isdir_ = false;
  openmode_ = 0;
  mode_ = 0;
  operation_ = 0;
  replicano_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Package::~Package() {
  SharedDtor();
}

void Package::SharedDtor() {
  if (virtualpath_ != &::google::protobuf::internal::kEmptyString) {
    delete virtualpath_;
  }
  if (realfullpath_ != &::google::protobuf::internal::kEmptyString) {
    delete realfullpath_;
  }
  if (this != default_instance_) {
  }
}

void Package::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Package::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Package_descriptor_;
}

const Package& Package::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_meta_2eproto();  return *default_instance_;
}

Package* Package::default_instance_ = NULL;

Package* Package::New() const {
  return new Package;
}

void Package::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_virtualpath()) {
      if (virtualpath_ != &::google::protobuf::internal::kEmptyString) {
        virtualpath_->clear();
      }
    }
    num_ = 0;
    if (has_realfullpath()) {
      if (realfullpath_ != &::google::protobuf::internal::kEmptyString) {
        realfullpath_->clear();
      }
    }
    isdir_ = false;
    openmode_ = 0;
    mode_ = 0;
    operation_ = 0;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    replicano_ = 0;
  }
  listitem_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Package::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional bytes virtualPath = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_virtualpath()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_num;
        break;
      }
      
      // optional int32 num = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &num_)));
          set_has_num();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_realFullPath;
        break;
      }
      
      // optional bytes realFullPath = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_realFullPath:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_realfullpath()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_isDir;
        break;
      }
      
      // optional bool isDir = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_isDir:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &isdir_)));
          set_has_isdir();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_listItem;
        break;
      }
      
      // repeated bytes listItem = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_listItem:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->add_listitem()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_listItem;
        if (input->ExpectTag(48)) goto parse_openMode;
        break;
      }
      
      // optional int32 openMode = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_openMode:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &openmode_)));
          set_has_openmode();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_mode;
        break;
      }
      
      // optional int32 mode = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_mode:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &mode_)));
          set_has_mode();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_Operation;
        break;
      }
      
      // optional int32 Operation = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_Operation:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &operation_)));
          set_has_operation();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(72)) goto parse_replicaNo;
        break;
      }
      
      // optional int32 replicaNo = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_replicaNo:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &replicano_)));
          set_has_replicano();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Package::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional bytes virtualPath = 1;
  if (has_virtualpath()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      1, this->virtualpath(), output);
  }
  
  // optional int32 num = 2;
  if (has_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->num(), output);
  }
  
  // optional bytes realFullPath = 3;
  if (has_realfullpath()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      3, this->realfullpath(), output);
  }
  
  // optional bool isDir = 4;
  if (has_isdir()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->isdir(), output);
  }
  
  // repeated bytes listItem = 5;
  for (int i = 0; i < this->listitem_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      5, this->listitem(i), output);
  }
  
  // optional int32 openMode = 6;
  if (has_openmode()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->openmode(), output);
  }
  
  // optional int32 mode = 7;
  if (has_mode()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(7, this->mode(), output);
  }
  
  // optional int32 Operation = 8;
  if (has_operation()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(8, this->operation(), output);
  }
  
  // optional int32 replicaNo = 9;
  if (has_replicano()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(9, this->replicano(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Package::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional bytes virtualPath = 1;
  if (has_virtualpath()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        1, this->virtualpath(), target);
  }
  
  // optional int32 num = 2;
  if (has_num()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->num(), target);
  }
  
  // optional bytes realFullPath = 3;
  if (has_realfullpath()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        3, this->realfullpath(), target);
  }
  
  // optional bool isDir = 4;
  if (has_isdir()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->isdir(), target);
  }
  
  // repeated bytes listItem = 5;
  for (int i = 0; i < this->listitem_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteBytesToArray(5, this->listitem(i), target);
  }
  
  // optional int32 openMode = 6;
  if (has_openmode()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->openmode(), target);
  }
  
  // optional int32 mode = 7;
  if (has_mode()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(7, this->mode(), target);
  }
  
  // optional int32 Operation = 8;
  if (has_operation()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(8, this->operation(), target);
  }
  
  // optional int32 replicaNo = 9;
  if (has_replicano()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(9, this->replicano(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Package::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional bytes virtualPath = 1;
    if (has_virtualpath()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->virtualpath());
    }
    
    // optional int32 num = 2;
    if (has_num()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->num());
    }
    
    // optional bytes realFullPath = 3;
    if (has_realfullpath()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->realfullpath());
    }
    
    // optional bool isDir = 4;
    if (has_isdir()) {
      total_size += 1 + 1;
    }
    
    // optional int32 openMode = 6;
    if (has_openmode()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->openmode());
    }
    
    // optional int32 mode = 7;
    if (has_mode()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->mode());
    }
    
    // optional int32 Operation = 8;
    if (has_operation()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->operation());
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional int32 replicaNo = 9;
    if (has_replicano()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->replicano());
    }
    
  }
  // repeated bytes listItem = 5;
  total_size += 1 * this->listitem_size();
  for (int i = 0; i < this->listitem_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::BytesSize(
      this->listitem(i));
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Package::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Package* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Package*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Package::MergeFrom(const Package& from) {
  GOOGLE_CHECK_NE(&from, this);
  listitem_.MergeFrom(from.listitem_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_virtualpath()) {
      set_virtualpath(from.virtualpath());
    }
    if (from.has_num()) {
      set_num(from.num());
    }
    if (from.has_realfullpath()) {
      set_realfullpath(from.realfullpath());
    }
    if (from.has_isdir()) {
      set_isdir(from.isdir());
    }
    if (from.has_openmode()) {
      set_openmode(from.openmode());
    }
    if (from.has_mode()) {
      set_mode(from.mode());
    }
    if (from.has_operation()) {
      set_operation(from.operation());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_replicano()) {
      set_replicano(from.replicano());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Package::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Package::CopyFrom(const Package& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Package::IsInitialized() const {
  
  return true;
}

void Package::Swap(Package* other) {
  if (other != this) {
    std::swap(virtualpath_, other->virtualpath_);
    std::swap(num_, other->num_);
    std::swap(realfullpath_, other->realfullpath_);
    std::swap(isdir_, other->isdir_);
    listitem_.Swap(&other->listitem_);
    std::swap(openmode_, other->openmode_);
    std::swap(mode_, other->mode_);
    std::swap(operation_, other->operation_);
    std::swap(replicano_, other->replicano_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Package::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Package_descriptor_;
  metadata.reflection = Package_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
