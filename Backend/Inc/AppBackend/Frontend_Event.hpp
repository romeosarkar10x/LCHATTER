#ifndef FRONTEND_EVENT_HPP
#define FRONTEND_EVENT_HPP

#include <iostream>
#include "AppBackend.hpp"

// class AppBackend;

class AppBackend::Frontend_Event
  {

  public:
    enum Enum_Frontend_Event : char
    {
      NONE,

      LOGIN,
      LOGIN_ANONYMOUS,
      LOGOUT,
      
      SEND_CHAT_MESSAGE,

        SEND_CONNECTION_REQUEST,
      ACCEPT_CONNECTION_REQUEST,
      REJECT_CONNECTION_REQUEST,

      // GROUP
      SEND_GROUP_CHAT_MESSAGE,
        
        SEND_GROUP_CONNECTION_REQUEST,
      ACCEPT_GROUP_CONNECTION_REQUEST,
      REJECT_GROUP_CONNECTION_REQUEST,
    };

    static void                 set_event(Enum_Frontend_Event event);
    static Enum_Frontend_Event  get_event();

    static void handle_event();

  private:
    static Enum_Frontend_Event _s_event;
    friend std::ostream& operator<<(std::ostream& o, const AppBackend::Frontend_Event::Enum_Frontend_Event e);
  };


#endif