#ifndef CONNECTION_REQUEST_CPP
#define CONNECTION_REQUEST_CPP

#include "User.cpp"
#include "../Other/Socket/Address.cpp"
#include "TimePoint.cpp"

class ConnectionRequest
{

public:
  class State
  {
  
  public:
    enum Enum_State
    {
      AWAITING_RESPONSE,
      ACCEPTED,
      REJECTED,
    };

    Enum_State  get_state() { return _m_state; }
    void        set_state(Enum_State state) { _m_state = state; }
    
  private:
    Enum_State _m_state { AWAITING_RESPONSE };
  };

  ConnectionRequest() = default;

  ConnectionRequest(const User& user, const Address& addr) :
  _m_user { user },
  _m_addr { addr } {}

  // ConnectionRequest(const ConnectionRequest& rhs) = default;
  // ConnectionRequest(ConnectionRequest&& rhs) = default;


  const User&       get_user() const { return _m_user; }

  const Address&    get_address() const { return _m_addr; }
  Address&          get_address() { return _m_addr; }

  const TimePoint&  get_timepoint() const { return _m_timepoint; }
  TimePoint&        get_timepoint() { return _m_timepoint; }

  State::Enum_State get_state() { return _m_state.get_state(); }
  void              set_state(State::Enum_State state) { _m_state.set_state(state); }

  bool operator<(const ConnectionRequest& rhs) { return _m_user.get_id().operator<(rhs._m_user.get_id()); }

  int serialize(char* buffer) const
  {
    int offset = 0;

    offset += _m_user.serialize(buffer, offset);
    offset += _m_addr.serialize(buffer, offset);
    offset += _m_timepoint.serialize(buffer, offset);

    return offset;
  }

  int serialize(char* buffer, int offset) const { return serialize(buffer + offset); }

  int deserialize(const char* buffer)
  {
    int offset = 0;

    offset += _m_user.deserialize(buffer, offset);
    offset += _m_addr.deserialize(buffer, offset);
    offset += _m_timepoint.deserialize(buffer, offset);

    return offset;
  }

  int deserialize(const char* buffer, int offset) { return deserialize(buffer + offset); }

private:
  User      _m_user {};
  Address   _m_addr {};
  State     _m_state {};
  TimePoint _m_timepoint {};
};

std::ostream& operator<<(std::ostream& o, const ConnectionRequest& r)
{
  o << r.get_user() << " " << r.get_timepoint() << " " << r.get_address(); return o;
}

#endif
