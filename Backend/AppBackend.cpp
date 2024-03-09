#include <vector>

#include "../Common/Addr.cpp"
#include "../Other/Socket/Udp/UdpSender.cpp"
#include "../Other/Socket/Udp/UdpReceiver.cpp"


class AppBackend
{
  // static bool _m_is_initialized;
  
  static UdpSender _m_sender;
  static UdpReceiver _m_receiver;

public:

  static void initialize()
  {
    
  }

  static void update()
  {

  }

  
  AppBackend() = delete;
  ~AppBackend() = delete;

};

// bool AppBackend::_m_is_initialized { false };
UdpSender AppBackend::_m_sender {};
UdpReceiver AppBackend::_m_receiver {};

