#ifndef USER_CPP
#define USER_CPP

#include <iostream>
#include <string>
#include <cassert>

#include "String.cpp"
#include "../Crypto/Hash/MD5_Digest.cpp"
#include "../Crypto/Hash/MD5_Hash.cpp"

class User
{
  String      _m_name;
  MD5_Digest  _m_id;
  
public:
  User() = default;

  User(const char* username, const char* psw) :
  _m_name { username },
  _m_id { MD5_Hash::calculate_digest(_m_name + psw) } {}
  
  User(const User& rhs) = default;  
  User(User&& rhs) noexcept = default;

  void init(const char* username, const char* psw)
  {
    _m_name = username;
    _m_id = { MD5_Hash::calculate_digest(_m_name + psw) };
  }

  User& operator=(const User& rhs) = default;
  User& operator=(User&& rhs) = default;

  const String& get_name() const { return _m_name; }
  const String& get_id() const { return _m_id.to_string(); }

  bool operator==(const User& rhs) const { return (_m_id == rhs._m_id); }

  int serialize(char* buffer) const
  {
    int offset = 0;

    offset += _m_name.serialize(buffer);
    offset += _m_id.serialize(reinterpret_cast<char*>(buffer) + offset);

    return offset;
  }

  int serialize(char* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }

  int deserialize(const char* buffer)
  {
    int offset = 0;

    offset += _m_name.deserialize(buffer, offset);
    offset += _m_id.deserialize(buffer, offset);
    
    return offset;
  }

  int deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }
};

std::ostream& operator<<(std::ostream& o, const User& user)
{
  o << "[" << user.get_name() << "@" << user.get_id() << "]"; return o;
}

#endif