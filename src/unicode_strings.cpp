#include <win_kernel_lib.h>

UNICODE_STRING* win_kernel_lib::unicode_strings::createStringCopy(const UNICODE_STRING& src,
  ULONG tag,
  POOL_TYPE pt)
{
  UNICODE_STRING* new_string{ nullptr };
  const auto size_required{ sizeof(*new_string) + src.Length };

  new_string = static_cast<UNICODE_STRING*>(ExAllocatePoolWithTag(pt, size_required, tag));
  if (new_string)
  {
    new_string->Length = 0;
    new_string->MaximumLength = src.Length;
    new_string->Buffer = reinterpret_cast<wchar_t*>(new_string + 1);
    RtlCopyUnicodeString(new_string, &src);
  }

  return new_string;
}

UNICODE_STRING* win_kernel_lib::unicode_strings::createStringCopy(const wchar_t* src,
  size_t src_size_in_bytes,
  ULONG tag,
  POOL_TYPE pt)
{
  UNICODE_STRING source;
  source.Length = source.MaximumLength = static_cast<USHORT>(src_size_in_bytes);
  source.Buffer = const_cast<wchar_t*>(src);

  return createStringCopy(source, tag, pt);
}
