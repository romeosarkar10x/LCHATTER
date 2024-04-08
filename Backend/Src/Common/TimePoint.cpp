#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstring>
#include <utility>

#include "../../Inc/Common/TimePoint.hpp"
#include "../../Inc/File/Serializer.hpp"

/// OS Dependent

TimePoint::TimePoint(int)  {}
TimePoint::TimePoint()     { GetSystemTimeAsFileTime(&_m_filetime); }

TimePoint::TimePoint(const TimePoint& rhs) :
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

TimePoint::TimePoint(TimePoint&& rhs) :
  _m_filetime { rhs._m_filetime },
  _m_time { rhs._m_time }, 
  _m_time_is_valid { std::exchange(rhs._m_time_is_valid, false) },
  _m_localtime { std::exchange(rhs._m_localtime, nullptr) },
  _m_localtime_is_valid { std::exchange(rhs._m_localtime_is_valid, false) } {}

TimePoint& TimePoint::operator=(const TimePoint& rhs) { TimePoint copy = rhs; swap(copy); return *this; }
TimePoint& TimePoint::operator=(TimePoint&& rhs) noexcept { swap(rhs); return *this; }

void TimePoint::swap(TimePoint& rhs) noexcept
{
  std::swap(_m_filetime, rhs._m_filetime);
  std::swap(_m_time, rhs._m_time);
  std::swap(_m_time_is_valid, rhs._m_time_is_valid);
  std::swap(_m_localtime, rhs._m_localtime);
  std::swap(_m_localtime_is_valid, rhs._m_localtime_is_valid);
}

TimePoint::~TimePoint()
{
  if(_m_localtime != nullptr)
  {
    delete _m_localtime;
    _m_localtime_is_valid = false;
    _m_localtime = nullptr;
  }
}

FILETIME TimePoint::get_filetime() const { return _m_filetime; }

time_t TimePoint::get_time() const
{
  if(_m_time_is_valid) { return _m_time; }
  
  ULARGE_INTEGER u_large;

  u_large.LowPart = _m_filetime.dwLowDateTime;
  u_large.HighPart = _m_filetime.dwHighDateTime;
  u_large.QuadPart /= 10000000ull;
  u_large.QuadPart -= 11644473600ull;

  _m_time = static_cast<time_t>(u_large.QuadPart);
  _m_time_is_valid = true;

  return _m_time;
}

void TimePoint::set_time(const TimePoint& rhs) { this->operator=(rhs); }

const tm* TimePoint::get_localtime() const
{
  if(_m_localtime_is_valid) { return _m_localtime; }
  if(_m_localtime == nullptr) { _m_localtime = new tm; }

  static_cast<void>(get_time());
  tm* localtime = std::localtime(&_m_time);

  std::memcpy(_m_localtime, localtime, sizeof(tm));
  _m_localtime_is_valid = true;
  return _m_localtime;
}

void TimePoint::refresh()
{
  GetSystemTimeAsFileTime(&_m_filetime);

  _m_time_is_valid = false;
  _m_localtime_is_valid = false;
}

int TimePoint::serialization_length() const
{
  return Serializer::serialization_length(_m_filetime);
}

void TimePoint::serialize(char* buffer, int& offset) const
{
  Serializer::serialize(_m_filetime, buffer, offset);
}

int TimePoint::deserialize(const char* buffer)
{
  std::memcpy(&_m_filetime, buffer, sizeof(FILETIME));

  _m_time_is_valid = false;
  _m_localtime_is_valid = false;

  return sizeof(FILETIME);
}

int TimePoint::deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }

bool TimePoint::operator<(const TimePoint& rhs) const
{
  if(_m_filetime.dwHighDateTime == rhs._m_filetime.dwHighDateTime) { return (_m_filetime.dwLowDateTime < rhs._m_filetime.dwLowDateTime); };
  return  (_m_filetime.dwHighDateTime < rhs._m_filetime.dwHighDateTime);
}

String TimePoint::to_string_localtime()
{
  auto localtime = get_localtime();
  return String::to_string(localtime->tm_hour) + ":" + String::to_string(localtime->tm_min) + ":" + String::to_string(localtime->tm_sec);
}

std::ostream& operator<<(std::ostream& o, const TimePoint& timepoint)
{
  const tm* localtime = timepoint.get_localtime();
  const FILETIME filetime = timepoint.get_filetime();
  o << "[" << localtime->tm_hour << ":" << localtime->tm_min << ":" << localtime->tm_sec << ":" << (filetime.dwLowDateTime % 10000000) / 10000 << "] ";
  return o;
}