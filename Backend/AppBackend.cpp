#ifndef APP_BACKEND_CPP
#define APP_BACKEND_CPP

#include <set>

#include "../Common/Addr.cpp"
#include "../Other/Socket/Udp/UdpSender.cpp"
#include "../Other/Socket/Udp/UdpReceiver.cpp"
#include "../App/Event.hpp"
#include "../Common/User.cpp"
#include "../Common/Connection.cpp"
#include "../Log/Logger.cpp"

class AppBackend
{
public:
  enum class State : unsigned char { NOT_LOGGED_IN, LOGGED_IN };

private:

  static const int _S_username_psw_buffer_length = 100;
  static char* _s_buffer_username;
  static char* _s_buffer_psw;

  static const int _S_message_buffer_length = 40000;
  static char* _s_buffer_message;

  static void _s_init_buffers()
  {
    _s_buffer_username = new char[_S_username_psw_buffer_length];
    _s_buffer_psw = new char[_S_username_psw_buffer_length];

    _s_buffer_message = new char[_S_message_buffer_length];
  }

  static Event _s_event;
  static State _s_state;

  static User _s_me;
  static UdpSender _s_sender;
  static UdpReceiver _s_receiver;

  static std::set<Connection> _s_connections;

  void _s_handle_event()
  {

  }


public:
  

  static const User& me() { return _s_me; }
  static const std::set<Connection>& connections() { return _s_connections; }

  static char* buffer_username() { return _s_buffer_username; }
  static char* buffer_psw() { return _s_buffer_psw; }

  static char* buffer_message() { return _s_buffer_message; }

  static const int buffer_username_length = _S_username_psw_buffer_length;
  static const int buffer_psw_length = _S_username_psw_buffer_length;
  
  static const int buffer_message_length = _S_message_buffer_length;


  static void init()
  {
    _s_init_buffers();
  }

  

  static void update()
  {
    
  }

  static void set_event(Event event) { _s_event = event; }
  
  static State state() { return _s_state; }
  
  AppBackend() = delete;
  ~AppBackend() = delete;

};

User AppBackend::_s_me {};
UdpSender AppBackend::_s_sender {};
UdpReceiver AppBackend::_s_receiver {};
AppBackend::State AppBackend::_s_state { AppBackend::State::NOT_LOGGED_IN };

std::set<Connection> AppBackend::_s_connections {};

#endif