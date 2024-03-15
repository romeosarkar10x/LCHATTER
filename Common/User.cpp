#ifndef USER_CPP
#define USER_CPP

#include <iostream>
#include <string>
#include <cassert>

#include "String.cpp"
#include "Hash/Md5_Digest.cpp"
#include "Hash/Md5_Hash.cpp"
#include "../Log/Logger.cpp"

class User
{
  bool _m_is_initialized { false };
  String _m_name;
  Md5_Digest _m_id;
  
public:
  User() = default;

  User(const char* username, const char* psw) : _m_is_initialized { true }, _m_name { username }, _m_id { Md5_Hash::calculate_digest(_m_name + psw) } {}

  void init(const char* username, const char* psw)
  {
    assert(!_m_is_initialized);

    _m_is_initialized = true;
    _m_name = username;
    _m_id = { Md5_Hash::calculate_digest(_m_name + psw) };
    _m_name = username;

    logger << "_m_name: " << _m_name << "\n";
    logger << "_m_id: " << _m_id << "\n";
  }

  const String& name() const { assert(_m_is_initialized); return _m_name; }
  const String& id() const { assert(_m_is_initialized); return _m_id.to_string(); }

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

    return offset;
  }
};

#endif