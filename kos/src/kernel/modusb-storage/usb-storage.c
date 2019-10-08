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
#ifndef GUARD_MODUSB_STORAGE_USB_STORAGE_C
#define GUARD_MODUSB_STORAGE_USB_STORAGE_C 1

#include "usb-storage.h"

#include <kernel/compiler.h>

#include <drivers/usb.h>
#include <kernel/driver.h>
#include <kernel/printk.h>
#include <kernel/types.h>

DECL_BEGIN

PRIVATE bool KCALL
usb_storage_probe(struct usb_controller *__restrict self,
                  struct usb_interface *__restrict intf,
                  size_t endpc, struct usb_endpoint *const endpv[]) {
	printk(KERN_DEBUG "usb_storage_probe()\n");
	/* TODO */
	return false;
}



PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL usb_storage_init(void) {
	printk(KERN_DEBUG "usb_storage_init()\n");
	printk(KERN_DEBUG "usb_register_interface_probe   = %p\n", &usb_register_interface_probe);
	printk(KERN_DEBUG "usb_unregister_interface_probe = %p\n", &usb_unregister_interface_probe);
	usb_register_interface_probe(&usb_storage_probe);
}

PRIVATE DRIVER_FINI void KCALL usb_storage_fini(void) {
	usb_unregister_interface_probe(&usb_storage_probe);
}


DECL_END

#endif /* !GUARD_MODUSB_STORAGE_USB_STORAGE_C */
