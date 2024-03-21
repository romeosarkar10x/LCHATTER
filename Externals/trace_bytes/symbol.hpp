#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include "global.hpp"

namespace Memory
{
  template<typename _T>
    struct symbolMixin
    {
      static constexpr c_string fill = _T::_Fill;
      struct hex { static constexpr c_string disabled = _T::Hex::_Disabled; };
      struct text
      {
        static constexpr c_string disabled = _T::Text::_Disabled,
          non_printable = _T::Text::_NonPrintable;
      };
      struct box
      {
        struct down
        {
          static constexpr c_string left = _T::Box::Down::_Left,
            right = _T::Box::Down::_Right;
        };
        struct up
        {
          static constexpr c_string left = _T::Box::Up::_Left,
            right = _T::Box::Up::_Right;
        };
        struct horizontal
        {
          static constexpr c_string h = _T::Box::Horizontal::_H,
            down = _T::Box::Horizontal::_Down,
            up = _T::Box::Horizontal::_Up,
            vertical = _T::Box::Horizontal::_Vertical;
        };
        struct vertical
        {
          static constexpr c_string v = _T::Box::Vertical::_V,
            right = _T::Box::Vertical::_Right,
            left = _T::Box::Vertical::_Left,
            horizontal = _T::Box::_Horizontal;
        };
      };
    };

  struct symbol__default : public symbolMixin<symbol__default>
  {
    static constexpr c_string _Fill = " ";
    struct Hex { static constexpr c_string _Disabled = "**"; };
    struct Text
    {
      static constexpr c_string _Disabled = ".",
        _NonPrintable = ".";
    };
    struct Box
    {
      struct Down
      {
        static constexpr c_string _Left = "┐",
          _Right = "┌";
      };
      struct Up
      {
        static constexpr c_string _Left = "┘",
          _Right = "└";
      };
      struct Horizontal
      {
        static constexpr c_string _H = "─",
          _Down = "┬",
          _Up = "┴",
          _Vertical = "┼";
      };
      struct Vertical
      {
        static constexpr c_string _V = "│",
          _Right = "├",
          _Left = "┤",
          _Horizontal = "┼";
      };
    };
  };

  struct symbol__a : public symbolMixin<symbol__a>
  {
    static constexpr c_string _Fill = " ";
    struct Hex { static constexpr c_string _Disabled = "**"; };
    struct Text
    {
      static constexpr c_string _Disabled = ".",
        _NonPrintable = ".";
    };
    struct Box
    {
      struct Down
      {
        static constexpr c_string _Left = "╗",
          _Right = "╔";
      };
      struct Up
      {
        static constexpr c_string _Left = "╝",
          _Right = "╚";
      };
      struct Horizontal
      {
        static constexpr c_string _H = "═",
          _Down = "╦",
          _Up = "╩",
          _Vertical = "╬";
      };
      struct Vertical
      {
        static constexpr c_string _V = "║",
          _Right = "╠",
          _Left = "╣",
          _Horizontal = "╬";
      };
    };
  };
}

#endif