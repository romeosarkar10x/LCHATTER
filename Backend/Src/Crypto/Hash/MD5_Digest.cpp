#include <iostream>
#include <cstring>
#include <utility>

#include "../../../Inc/Crypto/Hash/MD5_Digest.hpp"
#include "../../../Inc/Common/String.hpp"
#include "../../../Inc/Common/Fwd.hpp"
#include "../../../Inc/File/Serializer.hpp"
#include "../../../Inc/File/Deserializer.hpp"

MD5_Digest::MD5_Digest(const char* buffer) { std::memcpy(_m_buffer, buffer, sizeof(_m_buffer)); }

MD5_Digest::MD5_Digest(MD5_Digest&& rhs) :
  _m_string { std::move(rhs._m_string) },
  _m_is_valid { rhs._m_is_valid } { std::memcpy(_m_buffer, rhs._m_buffer, sizeof(_m_buffer)); }

void MD5_Digest::swap(MD5_Digest& rhs) noexcept
{
  std::swap(_m_buffer, rhs._m_buffer);
  _m_string.swap(rhs._m_string);
  std::swap(_m_is_valid, rhs._m_is_valid);
}

MD5_Digest& MD5_Digest::operator=(const MD5_Digest& rhs)
{
  MD5_Digest copy = rhs;
  swap(copy);
  return *this;
}

MD5_Digest& MD5_Digest::operator=(MD5_Digest&& rhs)
{
  swap(rhs);
  return *this;
}

const String& MD5_Digest::to_string() const
{
  if(_m_is_valid) { return _m_string; }
  
  char* s = new char[33]; u_int i = 0;
  
  auto hexadecimal_digit = [] (char value) -> char
  {
    if(value < static_cast<char>(10)) { return value + '0'; }
    return value - static_cast<char>(10) + 'a';
  };

  for(u_int offset = 0U; offset < 16U; offset++)
  {
    u_int curr_byte = static_cast<u_int>(*(_m_buffer + offset));
    s[i++] = hexadecimal_digit(static_cast<char>(curr_byte / 16u));
    s[i++] = hexadecimal_digit(static_cast<char>(curr_byte % 16u));
  }

  s[i] = '\0';

  _m_is_valid = true;
  _m_string = { s, i };

  return _m_string;
}

bool MD5_Digest::operator==(const MD5_Digest& rhs) const { return (std::memcmp(_m_buffer, rhs._m_buffer, 16) == 0); }

u_int MD5_Digest::serialization_length() const
{
  return Serializer::serialization_length(_m_buffer);
}

void MD5_Digest::serialize(char* buffer, u_int& offset) const
{
  Serializer::serialize(_m_buffer, buffer, offset);
}

void MD5_Digest::deserialize(const char* const buffer, u_int& offset)
{
  this->~MD5_Digest();

  Deserializer::deserialize(_m_buffer, buffer, offset);
  // std::memcpy(_m_buffer, buffer, sizeof(_m_buffer));
  // _m_is_valid = false;
  
  // return sizeof(_m_buffer);
}

MD5_Digest::~MD5_Digest()
{
  _m_string.~String();
  _m_is_valid = false;
}

std::ostream& operator<<(std::ostream& o, const MD5_Digest& digest)
{
  o << digest.to_string(); return o;
}