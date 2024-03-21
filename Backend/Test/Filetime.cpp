#include <windows.h>
#include <iostream>
#include <iomanip>

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
  
  
  
  void FileTimeToDateTime() {
      ULARGE_INTEGER ull;
      FILETIME ft = *reinterpret_cast<FILETIME*>(&_m_timepoint);
      ull.LowPart = ft.dwLowDateTime;
      ull.HighPart = ft.dwHighDateTime;

      // Convert FILETIME to Unix Epoch
      ull.QuadPart -= 116444736000000000ULL;  // Subtract the number of 100 nanosecond intervals from 1601 to 1970
      ull.QuadPart /= 10000000;  // Convert from 100-nanosecond intervals to seconds

      time_t time = static_cast<time_t>(ull.QuadPart);  // Cast to time_t
      tm *ltm = localtime(&time);  // Convert to local time

      // Output the result
      std::cout << "Year: " << 1900 + ltm->tm_year << std::endl;
      std::cout << "Month: " << 1 + ltm->tm_mon << std::endl;
      std::cout << "Day: " << ltm->tm_mday << std::endl;
      std::cout << "Hour: " << ltm->tm_hour << std::endl;
      std::cout << "Minute: " << ltm->tm_min << std::endl;
      std::cout << "Second: " << ltm->tm_sec << std::endl;
  }
};

// std::ostream& operator<<(std::ostream& __o, const TimePoint& __tp)
// {
//   __o << __tp.timepoint();
//   return __o;
// }





// // Example Usage
// int main() {
//     // FILETIME ft;
//     // GetSystemTimeAsFileTime(&ft);  // Get current time as FILETIME
//     // FileTimeToDateTime(ft);  // Convert and display as DateTime
//     TimePoint now;
//     now.FileTimeToDateTime();
//     return 0;
// }


int main()
{
  FILETIME t;
  GetSystemTimeAsFileTime(&t);

  std::cout << t.dwHighDateTime << " " << t.dwLowDateTime << "\n";
  return 0;
}