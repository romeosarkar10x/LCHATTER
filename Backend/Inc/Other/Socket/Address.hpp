#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <iostream>
#include <winsock2.h>

#include "../../Common/String.hpp"

class Address
{
  friend std::ostream& operator<<(std::ostream& o, const Address& a);

public:
  SOCKADDR_IN _m_addr;
  
  Address();
  Address(const char* port);
  Address(const char* ip_address, const char* port);
  Address(const Address& addr);

  ~Address() = default;

  Address& operator=(const Address& rhs);

  String get_port() const;
  String get_ip_address() const;

  /// ip-port validator needed

  // bool set_port(const Address& addr) { _m_addr.sin_port = addr._m_addr.sin_port; }
  // bool set_ip_address(const Address& addr) { _m_addr.sin_addr = addr._m_addr.sin_addr; }
  
  void set_port(const Address& addr);
  void set_ip_address(const Address& addr);

  String to_string() const;

  int serialization_length() const;
  void serialize(char* buffer, int& offset) const;
  
  int deserialize(const char* buffer);
  int deserialize(const char* buffer, int offset);
};

#endif