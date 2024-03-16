#include "UdpMessage.cpp"

class UdpMessage_Ping : public UdpMessage
{
public:

  Ping() : UdpMessage(UdpMessage::Type::PING) {}

  // Address _m_sender;
};