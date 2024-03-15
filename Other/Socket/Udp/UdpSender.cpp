#ifndef UDP_SENDER_CPP
#define UDP_SENDER_CPP

#include "Config.hpp"
#include "UdpMessage/ChatMessage.cpp"
#include "Udp_Base/UdpSender_Base.cpp"

class UdpSender final : private UdpSender_Base
{
  static const int _S_Offset = sizeof(_S_Signature);
public:
  void init()
  {
    UdpSender_Base::init();
    std::memcpy(buffer(), _S_Signature, _S_Signature_Length); 
  }

  void conn(const Addr& host);
  void conn_ack(const Addr& host);

  void ping(const Addr& host);

  void chat_msg(const Addr& receiver, const UdpChatMessage& msg)
  {
    reset_offset();
    _m_write_signature();
    _m_write_msg_type(msg.type());
    
    std::memcpy(static_cast<char*>(buffer()) + get_offset(), msg.buffer(), msg.length());
    increment_offset(msg.length());
    send(receiver);
  }

  void chat_msg(const Addr& receiver, const ChatMessage_View& msg)
  {
    reset_offset();
    _m_write_signature();
    _m_write_msg_type(msg.type());
    
    std::memcpy(static_cast<char*>(buffer()) + get_offset(), msg.buffer(), msg.length());
    increment_offset(msg.length());
    send(receiver);
  }

  void _m_write_signature()
  {
    void* p = reinterpret_cast<char*>(buffer()) + get_offset();
    memcpy(p, _S_Signature, _S_Signature_Length);
    increment_offset(_S_Signature_Length);
  }
  void _m_write_msg_type(UdpMessage::Type type)
  {
    void* p = reinterpret_cast<char*>(buffer()) + get_offset();
    *reinterpret_cast<UdpMessage*>(p) = type;
    increment_offset(static_cast<int>(sizeof(UdpMessage::Type)));
  }
};

#endif