#ifndef APPBASE_H
#define APPBASE_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <stdio.h>

void ErrorCallback(int error, const char *description);

template <typename Derived> class AppBase
{
public:
  AppBase();
  virtual ~AppBase();
  void Run();
  void Update();
  void StartUp();

private:
  GLFWwindow *window = nullptr;
  ImVec4 clear_color = ImVec4(0.1058, 0.1137f, 0.1255f, 1.00f);
};

#endif // APPBASE_H
