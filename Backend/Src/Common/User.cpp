#include <iostream>
#include <string>
#include <cassert>

#include "../../Inc/Common/User.hpp"
#include "../../Inc/File/Serializer.hpp"
#include "../../Inc/File/Deserializer.hpp"

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

u_int User::serialization_length() const
{
  return Serializer::serialization_length(_m_name) +
    Serializer::serialization_length(_m_id);
}

void User::serialize(char* const buffer, u_int& offset) const
{
  Serializer::serialize(_m_name, buffer, offset);
  Serializer::serialize(_m_id, buffer, offset);
}


void User::deserialize(const char* const buffer, u_int& offset)
{
  Deserializer::deserialize(_m_name, buffer, offset);
  Deserializer::deserialize(_m_id, buffer, offset);
}


std::ostream& operator<<(std::ostream& o, const User& user)
{
  o << "[" << user.get_name() << "@" << user.get_id() << "]"; return o;
}