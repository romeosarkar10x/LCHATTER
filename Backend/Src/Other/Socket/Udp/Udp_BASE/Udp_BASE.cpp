#include <cassert>

#include "../../../../../Inc/Other/Socket/Udp/Udp_BASE/Udp_BASE.hpp"
#include "../../../../../Inc/Other/Socket/WindowsSocketsApi.hpp"
/// OS Dependent


  
void Udp_BASE::_m_init()
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

void Udp_BASE::_m_destroy()
{
  if(_m_is_initialized)
  {
    delete [] _m_buffer;

    int ret = closesocket(_m_socket);
    assert(ret != SOCKET_ERROR);

    _m_is_initialized = false;
    WindowsSocketsApi::destroy();
  }
}

const Address&  Udp_BASE::get_socket_address() const { assert(_m_is_initialized); return _m_socket_address; }

char*         Udp_BASE::get_buffer() { assert(_m_is_initialized); return _m_buffer; }
int    Udp_BASE::get_buffer_size() { return _S_buffer_size; }

int Udp_BASE::get_offset() { assert(_m_is_initialized); return _m_offset; }
void Udp_BASE::reset_offset() { assert(_m_is_initialized); _m_offset = 0; }
void Udp_BASE::increment_offset(int amount) { assert(_m_is_initialized); _m_offset += amount; }


Udp_BASE::~Udp_BASE()
{
  _m_destroy();
}