#ifndef CHAT_H
#define CHAT_H

#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "app_base.hpp"

// Structure for a single message
struct Message {
  std::string sender;
  std::string content;
  time_t timestamp;
};

// Structure for a conversation
struct Conversation {
  std::string contactName;  // Or contact ID if you have one
  std::vector<Message> messages;
};

class Chat : public AppBase<Chat> {
 public:
  Chat();
  ~Chat() = default;

  void StartUp();
  void Update();

  static void MouseButtonCallback(GLFWwindow *window, int button, int action,
                                  int mods);
  static void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
  static void KeyCallback(GLFWwindow *window, int key, int scancode,
                          int actions, int mods);

 private:
  void SendMessage(const char *message);
  std::vector<Conversation> conversations;
  int selectedConversationIndex = -1;
};

#endif  // CHAT_H
