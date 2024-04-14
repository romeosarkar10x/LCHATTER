#include <fstream>

#include "Deserializer.hpp"

class Loader
{
  static const int    _S_buffer_size = 4000;
  
  std::ifstream    _m_in;
  bool            _m_is_initialized;

  char*   _m_buffer;
  u_int   _m_offset;

public:
  
  Loader() = default;
  Loader(const char* f_name);

  void init(const char* f_name);
  void destroy();

  // void reset();

  template<class T>
    void read(T& object)
    {
      Deserializer::deserialize(object, _m_buffer, _m_offset);
    }

  void load();
};

extern Loader loader;