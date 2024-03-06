#include <iostream>
#include <string>

class Address
{
  int _m_ipv4_address;
  short _m_port;
  
  Address(std::string ipv4_address, short port);
  Address(const char* ipv4_address, short port);

  std::string ipv4_address();
  std::string port();
  
};