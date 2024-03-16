#ifndef UDP_MSG_HPP
#define UDP_MSG_HPP

#include "../../../../Common/Address.cpp"



class UdpMessage
{
public:

  enum class Type : char {
    INV = -1,
    NONE = 0,
    PING,
    CHAT_MESSAGE,
    CONNECT,
    CONNECT_ACCEPT,
    CONNECT_REJECT
  };
  
  UdpMessage() = default;

  UdpMessage(Type message_type) : _m_type { message_type } {}

  Type get_type() const { return _m_type; }

private:
  Type _m_type { Type::NONE };
};



#endif