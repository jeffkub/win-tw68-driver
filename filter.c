#include "public.h"

#include "filter.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, TW68FilterCreate)
#pragma alloc_text (PAGE, TW68FilterCleanup)
#endif

NTSTATUS TW68FilterCreate(
    IN PKSFILTER Filter,
    IN PIRP Irp
)
{
    NTSTATUS status;
    PTW68_FILTER tw68Filter = NULL;

    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_FILTER,
        "%!FUNC!");

    tw68Filter = ExAllocatePoolZero(NonPagedPoolNx, sizeof(TW68_FILTER), 'liFC');
    if (tw68Filter == NULL)
    {
        TraceEvents(TRACE_LEVEL_CRITICAL, DBG_FILTER,
            "%!FUNC!: ExAllocatePoolZero failed");
        status = STATUS_INSUFFICIENT_RESOURCES;
        goto fail;
    }

    status = KsAddItemToObjectBag(Filter->Bag, tw68Filter, TW68FilterCleanup);

    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_CRITICAL, DBG_FILTER,
            "%!FUNC!: KsAddItemToObjectBag failed: %!STATUS!", status);
        goto fail;
    }

    Filter->Context = tw68Filter;

    return STATUS_SUCCESS;

fail:
    if (tw68Filter)
        ExFreePool(tw68Filter);

    return status;
}

VOID TW68FilterCleanup(
    IN PTW68_FILTER TW68Filter
)
{
    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_FILTER,
        "%!FUNC!");

    ExFreePool(TW68Filter);
}

static const KSFILTER_DISPATCH TW68FilterDispatch = {
    TW68FilterCreate,                       // Filter Create
    NULL,                                   // Filter Close
    NULL,                                   // Filter Process
    NULL                                    // Filter Reset
};

static const GUID g_KSNAME_Filter = { STATIC_KSNAME_Filter };

static const GUID TW68FilterCategories[FILTER_CATEGORIES_COUNT] = {
    STATICGUIDOF(KSCATEGORY_VIDEO),
    STATICGUIDOF(KSCATEGORY_CAPTURE),
    STATICGUIDOF(KSCATEGORY_VIDEO_CAMERA)
};

static const KSFILTER_DESCRIPTOR TW68FilterDescriptor = {
    &TW68FilterDispatch,                    // Dispatch Table
    NULL,                                   // Automation Table
    KSFILTER_DESCRIPTOR_VERSION,            // Version
    0,                                      // Flags
    &g_KSNAME_Filter,                       // Reference GUID
    DEFINE_KSFILTER_PIN_DESCRIPTORS(TW68PinDescriptors),
    DEFINE_KSFILTER_CATEGORIES(TW68FilterCategories),
    0,
    sizeof(KSNODE_DESCRIPTOR),
    NULL,
    0,
    NULL,
    NULL                                    // Component ID
};

const KSFILTER_DESCRIPTOR * const TW68FilterDescriptorTable[FILTER_COUNT] = {
    &TW68FilterDescriptor
};
