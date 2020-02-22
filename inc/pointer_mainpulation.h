#pragma once

namespace win_kernel_lib
{
  namespace pointer_manipulation
  {
    template<typename out_type, typename in_type>
    out_type* add_to_ptr(in_type* base, size_t offset)
    {
      char* result{reinterpret_cast<char*>(base)};
      result += offset;

      return reinterpret_cast<out_type*>(result);
    }
  }
}
