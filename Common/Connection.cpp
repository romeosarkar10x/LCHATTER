#include "ConnectionRequest.cpp" /// <winsock2.h>
#include "../Chat/Chat.cpp" /// <windows.h>

class Connection : public ConnectionRequest
{
  Chat      _m_chat {};
  TimePoint _m_last_message {};

public:
  
  Connection(ConnectionRequest& r) :
  ConnectionRequest { r } {}

  const Chat&       get_chat() const { return _m_chat; }
  Chat&             get_chat() { return _m_chat; }
  
  const TimePoint&  get_timepoint_last_message() const { return _m_last_message; }
};

