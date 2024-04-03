#ifndef UDP_MESSAGE_CONNECTION_REQUEST_ACCEPTED_HPP
#define UDP_MESSAGE_CONNECTION_REQUEST_ACCEPTED_HPP

#include "UdpMessage_ConnectionRequest.hpp"

class UdpMessage_ConnectionRequest_Accepted : public UdpMessage_ConnectionRequest
{

public:
  UdpMessage_ConnectionRequest_Accepted(const UdpMessage_ConnectionRequest& r);
  
  UdpMessage_ConnectionRequest_Accepted();

  // UdpMessage_ConnectAccept(const User& user, const Address& addr) :
  // UdpMessage_Connect { UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED , user, addr } {}
};

#endif