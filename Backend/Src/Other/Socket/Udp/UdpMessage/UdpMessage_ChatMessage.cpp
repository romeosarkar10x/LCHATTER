#include "../../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ChatMessage.hpp"
#include "../../../../../Inc/File/Serializer.hpp"

UdpMessage_ChatMessage::UdpMessage_ChatMessage(const ChatMessage& m) :
  UdpMessage { UdpMessage::Type::CHAT_MESSAGE },
  ChatMessage { m } {}

unsigned int UdpMessage_ChatMessage::serialization_length() const
{
  return Serializer::serialization_length(static_cast<const UdpMessage&>(*this)) +
    Serializer::serialization_length(static_cast<const ChatMessage&>(*this));
}

void UdpMessage_ChatMessage::serialize(char* buffer, unsigned int& offset) const
{
  Serializer::serialize(static_cast<const UdpMessage&>(*this), buffer, offset);
  Serializer::serialize(static_cast<const ChatMessage&>(*this), buffer, offset);
}

int UdpMessage_ChatMessage::deserialize(const char* buffer)
{
  int offset = 0;

  offset += UdpMessage::deserialize(buffer, offset);
  offset += ChatMessage::deserialize(buffer, offset);

  return offset;
}

int UdpMessage_ChatMessage::deserialize(const char* buffer, int offset)
  { return deserialize(buffer + offset); }
