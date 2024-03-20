#ifndef TIME_POINT_CPP
#define TIME_POINT_CPP

#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstring>
#include <utility>

class TimePoint
{
  FILETIME  _m_filetime;

  time_t    _m_time;
  bool      _m_time_is_valid { false };

  tm*       _m_localtime { nullptr };
  bool      _m_localtime_is_valid { false };

  friend std::ostream& operator<<(std::ostream& o, const TimePoint& timepoint);

public:
  TimePoint(int) {}
  TimePoint() { GetSystemTimeAsFileTime(&_m_filetime); }
    // std::cout << *this << "\x1b[32m.TimePoint()\x1b[m" << std::endl;

  TimePoint(const TimePoint& rhs) :
  _m_filetime { rhs._m_filetime },
  _m_time { rhs._m_time },
  _m_time_is_valid { rhs._m_time_is_valid },
  _m_localtime_is_valid { rhs._m_localtime_is_valid }
  {
    // std::cout << *this << "\x1b[32m.TimePoint(const TimePoint&\x1b[m " << rhs << "\x1b[32m);\x1b[m" << std::endl;
    if(_m_localtime_is_valid)
    {
      _m_localtime = new tm;
      std::memcpy(_m_localtime, rhs._m_localtime, sizeof(tm));
    }
  }

  TimePoint(TimePoint&& rhs) :
  _m_filetime { rhs._m_filetime },
  _m_time { rhs._m_time }, 
  _m_time_is_valid { rhs._m_time_is_valid },
  _m_localtime { std::exchange(rhs._m_localtime, nullptr) },
  _m_localtime_is_valid { rhs._m_localtime_is_valid } {}
  // {
  //   std::cout << "\x1b[32mTimePoint\x1b[m" << *this << " \x1b[32m(TimePoint&&\x1b[m " << rhs << "\x1b[32m]);\x1b[m" << std::endl;
  // }

  TimePoint& operator=(const TimePoint& rhs)
  {
    // std::cout << *this << "\x1b[32mTimePoint& operator=(const TimePoint&\x1b[m " << rhs << "\x1b[32m);\x1b[m" << std::endl;
    TimePoint copy = rhs;
    swap(copy);
    return *this;
  }

  TimePoint& operator=(TimePoint&& rhs) noexcept
  {
    // std::cout << "no no" << std::endl;
    swap(rhs);
    return *this;
  }

  void swap(TimePoint& rhs) noexcept
  {
    // std::cout << *this << "\x1b[32m.swap(TimePoint&&\x1b[m " << rhs << "\x1b[32m]);\x1b[m" << std::endl;
    std::swap(_m_filetime, rhs._m_filetime);
    std::swap(_m_time, rhs._m_time);
    std::swap(_m_time_is_valid, rhs._m_time_is_valid);
    std::swap(_m_localtime, rhs._m_localtime);
    std::swap(_m_localtime_is_valid, rhs._m_localtime_is_valid);
  }

  ~TimePoint()
  {
    // std::cout << *this << "\x1b[32m.~TimePoint()\x1b[m" << std::endl;
    if(_m_localtime != nullptr)
    {
      delete _m_localtime;
      _m_localtime_is_valid = false;
      _m_localtime = nullptr;
    }
  }
  
  time_t time() const
  {
    if(_m_time_is_valid) { return _m_time; }

    const_cast<TimePoint*>(this)->_m_time = *reinterpret_cast<const time_t*>(&_m_filetime);

    const_cast<TimePoint*>(this)->_m_time /= 10000000;
    const_cast<TimePoint*>(this)->_m_time -= 11644473600;
    
    const_cast<TimePoint*>(this)->_m_time_is_valid = true;
    return _m_time;
  }

  const tm* localtime() const
  {
    if(_m_localtime_is_valid) { return _m_localtime; }
    if(_m_localtime == nullptr) { const_cast<TimePoint*>(this)->_m_localtime = new tm; }

    static_cast<void>(const_cast<TimePoint*>(this)->time());
    tm* localtime = std::localtime(&_m_time);

    std::memcpy(_m_localtime, localtime, sizeof(tm));
    const_cast<TimePoint*>(this)->_m_localtime_is_valid = true;
    return _m_localtime;
  }
  
  void refresh()
  {
    GetSystemTimeAsFileTime(&_m_filetime);

    _m_time_is_valid = false;
    _m_localtime_is_valid = false;
  }

  int serialize(char* buffer) const
  {
    std::memcpy(buffer, &_m_filetime, sizeof(FILETIME));
    return sizeof(FILETIME);
  }

  int serialize(char* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }

  int deserialize(const char* buffer)
  {
    std::memcpy(&_m_filetime, buffer, sizeof(FILETIME));

    _m_time_is_valid = false;
    _m_localtime_is_valid = false;

    return sizeof(FILETIME);
  }

  int deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }

  bool operator<(const TimePoint& rhs) const
  {
    if(_m_filetime.dwHighDateTime == rhs._m_filetime.dwHighDateTime) {
      return (_m_filetime.dwLowDateTime < rhs._m_filetime.dwLowDateTime); 
    };

    return  (_m_filetime.dwHighDateTime < rhs._m_filetime.dwHighDateTime);
  }
};

std::ostream& operator<<(std::ostream& o, const TimePoint& timepoint)
{
  const tm* localtime = timepoint.localtime();
  o << "[" << localtime->tm_hour << ":" << localtime->tm_min << ":" << localtime->tm_sec << "]";
  return o;
}

// std::ostream& operator<<(std::ostream& o, const TimePoint& timepoint)
// {
//   o << " \x1b[1;31m" << reinterpret_cast<const void*>(&timepoint) << "\x1b[m {\n  _m_time: " << timepoint._m_time << ", _m_time_is_valid: " << timepoint._m_time_is_valid
//     << ", _m_localtime: " << timepoint._m_localtime << ", _m_localtime_is_valid: " << timepoint._m_localtime_is_valid << "\n}";
  
//   return o;
// }

#endif