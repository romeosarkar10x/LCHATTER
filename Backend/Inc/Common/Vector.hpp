#include <iostream>
#include <utility>
#include <type_traits>
#include <initializer_list>

#include <cassert>

template<typename T>
  class vector
  {

  public:
    using value_type = T;


  private:
    value_type*   _m_ptr;
    int           _m_size;
    int           _m_capacity;

    value_type*  _m_alloc(int s) { return reinterpret_cast<value_type*>(malloc(static_cast<int>(sizeof(value_type)) * s)); }
    void  _m_free(value_type* ptr) { free(ptr); }

    template<typename ...Args>
      void _m_construct_at(value_type* ptr, Args&& ...args) { new (ptr) value_type { std::forward<Args>(args)... }; }

    void _m_destroy_at(value_type* ptr)
    {
      ptr->~value_type();
    }
    
    void _m_n_default_construct_at(value_type* dest, int n)
    {
      for(int i = 0; i < n; i++) { _m_construct_at(dest + i); }
    }

    void _m_n_copy_construct_at(value_type* dest, const value_type* src, int n)
    {
      for(int i = 0; i < n; i++) { _m_construct_at(dest + i, *(src + i)); }
    }

    void _m_n_move_construct_at(value_type* dest, value_type* src, int n)
    {
      for(int i = 0; i < n; i++) { _m_construct_at(dest + i, std::move(*(src + i))); }
    }

    void _m_n_destroy_at(value_type* dest, int n)
    {
      for(int i = 0; i < n; i++) { _m_destroy_at(dest + i); }
    }

    void _m_resize()
    {
      int final_capacity = 2 * _m_capacity;
      if(final_capacity == 0) { final_capacity = 1; }
      
      _m_resize(final_capacity);
    }

    void _m_resize(int final_capacity)
    {
      /// alloc
      value_type* ptr = _m_alloc(final_capacity);
      
      /// move
      _m_n_move_construct_at(ptr, _m_ptr, _m_size);

      /// destroy and free
      _m_n_destroy_at(_m_ptr, _m_size);
      _m_free(_m_ptr);

      _m_capacity = final_capacity;
      _m_ptr = ptr;
    }

  public:
    vector() : _m_ptr { nullptr }, _m_size { 0 }, _m_capacity { 0 } {}

    vector(const std::initializer_list<value_type>& init_list) : vector()
    {
      _m_resize(static_cast<int>(init_list.size()));

      for(const value_type& val : init_list)
      {
        _m_construct_at(_m_ptr + _m_size, val);
        _m_size++;
      }
    }

    vector(const vector& rhs) : _m_ptr { rhs._m_ptr }, _m_size { rhs._m_size }, _m_capacity { rhs._m_capacity }
    {
      if(_m_capacity != 0)
      {
        /// alloc
        _m_ptr = _m_alloc(_m_capacity);
        
        /// copy
        _m_n_copy_construct_at(_m_ptr, rhs._m_ptr, _m_size);
      }
    }

    vector(vector&& rhs) : _m_ptr { rhs._m_ptr }, _m_size { rhs._m_size }, _m_capacity { rhs._m_capacity }
    {
      rhs._m_size = rhs._m_capacity = 0;
    }

    vector& operator=(const vector& rhs)
    {
      if(this == &rhs) { return *this; }
      
      vector copy { rhs };
      swap(copy);

      return *this;
    }

    vector& operator=(vector&& rhs)
    {
      vector copy { std::move(rhs) };
      swap(copy);

      return *this;
    }

    void swap(vector& rhs)
    {
      std::swap(_m_ptr, rhs._m_ptr);
      std::swap(_m_size, rhs._m_size);
      std::swap(_m_capacity, rhs._m_capacity);
    }

    friend void swap(vector& lhs, vector& rhs) { lhs.swap(rhs); }

    void reserve(int capacity)
    {
      if(_m_capacity < capacity)
      {
        int final_capacity = (_m_capacity == 0) ? capacity : _m_capacity;

        while(final_capacity < capacity)
        {
          final_capacity *= 2;
        }

        _m_resize(final_capacity);
      }
    }

    void reserve_exact(int capacity)
    {
      if(_m_capacity < capacity)
      {
        _m_resize(capacity);
      }
    }

    void push_back(const value_type& value)
    {
      if(_m_capacity < _m_size + 1)
      {
        _m_resize();
      }
      
      _m_construct_at(_m_ptr + _m_size, value);
      _m_size++;
    }

    void push_back(value_type&& value)
    {
      if(_m_capacity < _m_size + 1) { _m_resize(); }
      
      _m_construct_at(_m_ptr + _m_size, std::move(value));
      _m_size++;
    }

    template<typename ...Args>
      void emplace_back(Args&& ...args)
      {
        if(_m_capacity < _m_size + 1) { _m_resize(); }
        
        _m_construct_at(_m_ptr + _m_size, std::forward<Args>(args)...);
        _m_size++;
      }

    int size() const { return _m_size; }
    
    value_type& at(int index)
    {
      assert(0 <= index && index < _m_size);
      return _m_ptr[index];
    }

    const value_type& at(int index) const { return const_cast<vector*>(this)->at(index); }

    ~vector()
    {
      if(_m_capacity != 0)
      {
        _m_n_destroy_at(_m_ptr, _m_size);

        _m_size = _m_capacity = 0;
      }
    }

    friend std::ostream& operator<<(std::ostream& o, const vector<value_type>& v)
    {
      o << "{ ";
      for(int i = 0; i < v.size(); i++) { o << v.at(i) << " "; }
      o << "}";

      return o;
    }
  };
