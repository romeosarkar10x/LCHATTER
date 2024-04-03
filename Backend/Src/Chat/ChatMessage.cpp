#include "../../Inc/Chat/ChatMessage.hpp"

ChatMessage::ChatMessage(const User& sender, const String& message, bool is_me) :
_m_sender { sender },
_m_text { message },
_m_is_me { is_me } {}

const String&     ChatMessage::get_text() const { return _m_text; }
const TimePoint&  ChatMessage::get_time() const { return _m_timepoint; }
const User&       ChatMessage::get_sender() const { return _m_sender; }

bool              ChatMessage::is_me() const { return _m_is_me; }

bool ChatMessage::operator<(ChatMessage& rhs) { return _m_timepoint < rhs._m_timepoint; }

int ChatMessage::serialize(char* buffer) const
{
  int offset = 0;

  offset += _m_sender.serialize(buffer, offset);
  offset += _m_text.serialize(buffer, offset);
  offset += _m_timepoint.serialize(buffer, offset);

  return offset;
}

int ChatMessage::serialize(char* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }

int ChatMessage::deserialize(const char* buffer)
{
  int offset = 0;

  offset += _m_sender.deserialize(buffer, offset);
  offset += _m_text.deserialize(buffer, offset);
  offset += _m_timepoint.deserialize(buffer, offset);

  return offset;
}

int ChatMessage::deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }

std::ostream& operator<<(std::ostream& __o, const ChatMessage& chat_message)
{
  __o << chat_message.get_sender() << " ~ " << chat_message.get_text() << " %% " << chat_message.get_time(); return __o; 
}
