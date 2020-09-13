#include <wklib.h>

wklib::locks::eresource::eresource()
{
    ExInitializeResourceLite(&lock);
}

wklib::locks::eresource::~eresource()
{
    ExDeleteResourceLite(&lock);
}

void wklib::locks::eresource::lock_shared()
{
    FltAcquireResourceShared(&lock);
}

void wklib::locks::eresource::lock_exclusive()
{
    FltAcquireResourceExclusive(&lock);
}

void wklib::locks::eresource::release()
{
    FltReleaseResource(&lock);
}

wklib::locks::mutex::mutex()
{
    KeInitializeMutex(&mtx, 0);
}

void wklib::locks::mutex::lock()
{
#if DBG
    NTSTATUS acquire_status =
#endif
        KeWaitForMutexObject(&mtx, Executive, KernelMode, FALSE, nullptr);

    ASSERT(STATUS_SUCCESS == acquire_status);
}

void wklib::locks::mutex::unlock()
{
    KeReleaseMutex(&mtx, FALSE);
}
