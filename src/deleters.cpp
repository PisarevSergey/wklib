#include <win_kernel_lib.h>

void win_kernel_lib::deleters::pool_deleter::operator()(void* p)
{
  if (p)
  {
    ExFreePool(p);
  }
}