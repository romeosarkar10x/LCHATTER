#include "../../../../Common/Addr.cpp"

/*

** Message Format: [MessageType] [Payload]
  
** MessageType: Ping :: [Payload] is empty
** MessageType: ChatMessage :: [Payload] contains the chat
** MessageType: Connect :: [Payload] contains [UserName] [0] [UUID]
*/

// types of incoming messages:
// ping
// text message
// invitaion__add_friend
// 


class UdpMsg
{
public:
  enum class Type : char { INV = -1, NONE, PING, CHAT_MSG, CONN, CONN_ACK };
  UdpMsg() = default;
  constexpr UdpMsg(Type msg_type) : _m_msg_type { msg_type } {}

private:
  Type _m_msg_type { Type::NONE };
};
