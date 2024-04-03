#include "../../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ChatMessage.hpp"

UdpMessage_ChatMessage::UdpMessage_ChatMessage(const ChatMessage& m) :
  UdpMessage { UdpMessage::Type::CHAT_MESSAGE },
  ChatMessage { m } {}

int UdpMessage_ChatMessage::serialize(char* buffer) const
{
  int offset = 0;

  offset += UdpMessage::serialize(buffer, offset);
  offset += ChatMessage::serialize(buffer, offset);

  return offset;
}

int UdpMessage_ChatMessage::serialize(char* buffer, int offset) const
  { return serialize(reinterpret_cast<char*>(buffer) + offset); }

int UdpMessage_ChatMessage::deserialize(const char* buffer)
{
  int offset = 0;

  offset += UdpMessage::deserialize(buffer, offset);
  offset += ChatMessage::deserialize(buffer, offset);

  return offset;
}

int UdpMessage_ChatMessage::deserialize(const char* buffer, int offset)
  { return deserialize(buffer + offset); }
