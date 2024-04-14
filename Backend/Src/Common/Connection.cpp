#include "../../Inc/Common/Connection.hpp"
#include "../../Inc/File/Serializer.hpp"
#include "../../Inc/File/Deserializer.hpp"

Connection::Connection(ConnectionRequest& r) :
  ConnectionRequest { r },
  _m_timepoint_last_message { 0 } {}

const Chat& Connection::get_chat() const { return _m_chat; }
Chat& Connection::get_chat() { return _m_chat; }

const TimePoint& Connection::get_timepoint_last_message() const { return _m_timepoint_last_message; }

u_int Connection::serialization_length() const
{
  return Serializer::serialization_length(static_cast<const ConnectionRequest&>(*this)) +
    Serializer::serialization_length(_m_chat) +
    Serializer::serialization_length(_m_timepoint_last_message);
}

void Connection::serialize(char* const buffer, u_int& offset) const
{
  Serializer::serialize(static_cast<const ConnectionRequest&>(*this), buffer, offset);
  Serializer::serialize(_m_chat, buffer, offset);
  Serializer::serialize(_m_timepoint_last_message, buffer, offset);
}

void Connection::deserialize(const char* const buffer, u_int& offset)
{
  Deserializer::deserialize(static_cast<ConnectionRequest&>(*this), buffer, offset);
  Deserializer::deserialize(_m_chat, buffer, offset);
  Deserializer::deserialize(_m_timepoint_last_message, buffer, offset);
}