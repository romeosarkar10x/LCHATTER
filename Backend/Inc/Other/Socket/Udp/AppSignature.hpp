#ifndef APP_SIGNATURE_HPP
#define APP_SIGNATURE_HPP

#include <iostream>
#include "../../../../Inc/Common/String.hpp"

class AppSignature
{
  static const AppSignature _S_sig;

  const String _M_sig;

public:

  AppSignature(const char* sig) :
    _M_sig { sig } {}

  int serialization_length() const;
  void serialize(char* const buffer, int& offset) const;

  static const AppSignature& get_signature();
  bool is_match(const char* buffer) const;
};



#endif