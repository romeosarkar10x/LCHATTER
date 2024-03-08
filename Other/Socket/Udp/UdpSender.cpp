#include "../Common/Address.cpp"
#include "../Other/IncomingMessage.cpp"



class UdpSender // Singleton
{
  static Address _m_my_address;
  static bool _s_initialized;

  static Address my_address()
  {
    if(_s_initialized)
    {
      return _m_my_address;
    }
    

    
  }
  
  // void ping(const Address& host);
  // void send(const Address& receiver, const Message& message);
  

};

// bool UdpSender::_s_initialized = false;