#ifndef UDP_MESSAGE_HPP
#define UDP_MESSAGE_HPP

#include "../../Address.hpp"

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
    };

    Type() = default;

    Type(Enum_Type type);

    int serialize(char* buffer) const;
    int serialize(char* buffer, int offset) const;

    int deserialize(const char* buffer);
    int deserialize(const char* buffer, int offset);

    operator Type::Enum_Type() const;

  private:
    friend class UdpMessage;
    
    Enum_Type   _m_t;
  };
  
  UdpMessage() = default;

  UdpMessage(Type m_type);

  Type get_type() const;

  
  int serialize(char* buffer) const;
  int serialize(char* buffer, int offset) const;

  int deserialize(const char* buffer);
  int deserialize(const char* buffer, int offset);

private:
  Type _m_type { Type::NONE };

  friend std::ostream& operator<<(std::ostream& o, const Type t);
};


#endif