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

#include <dev/block.h>
#include <dev/char.h>
#include <drivers/pci.h>
#include <drivers/usb.h>
#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/interrupt.h>
#include <kernel/memory.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
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

#if !defined(NDEBUG) && 1
//#define UHCI_DEBUG_LOG_TD_COMPLETE 1
//#define UHCI_DEBUG_LOG_INTERRUPT 1
#define UHCI_DEBUG(...)             printk(__VA_ARGS__)
#else /* !NDEBUG */
#define UHCI_DEBUG(...) (void)0
#endif /* NDEBUG */

DECL_BEGIN

/* Write a memory location that may be read by hardware at any point in time. */
#define HW_WRITE(dst, value) ATOMIC_WRITE(dst, value)

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
	assertf(IS_ALIGNED(phys_addr, UHCI_FLE_ALIGN),
	        "phys_addr = %I32p", phys_addr);
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


LOCAL NOBLOCK bool
NOTHROW(FCALL uhci_controller_isstopped)(struct uhci_controller *__restrict self) {
	return (uhci_rdw(self, UHCI_USBSTS) & UHCI_USBSTS_HCH) != 0;
}

LOCAL NOBLOCK void
NOTHROW(FCALL uhci_controller_stop)(struct uhci_controller *__restrict self) {
	u16 cmd;
	cmd = uhci_rdw(self, UHCI_USBCMD);
	cmd &= ~UHCI_USBCMD_RS;
	uhci_wrw(self, UHCI_USBCMD, cmd);
	while (!uhci_controller_isstopped(self))
		task_pause();
}

LOCAL NOBLOCK void
NOTHROW(FCALL uhci_controller_resume)(struct uhci_controller *__restrict self) {
	u16 cmd;
	cmd = uhci_rdw(self, UHCI_USBCMD);
	cmd |= UHCI_USBCMD_RS;
	uhci_wrw(self, UHCI_USBCMD, cmd);
}


LOCAL NOBLOCK void
NOTHROW(FCALL uhci_controller_egsm_enter_log)(struct uhci_controller *__restrict self) {
	printk(KERN_INFO "[usb][pci:%I32p,io:%#Ix][+] Enter uhci suspend mode\n",
	       self->uc_pci->pd_base, self->uc_base.uc_mmbase);
}
LOCAL NOBLOCK void
NOTHROW(FCALL uhci_controller_egsm_leave_log)(struct uhci_controller *__restrict self) {
	printk(KERN_INFO "[usb][pci:%I32p,io:%#Ix][-] Leave uhci suspend mode\n",
	       self->uc_pci->pd_base, self->uc_base.uc_mmbase);
}

/* Check if any port has the `UHCI_PORTSC_CSC' (ConnectStatusChange) flag set. */
LOCAL NOBLOCK bool
NOTHROW(FCALL uhci_controller_have_csc_port)(struct uhci_controller *__restrict self) {
	u8 i;
	for (i = 0; i < self->uc_portnum; ++i) {
		u16 portst;
		portst = uhci_rdw(self, UHCI_PORTSC(i));
		if (portst & UHCI_PORTSC_CSC)
			return true;
	}
	return false;
}

LOCAL NOBLOCK bool
NOTHROW(FCALL uhci_controller_egsm_enter)(struct uhci_controller *__restrict self) {
	if (!(self->uc_flags & UHCI_CONTROLLER_FLAG_SUSPENDED)) {
		u16 cmd;
		cmd = uhci_rdw(self, UHCI_USBCMD);
		cmd |= UHCI_USBCMD_EGSM;
		uhci_wrw(self, UHCI_USBCMD, cmd);
		/* If the connected status of any port has changed, then we mustn't
		 * allow the controller to remain in EGSM mode, but rather handle the
		 * change in connectivity down below! */
		if unlikely(uhci_controller_have_csc_port(self)) {
			uhci_wrw(self, UHCI_USBCMD, cmd & ~(UHCI_USBCMD_EGSM));
			UHCI_DEBUG(KERN_DEBUG "[usb][pci:%I32p,io:%#Ix] Cannot enter "
			                      "uhci EGSM mode: there are changed ports\n",
			           self->uc_pci->pd_base, self->uc_base.uc_mmbase);
			return false;
		}
		self->uc_flags |= UHCI_CONTROLLER_FLAG_SUSPENDED;
		uhci_controller_egsm_enter_log(self);
	}
	return true;
}

LOCAL NOBLOCK void
NOTHROW(FCALL uhci_controller_egsm_leave)(struct uhci_controller *__restrict self) {
	if (self->uc_flags & UHCI_CONTROLLER_FLAG_SUSPENDED) {
		u16 cmd;
		uhci_controller_egsm_leave_log(self);
		cmd = uhci_rdw(self, UHCI_USBCMD);
		cmd &= ~UHCI_USBCMD_EGSM;
		uhci_wrw(self, UHCI_USBCMD, cmd);
		self->uc_flags &= ~UHCI_CONTROLLER_FLAG_SUSPENDED;
		COMPILER_WRITE_BARRIER();
		sig_broadcast(&self->uc_resdec);
	}
}

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_invcache)(struct uhci_controller *__restrict self,
                             u32 phys_addr) {
	/* XXX: Tell the UHCI controller to invalidate 4 bytes of physical memory at `phys_addr'? */
	(void)self;
	(void)phys_addr;
}




/* Remove a given QUEUE head `entry', that is pointed to by `pentry', from the chain. */
PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_osqh_unlink)(struct uhci_controller *__restrict self,
                                /*out_ref*/ REF struct uhci_osqh *__restrict entry,
                                struct uhci_osqh **__restrict pentry) {
	struct uhci_osqh *prev, *next;
	u32 hw_pointer;
	assert(sync_writing(&self->uc_lock));
	prev = container_of(pentry, struct uhci_osqh, qh_next);
	next = entry->qh_next;
	prev->qh_next = next;
	if (next) {
		/* Point to the next queue head. */
		assert(self->uc_qhlast != entry);
		hw_pointer = next->qh_self | UHCI_QHHP_QHTD;
	} else {
		assert(self->uc_qhlast == entry);
		if (self->uc_intreg) {
			/* Point back to the first interrupt handler polled every frame. */
			hw_pointer = self->uc_intreg->ui_td0_phys;
			/* Make sure to keep the qh-last pointer up to date. */
			self->uc_qhlast = prev != &self->uc_qhstart ? prev : NULL;
		} else if (prev != &self->uc_qhstart) {
			/* We may have been the last queue entry in line,
			 * but there are still other entires before us.
			 * As such, point back to the first queue entry. */
			assert(self->uc_qhstart.qh_next != NULL);
			hw_pointer = self->uc_qhstart.qh_self | UHCI_QHHP_QHTD;
			self->uc_qhlast = prev;
		} else {
			/* We ere the last queue entry, and there aren't
			 * even any interrupts handler left to-be called.
			 * As such, we can safely terminate the list. */
			hw_pointer = UHCI_QHHP_TERM;
			self->uc_qhlast = NULL;
		}
		if (self->uc_qhlast == NULL)
			sig_broadcast(&self->uc_resdec);
	}
	HW_WRITE(prev->qh_hp, hw_pointer);
	uhci_invcache(self, prev->qh_self + offsetof(struct uhci_osqh, qh_hp));
}

LOCAL NOBLOCK void
NOTHROW(FCALL uhci_osqh_append)(struct uhci_controller *__restrict self,
                                /*in_ref*/ REF struct uhci_osqh *__restrict osqh) {
	struct uhci_osqh *last;
	assert(sync_writing(&self->uc_lock));
	osqh->qh_next = NULL;
	last = self->uc_qhlast;
	self->uc_qhlast = osqh;
	if (last) {
		/* Append (or rather: insert) at the end. */
		osqh->qh_hp = last->qh_hp;
		assert(self->uc_qhstart.qh_next != NULL);
		/* Append at the end of the hardware list */
		HW_WRITE(last->qh_hp, osqh->qh_self | UHCI_QHHP_QHTD);
	} else {
		assert(self->uc_qhstart.qh_next == NULL);
		/* We're the first QUEU head to appear. */
		self->uc_qhstart.qh_next = osqh;
		/* Either point back to `uc_qhstart', or to the first interrupt. */
		osqh->qh_hp = self->uc_intreg ? self->uc_intreg->ui_td0_phys
		                              : self->uc_qhstart.qh_self | UHCI_QHHP_QHTD;
		/* Set the hardware link pointer to start the whole thing */
		HW_WRITE(self->uc_qhstart.qh_hp, osqh->qh_self | UHCI_QHHP_QHTD);
	}
	/* Make sure that EGSM isn't set, now that we've got something to do. */
	uhci_controller_egsm_leave(self);
}



LOCAL NOBLOCK void
NOTHROW(FCALL uhci_intreg_insert)(struct uhci_controller *__restrict self,
                                  /*in_ref*/ REF struct uhci_interrupt *__restrict ui) {
	/* Insert interrupts sorted by their number of hits, such that interrupts
	 * that get hit more often than others get triggered more often. */
	struct uhci_interrupt **pself, *next;
	size_t my_hitcount = ui->ui_hits;
	assert(sync_writing(&self->uc_lock));
	pself = &self->uc_intreg;
	while ((next = *pself) != NULL) {
		if (next->ui_hits <= my_hitcount)
			break; /* Insert before `next' */
		pself = &next->ui_reg.ife_next;
	}
	/* Insert into the list. */
	ui->ui_reg.ife_next = next;
	*pself = ui;
	/* Special case: The last TD of the last interrupt must point to `uc_qhstart' */
	if (!next) {
		*ui->ui_td1_next = self->uc_qhstart.qh_self | UHCI_TDLP_QHTD;
	} else {
		/* Have our last TD point to the first TD of the next interrupt. */
		assert(next->ui_td0_phys == (next->ui_qh ? next->ui_qh->qh_self | UHCI_QHHP_QHTD
		                                         : next->ui_reg.ife_tdsf->td_self));
		*ui->ui_td1_next = next->ui_td0_phys;
	}
	/* Special case: This is the first interrupt that will get executed
	 * In this case, we must have all ~empty~ frame lists entries point to it
	 * instead of pointing to `uc_qhstart'. Frame list entires that already
	 * contain pointers to isochronous interrupt handlers must be updated such
	 * that the last TD of the last isochronous interrupt handler points to
	 * the first TD of our interrupt */
	if (pself == &self->uc_intreg) {
		unsigned int i;
		assert(self->uc_intreg == ui);
		for (i = 0; i < 1024; ++i) {
			struct uhci_interrupt *intiso;
			intiso = self->uc_intiso[i];
			if (intiso) {
				struct uhci_interrupt_frameentry *ent;
				for (;;) {
					ent = intiso->ui_iso[i];
					assert(ent);
					if (!ent->ife_next)
						break;
					intiso = ent->ife_next;
				}
				HW_WRITE(ent->ife_tdsl->td_lp, ui->ui_td0_phys);
			} else {
				/* Simple case: Just have the frame list entry directly
				 * point at our interrupt handler! */
				HW_WRITE(self->uc_framelist[i], ui->ui_td0_phys);
			}
		}
	} else {
		struct uhci_interrupt *prev;
		/* Simple case: we've been inserted after an existing interrupt.
		 * In this case, we only have to update the next-pointer of the
		 * last TD of that preceding interrupt handler to point to us. */
		prev = container_of(pself, struct uhci_interrupt, ui_reg.ife_next);
		HW_WRITE(*prev->ui_td1_next, ui->ui_td0_phys);
	}
}

LOCAL NOBLOCK void
NOTHROW(FCALL uhci_intreg_unlink)(struct uhci_controller *__restrict self,
                                  struct uhci_interrupt **__restrict pui,
                                  /*out_ref*/ REF struct uhci_interrupt *__restrict ui) {
	/* Remove the given interrupt. */
	struct uhci_interrupt *next;
	u32 hw_next_pointer;
	assert(sync_writing(&self->uc_lock));
	assert(*pui == ui);
	/* Remove the interrupt from the software list. */
	next = ui->ui_reg.ife_next;
	*pui = next;
	if (next) {
		hw_next_pointer = next->ui_td0_phys;
	} else {
		/* Without a next-pointer, we're the last regular interrupt handler.
		 * As such, we must have the previous interrupt point to `uc_qhstart' */
		hw_next_pointer = self->uc_qhstart.qh_self | UHCI_QHHP_QHTD;
	}
	if (pui == &self->uc_intreg) {
		unsigned int i;
		/* Special case: Must update the pointers from all of the frame lists,
		 *               as well as all isochronous interrupt handlers. */
		uhci_controller_stop(self);
		COMPILER_WRITE_BARRIER();
		for (i = 0; i < 1024; ++i) {
			struct uhci_interrupt *intiso;
			intiso = self->uc_intiso[i];
			if (intiso) {
				struct uhci_interrupt_frameentry *ent;
				for (;;) {
					ent = intiso->ui_iso[i];
					assert(ent);
					if (!ent->ife_next)
						break;
					intiso = ent->ife_next;
				}
				assert(ent->ife_tdsf);
				assert(ent->ife_tdsl);
				assert(!ent->ife_tdsl->td_next);
				HW_WRITE(ent->ife_tdsl->td_lp, hw_next_pointer);
			} else {
				HW_WRITE(self->uc_framelist[i], hw_next_pointer);
			}
		}
		COMPILER_WRITE_BARRIER();
		uhci_controller_resume(self);
	} else {
		struct uhci_interrupt *prev;
		prev = container_of(pui, struct uhci_interrupt, ui_reg.ife_next);
		/* Invalidate the cache of the preceding next-pointer. */
		uhci_invcache(self,
		              prev->ui_qh ? prev->ui_qh->qh_self +
		                            offsetof(struct uhci_osqh, qh_hp)
		                          : prev->ui_reg.ife_tdsl->td_self +
		                            offsetof(struct uhci_ostd, td_lp));
	}
}



LOCAL NOBLOCK void
NOTHROW(FCALL uhci_intiso_insert)(struct uhci_controller *__restrict self,
                                  /*in_ref*/ REF struct uhci_interrupt *__restrict ui,
                                  unsigned int frameno) {
	u32 hw_next_pointer;
	struct uhci_interrupt_frameentry *ent;
	struct uhci_interrupt **pself, *next, *prev;
	assert(sync_writing(&self->uc_lock));
	ent = ui->ui_iso[frameno];
	assert(ent);
	/* Insert the new interrupt into the ISO vector. */
	pself = &self->uc_intiso[frameno];
	prev  = NULL;
	/* XXX: Select a different `pself'? */
	next          = *pself;
	ent->ife_next = next;
	*pself        = ui;
	/* Link the next pointer. */
	if (next) {
		/* Have our last TD point to the first TD of the next interrupt. */
		struct uhci_interrupt_frameentry *nent;
		assert(self->uc_iisocount != 0);
		nent = next->ui_iso[frameno];
		assert(nent);
		hw_next_pointer = nent->ife_tdsf->td_self;
	} else {
		assert(self->uc_iisocount == 0 ||
		       pself != &self->uc_intiso[frameno]);
		/* Must have our last TD point to either the
		 * first regular interrupt, or `uc_qhstart' */
		if (self->uc_intreg) {
			hw_next_pointer = self->uc_intreg->ui_td0_phys;
		} else {
			hw_next_pointer = self->uc_qhstart.qh_self | UHCI_QHHP_QHTD;
		}
	}
	ent->ife_tdsl->td_lp = hw_next_pointer;
	/* Insert our entry into the vector. */
	hw_next_pointer = ent->ife_tdsf->td_self;
	if (pself == &self->uc_intiso[frameno]) {
		assert(!prev);
		HW_WRITE(self->uc_framelist[frameno], hw_next_pointer);
	} else {
		struct uhci_interrupt_frameentry *pent;
		assert(prev);
		pent = prev->ui_iso[frameno];
		assert(pent);
		assert(pent->ife_tdsf);
		assert(pent->ife_tdsl);
		HW_WRITE(pent->ife_tdsl->td_lp, hw_next_pointer);
	}
	++self->uc_iisocount;
}

LOCAL NOBLOCK void
NOTHROW(FCALL uhci_intiso_unlink)(struct uhci_controller *__restrict self,
                                  struct uhci_interrupt *prev,
                                  /*out_ref*/ REF struct uhci_interrupt *__restrict ui,
                                  unsigned int frameno) {
	u32 hw_next_pointer, *phw_next_pointer, phw_next_pointer_addr;
	struct uhci_interrupt **pself, *next;
	struct uhci_interrupt_frameentry *ent;
	assert(sync_writing(&self->uc_lock));
	assert(self->uc_iisocount);
	assert(self->uc_intiso[frameno]);
	pself = &self->uc_intiso[frameno];
	if (prev != NULL)
		pself = &prev->ui_iso[frameno]->ife_next;
	assert(*pself == ui);
	ent = ui->ui_iso[frameno];
	assert(ent);
	next = ent->ife_next;
	/* Unlink from the software list. */
	*pself = next;
	if (next) {
		/* If we have a successor ISO interrupt, our
		 * hardware self-pointer must be updated to
		 * point to its first TD. */
		struct uhci_interrupt_frameentry *nent;
		nent = next->ui_iso[frameno];
		assert(nent);
		assert(nent->ife_tdsf);
		assert(nent->ife_tdsl);
		hw_next_pointer = nent->ife_tdsf->td_self;
	} else {
		/* Without a succeeding ISO interrupt, our
		 * hardware self-pointer must be updated to
		 * either point to the first regular interrupt,
		 * or simply point at `uc_qhstart'. */
		if (self->uc_intreg) {
			hw_next_pointer = self->uc_intreg->ui_td0_phys;
		} else {
			hw_next_pointer = self->uc_qhstart.qh_self | UHCI_QHHP_QHTD;
		}
	}
	/* Figure out where our hardware self-pointer is located at. */
	if (prev) {
		struct uhci_interrupt_frameentry *pent;
		struct uhci_ostd *tdsl;
		pent = prev->ui_iso[frameno];
		assert(pent);
		assert(pent->ife_tdsf);
		assert(pent->ife_tdsl);
		/* There is another ISO interrupt that is preceding us. */
		tdsl = pent->ife_tdsl;
		phw_next_pointer      = &tdsl->td_lp;
		phw_next_pointer_addr = tdsl->td_self + offsetof(struct uhci_ostd, td_lp);
	} else {
		/* Must directly modify the frame list. */
		phw_next_pointer      = &self->uc_framelist[frameno];
		phw_next_pointer_addr = self->uc_framelist_phys + frameno * 4;
	}
	/* Update our hardware self-pointer */
	COMPILER_WRITE_BARRIER();
	HW_WRITE(*phw_next_pointer, hw_next_pointer);
	COMPILER_WRITE_BARRIER();
	uhci_invcache(self, phw_next_pointer_addr);
	--self->uc_iisocount;
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
		if (!next) {
			if (prev != &ctrl->uc_qhstart)
				next = ctrl->uc_qhstart.qh_next;
		}
		hw_next_pointer = next ? next->qh_self | UHCI_QHHP_QHTD
		                       : UHCI_QHHP_TERM;
		if (ATOMIC_READ(osqh->qh_ep) & UHCI_QHEP_TERM) {
			/* The canceled operation was already completed.
			 * In this case, we don't need to stop the controller, since
			 * the unlinking process simply requires a cache invalidation. */
			HW_WRITE(prev->qh_hp, hw_next_pointer);
			uhci_invcache(ctrl, prev->qh_self + offsetof(struct uhci_osqh, qh_hp));
		} else {
			/* The operation was be in progress ~right now~
			 * -> Must stop the controller so that we can unlink it. */
			uhci_controller_stop(ctrl);
			HW_WRITE(prev->qh_hp, hw_next_pointer);
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

PRIVATE ATTR_NOINLINE NOBLOCK void
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
#ifdef UHCI_DEBUG_LOG_TD_COMPLETE
		UHCI_DEBUG(KERN_DEBUG "[usb][pci:%I32p,io:%#Ix] uhci:td:complete"
		                      " [actlen=%#I16x,maxlen=%#I16x,cs=%#I32x,tok=%#I32x]\n",
		           self->uc_pci->pd_base, self->uc_base.uc_mmbase,
		           actlen, maxlen, cs, td->td_tok);
#endif /* UHCI_DEBUG_LOG_TD_COMPLETE */
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
		if ((cs & (UHCI_TDCS_BSE | UHCI_TDCS_CRCTMO |
		           UHCI_TDCS_NAKR | UHCI_TDCS_BABBLE |
		           UHCI_TDCS_DBE | UHCI_TDCS_STALL |
		           UHCI_TDCS_ACTIVE)) != 0) {
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

PRIVATE NOBLOCK unsigned int
NOTHROW(FCALL uhci_int_do_invoke)(struct uhci_interrupt *__restrict ui,
                                  unsigned int status,
                                  void const *data, size_t datalen) {
	unsigned int result;
	uintptr_t intflags;
	intflags = ATOMIC_READ(ui->ui_flags);
	if unlikely(intflags & USB_INTERRUPT_FLAG_DELETED) {
do_stop:
		result = USB_INTERRUPT_HANDLER_RETURN_STOP;
	} else if (intflags & USB_INTERRUPT_FLAG_ISABLK) {
		REF struct basic_block_device *dev;
		dev = ((XATOMIC_WEAKLYREF(struct basic_block_device) *)&ui->ui_bind.ui_blk)->get();
		if unlikely(!dev)
			goto do_stop;
		result = (*ui->ui_handler)(dev, status, data, datalen);
		decref_unlikely(dev);
	} else {
		REF struct character_device *dev;
		dev = ((XATOMIC_WEAKLYREF(struct character_device) *)&ui->ui_bind.ui_chr)->get();
		if unlikely(!dev)
			goto do_stop;
		result = (*ui->ui_handler)(dev, status, data, datalen);
		decref_unlikely(dev);
	}
	return result;
}

PRIVATE ATTR_NOINLINE NOBLOCK unsigned int
NOTHROW(FCALL uhci_int_completed_ioerror)(struct uhci_interrupt *__restrict ui,
                                          void const *data, size_t datalen,
                                          error_code_t code,
                                          uintptr_t io_reason,
                                          uintptr_t pointer2 DFL(0)) {
	unsigned int result;
	struct exception_data odata;
	struct exception_data *mydat;
	mydat = error_data();
	odata = *mydat;
	memset(mydat, 0, sizeof(*mydat));
	mydat->e_code        = code;
	mydat->e_pointers[0] = E_IOERROR_SUBSYSTEM_USB;
	mydat->e_pointers[1] = io_reason;
	mydat->e_pointers[2] = pointer2;
	result = uhci_int_do_invoke(ui,
                                USB_INTERRUPT_HANDLER_STATUS_ERROR,
                                data,
                                datalen);
	*mydat = odata;
	return result;
}

PRIVATE NOBLOCK unsigned int
NOTHROW(FCALL uhci_int_completed)(struct uhci_controller *__restrict self,
                                  struct uhci_interrupt *__restrict ui,
                                  struct uhci_interrupt_frameentry *__restrict ent) {
	unsigned int result;
	struct uhci_ostd *td;
	size_t retsize = 0;
	/* Check for transfer errors. */
	for (td = ent->ife_tdsf; td; td = td->td_next) {
		u16 actlen, maxlen;
		u32 cs = ATOMIC_READ(td->td_cs);
		assert((td->td_next == NULL) == (td == ent->ife_tdsl));
		actlen = (cs + 1) & UHCI_TDCS_ACTLEN;
		maxlen = uhci_td_maxlen(td);
#ifdef UHCI_DEBUG_LOG_TD_COMPLETE
		UHCI_DEBUG(KERN_DEBUG "[usb][pci:%I32p,io:%#Ix] uhci:int:td:complete"
		                      " [actlen=%#I16x,maxlen=%#I16x,cs=%#I32x,tok=%#I32x]\n",
		           self->uc_pci->pd_base, self->uc_base.uc_mmbase,
		           actlen, maxlen, cs, td->td_tok);
#endif /* UHCI_DEBUG_LOG_TD_COMPLETE */
		/* Check for short packet */
		if (actlen < maxlen) {
			if unlikely(cs & UHCI_TDCS_SPD) {
				result = uhci_int_completed_ioerror(ui, ent->ife_buf, retsize,
				                                    ERROR_CODEOF(E_IOERROR_NODATA),
				                                    E_IOERROR_REASON_USB_SHORTPACKET);
				goto done;
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
				                    "uhci:int:td:incomplete packet (%I16u/%I16u) followed "
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
		retsize += actlen;
		assert(retsize <= ent->ife_bufsize);
		if ((cs & (UHCI_TDCS_BSE | UHCI_TDCS_CRCTMO |
		           UHCI_TDCS_NAKR | UHCI_TDCS_BABBLE |
		           UHCI_TDCS_DBE | UHCI_TDCS_STALL |
		           UHCI_TDCS_ACTIVE)) != 0) {
			result = uhci_int_completed_ioerror(ui, ent->ife_buf, retsize,
			                                    ERROR_CODEOF(E_IOERROR_ERRORBIT),
			                                    E_IOERROR_REASON_UHCI_TDCS,
			                                    cs);
			goto done;
		}
	}
	assert(retsize <= ent->ife_bufsize);
	result = uhci_int_do_invoke(ui, USB_INTERRUPT_HANDLER_STATUS_OK,
	                            ent->ife_buf, retsize);
done:
	return result;
}

LOCAL NOBLOCK void
NOTHROW(FCALL uhci_reset_int)(struct uhci_interrupt *__restrict ui,
                              struct uhci_interrupt_frameentry *__restrict ent) {
	struct uhci_ostd *td;
	td = ent->ife_tdsf;
	do {
		assert((td->td_next == NULL) ==
		       (td == ent->ife_tdsl));
		td->td_cs = ui->ui_initcs;
	} while ((td = td->td_next) != NULL);
	ent->ife_tdsl->td_cs |= UHCI_TDCS_IOC;
}

LOCAL NOBLOCK void
NOTHROW(FCALL uhci_update_d_bit)(struct uhci_interrupt *__restrict ui,
                                 struct uhci_interrupt_frameentry *__restrict ent) {
	if (ui->ui_flags & UHCI_INTERRUPT_FLAG_FLIPDBIT) {
		struct uhci_ostd *td;
		td = ent->ife_tdsf;
		do {
			assert((td->td_next == NULL) ==
			       (td == ent->ife_tdsl));
			td->td_tok ^= UHCI_TDTOK_DTOGGM;
		} while ((td = td->td_next) != NULL);
		/* Also update the data-toggle bit of the endpoint. */
		ui->ui_endp->ue_flags ^= USB_ENDPOINT_FLAG_DATATOGGLE;
	}
}

LOCAL NOBLOCK struct uhci_interrupt **
NOTHROW(FCALL uhci_finish_intreg)(struct uhci_controller *__restrict self,
                                  struct uhci_interrupt **__restrict pui,
                                  struct uhci_interrupt *__restrict ui) {
	u32 cs;
	struct uhci_osqh *qh;
	struct uhci_ostd *td;
	unsigned int restart_mode;
	assert(ui->ui_reg.ife_tdsf);
	assert(ui->ui_reg.ife_tdsl);
	if ((qh = ui->ui_qh) != NULL) {
		/* This one uses a queue-head, meaning we can just check if the QH has been filled. */
		u32 ep = ATOMIC_READ(qh->qh_ep);
		if (ep & UHCI_QHEP_TERM) {
			/* This queue has completed */
			restart_mode = uhci_int_completed(self, ui, &ui->ui_reg);
			goto done_qh;
		}
		/* Find the TD that is currently being executed. */
		td = uhci_ostd_findphys(ui->ui_reg.ife_tdsf, ep);
		if unlikely(!td) {
			/* Shouldn't happen... */
			printk(KERN_CRIT "[usb][pci:%I32p,io:%#Ix] uhci:int:bad:ep (%#I32p)\n",
			       self->uc_pci->pd_base, self->uc_base.uc_mmbase, ep);
			HW_WRITE(qh->qh_ep, UHCI_QHEP_TERM);
			restart_mode = uhci_int_completed_ioerror(ui, NULL, 0,
			                                          ERROR_CODEOF(E_IOERROR_NODATA),
			                                          E_IOERROR_REASON_UHCI_BADEP,
			                                          ep);
			goto done_qh;
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
					printk(KERN_ERR "[usb][pci:%I32p,io:%#Ix] uhci:int:short-packet (%I16u < %I16u)\n",
					       self->uc_pci->pd_base, self->uc_base.uc_mmbase, actlen, maxlen);
					restart_mode = uhci_int_completed_ioerror(ui, NULL, 0,
					                                          ERROR_CODEOF(E_IOERROR_NODATA),
					                                          E_IOERROR_REASON_USB_SHORTPACKET);
					goto done_qh;
				}
			}
		}
		/* Check for error bits (regardless of the state of ACTIVE). */
		if (cs & (UHCI_TDCS_BSE | UHCI_TDCS_CRCTMO |
		          UHCI_TDCS_NAKR | UHCI_TDCS_BABBLE |
		          UHCI_TDCS_DBE | UHCI_TDCS_STALL)) {
			printk(KERN_ERR "[usb][pci:%I32p,io:%#Ix] uhci:int:error (cs=%#I32x,tok=%#I32x)\n",
			       self->uc_pci->pd_base, self->uc_base.uc_mmbase, cs, ATOMIC_READ(td->td_tok));
			restart_mode = uhci_int_completed_ioerror(ui, NULL, 0,
			                                          ERROR_CODEOF(E_IOERROR_ERRORBIT),
			                                          E_IOERROR_REASON_UHCI_TDCS,
			                                          cs);
			goto done_qh;
		}
		if (!(cs & UHCI_TDCS_ACTIVE)) {
			printk(KERN_ERR "[usb][pci:%I32p,io:%#Ix] uhci:int:inactive for unknown reason\n",
			       self->uc_pci->pd_base, self->uc_base.uc_mmbase);
			restart_mode = uhci_int_completed_ioerror(ui, NULL, 0,
			                                          ERROR_CODEOF(E_IOERROR_NODATA),
			                                          E_IOERROR_REASON_UHCI_INCOMPLETE);
			goto done_qh;
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
		if (td->td_lp & UHCI_TDLP_DBS) {
			/* Depth-first -> Later QHs havn't been touched, yet
			 * As such, skip all the way to the very end. */
			while (ui->ui_reg.ife_next)
				ui = ui->ui_reg.ife_next;
		}
		goto do_next;
done_qh:
		if unlikely(restart_mode == USB_INTERRUPT_HANDLER_RETURN_STOP)
			goto do_unlink;
		/* Reset the interrupt. */
		uhci_reset_int(ui, &ui->ui_reg);
		uhci_update_d_bit(ui, &ui->ui_reg);
		/* Reset the initial TD pointer of the interrupt handler. */
		COMPILER_WRITE_BARRIER();
		HW_WRITE(qh->qh_ep, ui->ui_reg.ife_tdsf->td_self);
		COMPILER_WRITE_BARRIER();
	} else {
		/* Without QH. Check the first TD for completion/error. */
		td = ui->ui_reg.ife_tdsf;
		assert(td);
		assert((td->td_next == NULL) == (td == ui->ui_reg.ife_tdsl));
		cs = ATOMIC_READ(ui->ui_reg.ife_tdsf->td_cs);
		if (!(cs & UHCI_TDCS_ACTIVE)) {
			/* NOTE: `uhci_int_completed()' also checks for errors! */
			restart_mode = uhci_int_completed(self, ui, &ui->ui_reg);
			goto done_nqh;
		}
		/* Check for error bits. */
		if (cs & (UHCI_TDCS_BSE | UHCI_TDCS_CRCTMO |
		          UHCI_TDCS_NAKR | UHCI_TDCS_BABBLE |
		          UHCI_TDCS_DBE | UHCI_TDCS_STALL)) {
			printk(KERN_ERR "[usb][pci:%I32p,io:%#Ix] uhci:int:error (cs=%#I32x,tok=%#I32x)\n",
			       self->uc_pci->pd_base, self->uc_base.uc_mmbase, cs, ATOMIC_READ(td->td_tok));
			restart_mode = uhci_int_completed_ioerror(ui, NULL, 0,
			                                          ERROR_CODEOF(E_IOERROR_ERRORBIT),
			                                          E_IOERROR_REASON_UHCI_TDCS,
			                                          cs);
			goto done_nqh;
		}
		goto do_next;
done_nqh:
		if unlikely(restart_mode == USB_INTERRUPT_HANDLER_RETURN_STOP)
			goto do_unlink;
		/* Reset the interrupt. */
		{
			struct uhci_ostd *td;
			td = ui->ui_reg.ife_tdsf;
			cs = ui->ui_initcs;
			if likely(td == ui->ui_reg.ife_tdsl) {
				HW_WRITE(td->td_cs, cs | UHCI_TDCS_IOC);
			} else {
				do {
					assert((td->td_next == NULL) ==
					       (td == ui->ui_reg.ife_tdsl));
					if (!td->td_next)
						cs |= UHCI_TDCS_IOC;
					HW_WRITE(td->td_cs, cs);
				} while ((td = td->td_next) != NULL);
			}
		}
	}
do_next:
	return &ui->ui_reg.ife_next;
do_unlink:
	uhci_intreg_unlink(self, pui, ui);
	return pui;
}

/* Returns NULL if the entry was deleted.
 * Otherwise, return the self-pointer of the next entry. */
LOCAL NOBLOCK struct uhci_interrupt **
NOTHROW(FCALL uhci_finish_intiso)(struct uhci_controller *__restrict self,
                                  struct uhci_interrupt *prev,
                                  struct uhci_interrupt *__restrict ui,
                                  unsigned int frameno) {
	u32 cs;
	struct uhci_interrupt_frameentry *ent;
	ent = ui->ui_iso[frameno];
	assert(ent);
	assert(ent->ife_tdsf);
	assert(ent->ife_tdsl);
	cs = ATOMIC_READ(ent->ife_tdsl->td_cs);
	kernel_panic("TODO");
	(void)cs;
	if (0) {
		uhci_intiso_unlink(self, prev, ui, frameno);
		decref(ui);
		return NULL;
	}
	return &ent->ife_next;
}

LOCAL NOBLOCK void
NOTHROW(FCALL uhci_finish_completed_iso)(struct uhci_controller *__restrict self,
                                         unsigned int frameno) {
	struct uhci_interrupt *prev, **piter, *iter;
	iter = self->uc_intiso[frameno];
	if (!iter)
		return;
	piter = &self->uc_intiso[frameno];
	prev  = NULL;
	for (;;) {
		struct uhci_interrupt **pnext;
		pnext = uhci_finish_intiso(self,
		                           prev,
		                           iter,
		                           frameno);
		if (pnext) {
			prev  = iter;
			piter = pnext;
		}
		iter = *piter;
		if (!iter)
			break;
	}
}

PRIVATE NOBLOCK void
NOTHROW(FCALL uhci_finish_completed)(struct uhci_controller *__restrict self) {
	struct uhci_osqh **piter, *iter;
	assert(sync_writing(&self->uc_lock));

	/* When isochronous interrupts are being used, check if any of them have gotten data. */
	if (self->uc_iisocount != 0) {
		u16 i, frcurr;
		frcurr = uhci_rdw(self, UHCI_FRNUM) & 1023;
		if (frcurr > self->uc_framelast) {
			for (i = frcurr; i < self->uc_framelast; ++i)
				uhci_finish_completed_iso(self, i);
		} else if (frcurr < self->uc_framelast) {
			for (i = self->uc_framelast; i < 1024; ++i)
				uhci_finish_completed_iso(self, i);
			for (i = 0; i < frcurr; ++i)
				uhci_finish_completed_iso(self, i);
		} else {
			for (i = 0; i < 1024; ++i)
				uhci_finish_completed_iso(self, i);
		}
		self->uc_framelast = frcurr;
	}

	/* Check if any of the regular interrupts have gotten data. */
	if (self->uc_intreg != NULL) {
		struct uhci_interrupt **piter, *iter;
		piter = &self->uc_intreg;
		iter  = *piter;
		do {
			piter = uhci_finish_intreg(self, piter, iter);
		} while ((iter = *piter) != NULL);
	}

	/* Check if any of the one-time command lists have been completed. */
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
		if (cs & (UHCI_TDCS_BSE | UHCI_TDCS_CRCTMO |
		          UHCI_TDCS_NAKR | UHCI_TDCS_BABBLE |
		          UHCI_TDCS_DBE | UHCI_TDCS_STALL)) {
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
NOTHROW(FCALL uhci_interrupt_handler)(void *arg) {
	u16 status, ack;
	struct uhci_controller *self;
	self = (struct uhci_controller *)arg;
	status = uhci_rdw(self, UHCI_USBSTS);
	ack    = 0;
	if (status & (UHCI_USBSTS_USBINT | UHCI_USBSTS_ERROR |
	              UHCI_USBSTS_RD | UHCI_USBSTS_HSE |
	              UHCI_USBSTS_HCPE | UHCI_USBSTS_HCH)) {
		/* Remember that we've just gotten an interrupt. */
		atomic64_write(&self->uc_lastint, jiffies);
	}
	if unlikely(status & UHCI_USBSTS_HSE) {
		printk(KERN_CRIT "[usb][pci:%I32p,io:%#Ix] uhci:Host-System-Error set (status=%#I8x)\n",
		       self->uc_pci->pd_base, self->uc_base.uc_mmbase, status);
		/* XXX: Do something more? */
		uhci_wrw(self, UHCI_USBSTS, UHCI_USBSTS_HSE);
		ack |= UHCI_USBSTS_HSE;
	}
	if unlikely(status & UHCI_USBSTS_HCPE) {
		printk(KERN_CRIT "[usb][pci:%I32p,io:%#Ix] uhci:Host-Controller-Process-Error set (status=%#I8x)\n",
		       self->uc_pci->pd_base, self->uc_base.uc_mmbase, status);
		/* XXX: Do something more? */
		uhci_wrw(self, UHCI_USBSTS, UHCI_USBSTS_HCPE);
		ack |= UHCI_USBSTS_HCPE;
	}
	if (status & (UHCI_USBSTS_USBINT | UHCI_USBSTS_ERROR)) {
#ifdef UHCI_DEBUG_LOG_INTERRUPT
		UHCI_DEBUG(KERN_TRACE "[usb][pci:%I32p,io:%#Ix] uhci interrupt (status=%#I8x)\n",
		           self->uc_pci->pd_base, self->uc_base.uc_mmbase, status);
#endif /* UHCI_DEBUG_LOG_INTERRUPT */
		uhci_wrw(self, UHCI_USBSTS, status & (UHCI_USBSTS_USBINT | UHCI_USBSTS_ERROR));
		ack |= status & (UHCI_USBSTS_USBINT | UHCI_USBSTS_ERROR);
		/* One of two things happened:
		 *  - A TD with the IOC bit was finished
		 *  - Some TD got one of its error bits set. */
		if (!sync_trywrite(&self->uc_lock)) {
			/* Whoever is holding the lock must handle this interrupt, then... */
			ATOMIC_FETCHOR(self->uc_flags, UHCI_CONTROLLER_FLAG_INTERRUPTED);
			/* Try to acquire the lock again, so the `UHCI_CONTROLLER_FLAG_INTERRUPTED'
			 * flag becomes interlocked on our end. */
			if (!sync_trywrite(&self->uc_lock))
				goto done_tdint;
			ATOMIC_FETCHAND(self->uc_flags, ~UHCI_CONTROLLER_FLAG_INTERRUPTED);
		}
		uhci_finish_completed(self);
		/* No need to use `uhci_controller_unlock()' here. - We're the only place
		 * that could ever set the `UHCI_CONTROLLER_FLAG_INTERRUPTED' bit, so we
		 * know that no additional interrupt could happen after we release this
		 * lock! */
		sync_endwrite(&self->uc_lock);
	}
done_tdint:
	if (status & UHCI_USBSTS_RD) {
		UHCI_DEBUG(KERN_TRACE "[usb][pci:%I32p,io:%#Ix] uhci:Resume-Detect (status=%#I8x)\n",
		           self->uc_pci->pd_base, self->uc_base.uc_mmbase, status);
		if (!(ATOMIC_FETCHOR(self->uc_flags, UHCI_CONTROLLER_FLAG_RESDECT) & UHCI_CONTROLLER_FLAG_RESDECT))
			sig_broadcast(&self->uc_resdec);
		uhci_wrw(self, UHCI_USBSTS, UHCI_USBSTS_RD);
		ack |= UHCI_USBSTS_RD;
	}
	if unlikely(!ack) {
		printk(KERN_TRACE "[usb][pci:%I32p,io:%#Ix] uhci sporadic (status=%#I8x)\n",
		       self->uc_pci->pd_base, self->uc_base.uc_mmbase, status);
		return false;
	}
	return true;
}




PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL uhci_fini)(struct character_device *__restrict self) {
	struct uhci_controller *me;
	REF struct uhci_interrupt *iter, *next;
	unsigned int i;
	me = (struct uhci_controller *)self;

	/* Destroy the power control descriptor and thread. */
	if (me->uc_powerctl_desc) {
		xatomic_weaklyref_clear(&me->uc_powerctl_desc->up_ctrl);
		decref_unlikely(me->uc_powerctl_desc);
	}
	if (me->uc_powerctl_thrd) {
		decref(me->uc_powerctl_thrd);
		/* In (the likely) case that the power controller was
		 * waiting for something to happen, wake it up. */
		sig_broadcast(&me->uc_resdec);
	}

	/* Make sure that the controller is stopped. */
	if (me->uc_base.uc_mmbase != NULL)
		uhci_wrw(me, UHCI_USBCMD, 0);

	isr_unregister(&uhci_interrupt_handler, me); /* FIXME: This one can cause exceptions... */
	iter = me->uc_intreg;
	while (iter) {
		assert(!(iter->ui_flags & UHCI_INTERRUPT_FLAG_ISOCHRONOUS));
		next = iter->ui_reg.ife_next;
		decref(iter);
		iter = next;
	}
	for (i = 0; i < 1024; ++i) {
		iter = me->uc_intiso[i];
		while (iter) {
			assert(iter->ui_flags & UHCI_INTERRUPT_FLAG_ISOCHRONOUS);
			assert(iter->ui_iso[i]);
			next = iter->ui_iso[i]->ife_next;
			decref(iter);
			iter = next;
		}
	}
	if (me->uc_framelist)
		vpage_free(me->uc_framelist, 1);
}

/* Schedule the given queue for execution. */
PUBLIC void FCALL
uhci_controller_addqueue(struct uhci_controller *__restrict self,
                         REF struct uhci_osqh *__restrict osqh)
		THROWS(E_WOULDBLOCK) {
	sync_write(&self->uc_lock);
	uhci_osqh_append(self, osqh);
	uhci_controller_endwrite(self);
}

/* Construct new TDs for  */
#if __SIZEOF_VM_PHYS_T__ > 4
LOCAL bool KCALL
#else /* __SIZEOF_VM_PHYS_T__ > 4 */
LOCAL void KCALL
#endif /* __SIZEOF_VM_PHYS_T__ <= 4 */
uhci_construct_tds(struct uhci_ostd ***__restrict ppnexttd,
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

PRIVATE NONNULL((1, 2, 3)) void KCALL
uhci_transfer(struct usb_controller *__restrict self,
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
PRIVATE NONNULL((1, 2)) size_t KCALL
uhci_transfer_sync_with_phys(struct uhci_controller *__restrict self,
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
			uhci_transfer(self, tx_firstcopy, &aio);
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
PRIVATE NONNULL((1, 2, 3)) void KCALL
uhci_transfer(struct usb_controller *__restrict self,
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
	aio_handle_init(aio, &uhci_aio_type);
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
					if unlikely(!uhci_construct_tds(&pnexttd,
					                                tx_iter->ut_endp,
					                                tx_iter,
					                                tx_iter->ut_bufp,
					                                tx_iter->ut_buflen))
						goto cleanup_configured_and_do_syncio;
#else /* __SIZEOF_VM_PHYS_T__ > 4 */
					uhci_construct_tds(&pnexttd,
					                   tx_iter->ut_endp,
					                   tx_iter,
					                   tx_iter->ut_bufp,
					                   tx_iter->ut_buflen);
#endif /* __SIZEOF_VM_PHYS_T__ <= 4 */
					break;

				case USB_TRANSFER_BUFTYP_PHYSVEC: {
					struct aio_pbuffer_entry ent;
					AIO_PBUFFER_FOREACH(ent, tx_iter->ut_vbufp) {
#if __SIZEOF_VM_PHYS_T__ > 4
						if unlikely(!uhci_construct_tds(&pnexttd,
						                                tx_iter->ut_endp,
						                                tx_iter,
						                                ent.ab_base,
						                                ent.ab_size))
							goto cleanup_configured_and_do_syncio;
#else /* __SIZEOF_VM_PHYS_T__ > 4 */
						uhci_construct_tds(&pnexttd,
						                   tx_iter->ut_endp,
						                   tx_iter,
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
		transfer_size = uhci_transfer_sync_with_phys(me, tx);
		/* Still always propagate the total number of transferred bytes. */
		aio->ah_data[0] = (void *)transfer_size;
		aio_handle_init(aio, &uhci_aio_sync_type);
	}
	aio_handle_success(aio);
}


PRIVATE NOBLOCK void
NOTHROW(KCALL uhci_interrupt_frameentry_fini)(struct uhci_interrupt_frameentry *__restrict self) {
	struct uhci_ostd *td_iter, *td_next;
	assert(self->ife_tdsf != NULL);
	assert(self->ife_tdsl != NULL);
	/* Free the transfer buffer. */
	if ((self->ife_bufsize & ~1) != 0) {
		if (self->ife_bufsize & 1) {
			assert(IS_ALIGNED((uintptr_t)self->ife_buf, PAGESIZE));
			assert(IS_ALIGNED((uintptr_t)self->ife_bufsize - 1, PAGESIZE));
			vpage_free_untraced(self->ife_buf, self->ife_bufsize / PAGESIZE);
		} else {
			heap_free_untraced(&kernel_locked_heap,
			                   self->ife_buf,
			                   self->ife_bufsize,
			                   GFP_LOCKED);
		}
	}
	td_iter = self->ife_tdsf;
	do {
		td_next = td_iter->td_next;
		assert((td_next == NULL) == (td_iter == self->ife_tdsl));
		uhci_ostd_free(td_iter);
	} while ((td_iter = td_next) != NULL);
}

PRIVATE NOBLOCK void
NOTHROW(KCALL uhci_interrupt_fini)(struct usb_interrupt *__restrict self) {
	struct uhci_interrupt *me;
	me = (struct uhci_interrupt *)self;
	/* Free allocated TD descriptors. */
	if (me->ui_flags & UHCI_INTERRUPT_FLAG_ISOCHRONOUS) {
		unsigned int i;
		for (i = 0; i < 1024; ++i) {
			if (me->ui_iso[i])
				uhci_interrupt_frameentry_fini(me->ui_iso[i]);
		}
	} else {
		if (me->ui_qh)
			uhci_osqh_free(me->ui_qh);
		uhci_interrupt_frameentry_fini(&me->ui_reg);
	}
}



/* Construct TD descriptors. */
LOCAL void KCALL
uhci_construct_tds_for_interrupt(struct uhci_ostd ***__restrict ppnexttd,
                                 u32 *__restrict ptok, u32 cs, u16 maxpck,
                                 vm_phys_t start, size_t num_bytes) {
#if __SIZEOF_VM_PHYS_T__ > 4
	assert(!(num_bytes != 0 &&
	         (start > (vm_phys_t)0xffffffff ||
	          (start + num_bytes) > (vm_phys_t)0xffffffff)));
#endif /* __SIZEOF_VM_PHYS_T__ > 4 */
	/* Construct TD entires of up to `endp->ue_maxpck' bytes. */
	do {
		u16 mysize;
		struct uhci_ostd *td;
		td = uhci_ostd_alloc();
		**ppnexttd = td;
		*ppnexttd = &td->td_next;
		mysize = maxpck;
		if ((size_t)mysize > num_bytes)
			mysize = (u16)num_bytes;
		td->td_cs  = cs;
		td->td_tok = *ptok;
		td->td_tok |= ((mysize - 1) << UHCI_TDTOK_MAXLENS) & UHCI_TDTOK_MAXLENM;
		td->td_buf = (u32)start;
		*ptok ^= UHCI_TDTOK_DTOGGM;
		start     += mysize;
		num_bytes -= mysize;
	} while (num_bytes);
}


PRIVATE void KCALL
uhci_interrupt_frameentry_init(struct uhci_interrupt_frameentry *__restrict self,
                               u32 *__restrict ptok, u32 cs, u16 maxpck,
                               size_t buflen) {
	struct uhci_ostd **pnexttd, *td_iter;
	pnexttd = &self->ife_tdsf;
	if likely(buflen < PAGESIZE) {
		struct heapptr ptr;
		size_t min_align;
		vm_phys_t addr;
		min_align = 1;
		while (min_align < buflen)
			min_align <<= 1;
		assert(min_align >= buflen);
		ptr = heap_align_untraced(&kernel_locked_heap,
		                          min_align, 0, buflen,
		                          GFP_LOCKED | GFP_PREFLT); /* TODO: GFP_32BIT */
		/* Access the allocated memory at least once to ensure that it was faulted. */
		COMPILER_WRITE_BARRIER();
		*(u8 *)ptr.hp_ptr = 0;
		COMPILER_WRITE_BARRIER();
		addr = pagedir_translate((vm_virt_t)ptr.hp_ptr);
		TRY {
			uhci_construct_tds_for_interrupt(&pnexttd,
			                                 ptok, cs, maxpck,
			                                 addr, buflen);
		} EXCEPT {
			heap_free_untraced(&kernel_locked_heap,
			                   ptr.hp_ptr,
			                   ptr.hp_siz,
			                   GFP_LOCKED);
			RETHROW();
		}
		self->ife_buf     = ptr.hp_ptr;
		self->ife_bufsize = ptr.hp_siz;
	} else {
		/* Large buffer. */
		size_t i, num_pages;
		void *buf;
		num_pages = CEILDIV(buflen, PAGESIZE);
		/* NOTE: Unlink the heap allocation functions, vpage_alloc() is guarantied to
		 *       respect the `GFP_PREFLT' flag, so we don't even have to touch allocated
		 *       page in order to ensure that it got faulted. */
		buf = vpage_alloc_untraced(num_pages, 1,
		                           GFP_LOCKED | GFP_PREFLT); /* TODO: GFP_32BIT */
		assert(IS_ALIGNED((uintptr_t)self->ife_buf, PAGESIZE));
		TRY {
			i = 0;
			while (i < num_pages) {
				vm_ppage_t start;
				size_t num_cont, num_remaining;
				size_t maxlen;
				num_cont      = 1;
				num_remaining = num_pages - i;
				start = VM_ADDR2PAGE(pagedir_translate((vm_virt_t)((byte_t *)buf + i * PAGESIZE)));
				while (num_remaining &&
				       VM_ADDR2PAGE(pagedir_translate((vm_virt_t)((byte_t *)buf + (i + num_cont) * PAGESIZE))) ==
				       start + num_cont) {
					++num_cont;
					--num_remaining;
				}
				maxlen = num_cont * PAGESIZE;
				if (!num_remaining) {
					size_t remaning_bytes;
					assert(i + num_cont == num_pages);
					assert(buflen > (i * PAGESIZE));
					remaning_bytes = buflen - (i * PAGESIZE);
					if (maxlen < remaning_bytes)
						maxlen = remaning_bytes;
				}
				uhci_construct_tds_for_interrupt(&pnexttd,
				                                 ptok, cs, maxpck,
				                                 VM_PPAGE2ADDR(start),
				                                 maxlen);
				i += num_cont;
			}
		} EXCEPT {
			vpage_free_untraced(buf, num_pages);
			RETHROW();
		}
		self->ife_buf     = buf;
		self->ife_bufsize = (num_pages * PAGESIZE) | 1; /* least significant bit: vpage-based buffer. */
	}
	assert(pnexttd != &self->ife_tdsf);
	*pnexttd = NULL;
	assert(self->ife_tdsf != NULL);
	self->ife_tdsl = container_of(pnexttd, struct uhci_ostd, td_next);
	self->ife_tdsl->td_lp   = UHCI_TDLP_TERM;
	self->ife_tdsl->td_cs  |= UHCI_TDCS_IOC;
	assert(self->ife_tdsl->td_next == NULL);

	for (td_iter = self->ife_tdsf; td_iter != self->ife_tdsl;) {
		struct uhci_ostd *td_next;
		td_next = td_iter->td_next;
		/* Link up the hardware TD pointer chain. */
		td_iter->td_lp = td_next->td_self;
		td_iter = td_next;
	}
}

LOCAL NOBLOCK size_t
NOTHROW(FCALL uhci_count_tds)(struct uhci_ostd *__restrict first) {
	size_t result = 1;
	while ((first = first->td_next) != NULL)
		++result;
	return result;
}

LOCAL NOBLOCK size_t
NOTHROW(FCALL uhci_count_tds_in_isoint)(struct uhci_interrupt *first,
                                        unsigned int frameno) {
	size_t result = 0;
	while (first) {
		struct uhci_interrupt_frameentry *ent;
		ent = first->ui_iso[frameno];
		assert(ent);
		assert(ent->ife_tdsf);
		assert(ent->ife_tdsl);
		assert(ent->ife_tdsl->td_next == NULL);
		result += uhci_count_tds(ent->ife_tdsf);
		first = ent->ife_next;
	}
	return result;
}

LOCAL NOBLOCK size_t
NOTHROW(FCALL uhci_count_isotds_for_interval_and_offset)(struct uhci_controller *__restrict self,
                                                         unsigned int offset,
                                                         unsigned int interval) {
	size_t result = 0;
	unsigned int i;
	for (i = offset; i < 1024; i += interval) {
		result += uhci_count_tds_in_isoint(self->uc_intiso[i], i);
	}
	return result;
}



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
PRIVATE WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3, 4)) REF struct usb_interrupt *KCALL
uhci_register_interrupt(struct usb_controller *__restrict self, struct usb_endpoint *__restrict endp,
                        PUSB_INTERRUPT_HANDLER handler, void *__restrict character_or_block_device,
                        size_t buflen, uintptr_t flags, unsigned int poll_interval_in_milliseconds) {
	struct uhci_controller *me;
	unsigned int interval = 1;
	unsigned int frame_hits = 1;
	REF struct uhci_interrupt *result;
	assert(!(flags & (USB_INTERRUPT_FLAG_ISACHR |
	                  USB_INTERRUPT_FLAG_ISABLK |
	                  USB_INTERRUPT_FLAG_SHORT |
	                  USB_INTERRUPT_FLAG_EVENPERIOD)));
	if (flags & UHCI_INTERRUPT_FLAG_ISOCHRONOUS) {
		/* Figure out how often the poll should happen. */
		unsigned int i;
		interval = poll_interval_in_milliseconds;
		if (interval >= 1024)
			interval = 1024;
		if (interval < 1024 && (flags & USB_INTERRUPT_FLAG_EVENPERIOD)) {
			for (interval = 1; interval <= poll_interval_in_milliseconds; interval <<= 1)
				;
			interval >>= 1; /* One less. */
			assert(interval <= poll_interval_in_milliseconds);
			assert(interval <= 1024);
			assert(interval >= 1);
		}
		/* Duplicate the TD chain for every secondary frame that's going to be executed. */
		for (i = interval; i < 1024; i += interval)
			++frame_hits;
		if (!(flags & USB_INTERRUPT_FLAG_EVENPERIOD)) {
			/* Remove the last period if it overlaps at least half with the next period. */
			unsigned int overflow = i - 1024;
			if (overflow >= interval / 2)
				--frame_hits;
		}
	}

	me = (struct uhci_controller *)self;
	if (poll_interval_in_milliseconds != 0)
		flags |= UHCI_INTERRUPT_FLAG_ISOCHRONOUS;
	result = (REF struct uhci_interrupt *)kmalloc(flags & UHCI_INTERRUPT_FLAG_ISOCHRONOUS
	                                              ? (offsetof(struct uhci_interrupt, ui_isobuf) +
	                                                 (frame_hits * sizeof(struct uhci_interrupt_frameentry)))
	                                              : offsetafter(struct uhci_interrupt, ui_hits),
	                                              GFP_LOCKED | GFP_CALLOC | GFP_PREFLT);
	result->ui_refcnt  = 1;
	result->ui_fini    = &uhci_interrupt_fini;
	result->ui_flags   = flags;
	result->ui_endp    = incref(endp);
	result->ui_handler = handler;
	xatomic_weaklyref_cinit(&result->ui_bind.ui_blk,
	                        (struct block_device *)character_or_block_device);
	TRY {
		u32 tok, orig_tok, cs;
		u16 maxpck;
		STATIC_ASSERT(offsetof(struct uhci_interrupt, ui_reg) ==
		              offsetof(struct uhci_interrupt, ui_iso[0]));
		tok = UHCI_TDTOK_PID_IN;
		tok |= ((u32)endp->ue_dev << UHCI_TDTOK_DEVS) & UHCI_TDTOK_DEVM;
		tok |= ((u32)endp->ue_endp << UHCI_TDTOK_ENDPTS) & UHCI_TDTOK_ENDPTM;
#if USB_ENDPOINT_FLAG_DATATOGGLE == 1
		tok |= ((endp->ue_flags & USB_ENDPOINT_FLAG_DATATOGGLE) << UHCI_TDTOK_DTOGGS);
#else /* USB_ENDPOINT_FLAG_DATATOGGLE == 1 */
		tok |= (endp->ue_flags & USB_ENDPOINT_FLAG_DATATOGGLE) ? UHCI_TDTOK_DTOGGM : 0;
#endif /* USB_ENDPOINT_FLAG_DATATOGGLE != 1 */
		orig_tok = tok;
		cs = UHCI_TDCS_ACTIVE | ((3 << UHCI_TDCS_ERRCNTS) & UHCI_TDCS_ERRCNTM);
		if (endp->ue_flags & USB_ENDPOINT_FLAG_LOWSPEED)
			cs |= UHCI_TDCS_LSD;
		if (!(flags & USB_INTERRUPT_FLAG_SHORT))
			cs |= UHCI_TDCS_SPD;
		if (flags & UHCI_INTERRUPT_FLAG_ISOCHRONOUS)
			cs |= UHCI_TDCS_IOS;
		result->ui_initcs = cs;
		maxpck = endp->ue_maxpck;
		if (flags & UHCI_INTERRUPT_FLAG_ISOCHRONOUS) {
			/* Figure out how often the poll should happen. */
			unsigned int i, n;
			uhci_interrupt_frameentry_init(&result->ui_isobuf[0], &tok, cs, maxpck, buflen);
			result->ui_iso[0] = &result->ui_isobuf[0];
			/* Duplicate the TD chain for every secondary frame that's going to be executed. */
			for (n = 1, i = interval; n < frame_hits; ++n, i += interval) {
				struct uhci_interrupt_frameentry *ent;
				assert(i < 1024);
				ent = &result->ui_isobuf[n];
				uhci_interrupt_frameentry_init(ent, &tok, cs, maxpck, buflen);
				result->ui_iso[i] = ent;
			}
		} else {
			uhci_interrupt_frameentry_init(&result->ui_reg, &tok, cs, maxpck, buflen);
			assert(result->ui_reg.ife_tdsf);
			assert(result->ui_reg.ife_tdsl);
			result->ui_td0_phys = result->ui_reg.ife_tdsf->td_self;
			result->ui_td1_next = &result->ui_reg.ife_tdsl->td_lp;
			result->ui_hits     = 0;
			result->ui_qh       = NULL;
			if (result->ui_reg.ife_tdsf != result->ui_reg.ife_tdsl) {
				/* Use a queue head to stream-line multi-TD the data transfer. */
				struct uhci_osqh *qh;
				qh = uhci_osqh_alloc();
				qh->qh_ep = result->ui_td0_phys;
				qh->qh_next         = NULL;                    /* Unused field */
				qh->qh_tds          = result->ui_reg.ife_tdsf; /* Unused field (still init correctly, though) */
				qh->qh_aio          = NULL;                    /* Unused field */
				result->ui_qh       = qh;
				result->ui_td0_phys = qh->qh_self | UHCI_QHHP_QHTD;
			}
		}
		/* Check if the data-toggle flag changed. */
		if ((orig_tok & UHCI_TDTOK_DTOGGM) != (tok & UHCI_TDTOK_DTOGGM)) {
			if (flags & UHCI_INTERRUPT_FLAG_ISOCHRONOUS) {
				unsigned int i, n, louse, hiuse, totuse;
				struct uhci_ostd *hitd, *lotd;
				/* In the case of frame-specific transfers, it would be too much work
				 * to update all of those TD descriptors. - So instead, cheat a bit and
				 * Append one more TD at the very end. */
				hitd = uhci_ostd_alloc();
				for (n = 1, i = interval; n < frame_hits; ++n, i += interval)
					assert(result->ui_iso[i] == &result->ui_isobuf[n]);
				i -= interval;
				assert(result->ui_iso[i]);
				assert(result->ui_iso[i]->ife_tdsf);
				assert(result->ui_iso[i]->ife_tdsl);
				lotd = result->ui_iso[i]->ife_tdsl;
				result->ui_iso[i]->ife_tdsl = hitd;

				lotd->td_next = hitd;
				lotd->td_lp   = hitd->td_self;
				hitd->td_next = NULL;
				hitd->td_lp   = UHCI_TDLP_TERM;

				/* Split the used buffer size. */
				totuse = uhci_td_maxlen(lotd);
				louse  = CEILDIV(totuse, 2);
				hiuse  = totuse - louse;

				lotd->td_tok &= ~UHCI_TDTOK_MAXLENM;
				hitd->td_tok = lotd->td_tok;
				lotd->td_tok |= (((u32)louse - 1) << UHCI_TDTOK_MAXLENS) & UHCI_TDTOK_MAXLENM;
				hitd->td_tok |= (((u32)hiuse - 1) << UHCI_TDTOK_MAXLENS) & UHCI_TDTOK_MAXLENM;
				hitd->td_cs  = lotd->td_cs;
				hitd->td_buf = lotd->td_buf + louse;
				lotd->td_cs &= ~UHCI_TDCS_IOC;
				/* And with that, the D-bit even itself out over
				 * the course of the entire frame looping once. */
			} else {
				result->ui_flags |= UHCI_INTERRUPT_FLAG_FLIPDBIT;
			}
		}

		/* At this point, everything that we could possibly already know about the
		 * new interrupt handler has already been filled in. - Now it's time to
		 * actually register the thing! */
		sync_write(&me->uc_lock);
		if (flags & UHCI_INTERRUPT_FLAG_ISOCHRONOUS) {
			unsigned int n, i, winner_offset = 0;
			size_t winner_score = (size_t)-1;
			/* Figure out a suitable inter-frame shift with which we can balance
			 * out the number of isochronous data transfers within the same frame. */
			for (i = 0; i < interval; ++i) {
				size_t score;
				score = uhci_count_isotds_for_interval_and_offset(me, i, interval);
				if (score < winner_score) {
					winner_offset = i;
					if (!winner_score)
						break; /* Can't beat that! */
					winner_score = score;
				}
			}
			/* Adjust our `ui_iso' vector for the given offset. */
			if (winner_offset != 0) {
				memmove(result->ui_iso + winner_offset,
				        result->ui_iso,
				        (1024 - (interval - 1)) *
				        sizeof(struct uhci_interrupt_frameentry *));
				result->ui_iso[0] = NULL;
			}

			/* With that, we've finalized our ISO frame vector, and we can
			 * insert the interrupt descriptor into all of the proper slots. */
			for (n = 0, i = winner_offset; n < frame_hits; ++n, i += interval) {
				assert(result->ui_iso[i] == &result->ui_isobuf[n]);
				uhci_intiso_insert(me, (struct uhci_interrupt *)incref(result), i);
			}
		} else {
			uhci_intreg_insert(me, (struct uhci_interrupt *)incref(result));
		}
		uhci_controller_endwrite(me);
	} EXCEPT {
		assert(!isshared(result));
		destroy(result);
		RETHROW();
	}
	return result;
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
NOTHROW(FCALL uhci_controller_reset_port)(struct uhci_controller *__restrict self,
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

/* NOTE: This function _always_ release a lock to `&self->uc_disclock' */
PRIVATE void
NOTHROW(FCALL uhci_controller_device_attached)(struct uhci_controller *__restrict self,
                                               unsigned int portno,
                                               u16 portsc_status) {
	uintptr_t flags;
	printk(KERN_INFO "[usb][pci:%I32p,io:%#Ix] Device attached on uhci:%#I16x\n",
	       self->uc_pci->pd_base, self->uc_base.uc_mmbase, portno);
	/* NOTE: A call to `usb_device_discovered()' always releases the `uc_disclock' lock! */
	flags = portsc_status & UHCI_PORTSC_LSDA
	        ? USB_ENDPOINT_FLAG_LOWSPEED
	        : USB_ENDPOINT_FLAG_FULLSPEED;
	TRY {
		usb_device_discovered(self, flags);
	} EXCEPT {
		error_printf("discovering usb device on uhci[pci:%I32p,io:%#Ix] port #%I16u",
		             self->uc_pci->pd_base, self->uc_base.uc_mmbase, portno);
	}
}

PRIVATE void FCALL
uhci_controller_device_detached(struct uhci_controller *__restrict self,
                                unsigned int portno) {
	printk(KERN_INFO "[usb][pci:%I32p,io:%#Ix] Device detached from uhci port #%I16u\n",
	       self->uc_pci->pd_base, self->uc_base.uc_mmbase, portno);
	/* TODO */
}



/* Check for newly attached/detached devices. */
PRIVATE void KCALL
uhci_chk_port_changes(struct uhci_controller *__restrict self) {
	unsigned int i;
	printk(KERN_INFO "[usb][pci:%I32p,io:%#Ix] Check for uhci root-hub connectivity changes\n",
	       self->uc_pci->pd_base, self->uc_base.uc_mmbase);
again:
	sync_write(&self->uc_disclock);
	for (i = 0; i < self->uc_portnum; ++i) {
		u16 portsc;
		portsc = uhci_rdw(self, UHCI_PORTSC(i));
		if (!(portsc & UHCI_PORTSC_CSC))
			continue; /* Nothing's changed here... */
		if (portsc & UHCI_PORTSC_CCS) {
			uhci_wrw(self, UHCI_PORTSC(i), portsc & ~UHCI_PORTSC_PEDC);
			portsc = uhci_controller_reset_port(self, i);
			if (!(portsc & UHCI_PORTSC_PED))
				continue; /* Init failed... */
			/* New device was attached. */
			uhci_controller_device_attached(self, i, portsc);
			goto again;
		}
		/* Disable the port. */
		/* Clear ConnectStatus/EnableDisable-changed bits */
		portsc |= UHCI_PORTSC_CSC | UHCI_PORTSC_PEDC;
		uhci_wrw(self, UHCI_PORTSC(i), portsc);
		/* Clear the Port Enabled bit. */
		portsc &= ~(UHCI_PORTSC_PED | UHCI_PORTSC_CSC | UHCI_PORTSC_PEDC);
		uhci_wrw(self, UHCI_PORTSC(i), portsc);
		/* Clear the EnableDisable-changed bit */
		portsc |= UHCI_PORTSC_PEDC;
		uhci_wrw(self, UHCI_PORTSC(i), portsc);
		/* Inform the USB sub-system that a device has been detached. */
		sync_endwrite(&self->uc_disclock);
		uhci_controller_device_detached(self, i);
		goto again;
	}
	sync_endwrite(&self->uc_disclock);
}

PRIVATE void KCALL
uhci_handle_resume_detect(struct uhci_controller *__restrict self) {
	u16 cmd;
	/* Resume detected.
	 * -> Check for changes in port attachments. */
	ATOMIC_FETCHAND(self->uc_flags, ~UHCI_CONTROLLER_FLAG_RESDECT);
	sync_write(&self->uc_lock);
	TRY {
		/* Check if the FGR command flag was set.
		 * If it was, wait for 20ms and clear it. */
		cmd = uhci_rdw(self, UHCI_USBCMD);
		if (cmd & UHCI_USBCMD_FGR)
			sleep_milli(20);
		if (self->uc_flags & UHCI_CONTROLLER_FLAG_SUSPENDED) {
			/* Log the fact that we're clearing the EGSM flag. */
			uhci_controller_egsm_leave_log(self);
			self->uc_flags &= ~UHCI_CONTROLLER_FLAG_SUSPENDED;
		}
		/* Note that this is also what implicitly clears the EGSM flag. */
		if (!(cmd & UHCI_USBCMD_RS) || (cmd & (UHCI_USBCMD_FGR | UHCI_USBCMD_EGSM))) {
			uhci_wrw(self, UHCI_USBCMD,
			         UHCI_USBCMD_RS | UHCI_USBCMD_CF |
			         UHCI_USBCMD_MAXP);
		}
	} EXCEPT {
		uhci_controller_endwrite(self);
		RETHROW();
	}
	uhci_controller_endwrite(self);
	uhci_chk_port_changes(self);
}

PRIVATE void KCALL
uhci_powerctl_main(REF struct uhci_powerctl *__restrict ctl) {
	FINALLY_DECREF_UNLIKELY(ctl);
	for (;;) {
		qtime_t timeout;
		u64 last_int;
		uintptr_t flags;
		REF struct uhci_controller *uc;
		bool egsm_ok;
#define READ_CTRL() ((REF struct uhci_controller *)((XATOMIC_WEAKLYREF(struct character_device) *)&ctl->up_ctrl)->get())
		uc = READ_CTRL();
		if unlikely(!uc)
			break;
again_read_flags:
		flags = ATOMIC_READ(uc->uc_flags);
		/* Check if a resume event was detected. */
		if unlikely(flags & UHCI_CONTROLLER_FLAG_RESDECT) {
do_resdect:
			FINALLY_DECREF_UNLIKELY(uc);
			uhci_handle_resume_detect(uc);
			continue;
		}
		/* Connect to the `uc_resdec' lock and drop our reference from `uc'
		 * -> We must not be holding it while sleeping, so-as to allow the
		 *    controller to be destroyed while we're still running.
		 *    Should this happen, we'll still be informed about it by the
		 *    weak reference in `ctl' being cleared. */
do_connect:
		TRY {
			task_connect(&uc->uc_resdec);
		} EXCEPT {
			decref_unlikely(uc);
			RETHROW();
		}
		/* Now that we're interlocked with the RESDEC signal,
		 * check if another resume event got triggered. */
		flags = ATOMIC_READ(uc->uc_flags);
		if unlikely(flags & UHCI_CONTROLLER_FLAG_RESDECT) {
			decref_unlikely(uc);
			continue;
		}
		if (ATOMIC_READ(uc->uc_qhlast) != NULL) {
			/* Wait until all queue heads have been serviced. */
			/* XXX: We could easily add support for a watchdog here... */
			decref_unlikely(uc);
			task_waitfor();
			continue;
		}
		if (flags & UHCI_CONTROLLER_FLAG_SUSPENDED) {
			/* When the bus has already been suspended, then we can
			 * just wait until it gets resumed before doing anything! */
			decref_unlikely(uc);
			task_waitfor();
			continue;
		}
		/* There doesn't seem to be any traffic, so we wait for traffic
		 * to appear with a custom timeout that specifies how long to
		 * wait before the bus should automatically be suspended.
		 * Note that this is a relatively short delay, because for whatever
		 * reason, USB attach/detach events only generate interrupts  */
		last_int = atomic64_read_r(&uc->uc_lastint);
		timeout.q_jtime = last_int + uc->uc_suspdelay;
		decref_unlikely(uc);
		timeout.q_qtime = 0;
		timeout.q_qsize = 1;
		/* Wait for our timeout to expire. */
		if (task_waitfor(&timeout) != NULL)
			continue; /* Something happened! -> Don't time out. */

		/* Must (try to) suspend the controller. */
		uc = READ_CTRL();
		if unlikely(!uc)
			break;
		/* Quick check: Has something that we should worry about happened? */
		flags = ATOMIC_READ(uc->uc_flags);
		if (flags & UHCI_CONTROLLER_FLAG_RESDECT)
			goto do_resdect;
		if (ATOMIC_READ(uc->uc_qhlast) != NULL)
			goto do_connect;
		if (flags & UHCI_CONTROLLER_FLAG_SUSPENDED)
			goto do_connect;
		/* Lock the controller since we're about to access its registers. */
		TRY {
			sync_write(&uc->uc_lock);
		} EXCEPT {
			decref_unlikely(uc);
			RETHROW();
		}
		/* Check the controller state again (now that we've got the necessary lock) */
		flags = ATOMIC_READ(uc->uc_flags);
		if (flags & UHCI_CONTROLLER_FLAG_RESDECT) {
			sync_endwrite(&uc->uc_lock);
			goto do_resdect;
		}
		if (ATOMIC_READ(uc->uc_qhlast) != NULL) {
			sync_endwrite(&uc->uc_lock);
			goto do_connect;
		}
		if (flags & UHCI_CONTROLLER_FLAG_SUSPENDED) {
			sync_endwrite(&uc->uc_lock);
			goto do_connect;
		}
		/* Try to enter EGSM mode.
		 * Note that this function returns `false' if there are
		 * any ports with changed connectivity indicators! */
		egsm_ok = uhci_controller_egsm_enter(uc);
		uhci_controller_endwrite(uc);
		/* If we've successfully managed to enter EGSM mode, directly loop back. */
		if (egsm_ok)
			goto again_read_flags;
		/* There are some ports that have changed their connectivity status.
		 * -> Handle this change in connectivity, and loop back. */
		TRY {
			uhci_chk_port_changes(uc);
		} EXCEPT {
			decref_unlikely(uc);
			RETHROW();
		}
		goto again_read_flags;
	}
}



PRIVATE ATTR_FREETEXT void FCALL
uhci_controller_reset_port_and_probe(struct uhci_controller *__restrict self,
                                     unsigned int portno) {
	u16 status;
	UHCI_DEBUG(FREESTR(KERN_INFO "[usb][pci:%I32p,io:%#Ix] Checking for device on uhci port #%I16u\n"),
	           self->uc_pci->pd_base, self->uc_base.uc_mmbase, portno);
	sync_write(&self->uc_disclock);
	TRY {
		status = uhci_controller_reset_port(self, portno);
	} EXCEPT {
		sync_endwrite(&self->uc_disclock);
		RETHROW();
	}
	if (status & UHCI_PORTSC_PED)
		uhci_controller_device_attached(self, portno, status);
	else {
		sync_endwrite(&self->uc_disclock);
	}
}


#define UHC_BAR_CORRECT_IOTYPE 0x01 /* Require I/O typing (as opposed to mmio) */
#define UHC_BAR_CORRECT_IOSIZE 0x02 /* Require that IOSIZE = 0x20 */
#define UHC_BAR_CORRECT_UNIQUE 0x04 /* Require a unique match */
PRIVATE ATTR_FREETEXT unsigned int KCALL
uhci_find_pci_bar_ex(struct pci_device *__restrict dev,
                     unsigned int requirements) {
	unsigned int result, i;
	result = PD_RESOURCE_COUNT;
	for (i = 0; i < PD_RESOURCE_COUNT; ++i) {
		struct pci_resource *res;
		res = &dev->pd_res[PD_RESOURCE_BAR(i)];
		if (res->pr_flags == PCI_RESOURCE_FUNUSED)
			continue;
		if (!(res->pr_flags & PCI_RESOURCE_FIO) &&
		    (requirements & UHC_BAR_CORRECT_IOTYPE))
			continue;
		if ((res->pr_size != 0x20) &&
		    (requirements & UHC_BAR_CORRECT_IOSIZE))
			continue;
		if (!(requirements & UHC_BAR_CORRECT_UNIQUE)) {
			result = i;
			break;
		}
		if (result == PD_RESOURCE_COUNT)
			result = i;
		else {
			result = PD_RESOURCE_COUNT + 1;
		}
	}
	return result;
}

PRIVATE ATTR_FREETEXT unsigned int KCALL
uhci_find_pci_bar(struct pci_device *__restrict dev) {
	unsigned int result, flags;
	/* Nowhere in the UHCI specs does it say which BAR it has to be.
	 * -> Go through each bar and look for one that matches what we're
	 *    looking for. - For this, we can look at the IOSIZE attribute
	 *    of said BAR, as well as check if the BAR is even allocated.
	 * #1: If only 1 BAR is allocated, that's the one
	 * #2: If only 1 BAR has the expected I/O size, that's the one
	 *     FIXME: Looking at the I/O sizes, I have a feeling that the PCI
	 *            driver loads these incorrectly... (I'm reading 0xffff3fc0,
	 *            which is 0-BASE...)
	 * #3: If only 1 BAR has `PCI_RESOURCE_FIO' set, that's the one
	 * #4: Just use the first matching BAR...
	 */
	flags = UHC_BAR_CORRECT_UNIQUE;
again:
	result = uhci_find_pci_bar_ex(dev, flags | UHC_BAR_CORRECT_IOTYPE | UHC_BAR_CORRECT_IOSIZE);
	if (result < PD_RESOURCE_COUNT)
		goto done;
	result = uhci_find_pci_bar_ex(dev, flags | UHC_BAR_CORRECT_IOSIZE);
	if (result < PD_RESOURCE_COUNT)
		goto done;
	result = uhci_find_pci_bar_ex(dev, flags | UHC_BAR_CORRECT_IOTYPE);
	if (result < PD_RESOURCE_COUNT)
		goto done;
	result = uhci_find_pci_bar_ex(dev, flags);
	if (result < PD_RESOURCE_COUNT)
		goto done;
	if (flags & UHC_BAR_CORRECT_UNIQUE) {
		flags = 0;
		goto again;
	}
done:
	return result;
}


INTERN ATTR_FREETEXT void KCALL
usb_probe_uhci(struct pci_device *__restrict dev) {
	struct uhci_controller *result;
	unsigned int i, pci_bar;
	pci_bar = uhci_find_pci_bar(dev);
	if unlikely(pci_bar >= PD_RESOURCE_COUNT) {
		printk(FREESTR(KERN_ERR "[usb][pci:%I32p] Failed to determine uhci I/O bar\n"),
		       dev->pd_base);
		return;
	}

	result = CHARACTER_DEVICE_ALLOC(struct uhci_controller);
	FINALLY_DECREF_UNLIKELY(result);

	result->cd_type.ct_fini = &uhci_fini;
	sig_cinit(&result->uc_resdec);
	atomic_rwlock_cinit(&result->uc_lock);
	usb_controller_cinit(result);
	result->uc_pci          = dev;
	assert(IS_ALIGNED((uintptr_t)&result->uc_qhstart, UHCI_FLE_ALIGN));

	if (dev->pd_res[PD_RESOURCE_BAR(pci_bar)].pr_flags & PCI_RESOURCE_FIO) {
		result->uc_base.uc_iobase = (port_t)dev->pd_res[PD_RESOURCE_BAR(pci_bar)].pr_start;
	} else {
		vm_vpage_t page;
		page = vm_map(&vm_kernel,
		              (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_DEVICE), 1,
		              1, HINT_GETMODE(KERNEL_VMHINT_DEVICE),
		              &vm_datablock_physical,
		              (vm_vpage64_t)(vm_ppage_t)VM_ADDR2PAGE((vm_phys_t)dev->pd_res[PD_RESOURCE_BAR(pci_bar)].pr_start),
		              VM_PROT_READ | VM_PROT_WRITE,
		              VM_NODE_FLAG_NORMAL, 0);
		result->uc_base.uc_mmbase = (byte_t *)VM_PAGE2ADDR(page);
		result->uc_flags |= UHCI_CONTROLLER_FLAG_USESMMIO;
	}
	result->uc_transfer        = &uhci_transfer;
	result->uc_interrupt       = &uhci_register_interrupt;
	result->uc_framelist       = (u32 *)vpage_alloc(1, 1, GFP_LOCKED | GFP_PREFLT);
	result->uc_framelist_phys  = (u32)pagedir_translate((vm_virt_t)result->uc_framelist);
	result->uc_qhstart.qh_self = (u32)pagedir_translate((vm_virt_t)&result->uc_qhstart);

	/* Fill in the frame list */
	for (i = 0; i < UHCI_FRAMELIST_COUNT; ++i)
		result->uc_framelist[i] = result->uc_qhstart.qh_self | UHCI_FLE_QHTD;
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
	          (dev->pd_res[PD_RESOURCE_BAR(pci_bar)].pr_flags & PCI_RESOURCE_FIO
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
	                &uhci_interrupt_handler, result);

	/* Enable interrupts that we want to listen for. */
	uhci_wrw(result, UHCI_USBINTR,
	         UHCI_USBINTR_TIE | UHCI_USBINTR_RIE |
	         UHCI_USBINTR_IOC | UHCI_USBINTR_SPIE);

	/* Turn on the controller. */
	uhci_wrw(result, UHCI_USBCMD,
	         UHCI_USBCMD_RS | UHCI_USBCMD_CF |
	         UHCI_USBCMD_MAXP);

	/* Configure the suspend timeout */
	atomic64_cinit(&result->uc_lastint, jiffies);
	result->uc_suspdelay = CEILDIV(HZ, 5);

	{
		REF struct task *pth;
		REF struct uhci_powerctl *pctl;
		/* Create the power management descriptor. */
		pctl = (REF struct uhci_powerctl *)kmalloc(sizeof(struct uhci_powerctl),
		                                           GFP_NORMAL);
		pctl->up_refcnt = 1;
		xatomic_weaklyref_init(&pctl->up_ctrl, result);
		result->uc_powerctl_desc = pctl; /* Inherit reference */
		/* Create the power management thread. */
		TRY {
			pth = task_alloc(&vm_kernel);
		} EXCEPT {
			decref(pctl);
			RETHROW();
		}
		task_setup_kernel(pth, (thread_main_t)&uhci_powerctl_main, 1, incref(pctl));
		task_start(pth, TASK_START_FNORMAL);
		result->uc_powerctl_thrd = pth; /* Inherit reference. */
	}


	{
		static int n = 0; /* TODO: better naming */
		sprintf(result->cd_name, "uhci%c", 'a' + n++);
	}
	character_device_register_auto(result);

	/* Reset & probe for new connections. */
	for (i = 0; i < result->uc_portnum; ++i)
		uhci_controller_reset_port_and_probe(result, i);

//	sleep_milli(2000);
//
//	printk(KERN_RAW "%%{monitor:info usb\n}");
//	printk(KERN_RAW "%%{monitor:usb_del 0.1\n}");
//
//	for (;;)
//		asm("hlt");
}


DECL_END

#endif /* !GUARD_MODUSB_UHCI_C */
