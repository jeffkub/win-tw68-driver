#include "device.h"
#include "device.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, TW68DispatchCreate)
#pragma alloc_text (PAGE, TW68DispatchStart)
#pragma alloc_text (PAGE, TW68DispatchStop)
#pragma alloc_text (INIT, DriverEntry)
#endif

NTSTATUS TW68DispatchCreate(
    IN PKSDEVICE Device
)
{
    NTSTATUS status = 0;
    PCAPTURE_DEVICE dev;

    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");

    dev = ExAllocatePoolZero(NonPagedPoolNx, sizeof(CAPTURE_DEVICE), 'veDC');
    if (dev == NULL)
    {
        status = STATUS_INSUFFICIENT_RESOURCES;
    }

    /* TODO: Add to bag */

    Device->Context = dev;

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Exit");

    return status;
}

NTSTATUS TW68DispatchStart(
    IN PKSDEVICE Device,
    IN PIRP Irp,
    IN PCM_RESOURCE_LIST TranslatedResourceList,
    IN PCM_RESOURCE_LIST UntranslatedResourceList
)
{
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");

    return 0;
}

void TW68DispatchStop(
    IN PKSDEVICE Device,
    IN PIRP Irp
)
{
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");
}

const KSDEVICE_DISPATCH TW68DeviceDispatch = {
    TW68DispatchCreate,                     // Pnp Add Device
    TW68DispatchStart,                      // Pnp Start
    NULL,                                   // Post-Start
    NULL,                                   // Pnp Query Stop
    NULL,                                   // Pnp Cancel Stop
    TW68DispatchStop,                       // Pnp Stop
    NULL,                                   // Pnp Query Remove
    NULL,                                   // Pnp Cancel Remove
    NULL,                                   // Pnp Remove
    NULL,                                   // Pnp Query Capabilities
    NULL,                                   // Pnp Surprise Removal
    NULL,                                   // Power Query Power
    NULL,                                   // Power Set Power
    NULL                                    // Pnp Query Interface
};

const KSDEVICE_DESCRIPTOR TW68DeviceDescriptor = {
    &TW68DeviceDispatch,
    0,
    NULL
};

NTSTATUS DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    NTSTATUS status;

    WPP_INIT_TRACING(DriverObject, RegistryPath);

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");

    status = KsInitializeDriver(
        DriverObject,
        RegistryPath,
        &TW68DeviceDescriptor
    );

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Exit");

    return status;
}
