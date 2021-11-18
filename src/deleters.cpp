#include <wklib.h>

void wklib::deleters::pool_deleter::operator()(void* p) const
{
    ExFreePool(p);
}

void wklib::deleters::pool_deleter::operator()(const void* p) const
{
    ExFreePool(p);
}

void wklib::deleters::fltmgr_context_deleter::operator()(void* context) const
{
    FltReleaseContext(context);
}

void wklib::deleters::FltSecurityDescriptor::operator()(PSECURITY_DESCRIPTOR sd) const
{
    FltFreeSecurityDescriptor(sd);
}

void wklib::deleters::FltFileNameInformationDeleter::operator()(PFLT_FILE_NAME_INFORMATION fileName) const
{
    FltReleaseFileNameInformation(fileName);
}

void wklib::deleters::ReferencedKernelObject::operator()(void* object) const
{
    ObDereferenceObject(object);
}

void wklib::deleters::FltHandle::operator()(HANDLE fltHandle) const
{
    FltClose(fltHandle);
}

void wklib::deleters::ReferencedFltObject::operator()(void* fltObject) const
{
    FltObjectDereference(fltObject);
}
