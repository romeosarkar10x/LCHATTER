#ifndef FRONTEND_EVENT_CPP
#define FRONTEND_EVENT_CPP

#include <iostream>
#include "../Backend.cpp"

static std::ostream& operator<<(std::ostream& o, AppBackend::Frontend_Event::Enum_Frontend_Event e)
{
  switch(e)
  {
  case AppBackend::Frontend_Event::NONE:
    o << "AppBackend::Frontend_Event::NONE";
    break;

  case AppBackend::Frontend_Event::LOGIN:
    o << "AppBackend::Frontend_Event::LOGIN";
    break;

  case AppBackend::Frontend_Event::LOGIN_ANONYMOUS:
    o << "AppBackend::Frontend_Event::LOGIN_ANONYMOUS";
    break;

  case AppBackend::Frontend_Event::LOGOUT:
    o << "AppBackend::Frontend_Event::LOGOUT";
    break;

  case AppBackend::Frontend_Event::SEND_CHAT_MESSAGE:
    o << "AppBackend::Frontend_Event::SEND_CHAT_MESSAGE";
    break;

  case AppBackend::Frontend_Event::SEND_CONNECTION_REQUEST:
    o << "AppBackend::Frontend_Event::SEND_CONNECTION_REQUEST";
    break;

  case AppBackend::Frontend_Event::ACCEPT_CONNECTION_REQUEST:
    o << "AppBackend::Frontend_Event::ACCEPT_CONNECTION_REQUEST";
    break;

  case AppBackend::Frontend_Event::REJECT_CONNECTION_REQUEST:
    o << "AppBackend::Frontend_Event::REJECT_CONNECTION_REQUEST";
    break;
  
  default:
    o << "AppBackend::Frontend_Event@@ERROR##ENUMERATION_NOT_HANDLED";
    break;
  }

  return o;
}

#endif