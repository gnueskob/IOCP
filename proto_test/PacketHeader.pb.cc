// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PacketHeader.proto

#include "PacketHeader.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace lsbProto {
class PacketHeaderDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<PacketHeader> _instance;
} _PacketHeader_default_instance_;
}  // namespace lsbProto
static void InitDefaultsscc_info_PacketHeader_PacketHeader_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::lsbProto::_PacketHeader_default_instance_;
    new (ptr) ::lsbProto::PacketHeader();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::lsbProto::PacketHeader::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_PacketHeader_PacketHeader_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_PacketHeader_PacketHeader_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_PacketHeader_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_PacketHeader_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_PacketHeader_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_PacketHeader_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::lsbProto::PacketHeader, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::lsbProto::PacketHeader, totalsize_),
  PROTOBUF_FIELD_OFFSET(::lsbProto::PacketHeader, packetid_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::lsbProto::PacketHeader)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::lsbProto::_PacketHeader_default_instance_),
};

const char descriptor_table_protodef_PacketHeader_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\022PacketHeader.proto\022\010lsbProto\"\204\004\n\014Packe"
  "tHeader\022\021\n\ttotalSize\030\001 \001(\005\0221\n\010packetId\030\002"
  " \001(\0162\037.lsbProto.PacketHeader.PacketId\"\255\003"
  "\n\010PacketId\022\r\n\tUNDEFINED\020\000\022\033\n\027NTF_SYS_CON"
  "NECT_SESSION\020\n\022\031\n\025NTF_SYS_CLOSE_SESSION\020"
  "\013\022\r\n\tLOGIN_REQ\020\025\022\r\n\tLOGIN_RES\020\026\022\016\n\nLOGOU"
  "T_REQ\020\032\022\016\n\nLOGOUT_RES\020\033\022\022\n\016ROOM_ENTER_RE"
  "Q\020\037\022\022\n\016ROOM_ENTER_RES\020 \022\033\n\027ROOM_ENTER_NE"
  "W_USER_NTF\020!\022\022\n\016ROOM_USER_LIST\020\"\022\022\n\016ROOM"
  "_LEAVE_REQ\020$\022\022\n\016ROOM_LEAVE_RES\020%\022\027\n\023ROOM"
  "_LEAVE_USER_NTF\020&\022\021\n\rROOM_CHAT_REQ\020*\022\021\n\r"
  "ROOM_CHAT_RES\020+\022\021\n\rROOM_CHAT_NTF\020,\022\031\n\025RO"
  "OM_CHANGED_INFO_NTF\020.\022\021\n\014DEV_ECHO_REQ\020\361\001"
  "\022\021\n\014DEV_ECHO_RES\020\362\001\022\010\n\003MAX\020\200\002b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_PacketHeader_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_PacketHeader_2eproto_sccs[1] = {
  &scc_info_PacketHeader_PacketHeader_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_PacketHeader_2eproto_once;
static bool descriptor_table_PacketHeader_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_PacketHeader_2eproto = {
  &descriptor_table_PacketHeader_2eproto_initialized, descriptor_table_protodef_PacketHeader_2eproto, "PacketHeader.proto", 557,
  &descriptor_table_PacketHeader_2eproto_once, descriptor_table_PacketHeader_2eproto_sccs, descriptor_table_PacketHeader_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_PacketHeader_2eproto::offsets,
  file_level_metadata_PacketHeader_2eproto, 1, file_level_enum_descriptors_PacketHeader_2eproto, file_level_service_descriptors_PacketHeader_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_PacketHeader_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_PacketHeader_2eproto), true);
namespace lsbProto {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PacketHeader_PacketId_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_PacketHeader_2eproto);
  return file_level_enum_descriptors_PacketHeader_2eproto[0];
}
bool PacketHeader_PacketId_IsValid(int value) {
  switch (value) {
    case 0:
    case 10:
    case 11:
    case 21:
    case 22:
    case 26:
    case 27:
    case 31:
    case 32:
    case 33:
    case 34:
    case 36:
    case 37:
    case 38:
    case 42:
    case 43:
    case 44:
    case 46:
    case 241:
    case 242:
    case 256:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr PacketHeader_PacketId PacketHeader::UNDEFINED;
constexpr PacketHeader_PacketId PacketHeader::NTF_SYS_CONNECT_SESSION;
constexpr PacketHeader_PacketId PacketHeader::NTF_SYS_CLOSE_SESSION;
constexpr PacketHeader_PacketId PacketHeader::LOGIN_REQ;
constexpr PacketHeader_PacketId PacketHeader::LOGIN_RES;
constexpr PacketHeader_PacketId PacketHeader::LOGOUT_REQ;
constexpr PacketHeader_PacketId PacketHeader::LOGOUT_RES;
constexpr PacketHeader_PacketId PacketHeader::ROOM_ENTER_REQ;
constexpr PacketHeader_PacketId PacketHeader::ROOM_ENTER_RES;
constexpr PacketHeader_PacketId PacketHeader::ROOM_ENTER_NEW_USER_NTF;
constexpr PacketHeader_PacketId PacketHeader::ROOM_USER_LIST;
constexpr PacketHeader_PacketId PacketHeader::ROOM_LEAVE_REQ;
constexpr PacketHeader_PacketId PacketHeader::ROOM_LEAVE_RES;
constexpr PacketHeader_PacketId PacketHeader::ROOM_LEAVE_USER_NTF;
constexpr PacketHeader_PacketId PacketHeader::ROOM_CHAT_REQ;
constexpr PacketHeader_PacketId PacketHeader::ROOM_CHAT_RES;
constexpr PacketHeader_PacketId PacketHeader::ROOM_CHAT_NTF;
constexpr PacketHeader_PacketId PacketHeader::ROOM_CHANGED_INFO_NTF;
constexpr PacketHeader_PacketId PacketHeader::DEV_ECHO_REQ;
constexpr PacketHeader_PacketId PacketHeader::DEV_ECHO_RES;
constexpr PacketHeader_PacketId PacketHeader::MAX;
constexpr PacketHeader_PacketId PacketHeader::PacketId_MIN;
constexpr PacketHeader_PacketId PacketHeader::PacketId_MAX;
constexpr int PacketHeader::PacketId_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

void PacketHeader::InitAsDefaultInstance() {
}
class PacketHeader::_Internal {
 public:
};

PacketHeader::PacketHeader()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:lsbProto.PacketHeader)
}
PacketHeader::PacketHeader(const PacketHeader& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&totalsize_, &from.totalsize_,
    static_cast<size_t>(reinterpret_cast<char*>(&packetid_) -
    reinterpret_cast<char*>(&totalsize_)) + sizeof(packetid_));
  // @@protoc_insertion_point(copy_constructor:lsbProto.PacketHeader)
}

void PacketHeader::SharedCtor() {
  ::memset(&totalsize_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&packetid_) -
      reinterpret_cast<char*>(&totalsize_)) + sizeof(packetid_));
}

PacketHeader::~PacketHeader() {
  // @@protoc_insertion_point(destructor:lsbProto.PacketHeader)
  SharedDtor();
}

void PacketHeader::SharedDtor() {
}

void PacketHeader::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const PacketHeader& PacketHeader::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_PacketHeader_PacketHeader_2eproto.base);
  return *internal_default_instance();
}


void PacketHeader::Clear() {
// @@protoc_insertion_point(message_clear_start:lsbProto.PacketHeader)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&totalsize_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&packetid_) -
      reinterpret_cast<char*>(&totalsize_)) + sizeof(packetid_));
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* PacketHeader::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 totalSize = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          totalsize_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .lsbProto.PacketHeader.PacketId packetId = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
          set_packetid(static_cast<::lsbProto::PacketHeader_PacketId>(val));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool PacketHeader::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:lsbProto.PacketHeader)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 totalSize = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (8 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32>(
                 input, &totalsize_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .lsbProto.PacketHeader.PacketId packetId = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (16 & 0xFF)) {
          int value = 0;
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   int, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          set_packetid(static_cast< ::lsbProto::PacketHeader_PacketId >(value));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:lsbProto.PacketHeader)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:lsbProto.PacketHeader)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void PacketHeader::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:lsbProto.PacketHeader)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 totalSize = 1;
  if (this->totalsize() != 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32(1, this->totalsize(), output);
  }

  // .lsbProto.PacketHeader.PacketId packetId = 2;
  if (this->packetid() != 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnum(
      2, this->packetid(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:lsbProto.PacketHeader)
}

::PROTOBUF_NAMESPACE_ID::uint8* PacketHeader::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:lsbProto.PacketHeader)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 totalSize = 1;
  if (this->totalsize() != 0) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->totalsize(), target);
  }

  // .lsbProto.PacketHeader.PacketId packetId = 2;
  if (this->packetid() != 0) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      2, this->packetid(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:lsbProto.PacketHeader)
  return target;
}

size_t PacketHeader::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:lsbProto.PacketHeader)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 totalSize = 1;
  if (this->totalsize() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->totalsize());
  }

  // .lsbProto.PacketHeader.PacketId packetId = 2;
  if (this->packetid() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->packetid());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void PacketHeader::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:lsbProto.PacketHeader)
  GOOGLE_DCHECK_NE(&from, this);
  const PacketHeader* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<PacketHeader>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:lsbProto.PacketHeader)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:lsbProto.PacketHeader)
    MergeFrom(*source);
  }
}

void PacketHeader::MergeFrom(const PacketHeader& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:lsbProto.PacketHeader)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.totalsize() != 0) {
    set_totalsize(from.totalsize());
  }
  if (from.packetid() != 0) {
    set_packetid(from.packetid());
  }
}

void PacketHeader::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:lsbProto.PacketHeader)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PacketHeader::CopyFrom(const PacketHeader& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:lsbProto.PacketHeader)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PacketHeader::IsInitialized() const {
  return true;
}

void PacketHeader::InternalSwap(PacketHeader* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(totalsize_, other->totalsize_);
  swap(packetid_, other->packetid_);
}

::PROTOBUF_NAMESPACE_ID::Metadata PacketHeader::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace lsbProto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::lsbProto::PacketHeader* Arena::CreateMaybeMessage< ::lsbProto::PacketHeader >(Arena* arena) {
  return Arena::CreateInternal< ::lsbProto::PacketHeader >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>