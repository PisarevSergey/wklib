#pragma once

#include <ntddk.h>

namespace win_kernel_lib
{
  namespace avl_list_facility
  {
    using allocate_routine = void* (*)(CLONG size);
    using free_routine = void (*)(void*);

    template <typename T,
      allocate_routine custom_alloc,
      free_routine custom_free>
    class avl_list
    {
    public:
      avl_list()
      {
        RtlInitializeGenericTableAvl(&table, comp, alloc, free, nullptr);
      }

      ~avl_list()
      {
        while (auto e{ get_element_by_number(0) })
        {
          delete_entry(e);
        }
      }

      bool insert(void* item, CLONG item_size)
      {
        BOOLEAN inserted;
        RtlInsertElementGenericTableAvl(&table, item, item_size, &inserted);

        return (TRUE == inserted);
      }

      T* get_element_by_key(void* key_entry)
      {
        return static_cast<T*>(RtlLookupElementGenericTableAvl(&table, key_entry));
      }

      static void* alloc(RTL_AVL_TABLE*, CLONG size)
      {
        return custom_alloc(size);
      }

      static void free(RTL_AVL_TABLE*, void* p)
      {
        T* object{static_cast<char*>(p) + sizeof(RTL_BALANCED_LINKS)};
        object->~T();

        custom_free(p);
      }

      RTL_GENERIC_COMPARE_RESULTS comp(RTL_AVL_TABLE*,
        void* first,
        void* second)
      {
        auto result{ GenericEqual };

        T* first_object{ static_cast<T*>(first) };
        T* second_object{ static_cast<T*>(second) };

        if (*first_object < *second_object)
        {
          result = GenericLessThan;
        }
        else if (*first_object > * second_object)
        {
          result = GenericGreaterThan;
        }

        return result;
      }

    private:
      T* get_element_by_number(ULONG num)
      {
        return static_cast<T*>(RtlGetElementGenericTableAvl(&table, num));
      }

      void delete_entry(void* entry)
      {
        RtlDeleteElementGenericTableAvl(&table, entry);
      }

    private:
      RTL_AVL_TABLE table;
    };
  }
}


