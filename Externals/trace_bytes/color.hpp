#ifndef COLOR_HPP
#define COLOR_HPP

#include "global.hpp"

namespace Memory
{
  template<typename _T>
    struct colorMixin
    {
      static constexpr c_string
        heading = _T::_Heading,
        reset =_T::_Reset,
        border = _T::_Border,
        offset = _T::_offset;

      struct hex
      {
        static constexpr c_string
          normal = _T::Hex::_Normal,
          disabled = _T::Hex::_Disabled;
      };

      struct text
      {
        static constexpr c_string
          normal = _T::Text::_Normal,
          disabled = _T::Text::_Disabled,
          non_printable = _T::Text::_NonPrintable;
      };
    };

  struct color__none : colorMixin<color__none>
  {
    static constexpr c_string
      _Border = "",
      _offset = "",
      _Reset = "",
      _Heading = "";

    struct Hex
    {
      static constexpr c_string
        _Normal = "",
        _Disabled = "";
    };

    struct Text
    {
      static constexpr c_string
        _Normal = "",
        _Disabled = "",
        _NonPrintable = "";
    };
  };

  struct color__a : colorMixin<color__a>
  {
    static constexpr c_string
      _Border = "\x1b[1;93m",
      _Heading = "\x1b[33m",
      _offset = "\x1b[31m",
      _Reset = "\x1b[m";

    struct Hex
    {
      static constexpr c_string
        _Normal = "\x1b[32m",
        _Disabled = "\x1b[30m";
    };

    struct Text
    {
      static constexpr c_string
        _Normal = "\x1b[37m",
        _NonPrintable = "\x1b[37m",
        _Disabled = "\x1b[30m";
    };
  };
}

#endif