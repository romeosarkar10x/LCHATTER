#include "../../../../Inc/Other/Socket/Udp/UdpSender.hpp"

void UdpSender::send(const Address& receiver, const UdpMessage* m)
{
  int offset = 0;

  offset += AppSignature::serialize(get_buffer(), offset);
  offset += m->get_type().serialize(get_buffer(), offset);
  
  switch(m->get_type())
  {
  case UdpMessage::Type::CONNECTION_REQUEST:
    offset += static_cast<const UdpMessage_ConnectionRequest*>(m)->serialize(get_buffer(), offset);
    break;

  case UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED:
    offset += static_cast<const UdpMessage_ConnectionRequest_Accepted*>(m)->serialize(get_buffer(), offset);
    break;

  case UdpMessage::Type::CONNECTION_REQUEST_REJECTED:
    // offset += static_cast<UdpMessage_ConnectionRequest_Rejected*>(m)->serialize(get_buffer(), offset);
    break;

  case UdpMessage::Type::CHAT_MESSAGE:
    offset += static_cast<const UdpMessage_ChatMessage*>(m)->serialize(get_buffer(), offset);
    break;
    
  default:
    break;
  }
  
  reset_offset();
  increment_offset(offset);
  UdpSender_BASE::send(receiver);
}