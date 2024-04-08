#include <iostream>
#include <type_traits>

template<class T>
  struct underlying_array_type : std::type_identity<T> {};

template<class T>
  struct underlying_array_type<T[]> { using type = T; };

template<class T, int N>
  struct underlying_array_type<T[N]> { using type = T; };

template<class T>
  using underlying_array_type_t = underlying_array_type<T>::type;

template<class T>
  struct underlying_array_size : std::integral_constant<int, 0> {};

template<class T, int N>
  struct underlying_array_size<T[N]> : std::integral_constant<int, N> {};

template<class T>
  static constexpr int underlying_array_size_v = underlying_array_size<T>::value;

template<class T>
  using is_linear_array = std::__and_<
    std::is_array<T>,
    std::__not_<std::is_array<underlying_array_type_t<T>>>
  >;

template<class T>
  constexpr bool is_linear_array_v = is_linear_array<T>::value;

template<class T>
  using is_bounded_linear_array = std::__and_<
    is_linear_array<T>,
    std::is_bounded_array<T>
  >;

template<class T>
  constexpr bool is_bounded_linear_array_v = is_bounded_linear_array<T>::value;

// ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## 

template<class T>
  struct MyStruct;

template<class T>
  static constexpr int MyStruct_v = MyStruct<T>::value;

template<class T>
  struct MyStruct
  {
    static constexpr int value = 0;
  };

template<class T>
  struct MyStruct<T[]>
  {
    static constexpr int value = 10 * MyStruct_v<T> + 1;
  };

template<class T, int N>
  struct MyStruct<T[N]>
  {
    static constexpr int value = 10 * MyStruct_v<T> + N;
  };

// ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## 

int main()
{
  // std::cout << std::is_array_v<int>         << std::endl;
  // std::cout << std::is_array_v<int[][2]>    << std::endl;
  // std::cout << std::is_array_v<int[2]>      << std::endl;

  // std::cout << MyStruct_v<int[9][8][7][6]> << std::endl;


  // std::cout << is_linear_array_v<int> << std::endl;
  // std::cout << is_linear_array_v<int[]> << std::endl;
  // std::cout << is_linear_array_v<int[2]> << std::endl;
  // std::cout << is_linear_array_v<int[2][4]> << std::endl;
  // std::cout << is_linear_array_v<int[][4]> << std::endl;
  // std::cout << is_linear_array_v<int[2][3][4]> << std::endl;
  // std::cout << is_linear_array_v<int[][2][3]> << std::endl;

  std::cout << is_bounded_linear_array_v<int> << std::endl;
  std::cout << is_bounded_linear_array_v<int[]> << std::endl;
  std::cout << is_bounded_linear_array_v<int[2]> << std::endl;
  std::cout << is_bounded_linear_array_v<int[][3]> << std::endl;
  std::cout << is_bounded_linear_array_v<int[2][3]> << std::endl;

  std::cout << underlying_array_size_v<int[5]> << std::endl;
  return 0;
}