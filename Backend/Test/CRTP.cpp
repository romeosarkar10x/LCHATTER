#include <iostream>
#include <cassert>

template<class _T>
  class Buffer_Mixin
  {
  public:
    Buffer_Mixin() = delete;
    ~Buffer_Mixin() = delete;

    static int    get_buffer_size() { return _T::_S_buffer_size; }
    static char*  get_buffer() { assert(_T::_s_buffer != nullptr); return _T::_s_buffer; }

    static void init() { if(_T::_s_buffer == nullptr) { _T::_s_buffer = new char [_T::_S_buffer_size]; } }
    static void clear() { if(_T::_s_buffer != nullptr) { _T::_s_buffer[0] = 0; } }
    static void destroy() { if(_T::_s_buffer != nullptr) { delete [] _T::_s_buffer; _T::_s_buffer = nullptr; } }

  };

class IpAddress : public Buffer_Mixin<IpAddress>
{
  friend class Buffer_Mixin<IpAddress>;
  static const int  _S_buffer_size = 20; 
  static char*      _s_buffer;
};

char* IpAddress::_s_buffer { nullptr };


int main()
{
  IpAddress::init();
  IpAddress::clear();

  std::cout << IpAddress::get_buffer() << "\n";
  std::cout << IpAddress::get_buffer_size() << "\n";
  return 0;
}