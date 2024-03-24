#ifndef APP_BACKEND_CPP
#define APP_BACKEND_CPP

#include <set>
#include <algorithm>

#include <cstdlib>

#include "Common/User.cpp"
#include "Other/Socket/Address.cpp" /// <winsock2.h>
#include "Common/Connection.cpp"
#include "File/Logger.cpp" /// <windows.h>

#include "Other/Socket/Udp/UdpSender.cpp"
#include "Other/Socket/Udp/UdpReceiver.cpp"

class AppBackend
{
public:
  class State
  {

  public:
    enum Enum_State : char
    {
      NOT_LOGGED_IN,
      LOGGED_IN,
    };
    
    static Enum_State get_state() { return _s_state; }
    static void       set_state(Enum_State state) { _s_state = state; }
  
  private:
    static Enum_State _s_state;
  };

  class Buffer
  {
    template<class _T>
      class Buffer_Mixin /// CRTP
      {
      public:
        Buffer_Mixin() = delete;
        ~Buffer_Mixin() = delete;

        static int    get_buffer_size() { return _T::_S_buffer_size; }
        static char*  get_buffer() { assert(_T::_s_buffer != nullptr); return _T::_s_buffer; }

        static void init() { if(_T::_s_buffer == nullptr) { _T::_s_buffer = new char [_T::_S_buffer_size]; } }
        static void clear() { if(_T::_s_buffer != nullptr) { _T::_s_buffer[0] = 0; } }
        static void destroy() { if(_T::_s_buffer != nullptr) { delete [] _T::_s_buffer; _T::_s_buffer = nullptr; } }

      };

  public:
    class Username : public Buffer_Mixin<Username>
    {
      friend class Buffer_Mixin<Username>;
      static const int  _S_buffer_size = 20;
      static char*      _s_buffer;
    };

    class Password : public Buffer_Mixin<Password>
    {
      friend class Buffer_Mixin<Password>;
      static const int  _S_buffer_size = 20;
      static char*      _s_buffer;
    };
    
    class IpAddress : public Buffer_Mixin<IpAddress>
    {
      friend class Buffer_Mixin<IpAddress>;
      static const int  _S_buffer_size = 20; 
      static char*      _s_buffer;
    };
    
    class Port : public Buffer_Mixin<Port>
    {
      friend class Buffer_Mixin<Port>;
      static const int  _S_buffer_size = 10;
      static char*      _s_buffer;
    };
    
    class ChatMessage : public Buffer_Mixin<ChatMessage>
    {
      friend class Buffer_Mixin<ChatMessage>;
      static const int  _S_buffer_size = 4000;
      static char*      _s_buffer;
    };
    
    static void init()
    {
      Username    ::init();
      Password    ::init();
      IpAddress   ::init();
      Port        ::init();
      ChatMessage ::init();
    }

    static void clear()
    {
      Username    ::clear();
      Password    ::clear();
      IpAddress   ::clear();
      Port        ::clear();
      ChatMessage ::clear();
    }

    static void destroy()
    {
      Username    ::destroy();
      Password    ::destroy();
      IpAddress   ::destroy();
      Port        ::destroy();
      ChatMessage ::destroy();
    }
  };

  class Frontend_Event
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

      /// GROUP
      SEND_GROUP_CHAT_MESSAGE,
        
        SEND_GROUP_CONNECTION_REQUEST,
      ACCEPT_GROUP_CONNECTION_REQUEST,
      REJECT_GROUP_CONNECTION_REQUEST,
    };

    static void                 set_event(Enum_Frontend_Event event) { _s_event = event; }
    static Enum_Frontend_Event  get_event() { return _s_event; }

    static void handle_event()
    {
      if(Frontend_Event::get_event() == Frontend_Event::NONE) { return; }

      logger << Logger::timestamp << "EVENT_BEGIN " << Frontend_Event::get_event() << Logger::endl;

      switch(Frontend_Event::get_event())
      {
      case Frontend_Event::LOGIN_ANONYMOUS:
        Buffer::Username::clear();
        std::memcpy(Buffer::Username::get_buffer(), "anonymous", 10);
        // std::memcpy(Buffer::Password::get_buffer(), _s_receiver.get_socket_address().to_string());
        /* need to generate an unique password */

      case Frontend_Event::LOGIN:
        // Error Check ...
        _s_me.init(Buffer::Username::get_buffer(), Buffer::Password::get_buffer());
        logger << "Username: " << Buffer::Username::get_buffer() << ", Password: " << Buffer::Password::get_buffer() << Logger::endl;
        State::set_state(State::LOGGED_IN);
        break;

      case Frontend_Event::SEND_CONNECTION_REQUEST:
      {
        Address receiver { Buffer::IpAddress::get_buffer(), Buffer::Port::get_buffer() };
        _s_outgoing_connection_requests.emplace_back(User {}, receiver);
        
        auto* m = new UdpMessage_ConnectionRequest {
          ConnectionRequest { User { _s_me }, Address { _s_receiver.get_socket_address() } }
        };

        _s_sender.send(receiver, m);
        delete m;
        break;
      }

      case Frontend_Event::ACCEPT_CONNECTION_REQUEST:
      {
        auto itr = std::ranges::find(_s_incoming_connection_requests, _s_current_id, _Projection);
        assert(itr != _s_incoming_connection_requests.end());
        
        Address receiver_addr { itr->get_address() };

        auto* m = new UdpMessage_ConnectionRequest_Accepted {
          ConnectionRequest { User { _s_me }, Address { _s_receiver.get_socket_address() } }
        };

        itr->set_state(ConnectionRequest::State::ACCEPTED);
        // itr->get_address().set_ip_address(receiver_addr);
        _s_sender.send(receiver_addr, m);
        _s_connections.emplace_back(*itr);
        delete m;
        break;
      }

      case Frontend_Event::REJECT_CONNECTION_REQUEST:
      {

        break;
      }

      case Frontend_Event::SEND_CHAT_MESSAGE:
      {
        auto itr = std::ranges::find(_s_connections, _s_current_id, _Projection);

        auto* m = new UdpMessage_ChatMessage { ChatMessage { _s_me, Buffer::ChatMessage::get_buffer() } };
        itr->get_chat().emplace(_s_me, Buffer::ChatMessage::get_buffer());

        _s_sender.send(itr->get_address(), m);
        delete m;

        Buffer::ChatMessage::clear();
        break;
      }

      default:
        break;
      }

      logger << Logger::timestamp << "EVENT_END   " << Frontend_Event::get_event() << Logger::endl; 
      Frontend_Event::set_event(Frontend_Event::NONE);
    }

  private:
    static Enum_Frontend_Event _s_event;
  };

  static String _s_current_id;
  static constexpr auto _Projection = [] (const ConnectionRequest& c) -> const String& { return c.get_user().get_id(); };

  static User         _s_me;
  static UdpSender    _s_sender;
  static UdpReceiver  _s_receiver;

  static std::vector<ConnectionRequest> _s_incoming_connection_requests;
  static std::vector<ConnectionRequest> _s_outgoing_connection_requests;

  static std::vector<Connection> _s_connections;
  
private:
  
  static void handle_receive()
  {
    UdpMessage* m = _s_receiver.receive();
    Address sender_addr = _s_receiver.get_sender_address();

    if(m->get_type()._m_t == UdpMessage::Type::NONE) { return; }

    logger << Logger::timestamp << "RECEIVE_BEGIN " << m->get_type()._m_t << Logger::endl;
    
    switch(m->get_type()._m_t)
    {

    case UdpMessage::Type::CONNECTION_REQUEST:
    {
      UdpMessage_ConnectionRequest* r = static_cast<UdpMessage_ConnectionRequest*>(m);
      auto& user = r->get_user();
      auto itr = std::ranges::find(_s_incoming_connection_requests, user, [] (const ConnectionRequest& r) { return r.get_user(); });

      if(itr != _s_incoming_connection_requests.end())
      {
        itr->get_timepoint().set_time(r->get_timepoint());
        break;
      }

      _s_incoming_connection_requests.push_back(*static_cast<UdpMessage_ConnectionRequest*>(m));
      _s_incoming_connection_requests.back().get_address().set_ip_address(sender_addr);
      break;
    }
    
    case UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED:
    {
      auto id = static_cast<UdpMessage_ConnectionRequest_Accepted*>(m)->get_user().get_id();
      auto itr = std::ranges::find(_s_outgoing_connection_requests, id, _Projection);

      itr->set_state(ConnectionRequest::State::ACCEPTED);
      itr->get_address().set_ip_address(sender_addr);
      static_cast<UdpMessage_ConnectionRequest_Accepted*>(m)->get_address().set_ip_address(sender_addr);

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

    logger << Logger::timestamp << "RECEIVE_END   " << m->get_type()._m_t << Logger::endl;
  }

public:

  static void init()
  {
    logger << Logger::timestamp << "INIT_BEGIN " << Logger::endl;

    _s_sender.init();
    _s_receiver.init();

    Buffer::init();
    Buffer::clear();

    logger << Logger::timestamp << "INIT_END   " << Logger::endl;
  }

  static void update()
  {
    logger << Logger::timestamp << "UPDATE_BEGIN " << Logger::endl;

    Frontend_Event::handle_event();
    handle_receive();

    logger << Logger::timestamp << "UPDATE_END   " << Logger::endl;
  }

  
  static void   set_id(const String& id) { _s_current_id = id; }
  

  AppBackend() = delete;
  ~AppBackend() = delete;
};

char* AppBackend::Buffer::Username    ::_s_buffer { nullptr };
char* AppBackend::Buffer::Password    ::_s_buffer { nullptr };
char* AppBackend::Buffer::IpAddress   ::_s_buffer { nullptr };
char* AppBackend::Buffer::Port        ::_s_buffer { nullptr };
char* AppBackend::Buffer::ChatMessage ::_s_buffer { nullptr };

AppBackend::Frontend_Event::Enum_Frontend_Event AppBackend::Frontend_Event::_s_event { AppBackend::Frontend_Event::NONE };

String    AppBackend::_s_current_id {};

AppBackend::State::Enum_State AppBackend::State::_s_state { AppBackend::State::NOT_LOGGED_IN };

User          AppBackend::_s_me {};
UdpSender     AppBackend::_s_sender {};
UdpReceiver   AppBackend::_s_receiver {};

std::vector<Connection> AppBackend::_s_connections {};

std::vector<ConnectionRequest> AppBackend::_s_incoming_connection_requests;
std::vector<ConnectionRequest> AppBackend::_s_outgoing_connection_requests;

#include "App/Frontend_Event.cpp"

#endif