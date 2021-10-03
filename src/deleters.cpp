#include <wklib.h>

void wklib::deleters::pool_deleter::operator()(void* p)
{
    if (p)
    {
        ExFreePool(p);
    }
}

void wklib::deleters::pool_deleter::operator()(const void* p)
{
    if (p)
    {
        ExFreePool(const_cast<void*>(p));
    }
}

void wklib::deleters::fltmgr_context_deleter::operator()(void* context)
{
    if (context)
    {
        FltReleaseContext(context);
    }
}

void wklib::deleters::FltSecurityDescriptor::operator()(PSECURITY_DESCRIPTOR sd) const
{
    FltFreeSecurityDescriptor(sd);
}
