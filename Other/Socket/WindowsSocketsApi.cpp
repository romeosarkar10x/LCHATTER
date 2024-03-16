#ifndef WSA_CPP
#define WSA_CPP

#include <cassert>
#include <winsock2.h>

class WindowsSocketsApi
{
  static bool _s_is_initialized;
  static int  _s_count;

public:
  static void Startup()
  {
    if(!_s_is_initialized)
    {
      WSAData data;
      int ret = WSAStartup(MAKEWORD(2, 2), &data);
      assert(ret == 0); 
      _s_is_initialized = true;
    }
    _s_count++;
  }

  static void Cleanup()
  {
    if(0 == (--_s_count))
    {
      WSACleanup();
      _s_is_initialized = false;
    }
  }
};

bool WindowsSocketsApi::_s_is_initialized { false };
int WindowsSocketsApi::_s_count { 0 }; 

#endif