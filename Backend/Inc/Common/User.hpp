#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>
#include <cassert>

#include "String.hpp"
#include "../Crypto/Hash/MD5_Digest.hpp"
#include "../Crypto/Hash/MD5_Hash.hpp"

class User
{
  friend std::ostream& operator<<(std::ostream& o, const User& user);
  
  String      _m_name;
  MD5_Digest  _m_id;
  
public:
  User() = default;
  User(const char* username, const char* psw);
  
  User(const User& rhs) = default;  
  User(User&& rhs) noexcept = default;

  void init(const char* username, const char* psw);

  User& operator=(const User& rhs) = default;
  User& operator=(User&& rhs) = default;

  void set_name() const;
  void set_id() const;

  const String& get_name() const;
  const String& get_id() const;

  bool operator==(const User& rhs) const;

  int serialize(char* buffer) const;
  int serialize(char* buffer, int offset) const;

  int deserialize(const char* buffer);
  int deserialize(const char* buffer, int offset);
};


#endif