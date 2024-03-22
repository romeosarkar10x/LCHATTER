#ifndef UDP_BASE
#define UDP_BASE

#include <cassert>
#include <winsock2.h>

#include "../../Address.cpp"
#include "../../WindowsSocketsApi.cpp"
#include "../../../../File/Logger.cpp"

/* Platform dependent */

// static const u_short _S_Port = htons(22222);

class Udp_BASE
{
  static const int        _S_buffer_size = 4000;
  static const u_short    _S_Port = 0;
  
public:

  bool      _m_is_initialized { false };
  
  SOCKET    _m_socket;
  Address   _m_socket_address;
  
  char*     _m_buffer;
  int       _m_offset;
  
  void _m_init()
  {
    if(_m_is_initialized) { return; }

    WindowsSocketsApi::init();

    _m_offset = 0;
    _m_buffer = new char [_S_buffer_size];

    _m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    /* Set the socket I/O mode: In this case FIONBIO enables or disables
      the blocking mode for the socket based on the numerical value of iMode.
      If i_mode = 0, blocking is enabled; 
      If i_mode != 0, non-blocking mode is enabled. */
    u_long i_mode = 1;
    ioctlsocket(_m_socket, FIONBIO, &i_mode);

    _m_socket_address._m_addr.sin_family = AF_INET;
    _m_socket_address._m_addr.sin_port = _S_Port; /* [0] To let the Windows Sockets DLL select a usable port. */
    _m_socket_address._m_addr.sin_addr.s_addr = INADDR_ANY;
    
    int address_length = sizeof(_m_socket_address._m_addr);
    int ret = bind(_m_socket, reinterpret_cast<SOCKADDR*>(&_m_socket_address._m_addr), address_length);
    assert(ret != SOCKET_ERROR);

    getsockname(_m_socket, reinterpret_cast<SOCKADDR*>(&_m_socket_address._m_addr), &address_length);
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

  const Address&  get_socket_address() const { assert(_m_is_initialized); return _m_socket_address; }
  
  char*         get_buffer() { assert(_m_is_initialized); return _m_buffer; }
  static int    get_buffer_size() { return _S_buffer_size; }
  
  int           get_offset() { assert(_m_is_initialized); return _m_offset; }
  void          reset_offset() { assert(_m_is_initialized); _m_offset = 0; }
  void          increment_offset(int amount) { assert(_m_is_initialized); _m_offset += amount; }


  ~Udp_BASE()
  {
    _m_destroy();
  }
};

#endif