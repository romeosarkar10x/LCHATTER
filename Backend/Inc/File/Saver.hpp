#include <fstream>
#include <cassert>

#include "Serializer.hpp"

class Saver
{
  static const int    _S_buffer_size = 4000;
  
  std::ofstream   _m_out;
  bool            _m_is_initialized;

  char*           _m_buffer;
  unsigned int    _m_offset;

public:
  
  Saver() = default;
  Saver(const char* f_name);

  void init(const char* const f_name);
  void destroy();

  void reset();

  template<class T>
    void write(const T& object)
    {
      Serializer::serialize(object, _m_buffer, _m_offset);
    }

  void save();
};

extern Saver saver;