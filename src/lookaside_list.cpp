#include <wklib.h>

wklib::lookaside_list::lookaside_list(NTSTATUS& stat,
    POOL_TYPE pool_type,
    size_t entry_size,
    const ULONG tag,
    const ULONG flags,
    PALLOCATE_FUNCTION_EX allocf,
    PFREE_FUNCTION_EX freef)
{
    constexpr USHORT lookaside_depth{ 0 }; //Reserved. Always set this parameter to zero
    stat = ExInitializeLookasideListEx(&lookaside,
        allocf,
        freef,
        pool_type,
        flags,
        entry_size,
        tag,
        lookaside_depth);
    if (NT_SUCCESS(stat))
    {
        list_successfully_initialized = true;
    }
}

wklib::lookaside_list::~lookaside_list()
{
    if (list_successfully_initialized)
    {
        ExDeleteLookasideListEx(&lookaside);
    }
}

void* wklib::lookaside_list::allocate()
{
    return ExAllocateFromLookasideListEx(&lookaside);
}

void wklib::lookaside_list::free(void* p)
{
    ASSERT(p);
    ExFreeToLookasideListEx(&lookaside, p);
}
