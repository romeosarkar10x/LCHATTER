#include <cassert>
#include <cstring>
#include <winsock2.h>

#include "Udp_BASE.cpp"
#include "../UdpMessage/UdpMessage.cpp"
#include "../../../../File/Logger.cpp"

/// OS Dependent

class UdpSender_BASE : private Udp_BASE
{
  static Logger   _s_UdpSender_BASE_Logger;
  static int      _s_counter;
  
  int             _m_id;
  
public:
  UdpSender_BASE() : Udp_BASE {}, _m_id { _s_counter++ } {}
  ~UdpSender_BASE() = default;

  void init()
  {
    _s_UdpSender_BASE_Logger << Logger::timestamp << "INIT_BEGIN    " << Logger::endl;
    _m_init();
    _s_UdpSender_BASE_Logger << Logger::timestamp << "INIT_END      " << _m_socket_address << Logger::endl;
  }

  void destroy()
  {
    _s_UdpSender_BASE_Logger << Logger::timestamp << "DESTROY_BEGIN " << _m_socket_address << Logger::endl;
    _m_destroy();
    _s_UdpSender_BASE_Logger << Logger::timestamp << "DESTROY_END   " << Logger::endl;
  }

  // using Udp_BASE::get_port;
  using Udp_BASE::get_buffer;
  using Udp_BASE::get_socket_address;
  using Udp_BASE::get_buffer_size;
  
  // using Udp_BASE::set_length;
  // using Udp_BASE::get_length;

  using Udp_BASE::      get_offset;
  using Udp_BASE::    reset_offset;
  using Udp_BASE::increment_offset;

  
  void send(const Address& receiver_addr)
  {
    assert(_m_is_initialized);

    _s_UdpSender_BASE_Logger << Logger::timestamp << "[#" << _m_id << "] SEND " << receiver_addr << " @ OFFSET: " << _m_offset << Logger::endl;
    
    for(int i = 0; i < _m_offset; i++)
    {
      auto f = _s_UdpSender_BASE_Logger->flags();
      _s_UdpSender_BASE_Logger << std::hex
        << static_cast<u_int>(*(reinterpret_cast<u_char*>(_m_buffer) + i));
      _s_UdpSender_BASE_Logger->flags(f);
      
      char c = *(reinterpret_cast<char*>(_m_buffer) + i);
      if(31 < c && c < 127) { _s_UdpSender_BASE_Logger << "[" << c << "]"; }
      
      _s_UdpSender_BASE_Logger << " ";
    }
    
    _s_UdpSender_BASE_Logger << Logger::endl;

    int ret = sendto(_m_socket, reinterpret_cast<char*>(_m_buffer), _m_offset, 0, reinterpret_cast<const SOCKADDR*>(&receiver_addr._m_addr), sizeof(receiver_addr._m_addr));
    
    if(ret == SOCKET_ERROR)
    {
      _s_UdpSender_BASE_Logger << Logger::timestamp << "ERROR         " << WSAGetLastError() << Logger::endl;
    }
  }
};

int UdpSender_BASE::_s_counter { 0 };
Logger UdpSender_BASE::_s_UdpSender_BASE_Logger { "UdpSender_BASE.log" };