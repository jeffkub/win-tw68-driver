#pragma once

EXTERN_C_START

#define FILTER_COUNT 1
#define FILTER_CATEGORIES_COUNT 3

typedef struct _TW68_FILTER
{
    ULONG PrivateDeviceData;  // just a placeholder

} TW68_FILTER, *PTW68_FILTER;

NTSTATUS TW68FilterCreate(
    IN PKSFILTER Filter,
    IN PIRP Irp
);

VOID TW68FilterCleanup(
    IN PTW68_FILTER TW68Filter
);

extern const KSFILTER_DESCRIPTOR* const TW68FilterDescriptorTable[FILTER_COUNT];

EXTERN_C_END
