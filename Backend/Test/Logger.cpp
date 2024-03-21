#include <fstream>

#include "../Common/Logger.cpp"

int main()
{
  for(int i = 0; i < 10000; i++)
  {
    logger << Logger::timestamp << "hello world" << Logger::endl;
  }
  
  return 0;
}