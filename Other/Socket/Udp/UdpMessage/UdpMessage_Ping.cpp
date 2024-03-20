#ifndef UDP_MESSAGE_PING
#define UDP_MESSAGE_PING

#include "UdpMessage.cpp"
#include "../../../../Common/Address.cpp"

/// not implemented

class UdpMessage_Ping : public UdpMessage
{
  Address _m_sender;
public:

  UdpMessage_Ping() : UdpMessage { UdpMessage::Type::PING } {}
};

#endif