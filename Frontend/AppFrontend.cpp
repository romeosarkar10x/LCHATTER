#include <iostream>
#include <ncurses/ncurses.h>

// class Window
// {

// };

// text box
// display

int main()
{
  // std::cout << "hello world\n";
  initscr();
  raw();
  keypad(stdscr, true);
  
  int x, y;
  getmaxyx(stdscr, y, x);
  // char ch = getch();
  
  endwin();
  return 0;
}

/*
-lncurses -DNCURSES_STATIC
*/