#include "../../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest.hpp"
#include "../../../../../Inc/File/Serializer.hpp"

UdpMessage_ConnectionRequest::UdpMessage_ConnectionRequest() :
UdpMessage { UdpMessage::Type::CONNECTION_REQUEST } {}

UdpMessage_ConnectionRequest::UdpMessage_ConnectionRequest(const ConnectionRequest& r) :
UdpMessage { UdpMessage::Type::CONNECTION_REQUEST},
ConnectionRequest { r } {}

UdpMessage_ConnectionRequest::UdpMessage_ConnectionRequest(const User& user, const Address& addr) :
UdpMessage { UdpMessage::Type::CONNECTION_REQUEST },
ConnectionRequest { user, addr } {}

UdpMessage_ConnectionRequest::UdpMessage_ConnectionRequest(UdpMessage::Type t) :
UdpMessage { t } {}

UdpMessage_ConnectionRequest::UdpMessage_ConnectionRequest(UdpMessage::Type t, const ConnectionRequest& r) :
UdpMessage { t },
ConnectionRequest { r } {}
// UdpMessage_ConnectionRequest(UdpMessage::Type message_type) :
// UdpMessage { message_type } {}

// UdpMessage_ConnectionRequest(UdpMessage::Type message_type, const User& user, const Address& addr) :
// UdpMessage { message_type },
// _m_user { user },
// _m_addr { addr } {}

unsigned int UdpMessage_ConnectionRequest::serialization_length() const
{
  return Serializer::serialization_length(static_cast<const UdpMessage&>(*this)) + 
    Serializer::serialization_length(static_cast<const ConnectionRequest&>(*this));
}

void UdpMessage_ConnectionRequest::serialize(char* buffer, unsigned int& offset) const
{
  Serializer::serialize(static_cast<const UdpMessage&>(*this), buffer, offset);
  Serializer::serialize(static_cast<const ConnectionRequest&>(*this), buffer, offset);
}

int UdpMessage_ConnectionRequest::deserialize(const char* buffer)
{
  int offset = 0;
  
  offset += UdpMessage::deserialize(buffer, offset);
  offset += ConnectionRequest::deserialize(buffer, offset);

  return offset;
}

int UdpMessage_ConnectionRequest::deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }