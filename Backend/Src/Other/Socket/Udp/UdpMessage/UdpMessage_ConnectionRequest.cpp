#include <algorithm>

#include "../../../../../Inc/AppBackend/AppBackend.hpp"
#include "../../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ConnectionRequest.hpp"
#include "../../../../../Inc/File/Serializer.hpp"
#include "../../../../../Inc/File/Deserializer.hpp"

UdpMessage_ConnectionRequest::UdpMessage_ConnectionRequest(const ConnectionRequest& r) :
  ConnectionRequest { r } {}

UdpMessage_ConnectionRequest::UdpMessage_ConnectionRequest(const User& user, const Address& addr) :
  ConnectionRequest { user, addr } {}

u_int UdpMessage_ConnectionRequest::serialization_length() const
{
  return Serializer::serialization_length(static_cast<const ConnectionRequest&>(*this));
}

void UdpMessage_ConnectionRequest::serialize(char* buffer, u_int& offset) const
{
  Serializer::serialize(static_cast<const ConnectionRequest&>(*this), buffer, offset);
}

void UdpMessage_ConnectionRequest::deserialize(const char* buffer, u_int& offset)
{
  // this->~UdpMessage_ConnectionRequest();
  
  Deserializer::deserialize(static_cast<ConnectionRequest&>(*this), buffer, offset);
}

void UdpMessage_ConnectionRequest::handle()
{
  auto& incoming_requests = AppBackend::get_incoming_requests();
  auto itr = std::ranges::find(incoming_requests, _m_user,
    [] (const ConnectionRequest& r) { return r.get_user(); }
  );

  if(itr != incoming_requests.end())
  {
    itr->get_timepoint() = _m_timepoint;
    return;
  }

  _m_addr.set_ip_address(AppBackend::get_receiver().get_sender_address());
  incoming_requests.push_back(std::move(*this));
}