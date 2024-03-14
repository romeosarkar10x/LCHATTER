#include "UdpMessage.cpp"


class Conn : public UdpMessage
{
public:
  Conn() : UdpMessage { UdpMessage::Type::CONN } {}
};

