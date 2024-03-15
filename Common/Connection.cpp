#include "User.cpp"
#include "Addr.cpp"
#include "TimePoint.cpp"
#include "../Chat/Chat.cpp"

class Connection
{
  User      _m_user;
  Chat      _m_chat;
  Addr      _m_address;
  TimePoint _m_timepoint;

public:

  const User& user() { return _m_user; }
  const Chat& chat() { return _m_chat; }
  const Addr& address() { return _m_address; }
  const TimePoint& timepoint() { return _m_timepoint; }
};

