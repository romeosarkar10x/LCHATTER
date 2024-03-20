#include <cassert>
#include <cstring>
#include <winsock2.h>

#include "Udp_Base.cpp"
#include "../UdpMessage/UdpMessage.cpp"
#include "../../../../Common/Address.cpp"
#include "../../../../Log/Logger.cpp"


class UdpSender_Base : private Udp_Base
{
  static Logger _s_UdpSender_Base_Logger;
  static int _s_counter;
  
  int _m_id;
  
public:
  UdpSender_Base() : Udp_Base {}, _m_id { _s_counter++ } {}
  ~UdpSender_Base() = default;

  void init() { _m_init(); }
  void destroy() { _m_destroy(); }

  using Udp_Base::get_port;
  using Udp_Base::get_buffer;

  using Udp_Base::buffer_size;
  
  // using Udp_Base::set_length;
  // using Udp_Base::get_length;

  using Udp_Base::      get_offset;
  using Udp_Base::    reset_offset;
  using Udp_Base::increment_offset;

  
  void send(const Address_Base& receiver_addr)
  {
    assert(_m_is_initialized);

    _s_UdpSender_Base_Logger << "[" << _m_id << "].send " << receiver_addr << " @ "
      << "_m_buffer: " << _m_buffer << ", _m_offset: " << _m_offset << "\n";
    
    for(int i = 0; i < _m_offset; i++)
    {
      auto f = _s_UdpSender_Base_Logger->flags();
      _s_UdpSender_Base_Logger << std::hex
        << static_cast<u_int>(*(reinterpret_cast<u_char*>(_m_buffer) + i));
      _s_UdpSender_Base_Logger->flags(f);
      
      char c = *(reinterpret_cast<char*>(_m_buffer) + i);
      if(31 < c && c < 127) { _s_UdpSender_Base_Logger << "[" << c << "]"; }
      
      _s_UdpSender_Base_Logger << " ";
    }
    
    _s_UdpSender_Base_Logger << "\n";

    int ret = sendto(_m_socket, reinterpret_cast<char*>(_m_buffer), _m_offset, 0, reinterpret_cast<const SOCKADDR*>(&receiver_addr._m_addr), sizeof(receiver_addr._m_addr));
    
    if(ret == SOCKET_ERROR)
    {
      _s_UdpSender_Base_Logger << "WSAError: " << WSAGetLastError() << "\n";
      assert(WSAGetLastError() == WSAEWOULDBLOCK);
    }
  }
};

int UdpSender_Base::_s_counter { 0 };
Logger UdpSender_Base::_s_UdpSender_Base_Logger { "Udp_Sender.log" };