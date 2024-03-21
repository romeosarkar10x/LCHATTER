#include <iostream>
#include <WS2tcpip.h>
#include <iphlpapi.h>


int main()
{
  WSADATA d;
  WSAStartup(MAKEWORD(2, 2), &d);

  ULONG buffer_length = 50000;
  PIP_ADAPTER_ADDRESSES buffer = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(malloc(buffer_length));
  
  ULONG ret = GetAdaptersAddresses(AF_INET, 0, nullptr, reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer), &buffer_length);
  if(ret == ERROR_BUFFER_OVERFLOW) { std::cout << "ERROR_BUFFER_OVERFLOW" << std::endl; }

  PIP_ADAPTER_ADDRESSES node = buffer;

  while(node != nullptr)
  {
    std::cout << "AdapterName: " << node->AdapterName << "\n";
    std::wcout << "FriendlyName: " << node->FriendlyName << "\n";
    std::wcout << "Description: " << node->Description << "\n";
    std::wcout << "DnsSuffix: " << node->DnsSuffix << "\n";
    
    
    PIP_ADAPTER_UNICAST_ADDRESS node2 = node->FirstUnicastAddress;
    while(node2 != nullptr)
    {
      std::cout << "Address: " << inet_ntoa(reinterpret_cast<SOCKADDR_IN*>(node2->Address.lpSockaddr)->sin_addr) << "\n";
      node2 = node2->Next;
    }

    std::cout << "\n";
    node = node->Next;
  }

  WSACleanup();
  return 0;
}
