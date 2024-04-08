#ifndef UDP_MESSAGE_CONNECTION_REQUEST_HPP
#define UDP_MESSAGE_CONNECTION_REQUEST_HPP

#include <iostream>

#include "UdpMessage.hpp"
#include "../../../../Common/ConnectionRequest.hpp"

class UdpMessage_ConnectionRequest : public UdpMessage, public ConnectionRequest
{

public:

  UdpMessage_ConnectionRequest();
  UdpMessage_ConnectionRequest(const ConnectionRequest& r);
  UdpMessage_ConnectionRequest(const User& user, const Address& addr);
  UdpMessage_ConnectionRequest(UdpMessage::Type t);
  UdpMessage_ConnectionRequest(UdpMessage::Type t, const ConnectionRequest& r);
  
  int serialization_length() const;
  void serialize(char* buffer, int& offset) const;

  int deserialize(const char* buffer);
  int deserialize(const char* buffer, int offset);
};

#endif