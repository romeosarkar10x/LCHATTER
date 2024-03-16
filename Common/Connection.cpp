#include "User.cpp"
#include "Address.cpp"
#include "TimePoint.cpp"
#include "../Chat/Chat.cpp"

class Connection
{
  User      _m_user;
  Chat      _m_chat;
  Address   _m_address;
  TimePoint _m_timepoint;

public:

  const User& user() { return _m_user; }
  const Chat& chat() { return _m_chat; }
  const Address& address() { return _m_address; }
  const TimePoint& timepoint() { return _m_timepoint; }
};

