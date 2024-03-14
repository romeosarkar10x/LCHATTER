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
  enum class State : unsigned char { ON, LOGGED_IN };

private:
  static User _s_me;
  static Event _s_event;
  static State _s_state;
  static UdpSender _s_sender;
  static UdpReceiver _s_receiver;

  std::set<Connection> _s_connections;


public:
  // const char* 
  static const User& me() const { return _s_me; }
  
  static const std::set<Connection>& connections() { return _s_connections; }


  static void initialize()
  {
    
  }

  static void update()
  {
    
  }

  static void set_event(Event event)
  {

  }


  
  static State state() { return _s_state; }
  // static void set_state(State state) { _s_state = state; }
  
  AppBackend() = delete;
  ~AppBackend() = delete;

};

User AppBackend::_s_me {};
UdpSender AppBackend::_s_sender {};
UdpReceiver AppBackend::_s_receiver {};
AppBackend::State AppBackend::_s_state { AppBackend::State::ON };

#endif