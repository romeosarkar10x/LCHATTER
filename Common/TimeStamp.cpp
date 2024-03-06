#include <iostream>
#include <windows.h>

class TimeStamp
{
  FILETIME _m_timestamp;
  TimeStamp() { GetSystemTimeAsFileTime(&_m_timestamp); }
};

int main()
{

  while(true)
  {
    Sleep(2000);
    

    FILETIME now;
    GetSystemTimeAsFileTime(&now);

    std::cout << now.dwHighDateTime << " " << now.dwLowDateTime << "\n";
  }

  // now.
  return 0;
}
