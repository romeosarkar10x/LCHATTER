#include "chat.h"

Chat::Chat()
{
}

void Chat::StartUp()
{
  // Load a new font
  ImGuiIO &io = ImGui::GetIO();
  io.Fonts->AddFontFromFileTTF("./assets/fonts/helvetica-neue-5-cufonfonts/HelveticaNeueMedium.otf", 18.0f);

  // Adjust ImGui style parameters
  // ImGuiStyle &style = ImGui::GetStyle();
}

void Chat::Update()
{
  ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize); // Set window size to match GLFW window size
  ImGui::SetNextWindowPos(ImVec2(0, 0));                // Set window position to top-left corner

  ImGui::Begin("Chat App", nullptr,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove); // Begin ImGui window

  // Chat interface
  ImGui::Text("Chat Messages:");
  ImGui::Separator();

  // Example chat messages
  ImGui::Text("User1: Hello!");
  ImGui::Text("User2: Hi there!");
  ImGui::Text("User1: How are you?");
  ImGui::Text("User2: I'm doing well, thanks!");

  ImGui::Separator();

  // Chat input
  static char inputBuffer[256] = ""; // Buffer for user input
  if (ImGui::InputText("##ChatInput", inputBuffer, IM_ARRAYSIZE(inputBuffer), ImGuiInputTextFlags_EnterReturnsTrue))
  {
    // Enter key pressed, send the message
    SendMessage(inputBuffer);
    // Clear the input buffer
    memset(inputBuffer, 0, sizeof(inputBuffer));
  }

  // Set focus to the input field
  ImGui::SetKeyboardFocusHere(-1);

  ImGui::End(); // End ImGui window
}

// The callbacks are updated and called BEFORE the Update loop is entered
// It can be assumed that inside the Update loop all callbacks have already been processed
void Chat::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
  // For Dear ImGui to work it is necessary to queue if the mouse signal is already processed by Dear ImGui
  // Only if the mouse is not already captured it should be used here.
  ImGuiIO &io = ImGui::GetIO();
  if (!io.WantCaptureMouse)
  {
  }
}

void Chat::CursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
  // For Dear ImGui to work it is necessary to queue if the mouse signal is already processed by Dear ImGui
  // Only if the mouse is not already captured it should be used here.
  ImGuiIO &io = ImGui::GetIO();
  if (!io.WantCaptureMouse)
  {
  }
}

void Chat::KeyCallback(GLFWwindow *window, int key, int scancode, int actions, int mods)
{
  // For Dear ImGui to work it is necessary to queue if the keyboard signal is already processed by Dear ImGui
  // Only if the keyboard is not already captured it should be used here.
  ImGuiIO &io = ImGui::GetIO();
  if (!io.WantCaptureKeyboard)
  {
  }
}

void Chat::SendMessage(const char *message)
{
  // Placeholder for sending a message
  std::cout << "Sending message: " << message << std::endl;
}