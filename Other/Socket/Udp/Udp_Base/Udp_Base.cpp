#ifndef UDP_BASE
#define UDP_BASE

#include <cassert>
#include <winsock2.h>

#include "../../Address_Base.cpp"
#include "../../WindowsSocketsApi.cpp"
#include "../../../../Log/Logger.cpp"

/* Platform dependent */

// static const u_short _S_Port = htons(22222);
static const u_short _S_Port = 0;

class Udp_Base
{
public:

  static const int _S_buffer_size = 40000;

  bool      _m_is_initialized { false };
  
  SOCKET        _m_socket;
  Address_Base  _m_socket_addr;
  
  char*     _m_buffer;
  int       _m_offset;
  
  void _m_init()
  {
    if(_m_is_initialized) { return; }

    WindowsSocketsApi::init();

    _m_buffer = new char [_S_buffer_size];
    // _m_len = 0;

    _m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    /* Set the socket I/O mode: In this case FIONBIO enables or disables
      the blocking mode for the socket based on the numerical value of iMode.
      If i_mode = 0, blocking is enabled; 
      If i_mode != 0, non-blocking mode is enabled. */
    u_long i_mode = 1;
    ioctlsocket(_m_socket, FIONBIO, &i_mode);

    _m_socket_addr._m_addr.sin_family = AF_INET;
    _m_socket_addr._m_addr.sin_port = _S_Port; /* [0] To let the Windows Sockets DLL select a usable port. */
    _m_socket_addr._m_addr.sin_addr.s_addr = INADDR_ANY;
    
    int address_length = sizeof(_m_socket_addr._m_addr);
    int ret = bind(_m_socket, reinterpret_cast<SOCKADDR*>(&_m_socket_addr._m_addr), address_length);
    assert(ret != SOCKET_ERROR);

    getsockname(_m_socket, reinterpret_cast<SOCKADDR*>(&_m_socket_addr._m_addr), &address_length);
    _m_is_initialized = true;
  }

  void _m_destroy()
  {
    if(_m_is_initialized)
    {
      int ret = closesocket(_m_socket);
      assert(ret != SOCKET_ERROR);

      _m_is_initialized = false;
      WindowsSocketsApi::destroy();
    }
  }

  u_short get_port() const { assert(_m_is_initialized); return _m_socket_addr.get_port(); }
  char* get_buffer() { assert(_m_is_initialized); return _m_buffer; }

  static int buffer_size() { return _S_buffer_size; }
  
  // void  set_length(int length) { assert(_m_is_initialized); _m_len = length; }
  // int   get_length() { assert(_m_is_initialized); return _m_len; }
  
  int        get_offset() { assert(_m_is_initialized); return _m_offset; }
  void     reset_offset() { assert(_m_is_initialized); _m_offset = 0; }
  void increment_offset(int amount) { assert(_m_is_initialized); _m_offset += amount; }


  ~Udp_Base()
  {
    _m_destroy();
  }
};

#endif