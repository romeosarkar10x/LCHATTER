#ifndef UDP_RECEIVER_CPP
#define UDP_RECEIVER_CPP

#include <memory>

#include "AppSignature.cpp"
#include "Udp_BASE/UdpReceiver_BASE.cpp"

#include "UdpMessage/UdpMessage.cpp"
#include "UdpMessage/UdpMessage_ChatMessage.cpp"
#include "UdpMessage/UdpMessage_ConnectionRequest.cpp"
#include "UdpMessage/UdpMessage_ConnectionRequest_Accepted.cpp"
#include "UdpMessage/UdpMessage_ConnectionRequest_Rejected.cpp"
#include "UdpMessage/UdpMessage_Ping.cpp"

class UdpReceiver final : private UdpReceiver_BASE
{
  
public:
  const Address&  get_socket_address() { return UdpReceiver_BASE::get_socket_address(); }
  const Address&  get_sender_address() { return UdpReceiver_BASE::get_sender_address(); }
  
  using UdpReceiver_BASE::init;
  using UdpReceiver_BASE::destroy;

  UdpMessage* receive()
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

    switch(t._m_t)
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
};

#endif