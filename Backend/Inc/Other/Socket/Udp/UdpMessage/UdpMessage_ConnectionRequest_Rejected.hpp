#ifndef UDP_MESSAGE_CONNECTION_REQUEST_REJECTED_HPP
#define UDP_MESSAGE_CONNECTION_REQUEST_REJECTED_HPP

#include "UdpMessage_ConnectionRequest.hpp"

class UdpMessage_ConnectionRequest_Rejected : public UdpMessage
{
  
public:
  UdpMessage_ConnectionRequest_Rejected() :
  UdpMessage { UdpMessage::Type::CONNECTION_REQUEST_REJECTED } {}
};

#endif