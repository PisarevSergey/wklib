#pragma once

namespace win_kernel_lib
{
  namespace deleters
  {
    template <typename T>
    class default_deleter_object
    {
    public:
      void operator()(T* ptr)
      {
        delete ptr;
      }
    };


    class pool_deleter
    {
    public:
      void operator()(void* p);
      void operator()(const void* p);
    };
  }
}
