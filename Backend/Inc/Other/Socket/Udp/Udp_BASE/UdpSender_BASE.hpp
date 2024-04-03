#include <cassert>
#include <cstring>
#include <winsock2.h>

#include "Udp_BASE.hpp"
#include "../UdpMessage/UdpMessage.hpp"
#include "../../../../File/Logger.hpp"

/// OS Dependent

class UdpSender_BASE : private Udp_BASE
{
  static Logger   _s_UdpSender_BASE_Logger;
  static int      _s_counter;
  
  int             _m_id;
  
public:
  UdpSender_BASE();
  ~UdpSender_BASE() = default;

  void init();
  void destroy();

  using Udp_BASE::get_buffer;
  using Udp_BASE::get_socket_address;
  using Udp_BASE::get_buffer_size;
  

  using Udp_BASE::        get_offset;
  using Udp_BASE::      reset_offset;
  using Udp_BASE::  increment_offset;

  void send(const Address& receiver_addr);
};