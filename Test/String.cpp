#include "../Common/String.cpp"

void print_buffer(const void* buffer)
{
  std::cout << "buffer: [" << reinterpret_cast<const char*>(buffer) << "]";
}

int main()
{
  String s { "hello" }, s2 { " " }, s3 { "world" };
  std::cout << "\"" + s + s2 + s3 + "\"\n";

  print_buffer("\"" + s + s2 + s3 + "\"\n");

  return 0;
}