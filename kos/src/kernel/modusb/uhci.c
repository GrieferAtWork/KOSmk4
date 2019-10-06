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
#ifndef GUARD_MODUSB_UHCI_C
#define GUARD_MODUSB_UHCI_C 1
#define CONFIG_BUILDING_MODUSB 1
#define _KOS_SOURCE 1

#include "uhci.h"

#include <kernel/compiler.h>

#include <drivers/pci.h>
#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/interrupt.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <sched/cpu.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/except-io.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "usb.h"

DECL_BEGIN

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x


#undef CONFIG_UHCI_USE_QH_LOOPS
#if 1 /* Have the QH chain loop back on itself. */
#define CONFIG_UHCI_USE_QH_LOOPS 1
#endif

PRIVATE DEFINE_ATOMIC_RWLOCK(ostd_free_lock);
PRIVATE DEFINE_ATOMIC_RWLOCK(osqh_free_lock);
PRIVATE struct uhci_ostd *ostd_free = NULL;
PRIVATE struct uhci_osqh *osqh_free = NULL;

PUBLIC WUNUSED ATTR_RETNONNULL ATTR_MALLOC struct uhci_ostd *FCALL
uhci_ostd_alloc(void) THROWS(E_BADALLOC, E_WOULDBLOCK) {
	struct uhci_ostd *result;
	sync_write(&ostd_free_lock);
again_read:
	result = ATOMIC_READ(ostd_free);
	if (result) {
		if (!ATOMIC_CMPXCH_WEAK(ostd_free, result, result->td_next))
			goto again_read;
		sync_endwrite(&ostd_free_lock);
	} else {
		sync_endwrite(&ostd_free_lock);
		result = (struct uhci_ostd *)kmemalign(UHCI_FLE_ALIGN,
		                                       sizeof(struct uhci_ostd),
		                                       GFP_LOCKED | GFP_PREFLT);
		result->td_self = (u32)pagedir_translate((vm_virt_t)result);
	}
	assert(IS_ALIGNED((uintptr_t)result, UHCI_FLE_ALIGN));
	assert(result->td_self == (u32)pagedir_translate((vm_virt_t)result));
	return result;
}

PUBLIC WUNUSED ATTR_RETNONNULL ATTR_MALLOC struct uhci_osqh *FCALL
uhci_osqh_alloc(void) THROWS(E_BADALLOC, E_WOULDBLOCK) {
	struct uhci_osqh *result;
	sync_write(&osqh_free_lock);
again_read:
	result = ATOMIC_READ(osqh_free);
	if (result) {
		if (!ATOMIC_CMPXCH_WEAK(osqh_free, result, result->qh_next))
			goto again_read;
		sync_endwrite(&osqh_free_lock);
	} else {
		sync_endwrite(&osqh_free_lock);
		result = (struct uhci_osqh *)kmemalign(UHCI_FLE_ALIGN,
		                                       sizeof(struct uhci_osqh),
		                                       GFP_LOCKED | GFP_PREFLT);
		result->qh_self = (u32)pagedir_translate((vm_virt_t)result);
	}
	assert(IS_ALIGNED((uintptr_t)result, UHCI_FLE_ALIGN));
	assert(result->qh_self == (u32)pagedir_translate((vm_virt_t)result));
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL uhci_ostd_free)(struct uhci_ostd *__restrict self) {
	struct uhci_ostd *next;
	assert(self);
	assert(IS_ALIGNED((uintptr_t)self, UHCI_FLE_ALIGN));
	do {
		next = ATOMIC_READ(ostd_free);
		self->td_next = next;
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(ostd_free, next, self));
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL uhci_osqh_free)(struct uhci_osqh *__restrict self) {
	struct uhci_osqh *next;
	assert(self);
	assert(IS_ALIGNED((uintptr_t)self, UHCI_FLE_ALIGN));
	do {
		next = ATOMIC_READ(osqh_free);
		self->qh_next = next;
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(osqh_free, next, self));
}

PRIVATE WUNUSED struct uhci_ostd *
NOTHROW(FCALL uhci_ostd_findphys)(struct uhci_ostd *chain, u32 phys_addr) {
	assert(IS_ALIGNED(phys_addr, UHCI_FLE_ALIGN));
	for (; chain; chain = chain->td_next) {
		assert(IS_ALIGNED(chain->td_self, UHCI_FLE_ALIGN));
		if (chain->td_self == phys_addr)
			break; /* Found it! */
	}
	return chain;
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL uhci_osqh_destroy)(struct uhci_osqh *__restrict self) {
	struct uhci_ostd *iter, *next;
	iter = self->qh_tds;
	while (iter) {
		next = iter->td_next;
		uhci_ostd_free(iter);
		iter = next;
	}
	uhci_osqh_free(self);
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL uhci_aio_cancel)(struct aio_handle *__restrict self);

PRIVATE struct aio_handle_type uhci_aio_type = {
	/* .ht_cancel = */ &uhci_aio_cancel
};


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL uhci_aio_cancel)(struct aio_handle *__restrict self) {
	struct uhci_aio_data *data;
	data = (struct uhci_aio_data *)self->ah_data;
	if (ATOMIC_FETCHOR(data->ud_flags, UHCI_AIO_FSERVED) & UHCI_AIO_FSERVED)
		return; /* Already served. */
	/* TODO */
	decref_unlikely(data->ud_ctrl);
	decref(data->ud_osqh);
}


PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_osqh_aio_docomplete)(struct aio_handle *__restrict aio,
                                        unsigned int status) {
	struct uhci_aio_data *data;
	data = (struct uhci_aio_data *)aio->ah_data;
	if (!(ATOMIC_FETCHOR(data->ud_flags, UHCI_AIO_FSERVED) & UHCI_AIO_FSERVED)) {
		if (data->ud_flags & UHCI_AIO_FONEDMA) {
			vm_dmalock_release(&data->ud_dmalock);
		} else if (data->ud_dmalockvec) {
			struct vm_dmalock *iter;
			for (iter = data->ud_dmalockvec; iter->dl_part; ++iter)
				vm_dmalock_release(iter);
			kfree(data->ud_dmalockvec);
		}
		decref_unlikely(data->ud_ctrl);
		decref_unlikely(data->ud_osqh);
		(*aio->ah_func)(aio, status);
	}
}


PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_osqh_aio_completed)(struct uhci_controller *__restrict self,
                                       struct uhci_osqh *__restrict osqh,
                                       struct aio_handle *__restrict aio) {
	struct uhci_ostd *td;
	/* Check for transfer errors. */
	for (td = osqh->qh_tds; td; td = td->td_next) {
		u32 cs = td->td_cs;
		printk(KERN_DEBUG "[uhci] td:complete [cs=%#I32x,tok=%#I32x]\n", cs, td->td_tok);
		if ((cs & (UHCI_TDCS_CRCTMO | UHCI_TDCS_NAKR |
		           UHCI_TDCS_BABBLE | UHCI_TDCS_DBE |
		           UHCI_TDCS_STALL | UHCI_TDCS_ACTIVE)) != 0) {
			struct exception_data odata;
			struct exception_data *mydat;
			mydat = error_data();
			odata = *mydat;
			memset(mydat, 0, sizeof(*mydat));
			mydat->e_code = ERROR_CODEOF(E_IOERROR_ERRORBIT);
			mydat->e_pointers[0] = E_IOERROR_REASON_UHCI_TDCS;
			mydat->e_pointers[1] = E_IOERROR_SUBSYSTEM_USB;
			mydat->e_pointers[2] = cs;
			uhci_osqh_aio_docomplete(aio, AIO_COMPLETION_FAILURE);
			*mydat = odata;
			return;
		}
	}
	uhci_osqh_aio_docomplete(aio, AIO_COMPLETION_SUCCESS);
}

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_osqh_completed)(struct uhci_controller *__restrict self,
                                   REF struct uhci_osqh *__restrict osqh) {
	struct aio_handle *aio;
	/* QH was completed. -> Try to signal the connected AIO receiver. */
	aio = ATOMIC_XCH(osqh->qh_aio, NULL);
	if likely(aio != NULL)
		uhci_osqh_aio_completed(self, osqh, aio);
	decref(osqh);
}

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_osqh_completed_badep)(struct uhci_controller *__restrict self,
                                         REF struct uhci_osqh *__restrict osqh,
                                         u32 ep) {
	struct aio_handle *aio;
	/* QH was completed. -> Try to signal the connected AIO receiver. */
	aio = ATOMIC_XCH(osqh->qh_aio, NULL);
	if likely(aio != NULL) {
		struct exception_data odata;
		struct exception_data *mydat;
		mydat = error_data();
		odata = *mydat;
		memset(mydat, 0, sizeof(*mydat));
		mydat->e_code = ERROR_CODEOF(E_IOERROR_NODATA);
		mydat->e_pointers[0] = E_IOERROR_REASON_UHCI_BADEP;
		mydat->e_pointers[1] = E_IOERROR_SUBSYSTEM_USB;
		mydat->e_pointers[2] = ep;
		uhci_osqh_aio_docomplete(aio, AIO_COMPLETION_FAILURE);
		*mydat = odata;
	}
	decref(osqh);
}


PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_invcache)(struct uhci_controller *__restrict self,
                             u32 phys_addr) {
	/* XXX: Tell the UHCI controller to invalidate 4 bytes of physical memory at `phys_addr'? */
}

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_osqh_unlink)(struct uhci_controller *__restrict self,
                                struct uhci_osqh *__restrict entry,
                                struct uhci_osqh **__restrict pentry) {
	struct uhci_osqh *prev, *next;
	prev = container_of(pentry, struct uhci_osqh, qh_next);
	next = entry->qh_next;
	prev->qh_next = next;
#ifdef CONFIG_UHCI_USE_QH_LOOPS
	if (!next && prev != &self->uc_qhstart)
		next = self->uc_qhstart.qh_next;
#endif /* CONFIG_UHCI_USE_QH_LOOPS */
	prev->qh_hp = next ? next->qh_self | UHCI_QHHP_QHTD
	                   : UHCI_QHHP_TERM;
	uhci_invcache(self, prev->qh_self + offsetof(struct uhci_osqh, qh_hp));
}

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_finish_completed)(struct uhci_controller *__restrict self) {
	struct uhci_osqh **piter, *iter;
	assert(sync_writing(&self->uc_lock));
	piter = &self->uc_qhstart.qh_next;
	while ((iter = *piter) != NULL) {
		struct uhci_ostd *tds;
		u32 ep;
		ep = ATOMIC_READ(iter->qh_ep);
		printk(KERN_DEBUG "ep = %#I32x\n", ep);
		if (ep & UHCI_QHEP_TERM) {
			/* This queue has completed */
			uhci_osqh_unlink(self, iter, piter);
			uhci_osqh_completed(self, iter);
			continue;
		}
		/* Find the TD that is currently being executed. */
		tds = uhci_ostd_findphys(iter->qh_tds, ep);
		if unlikely(!tds) {
			/* Shouldn't happen... */
			uhci_osqh_unlink(self, iter, piter);
			uhci_osqh_completed_badep(self, iter, ep);
			continue;
		}
		/* In the case of depth-first, we can assume that there are no
		 * more completed queues to be found, since that would imply that
		 * our current queue would have also been completed! */
		if (tds->td_lp & UHCI_TDLP_DBS)
			break; /* Depth-first -> Later QHs havn't been touched, yet */
		piter = &iter->qh_next;
	}
}


/* Safely release a read/write lock on `self->uc_lock' */
PUBLIC NOBLOCK void
NOTHROW(FCALL uhci_controller_endwrite)(struct uhci_controller *__restrict self) {
again:
	assert(sync_writing(&self->uc_lock));
	if (ATOMIC_READ(self->uc_flags) & UHCI_CONTROLLER_FLAG_INTERRUPTED) {
		if (ATOMIC_FETCHAND(self->uc_flags, ~UHCI_CONTROLLER_FLAG_INTERRUPTED) &
		    UHCI_CONTROLLER_FLAG_INTERRUPTED)
			uhci_finish_completed(self);
	}
	sync_endwrite(&self->uc_lock);
	/* Do the interlocked check. */
	if (ATOMIC_READ(self->uc_flags) & UHCI_CONTROLLER_FLAG_INTERRUPTED) {
		if (sync_trywrite(&self->uc_lock))
			goto again;
	}
}
PUBLIC NOBLOCK void
NOTHROW(FCALL uhci_controller_endread)(struct uhci_controller *__restrict self) {
	assert(sync_reading(&self->uc_lock));
	if (ATOMIC_READ(self->uc_flags) & UHCI_CONTROLLER_FLAG_INTERRUPTED) {
		if (sync_tryupgrade(&self->uc_lock)) {
do_end_write:
			uhci_controller_endwrite(self);
			return;
		}
		sync_endread(&self->uc_lock);
		goto do_try_write;
	} else {
		sync_endread(&self->uc_lock);
		if (ATOMIC_READ(self->uc_flags) & UHCI_CONTROLLER_FLAG_INTERRUPTED) {
do_try_write:
			if (sync_trywrite(&self->uc_lock))
				goto do_end_write;
		}
	}
}


PRIVATE NOBLOCK bool
NOTHROW(FCALL uhci_controller_isstopped)(struct uhci_controller *__restrict self) {
	return (uhci_rdw(self, UHCI_USBSTS) & UHCI_USBSTS_HCH) != 0;
}

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_controller_stop)(struct uhci_controller *__restrict self) {
	u16 cmd;
	cmd = uhci_rdw(self, UHCI_USBCMD);
	cmd &= ~UHCI_USBCMD_RS;
	uhci_wrw(self, UHCI_USBCMD, cmd);
	while (!uhci_controller_isstopped(self))
		task_pause();
}

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_controller_resume)(struct uhci_controller *__restrict self) {
	u16 cmd;
	cmd = uhci_rdw(self, UHCI_USBCMD);
	cmd |= UHCI_USBCMD_RS;
	uhci_wrw(self, UHCI_USBCMD, cmd);
}


PRIVATE NOBLOCK bool
NOTHROW(FCALL uhci_interrupt)(void *arg) {
	u16 status;
	struct uhci_controller *self;
	self = (struct uhci_controller *)arg;
	status = uhci_rdw(self, UHCI_USBSTS);
	if (!(status & (UHCI_USBSTS_USBINT | UHCI_USBSTS_ERROR))) {
		printk(KERN_TRACE "[usb][pci:%I32p,io:%#Ix] uhci sporadic (status=%#I8x)\n",
		       self->uc_pci->pd_base, self->uc_base.uc_mmbase, status);
		return false; /* Not our interrupt! */
	}
	uhci_wrw(self, UHCI_USBSTS, status);
	printk(KERN_TRACE "[usb][pci:%I32p,io:%#Ix] uhci interrupt (status=%#I8x)\n",
	       self->uc_pci->pd_base, self->uc_base.uc_mmbase, status);
	if unlikely(status & UHCI_USBSTS_HSE) {
		printk(KERN_CRIT "[usb][pci:%I32p,io:%#Ix] uhci:Host-System-Error set (status=%#I8x)\n",
		       self->uc_pci->pd_base, self->uc_base.uc_mmbase, status);
	}
	if unlikely(status & UHCI_USBSTS_HCPE) {
		printk(KERN_CRIT "[usb][pci:%I32p,io:%#Ix] uhci:Host-Controller-Process-Error set (status=%#I8x)\n",
		       self->uc_pci->pd_base, self->uc_base.uc_mmbase, status);
	}
	if (status & UHCI_USBSTS_HCH)
		return true; /* Halted */
	if (status & UHCI_USBSTS_USBINT) {
		/* One of two things happened:
		 *  - A TD with the IOC bit was finished
		 *  - Some TD got one of its error bits set. */
		uhci_controller_stop(self);

		if (!sync_trywrite(&self->uc_lock)) {
			/* Whoever is holding the lock must handle this interrupt, then... */
			ATOMIC_FETCHOR(self->uc_flags, UHCI_CONTROLLER_FLAG_INTERRUPTED);
			/* Try to acquire the lock again, so the `UHCI_CONTROLLER_FLAG_INTERRUPTED'
			 * flag becomes interlocked on our end. */
			if (!sync_trywrite(&self->uc_lock))
				goto done;
			ATOMIC_FETCHAND(self->uc_flags, ~UHCI_CONTROLLER_FLAG_INTERRUPTED);
		}
		uhci_finish_completed(self);
		/* No need to use `uhci_controller_unlock()' here. - We're the only place
		 * that could ever set the `UHCI_CONTROLLER_FLAG_INTERRUPTED' bit, so we
		 * know that no additional interrupt could happen after we release this
		 * lock! */
		sync_endwrite(&self->uc_lock);
		uhci_controller_resume(self);
	}
done:
	return true;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL uhci_fini)(struct character_device *__restrict self) {
	struct uhci_controller *me;
	me = (struct uhci_controller *)self;
	/* Make sure that the controller is stopped. */
	uhci_wrw(me, UHCI_USBCMD, 0);
	isr_unregister(&uhci_interrupt, me);
	if (me->uc_framelist)
		vpage_free(me->uc_framelist, 1);
}


/* Schedule the given queue for execution. */
PUBLIC void FCALL
uhci_controller_addqueue(struct uhci_controller *__restrict self,
                         REF struct uhci_osqh *__restrict osqh)
		THROWS(E_WOULDBLOCK) {
	struct uhci_osqh *last;
	sync_write(&self->uc_lock);
	uhci_controller_stop(self);
	last = self->uc_qhstart.qh_next;
	if (last) {
		/* TODO: Keep track of the last entry within the controller. */
		while (last->qh_next)
			last = last->qh_next;
		last->qh_next = osqh;
#ifdef CONFIG_UHCI_USE_QH_LOOPS
		osqh->qh_hp = self->uc_qhstart.qh_next->qh_self | UHCI_QHHP_QHTD;
#else /* CONFIG_UHCI_USE_QH_LOOPS */
		osqh->qh_hp = UHCI_QHHP_TERM;
#endif /* !CONFIG_UHCI_USE_QH_LOOPS */
		/* Append at the end of the hardware list */
		ATOMIC_WRITE(last->qh_hp, osqh->qh_self | UHCI_QHHP_QHTD);
	} else {
		osqh->qh_next = NULL;
		osqh->qh_hp   = UHCI_QHHP_TERM;
		self->uc_qhstart.qh_next = osqh;
		/* Set the first (and currently only) element of the hardware list. */
		ATOMIC_WRITE(self->uc_qhstart.qh_hp, osqh->qh_self | UHCI_QHHP_QHTD);
	}
	uhci_controller_resume(self);
	uhci_controller_endwrite(self);
}


PRIVATE void
NOTHROW(FCALL sleep_milli)(unsigned int n) {
	qtime_t then = quantum_time();
	then.add_milliseconds(n);
	task_sleep(&then);
}

PRIVATE u16
NOTHROW(FCALL uhci_controller_resetport)(struct uhci_controller *__restrict self,
                                         unsigned int portno) {
	u16 st;
	unsigned int n;
	st = uhci_rdw(self, UHCI_PORTSC(portno));
	uhci_wrw(self, UHCI_PORTSC(portno), st | UHCI_PORTSC_RST);
	sleep_milli(50);
	st = uhci_rdw(self, UHCI_PORTSC(portno));
	uhci_wrw(self, UHCI_PORTSC(portno), st & ~UHCI_PORTSC_RST);
	for (n = 0; n < 10; ++n) {
		sleep_milli(10);
		st = uhci_rdw(self, UHCI_PORTSC(portno));
		/* Check if something is connected. */
		if (!(st & UHCI_PORTSC_CCS))
			break;
		/* ACK the status change */
		if (st & (UHCI_PORTSC_PEDC | UHCI_PORTSC_CSC)) {
			uhci_wrw(self, UHCI_PORTSC(portno),
			         st & ~(UHCI_PORTSC_PEDC | UHCI_PORTSC_CSC));
			continue;
		}
		/* Check if the device has become enabled. */
		if (st & UHCI_PORTSC_PED)
			break;
		/* Try to enable the port. */
		uhci_wrw(self, UHCI_PORTSC(portno),
		         st | UHCI_PORTSC_PED);
	}
	return st;
}

PRIVATE ATTR_FREETEXT void FCALL
uhci_controller_probeport(struct uhci_controller *__restrict self,
                          unsigned int portno) {
	u16 status;
	printk(FREESTR(KERN_INFO "[usb] Checking for device on %#I16x\n"), portno);
	status = uhci_controller_resetport(self, portno);
	if (status & UHCI_PORTSC_PED) {
		struct aio_multihandle_generic aio;
		struct uhci_osqh *qh;
		struct uhci_ostd *td;
		printk(FREESTR(KERN_INFO "[usb] Device found on %#I16x\n"), portno);


		/* Just some tinkering with how USB works from here on... */
		unsigned int toggle = 0;
		aio_multihandle_generic_init(&aio);
		td = uhci_ostd_alloc();
		qh = uhci_osqh_alloc();
		qh->qh_refcnt = 2;
		qh->qh_tds    = td;
		qh->qh_ep     = td->td_self;
		qh->qh_aio    = aio_multihandle_allochandle(&aio);
		{
			struct uhci_aio_data *d;
			d = (struct uhci_aio_data *)qh->qh_aio->ah_data;
			d->ud_osqh          = qh; /* Inherit reference */
			d->ud_ctrl          = (REF struct uhci_controller *)incref(self);
			d->ud_dmalockvec    = NULL;
			d->ud_flags         = UHCI_AIO_FNORMAL;
			qh->qh_aio->ah_type = &uhci_aio_type;
		}

		alignas(8) byte_t data[8];
		alignas(8) byte_t setup[8];
		memset(data, 0xcc, sizeof(data));
		memset(setup, 0, sizeof(setup));
		setup[0] = 0x80; /* bmRequestType = Device-to-host | Standard | Device; */
		setup[1] = 0;    /* bRequest = GET_STATUS; */
		*(u16 *)(setup + 2) = 0; /* Value */
		*(u16 *)(setup + 4) = 0; /* Index */
		*(u16 *)(setup + 6) = sizeof(data);
		td->td_cs   = UHCI_TDCS_ACTIVE | UHCI_TDCS_ERRCNTM;
		if (status & UHCI_PORTSC_LSDA)
			td->td_cs |= UHCI_TDCS_LSD;
		td->td_tok = UHCI_TDTOK_PID_SETUP |
		             (0 << UHCI_TDTOK_DEVS) |   /* ??? */
		             (0 << UHCI_TDTOK_ENDPTS) | /* ??? */
		             (toggle << UHCI_TDTOK_DTOGGS) |  /* ??? */
		             ((sizeof(setup) - 1) << UHCI_TDTOK_MAXLENS);
		td->td_buf = (u32)pagedir_translate((vm_virt_t)setup);
		td->td_next = uhci_ostd_alloc();
		td->td_lp   = td->td_next->td_self;
		td = td->td_next;
		toggle ^= 1;

		td->td_tok = UHCI_TDTOK_PID_IN |
		             (0 << UHCI_TDTOK_DEVS) |   /* ??? */
		             (0 << UHCI_TDTOK_ENDPTS) | /* ??? */
		             (toggle << UHCI_TDTOK_DTOGGS) |  /* ??? */
		             ((sizeof(data) - 1) << UHCI_TDTOK_MAXLENS);
		td->td_buf = (u32)pagedir_translate((vm_virt_t)&data);
		td->td_cs   = UHCI_TDCS_ACTIVE | UHCI_TDCS_ERRCNTM;
		if (status & UHCI_PORTSC_LSDA)
			td->td_cs |= UHCI_TDCS_LSD;
		td->td_next = uhci_ostd_alloc();
		td->td_lp   = td->td_next->td_self;
		td = td->td_next;
		toggle ^= 1;

		td->td_tok = UHCI_TDTOK_PID_OUT |
		             (0 << UHCI_TDTOK_DEVS) |   /* ??? */
		             (0 << UHCI_TDTOK_ENDPTS) | /* ??? */
		             (toggle << UHCI_TDTOK_DTOGGS) |  /* ??? */
		             UHCI_TDTOK_MAXLENM;
		td->td_buf = 0;
		td->td_cs  = UHCI_TDCS_ACTIVE | UHCI_TDCS_ERRCNTM | UHCI_TDCS_IOC;
		if (status & UHCI_PORTSC_LSDA)
			td->td_cs |= UHCI_TDCS_LSD;
		td->td_lp = UHCI_TDLP_TERM;
		td->td_next = NULL;
		toggle ^= 1;

		uhci_controller_addqueue(self, qh);
		aio_multihandle_done(&aio);
		aio_multihandle_generic_waitfor(&aio);
		aio_multihandle_generic_checkerror(&aio);
		printk(KERN_DEBUG "setup:\n%$[hex]\n", sizeof(setup), setup);
		printk(KERN_DEBUG "data:\n%$[hex]\n", sizeof(data), data);
	}
}


INTERN ATTR_FREETEXT void KCALL
usb_probe_uhci(struct pci_device *__restrict dev) {
	struct uhci_controller *result;
	unsigned int i;
	result = CHARACTER_DEVICE_ALLOC(struct uhci_controller);
	result->uc_pci = dev;
	assert(IS_ALIGNED((uintptr_t)&result->uc_qhstart, UHCI_FLE_ALIGN));
	if (dev->pd_res[PD_RESOURCE_BAR4].pr_flags & PCI_RESOURCE_FIO) {
		result->uc_base.uc_iobase = (port_t)dev->pd_res[PD_RESOURCE_BAR4].pr_start;
	} else {
		vm_vpage_t page;
		page = vm_map(&vm_kernel,
		              (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_DEVICE), 1,
		              1, HINT_GETMODE(KERNEL_VMHINT_DEVICE),
		              &vm_datablock_physical,
		              (vm_vpage64_t)(vm_ppage_t)VM_ADDR2PAGE((vm_phys_t)dev->pd_res[PD_RESOURCE_BAR4].pr_start),
		              VM_PROT_READ | VM_PROT_WRITE,
		              VM_NODE_FLAG_NORMAL, 0);
		result->uc_base.uc_mmbase = (byte_t *)VM_PAGE2ADDR(page);
		result->uc_flags |= UHCI_CONTROLLER_FLAG_USESMMIO;
	}
	atomic_rwlock_cinit(&result->uc_lock);
	result->cd_type.ct_fini    = &uhci_fini;
	result->uc_framelist       = (u32 *)vpage_alloc(1, 1, GFP_LOCKED | GFP_PREFLT);
	result->uc_framelist_phys  = (u32)pagedir_translate((vm_virt_t)result->uc_framelist);
	result->uc_qhstart.qh_self = (u32)pagedir_translate((vm_virt_t)&result->uc_qhstart);

	/* Fill in the frame list */
	for (i = 0; i < UHCI_FRAMELIST_COUNT; ++i)
		result->uc_framelist[i] = UHCI_FLE_QHTD | result->uc_qhstart.qh_self;
	/* Setup the start queue head as terminal */
	result->uc_qhstart.qh_hp = UHCI_QHHP_TERM;
	result->uc_qhstart.qh_ep = UHCI_QHEP_TERM;
	/* Figure out the number of available ports. */
	for (i = 0; i < UHCI_PORTSCMAXCNT; ++i) {
		u16 st = uhci_rdw(result, UHCI_PORTSC(i));
		if (!(st & UHCI_PORTSC_R1) || st == 0xffff)
			break; /* End-of-chain */
	}
	if unlikely(!i) {
		printk(FREESTR(KERN_WARNING "[usb][pci:%I32p,io:%#Ix] uhci controller has no ports\n"),
		       dev->pd_base, result->uc_base.uc_mmbase);
		destroy(result);
		return;
	}
	result->uc_portnum = i;

	/* Configure PCI access. */
	pci_write(dev->pd_base, PCI_DEV4,
	          (pci_read(dev->pd_base, PCI_DEV4) & ~(PCI_CDEV4_NOIRQ)) |
	          (PCI_CDEV4_BUSMASTER | PCI_CDEV4_ALLOW_MEMWRITE) |
	          (dev->pd_res[PD_RESOURCE_BAR4].pr_flags & PCI_RESOURCE_FIO
	           ? PCI_CDEV4_ALLOW_IOTOUCH
	           : PCI_CDEV4_ALLOW_MEMTOUCH));

	/* Disable legacy support. */
	pci_write(dev->pd_base, 0xc0, 0x8f00);
	pci_write(dev->pd_base, 0xc0, 0x2000);

	/* Set the controller. */
	uhci_wrw(result, UHCI_USBCMD,
	         uhci_rdw(result, UHCI_USBCMD) | UHCI_USBCMD_HCRESET);
	while (uhci_rdw(result, UHCI_USBCMD) & UHCI_USBCMD_HCRESET)
		task_pause();

	/* Prevent interrupts prior to being fully initialized. */
	uhci_wrw(result, UHCI_USBINTR, 0);
	uhci_wrw(result, UHCI_USBCMD, 0);

	/* Initialize the frame list. */
	uhci_wrl(result, UHCI_FLBASEADD, result->uc_framelist_phys);
	uhci_wrw(result, UHCI_SOFMOD, UHCI_SOFMOD_DEFAULT);
	uhci_wrw(result, UHCI_FRNUM, 0);

	/* Clear the status register */
	uhci_wrw(result, UHCI_USBSTS, 0xffff);

	/* Register the interrupt handler. */
	isr_register_at(X86_INTERRUPT_PIC1_BASE +
	                PCI_GDEV3C_IRQLINE(pci_read(dev->pd_base, PCI_GDEV3C)),
	                &uhci_interrupt, result);

	/* Enable interrupts that we want to listen for. */
	uhci_wrw(result, UHCI_USBINTR,
	         UHCI_USBINTR_TIE | UHCI_USBINTR_RIE |
	         UHCI_USBINTR_IOC | UHCI_USBINTR_SPIE);

	/* Turn on the controller. */
	uhci_wrw(result, UHCI_USBCMD,
	         UHCI_USBCMD_RS | UHCI_USBCMD_CF |
	         UHCI_USBCMD_MAXP);


	{
		/* TODO: better naming */
		static int n = 0;
		sprintf(result->cd_name, "uhci%d", n++);
	}
	character_device_register_auto(result);

	/* Probe connections. */
	for (i = 0; i < result->uc_portnum; ++i)
		uhci_controller_probeport(result, i);
	uhci_wrw(result, UHCI_USBCMD, 0);
}


DECL_END

#endif /* !GUARD_MODUSB_UHCI_C */
