#ifndef ADDRESS_CPP
#define ADDRESS_CPP

#include <iostream>
#include <string>
#include <winsock2.h>
#include <cassert>

#include "Fwd.hpp"

class Addr
{
  SOCKADDR_IN _m_socket_addr;
  friend class UdpSender; 
  friend class UdpReceiver; 
  Addr() = default;

public:
  
  Addr(const char* ipv4_address, u_short port)
  {
    _m_socket_addr.sin_family = AF_INET;
    _m_socket_addr.sin_port = htons(port);
    _m_socket_addr.sin_addr.s_addr = inet_addr(ipv4_address);
  }

  std::string ipv4_address()
  {
    char* p = inet_ntoa(_m_socket_addr.sin_addr);
    assert(p != nullptr);
    return p;
  }

  u_short port() { return ntohs(_m_socket_addr.sin_port); }
};

#endif