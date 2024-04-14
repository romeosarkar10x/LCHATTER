#include <iostream>
#include <type_traits>

template<class T>
  struct __contains_serialize
  {

  private:
    template<class U, U>
    struct dummy {};

    template<class U>
      static std::true_type test(dummy<void (U::*)(char*, u_int&) const, &U::serialize>*);

    template<class U>
      static std::false_type test(...);
  
  public:
    using type = decltype(test<T>(0));
  };

template<class T>
  struct contains_serialize : __contains_serialize<T>::type {};

template<class T>
  static constexpr bool contains_serialize_v = contains_serialize<T>::value;

struct foo {};
struct foo_with_incorrect_serialize { void serialize(char*, u_int&) const; };
struct foo_with_serialize { u_int serialize(char* const, u_int&) const; };

int main()
{
  std::cout << contains_serialize_v<foo> << std::endl;
  std::cout << contains_serialize_v<foo_with_incorrect_serialize> << std::endl;
  std::cout << contains_serialize_v<foo_with_serialize> << std::endl;
  return 0;
}