#ifndef UDP_BASE_HPP
#define UDP_BASE_HPP

#include <winsock2.h>

#include "../../Address.hpp"

/// OS Dependent

// static const u_short _S_Port = htons(22222);

class Udp_BASE
{
  static const int        _S_buffer_size = 4000;
  static const u_short    _S_Port = 0;
  
public:

  bool      _m_is_initialized { false };
  
  SOCKET    _m_socket;
  Address   _m_socket_address;
  
  char*     _m_buffer;
  int       _m_offset;
  
  void _m_init();
  void _m_destroy();

  const Address&  get_socket_address() const;
  
  char*           get_buffer();
  static int      get_buffer_size();
  
  int             get_offset();
  void            reset_offset();
  void            increment_offset(int amount);


  ~Udp_BASE();
};

#endif