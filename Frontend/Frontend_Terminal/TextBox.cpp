#ifndef TEXTBOX_CPP
#define TEXTBOX_CPP

#include <utility>
#include <memory>
#include <cassert>
#include <ncurses/ncurses.h>

#include "Window.cpp"

class TextBox
{
  enum Mode : unsigned char { INSERT, OVERTYPE };
  Window _m_win_border, _m_win_text;
  Mode _m_mode;

  int _m_buffer_size;
  char* _m_buffer;
  int _m_index { 0 };

public:
  TextBox() = default;
  TextBox(int height, int width, int y, int x) :
  _m_win_border(height, width, y, x),
  _m_win_text(height - 2, width - 2, y + 1, x + 1),
  _m_buffer_size { (height - 2) * (width - 2) + 1 },
  _m_buffer { new char[_m_buffer_size] }
  {
    _m_win_border.box();
    _m_win_border.refresh();
  }

  TextBox& operator=(const TextBox& rhs) = delete;
  TextBox& operator=(TextBox&& rhs)
  {
    this->swap(rhs);
    return *this;
  }

  void swap(TextBox& rhs) noexcept
  {
    _m_win_border.swap(rhs._m_win_border);
    _m_win_text.swap(rhs._m_win_text);
    std::swap(_m_buffer, rhs._m_buffer);
    std::swap(_m_buffer_size, rhs._m_buffer_size);
    std::swap(_m_index, rhs._m_index);
  }

  int getch() { return _m_win_text.getch(); }
  void putchar(char ch) { _m_win_text.printf("%c", ch); _m_win_text.refresh(); }

  // void move_cursor(Window::Direction d) { _m_win_text.move_cursor(d); }
  
  void echo(int key)
  {
    if(31 < key && key < 127)
    {
      putchar(_m_buffer[_m_index++] = static_cast<char>(key));
      return;
    }

    switch(key)
    {
    case -1:
      break;

    case KEY_BACKSPACE:
      if(_m_index == 0)
      {
        break;
      }

      _m_win_text.move_cursor(Window::Direction::LEFT);
      putchar(' ');
      _m_win_text.move_cursor(Window::Direction::LEFT);
      _m_index--;
      break;

    /* Disable moving UP, DOWN, LEFT, RIGHT as it is too difficult to implement at this level */

    // case KEY_UP:
    //   _m_win_text.move_cursor(Window::Direction::UP);
    //   break;
    // case KEY_DOWN:
    //   _m_win_text.move_cursor(Window::Direction::DOWN);
    //   break;
    // case KEY_LEFT:
    //   _m_win_text.move_cursor(Window::Direction::LEFT);
    //   break;
    // case KEY_RIGHT:
    //   _m_win_text.move_cursor(Window::Direction::RIGHT);
    //   break;

    // case KEY_DC:
      
    default:
      break;
    }
  }

  void clear()
  {
    

  }
  const char* text() { return _m_buffer; }

  ~TextBox()
  {
    if(_m_buffer != nullptr)
    {
      delete [] _m_buffer;
    }
  }
};



#endif