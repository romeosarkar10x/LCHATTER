#include <iostream>
#include <winsock2.h>
#include <cassert>

const u_short Port = 5150;

void start()
{
  unsigned long i_mode = 1;
  SOCKET receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  
  ioctlsocket(receiver, FIONBIO, &i_mode);

  SOCKADDR_IN receiver_addr;
  receiver_addr.sin_family = AF_INET;
  receiver_addr.sin_port = htons(Port);
  receiver_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  int ret = bind(receiver, reinterpret_cast<SOCKADDR*>(&receiver_addr), sizeof(receiver_addr));

  if(ret == SOCKET_ERROR)
  {
    std::cout << "bind failed!" << "\n";
  }
  std::cout << "ret: " << ret << ", bind successful\n";


  SOCKADDR_IN sender_addr;
  int length__sender_addr = sizeof(sender_addr);

  // sender_addr.sin_family = AF_INET;
  // sender_addr.sin_port = 5160;
  // sender_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  // sender_addr.sin_addr.s_addr = inet_addr("192.168.0.100");

  char *buffer = new char[1000];
  while(true)
  {
    Sleep(5);
    int ret = recvfrom(receiver, buffer, 1000, 0, reinterpret_cast<SOCKADDR*>(&sender_addr), &length__sender_addr);
    
    // std::cout << ret << "\n";
    // std::cout << WSAGetLastError() << " " << WSAEWOULDBLOCK << "\n";

    if(ret == SOCKET_ERROR)
    {
      assert((WSAGetLastError() == WSAEWOULDBLOCK));
      continue;
    }
    // if(ret != -1)
    // {

    // }
    buffer[ret] = 0;

    std::cout << "sin_family: " << sender_addr.sin_family << "\n";
    std::cout << "sin_port: " << sender_addr.sin_port << "\n";
    std::cout << "sin_addr: " << inet_ntoa(sender_addr.sin_addr) << "\n";

    std::cout << "buffer: " << buffer << "\n";
    
  }

  closesocket(receiver);
}

int main()
{
  WSAData wsa_data;
  WSAStartup(MAKEWORD(2, 2), &wsa_data);

  start();

  WSACleanup();
  return 0;
}