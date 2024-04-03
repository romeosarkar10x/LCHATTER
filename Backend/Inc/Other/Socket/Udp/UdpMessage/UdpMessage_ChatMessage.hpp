#ifndef UDP_MESSAGE_CHAT_MESSAGE_HPP
#define UDP_MESSAGE_CHAT_MESSAGE_HPP

#include "UdpMessage.hpp" /// <winsock2.h>
#include "../../../../Common/String.hpp"
#include "../../../../Chat/ChatMessage.hpp" /// <windows.h>

class UdpMessage_ChatMessage : public UdpMessage, public ChatMessage
{

public:
  UdpMessage_ChatMessage() = default;

  UdpMessage_ChatMessage(const ChatMessage& m);
  ~UdpMessage_ChatMessage() = default;

  int serialize(char* buffer) const;
  int serialize(char* buffer, int offset) const;

  int deserialize(const char* buffer);
  int deserialize(const char* buffer, int offset);
};

#endif