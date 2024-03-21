#ifndef CONNECTION_REQUEST_CPP
#define CONNECTION_REQUEST_CPP

#include "User.cpp"
#include "Address.cpp"
#include "TimePoint.cpp"

class ConnectionRequest
{

public:
  enum State { AWAITING_RESPONSE, ACCEPTED, REJECTED };

  ConnectionRequest() = default;

  ConnectionRequest(const User& user, const Address& addr) :
  _m_user { user },
  _m_addr { addr } {}

  // ConnectionRequest(const ConnectionRequest& rhs) = default;
  // ConnectionRequest(ConnectionRequest&& rhs) = default;


  const User&       get_user() const { return _m_user; }
  const Address&    get_address() const { return _m_addr; }
  Address&          get_address() { return _m_addr; }
  const TimePoint&  get_timepoint_last_seen() const { return _m_last_seen; }

  TimePoint&        get_timepoint_last_seen() { return _m_last_seen; }

  State get_state() { return _m_state; }
  void  set_state(State state) { _m_state = state; }
  

  bool operator<(const ConnectionRequest& rhs) { return _m_user.get_id().operator<(rhs._m_user.get_id()); }

  int serialize(char* buffer) const
  {
    int offset = 0;

    offset += _m_user.serialize(buffer, offset);
    offset += _m_addr.serialize(buffer, offset);
    offset += _m_last_seen.serialize(buffer, offset);

    return offset;
  }

  int serialize(char* buffer, int offset) const { return serialize(buffer + offset); }

  int deserialize(const char* buffer)
  {
    int offset = 0;

    offset += _m_user.deserialize(buffer, offset);
    offset += _m_addr.deserialize(buffer, offset);
    offset += _m_last_seen.deserialize(buffer, offset);

    return offset;
  }

  int deserialize(const char* buffer, int offset) { return deserialize(buffer + offset); }

private:
  User      _m_user {};
  Address   _m_addr {};
  State     _m_state { AWAITING_RESPONSE };
  TimePoint _m_last_seen {};
};

std::ostream& operator<<(std::ostream& o, const ConnectionRequest& r)
{
  o << r.get_user() << " " << r.get_address() << " " << r.get_timepoint_last_seen(); return o;
}

#endif
