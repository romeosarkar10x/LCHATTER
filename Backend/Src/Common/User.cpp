#include <iostream>
#include <string>
#include <cassert>

#include "../../Inc/Common/User.hpp"
#include "../../Inc/File/Serializer.hpp"

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

unsigned int User::serialization_length() const
{
  return Serializer::serialization_length(_m_name) +
    Serializer::serialization_length(_m_id);
}

void User::serialize(char* buffer, unsigned int& offset) const
{
  Serializer::serialize(_m_name, buffer, offset);
  Serializer::serialize(_m_id, buffer, offset);
}


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