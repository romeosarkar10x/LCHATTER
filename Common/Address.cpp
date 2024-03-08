#ifndef ADDRESS_CPP
#define ADDRESS_CPP

#include <iostream>
#include <string>
#include <winsock2.h>


#include "ForwardDeclaration.hpp"

class Address
{
  SOCKADDR_IN _m_socket_addr;
  friend class UdpReceiver; 
  Address() = default;

public:
  
  Address(std::string ipv4_address, short port);
  Address(const char* ipv4_address, short port);

  std::string ipv4_address();
  std::string port();
};

#endif