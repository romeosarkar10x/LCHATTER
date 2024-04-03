#include <iostream>
#include <cstring>

#include "../../Common/Fwd.hpp"
#include "MD5_Digest.hpp"

class MD5_Hash
{
  static u_int  _s_rotate_left(u_int u, u_char amount);
  static int    _s_tmp_buffer_length(int input_length);

public:
  MD5_Hash() = delete;
  
  MD5_Hash(const MD5_Hash&) = delete;
  MD5_Hash(MD5_Hash&&) = delete;
  
  MD5_Hash& operator=(const MD5_Hash&) = delete;
  MD5_Hash& operator=(MD5_Hash&&) = delete;
  
  ~MD5_Hash() = delete;

  static MD5_Digest calculate_digest(const void* input, int length);
  static MD5_Digest calculate_digest(const String& str);
};