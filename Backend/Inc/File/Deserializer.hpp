#ifndef DESERIALIZER_HPP
#define DESERIALIZER_HPP

#include <vector>

#include <windows.h>

#include "Trait.hpp"

class Deserializer
{

  public:
  template<class T>
    using is_trivially_deserializable = std::disjunction<
      std::is_enum<T>,
      std::is_arithmetic<T>
    >;

  template<class T>
    static constexpr bool is_trivially_deserializable_v = is_trivially_deserializable<T>::value;

  template<class T>
    using is_deserializable_by_def = contains_method_deserialize<T>;
      
      // contains_method_deserialization_length<T>
    // >;

  template<class T>
    static constexpr bool is_deserializable_by_def_v = is_deserializable_by_def<T>::value;
  
  template<class T>
    using is_primarily_deserializable = std::disjunction<
      is_trivially_deserializable<T>,
      is_deserializable_by_def<T>
    >;
  
  template<class T>
    static constexpr bool is_primarily_deserializable_v = is_primarily_deserializable<T>::value;

  template<class T>
    using is_linear_pointer_to_deserializable = std::conjunction<
      is_linear_pointer<T>,
      is_primarily_deserializable<underlying_pointer_type_t<T>>
    >;
  
  template<class T>
    static constexpr bool is_linear_pointer_to_deserializable_v = is_linear_pointer_to_deserializable<T>::value; 

  template<class T>
    using is_bounded_linear_array_of_deserializable = std::conjunction<
      is_bounded_linear_array<T>,
      is_primarily_deserializable<underlying_array_type_t<T>>
    >;
  
  template<class T>
    static constexpr bool is_bounded_linear_array_of_deserializable_v = is_bounded_linear_array_of_deserializable<T>::value; 
  
  template<class T>
    using is_deserializable = std::disjunction<
      is_primarily_deserializable<T>,
      is_linear_pointer_to_deserializable<T>,
      is_bounded_linear_array_of_deserializable<T>
    >;
  
  template<class T>
    static constexpr bool is_deserializable_v = is_deserializable<T>::value;

  /// Overloads for std::is_arithmetic_v<T>

  template<class T>
    static std::enable_if_t<std::is_arithmetic_v<T>, void>
      deserialize(T& object, const char* const buffer, u_int& offset)
    {
      object = *reinterpret_cast<const T*>(buffer + offset);
      offset += sizeof(T);
    }

  // template<class T>
  //   [[ nodiscard ]] static std::enable_if_t<std::is_arithmetic_v<T>, u_int>
  //     deserialization_length(const T, const char*, u_int& offset)
  //   {
  //     offset += sizeof(T);
  //     return sizeof(T);
  //   }

  /// Overloads for std::is_enum_v<T>

  template<class T>
    static std::enable_if_t<std::is_enum_v<T>, void>
      deserialize(T& object, const char* const buffer, u_int& offset)
    { deserialize(reinterpret_cast<std::underlying_type_t<T>&>(object), buffer, offset); }

  // template<class T>
  //   [[ nodiscard ]] static std::enable_if_t<std::is_enum_v<T>, u_int>
  //     deserialization_length(const T object, const char* const buffer, u_int& offset)
  //   { return deserialization_length(static_cast<std::underlying_type_t<T>>(object), buffer, offset); }

  /// Overloads for is_deserializable_by_def_v<T>

  template<class T>
    static std::enable_if_t<is_deserializable_by_def_v<T>, void>
      deserialize(T& object, const char* const buffer, u_int& offset)
    { return object.deserialize(buffer, offset); }

  template<class T>
    static std::enable_if_t<is_deserializable_by_def_v<T>, void>
      deserialize_nv(T& object, const char* const buffer, u_int& offset)
    { return object.T::deserialize(buffer, offset); }

  // template<class T>
  //   [[ nodiscard ]] static std::enable_if_t<is_deserializable_by_def_v<T>, u_int> deserialization_length
  //     (const T& object, const char* const buffer, u_int& offset)
  //   { return object.deserialization_length(buffer, offset); }

  /// Overloads for is_linear_pointer_to_deserializable_v<T>

  template<class T>
    static std::enable_if_t<is_linear_pointer_to_deserializable_v<T>, void>
      deserialize(T ptr_object, u_int n, const char* const buffer, u_int& offset)
    {
      for(u_int index = 0U; index < n; index++)
      {
        deserialize(ptr_object[index], buffer, offset);
      }
    }

  // template<class T>
  //   [[ nodiscard ]] static std::enable_if_t<is_linear_pointer_to_deserializable_v<T>, u_int>
  //     deserialization_length(const T ptr_object, u_int n, const char* const buffer, u_int& offset)
  //   {
  //     u_int total_length = 0U;

  //     for(u_int index = 0U; index < n; index++)
  //     {
  //       total_length += deserialization_length(ptr_object[index], buffer, offset);
  //     }
      
  //     return total_length;
  //   }

  /// Overloads for is_bounded_linear_array_of_deserializable_v<T>

  template<class T>
    static std::enable_if_t<is_bounded_linear_array_of_deserializable_v<T>, void>
      deserialize(T& array_objects, const char* const buffer, u_int& offset)
    {
      for(u_int index = 0U; index < underlying_array_size_v<T>; index++)
      {
        deserialize(array_objects[index], buffer, offset);
      }
    }
  
  // template<class T>
  //   [[ nodiscard ]] static std::enable_if_t<is_bounded_linear_array_of_deserializable_v<T>, u_int>
  //     deserialization_length(const T& array_objects, const char* const buffer, u_int& offset)
  //   {
  //     u_int total_length = 0U;

  //     for(u_int index = 0U; index < underlying_array_size_v<T>; index++)
  //     {
  //       total_length += deserialization_length(array_objects[index], buffer, offset);
  //     }
      
  //     return total_length;
  //   }
  
  // /// Overloads for std::vector<T> [where is_primarily_deserializable<T> = true]

  template<class T>
    static std::enable_if_t<is_primarily_deserializable_v<T>, void>
      deserialize(std::vector<T>& vector_objects, const char* const buffer, u_int& offset)
    {
      vector_objects.clear();

      typename std::vector<T>::size_type size;
      deserialize(size, buffer, offset);

      vector_objects.resize(size);

      for(size_t index = 0U; index < size; index++)
      {
        deserialize(vector_objects[index], buffer, offset);
      }
    }

  static void deserialize(FILETIME& object, const char* buffer, u_int& offset);
  // static u_int deserialization_length(FILETIME object, const char* buffer, u_int& offset);

  Deserializer() = delete;
  ~Deserializer() = delete;
};

#endif