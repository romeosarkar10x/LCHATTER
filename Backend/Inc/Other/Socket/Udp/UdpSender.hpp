#ifndef UDP_SENDER_HPP
#define UDP_SENDER_HPP

#include "AppSignature.hpp"
#include "Udp_BASE/UdpSender_BASE.hpp"

#include "UdpMessage/UdpMessage.hpp"
#include "UdpMessage/UdpMessage_ChatMessage.hpp"
#include "UdpMessage/UdpMessage_ConnectionRequest.hpp"
#include "UdpMessage/UdpMessage_ConnectionRequest_Accepted.hpp"
#include "UdpMessage/UdpMessage_ConnectionRequest_Rejected.hpp"
#include "UdpMessage/UdpMessage_Ping.hpp"

class UdpSender final : private UdpSender_BASE
{

public:
  using UdpSender_BASE::init;
  using UdpSender_BASE::destroy;

  void send(const Address& receiver, const UdpMessage* m);
};

#endif