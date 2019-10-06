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
#ifndef GUARD_MODUSB_USB_C
#define GUARD_MODUSB_USB_C 1
#define CONFIG_BUILDING_MODUSB 1
#define _KOS_SOURCE 1

#include "usb.h"

#include <kernel/compiler.h>
#include <kernel/aio.h>
#include <kos/io/usb.h>

#include <dev/char.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <stddef.h>

DECL_BEGIN

/* Function called when a new USB endpoint is discovered.
 * This function should try to engage with the endpoint in
 * order to discover what type of device is connected. */
PUBLIC void KCALL
usb_endpoint_discovered(struct usb_controller *__restrict self,
                        struct usb_endpoint *__restrict endp) {
	struct aio_handle_generic aio;
	struct usb_transfer token, data, handshake;
	struct usb_request token_request;

	/* TODO */

	u16 data_payload = 0xcccc;
	token.ut_type   = USB_TRANSFER_TYPE_SETUP;
	token.ut_flags  = USB_TRANSFER_FLAG_NORMAL;
	token.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	token.ut_buf    = &token_request;
	token.ut_buflen = sizeof(token_request);
	token.ut_next   = &data;

	token_request.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
	                           USB_REQUEST_RETYPE_TYPE_STD |
	                           USB_REQUEST_RETYPE_DIR_D2H;
	token_request.ur_request = USB_REQUEST_GET_STATUS;
	token_request.ur_index   = 0;
	token_request.ur_length  = sizeof(data_payload);

	data.ut_type   = USB_TRANSFER_TYPE_IN;
	data.ut_flags  = USB_TRANSFER_FLAG_NORMAL;
	data.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	data.ut_buf    = &data_payload;
	data.ut_buflen = sizeof(data_payload);
	data.ut_next   = &handshake;

	handshake.ut_type   = USB_TRANSFER_TYPE_OUT;
	handshake.ut_flags  = USB_TRANSFER_FLAG_NORMAL;;
	handshake.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	handshake.ut_buflen = 0;
	handshake.ut_next   = NULL;

	aio_handle_generic_init(&aio);
	(*self->uc_transfer)(self, endp, &token, &aio);
	TRY {
		aio_handle_generic_waitfor(&aio);
		aio_handle_generic_checkerror(&aio);
	} EXCEPT {
		aio_handle_generic_fini(&aio);
		RETHROW();
	}
	aio_handle_generic_fini(&aio);
	printk(KERN_DEBUG "data_payload = %#I16x\n", data_payload);
}


DECL_END

#endif /* ! */
