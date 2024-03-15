#include <cstring>
#include "../Common/String.cpp"
#include "../Common/Hash/Md5_Hash.cpp"
#include "../Common/Hash/Md5_Digest.cpp"

int main()
{
  String str { "hola" };

  auto digest = Md5_Hash::calculate_digest(str);
  std::cout << digest.to_string() << "\n";

  return 0;
}