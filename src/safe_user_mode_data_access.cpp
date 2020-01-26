#include <safe_user_mode_data_access.h>

NTSTATUS safe_user_mode_data_access::copy_data(void* destination_kernel_buffer,
  size_t destination_buffer_size,
  void* source_user_or_kernel_buffer,
  size_t source_buffer_size,
  bool read_access,
  ULONG alignment)
{
  NTSTATUS stat{STATUS_SUCCESS};

  __try
  {
    if (UserMode == ExGetPreviousMode())
    {
      if (read_access)
      {
        ProbeForRead(source_user_or_kernel_buffer, source_buffer_size, alignment);
      }
      else
      {
        ProbeForRead(source_user_or_kernel_buffer, source_buffer_size, alignment);
      }
    }

    if (destination_buffer_size >= source_buffer_size)
    {
      RtlCopyMemory(destination_kernel_buffer, source_user_or_kernel_buffer, source_buffer_size);
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

bool safe_user_mode_data_access::is_valid_user_address(void* base,
  ULONG size,
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
