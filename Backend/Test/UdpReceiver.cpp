#include <iostream>
#include <winsock2.h>
#include "../Other/Socket/Udp/UdpReceiver.cpp"

int main()
{
  WSAData wsa_data;
  WSAStartup(MAKEWORD(2, 2), &wsa_data);

  UdpReceiver r; r.init();

  while(true)
  {
    r.receive();
    Sleep(50);
  }


  WSACleanup();
  return 0;
}