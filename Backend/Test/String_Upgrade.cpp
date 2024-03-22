#include <iostream>
#include "../Common/String.cpp"
#include "../../Externals/trace_bytes/trace_bytes.hpp"


int main()
{
  String s { "12" }, s2 { "34" }, s3 { "abcde" }, s4 { "pqrst" }, s5 { "@#!!2212&&&&****" };

  std::cout << " s: " <<  s << std::endl;
  std::cout << "s2: " << s2 << std::endl;
  std::cout << "s3: " << s3 << std::endl;
  std::cout << "s4: " << s4 << std::endl;
  std::cout << "s5: " << s5 << std::endl;
  
  std::cout << "s + s2: " << s << " + " << s2 << ": " << s + s2 << std::endl; 
  std::cout << "s + s3: " << s << " + " << s3 << ": " << s + s3 << std::endl;
  std::cout << "s + s5: " << s << " + " << s5 << ": " << s + s5 << std::endl;

  std::cout << "s3 + s4: " << s3 << " + " << s4 << ": " << s3 + s4 << std::endl;
  std::cout << "s3 + s5: " << s3 << " + " << s5 << ": " << s3 + s5 << std::endl;

  std::cout << "s5 + s5: " << s5 << " + " << s5 << ": " << s5 + s5 << std::endl;

  std::cout << "s + s2 + s2: " << s << " + " << s2 << " + " << s2 << ": " << s + s2 + s2 << std::endl;
  std::cout << "s + s2 + s2 + s: " << s << " + " << s2 << " + " << s2 << " + " << s << ": " << s + s2 + s2 + s << std::endl;


  std::cout << "s + \"***\": " << s << " + " << "\"***\"" << ": " << s + "***" << std::endl;
  std::cout << "s + s + \"****\": " << s << " + " << s << " + " << "\"****\"" << ": " << s + s + "****" << std::endl;
  
  std::cout << "\"**\" + s : " << "\"**\" + " <<  s << ": " << "**" +  s << std::endl;
  std::cout << "\"**\" + s3: " << "\"**\" + " << s3 << ": " << "**" + s3 << std::endl;
  std::cout << "\"**\" + s5: " << "\"**\" + " << s5 << ": " << "**" + s5 << std::endl;

  /// serialization-deserialization
  char* buffer = new char [64];
  
  std::cout << "serialization_length: " << s5.serialize(buffer) << std::endl;
  Memory::trace_bytes(buffer, 64, 32);

  String s6 { s4 };
  std::cout << "s6: " << s6 << std::endl;
  
  s6.deserialize(buffer);
  std::cout << "s6: " << s6 << std::endl;

  std::cout << "s6 + s6: " << s6 << " + " << s6 << ": " << s6 + s6 << std::endl;

  /// logical operators
  std::cout << "(s < s2): (" << s << " < " << s2 << "): " << (s < s2) << std::endl;
  std::cout << "(s < s3): (" << s << " < " << s3 << "): " << (s < s3) << std::endl;
  std::cout << "(s < s5): (" << s << " < " << s5 << "): " << (s < s5) << std::endl;

  std::cout << "(s4 < s5): (" << s4 << " < " << s5 << "): " << (s4 < s5) << std::endl;
  std::cout << "(s4 < s6): (" << s4 << " < " << s6 << "): " << (s4 < s6) << std::endl;
  std::cout << "(s5 < s6): (" << s5 << " < " << s6 << "): " << (s5 < s6) << std::endl;
  std::cout << "(s6 < s6): (" << s6 << " < " << s6 << "): " << (s6 < s6) << std::endl;

  return 0;
}