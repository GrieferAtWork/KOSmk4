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
#include <kernel/memory.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <sched/cpu.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/except-io.h>
#include <kos/io/uhci.h>
#include <kos/io/usb.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "usb.h"

#if !defined(NDEBUG) && 0
#define UHCI_DEBUG(...) printk(__VA_ARGS__)
#else
#define UHCI_DEBUG(...) (void)0
#endif

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

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_invcache)(struct uhci_controller *__restrict self,
                             u32 phys_addr) {
	/* XXX: Tell the UHCI controller to invalidate 4 bytes of physical memory at `phys_addr'? */
	(void)self;
	(void)phys_addr;
}



PRIVATE NOBLOCK NONNULL((1)) void NOTHROW(KCALL uhci_aio_fini)(struct aio_handle *__restrict self);
PRIVATE NOBLOCK NONNULL((1)) void NOTHROW(KCALL uhci_aio_cancel)(struct aio_handle *__restrict self);
PRIVATE NOBLOCK NONNULL((1, 2)) unsigned int NOTHROW(KCALL uhci_aio_progress)(struct aio_handle *__restrict self, struct aio_handle_stat *__restrict stat);
PRIVATE NOBLOCK WUNUSED NONNULL((1)) size_t NOTHROW(KCALL uhci_aio_retsize)(struct aio_handle *__restrict self);
STATIC_ASSERT(sizeof(struct uhci_aio_data) <= (AIO_HANDLE_DRIVER_POINTER_COUNT * sizeof(void *)));
PRIVATE struct aio_handle_type uhci_aio_type = {
	/* .ht_fini     = */ &uhci_aio_fini,
	/* .ht_cancel   = */ &uhci_aio_cancel,
	/* .ht_progress = */ &uhci_aio_progress,
	/* .ht_retsize  = */ &uhci_aio_retsize,
};


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL uhci_aio_fini)(struct aio_handle *__restrict self) {
	struct uhci_aio_data *data;
	data = (struct uhci_aio_data *)self->ah_data;
	decref_unlikely(data->ud_ctrl);
	decref_likely(data->ud_osqh);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL uhci_aio_cancel)(struct aio_handle *__restrict self) {
	struct uhci_aio_data *data;
	struct uhci_controller *ctrl;
	data = (struct uhci_aio_data *)self->ah_data;
again:
	if (ATOMIC_READ(data->ud_flags) & UHCI_AIO_FSERVED)
		return; /* Already completed. */
	ctrl = data->ud_ctrl;

	/* Acquire a lock to the controller to prevent it from completing
	 * our AIO, and setting `UHCI_AIO_FSERVED' before we can. */
	if unlikely(!sync_trywrite(&ctrl->uc_lock)) {
		task_tryyield_or_pause();
		goto again;
	}
	if likely(!(ATOMIC_READ(data->ud_flags) & UHCI_AIO_FSERVED)) {
		/* Cancel our AIO now */
		struct uhci_osqh **posqh, *osqh, *prev, *next;
		u32 hw_next_pointer;
		osqh = data->ud_osqh;
		/* Find the predecessor. */
		posqh = &ctrl->uc_qhstart.qh_next;
		for (;;) {
			struct uhci_osqh *iter;
			iter = *posqh;
			assert(iter);
			if (iter == osqh)
				break;
			posqh = &iter->qh_next;
		}
		*posqh = next = osqh->qh_next;
		prev   = container_of(posqh, struct uhci_osqh, qh_next);
#ifdef CONFIG_UHCI_USE_QH_LOOPS
		if (!next && prev != &ctrl->uc_qhstart)
			next = ctrl->uc_qhstart.qh_next;
#endif /* CONFIG_UHCI_USE_QH_LOOPS */
		hw_next_pointer = next ? next->qh_self | UHCI_QHHP_QHTD
		                       : UHCI_QHHP_TERM;
		if (ATOMIC_READ(osqh->qh_ep) & UHCI_QHEP_TERM) {
			/* The canceled operation was already completed.
			 * In this case, we don't need to stop the controller, since
			 * the unlinking process simply requires a cache invalidation. */
			ATOMIC_WRITE(prev->qh_hp, hw_next_pointer);
			uhci_invcache(ctrl, prev->qh_self + offsetof(struct uhci_osqh, qh_hp));
		} else {
			/* The operation was be in progress ~right now~
			 * -> Must stop the controller so that we can unlink it. */
			uhci_controller_stop(ctrl);
			ATOMIC_WRITE(prev->qh_hp, hw_next_pointer);
			uhci_controller_resume(ctrl);
		}
		/* Drop the reference taken from the queue chain. */
		decref_nokill(osqh);
	}
	uhci_controller_endwrite(ctrl);
}

PRIVATE NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(KCALL uhci_aio_progress)(struct aio_handle *__restrict self,
                                 struct aio_handle_stat *__restrict stat) {
	size_t complete = 0, total = 0;
	struct uhci_aio_data *data;
	struct uhci_osqh *osqh;
	struct uhci_ostd *td;
	u32 current_ep;
	unsigned int result;
	data = (struct uhci_aio_data *)self->ah_data;
	osqh = data->ud_osqh;
	td   = osqh->qh_tds;
	/* Make use of the EP pointer to figure out
	 * how many TDs have already been executed. */
	current_ep = ATOMIC_READ(osqh->qh_ep);
	result = AIO_PROGRESS_STATUS_INPROGRESS;
	if (current_ep & UHCI_QHEP_TERM) {
		/* Queue has already terminated. */
		for (; td; td = td->td_next) {
			complete += uhci_td_actlen(td);
			total    += uhci_td_maxlen(td);
		}
	} else {
		/* If the first TD is still the next one to-be processed,
		 * then we indicate that the operation is still pending. */
		if (td->td_self == current_ep)
			result = AIO_PROGRESS_STATUS_PENDING;
		for (; td; td = td->td_next) {
			if (td->td_self == current_ep)
				break;
			complete += uhci_td_actlen(td);
			total    += uhci_td_maxlen(td);
		}
		for (; td; td = td->td_next)
			total += uhci_td_maxlen(td);
	}
	if (ATOMIC_READ(data->ud_flags) & UHCI_AIO_FSERVED)
		result = AIO_PROGRESS_STATUS_COMPLETED;
	stat->hs_completed = complete;
	stat->hs_total     = total;
	return result;
}


PRIVATE NOBLOCK WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL uhci_aio_retsize)(struct aio_handle *__restrict self) {
	struct uhci_aio_data *data;
	data = (struct uhci_aio_data *)self->ah_data;
	assert(data->ud_flags & UHCI_AIO_FSERVED);
	return data->ud_retsize;
}

LOCAL NOBLOCK void
NOTHROW(FCALL uhci_aio_handle_finidma)(struct uhci_aio_data *__restrict self) {
	if (self->ud_flags & UHCI_AIO_FONEDMA)
		vm_dmalock_release(&self->ud_dmalock);
	else if (self->ud_dmalockvec) {
		struct vm_dmalock *iter;
		for (iter = self->ud_dmalockvec; iter->dl_part; ++iter)
			vm_dmalock_release(iter);
		kfree(self->ud_dmalockvec);
	}
}

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_osqh_aio_docomplete)(struct aio_handle *__restrict aio,
                                        unsigned int status) {
	struct uhci_aio_data *data;
	data = (struct uhci_aio_data *)aio->ah_data;
	if (!(ATOMIC_FETCHOR(data->ud_flags, UHCI_AIO_FSERVED) & UHCI_AIO_FSERVED)) {
		uhci_aio_handle_finidma(data);
		(*aio->ah_func)(aio, status);
	}
}

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_osqh_completed_ioerror)(struct uhci_controller *__restrict self,
                                           struct uhci_osqh *__restrict osqh,
                                           error_code_t code,
                                           uintptr_t io_reason,
                                           uintptr_t pointer2 DFL(0)) {
	struct aio_handle *aio;
	struct uhci_aio_data *aio_data;
	aio = osqh->qh_aio;
	aio_data = (struct uhci_aio_data *)aio->ah_data;
	assert(aio_data->ud_osqh == osqh);
	if likely(!(ATOMIC_READ(aio_data->ud_flags) & UHCI_AIO_FSERVED)) {
		struct exception_data odata;
		struct exception_data *mydat;
		mydat = error_data();
		odata = *mydat;
		memset(mydat, 0, sizeof(*mydat));
		mydat->e_code        = code;
		mydat->e_pointers[0] = E_IOERROR_SUBSYSTEM_USB;
		mydat->e_pointers[1] = io_reason;
		mydat->e_pointers[2] = pointer2;
		uhci_osqh_aio_docomplete(aio, AIO_COMPLETION_FAILURE);
		*mydat = odata;
	}
}




PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_osqh_aio_completed)(struct uhci_controller *__restrict self,
                                       struct uhci_osqh *__restrict osqh,
                                       struct aio_handle *__restrict aio) {
	struct uhci_ostd *td;
	struct uhci_aio_data *data;
	data = (struct uhci_aio_data *)aio->ah_data;
	/* Check for transfer errors. */
	data->ud_retsize = 0;
	for (td = osqh->qh_tds; td; td = td->td_next) {
		u16 actlen, maxlen;
		u32 cs = ATOMIC_READ(td->td_cs);
		actlen = (cs + 1) & UHCI_TDCS_ACTLEN;
		maxlen = uhci_td_maxlen(td);
		UHCI_DEBUG(KERN_DEBUG "[usb][pci:%I32p,io:%#Ix] uhci:td:complete"
		                      " [actlen=%#I16x,maxlen=%#I16x,cs=%#I32x,tok=%#I32x]\n",
		           self->uc_pci->pd_base, self->uc_base.uc_mmbase,
		           actlen, maxlen, cs, td->td_tok);
		/* Check for short packet */
		if (actlen < maxlen) {
			if unlikely(cs & UHCI_TDCS_SPD) {
				/* Shouldn't actually get here... From what I can tell, on working
				 * hardware, this should be handled in `uhci_finish_completed()'. */
				uhci_osqh_completed_ioerror(self, osqh,
				                            ERROR_CODEOF(E_IOERROR_NODATA),
				                            E_IOERROR_REASON_USB_SHORTPACKET);
				return;
			}
			if (td->td_next != NULL) {
				struct uhci_ostd *next_nonempty;
				u8 mypid = td->td_tok & UHCI_TDTOK_PID;
				next_nonempty = td->td_next;
				for (;;) {
					if ((next_nonempty->td_tok & UHCI_TDTOK_PID) != mypid)
						goto short_packet_ok; /* Different type of packet (Partially filled, trailing buffers are OK) */
					if (uhci_td_actlen(next_nonempty) != 0)
						break; /* Non-empty follow-up packet. */
					if ((next_nonempty = next_nonempty->td_next) == NULL)
						goto short_packet_ok; /* There are no later buffers (Partially filled, trailing buffers are OK) */
				}
				printk(KERN_WARNING "[usb][pci:%I32p,io:%#Ix] "
				                    "uhci:td:incomplete packet (%I16u/%I16u) followed "
				                    "by non-empty packets of the same type (pid=%#I8x)\n",
				       self->uc_pci->pd_base, self->uc_base.uc_mmbase,
				       actlen, maxlen, mypid);
				/* XXX: What now? Should we be trying to shift around buffer memory
				 *      in order to fill the gap? - When does this even happen? Or
				 *      is this even allowed to happen, because if not, then I can
				 *      just have the transmission be completed with an error.
				 *      If we were to blindly re-merge data buffers, we might end
				 *      up causing problems in case there is some endpoint function
				 *      that results in multiple chunks of dynamically sized packets. */
			}
		}
short_packet_ok:
		data->ud_retsize += actlen;
		if ((cs & (UHCI_TDCS_CRCTMO | UHCI_TDCS_NAKR |
		           UHCI_TDCS_BABBLE | UHCI_TDCS_DBE |
		           UHCI_TDCS_STALL | UHCI_TDCS_ACTIVE)) != 0) {
			uhci_osqh_completed_ioerror(self, osqh,
			                            ERROR_CODEOF(E_IOERROR_ERRORBIT),
			                            E_IOERROR_REASON_UHCI_TDCS,
			                            cs);
			return;
		}
	}
	uhci_osqh_aio_docomplete(aio, AIO_COMPLETION_SUCCESS);
}

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_osqh_completed)(struct uhci_controller *__restrict self,
                                   struct uhci_osqh *__restrict osqh) {
	struct aio_handle *aio;
	struct uhci_aio_data *aio_data;
	/* QH was completed. -> Try to signal the connected AIO receiver. */
	aio = osqh->qh_aio;
	aio_data = (struct uhci_aio_data *)aio->ah_data;
	assert(aio_data->ud_osqh == osqh);
	if likely(!(ATOMIC_READ(aio_data->ud_flags) & UHCI_AIO_FSERVED))
		uhci_osqh_aio_completed(self, osqh, aio);
}


PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_osqh_unlink)(struct uhci_controller *__restrict self,
                                struct uhci_osqh *__restrict entry,
                                struct uhci_osqh **__restrict pentry) {
	struct uhci_osqh *prev, *next;
	u32 hw_pointer;
	prev = container_of(pentry, struct uhci_osqh, qh_next);
	next = entry->qh_next;
	prev->qh_next = next;
#ifdef CONFIG_UHCI_USE_QH_LOOPS
	if (!next && prev != &self->uc_qhstart)
		next = self->uc_qhstart.qh_next;
#endif /* CONFIG_UHCI_USE_QH_LOOPS */
	hw_pointer = next ? next->qh_self | UHCI_QHHP_QHTD
	                  : UHCI_QHHP_TERM;
	ATOMIC_WRITE(prev->qh_hp, hw_pointer);
	uhci_invcache(self, prev->qh_self + offsetof(struct uhci_osqh, qh_hp));
}

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_finish_completed)(struct uhci_controller *__restrict self) {
	struct uhci_osqh **piter, *iter;
	assert(sync_writing(&self->uc_lock));
	piter = &self->uc_qhstart.qh_next;
	while ((iter = *piter) != NULL) {
		struct uhci_ostd *td;
		u32 ep, cs;
		ep = ATOMIC_READ(iter->qh_ep);
		if (ep & UHCI_QHEP_TERM) {
			/* This queue has completed */
			uhci_osqh_unlink(self, iter, piter);
			uhci_osqh_completed(self, iter);
			decref(iter);
			continue;
		}
		/* Find the TD that is currently being executed. */
		td = uhci_ostd_findphys(iter->qh_tds, ep);
		if unlikely(!td) {
			/* Shouldn't happen... */
			printk(KERN_CRIT "[usb][pci:%I32p,io:%#Ix] uhci:bad:ep (%#I32p)\n",
			       self->uc_pci->pd_base, self->uc_base.uc_mmbase, ep);
			uhci_osqh_unlink(self, iter, piter);
			uhci_osqh_completed_ioerror(self, iter,
			                            ERROR_CODEOF(E_IOERROR_NODATA),
			                            E_IOERROR_REASON_UHCI_BADEP,
			                            ep);
			decref(iter);
			continue;
		}
		/* Check the status of this TD */
		cs = ATOMIC_READ(td->td_cs);
		if (!(cs & UHCI_TDCS_ACTIVE)) {
			/* This could happen because `UHCI_TDCS_SPD' was set,
			 * in which case us getting here means an error: packet-too-short. */
			if (cs & UHCI_TDCS_SPD) {
				/* Check if the packet really has the wrong size. */
				u16 actlen = (cs + 1) & UHCI_TDCS_ACTLEN;
				u16 maxlen = uhci_td_maxlen(td);
				if (actlen < maxlen) {
					/* That's an error! */
					printk(KERN_ERR "[usb][pci:%I32p,io:%#Ix] uhci:short-packet (%I16u < %I16u)\n",
					       self->uc_pci->pd_base, self->uc_base.uc_mmbase, actlen, maxlen);
					uhci_osqh_unlink(self, iter, piter);
					uhci_osqh_completed_ioerror(self, iter,
					                            ERROR_CODEOF(E_IOERROR_NODATA),
					                            E_IOERROR_REASON_USB_SHORTPACKET);
					decref(iter);
					continue;
				}
			}
		}
		/* Check for error bits (regardless of the state of ACTIVE). */
		if (cs & (UHCI_TDCS_CRCTMO | UHCI_TDCS_NAKR |
		          UHCI_TDCS_BABBLE | UHCI_TDCS_DBE |
		          UHCI_TDCS_STALL)) {
			printk(KERN_ERR "[usb][pci:%I32p,io:%#Ix] uhci:error (cs=%#I32x,tok=%#I32x)\n",
			       self->uc_pci->pd_base, self->uc_base.uc_mmbase, cs, ATOMIC_READ(td->td_tok));
			uhci_osqh_unlink(self, iter, piter);
			uhci_osqh_completed_ioerror(self, iter,
			                            ERROR_CODEOF(E_IOERROR_ERRORBIT),
			                            E_IOERROR_REASON_UHCI_TDCS,
			                            cs);
			decref(iter);
			continue;
		}
		if (!(cs & UHCI_TDCS_ACTIVE)) {
			printk(KERN_ERR "[usb][pci:%I32p,io:%#Ix] uhci:inactive for unknown reason\n",
			       self->uc_pci->pd_base, self->uc_base.uc_mmbase);
			uhci_osqh_unlink(self, iter, piter);
			uhci_osqh_completed_ioerror(self, iter,
			                            ERROR_CODEOF(E_IOERROR_NODATA),
			                            E_IOERROR_REASON_UHCI_INCOMPLETE);
			decref(iter);
			continue;
		}
		/* Incomplete transmission (can happen when an operation is split between multiple
		 * frames because of its size, or because it was sharing bandwidth by not having
		 * the `UHCI_TDLP_DBS' flag set) */
		UHCI_DEBUG(KERN_DEBUG "[usb][pci:%I32p,io:%#Ix] uhci:incomplete [ep=%#I32x,cs=%#I32x,tok=%#I32x]\n",
		           self->uc_pci->pd_base, self->uc_base.uc_mmbase,
		           ep, cs, ATOMIC_READ(td->td_tok));

		/* In the case of depth-first, we can assume that there are no
		 * more completed queues to be found, since that would imply that
		 * our current queue would have also been completed! */
		if (td->td_lp & UHCI_TDLP_DBS)
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
	uhci_wrw(self, UHCI_USBSTS, status & (UHCI_USBSTS_USBINT | UHCI_USBSTS_ERROR));
	UHCI_DEBUG(KERN_TRACE "[usb][pci:%I32p,io:%#Ix] uhci interrupt (status=%#I8x)\n",
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
	if (status & (UHCI_USBSTS_USBINT | UHCI_USBSTS_ERROR)) {
		/* One of two things happened:
		 *  - A TD with the IOC bit was finished
		 *  - Some TD got one of its error bits set. */
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
	uhci_controller_endwrite(self);
}

/* Construct new TDs for  */
#if __SIZEOF_VM_PHYS_T__ > 4
PRIVATE bool KCALL
#else /* __SIZEOF_VM_PHYS_T__ > 4 */
PRIVATE void KCALL
#endif /* __SIZEOF_VM_PHYS_T__ <= 4 */
uhci_construct_tds(struct usb_controller *__restrict self,
                   struct uhci_ostd ***__restrict ppnexttd,
                   struct usb_endpoint *__restrict endp,
                   struct usb_transfer const *__restrict tx,
                   vm_phys_t start, size_t num_bytes) {
	u32 tok, cs;
#if __SIZEOF_VM_PHYS_T__ > 4
	if unlikely(num_bytes != 0 &&
	            (start > (vm_phys_t)0xffffffff ||
	             (start + num_bytes) > (vm_phys_t)0xffffffff))
		return false; /* Need a 32-bit buffer. */
#endif /* __SIZEOF_VM_PHYS_T__ > 4 */
	assert(tx->ut_type < USB_TRANSFER_TYPE_COUNT);
	cs = UHCI_TDCS_ACTIVE |
	     ((3 << UHCI_TDCS_ERRCNTS) & UHCI_TDCS_ERRCNTM);
	/* When short packets aren't allowed, turn on short packet detection. */
	if (!(tx->ut_flags & USB_TRANSFER_FLAG_SHORT))
		cs |= UHCI_TDCS_SPD;
	switch (tx->ut_type) {

	case USB_TRANSFER_TYPE_IN:
	case USB_TRANSFER_TYPE_IN_STATUS:
		tok = UHCI_TDTOK_PID_IN;
		break;

	case USB_TRANSFER_TYPE_OUT:
	case USB_TRANSFER_TYPE_OUT_STATUS:
		tok = UHCI_TDTOK_PID_OUT;
		/* Disable short-packet-detect for outbound data */
		cs &= ~UHCI_TDCS_SPD;
		break;

	case USB_TRANSFER_TYPE_SETUP:
		tok = UHCI_TDTOK_PID_SETUP;
		/* Disable short-packet-detect for outbound data */
		cs &= ~UHCI_TDCS_SPD;
		break;

	default: __builtin_unreachable();
	}
	/* Set the LowSpeedDevice bit for low-speed endpoints. */
	if (endp->ue_flags & USB_ENDPOINT_FLAG_LOWSPEED)
		cs |= UHCI_TDCS_LSD;
	tok |= ((u32)endp->ue_dev << UHCI_TDTOK_DEVS) & UHCI_TDTOK_DEVM;
	tok |= ((u32)endp->ue_endp << UHCI_TDTOK_ENDPTS) & UHCI_TDTOK_ENDPTM;
	/* Construct TD entires of up to `endp->ue_maxpck' bytes. */
	do {
		u16 mysize;
		struct uhci_ostd *td;
		td = uhci_ostd_alloc();
		**ppnexttd = td;
		*ppnexttd = &td->td_next;
		mysize = endp->ue_maxpck;
		if ((size_t)mysize > num_bytes)
			mysize = (u16)num_bytes;
		td->td_cs  = cs;
		td->td_tok = tok;
		td->td_tok |= ((mysize - 1) << UHCI_TDTOK_MAXLENS) & UHCI_TDTOK_MAXLENM;
		td->td_buf = (u32)start;
		if (tx->ut_type > USB_TRANSFER_TYPE_OUT) {
			/* Setup/Status stage packets. */
			if (tx->ut_type == USB_TRANSFER_TYPE_SETUP) {
				/* Setup packets must be followed by DTOG=1 */
				endp->ue_flags |= USB_ENDPOINT_FLAG_DATATOGGLE;
			} else {
				/* Status packets are used to terminate the sequence and are required
				 * to have the data toggle bit set. However, if the device is the one
				 * to send the next data packet, then that page should come with the
				 * data toggle bit set to 0, so remember that fact now. */
				td->td_tok |= UHCI_TDTOK_DTOGGM;
				endp->ue_flags &= ~USB_ENDPOINT_FLAG_DATATOGGLE;
			}
		} else {
#if USB_ENDPOINT_FLAG_DATATOGGLE == 1
			td->td_tok |= ((endp->ue_flags & USB_ENDPOINT_FLAG_DATATOGGLE) << UHCI_TDTOK_DTOGGS);
#else /* USB_ENDPOINT_FLAG_DATATOGGLE == 1 */
			td->td_tok |= (endp->ue_flags & USB_ENDPOINT_FLAG_DATATOGGLE) ? UHCI_TDTOK_DTOGGM : 0;
#endif /* USB_ENDPOINT_FLAG_DATATOGGLE != 1 */
			endp->ue_flags ^= USB_ENDPOINT_FLAG_DATATOGGLE;
		}
		start     += mysize;
		num_bytes -= mysize;
	} while (num_bytes);
#if __SIZEOF_VM_PHYS_T__ > 4
	return true;
#endif /* __SIZEOF_VM_PHYS_T__ > 4 */
}

PRIVATE NONNULL((1, 2, 3, 4)) void KCALL
uhci_transfer(struct usb_controller *__restrict self,
              struct usb_endpoint *__restrict endp,
              struct usb_transfer const *__restrict tx,
              /*out*/ struct aio_handle *__restrict aio);

struct uhci_syncheap_page {
	vm_ppage_t shp_next;  /* Pointer to the next page (or `PAGEPTR_INVALID') */
	size_t     shp_count; /* Number of consecutively allocated pages. */
};

struct uhci_syncheap {
	vm_ppage_t sh_current; /* Physical address of a `struct uhci_syncheap_page' structure
	                        * describing the next allocated page (or `PAGEPTR_INVALID'). */
	size_t     sh_free;    /* Number of bytes, starting at `VM_PAGE2ADDR(sh_current) +
	                        * sizeof(struct uhci_syncheap_page)'. */
};

#define UHCI_SYNCHEAP_INIT  { PAGEPTR_INVALID, 0 }

PRIVATE NOBLOCK void
NOTHROW(KCALL uhci_syncheap_fini)(struct uhci_syncheap *__restrict self) {
	vm_ppage_t page;
	/* Free all allocated pages of physical memory. */
	page = self->sh_current;
	while (page != PAGEPTR_INVALID) {
		struct uhci_syncheap_page next;
		vm_copyfromphys(&next, VM_PPAGE2ADDR(self->sh_current),
		                sizeof(struct uhci_syncheap_page));
		page_free(page, next.shp_count);
		page = next.shp_next;
	}
	
}

#define UHCI_SYNCHEAP_ALLOC_FAILED ((u32)-1)
/* Allocate physical memory (or return `UHCI_SYNCHEAP_ALLOC_FAILED' on failure)
 * Note that even on failure, when `num_bytes > PAGESIZE', there is a
 * possibility that the re-attempting the allocation with a smaller size could
 * succeed. */
PRIVATE NOBLOCK u32
NOTHROW(KCALL uhci_syncheap_alloc)(struct uhci_syncheap *__restrict self,
                                   size_t num_bytes) {
	u32 result;
	if (num_bytes > self->sh_free) {
		/* Must allocate a new page block. */
		pageptr_t pg;
		struct uhci_syncheap_page header;
		header.shp_count = CEILDIV(num_bytes +
		                           sizeof(struct uhci_syncheap_page),
		                           PAGESIZE);
#if __SIZEOF_VM_PHYS_T__ > 4
		pg = page_malloc_between(0,
		                         VM_ADDR2PAGE((vm_phys_t)0xffffffff),
		                         header.shp_count);
#else /* __SIZEOF_VM_PHYS_T__ > 4 */
		pg = page_malloc(header.shp_count);
#endif /* __SIZEOF_VM_PHYS_T__ <= 4 */
		if (pg == PAGEPTR_INVALID)
			return UHCI_SYNCHEAP_ALLOC_FAILED;
		header.shp_next = self->sh_current;
		vm_copytophys(VM_PPAGE2ADDR(pg), &header, sizeof(header));
		self->sh_free = (header.shp_count * PAGESIZE) -
		                sizeof(struct uhci_syncheap_page);
		self->sh_current = pg;
	}
	assert(num_bytes < self->sh_free);
	result = (u32)VM_PPAGE2ADDR(self->sh_current);
	result += sizeof(struct uhci_syncheap_page);
	result += self->sh_free;
	result -= num_bytes;
	self->sh_free -= num_bytes;
	return result;
}

PRIVATE struct aio_pbuffer *KCALL
usb_transfer_allocate_pbuffer(struct uhci_syncheap *__restrict heap,
                              size_t num_bytes) {
	struct aio_pbuffer *result;
	struct aio_pbuffer_entry *entv;
	size_t req_pages = CEILDIV(num_bytes, PAGESIZE);
	assert(req_pages != 0);
	result = (struct aio_pbuffer *)kmalloc(sizeof(struct aio_pbuffer) +
	                                       req_pages *
	                                       sizeof(struct aio_pbuffer_entry),
	                                       GFP_NORMAL);
	TRY {
		size_t i;
		entv = (struct aio_pbuffer_entry *)((byte_t *)result + sizeof(struct aio_pbuffer));
		result->ab_entc = req_pages;
		result->ab_entv = entv;
		for (i = 0; i < req_pages; ++i) {
			u32 addr;
			size_t reqbytes;
			reqbytes = i == req_pages - 1
			           ? num_bytes & (PAGESIZE - 1)
			           : PAGESIZE;
			addr = uhci_syncheap_alloc(heap, reqbytes);
			if unlikely(addr == UHCI_SYNCHEAP_ALLOC_FAILED)
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
			entv[i].ab_base = (vm_phys_t)addr;
			entv[i].ab_size = reqbytes;
		}
		result->ab_head = entv[0];
		result->ab_last = entv[req_pages - 1].ab_size;
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	return result;
}


PRIVATE void KCALL
usb_transfer_allocate_physbuf(struct usb_transfer *__restrict tx,
                              struct uhci_syncheap *__restrict heap) {
	u32 bufaddr;
	bufaddr = uhci_syncheap_alloc(heap, tx->ut_buflen);
	if likely(bufaddr != UHCI_SYNCHEAP_ALLOC_FAILED) {
		tx->ut_bufp   = (vm_phys_t)bufaddr;
		tx->ut_buftyp = USB_TRANSFER_BUFTYP_PHYS;
		return;
	}
	if (tx->ut_buflen > PAGESIZE) {
		/* Allocate in single pages. */
		tx->ut_vbufp  = usb_transfer_allocate_pbuffer(heap, tx->ut_buflen);
		tx->ut_buftyp = USB_TRANSFER_BUFTYP_PHYSVEC;
		return;
	}
	THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
}


/* This function performs a synchronous transfer operation by going
 * through real physical memory in order to allow USB transfers to/
 * from buffers located in VIO memory regions, as well as physical
 * memory locations above 4GiB
 * @return: * : The total number of transferred bytes. */
PRIVATE NONNULL((1, 2, 3)) size_t KCALL
uhci_transfer_sync_with_phys(struct usb_controller *__restrict self,
                             struct usb_endpoint *__restrict endp,
                             struct usb_transfer const *__restrict tx) {
	size_t result;
	struct usb_transfer *tx_firstcopy = NULL;
	struct usb_transfer **ptx_copy, *tx_copy;
	struct usb_transfer const *tx_iter;
	struct uhci_syncheap heap = UHCI_SYNCHEAP_INIT;
	/* Allocate physical memory buffers for all TX packets
	 * and copy data from input packets inside, then perform
	 * the operation synchronously before copying data from
	 * output packets into the original buffers, and freeing
	 * the temporary buffers. */
	TRY {
		ptx_copy = &tx_firstcopy;
		tx_iter = tx;
		do {
			tx_copy = (struct usb_transfer *)kmalloc(sizeof(struct usb_transfer),
			                                         GFP_NORMAL);
			memcpy(tx_copy, tx_iter, sizeof(struct usb_transfer));
			*ptx_copy = tx_copy;
			ptx_copy = &tx_copy->ut_next;
			if (!tx_iter->ut_buflen)
				goto copy_next_tx;
			/* Allocate the buffer for the output TX */
			if (tx_iter->ut_buftyp == USB_TRANSFER_BUFTYP_PHYS) {
#if __SIZEOF_VM_PHYS_T__ > 4
				if (tx_iter->ut_bufp > (vm_phys_t)0xffffffff ||
				    (tx_iter->ut_bufp + tx_iter->ut_buflen) > (vm_phys_t)0xffffffff)
					goto do_alloc_new_buffer;
#endif /* __SIZEOF_VM_PHYS_T__ <= 4 */
				tx_copy->ut_bufp = tx_iter->ut_bufp;
			} else if (tx_iter->ut_buftyp == USB_TRANSFER_BUFTYP_PHYSVEC) {
#if __SIZEOF_VM_PHYS_T__ > 4
				struct aio_pbuffer_entry ent;
				AIO_PBUFFER_FOREACH(ent, tx_iter->ut_vbufp) {
					if (ent.ab_base > (vm_phys_t)0xffffffff ||
					    (ent.ab_base + ent.ab_size) > (vm_phys_t)0xffffffff)
						goto do_alloc_new_buffer;
				}
#endif /* __SIZEOF_VM_PHYS_T__ <= 4 */
				tx_copy->ut_vbufp = tx_iter->ut_vbufp;
			} else {
#if __SIZEOF_VM_PHYS_T__ > 4
do_alloc_new_buffer:
#endif /* __SIZEOF_VM_PHYS_T__ <= 4 */
				usb_transfer_allocate_physbuf(tx_copy, &heap);
			}
			/* Copy outgoing packet data into the physical memory buffers. */
			if (tx_iter->ut_type != USB_TRANSFER_TYPE_IN) {
				switch (tx_iter->ut_buftyp) {

				case USB_TRANSFER_BUFTYP_VIRT:
					if (tx_copy->ut_buftyp == USB_TRANSFER_BUFTYP_PHYSVEC) {
						aio_pbuffer_copyfrommem(tx_copy->ut_vbufp,
						                        0,
						                        tx_iter->ut_buf,
						                        tx_copy->ut_buflen);
					} else {
						vm_copytophys(tx_copy->ut_bufp,
						              tx_iter->ut_buf,
						              tx_copy->ut_buflen);
					}
					break;

				case USB_TRANSFER_BUFTYP_VIRTVEC:
					if (tx_copy->ut_buftyp == USB_TRANSFER_BUFTYP_PHYSVEC) {
						aio_buffer_copytovphys(tx_iter->ut_vbuf,
						                       tx_copy->ut_vbufp,
						                       0,
						                       0,
						                       tx_copy->ut_buflen);
					} else {
						aio_buffer_copytophys(tx_iter->ut_vbuf,
						                      tx_copy->ut_bufp,
						                      0,
						                      tx_copy->ut_buflen);
					}
					break;

				case USB_TRANSFER_BUFTYP_PHYS:
					if (tx_copy->ut_buftyp == USB_TRANSFER_BUFTYP_PHYS) {
						if (tx_copy->ut_bufp == tx_iter->ut_bufp)
							break; /* Same buffer was used. */
						vm_copyinphys(tx_copy->ut_bufp,
						              tx_iter->ut_bufp,
						              tx_copy->ut_buflen);
					} else {
						aio_pbuffer_copytophys(tx_copy->ut_vbufp,
						                       tx_iter->ut_bufp,
						                       0,
						                       tx_copy->ut_buflen);
					}
					break;

				case USB_TRANSFER_BUFTYP_PHYSVEC:
					if (tx_copy->ut_buftyp == USB_TRANSFER_BUFTYP_PHYSVEC) {
						if (tx_copy->ut_vbufp == tx_iter->ut_vbufp)
							break; /* Same buffer was used. */
						aio_pbuffer_copytovphys(tx_copy->ut_vbufp,
						                        tx_iter->ut_vbufp,
						                        0,
						                        0,
						                        tx_copy->ut_buflen);
					} else {
						aio_pbuffer_copyfromphys(tx_iter->ut_vbufp,
						                         0,
						                         tx_copy->ut_bufp,
						                         tx_copy->ut_buflen);
					}
					break;

				default: __builtin_unreachable();
				}
			}
copy_next_tx:
			;
		} while ((tx_iter = tx_iter->ut_next) != NULL);
		assert(*ptx_copy == NULL);
		{
			struct aio_handle_generic aio;
			aio_handle_generic_init(&aio);
			/* perform the transfer using our buffer copies. */
			uhci_transfer(self, endp, tx_firstcopy, &aio);
			TRY {
				aio_handle_generic_waitfor(&aio);
				aio_handle_generic_checkerror(&aio);
			} EXCEPT {
				aio_handle_generic_fini(&aio);
				RETHROW();
			}
			assert(aio.ah_type == &uhci_aio_type);
			result = uhci_aio_retsize(&aio);
			aio_handle_generic_fini(&aio);
		}
		/* Transfer input data buffers to their target locations. */
		tx_copy = tx_firstcopy;
		tx_iter = tx;
		assert(tx_copy);
		assert(tx_iter);
		for (;;) {
			assert(tx_copy->ut_type == tx_iter->ut_type);
			assert(tx_copy->ut_buflen == tx_iter->ut_buflen);
			if (tx_iter->ut_type == USB_TRANSFER_TYPE_IN) {
				switch (tx_iter->ut_buftyp) {

				case USB_TRANSFER_BUFTYP_VIRT:
					if (tx_copy->ut_buftyp == USB_TRANSFER_BUFTYP_PHYSVEC) {
						aio_pbuffer_copytomem(tx_copy->ut_vbufp,
						                      tx_iter->ut_buf,
						                      0,
						                      tx_copy->ut_buflen);
					} else {
						vm_copyfromphys(tx_iter->ut_buf,
						                tx_copy->ut_bufp,
						                tx_copy->ut_buflen);
					}
					break;

				case USB_TRANSFER_BUFTYP_VIRTVEC:
					if (tx_copy->ut_buftyp == USB_TRANSFER_BUFTYP_PHYSVEC) {
						aio_pbuffer_copytovmem(tx_copy->ut_vbufp,
						                       tx_iter->ut_vbuf,
						                       0,
						                       0,
						                       tx_copy->ut_buflen);
					} else {
						aio_buffer_copyfromphys(tx_iter->ut_vbuf,
						                        0,
						                        tx_copy->ut_bufp,
						                        tx_copy->ut_buflen);
					}
					break;

				case USB_TRANSFER_BUFTYP_PHYS:
					if (tx_copy->ut_buftyp == USB_TRANSFER_BUFTYP_PHYS) {
						if (tx_copy->ut_bufp == tx_iter->ut_bufp)
							break; /* Same buffer was used. */
						vm_copyinphys(tx_iter->ut_bufp,
						              tx_copy->ut_bufp,
						              tx_copy->ut_buflen);
					} else {
						aio_pbuffer_copytophys(tx_copy->ut_vbufp,
						                       tx_iter->ut_bufp,
						                       0,
						                       tx_copy->ut_buflen);
					}
					break;

				case USB_TRANSFER_BUFTYP_PHYSVEC:
					if (tx_copy->ut_buftyp == USB_TRANSFER_BUFTYP_PHYSVEC) {
						if (tx_copy->ut_vbufp == tx_iter->ut_vbufp)
							break; /* Same buffer was used. */
						aio_pbuffer_copytovphys(tx_copy->ut_vbufp,
						                        tx_iter->ut_vbufp,
						                        0,
						                        0,
						                        tx_copy->ut_buflen);
					} else {
						aio_pbuffer_copyfromphys(tx_iter->ut_vbufp,
						                         0,
						                         tx_copy->ut_bufp,
						                         tx_copy->ut_buflen);
					}
					break;

				default: __builtin_unreachable();
				}
			}
			tx_copy = tx_copy->ut_next;
			tx_iter = tx_iter->ut_next;
			if (!tx_iter)
				break;
		}
		assert((tx_iter != NULL) == (tx_copy != NULL));
	} EXCEPT {
		while (tx_firstcopy) {
			assert(tx);
			tx_copy = tx_firstcopy->ut_next;
			if (tx_firstcopy->ut_buftyp == USB_TRANSFER_BUFTYP_PHYSVEC &&
			    tx_firstcopy->ut_vbufp != tx->ut_vbufp)
				kfree((void *)tx_firstcopy->ut_vbufp);
			kfree(tx_firstcopy);
			tx_firstcopy = tx_copy;
			tx = tx->ut_next;
		}
		uhci_syncheap_fini(&heap);
		RETHROW();
	}
	while (tx_firstcopy) {
		assert(tx);
		tx_copy = tx_firstcopy->ut_next;
		if (tx_firstcopy->ut_buftyp == USB_TRANSFER_BUFTYP_PHYSVEC &&
		    tx_firstcopy->ut_vbufp != tx->ut_vbufp)
			kfree((void *)tx_firstcopy->ut_vbufp);
		kfree(tx_firstcopy);
		tx_firstcopy = tx_copy;
		tx = tx->ut_next;
	}
	return result;
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL uhci_aio_noop_noarg)(struct aio_handle *__restrict UNUSED(self)) {
}

PRIVATE NOBLOCK WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL uhci_aio_sync_retsize)(struct aio_handle *__restrict self) {
	return (size_t)self->ah_data[0];
}

/* No-op AIO handle type (intended for synchronous operations) */
PRIVATE struct aio_handle_type uhci_aio_sync_type = {
	/* .ht_fini     = */ &uhci_aio_noop_noarg,
	/* .ht_cancel   = */ &uhci_aio_noop_noarg,
	/* .ht_progress = */ NULL,
	/* .ht_retsize  = */ &uhci_aio_sync_retsize
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
PRIVATE NONNULL((1, 2, 3, 4)) void KCALL
uhci_transfer(struct usb_controller *__restrict self,
              struct usb_endpoint *__restrict endp,
              struct usb_transfer const *__restrict tx,
              /*out*/ struct aio_handle *__restrict aio) {
	struct uhci_aio_data *data;
	struct uhci_osqh *qh;
	struct uhci_ostd **pnexttd, *lasttd, *td_iter;
	struct uhci_controller *me;
	struct usb_transfer const *tx_iter;
	assert(tx != NULL);
	me   = (struct uhci_controller *)self;
	data = (struct uhci_aio_data *)aio->ah_data;
	qh   = uhci_osqh_alloc();
	aio->ah_type = &uhci_aio_type;
	TRY {
		qh->qh_refcnt = 2; /* +1: aio->ah_data->ud_osqh; +1: me->uc_qhstart.qh_next */
		qh->qh_aio    = aio;
		data->ud_flags      = UHCI_AIO_FNORMAL;
		data->ud_dmalockvec = NULL;
		tx_iter = tx;
		pnexttd = &qh->qh_tds;
		TRY {
			do {
				assert(tx_iter->ut_type < USB_TRANSFER_TYPE_COUNT);
				assert(tx_iter->ut_buftyp < USB_TRANSFER_BUFTYP_COUNT);
				switch (tx_iter->ut_buftyp) {

				case USB_TRANSFER_BUFTYP_VIRT:
					if (!tx_iter->ut_buflen)
						goto do_configure_simple_empty;
					/* TODO: vm_startdma() */
					goto cleanup_configured_and_do_syncio;

				case USB_TRANSFER_BUFTYP_VIRTVEC:
					if (!tx_iter->ut_buflen)
						goto do_configure_simple_empty;
					/* TODO: vm_startdmav() */
					goto cleanup_configured_and_do_syncio;

				case USB_TRANSFER_BUFTYP_PHYS:
do_configure_simple_empty:
#if __SIZEOF_VM_PHYS_T__ > 4
					if unlikely(!uhci_construct_tds(self, &pnexttd, endp, tx_iter,
					                                tx_iter->ut_bufp,
					                                tx_iter->ut_buflen))
						goto cleanup_configured_and_do_syncio;
#else /* __SIZEOF_VM_PHYS_T__ > 4 */
					uhci_construct_tds(self, &pnexttd, endp, tx_iter,
					                   tx_iter->ut_bufp,
					                   tx_iter->ut_buflen);
#endif /* __SIZEOF_VM_PHYS_T__ <= 4 */
					break;

				case USB_TRANSFER_BUFTYP_PHYSVEC: {
					struct aio_pbuffer_entry ent;
					AIO_PBUFFER_FOREACH(ent, tx_iter->ut_vbufp) {
#if __SIZEOF_VM_PHYS_T__ > 4
						if unlikely(!uhci_construct_tds(self, &pnexttd, endp, tx_iter,
						                                ent.ab_base,
						                                ent.ab_size))
							goto cleanup_configured_and_do_syncio;
#else /* __SIZEOF_VM_PHYS_T__ > 4 */
						uhci_construct_tds(self, &pnexttd, endp, tx_iter,
						                   ent.ab_base,
						                   ent.ab_size);
#endif /* __SIZEOF_VM_PHYS_T__ <= 4 */
					}
				}	break;

				default: __builtin_unreachable();
				}
			} while ((tx_iter = tx_iter->ut_next) != NULL);
			assert(pnexttd != &qh->qh_tds);
			*pnexttd = NULL;
			assert(qh->qh_tds != NULL);
			/* Configure the last TD in the queue. */
			lasttd = container_of(pnexttd, struct uhci_ostd, td_next);
			lasttd->td_lp = UHCI_TDLP_TERM;
			lasttd->td_cs |= UHCI_TDCS_IOC;
			td_iter = qh->qh_tds;
			qh->qh_ep = td_iter->td_self; /* Hardware pointer! */
			for (; td_iter != lasttd;) {
				struct uhci_ostd *td_next;
				td_next = td_iter->td_next;
				/* Link up the hardware TD pointer chain. */
				td_iter->td_lp = td_next->td_self;
				td_iter = td_next;
			}
			data->ud_osqh = qh; /* Inherit reference */
			data->ud_ctrl = (REF struct uhci_controller *)incref(me);
			TRY {
				uhci_controller_addqueue(me, qh);
			} EXCEPT {
				decref_nokill(me);
				RETHROW();
			}
		} EXCEPT {
			struct uhci_ostd **piter;
			/* Cleanup already acquired DMA locks */
			uhci_aio_handle_finidma(data);
			/* Cleanup already created TDs */
			piter = &qh->qh_tds;
			while (piter != pnexttd) {
				lasttd = *piter;
				if (piter != &qh->qh_tds)
					uhci_ostd_free(container_of(piter, struct uhci_ostd, td_next));
				piter  = &lasttd->td_next;
			}
			RETHROW();
		}
	} EXCEPT {
		uhci_osqh_free(qh);
		RETHROW();
	}
	return;
cleanup_configured_and_do_syncio:
	/* Cleanup already acquired DMA locks */
	uhci_aio_handle_finidma(data);
	{
		struct uhci_ostd **piter;
		/* Cleanup already created TDs */
		piter = &qh->qh_tds;
		while (piter != pnexttd) {
			lasttd = *piter;
			if (piter != &qh->qh_tds)
				uhci_ostd_free(container_of(piter, struct uhci_ostd, td_next));
			piter  = &lasttd->td_next;
		}
	}
	/* Allocate physical memory buffers for all TX packets
	 * and copy data from input packets inside, then perform
	 * the operation synchronously before copying data from
	 * output packets into the original buffers, and freeing
	 * the temporary buffers. */
	{
		size_t transfer_size;
		transfer_size = uhci_transfer_sync_with_phys(self, endp, tx);
		/* Still always propagate the total number of transferred bytes. */
		aio->ah_data[0] = (void *)transfer_size;
		aio->ah_type    = &uhci_aio_sync_type;
	}
	aio_handle_success(aio);
}




PRIVATE void
NOTHROW(FCALL sleep_milli)(unsigned int n) {
	qtime_t then = quantum_time();
	then.add_milliseconds(n);
	do {
		task_sleep(&then);
	} while (quantum_time() < then);
}

PRIVATE u16
NOTHROW(FCALL uhci_controller_resetport)(struct uhci_controller *__restrict self,
                                         unsigned int portno) {
	u16 st;
	unsigned int n;
	st = uhci_rdw(self, UHCI_PORTSC(portno));
	uhci_wrw(self, UHCI_PORTSC(portno),
	         st | UHCI_PORTSC_PEDC | UHCI_PORTSC_CSC | UHCI_PORTSC_RST);
	sleep_milli(50);
	st = uhci_rdw(self, UHCI_PORTSC(portno));
	/* Make sure not to write WC bits so they don't get cleared by this! */
	uhci_wrw(self, UHCI_PORTSC(portno),
	         st & ~(UHCI_PORTSC_PEDC | UHCI_PORTSC_CSC | UHCI_PORTSC_RST));
	for (n = 0; n < 10; ++n) {
		sleep_milli(10);
		st = uhci_rdw(self, UHCI_PORTSC(portno));
		/* Check if something is connected. */
		if (!(st & UHCI_PORTSC_CCS))
			break;
		/* ACK the status change
		 * Note that PEDC and CSC are r/wc, so
		 * writing them will actually clear them! */
		if (st & (UHCI_PORTSC_PEDC | UHCI_PORTSC_CSC)) {
			uhci_wrw(self, UHCI_PORTSC(portno), st);
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
	printk(FREESTR(KERN_INFO "[usb][pci:%I32p,io:%#Ix] Checking for device on uhci:%#I16x\n"),
	       self->uc_pci->pd_base, self->uc_base.uc_mmbase, portno);
	status = uhci_controller_resetport(self, portno);
	if (status & UHCI_PORTSC_PED) {
		struct usb_device *dev;
		printk(FREESTR(KERN_INFO "[usb][pci:%I32p,io:%#Ix] Device found on uhci:%#I16x\n"),
		       self->uc_pci->pd_base, self->uc_base.uc_mmbase, portno);
		dev = (struct usb_device *)kmalloc(sizeof(struct usb_device),
		                                   GFP_NORMAL | GFP_CALLOC);
		dev->ue_refcnt    = 1;
		dev->ue_interface = dev;
		dev->ui_device    = dev;
		dev->ue_maxpck    = 0x7ff; /* Not configured. (Physical limit of the protocol) */
		dev->ue_dev       = 0;     /* Not configured. (Gets set by `usb_device_discovered()') */
		dev->ue_endp      = 0;     /* Configure channel. */
		dev->ue_flags     = status & UHCI_PORTSC_LSDA ? USB_ENDPOINT_FLAG_LOWSPEED : 0;
		FINALLY_DECREF_UNLIKELY(dev);
		usb_device_discovered(self, dev);
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
	usb_controller_cinit(result);
	atomic_rwlock_cinit(&result->uc_lock);
	result->cd_type.ct_fini    = &uhci_fini;
	result->uc_transfer        = &uhci_transfer;
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
