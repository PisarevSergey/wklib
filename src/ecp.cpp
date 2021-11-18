#include <wklib.h>

NTSTATUS wklib::Ecp::isCsvFsOpen(PFLT_FILTER filter, PFLT_CALLBACK_DATA callbackData, bool& isCsvOpen)
{
    FLT_ASSERT(IRP_MJ_CREATE == callbackData->Iopb->MajorFunction);

    NTSTATUS stat;

    do
    {
        PECP_LIST ecpList;
        stat = FltGetEcpListFromCallbackData(filter, callbackData, &ecpList);
        if (!NT_SUCCESS(stat))
        {
            break;
        }

        if (nullptr == ecpList)
        {
            isCsvOpen = false;
            break;
        }

        void* ecpContext{ nullptr };
        stat = FltFindExtraCreateParameter(filter, ecpList, &GUID_ECP_CSV_DOWN_LEVEL_OPEN, &ecpContext, nullptr);
        if (STATUS_NOT_FOUND == stat)
        {
            isCsvOpen = false;
            stat = STATUS_SUCCESS;
            break;
        }

        if (!NT_SUCCESS(stat))
        {
            break;
        }

        isCsvOpen = ecpContext ? true : false;
    } while (false);

    return stat;
}

NTSTATUS wklib::Ecp::isPrefetchOpen(PFLT_FILTER filter, PFLT_CALLBACK_DATA callbackData, bool& isPrefetch)
{
    FLT_ASSERT(IRP_MJ_CREATE == callbackData->Iopb->MajorFunction);

    NTSTATUS stat;

    do
    {
        PECP_LIST ecpList;
        stat = FltGetEcpListFromCallbackData(filter, callbackData, &ecpList);
        if (!NT_SUCCESS(stat))
        {
            break;
        }

        if (nullptr == ecpList)
        {
            FLT_ASSERT(NT_SUCCESS(stat));
            isPrefetch = false;
            break;
        }

        void* ecpContext;
        stat = FltFindExtraCreateParameter(filter, ecpList, &GUID_ECP_PREFETCH_OPEN, &ecpContext, nullptr);
        if (STATUS_NOT_FOUND == stat)
        {
            isPrefetch = false;
            stat = STATUS_SUCCESS;
            break;
        }

        if (!NT_SUCCESS(stat))
        {
            break;
        }

        isPrefetch = ecpContext ? true : false;

        if (isPrefetch)
        {
            isPrefetch = FltIsEcpFromUserMode(filter, ecpContext) ? false : true;
        }

    } while (false);

    return stat;
}
