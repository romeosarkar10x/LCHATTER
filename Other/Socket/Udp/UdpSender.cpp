#ifndef UDP_SENDER_CPP
#define UDP_SENDER_CPP

#include "UdpMessage/UdpMessage_ChatMessage.cpp"
#include "Udp_Base/UdpSender_Base.cpp"
#include "AppConfig.cpp"



class UdpSender final : private UdpSender_Base
{
  static const int _S_Offset = sizeof(_S_Signature);
public:
  void init()
  {
    UdpSender_Base::init();
    std::memcpy(buffer(), _S_Signature, _S_Signature_Length); 
  }

  void send_connect(const Address& receiver)
  {

  }


  void send_connect_accept(const Address& receiver)
  {

  }
  
  void send_connect_reject(const Address& receiver)
  {

  }

  void send_ping(const Address& receiver)
  {
    
  }

  void send_chat_message(const Address& receiver, const ChatMessage& message)
  {
    // reset_offset();

    // _m_write_signature();
    // _m_write_message_type(UdpMessage::Type::CHAT_MESSAGE);
    
    // std::memcpy(static_cast<char*>(buffer()) + get_offset(), message.buffer(), message.length());
    // increment_offset(message.length());
    // send(receiver);
  }

  void _m_write_signature()
  {
    void* p = reinterpret_cast<char*>(buffer()) + get_offset();
    memcpy(p, _S_Signature, _S_Signature_Length);
    increment_offset(_S_Signature_Length);
  }

  void _m_write_message_type(UdpMessage::Type type)
  {
    void* p = reinterpret_cast<char*>(buffer()) + get_offset();
    *reinterpret_cast<UdpMessage*>(p) = type;
    increment_offset(static_cast<int>(sizeof(UdpMessage::Type)));
  }
};

#endif