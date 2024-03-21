#include <Windows.h>
#include "../Frontend/Window.cpp"

int main()
{
  initscr();
  noecho();
    // raw();
  keypad(stdscr, true);
  
  
  Window w { 6, 14, 4, 20 };
  w.box();

  while(true)
  {
    int ret = w.getch();
    if(ret != -1) { break; }
    Sleep(100);
  }

  // w.clear();
  w.~Window();

  wgetch(stdscr);


  endwin();
  return 0;
}