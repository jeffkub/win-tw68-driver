#include "public.h"

#include "device.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, TW68DeviceAdd)
#pragma alloc_text (PAGE, TW68DeviceCleanup)
#pragma alloc_text (PAGE, TW68DeviceStart)
#pragma alloc_text (PAGE, TW68DeviceStop)
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, DriverUnload)
#endif

NTSTATUS TW68DeviceAdd(
    IN PKSDEVICE Device
)
{
    NTSTATUS status;
    PTW68_DEVICE tw68Dev = NULL;

    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
        "%!FUNC!");

    tw68Dev = ExAllocatePoolZero(NonPagedPoolNx, sizeof(TW68_DEVICE), 'veDC');
    if (tw68Dev == NULL)
    {
        TraceEvents(TRACE_LEVEL_CRITICAL, DBG_DEV,
            "%!FUNC!: ExAllocatePoolZero failed");
        status = STATUS_INSUFFICIENT_RESOURCES;
        goto fail;
    }

    KsAcquireDevice(Device);
    status = KsAddItemToObjectBag(Device->Bag, tw68Dev, TW68DeviceCleanup);
    KsReleaseDevice(Device);

    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_CRITICAL, DBG_DEV,
            "%!FUNC!: KsAddItemToObjectBag failed: %!STATUS!", status);
        goto fail;
    }

    Device->Context = tw68Dev;

    return STATUS_SUCCESS;

fail:
    if (tw68Dev)
        ExFreePool(tw68Dev);

    return status;
}

VOID TW68DeviceCleanup(
    IN PTW68_DEVICE TW68Dev
)
{
    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
        "%!FUNC!");

    ExFreePool(TW68Dev);
}

NTSTATUS TW68DeviceStart(
    IN PKSDEVICE Device,
    IN PIRP Irp,
    IN PCM_RESOURCE_LIST TranslatedResourceList,
    IN PCM_RESOURCE_LIST UntranslatedResourceList
)
{
    PCM_FULL_RESOURCE_DESCRIPTOR list;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR desc;

    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
        "%!FUNC!");
    
    if (TranslatedResourceList == NULL)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
            "%!FUNC!: No resources found");
        return STATUS_DEVICE_CONFIGURATION_ERROR;
    }

    list = TranslatedResourceList->List;
    for (unsigned ix = 0; ix < TranslatedResourceList->Count; ix++)
    {
        for (unsigned jx = 0; jx < list->PartialResourceList.Count; jx++)
        {
            desc = list->PartialResourceList.PartialDescriptors + jx;

            switch (desc->Type)
            {
                case CmResourceTypeMemory:
                    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
                        "%!FUNC!: CmResourceTypeMemory found");
                    break;

                case CmResourceTypeInterrupt:
                    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
                        "%!FUNC!: CmResourceTypeInterrupt found");
                    break;

                default:
                    break;
            }
        }

        list = (PCM_FULL_RESOURCE_DESCRIPTOR)(list->PartialResourceList.PartialDescriptors +
                                              list->PartialResourceList.Count);
    }
    
    return STATUS_SUCCESS;
}

VOID TW68DeviceStop(
    IN PKSDEVICE Device,
    IN PIRP Irp
)
{
    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_DEV,
        "%!FUNC!");
}

static const KSDEVICE_DISPATCH TW68DeviceDispatch = {
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

static const KSDEVICE_DESCRIPTOR TW68DeviceDescriptor = {
    &TW68DeviceDispatch,                    // Dispatch Table
    FILTER_COUNT,                           // Filter Descriptor Count
    TW68FilterDescriptorTable,              // Filter Descriptor Table
    0,                                      // Version
    0                                       // Flags
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

    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_CRITICAL, DBG_INIT,
            "%!FUNC! KsInitializeDriver failed: %!STATUS!", status);
        WPP_CLEANUP(DriverObject);
    }

    DriverObject->DriverUnload = DriverUnload;

    return status;
}

_Use_decl_annotations_
VOID DriverUnload(
    PDRIVER_OBJECT DriverObject
)
{
    WPP_CLEANUP(DriverObject);
}
