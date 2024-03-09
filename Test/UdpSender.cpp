#include <iostream>
#include <winsock2.h>

#include "../Other/Socket/Udp/UdpSender.cpp"

int main()
{
  WSAData wsa_data;
  WSAStartup(MAKEWORD(2, 2), &wsa_data);
  
  Addr receiver_addr("127.0.0.1", 61506);
  char* buf = new char[1000];

  UdpSender s;

  while(true)
  {
    scanf(" %[^\n]s", buf);
    s.chat_msg(receiver_addr, buf);
  }

  WSACleanup();
  return 0;
}