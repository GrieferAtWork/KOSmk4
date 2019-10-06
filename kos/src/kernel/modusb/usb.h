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
#ifndef GUARD_MODUSB_USB_H
#define GUARD_MODUSB_USB_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <dev/char.h>

DECL_BEGIN

struct usb_device;
struct usb_descriptor;
struct usb_transaction;
struct usb_controller;

#define USB_SPEED_HIGH 0x00
#define USB_SPEED_FULL 0x01
#define USB_SPEED_LOW  0x02

struct usb_descriptor {
	/* USB Device Descriptor */
	u8 ud_speed; /* Speed of the device (one of `USB_SPEED_*') */
};


struct usb_device
#ifdef __cplusplus
	: character_device
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct character_device ud_dev;  /* The underlying character device. */
#endif /* !__cplusplus */
	struct usb_descriptor   ud_desc; /* Device descriptor. */
	/* TODO: Common interface */
};




struct usb_controller
#ifdef __cplusplus
	: character_device
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct character_device uc_dev; /* The underlying character device. */
#endif /* !__cplusplus */
	/* TODO: Common interface */

};






#ifdef CONFIG_BUILDING_MODUSB
struct pci_device;

/* Probe (and initialize if OK) for different types of USB controllers. */
INTDEF FREE void KCALL usb_probe_uhci(struct pci_device *__restrict dev);
INTDEF FREE void KCALL usb_probe_ohci(struct pci_device *__restrict dev);
#if 0
INTDEF FREE void KCALL usb_probe_ehci(struct pci_device *__restrict dev);
INTDEF FREE void KCALL usb_probe_xhci(struct pci_device *__restrict dev);
#endif
#endif /* CONFIG_BUILDING_MODUSB */

DECL_END

#endif /* !GUARD_MODUSB_USB_H */
