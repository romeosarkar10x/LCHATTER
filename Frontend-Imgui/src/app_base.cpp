#include "app_base.hpp"

void ErrorCallback(int error, const char *description)
{
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
