#include <cassert>
#include <cstring>

#include "../../../../../Inc/Other/Socket/Udp/Udp_BASE/UdpSender_BASE.hpp"

/// OS Dependent

UdpSender_BASE::UdpSender_BASE() : Udp_BASE {}, _m_id { _s_counter++ } {}

void UdpSender_BASE::init()
{
  _s_UdpSender_BASE_Logger << Logger::timestamp << "INIT_BEGIN    " << Logger::endl;
  _m_init();
  _s_UdpSender_BASE_Logger << Logger::timestamp << "INIT_END      " << _m_socket_address << Logger::endl;
}

void UdpSender_BASE::destroy()
{
  _s_UdpSender_BASE_Logger << Logger::timestamp << "DESTROY_BEGIN " << _m_socket_address << Logger::endl;
  _m_destroy();
  _s_UdpSender_BASE_Logger << Logger::timestamp << "DESTROY_END   " << Logger::endl;
}


void UdpSender_BASE::send(const Address& receiver_addr)
{
  assert(_m_is_initialized);

  _s_UdpSender_BASE_Logger << Logger::timestamp << "[#" << _m_id << "] SEND " << receiver_addr << " @ OFFSET: " << _m_offset << Logger::endl;
  
  for(u_int s = 0; s < _m_offset; s++)
  {
    auto f = _s_UdpSender_BASE_Logger->flags();
    _s_UdpSender_BASE_Logger << std::hex
      << static_cast<u_int>(*(reinterpret_cast<u_char*>(_m_buffer) + s));
    _s_UdpSender_BASE_Logger->flags(f);
    
    char c = *(reinterpret_cast<char*>(_m_buffer) + s);
    if(31 < c && c < 127) { _s_UdpSender_BASE_Logger << "[" << c << "]"; }
    
    _s_UdpSender_BASE_Logger << " ";
  }
  
  _s_UdpSender_BASE_Logger << Logger::endl;

  int ret = sendto(_m_socket, reinterpret_cast<char*>(_m_buffer), static_cast<int>(_m_offset), 0, reinterpret_cast<const SOCKADDR*>(&receiver_addr._m_addr), sizeof(receiver_addr._m_addr));
  
  if(ret == SOCKET_ERROR)
  {
    _s_UdpSender_BASE_Logger << Logger::timestamp << "ERROR         " << WSAGetLastError() << Logger::endl;
  }
}


int UdpSender_BASE::_s_counter { 0 };
Logger UdpSender_BASE::_s_UdpSender_BASE_Logger { "UdpSender_BASE.log" };