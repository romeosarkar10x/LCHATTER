#ifndef UDP_MESSAGE_CONNECTION_REQUEST_HPP
#define UDP_MESSAGE_CONNECTION_REQUEST_HPP

#include <iostream>

#include "UdpMessage.hpp"
#include "../../../../Common/ConnectionRequest.hpp"

class UdpMessage_ConnectionRequest : public UdpMessage, public ConnectionRequest
{

public:
  UdpMessage_ConnectionRequest() = default;

  UdpMessage_ConnectionRequest(const ConnectionRequest& r);
  UdpMessage_ConnectionRequest(const User& user, const Address& addr);
  
  UdpMessage::Type get_type() const override { return UdpMessage::Type::CONNECTION_REQUEST; }

  u_int   serialization_length() const override;
  void    serialize(char* buffer, u_int& offset) const override;

  void deserialize(const char* buffer, u_int& offset) override;
  
  void handle() override;
};

#endif