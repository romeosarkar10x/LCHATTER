#include "../../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest_Rejected.hpp"
#include "../../../../../Inc/File/Serializer.hpp"
#include "../../../../../Inc/File/Deserializer.hpp"

u_int UdpMessage_ConnectionRequest_Rejected::serialization_length() const
{
  return Serializer::serialization_length(static_cast<const UdpMessage_ConnectionRequest&>(*this));
}

void UdpMessage_ConnectionRequest_Rejected::serialize(char* const buffer, u_int& offset) const
{
  Serializer::serialize(static_cast<const UdpMessage_ConnectionRequest&>(*this), buffer, offset);
}

void UdpMessage_ConnectionRequest_Rejected::deserialize(const char* const buffer, u_int& offset)
{
  Deserializer::deserialize(static_cast<UdpMessage_ConnectionRequest&>(*this), buffer, offset);
}

void UdpMessage_ConnectionRequest_Rejected::handle()
{
  
}
