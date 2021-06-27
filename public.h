#pragma once

#include <wdm.h>

#include <windef.h>
#include <stdio.h>
#include <ntstrsafe.h>
#include <stdlib.h>
#include <windef.h>
#define NOBITMAP
#include <mmreg.h>
#undef NOBITMAP
#include <unknown.h>
#include <ks.h>
#include <ksmedia.h>

#include <initguid.h>
#include <uuids.h>

#pragma warning (disable : 4100 4127 4131 4189 4701 4706)

#include "trace.h"
#include "device.h"
#include "filter.h"
#include "pin.h"

DEFINE_GUID(GUID_DEVINTERFACE_tw68xx,
    0x8cacffba, 0xfc26, 0x45a0, 0xa6, 0x10, 0xf1, 0x92, 0x24, 0x85, 0x21, 0x90);
// {8cacffba-fc26-45a0-a610-f19224852190}

#ifndef mmioFOURCC    
#define mmioFOURCC( ch0, ch1, ch2, ch3 )                \
        ( (DWORD)(BYTE)(ch0) | ( (DWORD)(BYTE)(ch1) << 8 ) |    \
        ( (DWORD)(BYTE)(ch2) << 16 ) | ( (DWORD)(BYTE)(ch3) << 24 ) )
#endif

#define FOURCC_YUY2         mmioFOURCC('Y', 'U', 'Y', '2')
