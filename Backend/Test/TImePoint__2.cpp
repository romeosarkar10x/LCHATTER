#include <iostream>
#include <algorithm>
#include <vector>

#include "../Common/TimePoint.cpp"

int main()
{
  // TimePoint t {}, t2 { t };
  // std::cout << t << "\n";
  std::vector<TimePoint> timepoints;

  timepoints.emplace_back();
  Sleep(2000);
  timepoints.emplace_back();

  // std::cout << "## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## " << std::endl;
  std::ranges::sort(timepoints, std::less<> {});
  // std::cout << "## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## " << std::endl;

  return 0;
}