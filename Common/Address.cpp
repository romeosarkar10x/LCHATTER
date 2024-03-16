#ifndef ADDRESS_CPP
#define ADDRESS_CPP

#include <iostream>
#include <string>
#include <winsock2.h>
#include <cassert>
#include "../Other/Socket/Address_Base.cpp"

#include "Fwd.hpp"

class Address : public Address_Base
{
  Address() = default;
  
  friend UdpSender;
  friend UdpReceiver;

public:
  
  Address(const char* ip_address, u_short port) : Address_Base(ip_address, port) {}

  using Address_Base::port;
  using Address_Base::to_string;
  using Address_Base::ip_address;
};


#endif