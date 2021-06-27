#pragma once

EXTERN_C_START

typedef struct _CAPTURE_DEVICE
{
    ULONG PrivateDeviceData;  // just a placeholder

} CAPTURE_DEVICE, *PCAPTURE_DEVICE;

//WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, DeviceGetContext)

NTSTATUS TW68DeviceAdd(
    IN PKSDEVICE Device
);

void TW68DeviceCleanup(
    IN PCAPTURE_DEVICE CapDev
);

NTSTATUS TW68DeviceStart(
    IN PKSDEVICE Device,
    IN PIRP Irp,
    IN PCM_RESOURCE_LIST TranslatedResourceList,
    IN PCM_RESOURCE_LIST UntranslatedResourceList
);

void TW68DeviceStop(
    IN PKSDEVICE Device,
    IN PIRP Irp
);

NTSTATUS DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
);

EXTERN_C_END
