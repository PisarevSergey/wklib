#pragma once

#include <wdm.h>

namespace win_kernel_lib
{
  namespace os_version
  {
    class version
    {
    public:
      version();

      bool is_win7_plus() const;
      bool is_win8_plus() const;
      bool is_win8_1_plus() const;
      bool is_win10_plus() const;
    private:
      RTL_OSVERSIONINFOW ver_info;
    };
  }
}
