#include <iostream>
#include <cstring>
// #include "../../../../Common/User.cpp"
#include "UdpMessage.cpp"

class UdpChatMessage : public UdpMessage
{
  std::string _m_msg;

public:
  UdpChatMessage(const char* msg) : UdpMessage { UdpMessage::Type::CHAT_MSG }, _m_msg { msg } {}
  UdpChatMessage(const std::string& msg) : UdpMessage { UdpMessage::Type::CHAT_MSG }, _m_msg { msg } {}
  UdpChatMessage(std::string&& msg) : UdpMessage { UdpMessage::Type::CHAT_MSG }, _m_msg { std::move(msg) } {}
  ~UdpChatMessage() = default;
  
  const std::string& msg() const { return _m_msg; }
  int length() const { return static_cast<int>(_m_msg.length()); }
  const void* buffer() const { return _m_msg.c_str(); }
};


class ChatMessage_View : public UdpMessage
{
  const void* _m_msg;
  int _m_length;

public:
  ChatMessage_View(const char* msg, int length) : UdpMessage { UdpMessage::Type::CHAT_MSG }, _m_msg { msg }, _m_length { length } {}
  ChatMessage_View(const char* msg) : UdpMessage { UdpMessage::Type::CHAT_MSG }, _m_msg { msg }, _m_length { static_cast<int>(std::strlen(msg)) } {}

  ~ChatMessage_View() = default;
  
  const char* msg() const { return reinterpret_cast<const char*>(_m_msg); }
  int length() const { return _m_length; }
  const void* buffer() const { return _m_msg; }
};