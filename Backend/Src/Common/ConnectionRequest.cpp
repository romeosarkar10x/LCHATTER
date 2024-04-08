#include "../../Inc/Common/ConnectionRequest.hpp"
#include "../../Inc/File/Serializer.hpp"

ConnectionRequest::State::Enum_State ConnectionRequest::State::get_state() const { return _m_state; }
void ConnectionRequest::State::set_state(Enum_State state) { _m_state = state; }
  

ConnectionRequest::ConnectionRequest(const User& user, const Address& addr) :
  _m_user { user },
  _m_addr { addr } {}

const User& ConnectionRequest::get_user() const { return _m_user; }

const Address& ConnectionRequest::get_address() const { return _m_addr; }
Address& ConnectionRequest::get_address() { return _m_addr; }

const TimePoint& ConnectionRequest::get_timepoint() const { return _m_timepoint; }
TimePoint& ConnectionRequest::get_timepoint() { return _m_timepoint; }

ConnectionRequest::State::Enum_State ConnectionRequest::get_state() const { return _m_state.get_state(); }
void ConnectionRequest::set_state(State::Enum_State state) { _m_state.set_state(state); }

bool ConnectionRequest::operator<(const ConnectionRequest& rhs) { return _m_user.get_id().operator<(rhs._m_user.get_id()); }

int ConnectionRequest::serialization_length() const
{
  return Serializer::serialization_length(_m_user) +
    Serializer::serialization_length(_m_addr) +
    Serializer::serialization_length(_m_timepoint);
}

void ConnectionRequest::serialize(char* buffer, int& offset) const
{
  Serializer::serialize(_m_user, buffer, offset);
  Serializer::serialize(_m_addr, buffer, offset);
  Serializer::serialize(_m_timepoint, buffer, offset);
}

int ConnectionRequest::deserialize(const char* buffer)
{
  int offset = 0;

  offset += _m_user.deserialize(buffer, offset);
  offset += _m_addr.deserialize(buffer, offset);
  offset += _m_timepoint.deserialize(buffer, offset);

  return offset;
}

int ConnectionRequest::deserialize(const char* buffer, int offset) { return deserialize(buffer + offset); }

std::ostream& operator<<(std::ostream& o, const ConnectionRequest& r)
{
  o << r.get_user() << " " << r.get_timepoint() << " " << r.get_address(); return o;
}
