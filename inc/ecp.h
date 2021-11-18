#pragma once

namespace wklib
{
    namespace Ecp
    {
        NTSTATUS isCsvFsOpen(PFLT_FILTER filter, PFLT_CALLBACK_DATA callbackData, bool& isCsv);
        NTSTATUS isPrefetchOpen(PFLT_FILTER filter, PFLT_CALLBACK_DATA callbackData, bool& isPrefetch);
    }
}
