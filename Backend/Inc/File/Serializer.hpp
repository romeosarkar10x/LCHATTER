#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <windows.h>
#include <vector>

#include "Trait.hpp"

class Serializer
{

  public:
  template<class T>
    using is_trivially_serializable = std::disjunction<
      std::is_enum<T>,
      std::is_arithmetic<T>
    >;

  template<class T>
    static constexpr bool is_trivially_serializable_v = is_trivially_serializable<T>::value;

  template<class T>
    using is_serializable_by_def = std::conjunction<
      contains_method_serialize<T>,
      contains_method_serialization_length<T>
    >;

  template<class T>
    static constexpr bool is_serializable_by_def_v = is_serializable_by_def<T>::value;
  
  template<class T>
    using is_primarily_serializable = std::disjunction<
      is_trivially_serializable<T>,
      is_serializable_by_def<T>
    >;
  
  template<class T>
    static constexpr bool is_primarily_serializable_v = is_primarily_serializable<T>::value;

  template<class T>
    using is_linear_pointer_to_serializable = std::conjunction<
      is_linear_pointer<T>,
      is_primarily_serializable<underlying_pointer_type_t<T>>
    >;
  
  template<class T>
    static constexpr bool is_linear_pointer_to_serializable_v = is_linear_pointer_to_serializable<T>::value; 

  template<class T>
    using is_bounded_linear_array_of_serializable = std::conjunction<
      is_bounded_linear_array<T>,
      is_primarily_serializable<underlying_array_type_t<T>>
    >;
  
  template<class T>
    static constexpr bool is_bounded_linear_array_of_serializable_v = is_bounded_linear_array_of_serializable<T>::value; 
  
  template<class T>
    using is_serializable = std::disjunction<
      is_primarily_serializable<T>,
      is_linear_pointer_to_serializable<T>,
      is_bounded_linear_array_of_serializable<T>
    >;
  
  template<class T>
    static constexpr bool is_serializable_v = is_serializable<T>::value;

  /// Overloads for std::is_arithmetic_v<T>

  template<class T>
    static std::enable_if_t<std::is_arithmetic_v<T>, void>
      serialize(const T object, char* const buffer, u_int& offset)
    {
      *reinterpret_cast<T*>(buffer + offset) = object;
      offset += serialization_length(object);
    }

  template<class T>
    static std::enable_if_t<std::is_arithmetic_v<T>, u_int>
      serialization_length(T)
    { return sizeof(T); }

  /// Overloads for std::is_enum_v<T>

  template<class T>
    static std::enable_if_t<std::is_enum_v<T>, void>
      serialize(const T object, char* const buffer, u_int& offset)
    { serialize(static_cast<std::underlying_type_t<T>>(object), buffer, offset); }

  template<class T>
    static constexpr std::enable_if_t<std::is_enum_v<T>, u_int>
      serialization_length(const T object)
    { return serialization_length(static_cast<std::underlying_type_t<T>>(object)); }

  /// overloads for is_serializable_by_def_v<T>

  template<class T>
    static std::enable_if_t<is_serializable_by_def_v<T>, void>
      serialize(const T& object, char* const buffer, u_int& offset)
    { object.serialize(buffer, offset); }
  
  template<class T>
    static std::enable_if_t<is_serializable_by_def_v<T>, void>
      serialize_nv(const T& object, char* const buffer, u_int& offset)
    { object.T::serialize(buffer, offset); }

  template<class T>
    static constexpr std::enable_if_t<is_serializable_by_def_v<T>, u_int> serialization_length(const T& object)
    { return object.serialization_length(); }

  template<class T>
    static constexpr std::enable_if_t<is_serializable_by_def_v<T>, u_int> serialization_length_nv(const T& object)
    { return object.T::serialization_length(); }

  /// Overloads for is_linear_pointer_to_serializable_v<T>

  template<class T>
    static std::enable_if_t<is_linear_pointer_to_serializable_v<T>, void>
      serialize(const T ptr_object, u_int n, char* const buffer, u_int& offset)
    {
      for(u_int index = 0U; index < n; index++)
      {
        serialize(ptr_object[index], buffer, offset);
      }
    }

  template<class T>
    static constexpr std::enable_if_t<is_linear_pointer_to_serializable_v<T>, u_int>
      serialization_length(const T ptr_object, u_int n)
    {
      u_int total_length = 0U;

      for(u_int index = 0U; index < n; index++)
      {
        total_length += serialization_length(ptr_object[index]);
      }
      
      return total_length;
    }

  /// Overloads for is_bounded_linear_array_of_serializable_v<T>

  template<class T>
    static constexpr std::enable_if_t<is_bounded_linear_array_of_serializable_v<T>, void>
      serialize(const T& array_objects, char* const buffer, u_int& offset)
    {
      for(u_int index = 0U; index < underlying_array_size_v<T>; index++)
      {
        serialize(array_objects[index], buffer, offset);
      }
    }
  
  template<class T>
    static constexpr std::enable_if_t<is_bounded_linear_array_of_serializable_v<T>, u_int>
      serialization_length(const T& array_objects)
    {
      u_int total_length = 0U;

      for(u_int index = 0U; index < underlying_array_size_v<T>; index++)
      {
        total_length += serialization_length(array_objects[index]);
      }
      
      return total_length;
    }
  
  /// Overloads for std::vector<T> [where is_primarily_serializable<T> = true]

  template<class T>
    static std::enable_if_t<is_primarily_serializable_v<T>, void>
      serialize(const std::vector<T>& vector_objects, char* const buffer, u_int& offset)
    {
      serialize(vector_objects.size(), buffer, offset);
      
      for(size_t index = 0U; index < vector_objects.size(); index++)
      {
        serialize(vector_objects[index], buffer, offset);
      }
    }

  template<class T>
    static std::enable_if_t<is_primarily_serializable_v<T>, u_int>
      serialization_length(const std::vector<T>& vector_objects)
    {
      u_int total_length = 0U;

      for(size_t index = 0U; index < vector_objects.size(); index++)
      {
        total_length += serialization_length(vector_objects[index]);
      }

      return total_length;
    }

  static void serialize(const FILETIME object, char* const buffer, u_int& offset);
  static u_int serialization_length(const FILETIME object);

  Serializer() = delete;
  ~Serializer() = delete;
};

#endif