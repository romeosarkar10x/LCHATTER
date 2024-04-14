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
    friend class AppBackend;

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
      struct Buffer_Mixin
      {
        Buffer_Mixin() = delete;
        ~Buffer_Mixin() = delete;

        static int    get_buffer_size() { return _T::_S_buffer_size; }
        static char*  get_buffer() { assert(_T::_s_buffer != nullptr); return _T::_s_buffer; }

        static void alloc() { if(_T::_s_buffer == nullptr) { _T::_s_buffer = new char [_T::_S_buffer_size]; } }
        static void dealloc() { if(_T::_s_buffer != nullptr) { delete [] _T::_s_buffer; _T::_s_buffer = nullptr; } }
        
        static void clear() { if(_T::_s_buffer != nullptr) { _T::_s_buffer[0] = 0; } }

      };

  public:
    struct Username : public Buffer_Mixin<Username>
    {
      static const int  _S_buffer_size = 20;
      static char*      _s_buffer;
    };

    struct Password : public Buffer_Mixin<Password>
    {
      static const int  _S_buffer_size = 20;
      static char*      _s_buffer;
    };
    
    struct IpAddress : public Buffer_Mixin<IpAddress>
    {
      static const int  _S_buffer_size = 20; 
      static char*      _s_buffer;
    };
    
    struct Port : public Buffer_Mixin<Port>
    {
      static const int  _S_buffer_size = 10;
      static char*      _s_buffer;
    };
    
    struct ChatMessage : public Buffer_Mixin<ChatMessage>
    {
      static const int  _S_buffer_size = 40000;
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
  
  // static UdpSender& get_sender()
  // { return _s_sender; }

  // static UdpReceiver& get_receiver()
  // { return _s_receiver; }


  static std::vector<Connection>          _s_connections;
  static std::vector<ConnectionRequest>   _s_incoming_requests;
  static std::vector<ConnectionRequest>   _s_outgoing_requests;

  static std::vector<Connection>& get_connections()
  { return _s_connections; }

  static std::vector<ConnectionRequest>& get_incoming_requests()
  { return _s_incoming_requests; }

  static std::vector<ConnectionRequest>& get_outgoing_requests()
  { return _s_outgoing_requests; }


  static void handle_receive();
  static void load();
  static void save();
};

#endif