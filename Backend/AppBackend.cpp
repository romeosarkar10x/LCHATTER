#ifndef APP_BACKEND_CPP
#define APP_BACKEND_CPP

#include <set>
#include <cstdlib>

#include "../Common/Address.cpp"
#include "../Other/Socket/Udp/UdpSender.cpp"
#include "../Other/Socket/Udp/UdpReceiver.cpp"
#include "../App/Event.cpp"
#include "../Common/User.cpp"
#include "../Common/Connection.cpp"
#include "../Log/Logger.cpp"

class AppBackend
{
public:
  enum class State : unsigned char
  {
    NOT_LOGGED_IN,
    LOGGED_IN,
  };

private:

  static const int _S_username_psw_buffer_length = 100;
  static char* _s_buffer_username;
  static char* _s_buffer_psw;

  static const int _S_ip_address_buffer_length = 20;
  static char* _s_buffer_ip_address;
  static const int _S_port_buffer_length = 10;
  static char* _s_buffer_port;

  static const int _S_message_buffer_length = 40000;
  static char* _s_buffer_message;

  static Event _s_event;

  static State _s_state;

  static User _s_me;

  static UdpSender _s_sender;
  static UdpReceiver _s_receiver;

  static std::set<Connection> _s_connections;

  static void _s_init()
  {
    _s_sender.init();
    _s_receiver.init();
  }
  
  static void _s_init_buffers()
  {
    _s_buffer_username = new char[_S_username_psw_buffer_length];
    _s_buffer_psw = new char[_S_username_psw_buffer_length];

    _s_buffer_ip_address = new char[_S_ip_address_buffer_length];
    _s_buffer_port = new char[_S_port_buffer_length];

    _s_buffer_message = new char[_S_message_buffer_length];
  }

  static void _s_clear_buffers()
  {
    _s_buffer_username[0] = 0;
    _s_buffer_psw[0] = 0;

    _s_buffer_ip_address[0] = 0;
    _s_buffer_port[0] = 0;
    
    _s_buffer_message[0] = 0;
  }

  static void _s_handle_event()
  {
    switch(_s_event)
    {
    case Event::LOGIN:
      _s_login();
      _s_state = State::LOGGED_IN;
      break;
    case Event::LOGIN_ANONYMOUS:
      _s_login_anonymous();
      _s_state = State::LOGGED_IN;
      break;
    case Event::CONNECT:
      _s_connect();
      break;
    case Event::CONNECT_ACCEPT:
      _s_connect_accept();
      break;
    case Event::CONNECT_REJECT:
      _s_connect_reject();
      break;
    case Event::CHAT_MESSAGE:
      _s_chat_message();
      break;

    default:
      break;
    }

    _s_event = Event::NONE;
  }

  static void _s_login() { _s_me.init(_s_buffer_username, _s_buffer_psw); }
  
  static void _s_login_anonymous()
  {
    std::memcpy(_s_buffer_username, "ANONYMOUS", 10);
    /* need to generate an unique password */
    _s_login();
  }

  static void _s_connect()
  {
    Address address { _s_buffer_ip_address, static_cast<u_short>(std::strtoul(_s_buffer_port, nullptr, 0)) };
    _s_sender.send_connect(address);
  }

  static void _s_connect_reject()
  {

  }
  static void _s_connect_accept()
  {

  }

  static void _s_chat_message()
  {

  }

  static void _s_update()
  {
    // _s_receiver.receive();
  }

public:
  

  static const User& get_me() { return _s_me; }
  static const std::set<Connection>& get_connections() { return _s_connections; }

  static char* get_buffer_username() { return _s_buffer_username; }
  static char* get_buffer_psw() { return _s_buffer_psw; }

  static char* get_buffer_ip_address() { return _s_buffer_ip_address; }
  static char* get_buffer_port() { return _s_buffer_port; }

  static char* get_buffer_message() { return _s_buffer_message; }

  static const int buffer_username_length = _S_username_psw_buffer_length;
  static const int buffer_psw_length = _S_username_psw_buffer_length;

  static const int buffer_ip_address_length = _S_ip_address_buffer_length;
  static const int buffer_port_length = _S_port_buffer_length;

  static const int buffer_message_length = _S_message_buffer_length;

  static void init()
  {
    _s_init_buffers();
    _s_init();
  }

  static void update()
  {
    _s_handle_event();
    _s_update();
  }

  static void set_event(Event event)
  {
    logger << "set_event: " << event << "\n";
    _s_event = event;
  }
  
  static State get_state() { return _s_state; }
  
  AppBackend() = delete;
  ~AppBackend() = delete;

};

char* AppBackend::_s_buffer_username { nullptr };
char* AppBackend::_s_buffer_psw { nullptr };

char* AppBackend::_s_buffer_ip_address { nullptr };
char* AppBackend::_s_buffer_port { nullptr };

char* AppBackend::_s_buffer_message { nullptr };

Event AppBackend::_s_event { Event::NONE };

AppBackend::State AppBackend::_s_state { AppBackend::State::NOT_LOGGED_IN };

User AppBackend::_s_me {};

UdpSender AppBackend::_s_sender {};
UdpReceiver AppBackend::_s_receiver {};

std::set<Connection> AppBackend::_s_connections {};

#endif