#ifndef WINDOW_CPP
#define WINDOW_CPP

#include <utility>
#include <cassert>
#include <ncurses/ncurses.h>
#undef getch

class Window
{
  bool    _m_is_initialized;
  int     _m_height;
  int     _m_width;
  WINDOW* _m_window;

  void _m_move_cursor_up()
  {
    int curr_y = getcury(_m_window), curr_x = getcurx(_m_window);
    int ret = (curr_y != 0) ? wmove(_m_window, curr_y - 1, curr_x) : wmove(_m_window, 0, 0);
    assert(ret != ERR);
  }
  void _m_move_cursor_down()
  {
    int curr_y = getcury(_m_window), curr_x = getcurx(_m_window);
    int ret = (curr_y != _m_height - 1) ? wmove(_m_window, curr_y + 1, curr_x) : wmove(_m_window, _m_height - 1, _m_width - 1);
    assert(ret != ERR);
  }

  void _m_move_cursor_left()
  {
    int curr_y = getcury(_m_window), curr_x = getcurx(_m_window);
    if(curr_x == 0)
    {
      if(curr_y != 0) { wmove(_m_window, curr_y - 1, _m_width - 1); }
    }
    else { wmove(_m_window, curr_y, curr_x - 1); }
  }

  void _m_move_cursor_right()
  {
    int curr_y = getcury(_m_window), curr_x = getcurx(_m_window);
    if(curr_x == _m_width - 1)
    {
      if(curr_y != _m_height - 1) { wmove(_m_window, curr_y + 1, 0); }
    }
    else { wmove(_m_window, curr_y, curr_x + 1); }
  }

public:
  Window() : _m_is_initialized { false }, _m_window { nullptr } {}
  
  Window(int height, int width, int y, int x) :
  _m_is_initialized { true },
  _m_height { height },
  _m_width { width },
  _m_window { newwin(height, width, y, x) } { keypad(_m_window, true); }

  Window(WINDOW* window) : _m_is_initialized { true }, _m_window { window } { _m_height = getmaxy(_m_window), _m_width = getmaxx(_m_window); }

  Window(const Window& rhs) = delete; /// disable copying
  
  Window(Window&& rhs) noexcept :
  _m_is_initialized { rhs._m_is_initialized },
  _m_height { rhs._m_height },
  _m_width { rhs._m_width },
  _m_window { std::exchange(rhs._m_window, nullptr) } {}

  Window& operator=(const Window& rhs) = delete;
  
  Window& operator=(Window&& rhs) noexcept { swap(rhs); return *this; }

  void swap(Window& rhs) noexcept
  {
    std::swap(_m_is_initialized, rhs._m_is_initialized);
    std::swap(_m_height, rhs._m_height);
    std::swap(_m_width, rhs._m_width);
    std::swap(_m_window, rhs._m_window);
  }

  ~Window() noexcept
  {
    if(_m_window != nullptr)
    {
      clear();
      delwin(_m_window);
      _m_window = nullptr;
    }
  }

  void box() { ::box(_m_window, 0, 0); }

  template<typename ... _Tp>
    void printf(_Tp ... p) { wprintw(_m_window, p...); }

  template<typename ... _Tp>
    void mvprintf(_Tp ... p) { mvwprintw(_m_window, p...); }
  
  void refresh() { wrefresh(_m_window); }
  int getch() { return wgetch(_m_window); }
  
  
  void move_cursor(int y, int x) { wmove(_m_window, y, x); }
  
  int height() { return _m_height; }
  int width() { return _m_width; }
  
  void clear(){ mvprintf(0, 0, "%*c", _m_height * _m_width, ' '); refresh(); }

  enum Direction : u_int { UP, DOWN, LEFT, RIGHT };
  
  void move_cursor(Direction direction)
  {
    switch(direction)
    {
    case UP:
      _m_move_cursor_up();
      break;
    case DOWN:
      _m_move_cursor_down();
      break;
    case LEFT:
      _m_move_cursor_left();
      break;
    case RIGHT:
      _m_move_cursor_right();
      break;
    default:
      break;
    }
  }

  void nodelay(bool pred) { ::nodelay(_m_window, pred); }
  void resize(int height, int width) { wresize(_m_window, height, width); }
  
};

#endif