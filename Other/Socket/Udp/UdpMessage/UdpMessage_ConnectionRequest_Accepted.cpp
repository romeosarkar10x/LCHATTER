#ifndef UDP_MESSAGE_CONNECT_ACCEPT_CPP
#define UDP_MESSAGE_CONNECT_ACCEPT_CPP

#include "UdpMessage_ConnectionRequest.cpp"

class UdpMessage_ConnectionRequest_Accepted : public UdpMessage_ConnectionRequest
{

public:
  UdpMessage_ConnectionRequest_Accepted(const UdpMessage_ConnectionRequest& r) :
    UdpMessage_ConnectionRequest { UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED, r } {}
  
  UdpMessage_ConnectionRequest_Accepted() :
  UdpMessage_ConnectionRequest { UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED } {}

  // UdpMessage_ConnectAccept(const User& user, const Address& addr) :
  // UdpMessage_Connect { UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED , user, addr } {}
};

#endif