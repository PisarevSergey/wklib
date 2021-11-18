#pragma once

namespace wklib
{
    namespace deleters
    {
        template <typename T>
        class default_deleter
        {
        public:
            void operator()(T* ptr)
            {
                delete ptr;
            }
        };

        class pool_deleter
        {
        public:
            void operator()(void* p) const;
            void operator()(const void* p) const;
        };

        template <typename T>
        class referenced_object_deleter
        {
        public:
            void operator()(T* obj)
            {
                if (obj)
                {
                    obj->dereference();
                }
            }
        };

        class fltmgr_context_deleter
        {
        public:
            void operator()(void* context) const;
        };

        struct FltSecurityDescriptor
        {
            void operator()(PSECURITY_DESCRIPTOR sd) const;
        };

        struct FltFileNameInformationDeleter final
        {
            void operator()(PFLT_FILE_NAME_INFORMATION fileName) const;
        };

        struct ReferencedKernelObject final
        {
            void operator()(void* object) const;
        };

        struct FltHandle final
        {
            void operator()(HANDLE fltHandle) const;
        };

        struct ReferencedFltObject final
        {
            void operator()(void* fltObject) const;
        };
    }
}
