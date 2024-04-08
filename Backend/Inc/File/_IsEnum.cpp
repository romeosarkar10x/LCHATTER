#include <iostream>
#include <type_traits>

enum abc { abc_0, abc_1, abc_2 };

enum class scoped_abc { sabc_0, sabc_1, sabc_2 };

int main()
{
  std::cout << std::is_enum_v<abc> << std::endl;
  std::cout << std::is_enum_v<scoped_abc> << std::endl;
  return 0;
}