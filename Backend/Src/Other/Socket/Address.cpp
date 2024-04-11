#include <cstring>

#include "../../../Inc/Other/Socket/Address.hpp"
#include "../../../Inc/File/Serializer.hpp"

Address::Address() { _m_addr.sin_family = AF_INET; }

Address::Address(const char* port) : Address()
{
  _m_addr.sin_port = htons(static_cast<u_short>(std::strtoul(port, nullptr, 0)));
  _m_addr.sin_addr.s_addr = INADDR_ANY;
}

Address::Address(const char* ip_address, const char* port) : Address()
{
  _m_addr.sin_port = htons(static_cast<u_short>(std::strtoul(port, nullptr, 0)));
  _m_addr.sin_addr.s_addr = inet_addr(ip_address);
}

Address::Address(const Address& addr) { std::memcpy(&_m_addr, &addr._m_addr, sizeof(SOCKADDR_IN)); }

Address& Address::operator=(const Address& rhs)
{
  this->~Address();
  new (this) Address { rhs };
  return *this;
}

String Address::get_port() const { return String::to_string(ntohs(_m_addr.sin_port)); }
String Address::get_ip_address() const { return inet_ntoa(_m_addr.sin_addr); }

/// ip-port validator needed
// void set_port(const Address& addr) { _m_addr.sin_port = addr._m_addr.sin_port; }
// void set_ip_address(const Address& addr) { _m_addr.sin_addr = addr._m_addr.sin_addr; }

void Address::set_port(const Address& addr) { _m_addr.sin_port = addr._m_addr.sin_port; }
void Address::set_ip_address(const Address& addr) { _m_addr.sin_addr = addr._m_addr.sin_addr; }

String Address::to_string() const { return "{" + get_ip_address() + ":" + get_port() + "}"; }

unsigned int Address::serialization_length() const
{
  return Serializer::serialization_length(_m_addr.sin_port)+ 
    Serializer::serialization_length(_m_addr.sin_addr.s_addr); 
}

void Address::serialize(char* buffer, unsigned int& offset) const
{
  Serializer::serialize(_m_addr.sin_port, buffer, offset);
  Serializer::serialize(_m_addr.sin_addr.s_addr, buffer, offset); 
}

int Address::deserialize(const char* buffer)
{
  std::memcpy(&_m_addr.sin_port, buffer, sizeof(_m_addr.sin_port));
  std::memcpy(&(_m_addr.sin_addr), buffer + sizeof(_m_addr.sin_port), sizeof(_m_addr.sin_addr));

  return serialization_length();
}

int Address::deserialize(const char* buffer, int offset) { return deserialize(reinterpret_cast<const char*>(buffer) + offset); }

std::ostream& operator<<(std::ostream& o, const Address& a) { o << a.to_string(); return o; }