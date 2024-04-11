#ifndef APP_CPP
#define APP_CPP

#include <algorithm>
#include <cstring>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "App_Base.cpp"

class App : public App_Base<App>
{
public:
  App();
  ~App() = default;

  static App app;

  void StartUp();
  void Update();

  static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
  static void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
  static void KeyCallback(GLFWwindow *window, int key, int scancode, int actions, int mods);

private:
  void ShowLoginWindow();
  void ShowChatWindow();
  void AddConnectionWindow();
  void ShowConnectionRequestWindow();

  int selectedConnectionIndex = -1;
  int selectedRequestIndex = -1;
  ImFont *h1Font, *h2Font;
  ImGuiWindowFlags mainWindowFlag;
};

App App::app{};

bool showAddConnectionForm = false;
bool showConnectionRequestWindow = false;

std::vector<Connection> connections;
std::vector<ConnectionRequest> outgoingRequests;
std::vector<ConnectionRequest> incomingRequests;

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
  // io.Fonts->AddFontFromFileTTF("assets/fonts/CascadiaCode/CaskaydiaCoveNerdFont-Regular.ttf", 24.0f);
  // h1Font = io.Fonts->AddFontFromFileTTF("assets/fonts/Noto_Sans/NotoSans-VariableFont_wdth,wght.ttf", 48.0f);
  // h2Font = io.Fonts->AddFontFromFileTTF("assets/fonts/Noto_Sans/NotoSans-VariableFont_wdth,wght.ttf", 32.0f);

  io.Fonts->AddFontFromFileTTF("assets/fonts/HelveticaNeueLight.otf", 20.0f);
  // io.Fonts->AddFontFromFileTTF("assets/fonts/montserrat.regular.ttf", 24.0f);
  h1Font = io.Fonts->AddFontFromFileTTF("assets/fonts/montserrat.bold.ttf", 48.0f);
  h2Font = io.Fonts->AddFontFromFileTTF("assets/fonts/montserrat.bold.ttf", 32.0f);

  // Adjust ImGui style parameters
  // ImGuiStyle &style = ImGui::GetStyle();

  // generateDummyData();
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

  if (AppBackend::State::get_state() == AppBackend::State::NOT_LOGGED_IN)
  {
    ShowLoginWindow();
    // renderLoginWindow(app.window);
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

void App::ShowLoginWindow()
{
  static int focus = 0;
  ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll |
                                         ImGuiInputTextFlags_CallbackCharFilter;

  if (ImGui::Begin("MainWindow", nullptr, mainWindowFlag))
  {
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    ImVec2 childWindowSize =
        ImVec2(300, ImGui::GetFrameHeightWithSpacing() * 3 + ImGui::GetTextLineHeightWithSpacing());

    ImGui::SetCursorPos(ImVec2((windowSize.x - childWindowSize.x) / 2, (windowSize.y - childWindowSize.y) / 2));

    // Login Child Window
    {
      ImGui::BeginChild("ShowLoginWindow", childWindowSize, ImGuiChildFlags_Border);

      auto callback = [](ImGuiInputTextCallbackData *data) -> int {
        // printf("hello world\n");
        // printf("%hhd ", data->EventChar);
        printf("callback ");
        printf("%hd ", data->EventChar);

        if ('A' <= data->EventChar && data->EventChar <= 'Z')
        {
          data->EventChar += 32;
        }
        // data->EventChar = data->EventChar;
        return 0;
      };
      // Get the available width in the parent window
      ImVec2 availableSpace = ImGui::GetContentRegionAvail();
      // Use the available width but keep the default height for the input text
      ImVec2 inputSize = ImVec2(availableSpace.x, 0);

      // Before your InputTextWithHint, call SetNextItemWidth with -1.0f to fill the space
      ImGui::SetNextItemWidth(-1.0f);
      if (ImGui::InputTextWithHint("##Username", "Username", AppBackend::Buffer::Username::get_buffer(),
                                   AppBackend::Buffer::Username::get_buffer_size(),
                                   input_text_flags | ImGuiInputTextFlags_AllowTabInput, callback))

      {
        focus = 1;
      }

      if (focus == 0)
      {
        ImGui::SetKeyboardFocusHere(-1);
        focus = 2;
      }

      ImGui::SetNextItemWidth(-1.0f);
      if (ImGui::InputTextWithHint("##Password", "******", AppBackend::Buffer::Password::get_buffer(),
                                   AppBackend::Buffer::Password::get_buffer_size(),
                                   ImGuiInputTextFlags_Password |
                                       input_text_flags ^ ImGuiInputTextFlags_CallbackCharFilter))
      {
        AppBackend::Frontend_Event::set_event(AppBackend::Frontend_Event::LOGIN);
        focus = 0;
      }

      if (focus == 1)
      {
        ImGui::SetKeyboardFocusHere(-1);
        focus = 2;
      }

      if (ImGui::Button("LOG IN"))
      {
        AppBackend::Frontend_Event::set_event(AppBackend::Frontend_Event::LOGIN);
      }

      ImGui::Text("Anonymous Login");
      if (ImGui::IsItemClicked())
      {
        AppBackend::Frontend_Event::set_event(AppBackend::Frontend_Event::LOGIN_ANONYMOUS);
      }
    }
    ImGui::EndChild();
  }
  ImGui::End();
}
void App::AddConnectionWindow()
{
  strcpy(AppBackend::Buffer::IpAddress::get_buffer(), "127.0.0.1");
  ImGui::InputText("IP", AppBackend::Buffer::IpAddress::get_buffer(), AppBackend::Buffer::IpAddress::get_buffer_size());
  ImGui::InputText("PORT", AppBackend::Buffer::Port::get_buffer(), AppBackend::Buffer::Port::get_buffer_size());

  if (ImGui::Button("CONNECT"))
  {
    showAddConnectionForm = false;
    AppBackend::Frontend_Event::set_event(AppBackend::Frontend_Event::SEND_CONNECTION_REQUEST);
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

  incomingRequests = AppBackend::_s_incoming_connection_requests;
  std::ranges::sort(incomingRequests, std::less<>{}, [](const ConnectionRequest &r) { return r.get_timepoint(); });

  outgoingRequests = AppBackend::_s_outgoing_connection_requests;
  std::ranges::sort(outgoingRequests, std::less<>{}, [](const ConnectionRequest &r) { return r.get_timepoint(); });

  if (ImGui::Begin("Connection Requests", &showConnectionRequestWindow))
  {

    if (ImGui::BeginTabBar("RequestsTabBar"))
    {
      if (ImGui::BeginTabItem("Incoming Requests"))
      {

        for (int i = 0; i < (int)incomingRequests.size(); ++i)
        {
          ImGui::PushID(i);

          if (ImGui::Selectable(incomingRequests[i].get_user().get_id(), selectedRequestIndex == i))
          {
            selectedRequestIndex = (selectedRequestIndex == i) ? -1 : i;
          }
          if (incomingRequests[i].get_state() == ConnectionRequest::State::AWAITING_RESPONSE &&
              selectedRequestIndex == i)
          {
            ImGui::Text("Request Time: %s", incomingRequests[i].get_timepoint().to_string_localtime().get_buffer());
            if (ImGui::Button("Accept"))
            {
              AppBackend::set_id(incomingRequests[i].get_user().get_id());
              // std::cout << "id: " << incomingRequests[i].get_user().get_id() << std::endl;
              AppBackend::Frontend_Event::set_event(AppBackend::Frontend_Event::ACCEPT_CONNECTION_REQUEST);
              // AcceptConnectionRequest(incomingRequests[i]);
              selectedRequestIndex = -1;
            }
            ImGui::SameLine();
            if (ImGui::Button("Reject"))
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
          auto text = outgoingRequests[i].get_address().to_string();
          ImGui::Text(text);
          // ImGui::PushID(i);
          // if (ImGui::Selectable(outgoingRequests[i].get_address().get_ip_address(), selectedRequestIndex == i))
          // {
          //   selectedRequestIndex = (selectedRequestIndex == i) ? -1 : i;
          // }
          // ImGui::PopID();
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

bool operator!=(const ImVec2 &a, const ImVec2 &b)
{
  return (a.x != b.x || a.y != b.y);
}

void App::ShowChatWindow()
{
  static auto viewport_size = ImGui::GetMainViewport()->Size;
  connections = AppBackend::_s_connections;

  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0.0f, 0.0f});
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});

  if (ImGui::Begin("MainWindow", nullptr, mainWindowFlag))
  {
    ImGui::PopStyleVar(2);

    // ImVec2 windowSize = ImGui::GetContentRegionAvail();
    // ImVec2 windowSize = ImGui::GetMainViewport()->Size;
    static float leftWidth = viewport_size.x * 0.3f; // 30% for contacts
    float rightWidth = viewport_size.x - leftWidth;  // 70% for chats

    if (viewport_size != ImGui::GetMainViewport()->Size)
    {
      viewport_size = ImGui::GetMainViewport()->Size;
      leftWidth = viewport_size.x * (leftWidth / (leftWidth + rightWidth));
      rightWidth = viewport_size.x - leftWidth;
    }

    auto windowSize = viewport_size;

    // Left
    {
      ImGui::BeginChild("LeftParent", ImVec2(leftWidth, windowSize.y), ImGuiChildFlags_Border);

      // Display Port Number
      // char port[6];
      // std::snprintf(port, 6, "%u", AppBackend::_s_receiver.get_socket_address().get_port());

      ImGui::TextWrapped(String("Id : ") + AppBackend::_s_me.get_id());
      ImGui::TextWrapped(String("Port : ") + AppBackend::_s_receiver.get_socket_address().get_port());
      if (ImGui::IsItemClicked())
      {
        // Copy the text to the clipboard
        ImGui::SetClipboardText(AppBackend::_s_receiver.get_socket_address().get_port());
      }

      if (ImGui::Button("+"))
      {
        showAddConnectionForm = !showAddConnectionForm;
      }
      if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone))
        ImGui::SetTooltip("Add New Connection");

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

      for (int i = 0; i < static_cast<int>(AppBackend::_s_connections.size()); ++i)
      {
        auto label = connections[i].get_user().get_name() + "##" + connections[i].get_user().get_id();
        if (ImGui::Selectable(label, i == selectedConnectionIndex))
        {
          selectedConnectionIndex = i;
        }
      }
      ImGui::EndChild();
    }
    ImGui::SameLine();

    // Right
    {

      // ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
      // ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
      // ImGui::BeginGroup();
      ImGui::BeginChild("RightParent", ImVec2(rightWidth, windowSize.y), ImGuiChildFlags_Border);

      if (selectedConnectionIndex == -1)
      {
        TextWithAlignment("Select a chat to start messaging", ImVec2(1, 1));
      }
      else
      {
        const Connection &selectedConnection = connections[selectedConnectionIndex];

        ImGui::PushFont(h1Font);
        ImGui::Text(selectedConnection.get_user().get_name());
        ImGui::PopFont();

        ImGui::Separator();
        if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
        {
          auto itr = std::ranges::find(AppBackend::_s_connections, selectedConnection.get_user().get_id(),
                                       [](const Connection &c) { return c.get_user().get_id(); });
          if (ImGui::BeginTabItem("Chats"))
          {

            for (int cnt = 0; const ChatMessage &m : itr->get_chat().get_messages())
            {
              static float wrap_width = 200.0f;
              wrap_width = ImGui::GetContentRegionAvail().x * 0.6f;
              // if (m.is_me())
              if (cnt++ & 1)
              {
                // Calculate text width with wrapping
                ImVec2 textSize = ImGui::CalcTextSize(m.get_text(), NULL, false, wrap_width);

                // Calculate the starting X position for the text to right-align it
                // Ensure we don't go negative in case the text is wider than the available space
                float startPosX = std::max(ImGui::GetContentRegionAvail().x - textSize.x, 0.0f);

                // Set cursor position to align text to the right
                ImGui::SetCursorPosX(startPosX);

                ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red
                ImGui::TextUnformatted(m.get_text());
                ImGui::PopStyleColor();
                ImGui::PopTextWrapPos();
              }
              else
              {
                ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 1.0f, 1.0f)); // Pink
                ImGui::TextUnformatted(m.get_text());
                ImGui::PopStyleColor();
                ImGui::PopTextWrapPos();
              }
            }
            ImGui::EndTabItem();
          }
          if (ImGui::BeginTabItem("Details"))
          {
            ImGui::Text(itr->get_user().get_id());
            ImGui::EndTabItem();
          }
          ImGui::EndTabBar();
        }
        ImGui::Separator();

        static bool reclaim_focus = true;
        ImGuiInputTextFlags input_text_flags =
            ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll;

        // Used "##messageInputBox" to hide the label but ensure a unique ID
        auto get_buffer = AppBackend::Buffer::ChatMessage::get_buffer;

        auto sendProc = [&]() {
          if (get_buffer()[0] != '\0')
          {
            AppBackend::set_id(connections[selectedConnectionIndex].get_user().get_id());
            AppBackend::Frontend_Event::set_event(AppBackend::Frontend_Event::SEND_CHAT_MESSAGE);
          }
        };

        if (ImGui::InputText("##messageInputBox", get_buffer(), AppBackend::Buffer::ChatMessage::get_buffer_size(),
                             input_text_flags))
        {
          reclaim_focus = true;
          sendProc();
        }

        if (reclaim_focus)
        {
          ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
          reclaim_focus = false;
        }
        ImGui::SameLine();

        // Adjust the size of the Send button
        if (ImGui::Button("Send"))
        {
          reclaim_focus = true;
          sendProc();
        }
      }
      ImGui::EndChild();
    }

    auto mouse_pos = ImGui::GetMousePos();                                                  // absolute position
    float edge_x = leftWidth + ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x; // absolute position

    auto is_nearby = [](float pos_x, float mouse_pos_x, float diff) -> bool {
      return (pos_x - diff / 2.0 <= mouse_pos_x && mouse_pos_x <= pos_x + diff / 2.0);
    };

    // printf("(%f, %f)", mouse_pos.x, mouse_pos.y);
    static bool resize = false;

    if (resize || (is_nearby(edge_x, mouse_pos.x, 4.0f) &&
                   ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows)))
    {
      ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

      resize = ImGui::IsMouseDown(ImGuiDir_Left);

      if (resize)
      {
        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->AddLine(
            {leftWidth + ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x, ImGui::GetWindowPos().y},
            {leftWidth + ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x,
             ImGui::GetWindowPos().y + ImGui::GetWindowHeight()},
            IM_COL32(255, 0, 0, 255), 4.0f);

        float child_window_size_x =
            ImGui::GetMousePos().x - ImGui::GetWindowPos().x - ImGui::GetStyle().WindowPadding.x;

        if (child_window_size_x < 450)
        {
          child_window_size_x = 450;
        }
        else if (child_window_size_x > 800)
        {
          child_window_size_x = 800;
        }

        leftWidth = child_window_size_x;
      }
    }
  }
  ImGui::End();
}

#endif // CHAT_H