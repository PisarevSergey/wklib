#pragma once

#include <wdm.h>

namespace safe_user_mode_data_access
{
  NTSTATUS copy_data(void* destination_kernel_buffer,
    size_t destination_buffer_size,
    void* source_user_or_kernel_buffer,
    size_t source_buffer_size,
    bool user_mode_access,
    bool check_for_read = true,
    ULONG alignment = 1);

  bool is_valid_user_address(void* base,
    size_t size,
    bool check_for_read = true,
    ULONG alignment = 1);
}
