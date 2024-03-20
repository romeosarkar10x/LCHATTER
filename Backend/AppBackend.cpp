#ifndef APP_BACKEND_CPP
#define APP_BACKEND_CPP

#include <set>
#include <algorithm>

#include <cstdlib>

#include "../Log/Logger.cpp"

#include "../App/Event.cpp"
#include "../Common/User.cpp"
#include "../Common/Address.cpp"
#include "../Common/Connection.cpp"

#include "../Other/Socket/Udp/UdpSender.cpp"
#include "../Other/Socket/Udp/UdpReceiver.cpp"

class AppBackend
{
public:
  enum class State : unsigned char
  {
    NOT_LOGGED_IN,
    LOGGED_IN,
  };

  struct Buffer
  {
    struct UserName
    {
      static const int _S_buffer_size = 100;
      static char* _s_buffer;
    };

    struct Password
    {
      static const int _S_buffer_size = 100;
      static char* _s_buffer;
    };
    
    struct IpAddress
    {
      static const int _S_buffer_size = 20; 
      static char* _s_buffer;
    };
    
    struct Port
    {
      static const int _S_buffer_size = 10;
      static char* _s_buffer;
    };
    
    struct ChatMessage
    {
      static const int _S_buffer_size = 40000;
      static char* _s_buffer;
    };
    
    static void _s_init()
    {
      UserName::_s_buffer = new char [UserName::_S_buffer_size];
      Password::_s_buffer = new char [Password::_S_buffer_size];

      IpAddress::_s_buffer = new char [IpAddress::_S_buffer_size];
      Port::_s_buffer = new char [Port::_S_buffer_size];

      ChatMessage::_s_buffer = new char[ChatMessage::_S_buffer_size];
      assert(ChatMessage::_s_buffer != nullptr);
    }

    static void _s_clear()
    {
      UserName::_s_buffer[0] = 0;
      Password::_s_buffer[0] = 0;

      IpAddress::_s_buffer[0] = 0;
      Port::_s_buffer[0] = 0;
      
      ChatMessage::_s_buffer[0] = 0;
    }
  };

  static Event  _s_event;
  static String _s_current_id;
  static constexpr auto _Projection = [] (const ConnectionRequest& c) -> const String& { return c.get_user().get_id(); };

  static State _s_state;


  static User         _s_me;
  static UdpSender    _s_sender;
  static UdpReceiver  _s_receiver;

  static std::vector<ConnectionRequest> _s_incoming_connection_requests;
  static std::vector<ConnectionRequest> _s_outgoing_connection_requests;

  static std::vector<Connection> _s_connections;
  
private:
  static void _s_handle_event()
  {
    if(_s_event != Event::NONE) { logger << _s_event << "\n"; }

    switch(_s_event)
    {
    case Event::LOGIN_ANONYMOUS:
      std::memcpy(Buffer::UserName::_s_buffer, "ANONYMOUS_USER", 15);
      /* need to generate an unique password */
      // fall

    case Event::LOGIN:
      // Error Check ...
      _s_me.init(Buffer::UserName::_s_buffer, Buffer::Password::_s_buffer);
      _s_state = State::LOGGED_IN;
      break;

    case Event::SEND_CONNECTION_REQUEST:
    {
      Address receiver { Buffer::IpAddress::_s_buffer, static_cast<u_short>(std::strtoul(Buffer::Port::_s_buffer, nullptr, 0)) };
      _s_outgoing_connection_requests.emplace_back(User {}, receiver);
      
      auto* m = new UdpMessage_ConnectionRequest {
        ConnectionRequest { User { _s_me }, Address { _s_receiver.get_port() } }
      };

      _s_sender.send(receiver, m);
      delete m;
      break;
    }

    case Event::ACCEPT_CONNECTION_REQUEST:
    {
      // std::cout << "Current Id: " << _s_current_id << &_s_current_id << std::endl;
      // std::cout << &(_s_incoming_connection_requests[0].get_user().get_id()) << std::endl;
      // std::cout << _s_incoming_connection_requests.size() << std::endl;
      // for(const auto& r : _s_incoming_connection_requests) { std::cout << r.get_user().get_id() << " " << &r.get_user().get_id() << std::endl; }
      
      auto itr = std::ranges::find(_s_incoming_connection_requests, _s_current_id, _Projection);
      
      // std::cout << "HERE" << std::endl;
      assert(itr != _s_incoming_connection_requests.end());
      
      Address receiver_addr { itr->get_address() };

      auto* m = new UdpMessage_ConnectionRequest_Accepted {
        ConnectionRequest { User { _s_me }, Address { _s_receiver.get_port() } }
      };

      itr->set_state(ConnectionRequest::State::ACCEPTED);
      // itr->get_address().set_ip_address(receiver_addr);
      _s_sender.send(receiver_addr, m);
      _s_connections.emplace_back(*itr);
      delete m;
      break;
    }

    case Event::REJECT_CONNECTION_REQUEST:
    {

      break;
    }

    case Event::SEND_CHAT_MESSAGE:
    {
      auto itr = std::ranges::find(_s_connections, _s_current_id, _Projection);

      auto* m = new UdpMessage_ChatMessage { ChatMessage { _s_me, Buffer::ChatMessage::_s_buffer } };
      itr->get_chat().emplace(_s_me, Buffer::ChatMessage::_s_buffer);

      std::cout << "address: " << itr->get_address() << std::endl;
      _s_sender.send(itr->get_address(), m);
      delete m;

      Buffer::ChatMessage::_s_buffer[0] = 0;
      break;
    }

    default:
      break;
    }

    _s_event = Event::NONE;
  }

  static void _s_update()
  {
    UdpMessage* m = _s_receiver.receive();
    Address sender_addr = _s_receiver.get_address();
    
    switch(m->get_type()._m_t)
    {
    case UdpMessage::Type::NONE:
      break;

    case UdpMessage::Type::CONNECTION_REQUEST:
      _s_incoming_connection_requests.push_back(*static_cast<UdpMessage_ConnectionRequest*>(m));
      _s_incoming_connection_requests.back().get_address().set_ip_address(sender_addr);
      break;
    
    case UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED:
    {
      auto id = static_cast<UdpMessage_ConnectionRequest_Accepted*>(m)->get_user().get_id();
      auto itr = std::ranges::find(_s_outgoing_connection_requests, id, _Projection);

      itr->set_state(ConnectionRequest::State::ACCEPTED);
      itr->get_address().set_ip_address(sender_addr);
      static_cast<UdpMessage_ConnectionRequest_Accepted*>(m)->get_address().set_ip_address(sender_addr);

      std::cout << "here !! " << itr->get_address() << std::endl;
      // logger << itr->get_address() << "\n";
      _s_connections.emplace_back(*static_cast<UdpMessage_ConnectionRequest_Accepted*>(m));
      break;
    }
    
    case UdpMessage::Type::CONNECTION_REQUEST_REJECTED:
      break;
    
    case UdpMessage::Type::CHAT_MESSAGE:
    {
      auto id = static_cast<UdpMessage_ChatMessage*>(m)->get_sender().get_id();
      auto itr = std::ranges::find(_s_connections, id, _Projection);

      itr->get_chat().emplace(static_cast<ChatMessage>(*static_cast<UdpMessage_ChatMessage*>(m)));
      break;
    }
    
    case UdpMessage::Type::PING:
      break;

    default:
      break;
    }
    
  }

public:

  static void init()
  {
    _s_sender.init();
    _s_receiver.init();

    Buffer::_s_init();
    Buffer::_s_clear();
  }

  static void update()
  {
    _s_handle_event();
    _s_update();
  }

  
  static State  get_state() { return _s_state; }
  
  static void   set_event(Event event) { _s_event = event; }
  
  static void   set_id(const String& id) { _s_current_id = id; }
  

  AppBackend() = delete;
  ~AppBackend() = delete;

};

char* AppBackend::Buffer::UserName::_s_buffer { nullptr };
char* AppBackend::Buffer::Password::_s_buffer { nullptr };

char* AppBackend::Buffer::IpAddress::_s_buffer { nullptr };
char* AppBackend::Buffer::Port::_s_buffer { nullptr };

char* AppBackend::Buffer::ChatMessage::_s_buffer { nullptr };

Event AppBackend::_s_event { Event::NONE };
String AppBackend::_s_current_id {};

AppBackend::State AppBackend::_s_state { AppBackend::State::NOT_LOGGED_IN };

User AppBackend::_s_me {};
UdpSender AppBackend::_s_sender {};
UdpReceiver AppBackend::_s_receiver {};

std::vector<Connection> AppBackend::_s_connections {};

std::vector<ConnectionRequest> AppBackend::_s_incoming_connection_requests;
std::vector<ConnectionRequest> AppBackend::_s_outgoing_connection_requests;
 
#endif