#include <iostream>
#include <windows.h>

#include "Backend/AppBackend.cpp"

int main()
{

  AppBackend::initialize();


  while(true)
  {
    AppBackend::update();

    Sleep(100);
    
  }
  return 0;
}