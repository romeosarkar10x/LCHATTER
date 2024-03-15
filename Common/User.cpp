#ifndef USER_CPP
#define USER_CPP

#include <iostream>
#include <string>
#include <cassert>

#include "String.cpp"
#include "Hash/Md5_Digest.cpp"
#include "Hash/Md5_Hash.cpp"

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
    _m_id = { _m_name + psw };
    _m_name = username;
  }

  const String& name() const { assert(_m_is_initialized); return _m_name; }
  const String& id() const { assert(_m_is_initialized); return _m_id.to_string(); } 

  // static User me()
  // {
  //   if(_s_initialized)
  //   {
  //     return _s_me;
  //   }

  //   throw "error: user not initialized";
  // }
  // static void initialize(const std::string& username, const std::string& password)
  // {
  //   // _s_me.initialize
  // }
  // static void initialize_anonymous()
  // {
    
  // }

};

// bool User::_s_initialized { false };


#endif