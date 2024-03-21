#ifndef MD5_DIGEST_CPP
#define MD5_DIGEST_CPP

#include <iostream>
#include <cstring>
#include <utility>
#include "../../Common/String.cpp"
#include "../../Common/Fwd.hpp"


class MD5_Digest
{
  u_char _m_buffer[16];
  
  String _m_string;
  bool _m_is_valid { false };

  friend MD5_Hash;

public:
  MD5_Digest() = default;
  MD5_Digest(const char* buffer) { std::memcpy(_m_buffer, buffer, sizeof(_m_buffer)); }

  MD5_Digest(const MD5_Digest& rhs) = default;
  MD5_Digest(MD5_Digest&& rhs) :
  _m_string { std::move(rhs._m_string) },
  _m_is_valid { rhs._m_is_valid } { std::memcpy(_m_buffer, rhs._m_buffer, sizeof(_m_buffer)); }
  
  void swap(MD5_Digest& rhs) noexcept
  {
    std::swap(_m_buffer, rhs._m_buffer);
    _m_string.swap(rhs._m_string);
    std::swap(_m_is_valid, rhs._m_is_valid);
  }

  MD5_Digest& operator=(const MD5_Digest& rhs)
  {
    MD5_Digest copy = rhs;
    swap(copy);
    return *this;
  }

  MD5_Digest& operator=(MD5_Digest&& rhs)
  {
    swap(rhs);
    return *this;
  }

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

    const_cast<MD5_Digest*>(this)->_m_is_valid = true;
    const_cast<MD5_Digest*>(this)->_m_string = { s, i };

    return _m_string;
  }

  int serialize(char* buffer) const
  {
    std::memcpy(buffer, _m_buffer, 16);
    return 16;
  }

  int serialize(char* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }
  
  int deserialize(const char* buffer)
  {
    std::memcpy(_m_buffer, buffer, sizeof(_m_buffer));
    _m_is_valid = false;
    
    return sizeof(_m_buffer);
  }

  int deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }
};

std::ostream& operator<<(std::ostream& __o, const MD5_Digest& digest)
{
  __o << digest.to_string(); return __o;
}

#endif