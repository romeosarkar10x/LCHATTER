#ifndef CHAT_MESSAGE_CPP
#define CHAT_MESSAGE_CPP

#include "../Common/String.cpp"
#include "../Common/User.cpp"
#include "../Common/TimePoint.cpp"

class ChatMessage
{
  User      _m_sender;
  String    _m_text;
  TimePoint _m_timepoint {};

public:
  ChatMessage() = delete;
  
  /* need to handle all cases, where sender is [ rvalue | lvalue ], message is [ rvalue | lvalue ], ... */
  
  ChatMessage(const User& sender, const String& message) :
  _m_sender { sender },
  _m_text { message } {}

  const User& get_sender() const { return _m_sender; }
  const String& get_text() const { return _m_text; }
  const TimePoint& get_time() const { return _m_timepoint; }

  bool operator<(ChatMessage& rhs) { return _m_timepoint < rhs._m_timepoint; }
  
  int serialize(void* buffer)
  {
    int offset = 0;

    offset += _m_sender.serialize(buffer, offset);
    offset += _m_text.serialize(buffer, offset);
    offset += _m_timepoint.serialize(buffer, offset);

    return offset;
  }

  int serialize(void* buffer, int offset) { return serialize(reinterpret_cast<char*>(buffer) + offset); }

  int deserialize(const void* buffer)
  {
    int offset = 0;

    offset += _m_sender.deserialize(buffer, offset);
    offset += _m_text.deserialize(buffer, offset);
    offset += _m_timepoint.deserialize(buffer, offset);

    return offset;
  }

  int deserialize(const void* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }
};

std::ostream& operator<<(std::ostream& __o, const ChatMessage& chat_message)
{
  __o << chat_message.get_sender() << " ~ " << chat_message.get_text() << " %% " << chat_message.get_time(); return __o; 
}

#endif