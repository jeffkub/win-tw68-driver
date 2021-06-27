#include "public.h"

#include "device.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, TW68DeviceAdd)
#pragma alloc_text (PAGE, TW68DeviceCleanup)
#pragma alloc_text (PAGE, TW68DeviceStart)
#pragma alloc_text (PAGE, TW68DeviceStop)
#pragma alloc_text (INIT, DriverEntry)
#endif

NTSTATUS TW68DeviceAdd(
    IN PKSDEVICE Device
)
{
    NTSTATUS status;
    PTW68_DEVICE tw68Dev = NULL;

    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
        "%!FUNC! entry");

    tw68Dev = ExAllocatePoolZero(NonPagedPoolNx, sizeof(TW68_DEVICE), 'veDC');
    if (tw68Dev == NULL)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
            "ExAllocatePoolZero failed");
        status = STATUS_INSUFFICIENT_RESOURCES;
        goto fail;
    }

    KsAcquireDevice(Device);
    status = KsAddItemToObjectBag(Device->Bag, tw68Dev, TW68DeviceCleanup);
    KsReleaseDevice(Device);

    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
            "KsAddItemToObjectBag failed: %!STATUS!", status);
        goto fail;
    }

    Device->Context = tw68Dev;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
        "%!FUNC! exit");

    return STATUS_SUCCESS;

fail:
    if (tw68Dev)
        ExFreePool(tw68Dev);

    return status;
}

void TW68DeviceCleanup(
    IN PTW68_DEVICE TW68Dev
)
{
    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
        "%!FUNC! entry");

    ExFreePool(TW68Dev);

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
        "%!FUNC! exit");
}

NTSTATUS TW68DeviceStart(
    IN PKSDEVICE Device,
    IN PIRP Irp,
    IN PCM_RESOURCE_LIST TranslatedResourceList,
    IN PCM_RESOURCE_LIST UntranslatedResourceList
)
{
    NTSTATUS status;
    PTW68_DEVICE tw68Dev = Device->Context;

    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
        "%!FUNC! entry");

    if (!Device->Started)
    {
        /* Create the filter device */
        KsAcquireDevice(Device);
        status = KsCreateFilterFactory(
            Device->FunctionalDeviceObject,
            &TW68FilterDescriptor,
            L"GLOBAL",
            NULL,
            KSCREATE_ITEM_FREEONSTOP,
            NULL,
            NULL,
            NULL);
        KsReleaseDevice(Device);

        if (!NT_SUCCESS(status))
            goto fail;
    }

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
        "%!FUNC! exit");

    return STATUS_SUCCESS;

fail:
    return status;
}

void TW68DeviceStop(
    IN PKSDEVICE Device,
    IN PIRP Irp
)
{
    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
        "%!FUNC! entry");

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
        "%!FUNC! exit");
}

const KSDEVICE_DISPATCH TW68DeviceDispatch = {
    TW68DeviceAdd,                          // Pnp Add Device
    TW68DeviceStart,                        // Pnp Start
    NULL,                                   // Post-Start
    NULL,                                   // Pnp Query Stop
    NULL,                                   // Pnp Cancel Stop
    TW68DeviceStop,                         // Pnp Stop
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

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_INIT,
        "%!FUNC! TW68xx driver init");

    status = KsInitializeDriver(
        DriverObject,
        RegistryPath,
        &TW68DeviceDescriptor
    );

    return status;
}
