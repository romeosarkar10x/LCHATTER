#include "../Chat/Chat.cpp"

int main()
{
  Chat c;
  c.emplace(User { "ha ha ha", "psw!!" }, String { "hello world" });
  // ChatMessage m { User { "ha ha ha", "psw!!" }, String { "hello world" } };

  // std::cout << c.get_messages()[0] << "\n";
  return 0;
}