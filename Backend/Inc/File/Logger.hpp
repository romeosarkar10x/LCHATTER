#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include "../Common/TimePoint.hpp"

class Logger
{
  std::ofstream _m_file;

public:

  enum Manipulator : char { timestamp, endl };

  Logger(const char* f_name);
  
  template<typename _Tp>
    Logger& operator<<(_Tp&& _param) /// forward to std::ofstream
    {
      _m_file << (std::forward<_Tp>(_param));
      // _m_file.flush();
      return *this;
    }
  
  Logger& operator<<(Manipulator m);

  Logger(const Logger& rhs) = delete; /// no copy
  Logger(Logger&& rhs);

  Logger& operator=(const Logger& rhs) = delete; /// no assignment
  Logger& operator=(Logger&& rhs);

  void swap(Logger& rhs) noexcept;

  std::ofstream* operator->();
  ~Logger();
};

extern Logger logger;

#endif