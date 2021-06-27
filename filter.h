#pragma once

EXTERN_C_START

#define FILTER_CATEGORIES_COUNT 3

NTSTATUS TW68FilterCreate(
    IN PKSFILTER Filter,
    IN PIRP Irp
);

extern const KSFILTER_DESCRIPTOR TW68FilterDescriptor;

EXTERN_C_END
