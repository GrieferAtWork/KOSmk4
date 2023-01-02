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
#ifndef GUARD_MODUSB_STORAGE_USB_STORAGE_C
#define GUARD_MODUSB_STORAGE_USB_STORAGE_C 1

#include <kernel/compiler.h>

#include <drivers/usb.h>
#include <kernel/driver.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <hw/usb/class.h>
#include <hw/usb/usb.h>

#include <stddef.h>

#include "scsi.h"

DECL_BEGIN


PRIVATE bool KCALL
usb_storage_probe(struct usb_controller *__restrict self,
                  struct usb_interface *__restrict intf,
                  size_t endpc, struct usb_endpoint *const endpv[]) {
	if (intf->ui_intf_desc->ui_intf_class != USB_CLASS_MASS_STORAGE)
		return false; /* Not a mass storage device. */
	if (intf->ui_intf_desc->ui_intf_subclass == USB_SUBCLASS_MASS_STORAGE_SCSI) {
		size_t i;
		struct usb_endpoint *in, *out;
		/* There should be at  least 2 endpoints, both  using
		 * `USB_ENDPOINT_ATTRIB_TRANSFERTYPE_BULK', with  one
		 * being used for input, and the other being used for
		 * output. */
		if unlikely(endpc < 2) {
			printk(KERN_ERR "[usb-storage] SCSI interface with too few endpoint\n");
			return false;
		}
		in = out = NULL;
		for (i = 0; i < endpc; ++i) {
			struct usb_endpoint *endp;
			endp = endpv[i];
			if ((endp->ue_endp_desc->ue_attrib & USB_ENDPOINT_ATTRIB_TRANSFERTYPEM) !=
			    USB_ENDPOINT_ATTRIB_TRANSFERTYPE_BULK)
				continue;
			if (endp->ue_flags & USB_ENDPOINT_FLAG_INPUT) {
				if (!in) {
					in = endp;
				} else {
					printk(KERN_WARNING "[usb-storage] SCSI interface with multiple in-endpoints\n");
				}
			} else {
				if (!out) {
					out = endp;
				} else {
					printk(KERN_WARNING "[usb-storage] SCSI interface with multiple out-endpoints\n");
				}
			}
		}
		if unlikely(!in || !out) {
			printk(KERN_ERR "[usb-storage] SCSI interface missing its %s%s-endpoint%s\n",
			       !in ? "in" : "out",
			       !in && !out ? "- and out" : "",
			       !in && !out ? "s" : "");
			return false;
		}
		/* OK! We've got the in- and out-endpoints all figured out. */
		return usb_scsi_create(self, in, out);
	}
	/* XXX: Other sub-classes? */
	return false;
}



PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL usb_storage_init(void) {
	usb_register_interface_probe(&usb_storage_probe);
}

PRIVATE DRIVER_FINI void KCALL usb_storage_fini(void) {
	usb_unregister_interface_probe(&usb_storage_probe);
}


DECL_END

#endif /* !GUARD_MODUSB_STORAGE_USB_STORAGE_C */
