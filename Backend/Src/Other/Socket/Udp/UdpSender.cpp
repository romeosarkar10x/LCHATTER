#include "../../../../Inc/Other/Socket/Udp/UdpSender.hpp"
#include "../../../../Inc/File/Serializer.hpp"

void UdpSender::send(const Address& receiver, const UdpMessage* m)
{
  char* buffer = get_buffer(); int offset = 0;

  // offset += AppSignature::serialize(get_buffer(), offset);
  Serializer::serialize(AppSignature::get_signature(), buffer, offset);
  Serializer::serialize(m->get_type(), buffer, offset);
  // offset += m->get_type().serialize(get_buffer(), offset);
  
  switch(m->get_type())
  {
  case UdpMessage::Type::CONNECTION_REQUEST:
    Serializer::serialize(static_cast<const UdpMessage_ConnectionRequest&>(*m), buffer, offset);
    // offset += static_cast<const UdpMessage_ConnectionRequest*>(m)->serialize(get_buffer(), offset);
    break;

  case UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED:
    Serializer::serialize(static_cast<const UdpMessage_ConnectionRequest_Accepted&>(*m), buffer, offset);
    // offset += static_cast<const UdpMessage_ConnectionRequest_Accepted*>(m)->serialize(get_buffer(), offset);
    break;

  case UdpMessage::Type::CONNECTION_REQUEST_REJECTED:
    Serializer::serialize(static_cast<const UdpMessage_ConnectionRequest_Rejected&>(*m), buffer, offset);
    // offset += static_cast<UdpMessage_ConnectionRequest_Rejected*>(m)->serialize(get_buffer(), offset);
    break;

  case UdpMessage::Type::CHAT_MESSAGE:
    Serializer::serialize(static_cast<const UdpMessage_ChatMessage&>(*m), buffer, offset);
    // offset += static_cast<const UdpMessage_ChatMessage*>(m)->serialize(get_buffer(), offset);
    break;
    
  default:
    assert(false);
    break;
  }
  
  // std::cout << "offset: " << offset << std::endl;
  reset_offset();
  increment_offset(offset);
  UdpSender_BASE::send(receiver);
}