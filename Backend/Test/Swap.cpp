#include <iostream>

int main()
{
  char a[10] = "hello!!";
  char b[10] = "ha ha ha";

  std::swap(a, b);

  std::cout << a << "\n" << b << "\n";

  return 0;
}