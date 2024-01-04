/* Copyright (c) 2019-2024 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _HW_USB_HUB_H
#define _HW_USB_HUB_H 1

#include <__stdinc.h>

#include <bits/types.h>

__SYSDECL_BEGIN

/* For use with `USB_REQUEST_GET_DESCRIPTOR' */
#define USB_REQUEST_GET_DESCRIPTOR_VALUE_HUB 0x2900

/* Flags for `usb_hub_descriptor::uh_attrib' */
#define USB_HUB_ATTRIB_PSMM      0x0003 /* [bit(0:1)] PowerSwitchingMode */
#define USB_HUB_ATTRIB_PSMS           0 /* Shift for `USB_HUB_ATTRIB_PSMM' */
#define    USB_HUB_ATTRIB_PSM_GANGED    0x0000 /* All ports are powered at once */
#define    USB_HUB_ATTRIB_PSM_INDIV     0x0001 /* Ports can be powered individually */
#define USB_HUB_ATTRIB_COMPOUND  0x0004 /* [bit(2)] Hub is part of a compound device */
#define USB_HUB_ATTRIB_OCPROTM   0x0018 /* [bit(3:4)] OverCurrentProtection */
#define USB_HUB_ATTRIB_OCPROTS        3 /* Shift for `USB_HUB_ATTRIB_OCPROTM' */
#define    USB_HUB_ATTRIB_OCPROT_GLOBAL 0x0000 /* Current draw reports are the summation of all ports. */
#define    USB_HUB_ATTRIB_OCPROT_INDIV  0x0008 /* Current draw reports for each port. */
#define    USB_HUB_ATTRIB_OCPROT_NONE   0x0010 /* No protection. */
#define    USB_HUB_ATTRIB_OCPROT_NONE2  0x0018 /* Same as `USB_HUB_ATTRIB_OCPROT_NONE'. */
#define USB_HUB_ATTRIB_TTM       0x0060 /* [bit(5:6)] Think Time */
#define USB_HUB_ATTRIB_TTS            5 /* Shift for `USB_HUB_ATTRIB_TTM' */
#define    USB_HUB_ATTRIB_TT_8          0x0000 /* ... */
#define    USB_HUB_ATTRIB_TT_16         0x0020 /* ... */
#define    USB_HUB_ATTRIB_TT_24         0x0040 /* ... */
#define    USB_HUB_ATTRIB_TT_32         0x0060 /* ... */
#define USB_HUB_ATTRIB_PORTINDIC 0x0080 /* Port indicators are supported */

#ifdef __CC__
struct __ATTR_PACKED usb_hub_descriptor {
	__uint8_t  uh_size;            /* Size of the descriptor (in bytes) */
	__uint8_t  uh_type;            /* Descriptor type (== `(USB_REQUEST_GET_DESCRIPTOR_VALUE_HUB & 0xff00) >> 8') */
	__uint8_t  uh_num_ports;       /* # of ports provided by this hub. */
	__uint16_t uh_attrib;          /* Hub attributes (characteristics) (Set of `USB_HUB_ATTRIB_*') */
	__uint8_t  uh_powerondelay;    /* Time (in 2 millisecond intervals) before power stabilizes on a port. */
	__uint8_t  uh_current;         /* Max current requirements (in mA) */
	/* Bitset of devices that are removable here... */
};

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_HW_USB_HUB_H */
