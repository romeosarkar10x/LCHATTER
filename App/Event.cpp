#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>

enum class Event : unsigned char
{
  NONE,
  LOGIN,
  LOGIN_ANONYMOUS,
  LOGOUT,
  SEND_CHAT_MESSAGE,
  SEND_CONNECTION_REQUEST,
  ACCEPT_CONNECTION_REQUEST,
  REJECT_CONNECTION_REQUEST
};

std::ostream& operator<<(std::ostream& o, Event e)
{
  switch(e)
  {
  case Event::NONE:
    o << "Event::NONE";
    break;
  case Event::LOGIN:
    o << "Event::LOGIN";
    break;
  case Event::LOGIN_ANONYMOUS:
    o << "Event::LOGIN_ANONYMOUS";
    break;
  case Event::LOGOUT:
    o << "Event::LOGOUT";
    break;
  case Event::SEND_CHAT_MESSAGE:
    o << "Event::SEND_CHAT_MESSAGE";
    break;
  case Event::SEND_CONNECTION_REQUEST:
    o << "Event::SEND_CONNECTION_REQUEST";
    break;
  case Event::ACCEPT_CONNECTION_REQUEST:
    o << "Event::ACCEPT_CONNECTION_REQUEST";
    break;
  case Event::REJECT_CONNECTION_REQUEST:
    o << "Event::REJECT_CONNECTION_REQUEST";
    break;
  default:
    o << "Event::ERROR::EVENT_NOT_LISTED";
  }

  return o;
}


#endif