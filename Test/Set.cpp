#include <iostream>
#include <set>

#include "../Common/String.cpp"


int main()
{
  std::set<String> set;

  set.emplace("abc");
  set.emplace("def");
  set.emplace("xyz");
  
  for(auto s : set) { std::cout << s << " "; }

  auto itr = set.find("acc");
  if(itr == set.end()) { std::cout << "Element not found.\n"; }

  return 0;
}