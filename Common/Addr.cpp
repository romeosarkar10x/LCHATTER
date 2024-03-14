#ifndef ADDRESS_CPP
#define ADDRESS_CPP

#include <iostream>
#include <string>
#include <winsock2.h>
#include <cassert>
#include "../Other/Socket/Addr_Base.cpp"

#include "Fwd.hpp"

class Addr : public Addr_Base
{
  Addr() = default;
  friend UdpSender;
  friend UdpReceiver;

public:
  
  Addr(const char* ip_address, u_short port) : Addr_Base(ip_address, port) {}

  using Addr_Base::ip_address;
  using Addr_Base::port;
  using Addr_Base::to_string;
};


#endif