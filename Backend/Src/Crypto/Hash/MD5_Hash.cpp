#include <iostream>
#include <cstring>

#include "../../../Inc/Crypto/Hash/MD5_Hash.hpp"


u_int MD5_Hash::_s_rotate_left(u_int u, u_char amount)
{
  asm(
    "rol\t%[amount], %[u]\n\t"
    : [u]"+r"(u)
    : [amount]"c"(amount)
  );

  return u;
}

int MD5_Hash::_s_tmp_buffer_length(int input_length)
{
  return ((input_length + 8) / 64 + 1) * 64;
}

MD5_Digest MD5_Hash::calculate_digest(const void* input, int length) /// length in bytes
{
  void* tmp = new char[_s_tmp_buffer_length(length)];
  std::memcpy(tmp, input, length);

  { /// padding
    int original_length = length;
    reinterpret_cast<u_char*>(tmp)[length++] = static_cast<u_char>(0x80); /// append [1000000]

    while(length % 64u != 56u) { reinterpret_cast<u_char*>(tmp)[length++] = static_cast<u_char>(0x00); }
    *reinterpret_cast<u_long_long*>(reinterpret_cast<u_char*>(tmp) + length) = static_cast<u_long_long>(original_length) * 8ull; /// length of original message in bits
    length += 8u;
  }
  
  u_char shifts_cnt[64u] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
  };

  u_int k[64u] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
  };

  int num_chunks = length / 64u;
  u_int a = 0x67452301, b = 0xefcdab89, c = 0x98badcfe, d = 0x10325476;

  for(int i_chunk = 0; i_chunk < num_chunks; i_chunk++)
  {
    u_int a_curr = a, b_curr = b, c_curr = c, d_curr = d;
    u_int* m = reinterpret_cast<u_int*>((reinterpret_cast<u_char*>(tmp) + i_chunk * 64u));

    for(u_int u = 0; u < 64; u++)
    {
      u_int f, g;

      if(u < 16u)
      {
        f = (b_curr & c_curr) | ((~b_curr) & d_curr);
        g = u;
      }
      else if(u < 32u)
      {
        f = (d_curr & b_curr) | ((~d_curr) & c_curr);
        g = (5u * u + 1u) % 16u;
      }
      else if(u < 48u)
      {
        f = b_curr ^ c_curr ^ d_curr;
        g = (3u * u + 5u) % 16u;
      }
      else
      {
        f = c_curr ^ (b_curr | (~d_curr));
        g = (7u * u) % 16u;
      }

      f += a_curr + k[u] + m[g];
      a_curr = d_curr;
      d_curr = c_curr;
      c_curr = b_curr;
      b_curr += _s_rotate_left(f, shifts_cnt[u]);
    }

    a += a_curr, b += b_curr, c += c_curr, d += d_curr;
  }
  
  MD5_Digest digest {};
  
  u_int* digest_buffer = reinterpret_cast<u_int*>(digest._m_buffer);
  digest_buffer[0] = a, digest_buffer[1] = b, digest_buffer[2] = c, digest_buffer[3] = d;

  delete [] reinterpret_cast<char*>(tmp);    
  return digest;
}

MD5_Digest MD5_Hash::calculate_digest(const String& str) { return calculate_digest(str.get_buffer(), str.get_length()); }
