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

#include <dev/char.h>
#include <kernel/aio.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/task.h>

#include <hybrid/minmax.h>

#include <kos/except-io.h>
#include <kos/io/usb.h>

#include <assert.h>
#include <format-printer.h>
#include <stddef.h>
#include <string.h>
#include <unicode.h>

DECL_BEGIN

/* Destroy the given USB endpoint descriptor */
PUBLIC NOBLOCK void
NOTHROW(KCALL usb_endpoint_destroy)(struct usb_endpoint *__restrict self) {
	kfree(self->ue_str_vendor);
	kfree(self->ue_str_product);
	kfree(self->ue_str_serial);
	kfree(self);
}


/* Same as `usb_controller_transfer()', but wait for the transfer to
 * complete (essentially just a wrapper using `struct aio_handle_generic')
 * @return: * : The total number of transferred bytes. */
PUBLIC NONNULL((1, 2, 3)) size_t KCALL
usb_controller_transfer_sync(struct usb_controller *__restrict self,
                             struct usb_endpoint *__restrict endp,
                             struct usb_transfer const *__restrict tx) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	usb_controller_transfer(self, endp, tx, &aio);
	TRY {
		aio_handle_generic_waitfor(&aio);
		aio_handle_generic_checkerror(&aio);
	} EXCEPT {
		aio_handle_generic_fini(&aio);
		RETHROW();
	}
	assert(aio.ah_type->ht_retsize != NULL);
	result = (*aio.ah_type->ht_retsize)(&aio);
	aio_handle_generic_fini(&aio);
	return result;
}


/* Perform a USB control request.
 * This causes a sequence of at least 3 packets to be sent
 * out to the specified endpoint, starting with a token
 * command packet containing the given `request', followed
 * by as many in/out data packets for interfacing with `buf',
 * and finally followed by a handshake packet
 * @param: buf: A buffer of `request->ur_length' bytes used for
 *              request input/output data.
 *              The flag `request->ur_reqtype & USB_REQUEST_RETYPE_DIR_D2H'
 *              determines the direction in which data is send to/from
 *              the device. */
PUBLIC NONNULL((1, 2, 3, 5)) void KCALL
usb_controller_request(struct usb_controller *__restrict self,
                       struct usb_endpoint *__restrict endp,
                       struct usb_request const *__restrict request,
                       void *buf, /*out*/ struct aio_handle *__restrict aio) {
	struct usb_transfer token, data, status;
	/* The initial token packet. */
	token.ut_type   = USB_TRANSFER_TYPE_SETUP;
	token.ut_flags  = USB_TRANSFER_FLAG_NORMAL;
	token.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	token.ut_buf    = (void *)request;
	token.ut_buflen = sizeof(*request);
	token.ut_next   = &data;

	data.ut_type = request->ur_reqtype & USB_REQUEST_RETYPE_DIR_D2H
	               ? USB_TRANSFER_TYPE_IN
	               : USB_TRANSFER_TYPE_OUT;

	if (request->ur_length == 0) {
		/* Skip the data stage */
		token.ut_next = &status;
	} else {
		/* The data payload packet.
		 * Note that we allow short packets for this part! */
		data.ut_flags  = USB_TRANSFER_FLAG_SHORT;
		data.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
		data.ut_buf    = buf;
		data.ut_buflen = request->ur_length;
		data.ut_next   = &status;
	}

	/* The terminating status packet. */
	status.ut_type   = data.ut_type | USB_TRANSFER_TYPE_FLAG_STATUS;
	status.ut_flags  = USB_TRANSFER_FLAG_NORMAL;
	status.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	status.ut_buflen = 0;
	status.ut_next   = NULL;

	usb_controller_transfer(self, endp, &token, aio);
}

/* Same as `usb_controller_request()', but wait for the operation to complete.
 * Additionally, return the number of bytes written to, or read from `buf' */
PUBLIC NONNULL((1, 2, 3)) size_t KCALL
usb_controller_request_sync(struct usb_controller *__restrict self,
                            struct usb_endpoint *__restrict endp,
                            struct usb_request const *__restrict request,
                            void *buf) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	usb_controller_request(self, endp, request, buf, &aio);
	TRY {
		aio_handle_generic_waitfor(&aio);
		aio_handle_generic_checkerror(&aio);
	} EXCEPT {
		aio_handle_generic_fini(&aio);
		RETHROW();
	}
	assert(aio.ah_type->ht_retsize != NULL);
	result = (*aio.ah_type->ht_retsize)(&aio);
	aio_handle_generic_fini(&aio);
	/* The return value must be larger than the request made, since
	 * the request didn't have the SHORT flag set, and therefor had
	 * to have been transferred in full. */
	assert(result >= sizeof(struct usb_request));
	result -= sizeof(struct usb_request);
	return result;
}

LOCAL NOBLOCK bool
NOTHROW(KCALL usb_controller_addused)(struct usb_controller *__restrict self,
                                      u16 addr) {
	struct usb_device *dev;
	for (dev = self->uc_devs; dev; dev = dev->ud_next) {
		if (dev->ud_dev == addr)
			return true;
	}
	return false;
}

PRIVATE void KCALL
usb_controller_assign_device_address(struct usb_controller *__restrict self,
                                     struct usb_device *__restrict dev) {
	u16 addr;
	sync_write(&self->uc_devslock);
	/* Find an unused (and non-zero) address. */
	for (addr = 1; usb_controller_addused(self, addr); ++addr)
		;
	/* Make sure that the device can understand the address. */
	if unlikely(addr > 127) {
		sync_endwrite(&self->uc_devslock);
		THROW(E_IOERROR_NODATA,
		      E_IOERROR_SUBSYSTEM_USB,
		      E_IOERROR_REASON_USB_TOOMANY);
	}
	/* Remember the address, and link up the device in our chain. */
	dev->ud_dev   = addr;
	dev->ud_next  = self->uc_devs;
	self->uc_devs = (REF struct usb_device *)incref(dev);
	sync_endwrite(&self->uc_devslock);
}


/* Print the device string associated with `index' to the given `printer'.
 * If `index' is invalid, or the given `endp' didn't return a string, then
 * return 0 without doing anything. */
PUBLIC ssize_t KCALL
usb_controller_printstring(struct usb_controller *__restrict self,
                           struct usb_endpoint *__restrict endp, u8 index,
                           pformatprinter printer, void *arg) {
	byte_t buf[256];
	struct usb_request req;
	size_t transfer_size;
	char16_t *str_utf16;
	size_t str_utf16_len;
	struct format_16to8_data format_data;
	ssize_t result;
	if (!index)
		return 0; /* Index 0 indicates a string that isn't defined. */
	if (!endp->ue_lang_used)
		return 0; /* No language string support. */
	req.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
	                 USB_REQUEST_RETYPE_TYPE_STD |
	                 USB_REQUEST_RETYPE_DIR_D2H;
	req.ur_request = USB_REQUEST_GET_DESCRIPTOR;
	req.ur_value   = USB_REQUEST_GET_DESCRIPTOR_VALUE_STRING | index;
	req.ur_index   = endp->ue_lang_used;
	req.ur_length  = 1;
	transfer_size = usb_controller_request_sync(self, endp, &req, buf);
	if (!transfer_size || buf[0] < 4)
		return 0; /* Empty string (just ignore it...) */
	/* Transfer the entire string. */
	req.ur_length = buf[0];
	transfer_size = usb_controller_request_sync(self, endp, &req, buf);
	if ((size_t)buf[0] > transfer_size)
		buf[0] = (u8)transfer_size;
	if (buf[0] < 4)
		return 0; /* Empty string (just ignore it...) */
	if (buf[1] != ((USB_REQUEST_GET_DESCRIPTOR_VALUE_STRING & 0xff00) >> 8))
		return 0; /* Not a string??? */
	/* USB devices produce utf-16 strings (thanks mIcRoSoFt... ~ugh~)
	 * -> Just convert the strings to utf-8 right here */
	str_utf16     = (char16_t *)(buf + 2);
	str_utf16_len = (buf[0] - 2) / 2;
	format_data.fd_printer   = printer;
	format_data.fd_arg       = arg;
	format_data.fd_surrogate = 0;
	result = format_16to8(&format_data, str_utf16, str_utf16_len);
	return result;
}

struct heap_printer_data {
	char  *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	size_t ap_avail; /* Unused buffer size */
	size_t ap_used;  /* Used buffer size */
};

PRIVATE WUNUSED NONNULL((1, 2)) ssize_t KCALL
heap_printer(/*struct heap_printer_data **/void *arg,
             /*utf-8*/char const *__restrict data,
             size_t datalen) {
	struct heap_printer_data *buf;
	buf = (struct heap_printer_data *)arg;
	if (buf->ap_avail < datalen) {
		char *newbuf;
		size_t min_alloc = buf->ap_used + datalen;
		size_t new_alloc = buf->ap_used + buf->ap_avail;
		if (!new_alloc)
			new_alloc = 8;
		while (new_alloc < min_alloc)
			new_alloc *= 2;
		newbuf = (char *)krealloc_nx(buf->ap_base, (new_alloc + 1) * sizeof(char), GFP_NORMAL);
		if unlikely(!newbuf) {
			new_alloc = min_alloc;
			newbuf    = (char *)krealloc(buf->ap_base, (new_alloc + 1) * sizeof(char), GFP_NORMAL);
		}
		assert(new_alloc >= buf->ap_used + datalen);
		buf->ap_base  = newbuf;
		buf->ap_avail = new_alloc - buf->ap_used;
	}
	memcpy(buf->ap_base + buf->ap_used, data, datalen * sizeof(char));
	buf->ap_avail -= datalen;
	buf->ap_used  += datalen;
	return (ssize_t)datalen;
}


/* Helper wrapper for `usb_controller_printstring()'
 * This function returns a heap-allocated string, or NULL under the same
 * circumstances where `usb_controller_printstring()' would return `0' */
PUBLIC WUNUSED ATTR_MALLOC NONNULL((1, 2)) /*utf-8*/ char *KCALL
usb_controller_allocstring(struct usb_controller *__restrict self,
                           struct usb_endpoint *__restrict endp, u8 index) {
	char *result;
	struct heap_printer_data data = { NULL, 0, 0 };
	TRY {
		usb_controller_printstring(self, endp, index,
		                           &heap_printer, &data);
	} EXCEPT {
		kfree(data.ap_base);
		RETHROW();
	}

	if (data.ap_avail != 0) {
		char *newbuf;
		newbuf = (char *)krealloc_nx(data.ap_base,
		                             (data.ap_used + 1) * sizeof(char),
		                             GFP_NORMAL);
		if likely(newbuf)
			data.ap_base = newbuf;
	} else {
		if unlikely(!data.ap_used) {
			/* Special case: Nothing was printed. */
			assert(!data.ap_base);
			return NULL;
		}
	}
	result = data.ap_base;
	assert(result);
	result[data.ap_used] = '\0'; /* NUL-terminate */
	return result;
}


/* Function called when a new USB endpoint is discovered.
 * This function should try to engage with the endpoint in
 * order to discover what type of device is connected.
 * Note that the given `endp->ue_endp' is always `0' (configure
 * pipe), and that `endp->ue_dev' is also ZERO(0) (aka.: not
 * configured), with this function then being expected to
 * initialize those values before trying to detect the type
 * of connected device, as well as passing the endpoint to
 * the appropriate driver.
 * NOTE: This function is also responsible for assigning an
 *       address to the device, meaning that the caller should
 *       not yet insert `dev' into `self->uc_devs'. Doing this
 *       is part of this function's job. */
PUBLIC void KCALL
usb_device_discovered(struct usb_controller *__restrict self,
                      struct usb_device *__restrict dev) {
	struct usb_request req;
	struct usb_descriptor desc;
	size_t transfer_size;
	alignas(2) byte_t buf[256];

	req.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
	                 USB_REQUEST_RETYPE_TYPE_STD |
	                 USB_REQUEST_RETYPE_DIR_D2H;
	req.ur_request = USB_REQUEST_GET_DESCRIPTOR;
	req.ur_value   = USB_REQUEST_GET_DESCRIPTOR_VALUE_DEVICE;
	req.ur_index   = 0;
	/* NOTE: offsetafter(struct usb_descriptor, ud_maxpacketsize) == 8,
	 *       which is the minimum packet size supported by all devices */
	req.ur_length = offsetafter(struct usb_descriptor, ud_maxpacketsize);
	transfer_size = usb_controller_request_sync(self, dev, &req, &desc);

	/* Remember the max packet size supported by the device. */
	if likely(transfer_size >= offsetafter(struct usb_descriptor, ud_maxpacketsize))
		dev->ue_maxpck = desc.ud_maxpacketsize;

	/* Assign an address to the device. */
	usb_controller_assign_device_address(self, dev);

	/* Tell the device about the address we've assigned it. */
	req.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
	                 USB_REQUEST_RETYPE_TYPE_STD |
	                 USB_REQUEST_RETYPE_DIR_H2D;
	req.ur_request = USB_REQUEST_SET_ADDRESS;
	req.ur_value   = dev->ud_dev;
	req.ur_index   = dev->ud_dev;
	req.ur_length  = 0;
	usb_controller_request_sync(self, dev, &req, NULL);

	/* With the address assigned to the device, from now on make use of
	 * that address for the purposes of communications with the device */
	dev->ue_dev = dev->ud_dev;

	/* Allow the device to transition to the addressable state.
	 * The specs state that we should wait 2 milliseconds for this. */
	{
		qtime_t then = quantum_time();
		then.add_milliseconds(2);
		do {
			task_sleep(&then);
		} while (quantum_time() < then);
	}

	/* Check if we got less data than expected during the initial
	 * `USB_REQUEST_GET_DESCRIPTOR' call above. If so, then this
	 * is considered to be a ~strange~ device. */
	if unlikely(transfer_size < offsetafter(struct usb_descriptor, ud_maxpacketsize))
		goto strange_device;

	/* Load the remainder of the device's descriptor. */
	req.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
	                 USB_REQUEST_RETYPE_TYPE_STD |
	                 USB_REQUEST_RETYPE_DIR_D2H;
	req.ur_request = USB_REQUEST_GET_DESCRIPTOR;
	req.ur_value   = USB_REQUEST_GET_DESCRIPTOR_VALUE_DEVICE;
	req.ur_index   = 0;
	req.ur_length  = MIN(desc.ud_size, sizeof(desc));
	memset(&desc, 0, sizeof(desc));
	usb_controller_request_sync(self, dev, &req, &desc);

	/* Figure out the languages supported by the device. */
	req.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
	                 USB_REQUEST_RETYPE_TYPE_STD |
	                 USB_REQUEST_RETYPE_DIR_D2H;
	req.ur_request = USB_REQUEST_GET_DESCRIPTOR;
	req.ur_value   = USB_REQUEST_GET_DESCRIPTOR_VALUE_STRING;
	req.ur_index   = 0;
	req.ur_length  = 1;
	transfer_size = usb_controller_request_sync(self, dev, &req, buf);
	if (transfer_size != 0 && buf[0] >= 4) {
		req.ur_length = buf[0];
		/* Transfer language IDs */
		transfer_size = usb_controller_request_sync(self, dev, &req, buf);
		if ((size_t)buf[0] > transfer_size)
			buf[0] = (u8)transfer_size;
		if (buf[0] >= 4 && buf[1] == ((USB_REQUEST_GET_DESCRIPTOR_VALUE_STRING & 0xff00) >> 8)) {
			/* USB language codes can be found here:
			 * https://web.archive.org/web/20120417075804/http://www.usb.org/developers/docs/USB_LANGIDs.pdf
			 * ... And for some reason, the original page no longer exists... */
			size_t i, count = (buf[0] - 2) / 2;
			dev->ue_lang_used = *(u16 *)(buf + 2);
#define LANG_EN_US 0x0409
			/* Try to make use of English (if available) */
			if (count > 1 && dev->ue_lang_used != LANG_EN_US) {
				for (i = 1; i < count; ++i) {
					u16 l = ((u16 *)(buf + 2))[i];
					if (l == LANG_EN_US) {
						dev->ue_lang_used = LANG_EN_US;
						break;
					}
				}
			}
		}
		if (dev->ue_lang_used != 0) {
			/* Load device strings. */
			dev->ue_str_vendor  = usb_controller_allocstring(self, dev, desc.ud_str_vendor);
			dev->ue_str_product = usb_controller_allocstring(self, dev, desc.ud_str_product);
			dev->ue_str_serial  = usb_controller_allocstring(self, dev, desc.ud_str_serial);
		}
	}

	/* TODO: Gather available device configurations */
	/* TODO: Create descriptors for each of the device's endpoints */
	/* TODO: Notify loaded usb drivers about the newly discovered endpoint,
	 *       allowing them to look at it and figure out if they can expose
	 *       the endpoints functionality to us. */

	printk(KERN_DEBUG "ud_size          = %#I8x\n", desc.ud_size);
	printk(KERN_DEBUG "ud_type          = %#I8x\n", desc.ud_type);
	printk(KERN_DEBUG "ud_usbver        = %#I16x\n", desc.ud_usbver);
	printk(KERN_DEBUG "ud_dev_class     = %#I8x\n", desc.ud_dev_class);
	printk(KERN_DEBUG "ud_dev_subclass  = %#I8x\n", desc.ud_dev_subclass);
	printk(KERN_DEBUG "ud_dev_protocol  = %#I8x\n", desc.ud_dev_protocol);
	printk(KERN_DEBUG "ud_maxpacketsize = %#I8x\n", desc.ud_maxpacketsize);
	printk(KERN_DEBUG "ud_vendid        = %#I16x\n", desc.ud_vendid);
	printk(KERN_DEBUG "ud_prodid        = %#I16x\n", desc.ud_prodid);
	printk(KERN_DEBUG "ud_devicever     = %#I16x\n", desc.ud_devicever);
	printk(KERN_DEBUG "ud_str_vendor    = %#I8x\n", desc.ud_str_vendor);
	printk(KERN_DEBUG "ud_str_product   = %#I8x\n", desc.ud_str_product);
	printk(KERN_DEBUG "ud_str_serial    = %#I8x\n", desc.ud_str_serial);
	printk(KERN_DEBUG "ud_confcount     = %#I8x\n", desc.ud_confcount);
	printk(KERN_DEBUG "ue_str_vendor    = %q\n", dev->ue_str_vendor);
	printk(KERN_DEBUG "ue_str_product   = %q\n", dev->ue_str_product);
	printk(KERN_DEBUG "ue_str_serial    = %q\n", dev->ue_str_serial);

	return;
strange_device:
	/* TODO: Register the device as a generic character device. */
	;
}


DECL_END

#endif /* ! */
