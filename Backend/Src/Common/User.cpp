#include <iostream>
#include <string>
#include <cassert>

#include "../../Inc/Common/User.hpp"

User::User(const char* username, const char* psw) :
  _m_name { username },
  _m_id { MD5_Hash::calculate_digest(_m_name + psw) } {}


void User::init(const char* username, const char* psw)
{
  _m_name = username;
  _m_id = { MD5_Hash::calculate_digest(_m_name + psw) };
}

const String& User::get_name() const { return _m_name; }
const String& User::get_id() const { return _m_id.to_string(); }

bool User::operator==(const User& rhs) const { return (_m_id == rhs._m_id); }

int User::serialize(char* buffer) const
{
  int offset = 0;

  offset += _m_name.serialize(buffer);
  offset += _m_id.serialize(reinterpret_cast<char*>(buffer) + offset);

  return offset;
}

int User::serialize(char* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }

int User::deserialize(const char* buffer)
{
  int offset = 0;

  offset += _m_name.deserialize(buffer, offset);
  offset += _m_id.deserialize(buffer, offset);
  
  return offset;
}

int User::deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }

std::ostream& operator<<(std::ostream& o, const User& user)
{
  o << "[" << user.get_name() << "@" << user.get_id() << "]"; return o;
}