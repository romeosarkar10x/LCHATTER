#ifndef UDP_MESSAGE_CHAT_MESSAGE_CPP
#define UDP_MESSAGE_CHAT_MESSAGE_CPP

#include <iostream>
#include <cstring>

#include "UdpMessage.cpp" /// <winsock2.h>
#include "../../../../Common/String.cpp"
#include "../../../../Chat/ChatMessage.cpp" /// <windows.h>

class UdpMessage_ChatMessage : public UdpMessage, public ChatMessage
{

public:
  UdpMessage_ChatMessage() = default;

  UdpMessage_ChatMessage(const ChatMessage& m) :
  UdpMessage { UdpMessage::Type::CHAT_MESSAGE },
  ChatMessage { m } {}

  ~UdpMessage_ChatMessage() = default;

  int serialize(char* buffer) const
  {
    int offset = 0;

    offset += UdpMessage::serialize(buffer, offset);
    offset += ChatMessage::serialize(buffer, offset);

    return offset;
  }

  int serialize(char* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }

  int deserialize(const char* buffer)
  {
    int offset = 0;

    offset += UdpMessage::deserialize(buffer, offset);
    offset += ChatMessage::deserialize(buffer, offset);

    return offset;
  }

  int deserialize(const char* buffer, int offset) { return deserialize(buffer + offset); }
};

#endif