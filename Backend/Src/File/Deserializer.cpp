#include "../../Inc/File/Deserializer.hpp"

void Deserializer::deserialize(FILETIME& object, const char* const buffer, u_int& offset)
{
  Deserializer::deserialize(object.dwLowDateTime, buffer, offset);
  Deserializer::deserialize(object.dwHighDateTime, buffer, offset);
}

// u_int Deserializer::deserialization_length(const FILETIME object, const char* const buffer, u_int& offset)
// {
//   return Deserializer::deserialization_length(object.dwLowDateTime, buffer, offset) +
//     Deserializer::deserialization_length(object.dwHighDateTime, buffer, offset);
// }
