#include "../../Inc/File/Saver.hpp"

Saver::Saver(const char* f_name)
{
  init(f_name);
}

void Saver::init(const char* const f_name)
{
  _m_out.open(f_name, std::ios::binary);

  _m_buffer = new char [_S_buffer_size];
  _m_offset = 0;

  _m_is_initialized = true;
}

void Saver::destroy()
{
  if(_m_is_initialized)
  {
    delete [] _m_buffer;

    _m_is_initialized = false;
  }
}

void Saver::reset()
{
  _m_offset = 0;
}

void Saver::save()
{
  assert(_m_out.is_open());
  _m_out.write(_m_buffer, _m_offset);
}


Saver saver { "LC_SAVER.dat" };


// int main()
// {
//   char str[] = "Hello World!";

//   // saver.save(reinterpret_cast<char*>(array), 0, sizeof(array));
//   saver.write(str);
//   saver.save();
//   return 0;
// }