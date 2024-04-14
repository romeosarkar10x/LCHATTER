#include <iostream>
#include "../../Inc/AppBackend/Frontend_Event.hpp"


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
    std::memcpy(Buffer::Username::get_buffer(), "ANONYMOUS", 10);
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
    _s_outgoing_requests.emplace_back(User {}, receiver);
    
    auto* m = new UdpMessage_ConnectionRequest {
      ConnectionRequest { User { _s_me }, Address { _s_receiver.get_socket_address() } }
    };

    _s_sender.send(receiver, m);
    delete m;
    break;
  }

  case Frontend_Event::ACCEPT_CONNECTION_REQUEST:
  {
    std::cout << "Frontend_Event::ACCEPT_CONNECTION_REQUEST BEGIN" << std::endl;
    auto itr = std::ranges::find(_s_incoming_requests, _s_current_id, _Projection);
    assert(itr != _s_incoming_requests.end());
    
    Address receiver_addr { itr->get_address() };

    auto* m = new UdpMessage_ConnectionRequest_Accepted {
      ConnectionRequest { User { _s_me }, Address { _s_receiver.get_socket_address() } }
    };

    itr->set_state(ConnectionRequest::State::ACCEPTED);
    // itr->get_address().set_ip_address(receiver_addr);
    _s_sender.send(receiver_addr, m);
    _s_connections.emplace_back(*itr);
    delete m;
    std::cout << "Frontend_Event::ACCEPT_CONNECTION_REQUEST END" << std::endl;
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
    itr->get_chat().emplace(static_cast<ChatMessage&>(*m));

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


std::ostream& operator<<(std::ostream& o, AppBackend::Frontend_Event::Enum_Frontend_Event e)
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