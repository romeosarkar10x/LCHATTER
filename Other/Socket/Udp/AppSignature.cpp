#ifndef APP_SIGNATURE_CPP
#define APP_SIGNATURE_CPP

#include <cstring>

class AppSignature
{
  static const char _S_Signature[];
  static const int _S_Signature_Length;

public:

  static int serialize(char* buffer)
  {
    std::memcpy(buffer, _S_Signature, _S_Signature_Length);
    return _S_Signature_Length;
  }

  static int serialize(char* buffer, int offset) { return serialize(reinterpret_cast<char*>(buffer) + offset); }

  static int deserialize(void*) { return _S_Signature_Length; }

  static int deserialize(void*, int) { return _S_Signature_Length; }
  
  static bool is_valid(const char* buffer)
  {
    return (0 == std::memcmp(_S_Signature, buffer, _S_Signature_Length));
  }
};

const char AppSignature::_S_Signature[] = "LC";
const int AppSignature::_S_Signature_Length = static_cast<int>(std::strlen(_S_Signature));

#endif