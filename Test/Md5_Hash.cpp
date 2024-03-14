#include <cstring>
#include "../Common/Md5_Hash.cpp"

int main()
{
  char str[2048] = "";
  int length = static_cast<int>(std::strlen(str));

  std::cout << "length: " << length << "\n";

  Md5_Hash hash_object;
  hash_object.hash(str, length);
  std::cout << Md5_Hash::to_string(hash_object.buffer()) << "\n";

  return 0;
}