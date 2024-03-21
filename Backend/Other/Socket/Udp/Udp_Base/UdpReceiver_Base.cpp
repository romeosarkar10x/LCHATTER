#include <memory>
#include <cassert>
#include <winsock2.h>

#include "Udp_Base.cpp"
#include "../UdpMessage/UdpMessage.cpp"
#include "../../WindowsSocketsApi.cpp"
#include "../../../../Common/Address.cpp"
#include "../../../../File/Logger.cpp"

class UdpReceiver_Base : private Udp_Base
{
  static Logger _s_UdpReceiver_Base_Logger;
  static int _s_counter;
  
  int _m_id;
  Address_Base _m_sender_addr;

public:
  UdpReceiver_Base() : Udp_Base {}, _m_id { _s_counter++ } {}
  ~UdpReceiver_Base() = default;

  void init() { _m_init(); }
  void destory() { _m_destroy(); }

  using Udp_Base::buffer_size;
  using Udp_Base::get_offset;
  using Udp_Base::reset_offset;
  using Udp_Base::increment_offset;

  
  using Udp_Base::get_port;
  using Udp_Base::get_buffer;

  const Address_Base& get_address() const { return _m_sender_addr; }
  
  
  bool receive()
  {
    int length_sender_addr = sizeof(_m_sender_addr._m_addr);

    int ret = recvfrom(_m_socket, reinterpret_cast<char*>(_m_buffer), buffer_size(), 0, reinterpret_cast<SOCKADDR*>(&_m_sender_addr._m_addr), &length_sender_addr);

    if(ret == SOCKET_ERROR)
    {
      // _s_UdpReceiver_Base_Logger << "error " << WSAGetLastError() << "\n";
      // assert(WSAGetLastError() == WSAEWOULDBLOCK);
      return false;
    }

    reinterpret_cast<char*>(_m_buffer)[ret] = '\0';
    _m_offset = ret;

    _s_UdpReceiver_Base_Logger << "[" << _m_id << "].receive " << _m_sender_addr << " _m_buffer: " << _m_buffer << ", _m_offset: " << _m_offset << "\n";

    for(int i = 0; i < _m_offset; i++)
    {
      _s_UdpReceiver_Base_Logger << std::hex
        << static_cast<u_int>(*(reinterpret_cast<u_char*>(_m_buffer) + i));
      
      char c = *(reinterpret_cast<char*>(_m_buffer) + i);
      if(31 < c && c < 127) { _s_UdpReceiver_Base_Logger << "[" << c << "]"; }
      
      _s_UdpReceiver_Base_Logger << " ";
    }

    _s_UdpReceiver_Base_Logger << "\n";
    return true;
  }
};

int UdpReceiver_Base::_s_counter { 0 };
Logger UdpReceiver_Base::_s_UdpReceiver_Base_Logger { "Udp_Receiver.log" };