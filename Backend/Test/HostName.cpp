// #include <iostream>
// #include <cassert>
// #include <winsock2.h>

// int main()
// {
//   char s[100];
  
//   WSAData d;
//   WSAStartup(MAKEWORD(2, 2), &d);

//   int ret = gethostname(s, 100);
//   std::cout << "ret: " << ret << "\n";
//   std::cout << WSAGetLastError() << "\n";

//   std::cout << s << "\n";

//   hostent* host = gethostbyname(s);
//   std::cout << "host: " << host << "\n";


//   // std::cout << "h_length: " << host->h_length << "\n";
  
//   // for(int i = 0; host->h_addr_list[i] != nullptr ; i++)
//   // {
//   //   std::cout << inet_ntoa(reinterpret_cast<SOCKADDR_IN*>(*(host->h_addr_list + i))->sin_addr) << "\n";
//   // }
//   // std::cout << inet_ntoa(reinterpret_cast<SOCKADDR_IN*>(host->h_addr)->sin_addr) << "\n";

//   for (int i = 0; host->h_addr_list[i] != nullptr; i++) {
//     struct in_addr addr;
//     memcpy(&addr, host->h_addr_list[i], sizeof(struct in_addr));
//     char* ip = inet_ntoa(addr);

//     // Convert the IP address string to an integer for easy comparison
//     unsigned long ip_addr = inet_addr(ip);

//     // Check if the IP address is in the private range
//     if ((ip_addr >= inet_addr("10.0.0.0") && ip_addr <= inet_addr("10.255.255.255")) ||
//         (ip_addr >= inet_addr("172.16.0.0") && ip_addr <= inet_addr("172.31.255.255")) ||
//         (ip_addr >= inet_addr("192.168.0.0") && ip_addr <= inet_addr("192.168.255.255"))) {
//         std::cout << "Local IP Address: " << ip << std::endl;
//     }
// }



//   WSACleanup();

//   return 0;
// }

#include <iostream>
#include <WS2tcpip.h>
#include <iphlpapi.h>

// #pragma comment(lib, "iphlpapi.lib")
// #pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        std::cerr << "Failed to initialize Winsock.\n";
        return 1;
    }

    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = nullptr;
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    pAdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof(IP_ADAPTER_INFO));
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) malloc(ulOutBufLen);
    }

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR) {
        pAdapter = pAdapterInfo;
        while (pAdapter) {
            if (pAdapter->Type == MIB_IF_TYPE_ETHERNET) {
                std::cout << "Ethernet IP Address: " << pAdapter->IpAddressList.IpAddress.String << std::endl;
            }
            pAdapter = pAdapter->Next;
        }
    }

    if (pAdapterInfo) {
        free(pAdapterInfo);
    }

    WSACleanup();
    return 0;
}
