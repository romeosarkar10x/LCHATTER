#ifndef TIME_POINT_HPP
#define TIME_POINT_HPP

#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstring>
#include <utility>

#include "String.hpp"

/// OS Dependent

class TimePoint
{
  FILETIME          _m_filetime;

  mutable time_t    _m_time;
  mutable bool      _m_time_is_valid { false };

  mutable tm*       _m_localtime { nullptr };
  mutable bool      _m_localtime_is_valid { false };

  friend std::ostream& operator<<(std::ostream& o, const TimePoint& timepoint);

public:
  TimePoint(int);
  TimePoint();

  TimePoint(const TimePoint& rhs);

  TimePoint(TimePoint&& rhs);

  TimePoint& operator=(const TimePoint& rhs);
  TimePoint& operator=(TimePoint&& rhs)   noexcept;

  ~TimePoint();

  void swap(TimePoint& rhs)               noexcept;

  FILETIME  get_filetime()    const;
  time_t    get_time()        const;
  const tm* get_localtime()   const;

  void set_time(const TimePoint& rhs);
  
  void refresh();

  int serialize(char* buffer)               const;
  int serialize(char* buffer, int offset)   const;

  int deserialize(const char* buffer);
  int deserialize(const char* buffer, int offset);

  bool operator<(const TimePoint& rhs) const;

  String to_string_localtime();

private:
  friend std::ostream& operator<<(std::ostream& o, const TimePoint& timepoint);
};


#endif