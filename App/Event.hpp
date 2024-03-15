#ifndef EVENT_HPP
#define EVENT_HPP

enum class Event : unsigned char
{
  NONE,
  LOGIN,
  LOGIN_ANONYMOUS,
  LOGOUT, MESSAGE,
  CONNECT,
  CONNECT_ACCEPT,
  CONNECT_REJECT
};

#endif