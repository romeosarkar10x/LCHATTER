#ifndef CONNECTION_REQUEST_HPP
#define CONNECTION_REQUEST_HPP

#include "User.hpp"
#include "../Other/Socket/Address.hpp" /// <winsock2.h>
#include "TimePoint.hpp" /// <windows.h>

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

    Enum_State  get_state() const;
    void        set_state(const Enum_State state);
    
  private:
    Enum_State _m_state { AWAITING_RESPONSE };
  };

  ConnectionRequest() = default;

  ConnectionRequest(const User& user, const Address& addr);

  // ConnectionRequest(const ConnectionRequest& rhs) = default;
  // ConnectionRequest(ConnectionRequest&& rhs) = default;


  const User&       get_user()        const;

  const Address&    get_address()     const;
  Address&          get_address();

  const TimePoint&  get_timepoint()   const;
  TimePoint&        get_timepoint();

  State::Enum_State get_state()       const;
  void              set_state(State::Enum_State state);

  bool operator<(const ConnectionRequest& rhs);

  int serialize(char* buffer)               const;
  int serialize(char* buffer, int offset)   const;

  int deserialize(const char* buffer);
  int deserialize(const char* buffer, int offset);

private:
  User      _m_user       {};
  Address   _m_addr       {};
  State     _m_state      {};
  TimePoint _m_timepoint  {};

  friend std::ostream& operator<<(std::ostream& o, const ConnectionRequest& r);
};


#endif
