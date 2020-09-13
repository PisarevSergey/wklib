#pragma once

namespace wklib
{
    namespace aligning
    {
        template <typename T>
        T* align_up(void* to_align_ptr, const ULONG alignment)
        {
            const ULONG_PTR to_align{ reinterpret_cast<ULONG_PTR>(to_align_ptr) };
            static_assert(sizeof(to_align_ptr) == sizeof(to_align), "wrong size");
            return reinterpret_cast<T*>((to_align / alignment + ((to_align % alignment) ? 1 : 0)) * alignment);
        }

        template <typename T>
        T* align_up_and_get_offset(void* to_align_ptr, const ULONG alignment, ULONG& offset)
        {
            T* aligned_ptr{ align_up<T>(to_align_ptr, alignment) };

            offset = reinterpret_cast<ULONG>(reinterpret_cast<ULONG_PTR>(aligned_ptr) - reinterpret_cast<ULONG_PTR>(to_align_ptr));

            return aligned_ptr;
        }
    }
}
