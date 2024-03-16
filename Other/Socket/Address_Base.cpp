#ifndef ADDR_BASE
#define ADDR_BASE

#include <iostream>
#include <winsock2.h>
#include <cassert>
#include "../../Common/String.cpp"

class Address_Base
{
public:
  
  SOCKADDR_IN _m_addr;
  Address_Base() = default;
  
  Address_Base(const char* ip_address, u_short port)
  {
    _m_addr.sin_family = AF_INET;
    _m_addr.sin_port = htons(port);
    _m_addr.sin_addr.s_addr = inet_addr(ip_address);
  }

  String ip_address() const
  {
    char* p = inet_ntoa(_m_addr.sin_addr);
    assert(p != nullptr);
    return p;
  }

  u_short port() const { return ntohs(_m_addr.sin_port); }
  String to_string() const { return std::string("[") + static_cast<const char*>(ip_address()) + ":" + std::to_string(port()) + "]"; }
};

std::ostream& operator<<(std::ostream& o, Address_Base addr)
{
  o << addr.to_string(); return o;
}

#endif