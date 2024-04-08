#include <iostream>
#include <type_traits>

template<class T>
  struct __contains_serialize
  {

  private:
    template<
      class U,
      class V = decltype(std::declval<const U>().serialize(std::declval<char*>(), std::declval<int&>())),
      class = std::enable_if_t<std::is_same_v<int, V>>>
      static std::true_type test(U object);

    static std::false_type test(...);
  
  public:
    using type = decltype(test(std::declval<T>()));
  };

template<class T>
  struct contains_serialize : __contains_serialize<T>::type {};

template<class T>
  static constexpr bool contains_serialize_v = contains_serialize<T>::value;

struct foo {};
struct foo_with_incorrect_serialize { void serialize(const char*, int&) const; };
struct foo_with_serialize { int serialize(const char* const, int&) const; };

int main()
{
  std::cout << contains_serialize_v<foo> << std::endl;
  std::cout << contains_serialize_v<foo_with_incorrect_serialize> << std::endl;
  std::cout << contains_serialize_v<foo_with_serialize> << std::endl;
  return 0;
}