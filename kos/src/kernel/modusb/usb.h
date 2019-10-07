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

#include <hybrid/sync/atomic-rwlock.h>
#include <kernel/types.h>
#include <bits/format-printer.h>
#include <dev/char.h>

DECL_BEGIN

struct usb_endpoint {
	WEAK refcnt_t ue_refcnt;       /* Reference counter. */
	char         *ue_str_vendor;   /* [0..1][const][owned] Device vendor name (NUL-terminated utf-8 string) */
	char         *ue_str_product;  /* [0..1][const][owned] Device product name (NUL-terminated utf-8 string) */
	char         *ue_str_serial;   /* [0..1][const][owned] Device serial number (NUL-terminated utf-8 string) */
	u16           ue_lang_used;    /* [const] Language code used for strings (or 0 if unsupported). */
	u16           ue_maxpck;       /* [const] Max packet size. */
	u8            ue_dev;          /* [const] Device address. */
	u8            ue_endp;         /* [const] Endpoint index. */
	unsigned int  ue_toggle : 1;   /* Data toggle bit. */
	unsigned int  ue_lowspeed : 1; /* Low-speed device. */
};

/* Destroy the given USB endpoint descriptor */
FUNDEF NOBLOCK void NOTHROW(KCALL usb_endpoint_destroy)(struct usb_endpoint *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct usb_endpoint, ue_refcnt, usb_endpoint_destroy)

struct usb_device
#ifdef __cplusplus
	: usb_endpoint
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct usb_endpoint    ud_endp; /* Endpoint 0 (ue_endp==0). */
#endif /* !__cplusplus */
	REF struct usb_device *ud_next; /* [0..1][lock(:uc_endpt_lock)] Next device within the associated controller. */
	u8                     ud_dev;  /* [const] Device address (usually equals `ue_dev', except during the address-assign phase).
	                                 * Essentially, when it comes to checking which addresses are already in use,
	                                 * use `ud_dev'. When it comes to actually talking to a device, use `ue_dev'! */
};


struct usb_transfer {
	struct usb_transfer *ut_next;   /* [0..1] Next transfer packet. */
#define USB_TRANSFER_TYPE_IN          0 /* Receive data. */
#define USB_TRANSFER_TYPE_OUT         1 /* Send data. */
#define USB_TRANSFER_TYPE_FLAG_STATUS 2 /* Flag for getting the proper status-stage type, to-be or'd to a data-stage type.
	                                     * Note that this is the reverse direction of the data stage packet. */
#define USB_TRANSFER_TYPE_OUT_STATUS  2 /* Out status packet */
#define USB_TRANSFER_TYPE_IN_STATUS   3 /* In status packet */
#define USB_TRANSFER_TYPE_SETUP       4 /* Send control data. */
#define USB_TRANSFER_TYPE_COUNT       5 /* # of transfer types */
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
	struct character_device uc_dev;      /* The underlying character device. */
#endif /* !__cplusplus */
	struct atomic_rwlock    uc_devslock; /* Lock for `uc_devs' */
	REF struct usb_device  *uc_devs;     /* [0..1][lock(uc_devslock)] Chain of known USB devices. */
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
	                     /*out*/ struct aio_handle *__restrict aio);
	/* TODO: Interface for registering Isochronous interrupt handlers. */
};

#define usb_controller_cinit(self)              \
	(atomic_rwlock_cinit(&(self)->uc_devslock), \
	 __hybrid_assert((self)->uc_devs == __NULLPTR))


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
 *               indicate completion.
 *               Note that USB protocols also allow for back-propagation of
 *               the total number of transferred bytes from, which is available
 *               upon AIO completion via the `ht_retsize' operator of `aio',
 *               which is guarantied to have been initialized by this function. */
LOCAL NONNULL((1, 2, 3, 4)) void KCALL
usb_controller_transfer(struct usb_controller *__restrict self,
                        struct usb_endpoint *__restrict endp,
                        struct usb_transfer const *__restrict tx,
                        /*out*/ struct aio_handle *__restrict aio) {
	(*self->uc_transfer)(self, endp, tx, aio);
}

/* Same as `usb_controller_transfer()', but wait for the transfer to
 * complete (essentially just a wrapper using `struct aio_handle_generic')
 * @return: * : The total number of transferred bytes. */
FUNDEF NONNULL((1, 2, 3)) size_t KCALL
usb_controller_transfer_sync(struct usb_controller *__restrict self,
                             struct usb_endpoint *__restrict endp,
                             struct usb_transfer const *__restrict tx);


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
FUNDEF NONNULL((1, 2, 3, 5)) void KCALL
usb_controller_request(struct usb_controller *__restrict self,
                       struct usb_endpoint *__restrict endp,
                       struct usb_request const *__restrict request,
                       void *buf, /*out*/ struct aio_handle *__restrict aio);

/* Same as `usb_controller_request()', but wait for the operation to complete.
 * Additionally, return the number of bytes written to, or read from `buf' */
FUNDEF NONNULL((1, 2, 3)) size_t KCALL
usb_controller_request_sync(struct usb_controller *__restrict self,
                            struct usb_endpoint *__restrict endp,
                            struct usb_request const *__restrict request,
                            void *buf);

/* Print the device string associated with `index' to the given `printer'.
 * If `index' is invalid, or the given `endp' didn't return a string, then
 * return 0 without doing anything. */
FUNDEF NONNULL((1, 2, 4)) ssize_t KCALL
usb_controller_printstring(struct usb_controller *__restrict self,
                           struct usb_endpoint *__restrict endp, u8 index,
                           __pformatprinter printer, void *arg);

/* Helper wrapper for `usb_controller_printstring()'
 * This function returns a heap-allocated string, or NULL under the same
 * circumstances where `usb_controller_printstring()' would return `0' */
FUNDEF WUNUSED ATTR_MALLOC NONNULL((1, 2)) /*utf-8*/ char *KCALL
usb_controller_allocstring(struct usb_controller *__restrict self,
                           struct usb_endpoint *__restrict endp, u8 index);



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
FUNDEF void KCALL
usb_device_discovered(struct usb_controller *__restrict self,
                      struct usb_device *__restrict dev);



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
