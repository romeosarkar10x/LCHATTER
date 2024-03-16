#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>

enum class Event : unsigned char
{
  NONE,
  LOGIN,
  LOGIN_ANONYMOUS,
  LOGOUT,
  CHAT_MESSAGE,
  CONNECT,
  CONNECT_ACCEPT,
  CONNECT_REJECT
};

std::ostream& operator<<(std::ostream& o, Event e)
{
  switch(e)
  {
  case Event::NONE:
    o << "NONE";
    break;
  case Event::LOGIN:
    o << "LOGIN";
    break;
  case Event::LOGIN_ANONYMOUS:
    o << "LOGIN_ANONYMOUS";
    break;
  case Event::LOGOUT:
    o << "LOGOUT";
    break;
  case Event::CHAT_MESSAGE:
    o << "MESSAGE";
    break;
  case Event::CONNECT:
    o << "CONNECT";
    break;
  case Event::CONNECT_ACCEPT:
    o << "CONNECT_ACCEPT";
    break;
  case Event::CONNECT_REJECT:
    o << "CONNECT_REJECT";
    break;
  default:
    o << "EVENT_NOT_LISTED";
  }

  return o;
}


#endif