// #include <iostream>
#include <cstdio>
#include <winsock2.h>

#include "../Other/Socket/Udp/UdpSender.cpp"

int main()
{
  UdpSender s; s.init();

  char* buf = new char[40000];
  Addr receiver_addr("192.168.0.100", 5678);
  std::cout << _S_Signature << "\n";

  while(true)
  {
    scanf(" %[^\n]s", buf);
    s.chat_msg(receiver_addr, ChatMessage_View { buf });
  }

  return 0;
}