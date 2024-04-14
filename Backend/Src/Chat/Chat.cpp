#include "../../Inc/Chat/Chat.hpp"
#include "../../Inc/File/Serializer.hpp"
#include "../../Inc/File/Deserializer.hpp"

const std::vector<ChatMessage>& Chat::get_messages(){ return _m_messages; }

u_int Chat::serialization_length() const
{
  return Serializer::serialization_length(_m_messages);
}

void Chat::serialize(char* const buffer, u_int& offset) const
{
  Serializer::serialize(_m_messages, buffer, offset);
}

void Chat::deserialize(const char* const buffer, u_int& offset)
{
  Deserializer::deserialize(_m_messages, buffer, offset);
}