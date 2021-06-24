#pragma once

#include "public.h"

EXTERN_C_START

typedef struct _DEVICE_CONTEXT
{
    ULONG PrivateDeviceData;  // just a placeholder

} DEVICE_CONTEXT, *PDEVICE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, DeviceGetContext)

NTSTATUS tw68xxCreateDevice(
    _Inout_ PWDFDEVICE_INIT DeviceInit
);

NTSTATUS tw68xxEvtDeviceAdd(
    _In_    WDFDRIVER       Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
);

VOID tw68xxEvtDriverContextCleanup(
    _In_ WDFOBJECT DriverObject
);

NTSTATUS DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
);

EXTERN_C_END
