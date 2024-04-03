#include <cstring>

#include "../../../../Inc/Other/Socket/Udp/AppSignature.hpp"



int AppSignature::serialize(char* buffer)
{
  std::memcpy(buffer, _S_Signature, _S_Signature_Length);
  return _S_Signature_Length;
}

int AppSignature::serialize(char* buffer, int offset) { return serialize(reinterpret_cast<char*>(buffer) + offset); }

int AppSignature::deserialize(void*) { return _S_Signature_Length; }

int AppSignature::deserialize(void*, int) { return _S_Signature_Length; }

bool AppSignature::is_valid(const char* buffer)
{
  return (0 == std::memcmp(_S_Signature, buffer, _S_Signature_Length));
}


const char AppSignature::_S_Signature[] = "LC";
const int AppSignature::_S_Signature_Length = static_cast<int>(std::strlen(_S_Signature));