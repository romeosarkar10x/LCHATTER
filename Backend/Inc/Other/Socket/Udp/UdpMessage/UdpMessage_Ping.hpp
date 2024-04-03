#ifndef UDP_MESSAGE_PING_HPP
#define UDP_MESSAGE_PING_HPP

#include "UdpMessage.hpp"

/// not implemented

class UdpMessage_Ping : public UdpMessage
{
  Address _m_sender;
public:

  UdpMessage_Ping();
};

#endif