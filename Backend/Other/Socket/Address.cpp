#ifndef ADDRESS_CPP
#define ADDRESS_CPP

#include <iostream>
#include <cassert>
#include <winsock2.h>

#include "../../Common/String.cpp"

class Address
{

public:
  SOCKADDR_IN _m_addr;
  
  Address() { _m_addr.sin_family = AF_INET; }
  
  Address(const char* port) : Address()
  {
    _m_addr.sin_port = htons(static_cast<u_short>(std::strtoul(port, nullptr, 0)));
    _m_addr.sin_addr.s_addr = INADDR_ANY;
  }

  Address(const char* ip_address, const char* port) : Address()
  {
    _m_addr.sin_port = htons(static_cast<u_short>(std::strtoul(port, nullptr, 0)));
    _m_addr.sin_addr.s_addr = inet_addr(ip_address);
  }

  Address(const Address& addr) { std::memcpy(&_m_addr, &addr._m_addr, sizeof(SOCKADDR_IN)); }

  ~Address() {}

  Address& operator=(const Address& rhs)
  {
    this->~Address();
    new (this) Address { rhs };
    return *this;
  }

  String get_port() const { return String::to_string(ntohs(_m_addr.sin_port)); }
  String get_ip_address() const { return inet_ntoa(_m_addr.sin_addr); }

  /// ip-port validator needed
  // void set_port(const Address& addr) { _m_addr.sin_port = addr._m_addr.sin_port; }
  // void set_ip_address(const Address& addr) { _m_addr.sin_addr = addr._m_addr.sin_addr; }
  
  void set_port(const Address& addr) { _m_addr.sin_port = addr._m_addr.sin_port; }
  void set_ip_address(const Address& addr) { _m_addr.sin_addr = addr._m_addr.sin_addr; }

  String to_string() const { return "{" + get_ip_address() + ":" + get_port() + "}"; }

  int serialization_length() const { return sizeof(_m_addr.sin_port) + sizeof(_m_addr.sin_addr); }

  int serialize(char* buffer) const
  {
    std::memcpy(buffer, &_m_addr.sin_port, sizeof(_m_addr.sin_port));
    std::memcpy(buffer + sizeof(_m_addr.sin_port), &(_m_addr.sin_addr), sizeof(_m_addr.sin_addr));

    return serialization_length();
  }

  int serialize(char* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }
  
  int deserialize(const char* buffer)
  {
    std::memcpy(&_m_addr.sin_port, buffer, sizeof(_m_addr.sin_port));
    std::memcpy(&(_m_addr.sin_addr), buffer + sizeof(_m_addr.sin_port), sizeof(_m_addr.sin_addr));

    return serialization_length();
  }

  int deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }
};

std::ostream& operator<<(std::ostream& o, const Address& a) { o << a.to_string(); return o; }

#endif