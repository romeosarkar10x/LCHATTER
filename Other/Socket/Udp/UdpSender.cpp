#ifndef UDP_SENDER_CPP
#define UDP_SENDER_CPP

#include "AppSignature.cpp"
#include "Udp_Base/UdpSender_Base.cpp"

#include "UdpMessage/UdpMessage.cpp"
#include "UdpMessage/UdpMessage_ChatMessage.cpp"
#include "UdpMessage/UdpMessage_ConnectionRequest.cpp"
#include "UdpMessage/UdpMessage_ConnectionRequest_Accepted.cpp"
#include "UdpMessage/UdpMessage_ConnectionRequest_Rejected.cpp"
#include "UdpMessage/UdpMessage_Ping.cpp"

class UdpSender final : private UdpSender_Base
{

public:
  void init()
  {
    UdpSender_Base::init();
  }
  
  void send(const Address& receiver, const UdpMessage* m)
  {
    int offset = 0;

    offset += AppSignature::serialize(get_buffer(), offset);
    offset += m->get_type().serialize(get_buffer(), offset);
    
    switch(m->get_type()._m_t)
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

    // std::cout << "receiver: " << receiver << std::endl;
    // logger << receiver << "\n";

    UdpSender_Base::send(receiver);
  }
};

#endif