/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_tw68xx,
    0x8cacffba,0xfc26,0x45a0,0xa6,0x10,0xf1,0x92,0x24,0x85,0x21,0x90);
// {8cacffba-fc26-45a0-a610-f19224852190}
