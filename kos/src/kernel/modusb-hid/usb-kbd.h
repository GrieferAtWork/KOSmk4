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
#ifndef GUARD_MODUSB_HID_USB_KBD_H
#define GUARD_MODUSB_HID_USB_KBD_H 1

#include <kernel/compiler.h>

#include <dev/keyboard.h>
#include <drivers/usb.h>
#include <kernel/types.h>

DECL_BEGIN

struct usb_keyboard_device
#ifdef __cplusplus
	: kbddev
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct kbddev     uk_device;  /* The underlying keyboard. */
#endif /* !__cplusplus */
	REF struct usb_controller *uk_ctrl;    /* [1..1][const] The associated USB controller. */
	REF struct usb_interface  *uk_intf;    /* [1..1][const] The used USB interface. */
	REF struct usb_endpoint   *uk_data;    /* [1..1][const] The data endpoint of the keyboard. */
	REF struct usb_interrupt  *uk_intr;    /* [1..1][const] The keyboard interrupt handler. */
	u8                         uk_last[8]; /* [lock(PRIVATE(uk_intr))] Data from the previous interrupt. */
};

INTDEF bool KCALL
usb_keyboard_probe(struct usb_controller *__restrict self,
                   struct usb_interface *__restrict intf,
                   size_t endpc, struct usb_endpoint *const endpv[]);



DECL_END

#endif /* !GUARD_MODUSB_HID_USB_KBD_H */
