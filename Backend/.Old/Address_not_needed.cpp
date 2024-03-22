#ifndef ADDRESS_CPP
#define ADDRESS_CPP

#include <iostream>
#include <string>
#include "../Other/Socket/Address_BASE.cpp"

#include "Fwd.hpp"

class Address : public Address_BASE
{
  friend UdpSender;
  friend UdpReceiver;

public:
  Address() = default;
  Address(const Address_BASE& addr) : Address_BASE { addr } {};

  Address(const char* ip_address, const char* port) :
  Address_BASE { ip_address, static_cast<u_short>(std::strtoul(port, nullptr, 0)) } {}
};

std::ostream& operator<<(std::ostream& o, const Address& a)
{
  o << Address_BASE { a }; return o;
}

#endif