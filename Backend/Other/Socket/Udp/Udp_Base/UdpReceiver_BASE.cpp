#include <memory>
#include <cassert>
#include <winsock2.h>

#include "Udp_BASE.cpp"
#include "../UdpMessage/UdpMessage.cpp"
#include "../../WindowsSocketsApi.cpp"
#include "../../../../File/Logger.cpp"

/// OS Dependent

class UdpReceiver_BASE : private Udp_BASE
{
  static Logger   _s_UdpReceiver_BASE_Logger;
  static int      _s_counter;
  
  int             _m_id;
  Address         _m_sender_addr;

public:
  UdpReceiver_BASE() : Udp_BASE {}, _m_id { _s_counter++ } {}
  ~UdpReceiver_BASE() = default;

  void init()
  {
    _s_UdpReceiver_BASE_Logger << Logger::timestamp << "INIT_BEGIN    " << Logger::endl;
    _m_init();
    _s_UdpReceiver_BASE_Logger << Logger::timestamp << "INIT_END      " <<  _m_socket_address << Logger::endl;
  }

  void destroy()
  {
    _s_UdpReceiver_BASE_Logger << Logger::timestamp << "DESTROY_BEGIN " << _m_socket_address << Logger::endl;
    _m_destroy();
    _s_UdpReceiver_BASE_Logger << Logger::timestamp << "DESTROY_END   " << Logger::endl;
  }

  using Udp_BASE::get_socket_address;

  using Udp_BASE::get_buffer;
  using Udp_BASE::get_buffer_size;
  
  using Udp_BASE::get_offset;
  using Udp_BASE::reset_offset;
  using Udp_BASE::increment_offset;

  const Address& get_sender_address() const { return _m_sender_addr; }
  
  bool receive()
  {
    int length_sender_addr = sizeof(_m_sender_addr._m_addr);

    int ret = recvfrom(_m_socket, reinterpret_cast<char*>(_m_buffer), get_buffer_size(), 0, reinterpret_cast<SOCKADDR*>(&_m_sender_addr._m_addr), &length_sender_addr);

    if(ret == SOCKET_ERROR)
    {
      if(WSAGetLastError() != WSAEWOULDBLOCK)
      {
        _s_UdpReceiver_BASE_Logger << Logger::timestamp << "ERROR   " << WSAGetLastError() << Logger::endl;
      }

      return false;
    }

    reinterpret_cast<char*>(_m_buffer)[ret] = '\0';
    _m_offset = ret;

    _s_UdpReceiver_BASE_Logger << Logger::timestamp << "[#" << _m_id << "].receive " << _m_sender_addr << " @ "
      << " _m_buffer: " << _m_buffer << ", _m_offset: " << _m_offset << Logger::endl;

    for(int i = 0; i < _m_offset; i++)
    {
      _s_UdpReceiver_BASE_Logger << std::hex
        << static_cast<u_int>(*(reinterpret_cast<u_char*>(_m_buffer) + i));
      
      char c = *(reinterpret_cast<char*>(_m_buffer) + i);
      if(31 < c && c < 127) { _s_UdpReceiver_BASE_Logger << "[" << c << "]"; }
      
      _s_UdpReceiver_BASE_Logger << " ";
    }

    _s_UdpReceiver_BASE_Logger << Logger::endl;
    return true;
  }
};

int UdpReceiver_BASE::_s_counter { 0 };
Logger UdpReceiver_BASE::_s_UdpReceiver_BASE_Logger { "UdpReceiver_BASE.log" };