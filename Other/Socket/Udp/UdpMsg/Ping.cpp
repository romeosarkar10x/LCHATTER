#include "UdpMsg.cpp"

class Ping : public UdpMsg
{
public:

  Ping() : UdpMsg(UdpMsg::Type::PING) {}

  Addr _m_sender;
};