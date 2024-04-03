#include "../../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest_Accepted.hpp"


UdpMessage_ConnectionRequest_Accepted::UdpMessage_ConnectionRequest_Accepted(const UdpMessage_ConnectionRequest& r) :
  UdpMessage_ConnectionRequest { UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED, r } {}

UdpMessage_ConnectionRequest_Accepted::UdpMessage_ConnectionRequest_Accepted() :
UdpMessage_ConnectionRequest { UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED } {}

  // UdpMessage_ConnectAccept(const User& user, const Address& addr) :
  // UdpMessage_Connect { UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED , user, addr } {}