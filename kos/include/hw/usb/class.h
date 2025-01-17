/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _HW_USB_CLASS_H
#define _HW_USB_CLASS_H 1

#include <__stdinc.h>

__SYSDECL_BEGIN

/* https://web.archive.org/web/20130205095026/https://www.usb.org/developers/defined_class */
#define USB_CLASS_AUDIO               0x01 /* [TYPE(Interface)] Audio */
#define USB_CLASS_COM_CDC             0x02 /* [TYPE(Both)] Communications and CDC Control */
#define USB_CLASS_HID                 0x03 /* [TYPE(Interface)] HID (Human Interface Device) */
#define    USB_SUBCLASS_HID_BOOT              0x01 /* [TYPE(Interface)] Boot Interface Subclass */
#define    USB_PROTOCOL_HID_KEYBOARD          0x01 /* Keyboard */
#define    USB_PROTOCOL_HID_MOUSE             0x02 /* Mouse */
#define USB_CLASS_PHYSICAL            0x05 /* [TYPE(Interface)] Physical */
#define USB_CLASS_IMAGE               0x06 /* [TYPE(Interface)] Image */
#define USB_CLASS_PRINTER             0x07 /* [TYPE(Interface)] Printer */
#define USB_CLASS_MASS_STORAGE        0x08 /* [TYPE(Interface)] Mass Storage */
/* https://web.archive.org/web/20110516074333/http://www.usb.org/developers/devclass_docs/usb-msc-overview-1.3b.pdf */
#define    USB_SUBCLASS_MASS_STORAGE_RBC      0x01 /* Reduced Block Commands (RBC) T10 Project 1240-D */
#define    USB_SUBCLASS_MASS_STORAGE_ATAPI    0x02 /* MMC-5 (ATAPI) */
#define    USB_SUBCLASS_MASS_STORAGE_UFI      0x04 /* USB Floppy Interface (UFI) Specifies how to interface Floppy Disk Drives to USB. */
#define    USB_SUBCLASS_MASS_STORAGE_SCSI     0x06 /* SCSI transparent command set (BBB) */
#define    USB_SUBCLASS_MASS_STORAGE_LSDFS    0x07 /* Lockable Mass Storage. LSDFS specifies how host has to negotiate access before trying SCSI. */
#define    USB_SUBCLASS_MASS_STORAGE_IEEE1667 0x08 /* IEEE 1667 */
#define    USB_SUBCLASS_MASS_STORAGE_VENDOR   0xff /* Specific to device vendor */

#define USB_CLASS_HUB                 0x09 /* [TYPE(Device)] Hub */
#define USB_CLASS_CDC_DATA            0x0a /* [TYPE(Interface)] CDC-Data */
#define USB_CLASS_SMARTCARD           0x0b /* [TYPE(Interface)] Smart Card */
#define USB_CLASS_CONTENT_SECURITY    0x0d /* [TYPE(Interface)] Content Security */
#define USB_CLASS_VIDEO               0x0e /* [TYPE(Interface)] Video */
#define USB_CLASS_PERSONALHEALTHCARE  0x0f /* [TYPE(Interface)] Personal Healthcare */
#define USB_CLASS_AV_DEVICES          0x10 /* [TYPE(Interface)] Audio/Video Devices */
#define USB_CLASS_DIAGNOSTIC_DEVICE   0xdc /* [TYPE(Both)] Diagnostic Device */
#define USB_CLASS_WIRELESS_CONTROLLER 0xe0 /* [TYPE(Interface)] Wireless Controller */
#define USB_CLASS_MISC                0xef /* [TYPE(Both)] Miscellaneous */
#define USB_CLASS_APPLICATION_SPEC    0xfe /* [TYPE(Interface)] Application Specific */
#define USB_CLASS_VENDOR_SPEC         0xff /* [TYPE(Both)] Vendor Specific */

__SYSDECL_END

#endif /* !_HW_USB_CLASS_H */
