#ifndef CHAT_H
#define CHAT_H

#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "App_Base.cpp"

// /*
// Structure for a single message
struct Message
{
  std::string sender;
  std::string content;
  time_t timestamp;
};

// Structure for a conversation
struct Conversation
{
  std::string contactName; // Or contact ID if you have one
  std::vector<Message> messages;
};

struct ConnectionRequest
{
  std::string username;
};

class App : public App_Base<App>
{
public:
  App();
  ~App() = default;

  void StartUp();
  void Update();

  static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
  static void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
  static void KeyCallback(GLFWwindow *window, int key, int scancode, int actions, int mods);

private:
  void SendMessage(const char *message);
  void ShowLoginWindow();
  void ShowChatWindow();
  void AddConnectionWindow();
  void ShowConnectionRequestWindow();

  // std::vector<Conversation> conversations;
  int selectedConversationIndex = -1;
  int selectedRequestIndex = -1;
  ImFont *h1Font, *h2Font;
  ImGuiWindowFlags mainWindowFlag;
};

// /*
// int isLoggedIn = false,
bool showAddConnectionForm = false;
bool showConnectionRequestWindow = false;
std::vector<std::string> contactNames = {"Emily", "John", "Sarah", "Michael", "Alice", "David", "Bob", "Lisa"};

// Generates 20 dummy contacts and conversations
std::vector<Conversation> conversations;
std::vector<ConnectionRequest> outgoingRequests;
std::vector<ConnectionRequest> incomingRequests;

void generateDummyData()
{
  std::random_device rd;
  std::mt19937 rng(rd());

  for (int i = 0; i < static_cast<int>(contactNames.size()); ++i)
  {
    ConnectionRequest tmp;
    tmp.username = contactNames[i];
    incomingRequests.push_back(tmp);

    Conversation conv;
    conv.contactName = contactNames[i];

    // Generate some random messages
    int numMessages = rng() % 20 + 2; // Between 2 to 7 messages
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

  // return conversations;
}
// */

void TextWithAlignment(const char *text, ImVec2 alignment = ImVec2(0, 0), float y_padding = 0.0f,
                       ImColor color = ImColor(255, 255, 255))
{
  ImVec2 padding = ImGui::GetStyle().WindowPadding;
  ImVec2 itemSpacing = ImGui::GetStyle().ItemSpacing;

  // Calculate the size without padding and item spacing
  ImVec2 windowSize = ImGui::GetContentRegionAvail();
  // std::cout << text << std::endl;
  // std::cout << windowSize.x << " " << windowSize.y << std::endl;
  // windowSize.x -= (padding.x);                 // Subtract padding from both sides
  // windowSize.y -= (padding.y * 2) + itemSpacing.y; // Subtract padding from top and bottom and item spacing
  const ImVec2 text_size = ImGui::CalcTextSize(text);
  float textHeight = ImGui::GetTextLineHeightWithSpacing();

  // ImVec2 windowSize = ImGui::GetContentRegionAvail();

  if (alignment.x == 0) // Left aligned
  {
    // Do nothing
  }
  else if (alignment.x == 1) // Center aligned
  {
    ImGui::SameLine((windowSize.x / 2) - (text_size.x / 2));
  }
  else if (alignment.x == 2) // Right aligned
  {
    ImGui::SameLine(windowSize.x - text_size.x);
  }

  if (alignment.y == 0) // Top aligned
  {
    // Do nothing
  }
  else if (alignment.y == 1) // Center aligned
  {
    ImGui::SetCursorPosY((ImGui::GetCursorPosY() + windowSize.y) / 2 - textHeight);
  }
  else if (alignment.y == 2) // Bottom aligned
  {
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + windowSize.y - textHeight);
  }

  if (y_padding > 0.0f)
  {
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + y_padding);
  }
  ImGui::TextColored(color, text);
}

App::App()
{
}

void App::StartUp()
{
  // Load a new font
  ImGuiIO &io = ImGui::GetIO();
  io.Fonts->AddFontFromFileTTF("assets/fonts/CascadiaCode/CaskaydiaCoveNerdFont-Regular.ttf", 24.0f);
  h1Font = io.Fonts->AddFontFromFileTTF("assets/fonts/Noto_Sans/NotoSans-VariableFont_wdth,wght.ttf", 48.0f);
  h2Font = io.Fonts->AddFontFromFileTTF("assets/fonts/Noto_Sans/NotoSans-VariableFont_wdth,wght.ttf", 32.0f);

  // Adjust ImGui style parameters
  // ImGuiStyle &style = ImGui::GetStyle();

  generateDummyData();
}

void App::Update()
{
  mainWindowFlag = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings |
                   ImGuiWindowFlags_NoBringToFrontOnFocus;

  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);

  // Turn off padding for the child window
  // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  // ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

  if (AppBackend::get_state() == AppBackend::State::NOT_LOGGED_IN)
  {
    ShowLoginWindow();
  }
  else
  {
    ShowChatWindow();
  }

  // Don't forget to pop the style variable to reset the padding back to default for subsequent windows
  // ImGui::PopStyleVar(2);

  // ImGui::ShowDemoWindow();
}

// The callbacks are updated and called BEFORE the Update loop is entered
// It can be assumed that inside the Update loop all callbacks have already been
// processed
void App::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
  // For Dear ImGui to work it is necessary to queue if the mouse signal is
  // already processed by Dear ImGui Only if the mouse is not already captured
  // it should be used here.
  ImGuiIO &io = ImGui::GetIO();
  if (!io.WantCaptureMouse)
  {
  }
}

void App::CursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
  // For Dear ImGui to work it is necessary to queue if the mouse signal is
  // already processed by Dear ImGui Only if the mouse is not already captured
  // it should be used here.
  ImGuiIO &io = ImGui::GetIO();
  if (!io.WantCaptureMouse)
  {
  }
}

void App::KeyCallback(GLFWwindow *window, int key, int scancode, int actions, int mods)
{
  // For Dear ImGui to work it is necessary to queue if the keyboard signal is
  // already processed by Dear ImGui Only if the keyboard is not already
  // captured it should be used here.
  ImGuiIO &io = ImGui::GetIO();
  if (!io.WantCaptureKeyboard)
  {
  }
}

void App::SendMessage(const char *message)
{
  // Placeholder for sending a message
  std::cout << "Sending message: " << message << std::endl;
}

void App::ShowLoginWindow()
{
  if (ImGui::Begin("MainWindow", nullptr, mainWindowFlag))
  {
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    ImVec2 childWindowSize = ImVec2(400, 220);

    ImGui::SetCursorPos(ImVec2((windowSize.x - childWindowSize.x) / 2, (windowSize.y - childWindowSize.y) / 2));

    // Login Child Window
    {
      ImGui::BeginChild("ShowLoginWindow", childWindowSize);

      ImGui::InputText("Username", AppBackend::get_buffer_username(), AppBackend::buffer_username_length);
      ImGui::InputText("Password", AppBackend::get_buffer_psw(), AppBackend::buffer_psw_length,
                       ImGuiInputTextFlags_Password);

      // static char username[128] = "";
      // static char password[128] = "";

      // ImGui::InputText("Username", username, IM_ARRAYSIZE(username));
      // ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

      if (ImGui::Button("Log In"))
      {
        // isLoggedIn = true;
        AppBackend::set_event(Event::LOGIN);
      }
      if (ImGui::Button("Log in anonymous user"))
      {
        // isLoggedIn = true;
        AppBackend::set_event(Event::LOGIN_ANONYMOUS);
      }
    }
    ImGui::EndChild();
  }
  ImGui::End();
}
void App::AddConnectionWindow()
{
  // static char IP[128] = "";
  // static char PORT[128] = "";
  // ImGui::InputText("IP Addr", IP, IM_ARRAYSIZE(IP));
  // ImGui::InputText("PORT", PORT, IM_ARRAYSIZE(PORT));

  ImGui::InputText("IP Addr", AppBackend::get_buffer_ip_address(), AppBackend::buffer_ip_address_length);
  ImGui::InputText("PORT", AppBackend::get_buffer_port(), AppBackend::buffer_port_length);

  if (ImGui::Button("Connect"))
  {
    showAddConnectionForm = false;
    AppBackend::set_event(Event::CONNECT);
    // isLoggedIn = true;
  }
}

void App::ShowConnectionRequestWindow()
{
  // Set the fixed width for the window and let ImGui determine the height dynamically
  ImGui::SetNextWindowSize(ImVec2(600, 0), ImGuiCond_Always);

  ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.10f, 0.10f, 0.14f, 1.0f)); // Dark background
  ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.23f, 0.23f, 0.29f, 1.0f));      // Slightly lighter for tab backgrounds
  ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4(0.4f, 0.4f, 0.8f, 1.0f));  // Purple for hovered tabs
  ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(0.3f, 0.3f, 0.6f, 1.0f));   // Darker purple for active tabs

  if (ImGui::Begin("Connection Requests", &showConnectionRequestWindow))
  {

    if (ImGui::BeginTabBar("RequestsTabBar"))
    {
      if (ImGui::BeginTabItem("Incoming Requests"))
      {

        for (int i = 0; i < (int)incomingRequests.size(); ++i)
        {
          ImGui::PushID(i);

          if (ImGui::Selectable(incomingRequests[i].username.c_str(), selectedRequestIndex == i))
          {
            selectedRequestIndex = (selectedRequestIndex == i) ? -1 : i;
          }

          if (selectedRequestIndex == i)
          {
            if (ImGui::Button("Accept"))
            {
              // AcceptConnectionRequest(incomingRequests[i]);
              selectedRequestIndex = -1;
            }
            ImGui::SameLine();
            if (ImGui::Button("Decline"))
            {
              // DeclineConnectionRequest(incomingRequests[i]);
              selectedRequestIndex = -1;
            }
          }

          ImGui::PopID();
        }

        if (incomingRequests.empty())
        {
          ImGui::Text("No incoming requests.");
        }

        ImGui::EndTabItem();
      }

      if (ImGui::BeginTabItem("Outgoing Requests"))
      {
        for (int i = 0; i < (int)outgoingRequests.size(); ++i)
        {
          ImGui::PushID(i);

          if (ImGui::Selectable(outgoingRequests[i].username.c_str(), selectedRequestIndex == i))
          {
            selectedRequestIndex = (selectedRequestIndex == i) ? -1 : i;
          }

          if (selectedRequestIndex == i)
          {
            if (ImGui::Button("Accept"))
            {
              // AcceptConnectionRequest(outgoingRequests[i]);
              selectedRequestIndex = -1;
            }
            ImGui::SameLine();
            if (ImGui::Button("Decline"))
            {
              // DeclineConnectionRequest(outgoingRequests[i]);
              selectedRequestIndex = -1;
            }
          }

          ImGui::PopID();
        }

        if (outgoingRequests.empty())
        {
          ImGui::Text("No outgoing requests.");
        }

        ImGui::EndTabItem();
      }

      ImGui::EndTabBar();
    }
  }

  ImGui::End();

  // Pop all
  ImGui::PopStyleColor(4);
}

void App::ShowChatWindow()
{
  if (ImGui::Begin("MainWindow", nullptr, mainWindowFlag))
  {
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    float leftWidth = windowSize.x * 0.3f;  // 30% for contacts
    float rightWidth = windowSize.x * 0.7f; // 70% for chats

    // Left
    {
      ImGui::BeginChild("LeftParent", ImVec2(leftWidth, windowSize.y));

      ImGui::Text("username");
      if (ImGui::Button("Add New Connection"))
      {
        showAddConnectionForm = !showAddConnectionForm;
      }
      ImGui::SameLine();
      if (ImGui::Button("Connection Requests"))
      {
        showConnectionRequestWindow = !showConnectionRequestWindow;
      }
      if (showConnectionRequestWindow)
      {
        ShowConnectionRequestWindow();
      }
      if (showAddConnectionForm)
      {
        AddConnectionWindow();
      }
      ImGui::Separator();
      ImGui::PushFont(h2Font);
      ImGui::Text("Connections");
      ImGui::PopFont();
      ImGui::Separator();

      /*
      int i = 0;
      for (auto &connection : AppBackend::connections())
      {
        if (ImGui::Selectable(connection.user().name(), i == selectedConversationIndex))
        {
          selectedConversationIndex = i;
        }
        i++;
      }
      */

      for (int i = 0; i < static_cast<int>(conversations.size()); ++i)
      {
        if (ImGui::Selectable(conversations[i].contactName.c_str(), i == selectedConversationIndex))
        {
          selectedConversationIndex = i;
        }
      }
      ImGui::EndChild();
    }
    ImGui::SameLine();

    // Right
    {
      // ImGui::BeginGroup();
      ImGui::BeginChild("RightParent", ImVec2(rightWidth, windowSize.y));
      if (selectedConversationIndex == -1)
      {
        TextWithAlignment("Select a chat to start messaging", ImVec2(1, 1));
      }
      else
      {
        const Conversation &selectedConvo = conversations[selectedConversationIndex];

        ImGui::PushFont(h1Font);
        ImGui::Text("%s", selectedConvo.contactName.c_str());
        ImGui::PopFont();

        ImGui::Separator();
        if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
        {
          if (ImGui::BeginTabItem("Chats"))
          {
            for (const Message &msg : selectedConvo.messages)
            {
              ImGui::Text(msg.content.c_str());
            }
            ImGui::EndTabItem();
          }
          if (ImGui::BeginTabItem("Details"))
          {
            ImGui::Text("ID: 0123456789");
            ImGui::EndTabItem();
          }
          ImGui::EndTabBar();
        }
        // /*
        // ImVec2 windowSize = ImGui::GetContentRegionAvail();
        // ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 300);
        ImGui::Separator();

        static char messageBuffer[10000] = "";
        bool reclaim_focus = false;
        ImGuiInputTextFlags input_text_flags =
            ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll |
            ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
        // Used "##messageInputBox" to hide the label but ensure a unique ID
        if (ImGui::InputText(
                "##messageInputBox", messageBuffer, IM_ARRAYSIZE(messageBuffer), input_text_flags,
                [](ImGuiInputTextCallbackData *data) -> int { return 0; }, (void *)this))
        {
          reclaim_focus = true;
        }

        // Auto-focus on window apparition
        ImGui::SetItemDefaultFocus();
        if (reclaim_focus)
        {
          ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
        }
        ImGui::SameLine();

        // Adjust the size of the Send button
        ImGui::Button("Send");
        // */
      }
      ImGui::EndChild();
      // ImGui::EndGroup();
    }
  }
  ImGui::End();
}

#endif // CHAT_H