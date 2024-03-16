#include <memory>
#include "Udp_Base/UdpReceiver_Base.cpp"
#include "UdpMessage/UdpMessage.cpp"
#include "AppConfig.cpp"


class UdpReceiver final : private UdpReceiver_Base
{
  
public:
  void init()
  {
    UdpReceiver_Base::init();
    std::cout << "UdpReceiver Port: " << UdpReceiver::port() << "\n";
  }
  // std::unique_ptr<UdpMessage> receive()
  // {
  //   UdpReceiver_Base::receive();

  // }
  UdpMessage* receive()
  {
    UdpReceiver_Base::receive();

    // if()

  }

};