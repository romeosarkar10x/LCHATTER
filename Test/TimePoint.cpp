#include <windows.h>
#include "../Common/TimePoint.cpp"

int main()
{
  TimePoint t;
  std::cout << t << "\n";

  Sleep(1000);

  t.refresh();
  std::cout << t << "\n";

  return 0;
}