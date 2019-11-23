/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODUSB_OHCI_C
#define GUARD_MODUSB_OHCI_C 1
#define CONFIG_BUILDING_MODUSB 1

#include <kernel/compiler.h>

#include <drivers/pci.h>
#include <drivers/usb.h>
#include <kernel/printk.h>
#include <kos/io/ohci.h>

#include "ohci.h"

DECL_BEGIN

INTERN ATTR_FREETEXT void KCALL
usb_probe_ohci(struct pci_device *__restrict dev) {
	printk(FREESTR(KERN_WARNING "[usb] Not implemented: ohci support\n"));
	(void)dev;
}

DECL_END

#endif /* !GUARD_MODUSB_OHCI_C */
