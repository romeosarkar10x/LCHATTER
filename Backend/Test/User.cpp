#include <algorithm>
#include <vector>

#include "../Common/User.cpp"

int main()
{
  std::vector<User> users;
  users.emplace_back("romeosarkar", "1122");
  users.emplace_back("abhijeetadarsh", "22");
  users.emplace_back("ronaldo", "00");
  users.emplace_back("gadha", "**");
  users.emplace_back("abc", "$$$$####");
  users.emplace_back("doe", "abcd");
  users.emplace_back("johndeer", "xyzw");
  users.emplace_back("anonymous", "@@");
  users.emplace_back("alice", "alice");
  users.emplace_back("bob", "bob");
  users.emplace_back("chad", "malicious_intent");
  users.emplace_back("craig", "password_cracker");
  users.emplace_back("eve", "eavesdropper");
  users.emplace_back("mallory", "malicious");

  for(const User& u : users) { std::cout << u << std::endl; }
  std::cout << "##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@##@@"
    << std::endl;

  std::ranges::sort(users, std::less<> {}, [] (const User& u) { return u.get_name(); });
  for(const User& u : users) { std::cout << u << std::endl; }

  return 0;
}