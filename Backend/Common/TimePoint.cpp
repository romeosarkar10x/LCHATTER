#ifndef TIME_POINT_CPP
#define TIME_POINT_CPP

#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstring>
#include <utility>

#include "String.cpp"

/// OS Dependent


class TimePoint
{
  FILETIME  _m_filetime;

  time_t    _m_time;
  bool      _m_time_is_valid { false };

  tm*       _m_localtime { nullptr };
  bool      _m_localtime_is_valid { false };

  friend std::ostream& operator<<(std::ostream& o, const TimePoint& timepoint);

public:
  TimePoint(int)  {}
  TimePoint()     { GetSystemTimeAsFileTime(&_m_filetime); }

  TimePoint(const TimePoint& rhs) :
  _m_filetime { rhs._m_filetime },
  _m_time { rhs._m_time },
  _m_time_is_valid { rhs._m_time_is_valid },
  _m_localtime_is_valid { rhs._m_localtime_is_valid }
  {
    if(_m_localtime_is_valid)
    {
      _m_localtime = new tm;
      std::memcpy(_m_localtime, rhs._m_localtime, sizeof(tm));
    }
  }

  TimePoint(TimePoint&& rhs) :
  _m_filetime { rhs._m_filetime },
  _m_time { rhs._m_time }, 
  _m_time_is_valid { std::exchange(rhs._m_time_is_valid, false) },
  _m_localtime { std::exchange(rhs._m_localtime, nullptr) },
  _m_localtime_is_valid { std::exchange(rhs._m_localtime_is_valid, false) } {}

  TimePoint& operator=(const TimePoint& rhs) { TimePoint copy = rhs; swap(copy); return *this; }
  TimePoint& operator=(TimePoint&& rhs) noexcept { swap(rhs); return *this; }

  void swap(TimePoint& rhs) noexcept
  {
    std::swap(_m_filetime, rhs._m_filetime);
    std::swap(_m_time, rhs._m_time);
    std::swap(_m_time_is_valid, rhs._m_time_is_valid);
    std::swap(_m_localtime, rhs._m_localtime);
    std::swap(_m_localtime_is_valid, rhs._m_localtime_is_valid);
  }

  ~TimePoint()
  {
    if(_m_localtime != nullptr)
    {
      delete _m_localtime;
      _m_localtime_is_valid = false;
      _m_localtime = nullptr;
    }
  }

  FILETIME get_filetime() const { return _m_filetime; }
  
  time_t get_time() const
  {
    if(_m_time_is_valid) { return _m_time; }
    
    ULARGE_INTEGER u_large;

    u_large.LowPart = _m_filetime.dwLowDateTime;
    u_large.HighPart = _m_filetime.dwHighDateTime;
    u_large.QuadPart /= 10000000ull;
    u_large.QuadPart -= 11644473600ull;

    const_cast<TimePoint*>(this)->_m_time = static_cast<time_t>(u_large.QuadPart);
    const_cast<TimePoint*>(this)->_m_time_is_valid = true;

    return _m_time;
  }

  void set_time(const TimePoint& rhs) { this->operator=(rhs); }

  const tm* get_localtime() const
  {
    if(_m_localtime_is_valid) { return _m_localtime; }
    if(_m_localtime == nullptr) { const_cast<TimePoint*>(this)->_m_localtime = new tm; }

    static_cast<void>(const_cast<TimePoint*>(this)->get_time());
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
    if(_m_filetime.dwHighDateTime == rhs._m_filetime.dwHighDateTime) { return (_m_filetime.dwLowDateTime < rhs._m_filetime.dwLowDateTime); };
    return  (_m_filetime.dwHighDateTime < rhs._m_filetime.dwHighDateTime);
  }

  String to_string_localtime()
  {
    auto localtime = get_localtime();
    return String::to_string(localtime->tm_hour) + ":" + String::to_string(localtime->tm_min) + ":" + String::to_string(localtime->tm_sec);
  }
};

std::ostream& operator<<(std::ostream& o, const TimePoint& timepoint)
{
  const tm* localtime = timepoint.get_localtime();
  const FILETIME filetime = timepoint.get_filetime();
  o << "[" << localtime->tm_hour << ":" << localtime->tm_min << ":" << localtime->tm_sec << ":" << (filetime.dwLowDateTime % 10000000) / 10000 << "] ";
  return o;
}

#endif