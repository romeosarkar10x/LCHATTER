#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <windows.h>
#include <iostream>
#include <type_traits>

#include "Traits.hpp"

class Serializer
{
  public:

  template<class T>
    using is_non_void_fundamental =
      std::__and_<
        std::is_fundamental<T>,
        std::__not_<std::is_void<T>>
      >;
  
  template<class T>
    static constexpr bool is_non_void_fundamental_v = is_non_void_fundamental<T>::value;

  template<class T>
    using is_trivially_serializable = 
      std::__or_<
        std::is_enum<T>,
        is_non_void_fundamental<T>
      >;

  template<class T>
    static constexpr bool is_trivially_serializable_v = is_trivially_serializable<T>::value;

  template<class T>
    using is_serializable_by_def = std::__and_<
      contains_method_serialize<T>,
      contains_method_serialization_length<T>
    >;

  template<class T>
    static constexpr bool is_serializable_by_def_v = is_serializable_by_def<T>::value;

  template<class T>
    using is_linear_pointer_to_serializable = std::__and_<
      is_linear_pointer<T>,
      std::__or_<is_trivially_serializable<underlying_pointer_type_t<T>>, is_serializable_by_def<underlying_pointer_type_t<T>>>
    >;
  
  template<class T>
    static constexpr bool is_linear_pointer_to_serializable_v = is_linear_pointer_to_serializable<T>::value; 

  template<class T>
    using is_bounded_linear_array_of_serializable = std::__and_<
      is_bounded_linear_array<T>,
      std::__or_<is_trivially_serializable<underlying_array_type_t<T>>, is_serializable_by_def<underlying_array_type_t<T>>>
    >;
  
  template<class T>
    static constexpr bool is_bounded_linear_array_of_serializable_v = is_bounded_linear_array_of_serializable<T>::value; 
  
  template<class T>
    using is_serializable = std::__or_<
      is_trivially_serializable<T>,
      is_serializable_by_def<T>,
      is_linear_pointer_to_serializable<T>,
      is_bounded_linear_array_of_serializable<T>
    >;
  
  template<class T>
    static constexpr bool is_serializable_v = is_serializable<T>::value;

  /// Overloads for is_non_void_fundamental_v<T>

  template<class T>
    static std::enable_if_t<is_non_void_fundamental_v<T>, void>
      serialize(const T object, char* const buffer, int& offset)
    {
      *reinterpret_cast<T*>(buffer + offset) = object;
      offset += serialization_length(object);
    }

  template<class T>
    static std::enable_if_t<is_non_void_fundamental_v<T>, int>
      serialization_length(T) { return sizeof(T); }

  /// Overloads for std::is_enum_v<T>

  template<class T>
    static std::enable_if_t<std::is_enum_v<T>, void>
      serialize(const T object, char* const buffer, int& offset)
    {
      serialize(static_cast<std::underlying_type_t<T>>(object), buffer, offset);
    }

  template<class T>
    static constexpr std::enable_if_t<std::is_enum_v<T>, int>
      serialization_length(const T object) { return serialization_length(static_cast<std::underlying_type_t<T>>(object)); }

  /// Overloads for is_linear_pointer_to_serializable_v<T>

  template<class T>
    static std::enable_if_t<is_linear_pointer_to_serializable_v<T>, void>
      serialize(const T ptr_object, int n, char* const buffer, int& offset)
    {
      for(int i = 0; i < n; i++)
      {
        serialize(ptr_object[i], buffer, offset);
      }
    }

  template<class T>
    static constexpr std::enable_if_t<is_linear_pointer_to_serializable_v<T>, int>
      serialization_length(const T ptr_object, int n)
    {
      int total_length = 0;

      for(int i = 0; i < n; i++)
      {
        total_length += serialization_length(ptr_object[i]);
      }
      
      return total_length;
    }

  /// Overloads for is_bounded_linear_array_of_serializable_v<T>

  template<class T>
    static constexpr std::enable_if_t<is_bounded_linear_array_of_serializable_v<T>, void>
      serialize(const T& array_objects, char* const buffer, int& offset)
    {
      for(int i = 0; i < underlying_array_size_v<T>; i++)
      {
        serialize(array_objects[i], buffer, offset);
      }
    }
  
  template<class T>
    static constexpr std::enable_if_t<is_bounded_linear_array_of_serializable_v<T>, int>
      serialization_length(const T& array_objects)
    {
      int total_length = 0;

      for(int i = 0; i < underlying_array_size_v<T>; i++)
      {
        total_length += serialization_length(array_objects[i]);
      }
      
      return total_length;
    }
  
  /// overloads for is_serializable_by_def_v<T>

  template<class T>
    static std::enable_if_t<is_serializable_by_def_v<T>, void> serialize(const T& object, char* const buffer, int& offset)
    { return object.serialize(buffer, offset); }

  template<class T>
    static constexpr std::enable_if_t<is_serializable_by_def_v<T>, int> serialization_length(const T& object)
    { return object.serialization_length(); }

  static void serialize(const FILETIME object, char* const buffer, int& offset);
  static int  serialization_length(const FILETIME object);

  Serializer() = delete;
  ~Serializer() = delete;
};

#endif