#ifndef TRACE_BYTES_H
#define TRACE_BYTES_H

#include <iostream>
#include <cassert>

#include "color.hpp"
#include "symbol.hpp"
#include "byte.hpp"
#include "offset.hpp"

namespace Memory
{
  struct _trace_bytes_fn
  {
    using color = color__a;
    using symbol = symbol__a;

    void operator()(const void* start_ptr, int num_bytes, int group_size = 16) const
    {
      assert(group_size % 4 == 0);

      if(0u == num_bytes) { return; }

      int num_columns = group_size, num_rows = (num_bytes + group_size - 1) / group_size;
      assert(num_columns <= 256);

      auto append_n = [] (std::string& s, c_string s_append, int n) -> void
      {
        for(int i = 0; i < n; i++) { s += s_append; }
      };

      { /// @section top, @subsection top
        std::string s;
        s += symbol::box::down::right;
        append_n(s, symbol::box::horizontal::h, 6); // offset
        s += symbol::box::horizontal::down;
        append_n(s, symbol::box::horizontal::h, 3 * num_columns - 1); // hex
        s += symbol::box::horizontal::down;
        append_n(s, symbol::box::horizontal::h, num_columns); // text
        s += symbol::box::down::left;

        std::cout << color::border << s << color::reset << "\n";
      }

      { /// @section top, @subsection middle
        std::string s;
        s += std::string(color::border) + symbol::box::vertical::v + color::reset;
        s += std::string(color::heading) + "Offset" + color::reset; // offset
        s += std::string(color::border) + symbol::box::vertical::v + color::reset;

        for(int i_column = 0; i_column < num_columns; i_column++)
        {
          char xyz = static_cast<char>(i_column);
          byte b(&xyz);

          s += color::heading + b.to_string__hex() + color::reset;

          if(i_column != num_columns - 1)
          {
            s += symbol::fill;
          }
        }

        s += std::string(color::border) + symbol::box::vertical::v + color::reset;

        std::string text;
        switch(num_columns)
        {
        case 4:
          text += "Text";
          break;
        case 8:
          text += "  Text  ";
          break;
        case 12:
          text += "    Text    ";
          break;
        default:
          {
            int n = (num_columns - 12) / 2;
            append_n(text, symbol::fill, n);
            text += "Decoded Text";
            append_n(text, symbol::fill, n);
          }
          break;
        }

        s += std::string(color::heading) + text + color::reset; // text
        s += std::string(color::border) + symbol::box::vertical::v + color::reset;

        std::cout << s << "\n";
      }

      { /// @section top, @subsection bottom
        std::string s;
        s += symbol::box::vertical::right;
        append_n(s, symbol::box::horizontal::h, 6);
        s += symbol::box::horizontal::vertical;
        append_n(s, symbol::box::horizontal::h, 3 * num_columns - 1);
        s += symbol::box::horizontal::vertical;
        append_n(s, symbol::box::horizontal::h, num_columns);
        s += symbol::box::vertical::left;

        std::cout << color::border + s + color::reset << "\n";
      }

      /// @section middle
      int i_max = num_rows * num_columns;
      for(int i = 0; i < i_max; i += num_columns)
      {
        std::string s;
        s = s + color::border + symbol::box::vertical::v + color::reset;
        s = s + color::offset + offset::to_string(i) + color::reset; // offset
        s = s + color::border + symbol::box::vertical::v + color::reset;

        for(int curr_offset = 0; curr_offset < num_columns; curr_offset++) // hex
        {
          int total_offset = i + curr_offset;

          if(total_offset < num_bytes)
          {
            byte b(start_ptr, total_offset);
            s += color::hex::normal + b.to_string__hex();
          }
          else
          {
            s += std::string(color::hex::disabled) + symbol::hex::disabled;
          }
          s += color::reset;

          if(curr_offset != num_columns - 1) { s += symbol::fill; }
        }

        s = s + color::border + symbol::box::vertical::v + color::reset;

        for(int curr_offset = 0U; curr_offset < num_columns; curr_offset++) // text
        {
          int total_offset = i + curr_offset;

          if(total_offset < num_bytes)
          {
            byte b(start_ptr, total_offset);
            s += (b.is_printable() ? color::text::normal : color::text::non_printable) + b.to_string__ascii();
          }
          else { s += std::string(color::text::disabled) + symbol::text::disabled; }

          s += color::reset;
        }

        s += std::string(color::border) + symbol::box::vertical::v + color::reset;
        std::cout << s << "\n";
      }

      // @section bottom
      {
        std::string s;
        s += symbol::box::up::right;
        append_n(s, symbol::box::horizontal::h, 6);
        s += symbol::box::horizontal::up;
        append_n(s, symbol::box::horizontal::h, 3 * num_columns - 1);
        s += symbol::box::horizontal::up;
        append_n(s, symbol::box::horizontal::h, num_columns);
        s += symbol::box::up::left;

        std::cout << color::border + s + color::reset << std::endl;
      }
    }
  };
  
  constexpr auto trace_bytes = _trace_bytes_fn {};
}


#endif