#ifndef APP_BACKEND_HPP
#define APP_BACKEND_HPP

#include <set>
#include <algorithm>

#include <cstdlib>

#include "../Other/Socket/Address.hpp" /// <winsock2.h>
#include "../Common/User.hpp" /// <windows.h>
#include "../Common/Connection.hpp"
#include "../File/Logger.hpp" /// <windows.h>

#include "../Other/Socket/Udp/UdpSender.hpp"
#include "../Other/Socket/Udp/UdpReceiver.hpp"

class AppBackend
{
public:
  class State
  {

  public:
    enum Enum_State : char
    {
      NOT_LOGGED_IN,
      LOGGED_IN,
    };
    
    static Enum_State get_state();
    static void       set_state(Enum_State state);
  
  private:
    static Enum_State _s_state;
  };

  class Buffer
  {
    template<class _T>
      class Buffer_Mixin
      {
        
      public:
        Buffer_Mixin() = delete;
        ~Buffer_Mixin() = delete;

        static int    get_buffer_size() { return _T::_S_buffer_size; }
        static char*  get_buffer() { assert(_T::_s_buffer != nullptr); return _T::_s_buffer; }

        static void alloc() { if(_T::_s_buffer == nullptr) { _T::_s_buffer = new char [_T::_S_buffer_size]; } }
        static void dealloc() { if(_T::_s_buffer != nullptr) { delete [] _T::_s_buffer; _T::_s_buffer = nullptr; } }
        
        static void clear() { if(_T::_s_buffer != nullptr) { _T::_s_buffer[0] = 0; } }

      };

  public:
    class Username : public Buffer_Mixin<Username>
    {
      friend class Buffer_Mixin<Username>;
      static const int  _S_buffer_size = 20;
      static char*      _s_buffer;
    };

    class Password : public Buffer_Mixin<Password>
    {
      friend class Buffer_Mixin<Password>;
      static const int  _S_buffer_size = 20;
      static char*      _s_buffer;
    };
    
    class IpAddress : public Buffer_Mixin<IpAddress>
    {
      friend class Buffer_Mixin<IpAddress>;
      static const int  _S_buffer_size = 20; 
      static char*      _s_buffer;
    };
    
    class Port : public Buffer_Mixin<Port>
    {
      friend class Buffer_Mixin<Port>;
      static const int  _S_buffer_size = 10;
      static char*      _s_buffer;
    };
    
    class ChatMessage : public Buffer_Mixin<ChatMessage>
    {
      friend class Buffer_Mixin<ChatMessage>;
      static const int  _S_buffer_size = 4000;
      static char*      _s_buffer;
    };
    
    static void alloc();
    static void dealloc();

    static void clear();
  };

  class Frontend_Event;

  static void init();
  static void destroy();
  
  static void update();

  static void set_id(const String& id);

  static const User&        get_me() { return _s_me; }
  static const UdpSender&   get_sender() { return _s_sender; }
  static const UdpReceiver& get_receiver() { return _s_receiver; }

  AppBackend()  = delete;
  ~AppBackend() = delete;

private:

public:
  static String _s_current_id;
  static constexpr auto _Projection = [] (const ConnectionRequest& c) -> const String& { return c.get_user().get_id(); };

  static User         _s_me;
  static UdpSender    _s_sender;
  static UdpReceiver  _s_receiver;

  static std::vector<Connection>          _s_connections;
  static std::vector<ConnectionRequest>   _s_incoming_connection_requests;
  static std::vector<ConnectionRequest>   _s_outgoing_connection_requests;


  static void handle_receive();
  static void load();
  static void save();
};

#endif