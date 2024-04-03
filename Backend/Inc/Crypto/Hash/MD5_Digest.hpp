#ifndef MD5_DIGEST_HPP
#define MD5_DIGEST_HPP

#include <iostream>
#include <cstring>
#include <utility>

#include "../../Common/String.hpp"
#include "../../Common/Fwd.hpp"

class MD5_Digest
{
  u_char          _m_buffer[16];
  
  mutable String  _m_string;
  mutable bool    _m_is_valid { false };

  friend MD5_Hash;

public:
  MD5_Digest() = default;
  MD5_Digest(const char* buffer);

  MD5_Digest(const MD5_Digest& rhs) = default;
  MD5_Digest(MD5_Digest&& rhs);
  
  void swap(MD5_Digest& rhs) noexcept;

  MD5_Digest& operator=(const MD5_Digest& rhs);
  MD5_Digest& operator=(MD5_Digest&& rhs);

  const String& to_string() const;

  bool operator==(const MD5_Digest& rhs) const;

  int serialize(char* buffer)               const;
  int serialize(char* buffer, int offset)   const;
  
  int deserialize(const char* buffer);
  int deserialize(const char* buffer, int offset);

private:
  friend std::ostream& operator<<(std::ostream& o, const MD5_Digest& digest);
};


#endif