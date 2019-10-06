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

#include <kernel/malloc.h>
#include <kernel/types.h>
#include <dev/char.h>

DECL_BEGIN

struct usb_endpoint {
	WEAK refcnt_t ue_refcnt;       /* Reference counter. */
	u16           ue_maxpck;       /* [const] Max packet size. */
	u8            ue_dev;          /* [const] Device address. */
	u8            ue_endp;         /* [const] Endpoint index. */
	unsigned int  ue_toggle : 1;   /* Data toggle bit. */
	unsigned int  ue_lowspeed : 1; /* Low-speed device. */
};
DEFINE_REFCOUNT_FUNCTIONS(struct usb_endpoint, ue_refcnt, kfree)



struct usb_transfer {
	struct usb_transfer *ut_next;   /* [0..1] Next transfer packet. */
#define USB_TRANSFER_TYPE_IN    0   /* Receive data. */
#define USB_TRANSFER_TYPE_OUT   1   /* Send data. */
#define USB_TRANSFER_TYPE_SETUP 2   /* Send control data. */
#define USB_TRANSFER_TYPE_COUNT 3   /* # of transfer types */
	uintptr_quarter_t    ut_type;   /* Transfer type (One of `USB_TRANSFER_TYPE_*'). */
#define USB_TRANSFER_FLAG_NORMAL 0x00 /* Normal transfer flags. */
#define USB_TRANSFER_FLAG_SHORT  0x01 /* Allow short packets (used buffer size must not necessarily match given size). */
	uintptr_quarter_t    ut_flags;  /* Transfer flags (Set of `USB_TRANSFER_FLAG_*'). */
#define USB_TRANSFER_BUFTYP_VIRT    0 /* Virtual memory buffer */
#define USB_TRANSFER_BUFTYP_PHYS    1 /* Physical memory buffer */
#define USB_TRANSFER_BUFTYP_VIRTVEC 2 /* Virtual memory vector buffer */
#define USB_TRANSFER_BUFTYP_PHYSVEC 3 /* Physical memory vector buffer */
#define USB_TRANSFER_BUFTYP_COUNT   4 /* # of buffer types */
	uintptr_quarter_t    ut_buftyp; /* Buffer type (One of `USB_TRANSFER_BUFTYP_*'). */
	size_t               ut_buflen; /* Buffer length. */
	union { /* Used input/output buffer. */
		void                     *ut_buf;   /* [valid_if(ut_buftyp == USB_TRANSFER_BUFTYP_VIRT)] */
		vm_phys_t                 ut_bufp;  /* [valid_if(ut_buftyp == USB_TRANSFER_BUFTYP_PHYS)] */
		struct aio_buffer  const *ut_vbuf;  /* [valid_if(ut_buftyp == USB_TRANSFER_BUFTYP_VIRTVEC)] */
		struct aio_pbuffer const *ut_vbufp; /* [valid_if(ut_buftyp == USB_TRANSFER_BUFTYP_PHYSVEC)] */
	};
};


struct usb_controller
#ifdef __cplusplus
	: character_device
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct character_device uc_dev; /* The underlying character device. */
#endif /* !__cplusplus */
	/* [1..1] Perform a one-time transfer of a sequence of packets.
	 * This is the primary functions for OS-initiated communications
	 * with connected USB devices.
	 * For communications initiated by the device, see the interface
	 * for doing this below.
	 * @param: self: The controller which will be used for the transfer
	 * @param: endp: The targeted USB endpoint.
	 * @param: tx:   A chain of USB packets that must be transmitted to
	 *               the given `endp' in the same order in which they
	 *               are given here (the chain is described by `->ut_next->')
	 * @param: aio:  The AIO handle allowing the caller to perform the transfer
	 *               asynchronously.
	 *               Note that the caller is free to invalidate `tx', as well as
	 *               any of the pointed-to buffer controller structures (though
	 *               obviously not the buffers themself), as well as later transfer
	 *               descriptors even before the given `aio' handle is invoked to
	 *               indicate completion. */
	NONNULL((1, 2, 3, 4)) void
	(KCALL *uc_transfer)(struct usb_controller *__restrict self,
	                     struct usb_endpoint *__restrict endp,
	                     struct usb_transfer const *__restrict tx,
	                     struct aio_handle *__restrict aio);
	/* TODO: Interface for registering Isochronous interrupt handlers. */
};


/* Perform a one-time transfer of a sequence of packets.
 * This is the primary functions for OS-initiated communications
 * with connected USB devices.
 * For communications initiated by the device, see the interface
 * for doing this below.
 * @param: self: The controller which will be used for the transfer
 * @param: endp: The targeted USB endpoint.
 * @param: tx:   A chain of USB packets that must be transmitted to
 *               the given `endp' in the same order in which they
 *               are given here (the chain is described by `->ut_next->')
 * @param: aio:  The AIO handle allowing the caller to perform the transfer
 *               asynchronously.
 *               Note that the caller is free to invalidate `tx', as well as
 *               any of the pointed-to buffer controller structures (though
 *               obviously not the buffers themself), as well as later transfer
 *               descriptors even before the given `aio' handle is invoked to
 *               indicate completion. */
LOCAL NONNULL((1, 2, 3, 4)) void KCALL
usb_controller_transfer(struct usb_controller *__restrict self,
                        struct usb_endpoint *__restrict endp,
                        struct usb_transfer const *__restrict tx,
                        struct aio_handle *__restrict aio) {
	(*self->uc_transfer)(self, endp, tx, aio);
}

/* Same as `usb_controller_transfer()', but wait for the transfer to
 * complete (essentially just a wrapper using `struct aio_handle_generic')
 * @return: * : The total number of transferred bytes. */
FUNDEF size_t KCALL
usb_controller_transfer_sync(struct usb_controller *__restrict self,
                             struct usb_endpoint *__restrict endp,
                             struct usb_transfer const *__restrict tx);




/* Function called when a new USB endpoint is discovered.
 * This function should try to engage with the endpoint in
 * order to discover what type of device is connected.
 * Note that the given `endp->ue_endp' is always `0' (configure
 * pipe), and that `endp->ue_dev' is also ZERO(0) (aka.: not
 * configured), with this function then being expected to
 * initialize those values before trying to detect the type
 * of connected device, as well as passing the endpoint to
 * the appropriate driver. */
FUNDEF void KCALL
usb_endpoint_discovered(struct usb_controller *__restrict self,
                        struct usb_endpoint *__restrict endp);




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
