/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODUSB_HUB_H
#define GUARD_MODUSB_HUB_H 1

#include <kernel/compiler.h>

#include <drivers/usb.h>
#include <kernel/fs/chrdev.h>

DECL_BEGIN

struct usbhubdev
#ifdef __cplusplus
    : chrdev
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct chrdev              uh_dev;          /* The underlying character device. */
#endif /* !__cplusplus */
	REF struct usb_controller *uh_ctrl;         /* [1..1][const] The associated USB controller. */
	REF struct usb_interface  *uh_intf;         /* [1..1][const] The interface of the HUB */
	u8                         uh_num_ports;    /* [const][!0] # of ports provided by this hub. */
	u8                         uh_powerondelay; /* [const] Time (in 2 millisecond intervals) before power stabilizes on a port. */
	u16                        uh_attrib;       /* [const] Hub attributes (characteristics) (Set of `USB_HUB_ATTRIB_*') */
};

#define chrdev_asusbhub(self) ((struct usbhubdev *)(self))
#define device_asusbhub(self) chrdev_asusbhub(device_aschr(self))
#define fnode_asusbhub(self)  chrdev_asusbhub(fnode_aschrdev(self))
#define mfile_asusbhub(self)  chrdev_asusbhub(mfile_aschrdev(self))


#ifdef BUILDING_MODUSB
INTDEF bool KCALL
usbhubdev_probe(struct usb_controller *__restrict self,
                struct usb_interface *__restrict intf,
                size_t endpc, struct usb_endpoint *const endpv[]);
#endif /* BUILDING_MODUSB */

DECL_END

#endif /* !GUARD_MODUSB_HUB_H */
