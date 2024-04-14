#ifndef CHAT_HPP
#define CHAT_HPP

#include <vector>
#include <utility>

#include "ChatMessage.hpp"

class Chat
{
  std::vector<ChatMessage> _m_messages;
  
public:
  Chat() = default;

  template<typename ... _Tp>
    void emplace(_Tp&& ... args) { _m_messages.emplace_back(std::forward<_Tp>(args)...); }
  
  const std::vector<ChatMessage>& get_messages();

  u_int serialization_length() const;
  void serialize(char* buffer, u_int& offset) const;

  void deserialize(const char* buffer, u_int& offset);
};

#endif