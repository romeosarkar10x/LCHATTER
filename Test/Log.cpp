#include <fstream>
int main()
{
  const char* p = "Hello World!";
  std::ofstream fout("Test.txt");

  fout.operator<<(p).operator<<("\n");
  fout << p << "\n";
  
  return 0;
}