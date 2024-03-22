#include <iostream>
#include <vector>
#include <algorithm>

#include "../Common/ConnectionRequest.cpp"


int main()
{
  std::vector<ConnectionRequest> requests;

  requests.emplace_back(User { "Romeo", "1122" }, Address { "7777" });
  requests.emplace_back(User { "Abhij", "2211" }, Address { "192.168.0.100", "2212" });
  requests.emplace_back(User { "Sudip", "KIIT" }, Address { "2222" });
  requests.emplace_back(User { "Anony", "HACK" }, Address { "999" });

  std::ranges::sort(requests, std::less<> {}, [] (const ConnectionRequest& r) -> const TimePoint& { return r.get_timepoint_last_seen(); });
  for(const auto& r : requests) { std::cout << r << "\n"; }

  return 0;
}