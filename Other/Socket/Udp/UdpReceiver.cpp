#ifndef UDP_RECEIVER_CPP
#define UDP_RECEIVER_CPP

#include <memory>

#include "AppSignature.cpp"
#include "Udp_Base/UdpReceiver_Base.cpp"

#include "UdpMessage/UdpMessage.cpp"
#include "UdpMessage/UdpMessage_ChatMessage.cpp"
#include "UdpMessage/UdpMessage_ConnectionRequest.cpp"
#include "UdpMessage/UdpMessage_ConnectionRequest_Accepted.cpp"
#include "UdpMessage/UdpMessage_ConnectionRequest_Rejected.cpp"
#include "UdpMessage/UdpMessage_Ping.cpp"

class UdpReceiver final : private UdpReceiver_Base
{
  
public:
  using UdpReceiver_Base::get_port;
  
  const Address get_address() { return UdpReceiver_Base::get_address(); }
  

  void init()
  {
    UdpReceiver_Base::init();
  }

  UdpMessage* receive()
  {
    if(UdpReceiver_Base::receive() == false) { return new UdpMessage {}; }
    
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

    assert(offset == get_offset());
    return m;
  }
};

#endif