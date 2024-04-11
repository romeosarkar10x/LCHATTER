#ifndef CONSTRAINTS_HPP
#define CONSTRAINTS_HPP

#include "../Other/Socket/Address.hpp"
#include "../File/Serializer.hpp"

#include "User.hpp"
#include "String.hpp"
#include "TimePoint.hpp"
#include "ConnectionRequest.hpp"
#include "../Crypto/Hash/MD5_Digest.hpp"
#include "../Chat/ChatMessage.hpp"
#include "../File/Trait.hpp"

#include "../Other/Socket/Udp/AppSignature.hpp"
#include "../Other/Socket/Udp/UdpMessage/UdpMessage.hpp"
#include "../Other/Socket/Udp/UdpMessage/UdpMessage_ChatMessage.hpp"
#include "../Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest.hpp"

static_assert(Serializer::is_serializable_v<User>);
static_assert(Serializer::is_serializable_v<String>);
static_assert(Serializer::is_serializable_v<Address>);
static_assert(Serializer::is_serializable_v<TimePoint>);
static_assert(Serializer::is_serializable_v<MD5_Digest>);
static_assert(Serializer::is_serializable_v<ChatMessage>);
static_assert(Serializer::is_serializable_v<ConnectionRequest>);

static_assert(Serializer::is_serializable_v<UdpMessage>);
static_assert(Serializer::is_serializable_v<AppSignature>);
static_assert(Serializer::is_serializable_v<UdpMessage_ChatMessage>);
static_assert(Serializer::is_serializable_v<UdpMessage_ConnectionRequest>);

#endif