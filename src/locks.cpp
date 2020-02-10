#include <win_kernel_lib.h>

win_kernel_lib::locks::eresource::eresource()
{
  ExInitializeResourceLite(&lock);
}

win_kernel_lib::locks::eresource::~eresource()
{
  ExDeleteResourceLite(&lock);
}

void win_kernel_lib::locks::eresource::lock_shared()
{
  FltAcquireResourceShared(&lock);
}

void win_kernel_lib::locks::eresource::lock_exclusive()
{
  FltAcquireResourceExclusive(&lock);
}

void win_kernel_lib::locks::eresource::release()
{
  FltReleaseResource(&lock);
}
