#ifndef LOGGER_CPP
#define LOGGER_CPP

#include <fstream>
#include "../Common/TimePoint.cpp"

class Logger
{
  std::ofstream _m_file;

public:

  enum Manipulator : char { timestamp, endl };

  Logger(const char* f_name) : _m_file(f_name) {}
  
  template<typename _Tp>
    Logger& operator<<(_Tp&& _param) /// forward to std::ofstream
    {
      _m_file << (std::forward<_Tp>(_param));
      // _m_file.flush();
      return *this;
    }
  
  Logger& operator<<(Manipulator m)
  {
    switch(m)
    {
    case timestamp:
      _m_file << TimePoint {};
      break;
    case endl:
      _m_file << std::endl;
      break;
    }

    return *this;
  }

  Logger(const Logger& rhs) = delete; /// no copy
  Logger(Logger&& rhs) : _m_file { std::move(rhs._m_file) } {}

  Logger& operator=(const Logger& rhs) = delete; /// no assignment
  Logger& operator=(Logger&& rhs) { this->swap(rhs); return *this; }

  void swap(Logger& rhs) noexcept
  {
    _m_file.swap(rhs._m_file);
  }

  std::ofstream* operator->() { return &_m_file; }

  ~Logger() { _m_file.close(); }
};

Logger logger("App.log");
#endif