#pragma once

#include <ntddk.h>

namespace win_kernel_lib
{
  namespace avl_list_facility
  {
    template <typename T,
      PRTL_AVL_COMPARE_ROUTINE comp,
      PRTL_AVL_ALLOCATE_ROUTINE alloc,
      PRTL_AVL_FREE_ROUTINE free>
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


