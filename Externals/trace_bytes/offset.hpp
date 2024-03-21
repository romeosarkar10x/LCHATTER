#include <iostream>
#include "global.hpp"

namespace Memory
{
  struct offset
  {
    u_char m_length;

    static char get_hex_digit(char digit)
    {
      if(digit >= static_cast<char>(16))
      {
        // throw logic error!
      }

      if(digit > static_cast<char>(9)) {
        return (char)(digit - static_cast<char>(10)) + 'a';
      }

      return (char)digit + '0';
    }

    static std::string get_hex(char _byte)
    {
      std::string s;

      char digit_0 = _byte % 16, digit_1 = _byte / 16;
      s += get_hex_digit(digit_1);
      s += get_hex_digit(digit_0);

      return s;
    }

    static std::string to_string(int _offset)
    { // pads offset to 6 Characters!
      std::string s;
      int size = 0;
      while(_offset != 0)
      {
        char digit = static_cast<char>(_offset % 16);
        s += get_hex_digit(digit), _offset /= 16;
        size++;
      }
      
      while(size < 6) {
        s += '0', size++;
      }

      if(size > 6)
      {
        std::string error = "offset > 16^6";
        throw std::out_of_range(error);
      }

      for(int u = 0, v = size - 1U; u < v; u++, v--) {
        std::swap(s[u], s[v]);
      }

      return s;
    }
  };
}