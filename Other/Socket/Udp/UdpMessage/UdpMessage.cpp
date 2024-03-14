#ifndef UDP_MSG_HPP
#define UDP_MSG_HPP

#include "../../../../Common/Addr.cpp"

/*

** Message Format: [MessageType] [Payload]
  
** MessageType: Ping :: [][Payload] is empty
** MessageType: ChatMessage :: [Payload] contains the chat
** MessageType: Connect :: [Payload] contains [user_name] [0] []
** 
*/

class UdpMessage
{
public:
  enum class Type : char { INV = -1, NONE = 0, PING, CHAT_MSG, CONN, CONN_ACCEPT, CONN_REJECT };
  
  UdpMessage() = default;
  UdpMessage(Type msg_type) : _m_type { msg_type } {}

  Type type() const { return _m_type; }

private:
  Type _m_type { Type::NONE };
};



#endif