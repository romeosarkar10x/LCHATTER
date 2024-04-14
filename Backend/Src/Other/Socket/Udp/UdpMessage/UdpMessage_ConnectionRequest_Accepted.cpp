#include "../../../../../Inc/AppBackend/AppBackend.hpp"
#include "../../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest_Accepted.hpp"
#include "../../../../../Inc/File/Serializer.hpp"
#include "../../../../../Inc/File/Deserializer.hpp"

UdpMessage_ConnectionRequest_Accepted::UdpMessage_ConnectionRequest_Accepted(const UdpMessage_ConnectionRequest& r) :
  UdpMessage_ConnectionRequest { r } {}

u_int UdpMessage_ConnectionRequest_Accepted::serialization_length() const
{ return Serializer::serialization_length_nv(static_cast<const UdpMessage_ConnectionRequest&>(*this)); }

void UdpMessage_ConnectionRequest_Accepted::serialize(char* const buffer, u_int& offset) const
{ Serializer::serialize_nv(static_cast<const UdpMessage_ConnectionRequest&>(*this), buffer, offset); }

void UdpMessage_ConnectionRequest_Accepted::deserialize(const char* const buffer, u_int& offset)
{ Deserializer::deserialize_nv(static_cast<UdpMessage_ConnectionRequest&>(*this), buffer, offset); }

void UdpMessage_ConnectionRequest_Accepted::handle()
{
  auto& outgoing_requests = AppBackend::get_outgoing_requests();
  auto itr = std::ranges::find(outgoing_requests, _m_user,
    [] (const ConnectionRequest& r) { return r.get_user(); }
  );

  itr->set_state(ConnectionRequest::State::ACCEPTED);
  // itr->get_address().set_ip_address(sender_addr);
  _m_addr.set_ip_address(AppBackend::get_receiver().get_sender_address());
  // static_cast<UdpMessage_ConnectionRequest_Accepted*>(m)->get_address().set_ip_address(sender_addr);
  auto& connections = AppBackend::get_connections();

  if(std::ranges::find(connections, _m_user,
    [] (const Connection& c) -> const User& { return c.get_user(); }
  ) != connections.end())
  { return; }
  
  connections.emplace_back(*this);
}