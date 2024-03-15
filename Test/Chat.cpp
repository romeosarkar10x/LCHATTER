#include "../Chat/Chat.cpp"

int main()
{
  Chat c;
  c.emplace( User { "ha ha ha", "psw!!" }, String { "hello world" });

  

  return 0;
}