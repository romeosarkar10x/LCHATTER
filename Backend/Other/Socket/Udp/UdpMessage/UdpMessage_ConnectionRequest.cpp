#ifndef UDP_MESSAGE_CONNECTION_REQUEST_CPP
#define UDP_MESSAGE_CONNECTION_REQUEST_CPP

#include <iostream>

#include "UdpMessage.cpp"
#include "../../../../Common/ConnectionRequest.cpp"

class UdpMessage_ConnectionRequest : public UdpMessage, public ConnectionRequest
{

public:

  UdpMessage_ConnectionRequest() :
  UdpMessage { UdpMessage::Type::CONNECTION_REQUEST } {}

  UdpMessage_ConnectionRequest(const ConnectionRequest& r) :
  UdpMessage { UdpMessage::Type::CONNECTION_REQUEST},
  ConnectionRequest { r } {}

  UdpMessage_ConnectionRequest(const User& user, const Address& addr) :
  UdpMessage { UdpMessage::Type::CONNECTION_REQUEST },
  ConnectionRequest { user, addr } {}

  UdpMessage_ConnectionRequest(UdpMessage::Type t) :
  UdpMessage { t } {}

  UdpMessage_ConnectionRequest(UdpMessage::Type t, const ConnectionRequest& r) :
  UdpMessage { t },
  ConnectionRequest { r } {}
  // UdpMessage_ConnectionRequest(UdpMessage::Type message_type) :
  // UdpMessage { message_type } {}

  // UdpMessage_ConnectionRequest(UdpMessage::Type message_type, const User& user, const Address& addr) :
  // UdpMessage { message_type },
  // _m_user { user },
  // _m_addr { addr } {}
  
  int serialize(char* buffer) const
  {
    int offset = 0;
    
    offset += UdpMessage::serialize(buffer, offset);
    offset += ConnectionRequest::serialize(buffer, offset);

    return offset;
  }

  int serialize(char* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }

  int deserialize(const char* buffer)
  {
    int offset = 0;
    
    offset += UdpMessage::deserialize(buffer, offset);
    offset += ConnectionRequest::deserialize(buffer, offset);

    return offset;
  }

  int deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }
};

// std::ostream& operator<<(std::ostream& o, const UdpMessage_ConnectionRequest& m)
// {
//   o << 
// }

#endif