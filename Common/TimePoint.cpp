#ifndef TIME_POINT_CPP
#define TIME_POINT_CPP

#include <iostream>
#include <windows.h>

typedef unsigned long long u_long_long;

class TimePoint
{
  u_long_long _m_timepoint;

public:
  TimePoint() { GetSystemTimeAsFileTime(reinterpret_cast<FILETIME*>(&_m_timepoint)); }
  
  u_long_long timepoint() const { return _m_timepoint; }
  
  u_long_long age() const
  {
    unsigned long long timepoint_now;
    GetSystemTimeAsFileTime(reinterpret_cast<FILETIME*>(&timepoint_now));
    return timepoint_now - _m_timepoint;
  }
  
  void refresh() { GetSystemTimeAsFileTime(reinterpret_cast<FILETIME*>(&_m_timepoint)); }

  bool operator<(const TimePoint& rhs) const { return _m_timepoint < rhs._m_timepoint; }
};

// std::ostream& operator<<(std::ostream& __o, const TimePoint& __tp)
// {
//   __o << __tp.timepoint();
//   return __o;
// }

#endif