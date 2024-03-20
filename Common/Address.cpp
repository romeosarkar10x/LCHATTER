#ifndef ADDRESS_CPP
#define ADDRESS_CPP

#include <iostream>
#include <string>
#include "../Other/Socket/Address_Base.cpp"

#include "Fwd.hpp"

class Address : public Address_Base
{
  friend UdpSender;
  friend UdpReceiver;

public:
  Address() = default;
  Address(const Address_Base& addr) : Address_Base { addr } {};
  Address(u_short port) : Address_Base(port) {}

  Address(const char* ip_address, u_short port) : Address_Base(ip_address, port) {}

  using Address_Base::get_port;
  using Address_Base::to_string;
  using Address_Base::get_ip_address;

  using Address_Base::set_ip_address;
  
  using Address_Base::serialize;
  using Address_Base::deserialize;
};

std::ostream& operator<<(std::ostream& o, const Address& addr)
{
  o << addr.to_string(); return o;
}

#endif