#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include "../Common/String.hpp"
#include "../Common/User.hpp"
#include "../Common/TimePoint.hpp" /// <windows.h>

class ChatMessage
{

public:
  ChatMessage() = default;

  ChatMessage(const ChatMessage&) = default;
  
  /* need to handle all cases, where sender is [ rvalue | lvalue ], message is [ rvalue | lvalue ], ... */
  
  ChatMessage(const User& sender, const String& message, bool is_me = false);

  const String&     get_text()    const;
  const TimePoint&  get_time()    const;
  const User&       get_sender()  const;

  bool is_me() const;

  bool operator<(ChatMessage& rhs);
  
  u_int serialization_length() const;
  void serialize(char* buffer, u_int& offset) const;

  void deserialize(const char* buffer, u_int& offset);
  
protected:
  User      _m_sender;
  String    _m_text;
  TimePoint _m_timepoint { 0 };

  bool      _m_is_me { false };

  friend std::ostream& operator<<(std::ostream& o, const ChatMessage& chat_message);
};


#endif