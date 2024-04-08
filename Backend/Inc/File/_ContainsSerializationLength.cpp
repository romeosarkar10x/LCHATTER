#include <iostream>
#include <type_traits>

template<class T>
  struct __contains_serialization_length
  {

  private:
    template<
      class U,
      class V = decltype(std::declval<const U>().serialization_length()),
      class = std::enable_if_t<std::is_same_v<int, V>>>
      static std::true_type test(U object);

    static std::false_type test(...);
  
  public:
    using type = decltype(test(std::declval<T>()));
  };

template<class T>
  struct contains_serialization_length : __contains_serialization_length<T>::type {};

template<class T>
  static constexpr bool contains_serialization_length_v = contains_serialization_length<T>::value;

struct foo {};
struct foo_with_incorrect_serialization_length { void serialization_length() const; };
struct foo_with_serialization_length { int serialization_length() const; };

int main()
{
  std::cout << contains_serialization_length_v<foo> << std::endl;
  std::cout << contains_serialization_length_v<foo_with_incorrect_serialization_length> << std::endl;
  std::cout << contains_serialization_length_v<foo_with_serialization_length> << std::endl;
  return 0;
}