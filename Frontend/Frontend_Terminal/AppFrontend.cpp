#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <ncurses/ncurses.h>
#undef getch

#include "Window.cpp"
#include "TextBox.cpp"
#include "../App/Event.hpp"
#include "../Backend/AppBackend.cpp"
#include "../Log/Logger.cpp"


// bool _s_id_password = { false };

class AppFrontend
{
  static Window _s_app_window;
  
// State:ON:
  static bool _s_display_state_on;
  static Window _s_login;
  static TextBox _s_user_name;
  static TextBox _s_password;
  static bool _s_focus_user_name;

// State:LOGGED_IN:
  static bool _s_display_state_logged_in;
  static Window _s_connections;
  static Window _s_chats;
  // 


public:
  static void initialize()
  {
    initscr();
    noecho();
    // raw();
    keypad(stdscr, true);

    _s_app_window = Window { stdscr };

    _s_app_window.box();
    _s_app_window.mvprintf(0, _s_app_window.width() / 2 - 4, "LCHATTER");
    _s_app_window.refresh();
  }
  
  static Event display()
  {
    // Considering that User does not change the size of terminal window in between


    using State = AppBackend::State;
    switch(AppBackend::state())
    {
    case State::ON:
      return _m_display_state_on();
    case State::LOGGED_IN:
      return _m_display_state_logged_in();
    }
    // TextBox tb(6, 40, 2, 20);
    
    // int ret = tb.getch();
    // if(ret == KEY_ENTER) { return Event::SEND_MSG; }

    // tb.echo(ret);

    return Event::NONE;
  }

private:
  static Event _m_display_state_on()
  {
    const int height = 10, width = 60;
    // std::cout << "here ";
    if(!_s_display_state_on)
    {
      // std::cout << (_s_app_window.height() - height) / 2 << " " << (_s_app_window.width() - width) / 2 << "\n";
      _s_login = Window(height, width, (_s_app_window.height() - height) / 2, (_s_app_window.width() - width) / 2);
      _s_login.box();
      _s_login.mvprintf(0, (width - 5) / 2, "Login");
      _s_login.mvprintf(3, 4, "User_Name:");
      _s_login.mvprintf(6, 4, "Password:");
      _s_login.refresh();

      _s_user_name = TextBox(3, 40, (_s_app_window.height() - height) / 2 + 2, (_s_app_window.width() - width) / 2 + 14);
      _s_password = TextBox(3, 40, (_s_app_window.height() - height) / 2 + 5, (_s_app_window.width() - width) / 2 + 14);

      _s_display_state_on = true;
      _s_focus_user_name = true;
    }
    
    if(_s_focus_user_name)
    {
      int ret = _s_user_name.getch();
      _s_user_name.echo(ret);
      if(ret == '\n') { _s_focus_user_name = false; }
    }
    else
    {
      int ret = _s_password.getch();

      if(ret == '\n')
      {
        // _s_login.~Window();
        // _s_user_name.~TextBox();
        // _s_password.~TextBox();
        _s_login.clear();
        _s_user_name.clear();
        _s_password.clear();
        // std::cout << "here!!!" << "\n";
        return Event::LOGIN;
      }
      _s_password.echo('*');
    }
    
    // TextBox user_name(3, 40, (_s_app_window.height() - height) / 2 + 2, (_s_app_window.width() - width) / 2 + 14);
    // TextBox password(3, 40, (_s_app_window.height() - height) / 2 + 5, (_s_app_window.width() - width) / 2 + 14);
    
    // TextBox user_name, password;
    
    return Event::NONE;
  }

  static Event _m_display_state_logged_in()
  {
    if(!_s_display_state_logged_in)
    {
      _s_app_window.mvprintf(1, 2, "User_Name: %s, Id: %s", AppBackend::me().name().c_str(), AppBackend::me().id().c_str());  
      _s_app_window.refresh();

      int window_connections_width = _s_app_window.width() / 4;
      _s_connections = Window(_s_app_window.height() - 2, window_connections_width, 3, 0);
      _s_connections.box();
      _s_connections.mvprintf(0, _s_connections.width() / 2 - 6, "CONNECTIONS");

      _s_chats = Window(_s_app_window.height() - 2, _s_app_window.width() - window_connections_width + 1, 3, window_connections_width - 1);
      _s_chats.box();
      _s_chats.mvprintf(0, _s_chats.width() / 2 - 2, "CHATS");

      _s_connections.refresh();
      _s_chats.refresh();

      _s_display_state_logged_in = true;
    }

    return Event::NONE;
  }

public:
  static void terminate()
  {
    endwin();
  }

  static const char* user_name() { return _s_user_name.text(); }
  static const char* password() { return _s_password.text(); }
};

Window AppFrontend::_s_app_window {};


// on:
bool AppFrontend::_s_display_state_on{ false };
Window AppFrontend::_s_login {};
TextBox AppFrontend::_s_user_name {};
TextBox AppFrontend::_s_password {};
bool AppFrontend::_s_focus_user_name { true };


// logged_in:
bool AppFrontend::_s_display_state_logged_in { false };
Window AppFrontend::_s_connections {};
Window AppFrontend::_s_chats {};


// bool A

