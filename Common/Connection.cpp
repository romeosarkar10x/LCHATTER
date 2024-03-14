#include "User.cpp"
#include "Addr.cpp"
#include "TimePoint.cpp"


class Connection
{
  User _m_user;
  Addr _m_address;
  TimePoint _m_last_ping;
  
  const User& user() { return _m_user; }
  const Addr& address() { return _m_address; }

};
