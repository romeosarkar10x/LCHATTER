#include "../../Inc/Chat/ChatMessage.hpp"
#include "../../Inc/File/Serializer.hpp"
#include "../../Inc/File/Deserializer.hpp"

ChatMessage::ChatMessage(const User& sender, const String& message, bool is_me) :
  _m_sender { sender },
  _m_text   { message },
  _m_is_me  { is_me } {}

const String&     ChatMessage::get_text() const { return _m_text; }
const TimePoint&  ChatMessage::get_time() const { return _m_timepoint; }
const User&       ChatMessage::get_sender() const { return _m_sender; }

bool              ChatMessage::is_me() const { return _m_is_me; }

bool ChatMessage::operator<(ChatMessage& rhs) { return _m_timepoint < rhs._m_timepoint; }

u_int ChatMessage::serialization_length() const
{
  return Serializer::serialization_length(_m_sender) +
    Serializer::serialization_length(_m_text) +
    Serializer::serialization_length(_m_timepoint);
}

void ChatMessage::serialize(char* const buffer, u_int& offset) const
{
  Serializer::serialize(_m_sender, buffer, offset);
  Serializer::serialize(_m_text, buffer, offset);
  Serializer::serialize(_m_timepoint, buffer, offset);
  Serializer::serialize(_m_is_me, buffer, offset);
}

void ChatMessage::deserialize(const char* const buffer, u_int& offset)
{
  Deserializer::deserialize(_m_sender, buffer, offset);
  Deserializer::deserialize(_m_text, buffer, offset);
  Deserializer::deserialize(_m_timepoint, buffer, offset);
  Deserializer::deserialize(_m_is_me, buffer, offset);
}

std::ostream& operator<<(std::ostream& __o, const ChatMessage& chat_message)
{
  __o << chat_message.get_sender() << " ~ " << chat_message.get_text() << " %% " << chat_message.get_time(); return __o; 
}
