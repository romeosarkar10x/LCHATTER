#ifndef APP_SIGNATURE_HPP
#define APP_SIGNATURE_HPP

#include <cstring>

class AppSignature
{
  static const char _S_Signature[];
  static const int _S_Signature_Length;

public:

  static int serialize(char* buffer);
  static int serialize(char* buffer, int offset);
  
  static int deserialize(void*);
  static int deserialize(void*, int);
  
  static bool is_valid(const char* buffer);
};

#endif