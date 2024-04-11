#ifndef STRING_HPP
#define STRING_HPP

#include <string>

class String
{
  friend String operator+(const char* lhs, const String& rhs);

  char*         _m_p;
  unsigned int  _m_length;

  static const int _S_threshold_length = sizeof(_m_p); /// small string optimization

  inline void _m_destroy();

  char*         _m_get_buffer();
  const char*   _m_get_buffer() const;

public:
  String();
  String(const char* const s);
  String(const char* const s, const unsigned int length);

  String(const std::string& rhs);
  String(const String& rhs);
  String(String&& rhs) noexcept;

  ~String();
  
  String& operator=(const String& rhs);
  String& operator=(String&& rhs);

  void swap(String& rhs) noexcept;

  String operator+(const String& rhs) const;
  String operator+(const char* const rhs) const;

  bool operator<(const String& rhs) const;
  
  bool operator==(const String& rhs) const;
  bool operator!=(const String& rhs) const;
  
  const char*   get_buffer() const noexcept;
  unsigned int  get_length() const noexcept;

  operator const char*() const noexcept;
  
  unsigned int serialization_length() const;
  void serialize(char* buffer, unsigned int& offset) const;

  int deserialize(const char* const buffer);
  int deserialize(const char* buffer, int offset);

  template<typename T>
    static String to_string(T&& param) { return std::to_string(std::forward<T>(param)); }
};

#endif