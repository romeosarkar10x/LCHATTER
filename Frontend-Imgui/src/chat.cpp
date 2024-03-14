#include "chat.hpp"

int isLoggedIn = false;
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

void CenterText(const char *text, float y_padding = 0.0f, ImColor color = ImColor(255, 255, 255))
{
  const ImVec2 text_size = ImGui::CalcTextSize(text);
  float textHeight = ImGui::GetTextLineHeightWithSpacing();

  ImVec2 windowSize = ImGui::GetContentRegionAvail();
  ImGui::SameLine((windowSize.x / 2) - (text_size.x / 2));
  ImGui::SetCursorPosY((ImGui::GetCursorPosY() + windowSize.y) / 2 - textHeight);

  if (y_padding > 0.0f)
  {
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + y_padding);
  }
  ImGui::TextColored(color, text);
}

Chat::Chat()
{
}

void Chat::StartUp()
{
  // Load a new font
  ImGuiIO &io = ImGui::GetIO();
  io.Fonts->AddFontFromFileTTF("assets/fonts/CascadiaCode/CaskaydiaCoveNerdFont-Regular.ttf", 24.0f);
  headingFont = io.Fonts->AddFontFromFileTTF("assets/fonts/Noto_Sans/NotoSans-VariableFont_wdth,wght.ttf", 48.0f);

  // Adjust ImGui style parameters
  // ImGuiStyle &style = ImGui::GetStyle();

  conversations = generateDummyData();
}

void Chat::Update()
{
  if (!isLoggedIn)
  {
    LoginWindow();
  }
  else
  {
    ChatWindow();
  }
  // ImGui::ShowDemoWindow();
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

void Chat::LoginWindow()
{
  static ImGuiWindowFlags flags =
      ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

  // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
  ImGui::Begin("Main", nullptr, flags);

  // Set the window size first if you want to specify the size
  // ImVec2 windowSize = ImVec2(400, 300); // Example specific size
  ImVec2 windowSize = ImGui::GetContentRegionAvail(); // For full display size
  ImVec2 childWindowSize = {450, 220};
  ImVec2 windowPos = ImVec2((windowSize.x - childWindowSize.x) / 2, (windowSize.y - childWindowSize.y) / 2);

  // ImGui::SetNextChildWindowPos(windowPos, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
  ImGui::SetCursorPos(windowPos);

  // Using the flags variable which should be defined earlier in your code
  // with ImGuiWindowFlags_AlwaysAutoResize if you want the window to automatically resize based on its contents
  ImGui::BeginChild("MainKaChild", childWindowSize);
  {
    static char username[128] = "";
    static char password[128] = "";

    ImGui::InputText("Username", username, IM_ARRAYSIZE(username));
    ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

    if (ImGui::Button("Log In"))
    {
      isLoggedIn = true;
    }
    if (ImGui::Button("Log in anonymous user"))
    {
      isLoggedIn = true;
    }
  }

  ImGui::EndChild();
  ImGui::End();
}

void Chat::ChatWindow()
{
  static ImGuiWindowFlags flags =
      ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

  // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);

  if (ImGui::Begin("MainWindow", nullptr, flags))
  {
    // Calculate the widths based on the percentage of the available space
    float availableWidth = ImGui::GetContentRegionAvail().x;
    float leftWidth = availableWidth * 0.3f;  // 30% for contacts
    float rightWidth = availableWidth * 0.7f; // 70% for chats

    // Left
    {
      ImGui::BeginChild("Contacts", ImVec2(leftWidth, 0), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
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
      ImGui::BeginGroup();
      ImGui::BeginChild("Conversation&Details", ImVec2(rightWidth, -ImGui::GetFrameHeightWithSpacing()));
      if (selectedConversationIndex == -1)
      {
        CenterText("Select a chat to start messaging");
      }
      else
      {
        const Conversation &selectedConvo = conversations[selectedConversationIndex];

        ImGui::PushFont(headingFont);
        ImGui::Text("%s", selectedConvo.contactName.c_str());
        ImGui::PopFont();

        ImGui::Separator();
        if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
        {
          if (ImGui::BeginTabItem("Chats"))
          {
            for (const Message &msg : selectedConvo.messages)
            {
              ImGui::Text("%s:", msg.sender.c_str());
              ImGui::SameLine();
              ImGui::Text(msg.content.c_str());
            }

            ImGui::EndTabItem();
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
            ImGui::Button("Send", ImVec2(0, ImGui::GetTextLineHeight()));
          }
          if (ImGui::BeginTabItem("Details"))
          {
            ImGui::Text("ID: 0123456789");
            ImGui::EndTabItem();
          }
          ImGui::EndTabBar();
        }
      }
      ImGui::EndChild();
      ImGui::EndGroup();
    }
  }
  ImGui::End();
}