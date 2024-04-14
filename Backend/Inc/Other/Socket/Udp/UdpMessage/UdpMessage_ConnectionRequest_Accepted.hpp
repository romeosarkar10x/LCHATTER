#ifndef UDP_MESSAGE_CONNECTION_REQUEST_ACCEPTED_HPP
#define UDP_MESSAGE_CONNECTION_REQUEST_ACCEPTED_HPP

#include "UdpMessage_ConnectionRequest.hpp"

class UdpMessage_ConnectionRequest_Accepted : public UdpMessage_ConnectionRequest
{

public:
  UdpMessage_ConnectionRequest_Accepted() = default;

  UdpMessage_ConnectionRequest_Accepted(const UdpMessage_ConnectionRequest& r);
  
  UdpMessage::Type get_type() const override { return UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED; }

  u_int   serialization_length() const;
  void    serialize(char* buffer, u_int& offset) const;

  void deserialize(const char* buffer, u_int& offset) override;

  void handle() override;
};

#endif