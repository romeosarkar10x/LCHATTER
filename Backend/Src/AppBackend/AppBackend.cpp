#include "../../Inc/AppBackend/AppBackend.hpp"
#include "../../Inc/AppBackend/Frontend_Event.hpp"

AppBackend::State::Enum_State AppBackend::State::get_state() { return _s_state; }
void       AppBackend::State::set_state(Enum_State state) { _s_state = state; }
  
void AppBackend::Buffer::alloc()
{
  Username    ::alloc();
  Password    ::alloc();
  IpAddress   ::alloc();
  Port        ::alloc();
  ChatMessage ::alloc();
}

void AppBackend::Buffer::clear()
{
  Username    ::clear();
  Password    ::clear();
  IpAddress   ::clear();
  Port        ::clear();
  ChatMessage ::clear();
}

void AppBackend::Buffer::dealloc()
{
  Username    ::dealloc();
  Password    ::dealloc();
  IpAddress   ::dealloc();
  Port        ::dealloc();
  ChatMessage ::dealloc();
}

void AppBackend::handle_receive()
{
  logger << Logger::timestamp << "RECEIVE_BEGIN " << Logger::endl;
  
  UdpMessage* m = _s_receiver.receive();
  Address sender_addr = _s_receiver.get_sender_address();

  if(m->get_type() == UdpMessage::Type::NONE) { return; }
  
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
    const String& id = static_cast<UdpMessage_ConnectionRequest_Accepted*>(m)->get_user().get_id();
    auto itr = std::ranges::find(_s_outgoing_connection_requests, id, _Projection);

    itr->set_state(ConnectionRequest::State::ACCEPTED);
    itr->get_address().set_ip_address(sender_addr);
    static_cast<UdpMessage_ConnectionRequest_Accepted*>(m)->get_address().set_ip_address(sender_addr);

    if(std::ranges::find(_s_connections, id, [] (const Connection& c) -> const String& { return c.get_user().get_id(); }) != _s_connections.end())
    {
      break;
    }
    
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


void AppBackend::init()
{
  logger << Logger::timestamp << "INIT_BEGIN " << Logger::endl;

  _s_sender.init();
  _s_receiver.init();

  Buffer::alloc();
  Buffer::clear();

  logger << Logger::timestamp << "INIT_END   " << Logger::endl;
}

void AppBackend::destroy()
{
  _s_sender.destroy();
  _s_receiver.destroy();

  Buffer::dealloc();
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