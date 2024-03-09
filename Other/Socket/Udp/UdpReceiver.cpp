#include <memory>
#include <cassert>
#include <winsock2.h>

#include "../../../Common/Addr.cpp"
#include "UdpMsg/UdpMsg.cpp"




class UdpReceiver
{
  Addr _m_address;
  SOCKET _m_socket;
  
  static const int _BufferSize = 40000;
  std::unique_ptr<char> _m_buffer;

  void _m_initialize()
  {
    _m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    /* Set the socket I/O mode: In this case FIONBIO enables or disables
      the blocking mode for the socket based on the numerical value of iMode.
      If i_mode = 0, blocking is enabled; 
      If i_mode != 0, non-blocking mode is enabled. */

    u_long i_mode = 1;
    ioctlsocket(_m_socket, FIONBIO, &i_mode);
    

    _m_address._m_socket_addr.sin_family = AF_INET;
    _m_address._m_socket_addr.sin_port = 0; /* To let the Windows Sockets DLL select a usable port. */
    _m_address._m_socket_addr.sin_addr.s_addr = INADDR_ANY;
    
    int address_length = sizeof(_m_address._m_socket_addr);
    int ret = bind(_m_socket, reinterpret_cast<SOCKADDR*>(&_m_address._m_socket_addr), address_length);
    assert(ret != SOCKET_ERROR);

    getsockname(_m_socket, reinterpret_cast<SOCKADDR*>(&_m_address._m_socket_addr), &address_length);
    std::cout << "😉Receiver port: " << _m_address.port() << "\n";
  }


public:

  UdpReceiver() : _m_buffer { new char [_BufferSize] } { _m_initialize(); }
  
  ~UdpReceiver() noexcept
  {
    int ret = closesocket(_m_socket);
    assert(ret != SOCKET_ERROR);
  }

  // std::unique_ptr<IncomingMessage> get_incoming_message()
  void get_incoming_message()
  {
    SOCKADDR_IN sender_addr;
    int length__sender_addr = sizeof(sender_addr);

    int ret = recvfrom(_m_socket, _m_buffer.get(), 1000, 0, reinterpret_cast<SOCKADDR*>(&sender_addr), &length__sender_addr);

    if(ret == SOCKET_ERROR)
    {
      assert(WSAGetLastError() == WSAEWOULDBLOCK);

      return;

      // return new 
    }

    
    _m_buffer.get()[ret] = '\0';

    std::cout << "[" << inet_ntoa(sender_addr.sin_addr) << ":"
      << ntohs(sender_addr.sin_port)  << "] :: \"" << _m_buffer.get() << "\"\n";

  }
  
  // std::unique_ptr<IncomingMessage*> _m_parse()
  // {

  // }
  
};