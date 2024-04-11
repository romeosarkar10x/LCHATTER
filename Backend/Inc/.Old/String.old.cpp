#ifndef STRING_CPP
#define STRING_CPP

#include <iostream>
#include <utility>
#include <cstring>

/// A simple RAII holder for c-style strings

class String
{
  char* _m_p { nullptr };
  int   _m_length { 0 };

  friend String operator+(const char* lhs, const String& rhs);

public:
  String() = default;

  // String(char*& s, int length) : _m_p { std::exchange(s, nullptr) }, _m_length { length } {}
  // String(char*& s) : String { s, static_cast<int>(std::strlen(s)) } {}
  
  String(const char* s, int length) : _m_p { new char[length + 1] }, _m_length { length } { std::memcpy(_m_p, s, length + 1); }
  String(const char* s) : String { s, static_cast<int>(std::strlen(s)) } {}

  String(const std::string& rhs) : String { rhs.c_str(), static_cast<int>(rhs.length()) } {}

  String(const String& rhs) : _m_length { rhs._m_length }
  {
    if(rhs._m_p != nullptr)
    {
      _m_p = new char[_m_length + 1];
      std::memcpy(_m_p, rhs._m_p, _m_length + 1);
    }
  }

  String(String&& rhs) noexcept :
  _m_p { std::exchange(rhs._m_p, nullptr) },
  _m_length { std::exchange(rhs._m_length, 0) } {}

  ~String()
  {
    if(_m_p != nullptr)
    {
      delete [] _m_p;
      _m_p = nullptr;
      _m_length = 0;
    }
  }
  
  String& operator=(const String& rhs)
  {
    String copy = rhs;
    swap(copy);
    return *this;
  }

  String& operator=(String&& rhs) { swap(rhs); return *this; }

  void swap(String& rhs) noexcept
  {
    std::swap(_m_p, rhs._m_p);
    std::swap(_m_length, rhs._m_length);
  }

  String operator+(const String& rhs) const
  {
    int final_length = _m_length + rhs._m_length;
    char* p = new char[final_length + 1];

    std::memcpy(p, _m_p, _m_length);
    std::memcpy(p + _m_length, rhs._m_p, rhs._m_length + 1);

    String s;
    s._m_length = final_length;
    s._m_p = p;

    return s;
  }

  String operator+(const char* rhs) const
  {
    int rhs_length = static_cast<int>(std::strlen(rhs));
    int final_length = _m_length + rhs_length;
    char* p = new char[final_length + 1];

    std::memcpy(p, _m_p, _m_length);
    std::memcpy(p + _m_length, rhs, rhs_length + 1);

    String s;
    s._m_length = final_length;
    s._m_p = p;
    
    return s;
  }

  bool operator<(const String& rhs) const { return (strcmp(_m_p, rhs._m_p) < 0); }
  bool operator==(const String& rhs) const { return (strcmp(_m_p, rhs._m_p) == 0); }
  
  const char* get_buffer() const noexcept { return _m_p; }
  int         get_length() const noexcept { return _m_length; }

  operator const char*() const noexcept { return _m_p; }
  operator const void*() const noexcept { return _m_p; }
  
  unsigned int serialize(char* buffer) const
  {
    if(_m_p == nullptr)
    {
      reinterpret_cast<char*>(buffer)[0] = 0;
      return 1;
    }

    std::memcpy(buffer, _m_p, _m_length + 1);
    return _m_length + 1;
  }

  unsigned int serialize(char* buffer, int offset) const { return serialize(buffer + offset); }

  int deserialize(const char* buffer)
  {
    this->~String();
    new (this) String(buffer);
    return _m_length + 1;
  }

  int deserialize(const char* buffer, int offset) { return deserialize(buffer + offset); }
};

String operator+(const char* lhs, const String& rhs)
{
  int lhs_length = static_cast<int>(std::strlen(lhs));
  int rhs_length = rhs.get_length();
  int final_length = lhs_length + rhs_length;
  char* p = new char[final_length + 1];

  std::memcpy(p, lhs, lhs_length);
  std::memcpy(p + lhs_length, rhs._m_p, rhs_length + 1);

  return { p, final_length };
}

std::ostream& operator<<(std::ostream& __o, const String& string)
{
  __o << ((string.get_buffer() == nullptr) ? "null" : string.get_buffer()); return __o;
}

#endif