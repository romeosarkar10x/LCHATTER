#ifndef CHAT_CPP
#define CHAT_CPP

#include <vector>
#include <utility>
#include "ChatMessage.cpp"

class Chat
{
  std::vector<ChatMessage> _m_messages;
  
public:
  Chat() = default;

  template<typename ... _Tp>
    void emplace(_Tp&& ... args) { _m_messages.emplace_back(std::forward<_Tp>(args)...); }
  
  const std::vector<ChatMessage>& get_messages(){ return _m_messages; }
};

#endif