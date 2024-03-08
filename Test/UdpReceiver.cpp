#include <iostream>
#include <winsock2.h>
#include "../Other/Socket/Udp/UdpReceiver.cpp"

// const u_short Port = 0;

// void start()
// {
//   SOCKET receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  
//   SOCKADDR_IN receiver_addr;
//   receiver_addr.sin_family = AF_INET;
//   receiver_addr.sin_port = htons(Port);
//   receiver_addr.sin_addr.s_addr = htonl(INADDR_ANY);

//   int ret = bind(receiver, reinterpret_cast<SOCKADDR*>(&receiver_addr), sizeof(receiver_addr));

//   if(ret == SOCKET_ERROR)
//   {
//     std::cout << "bind failed!" << "\n";
//   }
//   std::cout << "ret: " << ret << ", bind successful\n";
  
  
//   // getsockopt(receiver, SOL_SOCKET, SO_)
//   // SOCKADDR_IN socket_name;
//   // int length__socket_name = sizeof(socket_name);
//   // getsockname(receiver, reinterpret_cast<SOCKADDR*>(&socket_name), &length__socket_name);
//   // SOCKADDR_IN socket_name;
//   int length__receiver_addr = sizeof(receiver_addr);
//   getsockname(receiver, reinterpret_cast<SOCKADDR*>(&receiver_addr), &length__receiver_addr);

//   // std::cout << "sin_family: " << receiver.sin_family << "\n";
//   std::cout << "sin_port: " << ntohs(receiver_addr.sin_port) << "\n";


//   SOCKADDR_IN sender_addr;
//   int length__sender_addr = sizeof(sender_addr);

//   // sender_addr.sin_family = AF_INET;
//   // sender_addr.sin_port = 5160;
//   // sender_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//   // sender_addr.sin_addr.s_addr = inet_addr("192.168.0.100");

//   char *buffer = new char[1000];
//   while(true)
//   {
//     // Sleep(20);
//     recvfrom(receiver, buffer, 1000, 0, reinterpret_cast<SOCKADDR*>(&sender_addr), &length__sender_addr);
    
//     std::cout << "sin_family: " << sender_addr.sin_family << "\n";
//     std::cout << "sin_port: " << sender_addr.sin_port << "\n";
//     std::cout << "sin_addr: " << inet_ntoa(sender_addr.sin_addr) << "\n";

//     std::cout << "buffer: " << buffer << "\n";
//   }

//   closesocket(receiver);
// }

int main()
{
  WSAData wsa_data;
  WSAStartup(MAKEWORD(2, 2), &wsa_data);

  // start();

  UdpReceiver r;

  while(true)
  {
    // char *buffer = new char[1000];
    r.get_incoming_message();
    Sleep(50);
    // std::cout << "\n";
  }


  WSACleanup();
  return 0;
}