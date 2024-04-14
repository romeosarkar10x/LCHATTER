// #include <filesystem>
// #include <iostream>

// int main()
// {
//   auto curr_path = std::filesystem::current_path();
//   std::cout << curr_path << std::endl;
//   std::cout << curr_path.root_path() << std::endl;
//   std::cout << curr_path.relative_path() << std::endl;
//   return 0;
// }
#include <windows.h>
#include <iostream>

// int main()
// {
//   char path[MAX_PATH];
//   if(GetModuleFileNameA(NULL, path, MAX_PATH) == 0)
//   {
//     std::cerr << "Error getting path" << std::endl;
//     return 1; // Return an error code
//   }
//   std::cout << "Executable Path: " << path << std::endl;
//   std::string_view str_path { path };
//   std::cout << str_path.substr(0, str_path.find_last_of("\\")) << std::endl;
//   return 0;
// }
