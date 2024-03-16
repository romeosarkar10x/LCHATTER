#include <cstring>
#include "../Common/String.cpp"
#include "../Common/Hash/MD5_Hash.cpp"
#include "../Common/Hash/MD5_Digest.cpp"

int main()
{
  String str { "hola" };

  auto digest = MD5_Hash::calculate_digest(str);
  std::cout << digest << "\n";

  return 0;
}