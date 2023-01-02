/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODUSB_INIT_C
#define GUARD_MODUSB_INIT_C 1
#define BUILDING_MODUSB
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <drivers/usb.h>
#include <kernel/driver.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <libpciaccess/pciaccess.h>

DECL_BEGIN

PRIVATE ATTR_FREETEXT void KCALL
USBProbe_LogFound(char const *__restrict name,
                  struct pci_device *__restrict dev) {
	printk(FREESTR(KERN_INFO "[usb] Found %s controller at pci:%I32p\n"),
	       name, dev->pd_addr);
}

PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL USB_Init(void) {
	struct pci_device *d;
	printk(FREESTR(KERN_INFO "[usb] Initialize usb\n"));

	/* Enumerate PCI USB controllers. */
	PCI_FOREACH_DEVICE_CLASS (d, 0x0c, 0x03) {
		switch (d->pd_progif_id) {

		case 0x00:
			USBProbe_LogFound(FREESTR("uhci"), d);
			usb_probe_uhci(d);
			break;

		case 0x10:
			USBProbe_LogFound(FREESTR("ohci"), d);
			usb_probe_ohci(d);
			break;

#if 0
		case 0x20:
			USBProbe_LogFound(FREESTR("ehci"), d);
			usb_probe_ehci(d);
			break;

		case 0x30:
			USBProbe_LogFound(FREESTR("xhci"), d);
			usb_probe_xhci(d);
			break;
#endif

		default:
			printk(FREESTR(KERN_TRACE "[usb] Unrecognized USB progif: %#.2I8x\n"),
			       d->pd_progif_id);
			break;
		}
	}
}


DECL_END

#endif /* !GUARD_MODUSB_INIT_C */
