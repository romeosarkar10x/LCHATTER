#include "UdpMessage.cpp"
#include "../../../../Common/User.cpp"

class UdpMessage_Connect : public UdpMessage
{
  User    _m_user {};
  Address _m_address;
  
public:

  UdpMessage_Connect(Address&& address) :
  UdpMessage { UdpMessage::Type::CONNECT },
  _m_address { std::move(address) } {}

  UdpMessage_Connect(UdpMessage::Type message_type, Address&& address) :
  UdpMessage { message_type },
  _m_address { std::move(address) } {}
  
  int deserialize(const void* buffer)
  {
    return _m_user.deserialize(buffer);
  }
};

