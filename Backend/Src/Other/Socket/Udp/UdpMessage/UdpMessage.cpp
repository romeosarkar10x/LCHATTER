#include "../../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage.hpp"
#include "../../../../../Inc/File/Serializer.hpp"

std::ostream& operator<<(std::ostream& o, const UdpMessage::Type t)
{
  switch(t)
  {

  case UdpMessage::Type::NONE:
    o << "UdpMessage::Type::NONE";
    break;

  case UdpMessage::Type::PING:
    o << "UdpMessage::Type::PING";
    break;

  case UdpMessage::Type::CHAT_MESSAGE:
    o << "UdpMessage::Type::CHAT_MESSAGE";
    break;

  case UdpMessage::Type::CONNECTION_REQUEST:
    o << "UdpMessage::Type::CONNECTION_REQUEST";
    break;

  case UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED:
    o << "UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED";
    break;

  case UdpMessage::Type::CONNECTION_REQUEST_REJECTED:
    o << "UdpMessage::Type::CONNECTION_REQUEST_REJECTED";
    break;
  
  case UdpMessage::Type::GROUP_CHAT_MESSAGE:
    o << "UdpMessage::Type::GROUP_CHAT_MESSAGE";
    break;
  
  case UdpMessage::Type::GROUP_CONNECTION_REQUEST:
    o << "UdpMessage::Type::GROUP_CONNECTION_REQUEST";
    break;
  
  case UdpMessage::Type::ACCEPT_GROUP_CONNECTION_REQUEST:
    o << "UdpMessage::Type::ACCEPT_GROUP_CONNECTION_REQUEST";
    break;

  case UdpMessage::Type::REJECT_GROUP_CONNECTION_REQUEST:
    o << "UdpMessage::Type::REJECT_GROUP_CONNECTION_REQUEST";
    break;
  
  default:
    o << "DEFAULT";
    break;
  }

  return o;
}

