#ifndef APP_SIGNATURE_HPP
#define APP_SIGNATURE_HPP

#include <iostream>
#include <cassert>

#include "../../../../Inc/Common/Fwd.hpp"

class AppSignature
{
  static const u_int _S_signature_length = 2U;
  static const AppSignature _S_signature;

  char _m_signature[_S_signature_length];

public:
  AppSignature() = default;

  AppSignature(const char* sig);

  u_int     serialization_length() const;
  void      serialize(char* buffer, u_int& offset) const;

  void  deserialize(const char* buffer, u_int& offset);

  static const AppSignature& get_signature();
  bool operator==(const AppSignature& rhs);
};

#endif