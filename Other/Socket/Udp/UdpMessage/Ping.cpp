#include "UdpMessage.cpp"

class Ping : public UdpMessage
{
public:

  Ping() : UdpMessage(UdpMessage::Type::PING) {}

  // Addr _m_sender;
};