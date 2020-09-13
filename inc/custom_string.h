#pragma once

namespace wklib
{
    namespace string_facility
    {
        class string final
        {
        public:
            string() noexcept;

            string(NTSTATUS& stat,
                const UNICODE_STRING& string_param,
                ULONG tag,
                POOL_TYPE pt = PagedPool) noexcept;

            string(NTSTATUS& stat,
                const wchar_t* nullterminated_string,
                ULONG tag,
                POOL_TYPE pt = PagedPool) noexcept;

            string(NTSTATUS& stat,
                const wchar_t* buffer,
                const USHORT buffer_size,
                ULONG tag,
                POOL_TYPE pt = PagedPool) noexcept;

            string(const string&) = delete;
            string& operator=(const string&) = delete;

            string(string&& src) noexcept;
            string& operator=(string&& src) noexcept;

            void reset(UNICODE_STRING* new_string) noexcept; //move
            UNICODE_STRING* release() { return us.release(); }

            operator bool() const { return us.get() ? true : false; }

            void* __cdecl operator new(size_t sz, POOL_TYPE pt, ULONG tag) noexcept;
            void* __cdecl operator new(size_t, void* p) noexcept;
            void __cdecl operator delete(void* p) noexcept;

            friend bool operator<(const string& s1, const string& s2) noexcept;
            friend bool operator>(const string& s1, const string& s2) noexcept;

        private:
            wklib::smart_pointers::auto_pointer<UNICODE_STRING, wklib::deleters::pool_deleter> us;
        };

        bool operator<(const string& s1, const string& s2) noexcept;
        bool operator>(const string& s1, const string& s2) noexcept;
    }
}
