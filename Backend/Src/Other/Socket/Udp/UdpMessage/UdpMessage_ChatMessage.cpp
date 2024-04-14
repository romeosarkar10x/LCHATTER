#include "../../../../../Inc/AppBackend/AppBackend.hpp"
#include "../../../../../Inc/Other/Socket/Udp/UdpMessage/UdpMessage_ChatMessage.hpp"
#include "../../../../../Inc/File/Serializer.hpp"
#include "../../../../../Inc/File/Deserializer.hpp"

UdpMessage_ChatMessage::UdpMessage_ChatMessage(const ChatMessage& m) :
  ChatMessage { m } {}

UdpMessage::Type UdpMessage_ChatMessage::get_type() const
{
  return UdpMessage::Type::CHAT_MESSAGE;
}

u_int UdpMessage_ChatMessage::serialization_length() const
{
  return Serializer::serialization_length(static_cast<const ChatMessage&>(*this));
}

void UdpMessage_ChatMessage::serialize(char* buffer, u_int& offset) const
{
  Serializer::serialize(static_cast<const ChatMessage&>(*this), buffer, offset);
}

void UdpMessage_ChatMessage::deserialize(const char* const buffer, u_int& offset)
{
  Deserializer::deserialize(static_cast<ChatMessage&>(*this), buffer, offset);
}

void UdpMessage_ChatMessage::handle()
{
  auto& connections = AppBackend::get_connections();

  auto itr = std::ranges::find(connections, _m_sender,
    [] (const Connection& c) -> const User& { return c.get_user(); }
  );
  
  std::cout << "HERE" << std::endl;
  toggle_sender_is_me();
  itr->get_chat().emplace(static_cast<ChatMessage&&>(*this));
}