#include "../../Inc/Common/Connection.hpp"

Connection::Connection(ConnectionRequest& r) :
ConnectionRequest { r } {}

const Chat& Connection::get_chat() const { return _m_chat; }
Chat& Connection::get_chat() { return _m_chat; }

const TimePoint& Connection::get_timepoint_last_message() const { return _m_last_message; }

