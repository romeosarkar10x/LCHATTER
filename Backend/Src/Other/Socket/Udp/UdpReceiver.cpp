#include "../../../../Inc/Other/Socket/Udp/UdpReceiver.hpp"

const Address&  UdpReceiver::get_socket_address() { return UdpReceiver_BASE::get_socket_address(); }
const Address&  UdpReceiver::get_sender_address() { return UdpReceiver_BASE::get_sender_address(); }

UdpMessage* UdpReceiver::receive()
{
  if(UdpReceiver_BASE::receive() == false) { return new UdpMessage {}; }
  
  int offset = 0;

  if(!AppSignature::is_valid(get_buffer()))
  {
    logger << "ERROR: Invalid AppSignature\n";
    return new UdpMessage { UdpMessage::Type::INVALID };
  }
  
  offset += AppSignature::deserialize(get_buffer(), offset);

  UdpMessage::Type t;
  offset += t.deserialize(get_buffer(), offset);

  UdpMessage* m = nullptr;

  switch(t)
  {
  case UdpMessage::Type::CONNECTION_REQUEST:
  {
    auto* tmp = new UdpMessage_ConnectionRequest {};
    offset += tmp->deserialize(get_buffer(), offset);
    m = tmp;
    break;
  }

  case UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED:
  {
    auto* tmp = new UdpMessage_ConnectionRequest_Accepted {};
    offset += tmp->deserialize(get_buffer(), offset);
    m = tmp;
    break;
  }

  case UdpMessage::Type::CONNECTION_REQUEST_REJECTED:
  {

  }
    // return new UdpMessage_ConnectionRequest_Rejected {};

  case UdpMessage::Type::CHAT_MESSAGE:
  {
    auto* tmp = new UdpMessage_ChatMessage {};
    offset += tmp->deserialize(get_buffer(), offset);
    m = tmp;
    break;
  }

  default:
    assert(false);
  }
  
  // std::cout << offset << " " << get_offset() << std::endl;
  assert(offset == get_offset());
  return m;
}
