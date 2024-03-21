#include <iostream>
#include <vector>
#include <algorithm>

#include "../Common/ConnectionRequest.cpp"

int main()
{
  std::vector<ConnectionRequest> requests;
  requests.emplace_back(User { "Romeo", "22" }, Address {});
  requests.emplace_back(User { "Abhij", "11" }, Address {});

  auto id = requests[1].get_user().get_id();
  auto itr = std::ranges::find(requests, id, [] (const ConnectionRequest& r) -> const String& { return r.get_user().get_id(); });

  assert(itr != requests.end());

  // std::ranges::find(connections, String { "a" }, );
  return 0;
}