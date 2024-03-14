#ifndef ADDR_BASE
#define ADDR_BASE

#include <iostream>
#include <winsock2.h>
#include <cassert>

class Addr_Base
{
public:
  
  SOCKADDR_IN _m_addr;
  Addr_Base() = default;
  
  Addr_Base(const char* ip_address, u_short port)
  {
    _m_addr.sin_family = AF_INET;
    _m_addr.sin_port = htons(port);
    _m_addr.sin_addr.s_addr = inet_addr(ip_address);
  }

  std::string ip_address() const
  {
    char* p = inet_ntoa(_m_addr.sin_addr);
    assert(p != nullptr);
    return p;
  }

  u_short port() const { return ntohs(_m_addr.sin_port); }
  std::string to_string() const { return "[" + ip_address() + ":" + std::to_string(port()) + "]"; }
};

#endif