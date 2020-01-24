#include <wdm.h>
#include <deleters.h>

void win_kernel_lib::deleters::pool_deleter::operator()(void* p)
{
  if (p)
  {
    ExFreePool(p);
  }
}