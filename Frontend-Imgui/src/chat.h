#ifndef CHAT_H
#define CHAT_H

#include "app_base.h"
#include <iostream>

class Chat : public AppBase<Chat>
{
public:
  Chat();
  ~Chat() = default;

  void StartUp();
  void Update();

  static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
  static void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
  static void KeyCallback(GLFWwindow *window, int key, int scancode, int actions, int mods);

private:
  void SendMessage(const char *message);
};

#endif // CHAT_H
