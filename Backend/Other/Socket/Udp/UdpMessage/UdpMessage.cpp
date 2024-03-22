#ifndef UDP_MESSAGE_CPP
#define UDP_MESSAGE_CPP

#include "../../Address.cpp"

class UdpMessage
{
public:

  class Type
  {

  public:
    enum Enum_Type : char
    {
      INVALID = -1,
      NONE = 0,
      PING,
      CHAT_MESSAGE,
      CONNECTION_REQUEST,
      CONNECTION_REQUEST_ACCEPTED,
      CONNECTION_REQUEST_REJECTED
    } _m_t;

    Type() = default;

    Type(Enum_Type type) : _m_t { type } {};

    int serialize(char* buffer) const
    {
      *reinterpret_cast<Enum_Type*>(buffer) = _m_t;
      return sizeof(Enum_Type);
    }

    int serialize(char* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }

    int deserialize(const char* buffer)
    {
      _m_t = *reinterpret_cast<const Enum_Type*>(buffer);
      return sizeof(Enum_Type);
    }

    int deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }
  };
  
  UdpMessage() = default;

  UdpMessage(Type m_type) : _m_type { m_type } {}

  Type get_type() const { return _m_type; }
  
  int serialize(char* buffer) const
  {
    return _m_type.serialize(buffer);
  }

  int serialize(char* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }

  int deserialize(const char* buffer)
  {
    return _m_type.deserialize(buffer);
  }

  int deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }

private:
  Type _m_type { Type::NONE };
};

#endif