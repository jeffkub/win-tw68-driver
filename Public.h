#pragma once

#include <wdm.h>

//#include <windef.h>
//#include <stdio.h>
#include <ntstrsafe.h>
#include <stdlib.h>
#include <windef.h>
#define NOBITMAP
#include <mmreg.h>
#undef NOBITMAP
#include <unknown.h>
#include <ks.h>
#include <ksmedia.h>

#pragma warning (disable : 4100 4127 4131 4189 4701 4706)

DEFINE_GUID (GUID_DEVINTERFACE_tw68xx,
    0x8cacffba,0xfc26,0x45a0,0xa6,0x10,0xf1,0x92,0x24,0x85,0x21,0x90);
// {8cacffba-fc26-45a0-a610-f19224852190}

#include "trace.h"
