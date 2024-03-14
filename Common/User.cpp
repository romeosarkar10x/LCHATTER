#ifndef USER_CPP
#define USER_CPP

#include <iostream>
#include <string>
#include <cassert>

// #include "Md5_Hash.cpp"
#include "String.cpp"

class User
{
  bool _m_is_initialized { false };
  String _m_name;
  String _m_id;
  
public:
  // User() : _m_name { nullptr }, _m_id { nullptr } {}
  User() = default;
  User(const char* username, const char* psw) : _m_is_initialized { true }
  {
    std::strlen(username);
  }

  void init(const char* username, const char* psw)
  {
    assert(!_m_is_initialized);

    _m_is_initialized = true;
    _m_name = std::string(username);
    // _m_id = 
  }

  const std::string& name() const { assert(_m_is_initialized); return _m_name; }
  const std::string& id() const { assert(_m_is_initialized); return _m_id; } 

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