#pragma once

namespace wklib
{
    class lookaside_list
    {
    public:
        lookaside_list(NTSTATUS& stat,
            POOL_TYPE pool_type,
            size_t entry_size,
            const ULONG tag,
            const ULONG flags = 0,
            PALLOCATE_FUNCTION_EX allocf = nullptr,
            PFREE_FUNCTION_EX freef = nullptr);
        ~lookaside_list();

        void* allocate();
        void free(void*);
    private:
        LOOKASIDE_LIST_EX lookaside;
        bool list_successfully_initialized{ false };
    };
}
