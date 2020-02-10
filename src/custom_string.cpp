#include <win_kernel_lib.h>

win_kernel_lib::string_facility::string::string() noexcept
{}

win_kernel_lib::string_facility::string::string(NTSTATUS& stat,
  const UNICODE_STRING& string_param,
  ULONG tag,
  POOL_TYPE pt) noexcept
{
  auto tmp_str{ win_kernel_lib::unicode_strings::createStringCopy(string_param, tag, pt) };
  if (tmp_str)
  {
    stat = STATUS_SUCCESS;
    us.reset(tmp_str);
  }
  else
  {
    stat = STATUS_INSUFFICIENT_RESOURCES;
  }
}

win_kernel_lib::string_facility::string::string(NTSTATUS& stat,
  const wchar_t* nullterminated_string,
  ULONG tag,
  POOL_TYPE pt) noexcept
{
  auto tmp_str{ win_kernel_lib::unicode_strings::createStringCopy(nullterminated_string, tag, pt) };
  if (tmp_str)
  {
    stat = STATUS_SUCCESS;
    us.reset(tmp_str);
  }
  else
  {
    stat = STATUS_INSUFFICIENT_RESOURCES;
  }
}

win_kernel_lib::string_facility::string::string(NTSTATUS& stat,
  const wchar_t* buffer,
  const USHORT buffer_size,
  ULONG tag,
  POOL_TYPE pt) noexcept
{
  auto tmp_str{ win_kernel_lib::unicode_strings::createStringCopy(buffer, buffer_size, tag, pt) };
  if (tmp_str)
  {
    stat = STATUS_SUCCESS;
    us.reset(tmp_str);
  }
  else
  {
    stat = STATUS_INSUFFICIENT_RESOURCES;
  }

}

win_kernel_lib::string_facility::string::string(string&& src) noexcept
{
  us.reset(src.us.release());
}

win_kernel_lib::string_facility::string& win_kernel_lib::string_facility::string::operator=(string&& src) noexcept
{
  if (this != &src)
  {
    us.reset(src.us.release());
  }

  return *this;
}

void win_kernel_lib::string_facility::string::reset(UNICODE_STRING* new_string) noexcept //move
{
  us.reset(new_string);
}

void* __cdecl win_kernel_lib::string_facility::string::operator new(size_t sz,
  POOL_TYPE pt,
  ULONG tag) noexcept
{
  return ExAllocatePoolWithTag(pt, sz, tag);
}

void __cdecl win_kernel_lib::string_facility::string::operator delete(void* p) noexcept
{
  if (p)
  {
    ExFreePool(p);
  }
}

void* __cdecl win_kernel_lib::string_facility::string::operator new(size_t, void* p) noexcept
{
  return p;
}

bool win_kernel_lib::string_facility::operator<(const string& s1,
  const string& s2) noexcept
{
  return (RtlCompareUnicodeString(s1.us.get(), s2.us.get(), TRUE) < 0);
}

bool win_kernel_lib::string_facility::operator>(const string& s1,
  const string& s2) noexcept
{
  return (RtlCompareUnicodeString(s1.us.get(), s2.us.get(), TRUE) > 0);
}
