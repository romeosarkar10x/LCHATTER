#include <iostream>
#include "symbol.hpp"

namespace Memory
{
  struct byte
  {
    using symbol = symbol__default;

    const void* ptr;
    byte(const void* _ptr, size_t _offset) : ptr(reinterpret_cast<const void*>(reinterpret_cast<const u_char*>(_ptr) + _offset)) { }
    byte(const void* _ptr) : byte(_ptr, 0U) { }
    
    static char to_char__hex_digit(u_char digit)
    {
      if(digit >= static_cast<u_char>(16u))
      {
        // throw logic error!
      }

      if(digit > static_cast<u_char>(9u)) {
        return (char)(digit - static_cast<u_char>(10u)) + 'a';
      }
      return (char)digit + '0';
    }

    std::string to_string__hex()
    {
      u_char n = __u_char(), digit_0 = static_cast<u_char>(n % 16u), digit_1 = static_cast<u_char>(n / 16u);

      std::string hex;
      hex += to_char__hex_digit(digit_1);
      hex += to_char__hex_digit(digit_0);

      return hex;
    }

    bool is_printable()
    {
      char c = __char();
      if(' ' <= c && c <= '~') {
        return true;
      }

      return false;
    }

    std::string to_string__ascii()
    {
      if(is_printable()) {
        return std::string() + __char();
      }

      return symbol::text::non_printable;
    }

  private:
    char __char() {
      return *reinterpret_cast<const char*>(ptr);
    }

    u_char __u_char() {
      return *reinterpret_cast<const u_char*>(ptr);
    }
  };
}