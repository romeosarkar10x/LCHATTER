#include "UdpMessage.hpp"

class UdpMessage_None : public UdpMessage
{

public:
  UdpMessage_None() = default;

  UdpMessage::Type get_type() const { return UdpMessage::Type::NONE; }
  
  u_int   serialization_length() const override { return 0U; };
  void    serialize(char*, u_int&) const override {}

  void deserialize(const char*, u_int&) override {}

  void handle() override {}
};