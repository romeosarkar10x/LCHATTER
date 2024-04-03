#include "../../Inc/AppBackend/AppBackend.hpp"

AppBackend::State::Enum_State AppBackend::State::get_state() { return _s_state; }
void       AppBackend::State::set_state(Enum_State state) { _s_state = state; }
  
void AppBackend::Buffer::init()
{
  Username    ::init();
  Password    ::init();
  IpAddress   ::init();
  Port        ::init();
  ChatMessage ::init();
}

void AppBackend::Buffer::clear()
{
  Username    ::clear();
  Password    ::clear();
  IpAddress   ::clear();
  Port        ::clear();
  ChatMessage ::clear();
}

void AppBackend::Buffer::destroy()
{
  Username    ::destroy();
  Password    ::destroy();
  IpAddress   ::destroy();
  Port        ::destroy();
  ChatMessage ::destroy();
}



void AppBackend::Frontend_Event::set_event(Enum_Frontend_Event event) { _s_event = event; }
AppBackend::Frontend_Event::Enum_Frontend_Event  AppBackend::Frontend_Event::get_event() { return _s_event; }

void AppBackend::Frontend_Event::handle_event()
{
  if(Frontend_Event::get_event() == Frontend_Event::NONE) { return; }

  logger << Logger::timestamp << "EVENT_BEGIN " << Frontend_Event::get_event() << Logger::endl;

  switch(Frontend_Event::get_event())
  {
  case Frontend_Event::LOGIN_ANONYMOUS:
    Buffer::Username::clear();
    std::memcpy(Buffer::Username::get_buffer(), "anonymous", 10);
    [[ fallthrough ]];

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

    auto* m = new UdpMessage_ChatMessage { ChatMessage { _s_me, Buffer::ChatMessage::get_buffer(), true } };
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

void AppBackend::handle_receive()
{
  UdpMessage* m = _s_receiver.receive();
  Address sender_addr = _s_receiver.get_sender_address();

  if(m->get_type() == UdpMessage::Type::NONE) { return; }

  logger << Logger::timestamp << "RECEIVE_BEGIN " << m->get_type() << Logger::endl;
  
  switch(m->get_type())
  {

  case UdpMessage::Type::CONNECTION_REQUEST:
  {
    UdpMessage_ConnectionRequest* ptr_r = static_cast<UdpMessage_ConnectionRequest*>(m);
    auto& user = ptr_r->get_user();
    auto itr = std::ranges::find(_s_incoming_connection_requests, user, [] (const ConnectionRequest& r) { return r.get_user(); });

    if(itr != _s_incoming_connection_requests.end())
    {
      itr->get_timepoint().set_time(ptr_r->get_timepoint());
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

  logger << Logger::timestamp << "RECEIVE_END   " << m->get_type() << Logger::endl;
}


void AppBackend:: init()
{
  logger << Logger::timestamp << "INIT_BEGIN " << Logger::endl;

  _s_sender.init();
  _s_receiver.init();

  Buffer::init();
  Buffer::clear();

  logger << Logger::timestamp << "INIT_END   " << Logger::endl;
}

void AppBackend::update()
{
  logger << Logger::timestamp << "UPDATE_BEGIN " << Logger::endl;

  Frontend_Event::handle_event();
  handle_receive();

  logger << Logger::timestamp << "UPDATE_END   " << Logger::endl;
}

  
void   AppBackend::set_id(const String& id) { _s_current_id = id; }
  

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