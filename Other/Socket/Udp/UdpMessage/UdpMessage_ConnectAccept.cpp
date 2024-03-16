#include "UdpMessage_Connect.cpp"

class UdpMessage_ConnectAccept : public UdpMessage_Connect
{

public:
  UdpMessage_ConnectAccept(Address&& address) :
  UdpMessage_Connect { UdpMessage::Type::CONNECT_ACCEPT, std::move(address) } {}
};
