#ifndef STRING_CPP
#define STRING_CPP

#include <cstring>
#include <string>
#include <utility>
#include <cinttypes>

class String
{
  char* _m_p;
  int   _m_length;

  static const int _S_threshold_length = sizeof(_m_p);

  friend String operator+(const char* lhs, const String& rhs);

  char* _m_get_buffer()
  {
    if(_m_length < _S_threshold_length) { return reinterpret_cast<char*>(&_m_p); }
    return _m_p;
  }

  const char* _m_get_buffer() const
  {
    return const_cast<String*>(this)->_m_get_buffer();
  }

  // static const _m_next_power_of_two()

public:
  String() : _m_length { 0 } { reinterpret_cast<char*>(&_m_p)[0] = 0; }
  
  String(const char* const s) : String { s, static_cast<int>(std::strlen(s)) } {}
  
  String(const char* const s, const int length) : _m_length { length }
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

  String(const std::string& rhs) : String { rhs.c_str(), static_cast<int>(rhs.length()) } {}
  
  String(const String& rhs) : _m_p { rhs._m_p }, _m_length { rhs._m_length }
  {
    if(_m_length >= _S_threshold_length)
    {
      _m_p = new char[_m_length + 1];
      std::memcpy(_m_p, rhs._m_p, _m_length + 1);
    }
  }

  String(String&& rhs) noexcept :
  _m_p { rhs._m_p },
  _m_length { std::exchange(rhs._m_length, 0) } { reinterpret_cast<char*>(&rhs._m_p)[0] = 0; }

  ~String()
  {
    if(_m_length >= _S_threshold_length)
    {
      delete [] _m_p;

      _m_length = 0;
      reinterpret_cast<char*>(&_m_p)[0] = 0;
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
    String s {};
    int total_length = _m_length + rhs._m_length;

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

  String operator+(const char* const rhs) const
  {
    int rhs_length = static_cast<int>(std::strlen(rhs));
    int total_length = _m_length + rhs_length;

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

  bool operator<(const String& rhs) const { return (strcmp(_m_get_buffer(), rhs._m_get_buffer()) < 0); }
  
  bool operator==(const String& rhs) const { return (strcmp(_m_get_buffer(), rhs._m_get_buffer()) == 0); }
  bool operator!=(const String& rhs) const { return !operator==(rhs); }
  
  const char* get_buffer() const noexcept { return _m_get_buffer(); }
  int         get_length() const noexcept { return _m_length; }

  operator const char*() const noexcept { return _m_get_buffer(); }
  
  int serialization_length() const { return static_cast<int>(sizeof(int)) + _m_length + 1; }
  
  int serialize(char* const buffer) const
  {
    *reinterpret_cast<int*>(buffer) = _m_length;
    std::memcpy(buffer + sizeof(int), _m_get_buffer(), _m_length + 1);

    return serialization_length();
  }

  int serialize(char* buffer, int offset) const { return serialize(buffer + offset); }

  int deserialize(const char* const buffer)
  {
    this->~String();
    new (this) String { buffer + sizeof(int), *reinterpret_cast<const int*>(buffer) };
    
    return static_cast<int>(sizeof(int)) + _m_length + 1;
  }

  int deserialize(const char* buffer, int offset) { return deserialize(buffer + offset); }

  template<typename _Tp>
    static String to_string(_Tp&& param) { return std::to_string(std::forward<_Tp>(param)); }
};

String operator+(const char* lhs, const String& rhs)
{
  int lhs_length = static_cast<int>(std::strlen(lhs)), rhs_length = rhs.get_length();
  int total_length = lhs_length + rhs_length;

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

#endif