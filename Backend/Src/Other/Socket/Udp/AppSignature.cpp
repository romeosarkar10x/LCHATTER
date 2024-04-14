#include <iostream>
#include <cstring>

#include "../../../../Inc/Other/Socket/Udp/AppSignature.hpp"
#include "../../../../Inc/File/Serializer.hpp"
#include "../../../../Inc/File/Deserializer.hpp"

AppSignature::AppSignature(const char* const sig)
{
  u_int sig_length = static_cast<u_int>(std::strlen(sig));

  assert(sig_length == _S_signature_length);
  std::memcpy(_m_signature, sig, _S_signature_length);
}

u_int AppSignature::serialization_length() const
{
  return Serializer::serialization_length(_m_signature);
}

void AppSignature::serialize(char* const buffer, u_int& offset) const
{
  Serializer::serialize(_m_signature, buffer, offset);
}

void AppSignature::deserialize(const char* const buffer, u_int& offset)
{
  Deserializer::deserialize(_m_signature, buffer, offset);
}

const AppSignature& AppSignature::get_signature()
{
  return _S_signature;
}

bool AppSignature::operator==(const AppSignature& rhs)
{
  return (std::memcmp(_m_signature, rhs._m_signature, _S_signature_length) == 0);
}

const AppSignature AppSignature::_S_signature { "LC" };