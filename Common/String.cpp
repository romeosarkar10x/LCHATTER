#include <iostream>
#include <utility>
#include <cstring>

/// A simple RAII holder for c-style strings

class String
{
  char* _m_p;
  int _m_length;

public:
  String() : _m_p { nullptr }, _m_length { 0 } {}
  
  String(const char* s, int length) : _m_p { new char[length + 1] }, _m_length { length + 1 } { std::memcpy(_m_p, s, length + 1); }

  String(const char* s)
  {
    _m_length = static_cast<int>(std::strlen(s));
    _m_p = new char[_m_length + 1];
    std::memcpy(_m_p, s, _m_length + 1);
  }

  String(const String& rhs) : _m_length { rhs._m_length }
  {
    _m_p = new char[_m_length + 1];
    std::memcpy(_m_p, rhs._m_p, _m_length + 1);
  }

  String(String&& rhs) : _m_p { std::exchange(rhs._m_p, nullptr) }, _m_length { std::exchange(rhs._m_length, 0) } {}
  
  String& operator=(const String& rhs)
  {
    String copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  String& operator=(String&& rhs) { std::swap(*this, rhs); return *this; }

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

  const void* buffer() const { return _m_p; }
  const char* ptr() const { return _m_p; }
  int length() const { return _m_length; }

  ~String()
  {
    if(_m_p != nullptr)
    {
      delete [] _m_p;
      _m_p = nullptr;
      _m_length = 0;
    }
  }
};

String operator+(const char* lhs, const String& rhs)
{
  return rhs.operator+(lhs);
}

std::ostream& operator<<(std::ostream& __o, const String& string)
{
  __o << string.ptr(); return __o;
}