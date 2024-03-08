#include <iostream>
#include <string>




class User // User + Singleton
{
  std::string _m_username;

  static User _s_me;
  static bool _s_initialized;

public:
  std::string username();
  std::string id();

  static User me()
  {
    if(_s_initialized)
    {
      return _s_me;
    }

    throw "error: user not initialized";
  }
  static void initialize(const std::string& username, const std::string& password)
  {
    // _s_me.initialize
  }
  static void initialize_anonymous()
  {
    
  }

};

bool User::_s_initialized { false };
