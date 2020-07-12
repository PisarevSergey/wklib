#pragma once

namespace wklib
{
  namespace deleters
  {
    template <typename T>
    class default_deleter
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

    template <typename T>
    class referenced_object_deleter
    {
    public:
      void operator()(T* obj)
      {
        if (obj)
        {
          obj->dereference();
        }
      }
    };

    class fltmgr_context_deleter
    {
    public:
      void operator()(void* context);
    };
  }
}
