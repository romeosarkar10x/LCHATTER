#ifndef MD5_DIGEST_CPP
#define MD5_DIGEST_CPP

#include <iostream>
#include "../String.cpp"
#include "../Fwd.hpp"

class Md5_Digest
{
  u_char _m_buffer[16];
  String _m_string;
  bool _m_is_valid { false };

public:
  Md5_Digest() = default;
  Md5_Digest(const void* buffer) { std::memcpy(_m_buffer, buffer, 16); }

  const String& to_string() const
  {
    if(_m_is_valid) { return _m_string; }
    char* s = new char[33]; int i = 0;
  
    auto hexadecimal_digit = [] (char value) -> char
    {
      if(value < static_cast<char>(10)) { return value + '0'; }
      return value - static_cast<char>(10) + 'a';
    };

    for(int offset = 0; offset < 16; offset++)
    {
      u_int byte = static_cast<u_int>(*(_m_buffer + offset));
      s[i++] = hexadecimal_digit(static_cast<char>(byte / 16u));
      s[i++] = hexadecimal_digit(static_cast<char>(byte % 16u));
    }

    s[i] = 0;
    const_cast<Md5_Digest*>(this)->_m_is_valid = true;
    return const_cast<Md5_Digest*>(this)->_m_string = { s, i };
  }

  int serialize(void* buffer) const
  {
    std::memcpy(buffer, _m_buffer, 16);
    return 16;
  }

  int serialize(void* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }
  
  int deserialize(const void* buffer)
  {
    std::memcpy(_m_buffer, buffer, 16);
    _m_is_valid = false;
    return 16;
  }

  int deserialize(const void* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }
};

std::ostream& operator<<(std::ostream& __o, const Md5_Digest& digest)
{
  __o << digest.to_string(); return __o;
}

#endif