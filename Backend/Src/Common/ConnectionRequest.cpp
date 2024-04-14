#include "../../Inc/Common/ConnectionRequest.hpp"
#include "../../Inc/File/Serializer.hpp"
#include "../../Inc/File/Deserializer.hpp"

ConnectionRequest::ConnectionRequest(const User& user, const Address& addr) :
  _m_user { user },
  _m_addr { addr } {}

const User& ConnectionRequest::get_user() const { return _m_user; }

const Address&    ConnectionRequest::get_address() const { return _m_addr; }
Address&          ConnectionRequest::get_address() { return _m_addr; }

const TimePoint&    ConnectionRequest::get_timepoint() const { return _m_timepoint; }
TimePoint&          ConnectionRequest::get_timepoint() { return _m_timepoint; }

ConnectionRequest::State    ConnectionRequest::get_state() const { return _m_state; }
void                        ConnectionRequest::set_state(State state) { _m_state = state; }

bool ConnectionRequest::operator<(const ConnectionRequest& rhs) { return (_m_user.get_id() < rhs._m_user.get_id()); }

u_int ConnectionRequest::serialization_length() const
{
  return Serializer::serialization_length(_m_user) +
    Serializer::serialization_length(_m_addr) +
    Serializer::serialization_length(_m_timepoint) + 
    Serializer::serialization_length(_m_state);
}

void ConnectionRequest::serialize(char* const buffer, u_int& offset) const
{
  Serializer::serialize(_m_user, buffer, offset);
  Serializer::serialize(_m_addr, buffer, offset);
  Serializer::serialize(_m_state, buffer, offset);
  Serializer::serialize(_m_timepoint, buffer, offset);
}

void ConnectionRequest::deserialize(const char* const buffer, u_int& offset)
{
  Deserializer::deserialize(_m_user, buffer, offset);
  Deserializer::deserialize(_m_addr, buffer, offset);
  Deserializer::deserialize(_m_state, buffer, offset);
  Deserializer::deserialize(_m_timepoint, buffer, offset);
}

std::ostream& operator<<(std::ostream& o, const ConnectionRequest& r)
{
  o << r.get_user() << " " << r.get_timepoint() << " " << r.get_address(); return o;
}
