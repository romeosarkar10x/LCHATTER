#ifndef WINDOWS_SOCKET_API
#define WINDOWS_SOCKET_API

#include <cassert>
#include <winsock2.h>

class WindowsSocketsApi
{
  static bool _s_is_initialized;
  static int  _s_count;

public:
  static void init();
  static void destroy();
};

#endif