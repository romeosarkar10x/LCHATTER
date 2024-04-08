#include <iostream>
#include <type_traits>

template<class T>
  struct underlying_pointer_type : std::type_identity<T> {};

template<class T>
  struct underlying_pointer_type<T*>
  { using type = T; };

template<class T>
  using underlying_pointer_type_t = underlying_pointer_type<T>::type;

template<class T>
  using is_linear_pointer = std::__and_<
    std::is_pointer<T>,
    std::__not_<std::is_pointer<underlying_pointer_type_t<T>>>
  >;

template<class T>
  static constexpr bool is_linear_pointer_v = is_linear_pointer<T>::value;


// template<class T>
//   struct TypeDisplayer
//   {
//     void operator()() { std::cout << __PRETTY_FUNCTION__ << __FUNCTION__ << __LINE__ << std::endl; }
//   };


int main()
{
  std::cout << is_linear_pointer_v<int>     << std::endl;
  std::cout << is_linear_pointer_v<int*>    << std::endl; // 1
  std::cout << is_linear_pointer_v<int**>   << std::endl;
  std::cout << is_linear_pointer_v<int***>  << std::endl;
  
  std::cout << is_linear_pointer_v<char>     << std::endl;
  std::cout << is_linear_pointer_v<char*>    << std::endl; // 1
  std::cout << is_linear_pointer_v<char**>   << std::endl;
  std::cout << is_linear_pointer_v<char***>  << std::endl;

  return 0;
}