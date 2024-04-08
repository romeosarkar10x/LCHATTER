#include <iostream>
#include <type_traits>

#include "../../Inc/File/Serializer.hpp"

void Serializer::serialize(const FILETIME object, char* const buffer, int& offset)
{
  Serializer::serialize(object.dwLowDateTime, buffer, offset);
  Serializer::serialize(object.dwHighDateTime, buffer, offset);
}

int Serializer::serialization_length(const FILETIME object)
{
  return Serializer::serialization_length(object.dwLowDateTime) + 
    Serializer::serialization_length(object.dwHighDateTime);
}

// int main()
// {
//   int arr[] = { 2, 3, 4, 5 };
  
//   char* buffer = reinterpret_cast<char*>(arr);
//   int offset = 0;

//   Serializer::serialize(4, buffer, offset);
//   Serializer::serialize(5, buffer, offset);
//   Serializer::serialize(6, buffer, offset);
//   Serializer::serialize(7, buffer, offset);

//   for(int i = 0; i < 4; i++)
//   {
//     std::cout << arr[i] << " ";
//   }

//   std::cout << std::endl;

//   return 0;
// }