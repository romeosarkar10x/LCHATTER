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
  // ~UdpMessage_ChatMessage() override = default;

  u_int serialization_length() const override;
  void serialize(char* buffer, u_int& offset) const override;

  UdpMessage::Type get_type() const override;
  
  void deserialize(const char* buffer, u_int& offset) override;

  void handle() override;
};

#endif