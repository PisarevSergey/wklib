#pragma once

namespace wklib
{
  namespace smart_pointers
  {
    template <typename T, typename deleter_type = wklib::deleters::default_deleter<T>>
    class auto_pointer
    {
    public:
      explicit auto_pointer(T* object = nullptr) noexcept : ptr{ object }
      {}

      auto_pointer(deleter_type dltr, T* object = nullptr) noexcept : del_obj{ dltr }, ptr{ object }
      {}

      ~auto_pointer() noexcept
      {
        del_obj(ptr);
        ptr = nullptr;
      }

      auto_pointer(const auto_pointer&) = delete;
      auto_pointer& operator=(const auto_pointer&) = delete;

      auto_pointer(auto_pointer&& src) noexcept
      {
        free();
        move(src);
      }

      auto_pointer& operator=(auto_pointer&& src) noexcept
      {
        if (&src != this)
        {
          free();
          move(src);
        }

        return *this;
      }

      void reset(T* new_ptr = nullptr) noexcept
      {
        free();
        ptr = new_ptr;
      }

      T* release() noexcept
      {
        T* tmp{ ptr };
        ptr = nullptr;
        return tmp;
      }

      T* get() noexcept
      {
        return ptr;
      }

      const T* get() const noexcept
      {
        return ptr;
      }

      T* operator->() noexcept
      {
        return ptr;
      }

      const T* operator->() const noexcept
      {
        return ptr;
      }

    private:
      void free()
      {
        if (ptr)
        {
          del_obj(ptr);
          ptr = nullptr;
        }
      }

      void move(auto_pointer&& src)
      {
        ptr = src.ptr;
        del_obj = src.del_obj;

        src.ptr = nullptr;
        src.del_obj = del_obj{};
      }

    private:
      T* ptr;
      deleter_type del_obj;
    };
  }
}

