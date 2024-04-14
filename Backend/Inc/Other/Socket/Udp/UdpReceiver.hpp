#ifndef UDP_RECEIVER_HPP
#define UDP_RECEIVER_HPP

#include "AppSignature.hpp"
#include "Udp_BASE/UdpReceiver_BASE.hpp"

#include "UdpMessage/UdpMessage.hpp"

class UdpReceiver final : private UdpReceiver_BASE
{
  
public:
  const Address&  get_socket_address() const;
  const Address&  get_sender_address() const;
  
  using UdpReceiver_BASE::init;
  using UdpReceiver_BASE::destroy;

  UdpMessage* receive();
};

#endif