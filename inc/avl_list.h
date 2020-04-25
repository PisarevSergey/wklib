#pragma once

namespace win_kernel_lib
{
  namespace avl_list_facility
  {
    template <typename T,
      typename list_entry_allocator_type,
      typename entry_deleter>
    class avl_list  //list of pointers to objects
    {
    public:
      using stored_item_type = T*;

      //avl_list() : allocator{ nullptr }, initialized{false}
      //{
      //  RtlZeroMemory(&table, sizeof(table));
      //}

      avl_list(list_entry_allocator_type* allocator_param) : allocator{ allocator_param }/*, initialized{true}*/
      {
        ASSERT(allocator);

        RtlInitializeGenericTableAvl(&table, comp, alloc, free, this);
      }

      ~avl_list()
      {
        //if (initialized)
        {
          clear();

          allocator = nullptr;
        }
      }

      //void initialize(entry_allocator_type* allocator_param)
      //{
      //  ASSERT(allocator_param);

      //  allocator = allocator_param;
      //  RtlInitializeGenericTableAvl(&table, comp, alloc, free, this);

      //  initialized = true;
      //}

      stored_item_type* insert(stored_item_type item_to_insert, bool& inserted_as_new_element) // copy of pointer to object
      {
        stored_item_type* entry{ nullptr };
        inserted_as_new_element = false;

        if (item_to_insert)
        {
          BOOLEAN inserted;
          entry = static_cast<stored_item_type*>(RtlInsertElementGenericTableAvl(&table,
            &item_to_insert,
            sizeof(item_to_insert), &inserted));
          if (entry)
          {
            ASSERT(*entry);

            if (inserted)
            {
              inserted_as_new_element = true;
            }
          }
        }

        return entry;
      }

      stored_item_type* get_element_by_key(stored_item_type key_entry)
      {
        return static_cast<stored_item_type*>(RtlLookupElementGenericTableAvl(&table, &key_entry));
      }

      void clear()
      {
        //ASSERT(true == initialized);

        while (auto e{ get_element_by_number(0) })
        {
          delete_entry(e);
        }
      }

      static void* alloc(RTL_AVL_TABLE* table_param, CLONG size)
      {
        return static_cast<avl_list*>(table_param->TableContext)->allocator->allocate(size);
      }

      static void free(RTL_AVL_TABLE* table_param, void* p)
      {
        stored_item_type* entry{ static_cast<stored_item_type*>(Add2Ptr(p, sizeof(RTL_BALANCED_LINKS))) };
        static_cast<avl_list*>(table_param->TableContext)->deleter(*entry);

        static_cast<avl_list*>(table_param->TableContext)->allocator->deallocate(p);
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
      list_entry_allocator_type* allocator;
      entry_deleter deleter;
      //bool initialized;
    };
  }
}


