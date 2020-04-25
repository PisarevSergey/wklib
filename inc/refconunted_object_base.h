#pragma once

namespace win_kernel_lib
{
  namespace refcounted_object
  {
    template <typename derived_class, typename deleter = win_kernel_lib::deleters::default_deleter<derived_class>>
    class base
    {
    public:
      derived_class* reference()
      {
        InterlockedIncrement64(&refcount);
        return static_cast<derived_class*>(this);
      }

      void dereference()
      {
        if (0 == InterlockedDecrement64(&refcount))
        {
          deleter_object(static_cast<derived_class*>(this));
        }
      }
    protected:
      virtual ~base() {}
    private:
      deleter deleter_object;
      volatile LONG64 refcount{1};
    };
  }
}
