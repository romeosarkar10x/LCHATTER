#ifndef CONNECTION_REQUEST_HPP
#define CONNECTION_REQUEST_HPP

#include "../Other/Socket/Address.hpp" /// <winsock2.h>
#include "User.hpp" /// <windows.h>
#include "TimePoint.hpp" /// <windows.h>

class ConnectionRequest
{

public:
  enum class State
  {
    AWAITING_RESPONSE,
    ACCEPTED,
    REJECTED,
  };
  // class State
  // {
  
  // public:
    
  //   State() = default;
  //   ~State() = default;

  //   Enum_State  get_state() const;
  //   void        set_state(const Enum_State state);

    
    
  // private:
  //   Enum_State _m_state { AWAITING_RESPONSE };
  // };

  ConnectionRequest() = default;

  ConnectionRequest(const User& user, const Address& addr);

  const User&       get_user()        const;

  const Address&    get_address()     const;
  Address&          get_address();

  const TimePoint&  get_timepoint()   const;
  TimePoint&        get_timepoint();

  State   get_state()       const;
  void    set_state(State state);

  bool operator<(const ConnectionRequest& rhs);

  u_int   serialization_length() const;
  void    serialize(char* buffer, u_int& offset) const;

  void deserialize(const char* buffer, u_int& offset);

protected:
  User      _m_user       {};
  Address   _m_addr       {};
  State     _m_state      { State::AWAITING_RESPONSE };
  TimePoint _m_timepoint  { 0 };

  friend std::ostream& operator<<(std::ostream& o, const ConnectionRequest& r);
};


#endif
