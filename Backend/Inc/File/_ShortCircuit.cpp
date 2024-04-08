#include <iostream>

template<class T>
  struct x {};

int main()
{
  std::bool_constant<std::false_type::value && x<void>::value>object {};
  std::cout << object.value << std::endl;
  return 0;
}