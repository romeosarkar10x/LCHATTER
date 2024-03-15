#ifndef LOG_CPP
#define LOG_CPP

#include <fstream>
#include "../Other/Socket/Addr_Base.cpp"

std::ostream& operator<<(std::ostream& __o, const Addr_Base& __addr)
{
  __o << __addr.to_string(); return __o;
}

class Logger
{
  std::ofstream _m_file;

public:
  Logger(const char* f_name) : _m_file(f_name) {}
  
  template<typename _Tp>
    Logger& operator<<(_Tp&& _param)
    {
      _m_file << (std::forward<_Tp>(_param));
      _m_file.flush();
      return *this;
    }
  
  Logger(const Logger& rhs) = delete;
  Logger(Logger&& rhs) : _m_file { std::move(rhs._m_file) } {}

  Logger& operator=(const Logger& rhs) = delete;
  Logger& operator=(Logger&& rhs) { this->swap(rhs); return *this; }

  void swap(Logger& rhs) noexcept
  {
    _m_file.swap(rhs._m_file);
  }

  std::ofstream* operator->() { return &_m_file; }

  ~Logger() { _m_file.close(); }
};



Logger logger("App.log");
#endif