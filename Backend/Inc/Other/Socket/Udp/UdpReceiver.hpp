#ifndef UDP_RECEIVER_HPP
#define UDP_RECEIVER_HPP

#include "AppSignature.hpp"
#include "Udp_BASE/UdpReceiver_BASE.hpp"

#include "UdpMessage/UdpMessage.hpp"
#include "UdpMessage/UdpMessage_ChatMessage.hpp"
#include "UdpMessage/UdpMessage_ConnectionRequest.hpp"
#include "UdpMessage/UdpMessage_ConnectionRequest_Accepted.hpp"
#include "UdpMessage/UdpMessage_ConnectionRequest_Rejected.hpp"
#include "UdpMessage/UdpMessage_Ping.hpp"

class UdpReceiver final : private UdpReceiver_BASE
{
  
public:
  const Address&  get_socket_address();
  const Address&  get_sender_address();
  
  using UdpReceiver_BASE::init;
  using UdpReceiver_BASE::destroy;

  UdpMessage* receive();
};

#endif