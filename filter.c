#include "public.h"

#include "filter.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, TW68FilterCreate)
#endif

NTSTATUS TW68FilterCreate(
    IN PKSFILTER Filter,
    IN PIRP Irp
)
{
    PAGED_CODE();

    return STATUS_SUCCESS;
}

const KSFILTER_DISPATCH TW68FilterDispatch = {
    TW68FilterCreate,                       // Filter Create
    NULL,                                   // Filter Close
    NULL,                                   // Filter Process
    NULL                                    // Filter Reset
};

const GUID g_KSNAME_Filter = { STATIC_KSNAME_Filter };

const GUID TW68FilterCategories[FILTER_CATEGORIES_COUNT] = {
    STATICGUIDOF(KSCATEGORY_VIDEO),
    STATICGUIDOF(KSCATEGORY_CAPTURE),
    STATICGUIDOF(KSCATEGORY_VIDEO_CAMERA)
};

const KSFILTER_DESCRIPTOR TW68FilterDescriptor = {
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
