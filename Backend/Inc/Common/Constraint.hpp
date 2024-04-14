#ifndef CONSTRAINTS_HPP
#define CONSTRAINTS_HPP

#include "../Other/Socket/Address.hpp"  // contains <winsock2.h>
#include "../File/Serializer.hpp"       // contains <windows.h>
#include "../File/Deserializer.hpp"     // contains <windows.h>

#include "User.hpp"
#include "String.hpp"
#include "TimePoint.hpp"
#include "Connection.hpp"
#include "ConnectionRequest.hpp"

#include "../Chat/Chat.hpp"
#include "../File/Trait.hpp"
#include "../Chat/ChatMessage.hpp"
#include "../Crypto/Hash/MD5_Digest.hpp"

#include "../Other/Socket/Udp/AppSignature.hpp"
#include "../Other/Socket/Udp/UdpMessage/UdpMessage.hpp"
#include "../Other/Socket/Udp/UdpMessage/UdpMessage_ChatMessage.hpp"
#include "../Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest.hpp"
#include "../Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest_Accepted.hpp"
#include "../Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest_Rejected.hpp"

static_assert(Serializer::is_serializable_v<User>);
static_assert(Serializer::is_serializable_v<String>);
static_assert(Serializer::is_serializable_v<Address>);
static_assert(Serializer::is_serializable_v<TimePoint>);
static_assert(Serializer::is_serializable_v<MD5_Digest>);

static_assert(Serializer::is_serializable_v<Chat>);
static_assert(Serializer::is_serializable_v<ChatMessage>);

static_assert(Serializer::is_serializable_v<Connection>);
static_assert(Serializer::is_serializable_v<ConnectionRequest>);

static_assert(Serializer::is_serializable_v<UdpMessage>);
static_assert(Serializer::is_serializable_v<AppSignature>);
static_assert(Serializer::is_serializable_v<UdpMessage_ChatMessage>);
static_assert(Serializer::is_serializable_v<UdpMessage_ConnectionRequest>);
static_assert(Serializer::is_serializable_v<UdpMessage_ConnectionRequest_Accepted>);
static_assert(Serializer::is_serializable_v<UdpMessage_ConnectionRequest_Rejected>);


static_assert(Deserializer::is_deserializable_v<User>);
static_assert(Deserializer::is_deserializable_v<String>);
static_assert(Deserializer::is_deserializable_v<Address>);
static_assert(Deserializer::is_deserializable_v<TimePoint>);
static_assert(Deserializer::is_deserializable_v<MD5_Digest>);

static_assert(Deserializer::is_deserializable_v<Chat>);
static_assert(Deserializer::is_deserializable_v<ChatMessage>);

static_assert(Deserializer::is_deserializable_v<Connection>);
static_assert(Deserializer::is_deserializable_v<ConnectionRequest>);

static_assert(Deserializer::is_deserializable_v<UdpMessage>);
static_assert(Deserializer::is_deserializable_v<AppSignature>);
static_assert(Deserializer::is_deserializable_v<UdpMessage_ChatMessage>);
static_assert(Deserializer::is_deserializable_v<UdpMessage_ConnectionRequest>);
static_assert(Deserializer::is_deserializable_v<UdpMessage_ConnectionRequest_Accepted>);
static_assert(Deserializer::is_deserializable_v<UdpMessage_ConnectionRequest_Rejected>);

#endif