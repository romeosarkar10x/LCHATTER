#include "chat.hpp"

// Sample names - expand as needed
std::vector<std::string> contactNames = {"Emily", "John", "Sarah", "Michael", "Alice", "David", "Bob", "Lisa"};

// Generates 20 dummy contacts and conversations
std::vector<Conversation> generateDummyData()
{
  std::vector<Conversation> conversations;
  std::random_device rd;
  std::mt19937 rng(rd());

  for (int i = 0; i < static_cast<int>(contactNames.size()); ++i)
  {
    Conversation conv;
    conv.contactName = contactNames[i];

    // Generate some random messages
    int numMessages = rng() % 5 + 2; // Between 2 to 7 messages
    for (int j = 0; j < numMessages; ++j)
    {
      Message msg;
      msg.sender = (rng() % 2 == 0) ? "You" : conv.contactName; // Alternate sender
      msg.content = "Sample Message " + std::to_string(j + 1);
      msg.timestamp = time(nullptr) - (rng() % 864000); // Within the last 10 days
      conv.messages.push_back(msg);
    }

    conversations.push_back(conv);
  }

  return conversations;
}

Chat::Chat()
{
}

void Chat::StartUp()
{
  // Load a new font
  ImGuiIO &io = ImGui::GetIO();
  io.Fonts->AddFontFromFileTTF("assets/fonts/CascadiaCode/CaskaydiaCoveNerdFont-Regular.ttf", 18.0f);

  // Adjust ImGui style parameters
  // ImGuiStyle &style = ImGui::GetStyle();

  conversations = generateDummyData();
}

void Chat::Update()
{
  bool show_demo_window = true;
  if (show_demo_window)
  {
    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
    ImGui::ShowDemoWindow(&show_demo_window);
  }
}

// The callbacks are updated and called BEFORE the Update loop is entered
// It can be assumed that inside the Update loop all callbacks have already been
// processed
void Chat::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
  // For Dear ImGui to work it is necessary to queue if the mouse signal is
  // already processed by Dear ImGui Only if the mouse is not already captured
  // it should be used here.
  ImGuiIO &io = ImGui::GetIO();
  if (!io.WantCaptureMouse)
  {
  }
}

void Chat::CursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
  // For Dear ImGui to work it is necessary to queue if the mouse signal is
  // already processed by Dear ImGui Only if the mouse is not already captured
  // it should be used here.
  ImGuiIO &io = ImGui::GetIO();
  if (!io.WantCaptureMouse)
  {
  }
}

void Chat::KeyCallback(GLFWwindow *window, int key, int scancode, int actions, int mods)
{
  // For Dear ImGui to work it is necessary to queue if the keyboard signal is
  // already processed by Dear ImGui Only if the keyboard is not already
  // captured it should be used here.
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
