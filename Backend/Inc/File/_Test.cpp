#include <iostream>
#include <type_traits>

template<class T>
  using is_fundamentally_serializable = 
    std::__or_<
      std::is_enum<T>,
      std::__and_<std::is_fundamental<T>, std::__not_<std::is_void<T>>> >;

template<class T>
  constexpr bool is_fundamentally_serializable_v = is_fundamentally_serializable<T>::value;

enum MyEnum : int { ENUMERATOR_0, ENUMERATOR_1 };

int main()
{
  
  std::cout << is_fundamentally_serializable_v<int>     << std::endl;
  std::cout << is_fundamentally_serializable_v<double>  << std::endl;
  std::cout << is_fundamentally_serializable_v<MyEnum>  << std::endl;

  return 0;
}