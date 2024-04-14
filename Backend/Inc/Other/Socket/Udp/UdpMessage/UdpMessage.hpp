#ifndef UDP_MESSAGE_HPP
#define UDP_MESSAGE_HPP

#include "../../Address.hpp"

/* Abstract */
class UdpMessage
{
public:

  enum class Type : char
  {
    INVALID = -1,
    NONE = 0,
    PING,

    CHAT_MESSAGE,

    CONNECTION_REQUEST,
    CONNECTION_REQUEST_ACCEPTED,
    CONNECTION_REQUEST_REJECTED,

    // GROUP
    GROUP_CHAT_MESSAGE,
    
    GROUP_CONNECTION_REQUEST,
    ACCEPT_GROUP_CONNECTION_REQUEST,
    REJECT_GROUP_CONNECTION_REQUEST
  };
  
  UdpMessage() = default;
  virtual ~UdpMessage() = default;

  virtual Type get_type() const = 0;

  virtual u_int   serialization_length() const = 0;
  virtual void    serialize(char* buffer, u_int& offset) const = 0;

  virtual void deserialize(const char* buffer, u_int& offset) = 0;

  virtual void handle() = 0;

  friend std::ostream& operator<<(std::ostream& o, const Type t);
};


#endif