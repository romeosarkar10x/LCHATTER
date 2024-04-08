#include "../../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage.hpp"
#include "../../../../../Inc/File/Serializer.hpp"

UdpMessage::Type::Type(Enum_Type type) : _m_t { type } {};

int UdpMessage::Type::serialization_length() const
{
  return Serializer::serialization_length(_m_t);
}

void UdpMessage::Type::serialize(char* buffer, int& offset) const
{
  Serializer::serialize(_m_t, buffer, offset);
  // *reinterpret_cast<Enum_Type*>(buffer) = _m_t;
  // return sizeof(Enum_Type);
}


int UdpMessage::Type::deserialize(const char* buffer)
{
  _m_t = *reinterpret_cast<const Enum_Type*>(buffer);
  return sizeof(Enum_Type);
}

int UdpMessage::Type::deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }

UdpMessage::Type::operator Type::Enum_Type() const { return _m_t; }

UdpMessage::UdpMessage(Type m_type) : _m_type { m_type } {}

UdpMessage::Type UdpMessage::get_type() const { return _m_type; }


int UdpMessage::serialization_length() const
{
  return Serializer::serialization_length(_m_type);
}

void UdpMessage::serialize(char* const buffer, int& offset) const
{
  Serializer::serialize(_m_type, buffer, offset);
}


int UdpMessage::deserialize(const char* buffer)
{
  return _m_type.deserialize(buffer);
}

int UdpMessage::deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }



std::ostream& operator<<(std::ostream& o, const UdpMessage::Type t)
{
  switch(t)
  {
  case UdpMessage::Type::INVALID:
    o << "INVALID";
    break;
  case UdpMessage::Type::NONE:
    o << "NONE";
    break;
  case UdpMessage::Type::PING:
    o << "PING";
    break;
  case UdpMessage::Type::CHAT_MESSAGE:
    o << "CHAT_MESSAGE";
    break;
  case UdpMessage::Type::CONNECTION_REQUEST:
    o << "CONNECTION_REQUEST";
    break;
  case UdpMessage::Type::CONNECTION_REQUEST_ACCEPTED:
    o << "CONNECTION_REQUEST_ACCEPTED";
    break;
  case UdpMessage::Type::CONNECTION_REQUEST_REJECTED:
    o << "CONNECTION_REQUEST_REJECTED";
    break;
  }

  return o;
}

