#include <cstring>

#include "../../../Inc/Other/Socket/Address.hpp"
#include "../../../Inc/File/Serializer.hpp"
#include "../../../Inc/File/Deserializer.hpp"

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

u_int Address::serialization_length() const
{
  return Serializer::serialization_length(_m_addr.sin_port)+ 
    Serializer::serialization_length(_m_addr.sin_addr.s_addr); 
}

void Address::serialize(char* buffer, u_int& offset) const
{
  Serializer::serialize(_m_addr.sin_port, buffer, offset);
  Serializer::serialize(_m_addr.sin_addr.s_addr, buffer, offset); 
}

void Address::deserialize(const char* const buffer, u_int& offset)
{
  this->~Address();

  Deserializer::deserialize(_m_addr.sin_port, buffer, offset);
  Deserializer::deserialize(_m_addr.sin_addr.s_addr, buffer, offset);
}

std::ostream& operator<<(std::ostream& o, const Address& a) { o << a.to_string(); return o; }