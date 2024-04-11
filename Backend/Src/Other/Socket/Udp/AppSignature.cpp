#include <iostream>
#include <cstring>

#include "../../../../Inc/Other/Socket/Udp/AppSignature.hpp"
#include "../../../../Inc/File/Serializer.hpp"

unsigned int AppSignature::serialization_length() const
{
  return _M_sig.get_length();
}

void AppSignature::serialize(char* const buffer, unsigned int& offset) const
{
  Serializer::serialize(_M_sig.get_buffer(), _M_sig.get_length(), buffer, offset);
}

const AppSignature& AppSignature::get_signature()
{
  return _S_sig;
}

bool AppSignature::is_match(const char* const buffer) const
{
  return (0 == std::memcmp(_M_sig.get_buffer(), buffer, _M_sig.get_length()));
  // std::cout << "_M_sig: " << _M_sig.get_buffer() << std::endl;
  // std::cout << "buffer: " << buffer << std::endl;
  // return ans;
}

const AppSignature AppSignature::_S_sig { "LC" };