#include <iostream>
#include <windows.h>

class TimeStamp
{
  unsigned long long _m_timestamp;

public:
  TimeStamp() { GetSystemTimeAsFileTime(reinterpret_cast<FILETIME*>(&_m_timestamp)); }
  bool operator<(const TimeStamp& rhs);

  unsigned long long timestamp() const { return _m_timestamp; }
};

std::ostream& operator<<(std::ostream& __o, const TimeStamp& __timestamp)
{
  __o << __timestamp.timestamp();
  return __o;
}


