#pragma once

namespace win_kernel_lib
{
  namespace avl_list_facility
  {
    using allocate_routine = void* (*)(CLONG size);
    using free_routine = void (*)(void*);

    template <typename T,
      allocate_routine custom_alloc,
      free_routine custom_free>
    class avl_list  //list of pointers to objects
    {
    public:
      using stored_item_type = T*;

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

      bool insert(stored_item_type item) // copy of pointer to object
      {
        BOOLEAN inserted;
        RtlInsertElementGenericTableAvl(&table, &item, sizeof(item), &inserted);

        return (inserted ? true : false);
      }

      stored_item_type* get_element_by_key(stored_item_type key_entry)
      {
        return static_cast<stored_item_type*>(RtlLookupElementGenericTableAvl(&table, &key_entry));
      }

      static void* alloc(RTL_AVL_TABLE*, CLONG size)
      {
        return custom_alloc(size);
      }

      static void free(RTL_AVL_TABLE*, void* p)
      {
        stored_item_type* entry{ static_cast<stored_item_type*>(Add2Ptr(p, sizeof(RTL_BALANCED_LINKS))) };
        delete *entry;

        custom_free(p);
      }

      static RTL_GENERIC_COMPARE_RESULTS comp(RTL_AVL_TABLE*,
        void* first,
        void* second)
      {
        auto result{ GenericEqual };

        stored_item_type* first_object{ static_cast<stored_item_type*>(first) };
        stored_item_type* second_object{ static_cast<stored_item_type*>(second) };

        if (**first_object < **second_object)
        {
          result = GenericLessThan;
        }
        else if (**first_object > **second_object)
        {
          result = GenericGreaterThan;
        }

        return result;
      }

    private:
      stored_item_type* get_element_by_number(ULONG num)
      {
        return static_cast<stored_item_type*>(RtlGetElementGenericTableAvl(&table, num));
      }

      void delete_entry(stored_item_type* entry)
      {
        RtlDeleteElementGenericTableAvl(&table, entry);
      }

    private:
      RTL_AVL_TABLE table;
    };
  }
}


