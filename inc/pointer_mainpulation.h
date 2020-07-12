#pragma once

namespace wklib
{
  namespace pointer_manipulation
  {
    template<typename out_type, typename in_type>
    out_type* add_to_ptr(in_type* base, size_t offset)
    {
      const char* result{reinterpret_cast<const char*>(base)};
      result += offset;

      return reinterpret_cast<out_type*>(const_cast<char*>(result));
    }
  }
}
