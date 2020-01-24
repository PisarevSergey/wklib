#pragma once

#include <deleters.h>

namespace win_kernel_lib
{
  namespace smart_pointers
  {
    template <typename T, typename deleter_type = win_kernel_lib::deleters::default_deleter_object<T>>
    class auto_pointer
    {
    public:
      explicit auto_pointer(T* object = nullptr) : ptr{ object }
      {}

      auto_pointer(deleter_type dltr, T* object = nullptr) : del_obj{ dltr }, ptr{ object }
      {}

      ~auto_pointer()
      {
        del_obj(ptr);
        ptr = nullptr;
      }

      auto_pointer(const auto_pointer&) = delete;
      auto_pointer& operator=(const auto_pointer&) = delete;

      auto_pointer(auto_pointer&& src)
      {
        del_obj(ptr);
        ptr = src.ptr;
        src.ptr = nullptr;
      }

      auto_pointer& operator=(auto_pointer&& src)
      {
        if (&src != this)
        {
          del_obj(ptr);
          ptr = src.ptr;
          src.ptr = nullptr;
        }

        return *this;
      }

      void reset(T* new_ptr = nullptr)
      {
        if (new_ptr != ptr)
        {
          del_obj(ptr);
          ptr = new_ptr;
        }
      }

      T* get()
      {
        return ptr;
      }

      T* operator->()
      {
        return ptr;
      }

    private:
      T* ptr;
      deleter_type del_obj;
    };
  }
}

