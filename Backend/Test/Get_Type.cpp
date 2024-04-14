#include "../Inc/Other/Socket/Udp/UdpMessage/UdpMessage.hpp"
#include "../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest.hpp"

int main()
{
  UdpMessage* m = new UdpMessage_ConnectionRequest();
  m->~UdpMessage();
  
  std::cout << m->get_type() << std::endl;
  
  return 0;
}