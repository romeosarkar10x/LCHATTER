#ifndef UDP_MESSAGE_CONNECTION_REQUEST_REJECTED_HPP
#define UDP_MESSAGE_CONNECTION_REQUEST_REJECTED_HPP

#include "UdpMessage_ConnectionRequest.hpp"

class UdpMessage_ConnectionRequest_Rejected : public UdpMessage_ConnectionRequest
{
  
public:
  UdpMessage_ConnectionRequest_Rejected() = default;

  u_int   serialization_length() const;
  void    serialize(char* buffer, u_int& offset) const;

  void deserialize(const char* buffer, u_int& offset) override;

  void handle() override;
};

#endif