#include "../../Common/Address.cpp"

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


enum class IncomingMessageType : unsigned char { None, Ping, Connect, ChatMessage };

class IncomingMessage
{
  enum class Type : char { INV = -1, NONE, PING, MSG, CONN, CONN_ACK } _m_message_type;
  Address _m_sender;

public:
  // IncomingMessageType ;
};