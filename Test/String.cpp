#include "../Common/String.cpp"

int main()
{
  String s { "hello" }, s2 { " " }, s3 { "world" };
  std::cout << "\"" + s + s2 + s3 + "\"\n";

  return 0;
}