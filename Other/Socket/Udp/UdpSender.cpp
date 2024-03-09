#include "../../../Common/Addr.cpp"
#include "UdpMsg/UdpMsg.cpp"
#include <cassert>
#include <cstring>


class UdpSender
{
  Addr _m_address;
  SOCKET _m_socket;

  void _m_initialize()
  {
    _m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    u_long i_mode = 1;
    ioctlsocket(_m_socket, FIONBIO, &i_mode);

    _m_address._m_socket_addr.sin_family = AF_INET;
    _m_address._m_socket_addr.sin_port = 0; /* To let the Windows Sockets DLL select a usable port. */
    _m_address._m_socket_addr.sin_addr.s_addr = INADDR_ANY;

    int address_length = sizeof(_m_address._m_socket_addr);
    int ret = bind(_m_socket, reinterpret_cast<SOCKADDR*>(&_m_address._m_socket_addr), address_length);
    assert(ret != SOCKET_ERROR);

    getsockname(_m_socket, reinterpret_cast<SOCKADDR*>(&_m_address._m_socket_addr), &address_length);
    std::cout << "😃Sender port: " << _m_address.port() << "\n";
  }

public:
  UdpSender() { _m_initialize(); }

  ~UdpSender() noexcept
  {
    int ret = closesocket(_m_socket);
    assert(ret != SOCKET_ERROR);
  }

  void chat_msg(const Addr& receiver_addr, const char* msg, int msg_len = -1)
  {
    if(msg_len == -1) { msg_len = std::strlen(msg); }
    
    int ret = sendto(_m_socket, msg, msg_len, 0, reinterpret_cast<const SOCKADDR*>(&receiver_addr._m_socket_addr), sizeof(receiver_addr._m_socket_addr));
    std::cout << WSAGetLastError() << "\n";
    assert(ret != SOCKET_ERROR);
  }

  void ping(const Addr& receiver_addr);
  void conn(const Addr& receiver_addr);
  void conn_ack(const Addr& receiver_addr);


  // void ping(const Addr& host);
  // void send(const Addr& receiver, const Message& message);
  

};

// bool UdpSender::_s_initialized = false;