#include <iostream>
#include "Trait.hpp"

class MyClass
{

public:
  void deserialize(const char*, u_int&);
  u_int deserialization_length(const char*, u_int&) const;
};

int main()
{
  std::cout << contains_method_deserialize_v<MyClass> << std::endl;
  std::cout << contains_method_deserialization_length_v<MyClass> << std::endl;
  return 0;
}