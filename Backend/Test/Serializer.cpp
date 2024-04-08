#include <iostream>

#include "../Inc/File/Serializer.hpp"
#include "../../Externals/trace_bytes/trace_bytes.hpp"

int main()
{
  char* buffer = new char [2400];

  int offset = 0;


  {
    char c = 'h';
    Serializer::serialize(c, buffer, offset);
  }

  {
    int x = 15;
    Serializer::serialize(x, buffer, offset);
  }

  {
    enum MyEnum : int { EN_0 = 13, EN_1 } e { EN_0 };
    Serializer::serialize(e, buffer, offset);
  }
  
  Memory::trace_bytes(buffer, 2400, 32);
  
  return 0;
}