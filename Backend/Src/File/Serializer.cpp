class Serializer
{

  public:
  
  template<typename _Tp>
  struct is_serializable
  {
    // bool value 
  };

  template<typename _Tp>
    static int serialize(char* buffer, _Tp&& object)
    {
      // static_assert()
    }

  Serializer() = delete;
  ~Serializer() = delete;
};