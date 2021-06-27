#pragma once

EXTERN_C_START

#define PIN_COUNT 1
#define PIN_DATA_RANGE_COUNT 1

typedef struct _TW68_PIN
{
    ULONG PrivateDeviceData;  // just a placeholder

} TW68_PIN, *PTW68_PIN;

NTSTATUS TW68PinCreate(
    IN PKSPIN Pin,
    IN PIRP Irp
);

void TW68PinCleanup(
    IN PTW68_PIN TW68Pin
);

NTSTATUS TW68PinProcess(
    IN PKSPIN Pin
);

NTSTATUS TW68PinSetFormat(
    IN PKSPIN Pin,
    IN PKSDATAFORMAT OldFormat OPTIONAL,
    IN PKSMULTIPLE_ITEM OldAttributeList OPTIONAL,
    IN const KSDATARANGE* DataRange,
    IN const KSATTRIBUTE_LIST* AttributeRange OPTIONAL
);

NTSTATUS TW68SetState(
    IN PKSPIN Pin,
    IN KSSTATE ToState,
    IN KSSTATE FromState
);

NTSTATUS TW68IntersectHandler(
    IN PKSFILTER Filter,
    IN PIRP Irp,
    IN PKSP_PIN PinInstance,
    IN PKSDATARANGE CallerDataRange,
    IN PKSDATARANGE DescriptorDataRange,
    IN ULONG BufferSize,
    OUT PVOID Data OPTIONAL,
    OUT PULONG DataSize
);

extern const KSPIN_DESCRIPTOR_EX TW68PinDescriptors[PIN_COUNT];

EXTERN_C_END
