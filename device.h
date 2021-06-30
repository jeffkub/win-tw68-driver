#pragma once

EXTERN_C_START

typedef struct _TW68_DEVICE
{
    ULONG PrivateDeviceData;  // just a placeholder

} TW68_DEVICE, *PTW68_DEVICE;

NTSTATUS TW68DeviceAdd(
    IN PKSDEVICE Device
);

VOID TW68DeviceCleanup(
    IN PTW68_DEVICE CapDev
);

NTSTATUS TW68DeviceStart(
    IN PKSDEVICE Device,
    IN PIRP Irp,
    IN PCM_RESOURCE_LIST TranslatedResourceList,
    IN PCM_RESOURCE_LIST UntranslatedResourceList
);

VOID TW68DeviceStop(
    IN PKSDEVICE Device,
    IN PIRP Irp
);

NTSTATUS DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
);

DRIVER_UNLOAD DriverUnload;

EXTERN_C_END
