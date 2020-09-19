/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_DRIVERS_USB_H
#define GUARD_KERNEL_INCLUDE_DRIVERS_USB_H 1

#include <kernel/compiler.h>

#include <dev/char.h>
#include <kernel/types.h>
#include <misc/atomic-ref.h>
#include <sched/mutex.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <bits/format-printer.h>
#include <kos/kernel/memory.h>

#include <stdbool.h>

/* To use this header, you must add `LIB(":usb")' to your driver's linker group. */

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

DECL_BEGIN

struct usb_device;
struct usb_interface;

struct usb_endpoint {
	WEAK refcnt_t                    ue_refcnt;    /* Reference counter. */
	REF struct usb_interface        *ue_interface; /* [1..1][const][ref_if(!= this)] The associated interface.
	                                                * Note that an interface is also always a descriptor for endpoint 0! */
	u16                              ue_maxpck;    /* [const] Max packet size allowed by this endpoint. */
	u8                               ue_dev;       /* [const] Device address. */
	u8                               ue_endp;      /* [const] Endpoint index (always 0 when `ue_interface == this'). */
#define USB_ENDPOINT_FLAG_DATATOGGLE 0x0001        /* Data toggle bit. */
#define USB_ENDPOINT_MASK_SPEED      0x0300        /* Mask for the device's speed. */
#define USB_ENDPOINT_FLAG_FULLSPEED  0x0000        /* [const] Full-speed device. */
#define USB_ENDPOINT_FLAG_LOWSPEED   0x0100        /* [const] Low-speed device. */
#define USB_ENDPOINT_FLAG_HIGHSPEED  0x0200        /* [const] Low-speed device. */
#define USB_ENDPOINT_FLAG_INPUT      0x0400        /* [const] Input-only endpoint (when clear: output-only endpoint).
	                                                * Note that when `ue_endp == 0', then both input and output are allowed! */
#define USB_ENDPOINT_FLAG_STRANGE    0x0800        /* [const] Set for strange devices (and strange devices only!) */
	u32                              ue_flags;     /* Flags (Set of `USB_ENDPOINT_FLAG_*') */
	struct usb_endpoint_descriptor  *ue_endp_desc; /* [1..1][const][valid_if(ue_interface != this)]
	                                                * The endpoint's descriptor (set to NULL if invalid). */
};

/* Destroy the given USB endpoint descriptor */
FUNDEF NOBLOCK void NOTHROW(KCALL usb_endpoint_destroy)(struct usb_endpoint *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct usb_endpoint, ue_refcnt, usb_endpoint_destroy)

struct usb_interface
#ifdef __cplusplus
	: usb_endpoint
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct usb_endpoint              ui_endp;      /* The associated endpoint. */
#endif /* !__cplusplus */
	REF struct usb_device           *ui_device;    /* [1..1][const][ref_if(!= this)] The associated device.
	                                                * Note that a device is also always a descriptor for endpoint 0!
	                                                * Though also note that an interface is also a descriptor for endpoint 0. */
	u8                               ui_intf;      /* [const][valid_if(ui_device != this)][== ue_intf_desc->ui_intf]
	                                                * Interface index. (part of the USB protocol; not part of the packet addressing system) (set to `0' if invalid) */
	struct usb_interface_descriptor *ui_intf_desc; /* [1..1][const][valid_if(ui_device != this)]
	                                                * The interface's descriptor (set to NULL if invalid). */
	char                            *ui_intf_name; /* [0..1][const][valid_if(ui_device != this)][owned]
	                                                * Name of the interface (if available) (set to NULL if invalid). */
};

struct usb_configuration {
	struct usb_configuration_descriptor *uc_config; /* [1..1][owned] Configuration. */
	char                                *uc_desc;   /* [0..1][owned] An optional string describing this config. */
};

struct usb_device
#ifdef __cplusplus
	: usb_interface
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct usb_interface      ud_intf;         /* The associated interface. */
#endif /* !__cplusplus */
	REF struct usb_device    *ud_next;         /* [0..1][lock(:uc_endpt_lock)] Next device within the associated controller. */
	char                     *ud_str_vendor;   /* [0..1][const][owned] Device vendor name (NUL-terminated utf-8 string) */
	char                     *ud_str_product;  /* [0..1][const][owned] Device product name (NUL-terminated utf-8 string) */
	char                     *ud_str_serial;   /* [0..1][const][owned] Device serial number (NUL-terminated utf-8 string) */
	struct usb_configuration *ud_config;       /* [1..1][const] Used configuration. (WARNING: May be NULL for strange devices; s.a. `USB_ENDPOINT_FLAG_STRANGE') */
	struct usb_configuration  ud_configv[16];  /* [1..ud_configc] Vector of possible configurations.
	                                            * Each entry in this vector has a total size of `ENT->uc_total_len' bytes,
	                                            * with the main descriptor being followed by a variable number of additional
	                                            * descriptors, starting at `(byte_t *)ENT + ENT->uc_size', each of which is
	                                            * lead by a 2-byte pair `byte_t SIZE, TYPE;' */
	u16                       ud_lang_used;    /* [const] Language code used for strings (or 0 if unsupported). */
	u8                        ud_dev;          /* [const] Device address (usually equals `ue_dev', except during the address-assign phase).
	                                            * Essentially, when it comes to checking which addresses are already in use,
	                                            * use `ud_dev'. When it comes to actually talking to a device, use `ue_dev'! */
	u8                        ud_dev_class;    /* [const] Device class */
	u8                        ud_dev_subclass; /* [const] Device subclass */
	u8                        ud_dev_protocol; /* [const] Device protocol */
	u8                        ud_configc;      /* [const][< 16] Number of available configurations */
};


struct usb_transfer {
	struct usb_transfer *ut_next;   /* [0..1] Next transfer packet. */
	struct usb_endpoint *ut_endp;   /* [1..1] The target endpoint. */
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
		physaddr_t                ut_bufp;  /* [valid_if(ut_buftyp == USB_TRANSFER_BUFTYP_PHYS)] */
		struct aio_buffer  const *ut_vbuf;  /* [valid_if(ut_buftyp == USB_TRANSFER_BUFTYP_VIRTVEC)] */
		struct aio_pbuffer const *ut_vbufp; /* [valid_if(ut_buftyp == USB_TRANSFER_BUFTYP_PHYSVEC)] */
	};
};


struct character_device;
struct block_device;


/* USB interrupt handler.
 * @param: self:   [1..1] Either a `struct character_device' or `struct block_device'
 *                 When a reference could not be acquired to the given, the callback
 *                 is not invoked, and behaves as if `USB_INTERRUPT_HANDLER_RETURN_STOP'
 *                 was returned.
 * @param: status: One of `USB_INTERRUPT_HANDLER_STATUS_*'
 * @return: * :    One of `USB_INTERRUPT_HANDLER_RETURN_*' */
typedef NOBLOCK NONNULL((1)) unsigned int
/*NOTHROW*/ (KCALL *PUSB_INTERRUPT_HANDLER)(void *__restrict self,
                                            unsigned int status,
                                            void const *data,
                                            size_t datalen);
#define USB_INTERRUPT_HANDLER_STATUS_OK    0 /* Data was successfully received. */
#define USB_INTERRUPT_HANDLER_STATUS_ERROR 1 /* The USB controller has indicated an error.
                                              * In this case, error_data() has been filled in with additional
                                              * information about the error (usually identical to what would
                                              * be thrown if the same problem had happened during a transmission
                                              * started with `usb_controller_transfer()')
                                              * Note however that the interrupt handler itself is called from
                                              * a context where it may not propagate errors itself, or perform
                                              * any blocking operation, meaning that the only safe thing for it
                                              * to do if it wishes to propagate the exception, is to use a mechanism
                                              * similar (or maybe even backed) by `AIO_COMPLETION_FAILURE' */

#define USB_INTERRUPT_HANDLER_RETURN_SCHED 0 /* Re-schedule the interrupt to-be executed once again. */
#define USB_INTERRUPT_HANDLER_RETURN_STOP  1 /* Stop polling the device for data, and remove the interrupt descriptor
                                              * from the set of those that the USB controller will use for polling
                                              * connected devices for incoming data. */

typedef NOBLOCK NONNULL((1)) unsigned int
/*NOTHROW*/ (KCALL *PUSB_INTERRUPT_HANDLER_CHR)(struct character_device *__restrict self,
                                                unsigned int status,
                                                void const *data, size_t datalen);
typedef NOBLOCK NONNULL((1)) unsigned int
/*NOTHROW*/ (KCALL *PUSB_INTERRUPT_HANDLER_BLK)(struct block_device *__restrict self,
                                                unsigned int status,
                                                void const *data, size_t datalen);



struct usb_interrupt {
	/* Descriptor for interrupt handlers for isochronous (e.g. a microphone),
	 * and interrupt-driven (e.g. a keyboard) USB devices. */
	WEAK refcnt_t            ui_refcnt; /* Reference counter. */
	/* [1..1][const] Finalizer for controller-specific data. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (KCALL *ui_fini)(struct usb_interrupt *__restrict self);
#define USB_INTERRUPT_FLAG_NORMAL      0x0000 /* Normal flags. */
#define USB_INTERRUPT_FLAG_ISACHR      0x0000 /* [const] The bound device is a `struct character_device'. */
#define USB_INTERRUPT_FLAG_ISABLK      0x0001 /* [const] The bound device is a `struct block_device'. */
#define USB_INTERRUPT_FLAG_SHORT       0x0002 /* [const] Allow short packets. */
#define USB_INTERRUPT_FLAG_EVENPERIOD  0x0004 /* [const] Try to round `poll_interval_in_milliseconds', such
	                                           * that all polls happen perfectly evenly spaced from each other.
	                                           * Otherwise, allow 1 in N poll operations to be made slightly
	                                           * earlier, or slightly later than the previous/next. */
#define USB_INTERRUPT_FLAG_DELETED     0x0008 /* [lock(WRITE_ONCE)] The descriptor was deleted. */
#define USB_INTERRUPT_FLAG_CTRL(i)    (0x0010 << (i)) /* Controller-specific flag #i. */
	uintptr_t                ui_flags;   /* Flags (Set of `USB_INTERRUPT_FLAG_*') */
	REF struct usb_endpoint *ui_endp;    /* [const][1..1] The endpoint that is being polled. */
	PUSB_INTERRUPT_HANDLER   ui_handler; /* [const][1..1] Interrupt handler callback. */
	union {
		XATOMIC_WEAKLYREF_STRUCT(struct character_device)   ui_chr; /* [0..1] The pointed-to device. */
		XATOMIC_WEAKLYREF_STRUCT(struct basic_block_device) ui_blk; /* [0..1] The pointed-to device. */
	}                        ui_bind;   /* The bound interrupt handler callback. */
	/* Controller-specific data goes here. */
};
#define USB_INTERRUPT_BINDCHR(self) ((XATOMIC_WEAKLYREF(struct character_device) &)(self)->ui_bind.ui_chr)
#define USB_INTERRUPT_BINDBLK(self) ((XATOMIC_WEAKLYREF(struct basic_block_device) &)(self)->ui_bind.ui_blk)


/* Destroy the given USB interrupt descriptor. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL usb_interrupt_destroy)(struct usb_interrupt *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct usb_interrupt, ui_refcnt, usb_interrupt_destroy)

/* Similar to `decref()', but simultaneously prevent the interrupt for ever firing again.
 * Note that a USB interrupt will stop firing and be removed from the controller's chain
 * of registered interrupts under 3 circumstances:
 *   - When the `USB_INTERRUPT_FLAG_DELETED' flag was set.
 *   - When the bound character- or block-device has been destroyed.
 *   - When the associated callback returns `USB_INTERRUPT_HANDLER_RETURN_STOP'.
 * This function is mean to be used in places such as an ioctl() with the purpose of
 * suspending the data reception from a device such as a microphone.
 * WARNING: Even after this function was called, there exists a small window of time
 *          where the associated interrupt handler will still be invoked, since the
 *          USB controller driver may have already checked for the presence of the
 *          `USB_INTERRUPT_FLAG_DELETED' flag before it got set here, at which point
 *          the callback may be invoked after the interrupt should have already been
 *          deleted. */
LOCAL NOBLOCK void
NOTHROW(KCALL usb_interrupt_delete)(REF struct usb_interrupt *__restrict self) {
	__hybrid_atomic_or(self->ui_flags,
	                   USB_INTERRUPT_FLAG_DELETED,
	                   __ATOMIC_ACQ_REL);
	decref(self);
}

/* Similar to `decref()', but must be called from the finalizer of the bound character-
 * or block-device in order to both inform the USB controller that the device to which
 * this interrupt was bound has been destroyed (this part is required since a USB
 * interrupt only ever holds a weak reference to the bound device, thus preventing the
 * possibility of a reference loop, meaning it needs to be notified when the device gets
 * destroyed), as well as drop the reference previously held by the bound device. */
LOCAL NOBLOCK void
NOTHROW(KCALL usb_interrupt_clear)(REF struct usb_interrupt *__restrict self) {
	xatomic_weaklyref_clear(&self->ui_bind.ui_blk);
	decref(self);
}





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
	struct mutex            uc_disclock; /* Lock that must be held when resetting ports for the purpose
	                                      * of discovering new devices. This lock is required to prevent
	                                      * multiple threads from resetting the ports of different hubs,
	                                      * which could lead to multiple devices bound to ADDR=0, making
	                                      * it impossible to safely configure them individually. */
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
	NONNULL((1, 2, 3)) void
	(KCALL *uc_transfer)(struct usb_controller *__restrict self,
	                     struct usb_transfer const *__restrict tx,
	                     /*out*/ struct aio_handle *__restrict aio);

	/* [1..1] Create an interrupt descriptor.
	 * @param: endp:                          The endpoint from which to poll data.
	 * @param: handler:                       The handler to-be invoked.
	 * @param: character_or_block_device:     Either a `struct character_device' or `struct block_device',
	 *                                        depending on the setting of `USB_INTERRUPT_FLAG_ISABLK'
	 * @param: buflen:                        The (max) number of bytes of data to-be pulled from the device.
	 *                                        Note that unless `USB_INTERRUPT_FLAG_SHORT' is set, this is the
	 *                                        mandatory buffer size, with it being an error if the device
	 *                                        produces less data that this, meaning that unless said flag is
	 *                                        set, your handler is allowed to completely ignore its `datalen'
	 *                                        argument and simply assume that the buffer's size is equal to
	 *                                        the `buflen' value passed when the interrupt was registered.
	 * @param: flags:                         Set of `USB_INTERRUPT_FLAG_*'
	 * @param: poll_interval_in_milliseconds: A hint for how often the USB device should be polled.
	 *                                        When set to `0', the device will be polled as often as possible. */
	ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3, 4)) REF struct usb_interrupt *
	(KCALL *uc_interrupt)(struct usb_controller *__restrict self, struct usb_endpoint *__restrict endp,
	                      PUSB_INTERRUPT_HANDLER handler, void *__restrict character_or_block_device,
	                      size_t buflen, uintptr_t flags, unsigned int poll_interval_in_milliseconds);
};

#define usb_controller_cinit(self)                  \
	(atomic_rwlock_cinit(&(self)->uc_devslock),     \
	 __hybrid_assert((self)->uc_devs == __NULLPTR), \
	 mutex_cinit(&(self)->uc_disclock))


/* Perform a one-time transfer of a sequence of packets.
 * This is the primary functions for OS-initiated communications
 * with connected USB devices.
 * For communications initiated by the device, see the interface
 * for doing this below.
 * @param: self: The controller which will be used for the transfer
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
LOCAL NONNULL((1, 2, 3)) void KCALL
usb_controller_transfer(struct usb_controller *__restrict self,
                        struct usb_transfer const *__restrict tx,
                        /*out*/ struct aio_handle *__restrict aio) {
	(*self->uc_transfer)(self, tx, aio);
}

/* Same as `usb_controller_transfer()', but wait for the transfer to
 * complete (essentially just a wrapper using `struct aio_handle_generic')
 * @return: * : The total number of transferred bytes. */
FUNDEF NONNULL((1, 2)) size_t KCALL
usb_controller_transfer_sync(struct usb_controller *__restrict self,
                             struct usb_transfer const *__restrict tx);



/* Create an interrupt descriptor.
 * @param: endp:                          The endpoint from which to poll data.
 * @param: handler:                       The handler to-be invoked.
 * @param: character_or_block_device:     Either a `struct character_device' or `struct block_device',
 *                                        depending on the setting of `USB_INTERRUPT_FLAG_ISABLK'
 * @param: buflen:                        The (max) number of bytes of data to-be pulled from the device.
 *                                        Note that unless `USB_INTERRUPT_FLAG_SHORT' is set, this is the
 *                                        mandatory buffer size, with it being an error if the device
 *                                        produces less data that this, meaning that unless said flag is
 *                                        set, your handler is allowed to completely ignore its `datalen'
 *                                        argument and simply assume that the buffer's size is equal to
 *                                        the `buflen' value passed when the interrupt was registered.
 * @param: flags:                         Set of `USB_INTERRUPT_FLAG_*'
 * @param: poll_interval_in_milliseconds: A hint for how often the USB device should be polled.
 *                                        When set to `0', the device will be polled as often as possible. */
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3, 4)) REF struct usb_interrupt *KCALL
usb_controller_interrupt_create(struct usb_controller *__restrict self, struct usb_endpoint *__restrict endp,
                                PUSB_INTERRUPT_HANDLER handler, void *__restrict character_or_block_device,
                                size_t buflen, uintptr_t flags, unsigned int poll_interval_in_milliseconds DFL(0)) {
	REF struct usb_interrupt *result;
	__hybrid_assert(self->uc_interrupt);
	result = (*self->uc_interrupt)(self, endp, handler, character_or_block_device,
	                               buflen, flags, poll_interval_in_milliseconds);
	return result;
}


#ifdef __cplusplus
extern "C++" {
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct usb_interrupt *KCALL
usb_controller_interrupt_create(struct usb_controller *__restrict self,
                                struct usb_endpoint *__restrict endp,
                                PUSB_INTERRUPT_HANDLER_CHR handler,
                                struct character_device *__restrict device,
                                size_t buflen, uintptr_t flags DFL(USB_INTERRUPT_FLAG_NORMAL),
                                unsigned int poll_interval_in_milliseconds DFL(0)) {
	REF struct usb_interrupt *result;
	__hybrid_assert(!(flags & (USB_INTERRUPT_FLAG_ISACHR | USB_INTERRUPT_FLAG_ISABLK)));
	result = usb_controller_interrupt_create(self, endp,
	                                         (PUSB_INTERRUPT_HANDLER)handler,
	                                         (void *)device, buflen,
	                                         flags | USB_INTERRUPT_FLAG_ISACHR,
	                                         poll_interval_in_milliseconds);
	return result;
}

LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct usb_interrupt *KCALL
usb_controller_interrupt_create(struct usb_controller *__restrict self,
                                struct usb_endpoint *__restrict endp,
                                PUSB_INTERRUPT_HANDLER_BLK handler,
                                struct block_device *__restrict device,
                                size_t buflen, uintptr_t flags DFL(USB_INTERRUPT_FLAG_NORMAL),
                                unsigned int poll_interval_in_milliseconds DFL(0)) {
	REF struct usb_interrupt *result;
	__hybrid_assert(!(flags & (USB_INTERRUPT_FLAG_ISACHR | USB_INTERRUPT_FLAG_ISABLK)));
	result = usb_controller_interrupt_create(self, endp,
	                                         (PUSB_INTERRUPT_HANDLER)handler,
	                                         (void *)device, buflen,
	                                         flags | USB_INTERRUPT_FLAG_ISABLK,
	                                         poll_interval_in_milliseconds);
	return result;
}
}
#endif /* __cplusplus */




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
 * If `index' is invalid, or the given `dev' didn't return a string, then
 * return 0 without doing anything. */
FUNDEF NONNULL((1, 2, 4)) ssize_t KCALL
usb_controller_printstring(struct usb_controller *__restrict self,
                           struct usb_device *__restrict dev, u8 index,
                           __pformatprinter printer, void *arg);

/* Helper wrapper for `usb_controller_printstring()'
 * This function returns a heap-allocated string, or NULL under the same
 * circumstances where `usb_controller_printstring()' would return `0' */
FUNDEF ATTR_MALLOC WUNUSED NONNULL((1, 2)) /*utf-8*/ char *KCALL
usb_controller_allocstring(struct usb_controller *__restrict self,
                           struct usb_device *__restrict dev, u8 index);



/* Function called when a new USB endpoint is discovered.
 * NOTE: This function also releases a lock to `self->uc_disclock'
 *       once the device has been assigned an address. In the event
 *       that an exception occurs before then, this lock will also
 *       be released, meaning that this function _always_ releases
 *       such a lock.
 * @param: endpoint_flags: Set of `USB_ENDPOINT_FLAG_*', though only
 *                         flags masked by `USB_ENDPOINT_MASK_SPEED'
 *                         may be specified. */
FUNDEF void KCALL
usb_device_discovered(struct usb_controller *__restrict self,
                      u32 endpoint_flags);


/* Try to bind the given USB device `dev' to a driver.
 * This function should look at `dev->ud_dev_(class|subclass|protocol)'
 * in order to determine the type of connected device.
 * If all registered callbacks fail to identify the device, at least one
 * of the device's configurations will be chosen, which will then be used
 * to scan for interfaces, which are then passed to callbacks registered
 * with `usb_register_interface_probe()'
 * @assume(dev->ud_configc >= 2);
 * @assume(dev->ud_dev_class != 0);
 * @return: true:  The device was discovered successfully.
 *                 In this case, the callback will have initialized
 *                 `dev->ud_config' to point to the appropriate configuration.
 * @return: false: The device wasn't recognized. */
typedef bool (KCALL *PUSB_DEVICE_PROBE)(struct usb_controller *__restrict self,
                                        struct usb_device *__restrict dev);

/* Try to bind the given `intf', as well as the associated endpoints a driver.
 * This function should be implemented by USB driver providers, and should look
 * at `intf->ui_intf_desc->ui_intf_(class|subclass|protocol)' in order to determine
 * if the interface's classification is recognized by the specific driver.
 * If the interface isn't recognized, the function should bail out and return `false'
 * @assume(endpv[0..endpc-1] != NULL)
 * @return: true:  The interface was discovered successfully.
 * @return: false: The interface wasn't recognized. */
typedef bool (KCALL *PUSB_INTERFACE_PROBE)(struct usb_controller *__restrict self,
                                           struct usb_interface *__restrict intf,
                                           size_t endpc, struct usb_endpoint *const endpv[]);

/* Register/unregister USB device/interface probe callbacks that get invoked
 * when a new device is discovered.
 * Note that device probes are only invoked for multi-function devices (i.e. ones
 * with multiple configurations), and have the purpose to allow drivers to be provided
 * for combinations of certain devices.
 * NOTE: After registering a new interface probe function, any USB interface that had
 *       not been recognized at that point will immediately be probed using the given
 *       `func' before returning. */
FUNDEF bool KCALL usb_register_device_probe(PUSB_DEVICE_PROBE func) THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF bool KCALL usb_register_interface_probe(PUSB_INTERFACE_PROBE func) THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF bool KCALL usb_unregister_device_probe(PUSB_DEVICE_PROBE func) THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF bool KCALL usb_unregister_interface_probe(PUSB_INTERFACE_PROBE func) THROWS(E_WOULDBLOCK, E_BADALLOC);


struct block_device;
struct character_device;

/* Register mappings between USB devices and device files, such that
 * the USB system can attempt to unregister and remove device files
 * bound to some USB device when it is detected that the usb device
 * was unplugged from the system.
 * Note that these functions should be called like this:
 * >> struct (character|block)_device *mydev;
 * >> mydev = CREATE_DEVICE(usb_dev);
 * >> (character|block)_device_register[_auto](mydev);
 * >> TRY {
 * >>     usb_register_device(usb_dev, mydev);
 * >> } EXCEPT {
 * >>     (character|block)_device_unregister(mydev);
 * >>     RETHROW();
 * >> }
 * Note that it is possible to register any number of devices for any
 * single given USB device, however it is not possible to delete such
 * a registration, other than physically removing the associated device.
 */
FUNDEF void KCALL usb_register_block_device(struct usb_device *__restrict usb_dev, struct block_device *__restrict dev) THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF void KCALL usb_register_character_device(struct usb_device *__restrict usb_dev, struct character_device *__restrict dev) THROWS(E_WOULDBLOCK, E_BADALLOC);
#ifdef __cplusplus
extern "C++" {
FUNDEF void KCALL usb_register_device(struct usb_device *__restrict usb_dev, struct block_device *__restrict dev) ASMNAME("usb_register_block_device");
FUNDEF void KCALL usb_register_device(struct usb_device *__restrict usb_dev, struct character_device *__restrict dev) ASMNAME("usb_register_character_device");
}
#endif /* __cplusplus */


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

#endif /* !GUARD_KERNEL_INCLUDE_DRIVERS_USB_H */
