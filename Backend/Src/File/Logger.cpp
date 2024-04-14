#include "../../Inc/File/Logger.hpp"

Logger::Logger(const char* f_name) : _m_file(f_name) {}

Logger& Logger::operator<<(Manipulator m)
{
  switch(m)
  {
  case timestamp:
    _m_file << TimePoint { 0 };
    break;
  case endl:
    _m_file << std::endl;
    break;
  }

  return *this;
}

Logger::Logger(Logger&& rhs) : _m_file { std::move(rhs._m_file) } {}

Logger& Logger::operator=(Logger&& rhs) { this->swap(rhs); return *this; }

void Logger::swap(Logger& rhs) noexcept
{
  _m_file.swap(rhs._m_file);
}

std::ofstream* Logger::operator->() { return &_m_file; }

Logger::~Logger() { _m_file.close(); }

Logger logger { "LC_AppBackend.log" };