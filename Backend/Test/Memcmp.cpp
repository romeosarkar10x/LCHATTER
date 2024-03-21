#include <iostream>
#include <cstring>

int main()
{
  const char* s = "lc", * s2 = "LC";

  std::cout << std::memcmp(s, s2, 2) << "\n";
  return 0;
}