#include <wklib.h>

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

win_kernel_lib::locks::mutex::mutex()
{
  KeInitializeMutex(&mtx, 0);
}

void win_kernel_lib::locks::mutex::lock()
{
#if DBG
  NTSTATUS acquire_status =
#endif
  KeWaitForMutexObject(&mtx, Executive, KernelMode, FALSE, nullptr);

  ASSERT(STATUS_SUCCESS == acquire_status);
}

void win_kernel_lib::locks::mutex::unlock()
{
  KeReleaseMutex(&mtx, FALSE);
}
