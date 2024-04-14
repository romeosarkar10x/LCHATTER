#include "../../../../Inc/Other/Socket/Udp/UdpReceiver.hpp"
#include "../../../../Inc/File/Deserializer.hpp"

#include "../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_None.hpp"
#include "../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ChatMessage.hpp"
#include "../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest.hpp"
#include "../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest_Accepted.hpp"
#include "../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest_Rejected.hpp"
#include "../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_Ping.hpp"

const Address&  UdpReceiver::get_socket_address() const { return UdpReceiver_BASE::get_socket_address(); }
const Address&  UdpReceiver::get_sender_address() const { return UdpReceiver_BASE::get_sender_address(); }

UdpMessage* UdpReceiver::receive()
{
  if(UdpReceiver_BASE::receive() == false) { return new UdpMessage_None {}; }
  
  char* buffer = get_buffer(); u_int offset = 0U;

  AppSignature sig {};
  Deserializer::deserialize(sig, buffer, offset);

  if(AppSignature::get_signature() != sig)
  {
    logger << "ERROR: INVALID APP SIGNATURE" << Logger::endl;
  }

  UdpMessage::Type type {};
  Deserializer::deserialize(type, buffer, offset);

  UdpMessage* m = nullptr;

  switch(type)
  {
  case UdpMessage::Type::CONNECTION_REQUEST:
  {
    auto tmp = new UdpMessage_ConnectionRequest {};
    auto type = tmp->get_type();
    std::cout << type << std::endl;
    Deserializer::deserialize(*tmp, buffer, offset);
    m = tmp;
    type = m->get_type();
    std::cout << type << std::endl;
    break;
  }

  case UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED:
  {
    auto* tmp = new UdpMessage_ConnectionRequest_Accepted {};
    Deserializer::deserialize(*tmp, buffer, offset);
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
    // offset += tmp->deserialize(get_buffer(), offset);
    Deserializer::deserialize(*tmp, buffer, offset);
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
