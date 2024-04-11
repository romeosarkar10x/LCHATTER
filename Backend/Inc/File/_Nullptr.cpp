#include <iostream>
#include <type_traits>

int main()
{
  std::cout << sizeof(nullptr) << std::endl;
  std::cout << std::is_fundamental_v<std::nullptr_t> << std::endl;
  return 0;
}