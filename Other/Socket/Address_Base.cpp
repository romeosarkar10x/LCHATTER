#ifndef ADDRESS_BASE_CPP
#define ADDRESS_BASE_CPP

#include <iostream>
#include <cassert>
#include <winsock2.h>

#include "../../Common/String.cpp"

class Address_Base
{
public:
  
  SOCKADDR_IN _m_addr;
  Address_Base() = default;

  Address_Base(u_short port)
  {
    _m_addr.sin_family = AF_INET;
    _m_addr.sin_port = htons(port);
    _m_addr.sin_addr.s_addr = INADDR_ANY;
  }
  
  Address_Base(const char* ip_address, u_short port)
  {
    _m_addr.sin_family = AF_INET;
    _m_addr.sin_port = htons(port);
    _m_addr.sin_addr.s_addr = inet_addr(ip_address);
  }

  Address_Base(const Address_Base& rhs)
  {
    std::memcpy(&_m_addr, &rhs._m_addr, sizeof(SOCKADDR_IN));
  }

  String  get_ip_address() const { return inet_ntoa(_m_addr.sin_addr); }
  u_short get_port() const { return ntohs(_m_addr.sin_port); }

  void set_ip_address(const Address_Base& rhs) { _m_addr.sin_addr = rhs._m_addr.sin_addr; }

  String to_string() const { return std::string("[") + static_cast<const char*>(get_ip_address()) + ":" + std::to_string(get_port()) + "]"; }

  int serialize(char* buffer) const
  {
    std::memcpy(buffer, &_m_addr, sizeof(SOCKADDR_IN));
    return sizeof(SOCKADDR_IN);
  }

  int serialize(char* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }
  
  int deserialize(const char* buffer)
  {
    std::memcpy(&_m_addr, buffer, sizeof(SOCKADDR_IN));
    return sizeof(SOCKADDR_IN);
  }

  int deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }
};

std::ostream& operator<<(std::ostream& o, const Address_Base& addr)
{
  o << addr.to_string(); return o;
}


#endif