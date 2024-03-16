#include "UdpMessage_Connect.cpp"



class UdpMessage_ConnectReject : public UdpMessage_Connect
{
  
public:
  UdpMessage_ConnectReject(Address&& address) :
  UdpMessage_Connect { UdpMessage::Type::CONNECT_REJECT, std::move(address) } {}
};
