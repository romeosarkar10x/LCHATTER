#ifndef USER_CPP
#define USER_CPP

#include <iostream>
#include <string>
#include <cassert>

#include "String.cpp"
#include "Hash/MD5_Digest.cpp"
#include "Hash/MD5_Hash.cpp"

class User
{
  bool _m_is_initialized { false };
  String _m_name;
  MD5_Digest _m_id;
  
public:
  User() = default;
  User(const char* username, const char* psw) :
  _m_is_initialized { true },
  _m_name { username },
  _m_id { MD5_Hash::calculate_digest(_m_name + psw) } {}
  
  User(const User& rhs) = default;  
  User(User&& rhs) noexcept = default;
  // User(User&& rhs) noexcept :
  // _m_is_initialized { rhs._m_is_initialized },
  // _m_name { std::move(_m_name) },
  // _m_id { std::move(_m_id) } {}

  void init(const char* username, const char* psw)
  {
    assert(!_m_is_initialized);

    _m_is_initialized = true;
    _m_name = username;
    _m_id = { MD5_Hash::calculate_digest(_m_name + psw) };
  }

  const String& get_name() const { assert(_m_is_initialized); return _m_name; }
  const String& get_id() const { assert(_m_is_initialized); return _m_id.to_string(); }

  int serialize(void* buffer) const
  {
    assert(_m_is_initialized);
    
    int offset = 0;
    offset += _m_name.serialize(buffer);
    offset += _m_id.serialize(reinterpret_cast<char*>(buffer) + offset);
    return offset;
  }

  int serialize(void* buffer, int offset) const { return serialize(reinterpret_cast<char*>(buffer) + offset); }

  int deserialize(const void* buffer)
  {
    int offset = 0;

    offset += _m_name.deserialize(buffer, offset);
    offset += _m_id.deserialize(buffer, offset);
    
    _m_is_initialized = true;
    return offset;
  }

  int deserialize(const void* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }
};

std::ostream& operator<<(std::ostream& __o, const User& user)
{
  __o << "[" << user.get_name() << "@" << user.get_id() << "]"; return __o;
}

#endif