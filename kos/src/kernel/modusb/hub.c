/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODUSB_HUB_C
#define GUARD_MODUSB_HUB_C 1
#define CONFIG_BUILDING_MODUSB 1
#define _KOS_SOURCE 1

#include "hub.h"

#include <kernel/compiler.h>

#include <dev/char.h>
#include <drivers/usb.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <sched/cpu.h>

#include <hw/usb/class.h>
#include <hw/usb/hub.h>
#include <hw/usb/usb.h>

#include <stddef.h>
#include <stdio.h>

DECL_BEGIN

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL usb_hub_fini)(struct character_device *__restrict self) {
	struct usb_hub_device *me;
	me = (struct usb_hub_device *)self;
	decref(me->uh_intf);
	decref(me->uh_ctrl);
}


PRIVATE void
NOTHROW(FCALL sleep_milli)(unsigned int n) {
	struct timespec then = realtime();
	then.add_milliseconds(n);
	do {
		task_sleep_tms(&then);
	} while (realtime() < then);
}


PRIVATE void KCALL
usb_hub_reset_port_and_probe(struct usb_hub_device *__restrict self,
                             u8 portno) {
	struct usb_request req;
	struct usb_controller *ctrl;
	u16 st;
	unsigned int n;
	printk(FREESTR(KERN_INFO "[usb][addr:%#I8x] Checking for device attached to hub port #%I8u\n"),
	       self->uh_intf->ue_dev, portno);
	ctrl = self->uh_ctrl;
	sync_write(&ctrl->uc_disclock);
	TRY {
		/* Reset the port. */
		req.ur_reqtype = USB_REQUEST_RETYPE_DEST_OTH |
		                 USB_REQUEST_RETYPE_TYPE_CLS |
		                 USB_REQUEST_RETYPE_DIR_H2D;
		req.ur_request = USB_REQUEST_SET_FEATURE;
		req.ur_value   = 4; /* Port reset */
		req.ur_index   = portno + 1;
		req.ur_length  = 0;
		usb_controller_request_sync(ctrl, self->uh_intf,
		                            &req, NULL);

		req.ur_reqtype = USB_REQUEST_RETYPE_DEST_OTH |
		                 USB_REQUEST_RETYPE_TYPE_CLS |
		                 USB_REQUEST_RETYPE_DIR_D2H;
		req.ur_request = USB_REQUEST_GET_STATUS;
		req.ur_value   = 0;
		req.ur_length  = sizeof(st);
		/* Wait for the port to become enabled. */
		for (n = 0; n < 10; ++n) {
			sleep_milli(10);
			st = 0;
			usb_controller_request_sync(ctrl, self->uh_intf, &req, &st);

			/* Check for a connection on this port. */
			if (!(st & 1))
				break;

			/* Check if the port is enabled. */
			if (st & 2)
				goto do_probe_port;
		}
	} EXCEPT {
		sync_endwrite(&ctrl->uc_disclock);
		RETHROW();
	}
	sync_endwrite(&ctrl->uc_disclock);
	return;
do_probe_port:
	{
		uintptr_t flags;
		printk(FREESTR(KERN_INFO "[usb][addr:%#I8x] Device found attached to hub on port #%I8u\n"),
		       self->uh_intf->ue_dev, portno);
		flags = (st & 0x600) == 0
		        ? USB_ENDPOINT_FLAG_FULLSPEED
		        : (st & 0x600) == 0x200
		          ? USB_ENDPOINT_FLAG_LOWSPEED
		          : USB_ENDPOINT_FLAG_HIGHSPEED;
		/* NOTE: A call to `usb_device_discovered()' always releases the `uc_disclock' lock! */
		usb_device_discovered(ctrl, flags);
	}
}



INTERN bool KCALL
usb_hub_probe(struct usb_controller *__restrict self,
              struct usb_interface *__restrict intf,
              size_t endpc, struct usb_endpoint *const endpv[]) {
	REF struct usb_hub_device *result;
	struct usb_request req;
	struct usb_hub_descriptor desc;
	size_t transfer_size;
	if (intf->ui_intf_desc->ui_intf_class != USB_CLASS_HUB)
		return false;
	printk(KERN_NOTICE "[usb] HUB detected\n");

	req.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
	                 USB_REQUEST_RETYPE_TYPE_CLS |
	                 USB_REQUEST_RETYPE_DIR_D2H;
	req.ur_request = USB_REQUEST_GET_DESCRIPTOR;
	req.ur_value   = USB_REQUEST_GET_DESCRIPTOR_VALUE_HUB;
	req.ur_index   = 0;
	req.ur_length = sizeof(desc);
	transfer_size = usb_controller_request_sync(self, intf, &req, &desc);
	if ((size_t)desc.uh_size > transfer_size)
		desc.uh_size = (u8)transfer_size;
	if (desc.uh_size < offsetafter(struct usb_hub_descriptor, uh_powerondelay)) {
		printk(KERN_ERR "[usb] Descriptor returned by hub is too small\n");
		return false;
	}
	if (desc.uh_type != ((USB_REQUEST_GET_DESCRIPTOR_VALUE_HUB & 0xff00) >> 8)) {
		printk(KERN_ERR "[usb] Descriptor returned by hub has an invalid type %#.2I8x\n",
		       desc.uh_type);
		return false;
	}
	if unlikely(desc.uh_num_ports == 0) {
		printk(KERN_ERR "[usb] HUB doesn't have any ports\n");
		return false;
	}
	/* XXX: Validate the proper amount/kinds of end-points? */
	(void)endpc;
	(void)endpv;

	result = CHARACTER_DEVICE_ALLOC(struct usb_hub_device);
	result->uh_ctrl         = (REF struct usb_controller *)incref(self);
	result->uh_intf         = (REF struct usb_interface *)incref(intf);
	result->uh_num_ports    = desc.uh_num_ports;
	result->uh_powerondelay = desc.uh_powerondelay;
	result->uh_attrib       = desc.uh_attrib;
	result->cd_type.ct_fini = &usb_hub_fini;
	/* TODO: Implement ioctl() */
	FINALLY_DECREF_UNLIKELY(result);

	/* Create a device file for the hub. */
	{
		static int n = 0; /* TODO: better naming */
		sprintf(result->cd_name, "usbhub%c", 'a' + n++);
	}
	character_device_register_auto(result);
	TRY {
		usb_register_character_device(intf->ui_device,
		                              result);
	} EXCEPT {
		character_device_unregister(result);
		RETHROW();
	}

	{
		u8 i;
		/* Enable power to all ports. */
		if ((result->uh_attrib & USB_HUB_ATTRIB_PSMM) == USB_HUB_ATTRIB_PSM_INDIV) {
			for (i = 0; i < result->uh_num_ports; ++i) {
				req.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
				                 USB_REQUEST_RETYPE_TYPE_CLS |
				                 USB_REQUEST_RETYPE_DIR_H2D;
				req.ur_request = USB_REQUEST_SET_FEATURE;
				req.ur_value   = 8; /* Port power */
				req.ur_index   = i + 1;
				req.ur_length  = 0;
				usb_controller_request_sync(self, intf, &req, NULL);
			}
			sleep_milli(2 * result->uh_powerondelay);
		}
		/* Reset and probe all of the hub's ports. */
		for (i = 0; i < result->uh_num_ports; ++i)
			usb_hub_reset_port_and_probe(result, i);
	}
	return true;
}

DECL_END

#endif /* !GUARD_MODUSB_HUB_C */
