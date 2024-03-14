#include <string>

class Md5_Digest
{
  char [16] _m_buffer;
public:
  std::string to_string()
  {
    std::string s;
  
    auto hexadecimal_digit = [] (char value) -> char
    {
      if(value < static_cast<char>(10)) { return value + '0'; }
      return value - static_cast<char>(10) + 'a';
    };

    for(int offset = 0; offset < 16; offset++)
    {
      u_int byte = static_cast<u_int>(*(reinterpret_cast<const u_char*>(_m_buffer) + offset));
      s = s + hexadecimal_digit(static_cast<char>(byte / 16)) + hexadecimal_digit(static_cast<char>(byte % 16));
    }

    return s;
  }
  
};