#include <cstring>
#include <utility>
#include <cinttypes>

#include "../../Inc/Common/String.hpp"
#include "../../Inc/File/Serializer.hpp"
#include "../../Inc/File/Deserializer.hpp"

void String::_m_destroy()
{
  if(_m_length >= _S_threshold_length)
  {
    delete [] _m_p;

    _m_length = 0;
    reinterpret_cast<char*>(&_m_p)[0] = 0;
  }
}

char* String::_m_get_buffer()
{
  if(_m_length < _S_threshold_length) { return reinterpret_cast<char*>(&_m_p); }
  return _m_p;
}

const char* String::_m_get_buffer() const
{
  return const_cast<String*>(this)->_m_get_buffer();
}

String::String() : _m_length { 0 } { reinterpret_cast<char*>(&_m_p)[0] = 0; }

String::String(const char* const s) : String { s, static_cast<u_int>(std::strlen(s)) } {}

String::String(const char* const s, const u_int length) : _m_length { length }
{
  if(length < _S_threshold_length)
  {
    std::memcpy(&_m_p, s, length + 1);
  }
  else
  {
    _m_p = new char [length + 1];
    std::memcpy(_m_p, s, length + 1);
  }
}

String::String(const std::string& rhs) : String { rhs.c_str(), static_cast<u_int>(rhs.length()) } {}

String::String(const String& rhs) : _m_p { rhs._m_p }, _m_length { rhs._m_length }
{
  if(_m_length >= _S_threshold_length)
  {
    _m_p = new char[_m_length + 1];
    std::memcpy(_m_p, rhs._m_p, _m_length + 1);
  }
}

String::String(String&& rhs) noexcept :
  _m_p { rhs._m_p },
  _m_length { std::exchange(rhs._m_length, 0) } { reinterpret_cast<char*>(&rhs._m_p)[0] = 0; }

String::~String()
{
  _m_destroy();
}

String& String::operator=(const String& rhs)
{
  String copy = rhs;
  swap(copy);
  return *this;
}

String& String::operator=(String&& rhs) { swap(rhs); return *this; }

void String::swap(String& rhs) noexcept
{
  std::swap(_m_p, rhs._m_p);
  std::swap(_m_length, rhs._m_length);
}  

String String::operator+(const String& rhs) const
{
  String s {};
  u_int total_length = _m_length + rhs._m_length;

  if(total_length < _S_threshold_length)
  {
    std::memcpy(&s._m_p, &_m_p, _m_length);
    std::memcpy(reinterpret_cast<char*>(&s._m_p) + _m_length, &rhs._m_p, rhs._m_length + 1);
  }
  else
  {
    char* p = new char [total_length + 1];

    std::memcpy(p, _m_get_buffer(), _m_length);
    std::memcpy(p + _m_length, rhs._m_get_buffer(), rhs._m_length + 1);

    s._m_p = p;
  }

  s._m_length = total_length;
  return s;
}

String String::operator+(const char* const rhs) const
{
  u_int rhs_length = static_cast<u_int>(std::strlen(rhs));
  u_int total_length = _m_length + rhs_length;

  String s {};

  if(total_length < _S_threshold_length)
  {
    std::memcpy(&s._m_p, &_m_p, _m_length);
    std::memcpy(reinterpret_cast<char*>(&s._m_p) + _m_length, rhs, rhs_length + 1);
  }
  else
  {
    char*p = new char [total_length + 1];

    std::memcpy(p, _m_get_buffer(), _m_length);
    std::memcpy(p + _m_length, rhs, rhs_length + 1);

    s._m_p = p;
  }

  s._m_length = total_length;
  return s;
}

bool String::operator<(const String& rhs) const { return (strcmp(_m_get_buffer(), rhs._m_get_buffer()) < 0); }

bool String::operator==(const String& rhs) const { return (strcmp(_m_get_buffer(), rhs._m_get_buffer()) == 0); }
bool String::operator!=(const String& rhs) const { return !operator==(rhs); }

const char*   String::get_buffer() const noexcept { return _m_get_buffer(); }
u_int  String::get_length() const noexcept { return _m_length; }

String::operator const char*() const noexcept { return _m_get_buffer(); }

u_int String::serialization_length() const
{
  return Serializer::serialization_length(_m_length) +
    Serializer::serialization_length(_m_get_buffer(), _m_length + 1);
}

void String::serialize(char* const buffer, u_int& offset) const
{
  Serializer::serialize(_m_length, buffer, offset);
  Serializer::serialize(_m_get_buffer(), _m_length, buffer, offset);
}

void String::deserialize(const char* const buffer, u_int& offset)
{
  this->~String();

  Deserializer::deserialize(_m_length, buffer, offset);
  
  if(_m_length >= _S_threshold_length)
  {
    _m_p = new char[_m_length + 1U];
  }

  Deserializer::deserialize(_m_get_buffer(), _m_length, buffer, offset);
  _m_get_buffer()[_m_length] = '\0';
}

String operator+(const char* lhs, const String& rhs)
{
  u_int lhs_length = static_cast<u_int>(std::strlen(lhs)), rhs_length = rhs.get_length();
  u_int total_length = lhs_length + rhs_length;

  String s {};

  if(total_length < String::_S_threshold_length)
  {
    std::memcpy(&s._m_p, lhs, lhs_length + 1);
    std::memcpy(reinterpret_cast<char*>(&s._m_p) + lhs_length, &rhs._m_p, rhs_length);
  }
  else
  {
    char* p = new char[total_length + 1];

    std::memcpy(p, lhs, lhs_length);
    std::memcpy(p + lhs_length, rhs._m_get_buffer(), rhs_length + 1);

    s._m_length = total_length;
    s._m_p = p;
  }

  return s;
}