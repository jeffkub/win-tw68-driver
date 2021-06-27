#include "public.h"

#include "pin.tmh"

#define DMAX_X 320
#define DMAX_Y 240
#define D_X 320
#define D_Y 240

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, TW68PinCreate)
#pragma alloc_text (PAGE, TW68PinProcess)
#pragma alloc_text (PAGE, TW68PinSetFormat)
#pragma alloc_text (PAGE, TW68SetState)
#pragma alloc_text (PAGE, TW68IntersectHandler)
#endif

NTSTATUS TW68PinCreate(
    IN PKSPIN Pin,
    IN PIRP Irp
)
{
    PAGED_CODE();

    return STATUS_SUCCESS;
}

NTSTATUS TW68PinProcess(
    IN PKSPIN Pin
)
{
    PAGED_CODE();

    return STATUS_SUCCESS;
}

NTSTATUS TW68PinSetFormat(
    IN PKSPIN Pin,
    IN PKSDATAFORMAT OldFormat OPTIONAL,
    IN PKSMULTIPLE_ITEM OldAttributeList OPTIONAL,
    IN const KSDATARANGE* DataRange,
    IN const KSATTRIBUTE_LIST* AttributeRange OPTIONAL
)
{
    PAGED_CODE();

    return STATUS_SUCCESS;
}

NTSTATUS TW68SetState(
    IN PKSPIN Pin,
    IN KSSTATE ToState,
    IN KSSTATE FromState
)
{
    PAGED_CODE();

    return STATUS_SUCCESS;
}

NTSTATUS TW68IntersectHandler(
    IN PKSFILTER Filter,
    IN PIRP Irp,
    IN PKSP_PIN PinInstance,
    IN PKSDATARANGE CallerDataRange,
    IN PKSDATARANGE DescriptorDataRange,
    IN ULONG BufferSize,
    OUT PVOID Data OPTIONAL,
    OUT PULONG DataSize
)
{
    PAGED_CODE();

    return STATUS_SUCCESS;
}

const KSPIN_DISPATCH TW68PinDispatch = {
    TW68PinCreate,                          // Pin Create
    NULL,                                   // Pin Close
    TW68PinProcess,                         // Pin Process
    NULL,                                   // Pin Reset
    TW68PinSetFormat,                       // Pin Set Data Format
    TW68SetState,                           // Pin Set Device State
    NULL,                                   // Pin Connect
    NULL,                                   // Pin Disconnect
    NULL,                                   // Clock Dispatch
    NULL                                    // Allocator Dispatch
};

const KS_DATARANGE_VIDEO FormatYUY2_Capture = {
    // KSDATARANGE
    {
        sizeof(KS_DATARANGE_VIDEO),            // FormatSize
        0,                                      // Flags
        DMAX_X * DMAX_Y * 2,                    // SampleSize
        0,                                      // Reserved
        STATICGUIDOF(KSDATAFORMAT_TYPE_VIDEO), // aka. MEDIATYPE_Video
        0x32595559, 0x0000, 0x0010, 0x80, 0x00,
        0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71,     //aka. MEDIASUBTYPE_YUY2,
        STATICGUIDOF(KSDATAFORMAT_SPECIFIER_VIDEOINFO) // aka. FORMAT_VideoInfo
    },

    TRUE,               // BOOL,  bFixedSizeSamples (all samples same size?)
    FALSE,              // BOOL,  bTemporalCompression (all I frames?)
    0,                  // Reserved (was StreamDescriptionFlags)
    0,                  // Reserved (was MemoryAllocationFlags)

    // _KS_VIDEO_STREAM_CONFIG_CAPS  
    {
        STATICGUIDOF(KSDATAFORMAT_SPECIFIER_VIDEOINFO), // GUID
        KS_AnalogVideo_None,                            // AnalogVideoStandard
        DMAX_X, DMAX_Y, // InputSize, (the inherent size of the incoming signal
                        //             with every digitized pixel unique)
        D_X,D_Y,        // MinCroppingSize, smallest rcSrc cropping rect allowed
        DMAX_X, DMAX_Y, // MaxCroppingSize, largest  rcSrc cropping rect allowed
        8,              // CropGranularityX, granularity of cropping size
        1,              // CropGranularityY
        8,              // CropAlignX, alignment of cropping rect 
        1,              // CropAlignY;
        D_X, D_Y,       // MinOutputSize, smallest bitmap stream can produce
        DMAX_X, DMAX_Y, // MaxOutputSize, largest  bitmap stream can produce
        8,              // OutputGranularityX, granularity of output bitmap size
        1,              // OutputGranularityY;
        0,              // StretchTapsX  (0 no stretch, 1 pix dup, 2 interp...)
        0,              // StretchTapsY
        0,              // ShrinkTapsX 
        0,              // ShrinkTapsY 
        333667,         // MinFrameInterval, 100 nS units
        640000000,      // MaxFrameInterval, 100 nS units
        8 * 2 * 30 * D_X * D_Y,  // MinBitsPerSecond;
        8 * 2 * 30 * DMAX_X * DMAX_Y,   // MaxBitsPerSecond;
    },

    // KS_VIDEOINFOHEADER (default format)
    {
        0, 0, 0, 0,                         // RECT  rcSource; 
        0, 0, 0, 0,                         // RECT  rcTarget; 
        DMAX_X * DMAX_Y * 2 * 8 * 30,       // DWORD dwBitRate;
        0L,                                 // DWORD dwBitErrorRate; 
        333667,                             // REFERENCE_TIME  AvgTimePerFrame;   
        sizeof(KS_BITMAPINFOHEADER),       // DWORD biSize;
        DMAX_X,                             // LONG  biWidth;
        DMAX_Y,                             // LONG  biHeight;
        1,                                  // WORD  biPlanes;
        16,                                 // WORD  biBitCount;
        FOURCC_YUY2,                        // DWORD biCompression;
        DMAX_X * DMAX_Y * 2,                // DWORD biSizeImage;
        0,                                  // LONG  biXPelsPerMeter;
        0,                                  // LONG  biYPelsPerMeter;
        0,                                  // DWORD biClrUsed;
        0                                   // DWORD biClrImportant;
    }
};

const PKSDATARANGE CapturePinDataRanges[PIN_DATA_RANGE_COUNT] = {
    (PKSDATARANGE)&FormatYUY2_Capture
};

GUID g_PINNAME_VIDEO_CAPTURE = { STATIC_PINNAME_VIDEO_CAPTURE };

DECLARE_SIMPLE_FRAMING_EX(
    CapturePinAllocatorFraming,
    STATICGUIDOF(KSMEMORY_TYPE_KERNEL_NONPAGED),
    KSALLOCATOR_REQUIREMENTF_SYSTEM_MEMORY |
        KSALLOCATOR_REQUIREMENTF_PREFERENCES_ONLY,
    2,
    0,
    2 * PAGE_SIZE,
    2 * PAGE_SIZE
);

const KSPIN_DESCRIPTOR_EX TW68PinDescriptors[PIN_COUNT] = {
    {
        &TW68PinDispatch,
        NULL,
        {
            0,                              // Interfaces (NULL, 0 == default)
            NULL,
            0,                              // Mediums (NULL, 0 == default)
            NULL,
            SIZEOF_ARRAY(CapturePinDataRanges),// Range Count
            CapturePinDataRanges,           // Ranges
            KSPIN_DATAFLOW_OUT,             // Dataflow
            KSPIN_COMMUNICATION_BOTH,       // Communication
            &PIN_CATEGORY_CAPTURE,          // Category
            &g_PINNAME_VIDEO_CAPTURE,       // Name
            0                               // Reserved
        },
        KSPIN_FLAG_PROCESS_IN_RUN_STATE_ONLY,// Pin Flags
        1,                                  // Instances Possible
        1,                                  // Instances Necessary
        &CapturePinAllocatorFraming,        // Allocator Framing
        TW68IntersectHandler
    }
};
