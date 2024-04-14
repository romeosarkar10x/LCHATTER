#include <iostream>
#include <type_traits>

enum class MyEnum : int { E_0, E_1, E_2, E_3 };

void print(MyEnum e)
{
  switch(e)
  {
  case MyEnum::E_0:
    std::cout << "E_0";
    break;

  case MyEnum::E_1:
    std::cout << "E_1";
    break;

  case MyEnum::E_2:
    std::cout << "E_2";
    break;

  case MyEnum::E_3:
    std::cout << "E_3";
    break;

  default:
    std::cout << "E_X";
    break;
  }

  std::cout << std::endl;
}

int main()
{
  MyEnum e;
  reinterpret_cast<int&>(e) = 10;

  print(e);
  return 0;
}