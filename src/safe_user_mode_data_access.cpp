#include <safe_user_mode_data_access.h>

NTSTATUS win_kernel_lib::safe_user_mode_data_access::copy_data(void* destination_kernel_buffer,
  size_t destination_buffer_size,
  void* source_user_or_kernel_buffer,
  size_t source_buffer_size,
  bool user_mode_access,
  bool check_for_read,
  ULONG alignment)
{
  NTSTATUS stat{STATUS_UNSUCCESSFUL};

  const bool valid_address{ user_mode_access ? is_valid_user_address(source_user_or_kernel_buffer, source_buffer_size, check_for_read, alignment) : true };
  __try
  {
    if (valid_address)
    {
      if (destination_buffer_size >= source_buffer_size)
      {
        RtlCopyMemory(destination_kernel_buffer, source_user_or_kernel_buffer, source_buffer_size);
        stat = STATUS_SUCCESS;
      }
      else
      {
        stat = STATUS_INVALID_PARAMETER;
      }
    }
    else
    {
      stat = STATUS_INVALID_PARAMETER;
    }
  }
  __except (EXCEPTION_EXECUTE_HANDLER)
  {
    stat = GetExceptionCode();
  }

  return stat;
}

bool win_kernel_lib::safe_user_mode_data_access::is_valid_user_address(void* base,
  size_t size,
  bool check_for_read,
  ULONG alignment)
{
  bool valid{ true };

  __try
  {
    if (check_for_read)
    {
      ProbeForRead(base, size, alignment);
    }
    else
    {
      ProbeForWrite(base, size, alignment);
    }
  }
  __except (EXCEPTION_EXECUTE_HANDLER)
  {
    valid = false;
  }

  return valid;
}
