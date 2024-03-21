#include "trace_bytes.hpp"

int main()
{
  const char* s = "can you trace me!😈";
  Memory::trace_bytes(s, 5000, 32);
  return 0;
}