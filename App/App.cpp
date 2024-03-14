#include <cassert>

#include "../Backend/AppBackend.cpp"
#include "../Frontend/AppFrontend.cpp"
#include "Event.hpp"
#include "../Log/Logger.cpp"


class App
{
public:
  static void initialize()
  {
    AppBackend::initialize();
    AppFrontend::initialize();
    // wprintw(stdscr, "here!!");

    // assert(false);
    
  }

  static void run()
  {
    while(true)
    {
      Event event = AppFrontend::display();
      handle_event(event);
      AppBackend::update();
      Sleep(10);
    }
  }

  static void handle_event(Event event)
  {
    if(event == Event::NONE) { return; }
    
    switch(event)
    {
    case Event::NONE:
      break;
    case Event::LOGIN:
      AppBackend::me() = User(AppFrontend::user_name(), AppFrontend::password());
      AppBackend::set_state(AppBackend::State::LOGGED_IN);
      break;
    
    case Event::SEND_MSG:
      
      break;
      
    }

      
  }


};

int main()
{


  App::initialize();
  App::run();
  

  return 0;
}