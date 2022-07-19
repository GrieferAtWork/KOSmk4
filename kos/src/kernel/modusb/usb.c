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
#ifndef GUARD_MODUSB_USB_C
#define GUARD_MODUSB_USB_C 1
#define BUILDING_MODUSB
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <drivers/usb.h>
#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/malloc.h>
#include <kernel/mman/driver.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <hw/usb/usb.h>
#include <kos/aref.h>
#include <kos/except/reason/io.h>

#include <assert.h>
#include <format-printer.h>
#include <stddef.h>
#include <string.h>
#include <unicode.h>

#include "hub.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

struct usb_probe_entry {
	union {
		PUSB_DEVICE_PROBE    c_device; /* [1..1] Device probe callback */
		PUSB_INTERFACE_PROBE c_intf;   /* [1..1] Interface probe callback */
		void                *c_func;   /* [1..1] Probe callback */
	};
	REF struct driver       *c_driver; /* [1..1] The driver implementing this probe. */
};

struct usb_probe_vector {
	WEAK refcnt_t                                   upv_refcnt; /* Callback vector reference counter. */
	size_t                                          upv_count;  /* Number of elements. */
	COMPILER_FLEXIBLE_ARRAY(struct usb_probe_entry, upv_elem);  /* [0..upv_count] Vector of elements. */
};
DEFINE_REFCNT_FUNCTIONS(struct usb_probe_vector, upv_refcnt, kfree)

ARREF(usb_probe_vector_arref, usb_probe_vector);

PRIVATE struct usb_probe_vector empty_probe_vector = { 3, 0 };
PRIVATE struct usb_probe_vector_arref probe_device    = ARREF_INIT(&empty_probe_vector);
PRIVATE struct usb_probe_vector_arref probe_interface = ARREF_INIT(&empty_probe_vector);



struct usb_unknown_interface {
	WEAK refcnt_t                                      uui_refcnt; /* Reference counter. */
	REF struct usb_unknown_interface                  *uui_next;   /* [0..1][lock(ATOMIC)] Next unknown interface. */
	REF struct usb_controller                         *uui_ctrl;   /* [1..1] The associated controller. */
	REF struct usb_interface                          *uui_intf;   /* [1..1] The associated interface. */
	size_t                                             uui_endpc;  /* Number of endpoints. */
	COMPILER_FLEXIBLE_ARRAY(REF struct usb_endpoint *, uui_endpv); /* [1..1][0..uui_endpc] Associated interfaces. */
};

LOCAL NOBLOCK void
NOTHROW(KCALL usb_unknown_interface_destroy)(struct usb_unknown_interface *__restrict self) {
	size_t i;
	for (i = 0; i < self->uui_endpc; ++i)
		decref_likely(self->uui_endpv[i]);
	decref_likely(self->uui_intf);
	decref_likely(self->uui_ctrl);
	kfree(self);
}

DEFINE_REFCNT_FUNCTIONS(struct usb_unknown_interface, uui_refcnt, usb_unknown_interface_destroy)


/* [lock(ATOMIC)] Chain of unknown USB interfaces.
 * NOTE: Set to `USB_UNKNOWNS_CLOSED' after the usb driver has been finalized. */
PRIVATE WEAK REF struct usb_unknown_interface *usb_unknowns = NULL;

#define USB_UNKNOWNS_CLOSED  ((REF struct usb_unknown_interface *)-1)
PRIVATE DRIVER_FINI void KCALL usb_unknowns_fini(void) {
	REF struct usb_unknown_interface *un, *next;
	un = ATOMIC_XCH(usb_unknowns, USB_UNKNOWNS_CLOSED);
	if (un != USB_UNKNOWNS_CLOSED) {
		while (un) {
			next = un->uui_next;
			decref_likely(un);
			un = next;
		}
	}
}

PRIVATE NOBLOCK void
NOTHROW(KCALL usb_unknowns_appendall)(/*inherit*/ REF struct usb_unknown_interface *self) {
	struct usb_unknown_interface *last;
	if (!self)
		return; /* No devices to append. */
	last = self;
	while (last->uui_next)
		last = last->uui_next;
	for (;;) {
		struct usb_unknown_interface *next;
		next = ATOMIC_READ(usb_unknowns);
		if unlikely(next == USB_UNKNOWNS_CLOSED) {
			/* The USB driver was closed (discard the given interface) */
			decref(self);
			return;
		}
		last->uui_next = next;
		COMPILER_WRITE_BARRIER();
		if (ATOMIC_CMPXCH_WEAK(usb_unknowns, next, self))
			break;
	}
}

/* [0..1] The thread currently probing for unknown interfaces.
 *        To prevent a  single interface from  being more than  once,
 *        only a  single thread  can ever  probe unknown  interfaces,
 *        and even then, recursion mustn't be allowed, with recursive
 *        calls simply ending up as no-ops. */
PRIVATE WEAK struct task *usb_probe_unknown_lock = NULL;
PRIVATE struct sig usb_probe_unknown_unlock = SIG_INIT;

PRIVATE bool KCALL usb_probe_unknown_acquire(void) {
	struct task *ot, *me;
	assert(!task_wasconnected());
	me = THIS_TASK;
again:
	ot = ATOMIC_CMPXCH_VAL(usb_probe_unknown_lock, NULL, me);
	if (!ot)
		return true; /* Lock acquired. */
	if unlikely(ot == me)
		return false; /* Don't allow recursion. */
	task_connect(&usb_probe_unknown_unlock);
	if (ATOMIC_CMPXCH(usb_probe_unknown_lock, NULL, me)) {
		task_disconnectall();
		return true;
	}
	task_waitfor();
	goto again;
}

PRIVATE NOBLOCK void NOTHROW(KCALL usb_probe_unknown_release)(void) {
	assert(usb_probe_unknown_lock == THIS_TASK);
	ATOMIC_WRITE(usb_probe_unknown_lock, NULL);
	/* Only one thread can be holding `usb_probe_unknown_lock',
	 * so only wake  up a single  thread by using  `sig_send()' */
	sig_send(&usb_probe_unknown_unlock);
}

LOCAL bool KCALL
usb_probe_builtin_interfaces(struct usb_controller *__restrict self,
                             struct usb_interface *__restrict intf,
                             size_t endpc, struct usb_endpoint *const endpv[]) {
	if (usbhubdev_probe(self, intf, endpc, endpv))
		goto ok;
	/* Other builtin interfaces would go here... */
	return false;
ok:
	return true;
}



/* Probe all unknown interfaces using the given `func', removing
 * interfaces  that   have  been   identified  following   this.
 * Additionally, `func' may be NULL to use all global callback probes
 * for probing unknown interfaces. */
PRIVATE void KCALL usb_probe_identify_unknown(PUSB_INTERFACE_PROBE func) {
	REF struct usb_unknown_interface *chain, **piter, *iter;
	REF struct usb_probe_vector *probes = NULL;
	if (!usb_probe_unknown_acquire())
		return; /* Recursion within the same thread. */
	if (!func)
		probes = arref_get(&probe_interface);
	RAII_FINALLY {
		usb_probe_unknown_release();
		xdecref_unlikely(probes);
	};
	for (;;) {
		chain = ATOMIC_READ(usb_unknowns);
		if (chain == USB_UNKNOWNS_CLOSED)
			return; /* No-op after finalize */
		if (chain == NULL)
			return; /* Nothing to enumerate */
		if (ATOMIC_CMPXCH_WEAK(usb_unknowns, chain, NULL))
			break;
	}
	RAII_FINALLY { usb_unknowns_appendall(chain); };
	piter = &chain;
again_piter:
	for (; (iter = *piter) != NULL;
	     piter = &iter->uui_next) {
		bool was_found;
		if (func) {
			assert(!probes);
			was_found = (*func)(iter->uui_ctrl,
			                    iter->uui_intf,
			                    iter->uui_endpc,
			                    iter->uui_endpv);
		} else {
			/* Scan using all defined probes. */
			size_t i;
			assert(probes);
			was_found = false;
			for (i = 0; i < probes->upv_count; ++i) {
				was_found = (*probes->upv_elem[i].c_intf)(iter->uui_ctrl,
				                                          iter->uui_intf,
				                                          iter->uui_endpc,
				                                          iter->uui_endpv);
				if (was_found)
					break;
			}
		}
		if (was_found) {
			/* Found one! (remove from the list to-be restored later) */
			*piter = iter->uui_next;
			/* Drop the chain reference from the removed element. */
			decref_likely(iter);
			goto again_piter;
		}
	}
}




PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL vector_contains)(struct usb_probe_vector const *__restrict self,
                               void *func) {
	size_t i;
	for (i = 0; i < self->upv_count; ++i) {
		if (self->upv_elem[i].c_func == func)
			return true;
	}
	return false;
}

PRIVATE bool KCALL
probe_add(struct usb_probe_vector_arref *__restrict self, void *func) {
	REF struct usb_probe_vector *ovec, *nvec;
	REF struct driver *func_driver;
	size_t i;
again:
	ovec = arref_get(self);
	if unlikely(vector_contains(ovec, func)) {
		decref_unlikely(ovec);
		return false;
	}
	func_driver = driver_fromaddr(func);
	TRY {
		if unlikely(!func_driver)
			THROW(E_SEGFAULT_NOTEXECUTABLE, func, E_SEGFAULT_CONTEXT_FAULT);
		nvec = (REF struct usb_probe_vector *)kmalloc(offsetof(struct usb_probe_vector, upv_elem) +
		                                              (ovec->upv_count + 1) * sizeof(struct usb_probe_entry),
		                                              GFP_NORMAL);
	} EXCEPT {
		decref_unlikely(func_driver);
		decref_unlikely(ovec);
		RETHROW();
	}
	memcpy(nvec->upv_elem,
	       ovec->upv_elem,
	       ovec->upv_count,
	       sizeof(struct usb_probe_entry));
	/* Update reference counts of copied drivers. */
	for (i = 0; i < ovec->upv_count; ++i)
		incref(ovec->upv_elem[i].c_driver);
	nvec->upv_refcnt = 1;
	nvec->upv_elem[ovec->upv_count].c_func   = func;
	nvec->upv_elem[ovec->upv_count].c_driver = incref(func_driver);
	nvec->upv_count = ovec->upv_count + 1;

	if (!arref_cmpxch_inherit_new(self, ovec, nvec)) {
		destroy(nvec);
		decref_unlikely(ovec);
		decref_unlikely(func_driver);
		goto again;
	}
	printk(KERN_INFO "[usb] Register %s-probe (%p in driver %q)\n",
	       self == &probe_device ? "device" : "interface",
	       func, func_driver->d_name);
	decref_unlikely(func_driver);
	decref(ovec);
	return true;
}

PRIVATE bool KCALL
probe_del(struct usb_probe_vector_arref *__restrict self, void *func) {
	REF struct usb_probe_vector *ovec, *nvec;
	REF struct driver *func_driver;
	size_t i, del_index;
again:
	ovec = arref_get(self);
	for (del_index = 0; del_index < ovec->upv_count; ++del_index) {
		if (ovec->upv_elem[del_index].c_func == func)
			goto found_index;
	}
	decref_unlikely(ovec);
	return false;
found_index:
	TRY {
		nvec = (REF struct usb_probe_vector *)kmalloc(offsetof(struct usb_probe_vector, upv_elem) +
		                                              (ovec->upv_count - 1) * sizeof(struct usb_probe_entry),
		                                              GFP_NORMAL);
	} EXCEPT {
		decref_unlikely(ovec);
		RETHROW();
	}
	nvec->upv_refcnt = 1;
	nvec->upv_count  = ovec->upv_count - 1;
	memcpy(nvec->upv_elem,
	       ovec->upv_elem,
	       del_index,
	       sizeof(struct usb_probe_entry));
	memcpy(nvec->upv_elem + del_index,
	       ovec->upv_elem + (del_index + 1),
	       nvec->upv_count - del_index,
	       sizeof(struct usb_probe_entry));
	/* Update reference counts of copied drivers. */
	for (i = 0; i < nvec->upv_count; ++i)
		incref(nvec->upv_elem[i].c_driver);
	func_driver = ovec->upv_elem[del_index].c_driver; /* Inherit reference */
	if (!arref_cmpxch_inherit_new_nokill(self, ovec, nvec)) {
		destroy(nvec);
		decref_unlikely(ovec);
		goto again;
	}
	printk(KERN_INFO "[usb] Delete %s-probe (%p in driver %q)\n",
	       self == &probe_device ? "device" : "interface",
	       func, func_driver->d_name);
	decref(func_driver);
	decref(ovec);
	return true;
}

/* Register/unregister USB device/interface probe callbacks that get invoked
 * when a new device is discovered.
 * Note that device  probes are  only invoked  for multi-function  devices (i.e.  ones
 * with multiple configurations), and have the purpose to allow drivers to be provided
 * for combinations of certain devices.
 * NOTE: After registering a new interface probe function, any USB interface that had
 *       not been recognized at that point will immediately be probed using the given
 *       `func' before returning. */
PUBLIC bool KCALL
usb_register_device_probe(PUSB_DEVICE_PROBE func)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	return probe_add(&probe_device, (void *)func);
}

PUBLIC bool KCALL
usb_register_interface_probe(PUSB_INTERFACE_PROBE func)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	bool result;
	result = probe_add(&probe_interface, (void *)func);
	if (result) {
		/* Got through all  strange interfaces we've  encountered thus  far,
		 * and try to identify them using this newly added probing function. */
		usb_probe_identify_unknown(func);
	}
	return result;
}

PUBLIC bool KCALL
usb_unregister_device_probe(PUSB_DEVICE_PROBE func)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	return probe_del(&probe_device, (void *)func);
}

PUBLIC bool KCALL
usb_unregister_interface_probe(PUSB_INTERFACE_PROBE func)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	return probe_del(&probe_interface, (void *)func);
}


/* Create a character device under /dev for a strange USB endpoint/device. */
PRIVATE void KCALL
usb_create_strange_device_nowarn(struct usb_controller *__restrict self,
                                 struct usb_device *__restrict dev) {
	(void)self;
	(void)dev;
	/* TODO */
}

PRIVATE void KCALL
usb_create_strange_device(struct usb_controller *__restrict self,
                          struct usb_device *__restrict dev) {
	printk(KERN_WARNING "[usb] Creating device file for strange USB "
	                    "device %q:%q:%q (interface:%q, endpoint:%I8u)\n",
	       dev->ue_interface->ui_device->ud_str_vendor,
	       dev->ue_interface->ui_device->ud_str_product,
	       dev->ue_interface->ui_device->ud_str_serial,
	       dev->ue_interface->ui_intf_name,
	       dev->ue_endp);
	usb_create_strange_device_nowarn(self, dev);
}







PRIVATE void KCALL
usb_interface_discovered(struct usb_controller *__restrict self,
                         struct usb_interface *__restrict intf,
                         size_t endpc, struct usb_endpoint *const endpv[]) {
	size_t i;
	REF struct usb_probe_vector *probes, *new_probes;
	printk(KERN_NOTICE "[usb] Discovered device %q:%q:%q with interface "
	                   "%q(%#x.%#x.%#x) (config %q) and %Iu endpoints",
	       intf->ui_device->ud_str_vendor,
	       intf->ui_device->ud_str_product,
	       intf->ui_device->ud_str_serial,
	       intf->ui_intf_name,
	       intf->ui_intf_desc->ui_intf_class,
	       intf->ui_intf_desc->ui_intf_subclass,
	       intf->ui_intf_desc->ui_intf_protocol,
	       intf->ui_device->ud_config->uc_desc,
	       endpc);
	if (endpc != 0) {
		printk(KERN_NOTICE " [%I8u", endpv[0]->ue_endp);
		for (i = 1; i < endpc; ++i) {
			printk(KERN_NOTICE ",%I8u",
				   endpv[i]->ue_endp);
		}
		printk(KERN_NOTICE "]\n");
	} else {
		printk(KERN_NOTICE "\n");
	}

	/* Go through loaded drivers and try to have drivers bind the interface. */
	probes = arref_get(&probe_interface);
	TRY {
		REF struct usb_unknown_interface *unknown;
		/* Try to probe the device for matching one of the builtin interfaces (e.g. a HUB) */
		if (usb_probe_builtin_interfaces(self, intf, endpc, endpv))
			return;
		for (i = 0; i < probes->upv_count; ++i) {
			/* Try to identify this interface/endpoint combination. */
			if ((*probes->upv_elem[i].c_intf)(self, intf, endpc, endpv))
				return;
		}
		/* Create a descriptor to keep track of the unknown interface. */
		if unlikely(ATOMIC_READ(usb_unknowns) == USB_UNKNOWNS_CLOSED)
			return; /* No-op after USB has been finalized. */

		unknown = (REF struct usb_unknown_interface *)kmalloc(offsetof(struct usb_unknown_interface, uui_endpv) +
		                                                      (endpc * sizeof(REF struct usb_endpoint *)),
		                                                      GFP_NORMAL);
		unknown->uui_refcnt = 1; /* The reference inherited by `usb_unknowns' */
		unknown->uui_ctrl   = (REF struct usb_controller *)incref(self);
		unknown->uui_intf   = (REF struct usb_interface *)incref(intf);
		unknown->uui_endpc  = endpc;
		memcpy(unknown->uui_endpv, endpv,
		       endpc, sizeof(REF struct usb_endpoint *));
		for (i = 0; i < endpc; ++i)
			incref(unknown->uui_endpv[i]);

		/* Register the unknown interface. */
		for (;;) {
			REF struct usb_unknown_interface *next_unknown;
			next_unknown = ATOMIC_READ(usb_unknowns);
			if unlikely(next_unknown == USB_UNKNOWNS_CLOSED) {
				/* No-op after the USB driver has been finalized. */
				destroy(unknown);
				return;
			}
			unknown->uui_next = next_unknown;
			COMPILER_WRITE_BARRIER();
			if (ATOMIC_CMPXCH_WEAK(usb_unknowns, next_unknown, unknown))
				break;
		}

		printk(KERN_NOTICE "[usb] Failed to identify device %q:%q:%q "
		                   "with interface %q(%#x.%#x.%#x) (config %q)\n",
		       intf->ui_device->ud_str_vendor,
		       intf->ui_device->ud_str_product,
		       intf->ui_device->ud_str_serial,
		       intf->ui_intf_name,
		       intf->ui_intf_desc->ui_intf_class,
		       intf->ui_intf_desc->ui_intf_subclass,
		       intf->ui_intf_desc->ui_intf_protocol,
		       intf->ui_device->ud_config->uc_desc);
	} EXCEPT {
		decref_unlikely(probes);
		RETHROW();
	}
	/* Check if new probes may have been added in the mean  time.
	 * If so, try  once again to  identify unknown devices,  thus
	 * ensuring that every probe has had a chance to identify our
	 * new unknown interface. */
	for (;;) {
		new_probes = arref_ptr(&probe_interface);
		if likely(new_probes == probes)
			break;
		new_probes = arref_get(&probe_interface);
		decref_unlikely(probes);
		probes = new_probes;
		usb_probe_identify_unknown(NULL);
	}
	decref_unlikely(probes);
}







/* Destroy the given USB endpoint descriptor */
PUBLIC NOBLOCK void
NOTHROW(KCALL usb_endpoint_destroy)(struct usb_endpoint *__restrict self) {
	if (self->ue_interface != self) {
		decref(self->ue_interface);
	} else {
		struct usb_interface *intf_me;
		intf_me = (struct usb_interface *)self;
		if (intf_me->ui_device != self) {
			kfree(intf_me->ui_intf_name);
			decref(intf_me->ui_device);
		} else {
			u8 i;
			struct usb_device *dev_me;
			dev_me = (struct usb_device *)self;
			for (i = 0; i < dev_me->ud_configc; ++i) {
				kfree(dev_me->ud_configv[i].uc_config);
				kfree(dev_me->ud_configv[i].uc_desc);
			}
			kfree(dev_me->ud_str_vendor);
			kfree(dev_me->ud_str_product);
			kfree(dev_me->ud_str_serial);
		}
	}
	kfree(self);
}


/* Same as  `usb_controller_transfer()',  but  wait for  the  transfer  to
 * complete (essentially just a wrapper using `struct aio_handle_generic')
 * @return: * : The total number of transferred bytes. */
PUBLIC NONNULL((1, 2)) size_t KCALL
usb_controller_transfer_sync(struct usb_controller *__restrict self,
                             struct usb_transfer const *__restrict tx) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	usb_controller_transfer(self, tx, &aio);
	RAII_FINALLY { aio_handle_generic_fini(&aio); };
	aio_handle_generic_waitfor(&aio);
	aio_handle_generic_checkerror(&aio);
	assert(aio.ah_type);
	assert(aio.ah_type->ht_retsize != NULL);
	result = (*aio.ah_type->ht_retsize)(&aio);
	return result;
}


/* Perform a USB control request.
 * This  causes a sequence  of at least 3  packets to be sent
 * out to  the  specified  endpoint, starting  with  a  token
 * command packet  containing the  given `request',  followed
 * by as many in/out data packets for interfacing with `buf',
 * and finally followed by a handshake packet
 * @param: buf: A buffer of `request->ur_length' bytes used for
 *              request input/output data.
 *              The flag `request->ur_reqtype & USB_REQUEST_RETYPE_DIR_D2H'
 *              determines the  direction in  which  data is  send  to/from
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
	token.ut_endp   = endp;

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
		data.ut_endp   = endp;
	}

	/* The terminating status packet. */
	status.ut_type   = data.ut_type | USB_TRANSFER_TYPE_FLAG_STATUS;
	status.ut_flags  = USB_TRANSFER_FLAG_NORMAL;
	status.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	status.ut_buflen = 0;
	status.ut_next   = NULL;
	status.ut_endp   = endp;

	usb_controller_transfer(self, &token, aio);
}

/* Same as `usb_controller_request()', but wait for the operation to complete.
 * Additionally,  return the  number of bytes  written to, or  read from `buf' */
PUBLIC NONNULL((1, 2, 3)) size_t KCALL
usb_controller_request_sync(struct usb_controller *__restrict self,
                            struct usb_endpoint *__restrict endp,
                            struct usb_request const *__restrict request,
                            void *buf) {
	size_t result;
	struct aio_handle_generic aio;
	aio_handle_generic_init(&aio);
	usb_controller_request(self, endp, request, buf, &aio);
	{
		RAII_FINALLY { aio_handle_generic_fini(&aio); };
		aio_handle_generic_waitfor(&aio);
		aio_handle_generic_checkerror(&aio);
		assert(aio.ah_type);
		assert(aio.ah_type->ht_retsize != NULL);
		result = (*aio.ah_type->ht_retsize)(&aio);
	}
	/* The return value must be larger than the request made, since
	 * the request didn't have the SHORT flag set, and therefor had
	 * to have been transferred in full. */
	assert(result >= sizeof(struct usb_request));
	result -= sizeof(struct usb_request);
	return result;
}

LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL usb_controller_isused)(struct usb_controller const *__restrict self,
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
	usb_controller_devs_write(self);

	/* Find an unused (and non-zero) address. */
	for (addr = 1; usb_controller_isused(self, addr); ++addr)
		;

	/* Make sure that the device can understand the address. */
	if unlikely(addr > 127) {
		usb_controller_devs_endwrite(self);
		THROW(E_IOERROR_NODATA,
		      E_IOERROR_SUBSYSTEM_USB,
		      E_IOERROR_REASON_USB_TOOMANY);
	}

	/* Remember the address, and link up the device in our chain. */
	dev->ud_dev   = addr;
	dev->ud_next  = self->uc_devs;
	self->uc_devs = (REF struct usb_device *)incref(dev);
	usb_controller_devs_endwrite(self);
}


/* Print the device string associated with `index' to the given `printer'.
 * If `index' is invalid, or the given `dev' didn't return a string,  then
 * return 0 without doing anything. */
PUBLIC ssize_t KCALL
usb_controller_printstring(struct usb_controller *__restrict self,
                           struct usb_device *__restrict dev, u8 index,
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
	if (!dev->ud_lang_used)
		return 0; /* No language string support. */
	req.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
	                 USB_REQUEST_RETYPE_TYPE_STD |
	                 USB_REQUEST_RETYPE_DIR_D2H;
	req.ur_request = USB_REQUEST_GET_DESCRIPTOR;
	req.ur_value   = USB_REQUEST_GET_DESCRIPTOR_VALUE_STRING | index;
	req.ur_index   = dev->ud_lang_used;
	req.ur_length  = 1;
	transfer_size = usb_controller_request_sync(self, dev, &req, buf);
	if (!transfer_size || buf[0] < 4)
		return 0; /* Empty string (just ignore it...) */
	/* Transfer the entire string. */
	req.ur_length = buf[0];
	transfer_size = usb_controller_request_sync(self, dev, &req, buf);
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
heap_printer(/*struct heap_printer_data **/ void *arg,
             /*utf-8*/ char const *__restrict data,
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
	memcpy(buf->ap_base + buf->ap_used, data,
	       datalen, sizeof(char));
	buf->ap_avail -= datalen;
	buf->ap_used  += datalen;
	return (ssize_t)datalen;
}

/* Helper wrapper for `usb_controller_printstring()'
 * This function returns a heap-allocated string, or NULL under the same
 * circumstances where `usb_controller_printstring()'  would return  `0' */
PUBLIC ATTR_MALLOC WUNUSED NONNULL((1, 2)) /*utf-8*/ char *KCALL
usb_controller_allocstring(struct usb_controller *__restrict self,
                           struct usb_device *__restrict dev, u8 index) {
	char *result;
	struct heap_printer_data data = { NULL, 0, 0 };
	TRY {
		usb_controller_printstring(self, dev, index,
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


PRIVATE ATTR_MALLOC WUNUSED struct usb_configuration_descriptor *KCALL
usb_controller_lookup_configuration(struct usb_controller *__restrict self,
                                    struct usb_device *__restrict dev,
                                    u8 confno) {
	struct usb_configuration_descriptor *result;
	struct {
		__uint8_t  uc_size;      /* Size of the descriptor (in bytes) */
		__uint8_t  uc_type;      /* Descriptor type (== `(USB_REQUEST_GET_DESCRIPTOR_VALUE_CONFIGURATION & 0xff00) >> 8') */
		__uint16_t uc_total_len; /* Total length of the descriptor (including trailing data) */
	} header;
	size_t transfer_size;
	struct usb_request req;

	/* Request the configuration header. */
	req.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
	                 USB_REQUEST_RETYPE_TYPE_STD |
	                 USB_REQUEST_RETYPE_DIR_D2H;
	req.ur_request = USB_REQUEST_GET_DESCRIPTOR;
	req.ur_value   = USB_REQUEST_GET_DESCRIPTOR_VALUE_CONFIGURATION | confno;
	req.ur_index   = 0;
	req.ur_length  = sizeof(header);
	transfer_size  = usb_controller_request_sync(self, dev, &req, &header);
	if unlikely(header.uc_type != ((USB_REQUEST_GET_DESCRIPTOR_VALUE_CONFIGURATION & 0xff00) >> 8)) {
		/* Not actually a configuration */
badtype:
		printk(KERN_WARNING "[usb] configuration descriptor #%I8u has incorrect type (%q:%q:%q)\n",
		       confno, dev->ud_str_vendor, dev->ud_str_product, dev->ud_str_serial);
		return NULL;
	}
	if unlikely(transfer_size < sizeof(header) ||
	            header.uc_total_len < header.uc_size ||
	            header.uc_size < offsetafter(struct usb_configuration_descriptor, uc_conf_value)) {
badconf:
		/* Invalid configuration constraints. */
		printk(KERN_WARNING "[usb] Invalid configuration descriptor #%I8u (%q:%q:%q)\n",
		       confno, dev->ud_str_vendor, dev->ud_str_product, dev->ud_str_serial);
		return NULL;
	}
	result = (struct usb_configuration_descriptor *)kmalloc(header.uc_total_len,
	                                                        GFP_NORMAL | GFP_PREFLT);
	TRY {
		/* Read the remainder of the configuration. */
		req.ur_length = header.uc_total_len;
		transfer_size = usb_controller_request_sync(self, dev, &req, result);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	/* Re-validate data read from the device. */
	if unlikely(result->uc_type != ((USB_REQUEST_GET_DESCRIPTOR_VALUE_CONFIGURATION & 0xff00) >> 8)) {
		/* Not actually a configuration */
		kfree(result);
		goto badtype;
	}
	/* Constrain returned fields by the actual amount of transferred data. */
	if unlikely((size_t)result->uc_total_len > transfer_size)
		result->uc_total_len = (u16)transfer_size;
	if unlikely(result->uc_total_len > header.uc_total_len)
		result->uc_total_len = header.uc_total_len;
	if unlikely(transfer_size < sizeof(header) ||
	            result->uc_total_len < result->uc_size ||
	            result->uc_size < offsetafter(struct usb_configuration_descriptor, uc_conf_value)) {
		kfree(result);
		goto badconf;
	}
	assert(result->uc_total_len <= header.uc_total_len);
	if unlikely(result->uc_total_len < header.uc_total_len) {
		struct usb_configuration_descriptor *new_result;
		new_result = (struct usb_configuration_descriptor *)krealloc_nx(result,
		                                                                result->uc_total_len,
		                                                                GFP_NORMAL);
		if likely(new_result)
			result = new_result;
	}
	return result;
}

PRIVATE void
NOTHROW(FCALL sleep_milli)(unsigned int n) {
	ktime_t then = ktime();
	then += relktime_from_milliseconds(n);
	task_sleep_until(then);
}



/* Function called when a new USB endpoint is discovered.
 * NOTE: This  function also releases a lock to `self->uc_disclock'
 *       once the device has been assigned an address. In the event
 *       that an exception occurs before then, this lock will  also
 *       be  released, meaning that this function _always_ releases
 *       such a lock.
 * @param: endpoint_flags: Set of `USB_ENDPOINT_FLAG_*' */
PUBLIC void KCALL
usb_device_discovered(struct usb_controller *__restrict self,
                      u32 endpoint_flags) {
	REF struct usb_device *dev;
	struct usb_request req;
	struct usb_device_descriptor desc;
	size_t transfer_size;
	alignas(2) byte_t buf[256];
	u8 used_conf;
	u16 device_max_packet_size;
	assert((endpoint_flags & ~USB_ENDPOINT_MASK_SPEED) == 0);
	{
		/* Always  release  the  device-discover-lock  as
		 * soon as we've assigned the device its address. */
		RAII_FINALLY { usb_controller_disclock_release(self); };

		/* Create a descriptor for the device. */
		dev = (REF struct usb_device *)kmalloc(sizeof(struct usb_device),
		                                       GFP_NORMAL | GFP_CALLOC);
		dev->ue_refcnt    = 1;
		dev->ue_interface = dev;
		dev->ui_device    = dev;
		dev->ue_maxpck    = 0x7ff; /* Not configured. (Physical limit of the protocol) */
//		dev->ue_dev       = 0;     /* Not configured. (Gets set by `usb_device_discovered()') */
//		dev->ue_endp      = 0;     /* Configure channel. */
		dev->ue_flags     = endpoint_flags;
		TRY {
			req.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
			                 USB_REQUEST_RETYPE_TYPE_STD |
			                 USB_REQUEST_RETYPE_DIR_D2H;
			req.ur_request = USB_REQUEST_GET_DESCRIPTOR;
			req.ur_value   = USB_REQUEST_GET_DESCRIPTOR_VALUE_DEVICE;
			req.ur_index   = 0;
			/* NOTE: offsetafter(struct usb_device_descriptor, ud_maxpacketsize) == 8,
			 *       which  is  the  minimum  packet  size  supported  by  all devices */
			req.ur_length = offsetafter(struct usb_device_descriptor, ud_maxpacketsize);
			transfer_size = usb_controller_request_sync(self, dev, &req, &desc);

			/* Remember the max packet size supported by the device. */
			device_max_packet_size = dev->ue_maxpck;
			if likely(transfer_size >= offsetafter(struct usb_device_descriptor, ud_maxpacketsize) &&
			          desc.ud_type == (USB_REQUEST_GET_DESCRIPTOR_VALUE_DEVICE & 0xff00) >> 8)
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
		} EXCEPT {
			decref_unlikely(dev);
			RETHROW();
		}
	} /* FINALLY {
		usb_controller_disclock_release(self);
	} */

	/* Cleanup our initial reference to the device once this function returns. */
	FINALLY_DECREF_UNLIKELY(dev);

	/* With the address assigned to the device, from now on make use of
	 * that address for the purposes of communications with the  device */
	dev->ue_dev = dev->ud_dev;

	/* Allow the  device to  transition to  the addressable  state.
	 * The specs state that we should wait 2 milliseconds for this. */
	sleep_milli(2);

	/* Check if we got less data than expected during the initial
	 * `USB_REQUEST_GET_DESCRIPTOR'  call above. If so, then this
	 * is considered to be a ~strange~ device. */
	if unlikely(transfer_size < offsetafter(struct usb_device_descriptor, ud_maxpacketsize) ||
	            desc.ud_type != (USB_REQUEST_GET_DESCRIPTOR_VALUE_DEVICE & 0xff00) >> 8)
		goto strange_device;

	/* Load the remainder of the device's descriptor. */
	req.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
	                 USB_REQUEST_RETYPE_TYPE_STD |
	                 USB_REQUEST_RETYPE_DIR_D2H;
	req.ur_request = USB_REQUEST_GET_DESCRIPTOR;
	req.ur_value   = USB_REQUEST_GET_DESCRIPTOR_VALUE_DEVICE;
	req.ur_index   = 0;
	req.ur_length  = MIN(desc.ud_size, sizeof(desc));
	transfer_size  = usb_controller_request_sync(self, dev, &req, &desc);
	if unlikely(transfer_size < sizeof(desc))
		bzero((byte_t *)&desc + transfer_size, sizeof(desc) - transfer_size);

	/* Store the identification bits within the device structure. */
	dev->ud_dev_class    = desc.ud_dev_class;
	dev->ud_dev_subclass = desc.ud_dev_subclass;
	dev->ud_dev_protocol = desc.ud_dev_protocol;

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
			size_t count = (buf[0] - 2) / 2;
			dev->ud_lang_used = *(u16 const *)(buf + 2);
#define LANG_EN_US 0x0409
			/* Try to make use of English (if available) */
			if (count > 1 && dev->ud_lang_used != LANG_EN_US) {
				size_t i;
				for (i = 1; i < count; ++i) {
					u16 l = ((u16 *)(buf + 2))[i];
					if (l == LANG_EN_US) {
						dev->ud_lang_used = LANG_EN_US;
						break;
					}
				}
			}
		}
		if (dev->ud_lang_used != 0) {
			/* Load device strings. */
			dev->ud_str_vendor  = usb_controller_allocstring(self, dev, desc.ud_str_vendor);
			dev->ud_str_product = usb_controller_allocstring(self, dev, desc.ud_str_product);
			dev->ud_str_serial  = usb_controller_allocstring(self, dev, desc.ud_str_serial);
		}
	}

	/* Protect against weird devices with more than 16 configurations.
	 * The USB protocol makes it impossible to query information about
	 * more than 16 possible configurations! */
	if unlikely(desc.ud_confcount > 16) {
		printk(KERN_WARNING "[usb] Device supports more than 16 (%I8u) configurations (%q:%q:%q)\n",
		       desc.ud_confcount, dev->ud_str_vendor, dev->ud_str_product, dev->ud_str_serial);
		desc.ud_confcount = 16;
	}

	/* The USB specs mandate that any device has at least one configuration.
	 * And I'm inclined to share that opinion, so anything that doesn't have
	 * at least one configuration is considered a ~strange~ device. */
	if unlikely(!desc.ud_confcount) {
strange_device_without_configs:
		printk(KERN_WARNING "[usb] Device %q:%q:%q doesn't seem to have any valid configurations\n",
		       dev->ud_str_vendor, dev->ud_str_product, dev->ud_str_serial);
		goto strange_device;
	}

	/* Gather available device configurations */
	{
		u8 i, j;
		/* Must set the max config count beforehand, so that `usb_endpoint_destroy()'
		 * can  easily  clean  up   successfully  loaded  configurations  on   error. */
		dev->ud_configc = desc.ud_confcount;
		for (i = j = 0; i < desc.ud_confcount; ++i) {
			struct usb_configuration_descriptor *conf;
			/* Load the configuration itself. */
			conf = usb_controller_lookup_configuration(self, dev, i);
			if unlikely(!conf)
				continue;
			dev->ud_configv[j].uc_config = conf;
			/* Load the configuration description. */
			if (conf->uc_size >= offsetafter(struct usb_configuration_descriptor, uc_conf_name))
				dev->ud_configv[j].uc_desc = usb_controller_allocstring(self, dev, conf->uc_conf_name);
			++j;
		}
		dev->ud_configc = j;
		/* Same as above: We need at least 1 valid configuration. */
		if unlikely(!j)
			goto strange_device_without_configs;
	}

	used_conf = 0;
	/* Handle multi-purpose devices (e.g. a printer/scanner combo). */
	if (dev->ud_configc != 1) {
		/* A device class of 0 indicates that the device's different classes operate independently. */
		if (dev->ud_dev_class != 0) {
			size_t i;
			REF struct usb_probe_vector *probes;
			probes = arref_get(&probe_device);
			FINALLY_DECREF_UNLIKELY(probes);
			/* Pass the device as a whole to loaded drivers and see if they can
			 * identify what's the deal with  it, and select the  configuration
			 * for us. */
			for (i = 0; i < probes->upv_count; ++i) {
				DBG_memset(&dev->ud_config, 0xcc, sizeof(dev->ud_config));
				if ((*probes->upv_elem[i].c_device)(self, dev)) {
#ifndef NDEBUG
					do  {
						unsigned int j;
						for (j = 0; j < dev->ud_configc; ++j) {
							if (dev->ud_config == &dev->ud_configv[j])
								goto did_find_correct_config;
						}
					} while (__assertion_checkf("dev->ud_config in dev->ud_configv",
					                            "Device config %p is not a valid configuration",
					                            dev->ud_config));
did_find_correct_config:
#endif /* !NDEBUG */
					goto done;
				}
			}
		}
		/* XXX: Change the API to allow for simultaneous use of multi-function
		 *      USB devices, by  switching between configurations  on-the-fly? */
		used_conf = 0; /* ??? (Maybe prioritize certain options over others?) */
		printk(KERN_WARNING "[usb] Multi-function device %q:%q:%q not "
		                    "recognized. Available configurations are:\n",
		       dev->ud_str_vendor, dev->ud_str_product, dev->ud_str_serial);
		{
			u8 i;
			for (i = 0; i < dev->ud_configc; ++i) {
				printk(KERN_WARNING "[usb] Config#%u: %q\n",
				       i, dev->ud_configv[i].uc_desc);
			}
		}
		printk(KERN_WARNING "[usb] Configuring as %q\n",
		       dev->ud_configv[used_conf].uc_desc);
	}
	req.ur_reqtype = USB_REQUEST_RETYPE_DEST_DEV |
	                 USB_REQUEST_RETYPE_TYPE_STD |
	                 USB_REQUEST_RETYPE_DIR_H2D;
	req.ur_request = USB_REQUEST_SET_CONFIGURATION;
	req.ur_value   = dev->ud_configv[used_conf].uc_config->uc_conf_value;
	req.ur_index   = 0;
	req.ur_length  = 0;
	dev->ud_config = &dev->ud_configv[used_conf];
	printk(KERN_NOTICE "[usb] Set configuration for %q:%q:%q to %q (conf#%I8u)\n",
	       dev->ud_str_vendor, dev->ud_str_product, dev->ud_str_serial,
	       dev->ud_config->uc_desc, used_conf);
	usb_controller_request_sync(self, dev, &req, NULL);

	/* Create  endpoints  for  every  interface:endpoint  pair  that  we  can find
	 * within  the selected  configuration. Then,  pass those  endpoints to loaded
	 * drivers  in  order   to  try   and  figure  out   an  appropriate   driver.
	 * And if that doesn't work, just turn all of them into strange USB endpoints. */
	{
		size_t interface_count = 0;
		byte_t *iter, *end;
		struct usb_configuration_descriptor *config;
		u16 used_endpoints = 1;
		bool allow_alternates = false;
		bool has_alternates = false;
		config = dev->ud_config->uc_config;
again_scanconfig:
		iter = (byte_t *)config + config->uc_size;
		end  = (byte_t *)config + config->uc_total_len;
		while (iter + 2 < end) {
			u8 size, type;
			size = iter[0];
			type = iter[1];
			if unlikely(size < 2)
				break;
			if unlikely((size_t)size > (size_t)(end - iter)) {
				size = (u8)(size_t)(end - iter);
				iter[0] = size;
			}
			if (type == ((USB_REQUEST_GET_DESCRIPTOR_VALUE_INTERFACE & 0xff00) >> 8) &&
			    size >= offsetafter(struct usb_interface_descriptor, ui_intf_protocol)) {
				REF struct usb_endpoint *interface_endpts[16];
				REF struct usb_interface *intf;
				struct usb_interface_descriptor *intf_desc;
				size_t interface_endpoint_count = 0;
				intf_desc = (struct usb_interface_descriptor *)iter;
				if (intf_desc->ui_alt_setting != 0) {
					has_alternates = true;
					if (!allow_alternates)
						goto search_for_next_intf;
				}
				intf = (REF struct usb_interface *)kmalloc(sizeof(struct usb_interface), GFP_NORMAL);
				intf->ue_refcnt    = 1;
				intf->ue_interface = intf;
				intf->ue_maxpck    = dev->ue_maxpck;
				intf->ue_dev       = dev->ue_dev;
				intf->ue_endp      = 0; /* Interface descriptors always refer to endpoint 0 */
				intf->ue_flags     = dev->ue_flags & ~(USB_ENDPOINT_FLAG_DATATOGGLE);
				intf->ue_endp_desc = NULL;
				intf->ui_device    = (REF struct usb_device *)incref(dev);
				intf->ui_intf      = intf_desc->ui_intf;
				intf->ui_intf_desc = intf_desc;
				intf->ui_intf_name = NULL;
				FINALLY_DECREF_UNLIKELY(intf);
				/* Load the name of the interface. */
				if (size >= offsetafter(struct usb_interface_descriptor, ui_intf_str))
					intf->ui_intf_name = usb_controller_allocstring(self, dev, intf_desc->ui_intf_str);

				TRY {
					/* Search for endpoints associated with this interface. */
					iter += size;
					while (iter + 2 < end) {
						size = iter[0];
						type = iter[1];
						if unlikely(size < 2)
							break;
						if unlikely((size_t)size > (size_t)(end - iter)) {
							size = (u8)(size_t)(end - iter);
							iter[0] = size;
						}
						if (type == ((USB_REQUEST_GET_DESCRIPTOR_VALUE_ENDPOINT & 0xff00) >> 8) &&
						    size >= offsetafter(struct usb_endpoint_descriptor, ue_addr)) {
							REF struct usb_endpoint *endp;
							struct usb_endpoint_descriptor *endp_desc;
							u16 addr_mask;
							endp_desc = (struct usb_endpoint_descriptor *)iter;
							/* Ignore descriptors for endpoint #0 (that one's always just the control endpoint) */
							if ((endp_desc->ue_addr & USB_ENDPOINT_ADDR_INDEX) == 0)
								goto search_for_next_endp;
							addr_mask = (u16)1 << (endp_desc->ue_addr & USB_ENDPOINT_ADDR_INDEX);
							if unlikely(used_endpoints & addr_mask) {
								printk(KERN_WARNING "[usb] Endpoint %u of interface %q on device %q:%q:%q "
								                    "is already in use and cannot be bound more than once\n",
								       endp_desc->ue_addr & USB_ENDPOINT_ADDR_INDEX, intf->ui_intf_name,
								       dev->ud_str_vendor, dev->ud_str_product, dev->ud_str_serial);
								goto search_for_next_endp;
							}
							used_endpoints |= addr_mask;
							endp = (REF struct usb_endpoint *)kmalloc(sizeof(struct usb_endpoint), GFP_NORMAL);
							endp->ue_refcnt    = 1;
							endp->ue_interface = (REF struct usb_interface *)incref(intf);
							endp->ue_maxpck    = device_max_packet_size;
							if likely(size >= offsetafter(struct usb_endpoint_descriptor, ue_maxpacketsize)) {
								endp->ue_maxpck = endp_desc->ue_maxpacketsize;
							} else {
								/* Don't run any risks, and use the size limit from the control  channel.
								 * However, for properly functioning devices, we shouldn't even get here. */
								endp->ue_maxpck = intf->ue_maxpck;
							}
							endp->ue_dev   = intf->ue_dev;
							endp->ue_endp  = endp_desc->ue_addr & USB_ENDPOINT_ADDR_INDEX;
							endp->ue_flags = dev->ue_flags & USB_ENDPOINT_FLAG_LOWSPEED;
							if (endp_desc->ue_addr & USB_ENDPOINT_ADDR_IN)
								endp->ue_flags |= USB_ENDPOINT_FLAG_INPUT;
							endp->ue_endp_desc = endp_desc;
							assert(interface_endpoint_count < 16);
							interface_endpts[interface_endpoint_count] = endp; /* Inherit reference */
							++interface_endpoint_count;
						}
search_for_next_endp:
						iter += size;
					}
					if unlikely(interface_endpoint_count == 0) {
						/* Interface without any endpoints (shouldn't happen... I think?) */
						printk(KERN_WARNING "[usb] Interface %q of device %q:%q:%q configured "
						                    "with %q doesn't seem to have any endpoints\n",
						       intf->ui_intf_name, dev->ud_str_vendor, dev->ud_str_product,
						       dev->ud_str_serial, dev->ud_config->uc_desc);
					}
					/* Notify  the system of the discovery of this
					 * interface, as well as associated endpoints. */
					usb_interface_discovered(self, intf,
					                         interface_endpoint_count,
					                         interface_endpts);
					++interface_count;
				} EXCEPT {
					while (interface_endpoint_count) {
						--interface_endpoint_count;
						decref(interface_endpts[interface_endpoint_count]);
					}
					RETHROW();
				}
				while (interface_endpoint_count) {
					--interface_endpoint_count;
					decref(interface_endpts[interface_endpoint_count]);
				}
				if (iter + 2 >= end)
					break;
			}
search_for_next_intf:
			iter += size;
		}
		if (!allow_alternates && has_alternates && used_endpoints != (u16)-1) {
			/* Do a second scan where we  */
			allow_alternates = true;
			goto again_scanconfig;
		}

		/* If we didn't manage to find any interface, then just consider
		 * this to be a strange device altogether.
		 * Note that this has nothing to do with us not finding a  driver
		 * for the endpoint, but just not being able to figure out what's
		 * the deal with the thing. */
		if unlikely(!interface_count) {
			printk(KERN_WARNING "[usb] Device %q:%q:%q doesn't seem to have "
			                    "any interfaces when configured for %q\n",
			       dev->ud_str_vendor, dev->ud_str_product, dev->ud_str_serial,
			       dev->ud_config->uc_desc);
			goto strange_device;
		}
	}
done:
	return;
strange_device:
	/* Register the device  as a  generic character  device,
	 * but don't pass the device for the purpose of endpoint
	 * detection to loaded drivers. */
	dev->ue_flags |= USB_ENDPOINT_FLAG_STRANGE;
	usb_create_strange_device(self, dev);
}


/* Register mappings between USB devices and device files, such that
 * the  USB system can attempt to unregister and remove device files
 * bound to some USB device when it is detected that the usb  device
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
 * Note that it is  possible to register any  number of devices for  any
 * single  given USB device,  however it is not  possible to delete such
 * a registration, other than physically removing the associated device.
 */
PUBLIC NONNULL((1, 2)) void KCALL
usb_register_device(struct usb_device *__restrict usb_dev,
                    struct device *__restrict dev)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	/* TODO */
	(void)usb_dev;
	(void)dev;
}


/* Destroy the given USB interrupt descriptor. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL usb_interrupt_destroy)(struct usb_interrupt *__restrict self) {
	assert(self->ui_fini);
	(*self->ui_fini)(self);
	decref_unlikely(self->ui_endp);
	kfree(self);
}



DECL_END

#endif /* !GUARD_MODUSB_USB_C */
