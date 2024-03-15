#ifndef CHAT_MESSAGE_CPP
#define CHAT_MESSAGE_CPP

#include "../Common/String.cpp"
#include "../Common/User.cpp"
#include "../Common/TimePoint.cpp"

class ChatMessage
{
  User      _m_sender;
  String    _m_message;
  TimePoint _m_timepoint;

public:
  ChatMessage() = delete;
  
  /* need to handle all cases, where sender is [ rvalue | lvalue ], message is [ rvalue | lvalue ], ... */
  
  ChatMessage(const User& sender, const String& message, const TimePoint& timepoint = {}) :
  _m_sender { sender },
  _m_message { message },
  _m_timepoint { timepoint } {}
  

  const User& sender() const { return _m_sender; }
  const String& message() const { return _m_message; }
  const TimePoint& time() const { return _m_timepoint; }

  bool operator<(ChatMessage& rhs) { return _m_timepoint < rhs._m_timepoint; }
};

#endif