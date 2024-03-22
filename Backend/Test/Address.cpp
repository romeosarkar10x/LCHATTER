#include <iostream>
#include "../Other/Socket/Address.cpp"
#include "../../Externals/trace_bytes/trace_bytes.hpp"

int main()
{
  char* buffer = new char [1000];

  Address a { "192.168.0.100", "2212" };
  std::cout << a << std::endl;

  Address b { "1.1.1.1", "80" };
  std::cout << b << std::endl;

  a.serialize(buffer);
  Memory::trace_bytes(buffer, 100, 32);
  b.deserialize(buffer);

  std::cout << a << std::endl;
  return 0;
}