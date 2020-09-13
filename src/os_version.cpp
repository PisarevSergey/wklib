#include <wklib.h>

wklib::os_version::version::version()
{
    ver_info = { 0 };
    ver_info.dwOSVersionInfoSize = sizeof(ver_info);
    RtlGetVersion(&ver_info);
}

bool wklib::os_version::version::is_win7_plus() const
{
    return ((ver_info.dwMajorVersion > 6) || ((6 == ver_info.dwMajorVersion) && (ver_info.dwMinorVersion >= 1)));
}

bool wklib::os_version::version::is_win8_plus() const
{
    return ((ver_info.dwMajorVersion > 6) || ((6 == ver_info.dwMajorVersion) && (ver_info.dwMinorVersion >= 2)));
}

bool wklib::os_version::version::is_win8_1_plus() const
{
    return ((ver_info.dwMajorVersion > 6) || ((6 == ver_info.dwMajorVersion) && (ver_info.dwMinorVersion >= 3)));
}

bool wklib::os_version::version::is_win10_plus() const
{
    return (ver_info.dwMajorVersion >= 10);
}
