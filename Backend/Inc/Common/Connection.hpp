#include "ConnectionRequest.hpp" /// <winsock2.h>
#include "../Chat/Chat.hpp" /// <windows.h>

class Connection : public ConnectionRequest
{
  Chat      _m_chat {};
  TimePoint _m_last_message {};

public:
  Connection() = default;
  
  Connection(ConnectionRequest& r);

  const Chat&       get_chat() const;
  Chat&             get_chat();
  
  const TimePoint&  get_timepoint_last_message() const;
};

