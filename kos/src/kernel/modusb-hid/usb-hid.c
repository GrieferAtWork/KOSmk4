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
#ifndef GUARD_MODUSB_HID_USB_HID_C
#define GUARD_MODUSB_HID_USB_HID_C 1

#include <kernel/compiler.h>

#include <drivers/usb.h>
#include <kernel/driver.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <hw/hid/usb-hid.h>
#include <hw/usb/class.h>
#include <hw/usb/usb.h>

#include "usb-kbd.h"

DECL_BEGIN


PRIVATE bool KCALL
usb_hid_probe(struct usb_controller *__restrict self,
              struct usb_interface *__restrict intf,
              size_t endpc, struct usb_endpoint *const endpv[]) {
	if (intf->ui_intf_desc->ui_intf_class != USB_CLASS_HID)
		return false; /* Not an hid device. */
	if (intf->ui_intf_desc->ui_intf_subclass != USB_SUBCLASS_HID_BOOT)
		return false; /* Not an hid device. */
	if (intf->ui_intf_desc->ui_intf_protocol == USB_PROTOCOL_HID_KEYBOARD)
		return usb_keyboard_probe(self, intf, endpc, endpv); /* Keyboard. */
	if (intf->ui_intf_desc->ui_intf_protocol == USB_PROTOCOL_HID_MOUSE)
		return false; /* TODO */
	return false;
}



PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL usb_hid_init(void) {
	usb_register_interface_probe(&usb_hid_probe);
}

PRIVATE DRIVER_FINI void KCALL usb_hid_fini(void) {
	usb_unregister_interface_probe(&usb_hid_probe);
}


DECL_END

#endif /* !GUARD_MODUSB_HID_USB_HID_C */
