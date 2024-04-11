#ifndef LINEAR_POINTER_HPP
#define LINEAR_POINTER_HPP

#include <type_traits>

template<class T>
  struct underlying_pointer_type : std::type_identity<void> { };

template<class T>
  struct underlying_pointer_type<T*>
  { using type = T; };

template<class T>
  using underlying_pointer_type_t = underlying_pointer_type<T>::type;

template<class T>
  using is_linear_pointer = std::conjunction<
    std::is_pointer<T>,
    std::negation<std::is_pointer<underlying_pointer_type_t<T>>>
  >;

template<class T>
  static constexpr bool is_linear_pointer_v = is_linear_pointer<T>::value;

template<class T>
  struct __contains_method_serialize
  {

  private:
    template<
      class U,
      class V = decltype(std::declval<const U>().serialize(std::declval<char*>(), std::declval<unsigned int&>())),
      class = std::enable_if_t<std::is_same_v<void, V>>
    >
      static std::true_type test(U object);

    static std::false_type test(...);
  
  public:
    using type = decltype(test(std::declval<T>()));
  };

template<class T>
  struct contains_method_serialize : __contains_method_serialize<T>::type {};

template<class T>
  static constexpr bool contains_method_serialize_v = contains_method_serialize<T>::value;

template<class T>
  struct __contains_method_serialization_length
  {

  private:
    template<
      class U,
      class V = decltype(std::declval<const U>().serialization_length()),
      class = std::enable_if_t<std::is_same_v<unsigned int, V>>
    >
      static std::true_type test(U object);

    static std::false_type test(...);
  
  public:
    using type = decltype(test(std::declval<T>()));
  };

template<class T>
  struct contains_method_serialization_length : __contains_method_serialization_length<T>::type {};

template<class T>
  static constexpr bool contains_method_serialization_length_v = contains_method_serialization_length<T>::value;

template<class T>
  struct underlying_array_type : std::type_identity<void> {};

template<class T>
  struct underlying_array_type<T[]> { using type = T; };

template<class T, unsigned int N>
  struct underlying_array_type<T[N]> { using type = T; };

template<class T>
  using underlying_array_type_t = underlying_array_type<T>::type;

template<class T>
  struct underlying_array_size : std::integral_constant<unsigned int, 0U> {};

template<class T, unsigned int N>
  struct underlying_array_size<T[N]> : std::integral_constant<unsigned int, N> {};

template<class T>
  static constexpr unsigned int underlying_array_size_v = underlying_array_size<T>::value;

template<class T>
  using is_linear_array = std::conjunction<
    std::is_array<T>,
    std::negation<std::is_array<underlying_array_type_t<T>>>
  >;

template<class T>
  constexpr bool is_linear_array_v = is_linear_array<T>::value;

template<class T>
  using is_bounded_linear_array = std::conjunction<
    is_linear_array<T>,
    std::is_bounded_array<T>
  >;

template<class T>
  constexpr bool is_bounded_linear_array_v = is_bounded_linear_array<T>::value;

#endif