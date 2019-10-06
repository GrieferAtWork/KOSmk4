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
#ifndef GUARD_MODUSB_UHCI_H
#define GUARD_MODUSB_UHCI_H 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <kernel/vm.h>

#include <kos/io/uhci.h>
#include <stdalign.h>
#include <sys/io.h>

#include "usb.h"

DECL_BEGIN

union uhci_iobase {
	port_t  uc_iobase; /* I/O base address. */
	byte_t *uc_mmbase; /* MMIO base address. */
};

struct uhci_ostd: uhci_td {
	PHYS u32          td_self; /* [const] Physical self-pointer (to the hardware part). */
	struct uhci_ostd *td_next; /* [0..1][owned] Next TD in this chain / next free TD.
	                            * In the former case, `uhci_td::td_lp' is set to `td_next->td_self' */
};

struct aio_handle;
struct uhci_controller;

struct uhci_osqh: uhci_qh {
	WEAK refcnt_t         qh_refcnt; /* Reference counter. */
	PHYS u32              qh_self;   /* [const] Physical self-pointer (to the hardware part). */
	REF struct uhci_osqh *qh_next;   /* [0..1] Next QH in this chain / next free TD.
	                                  * In the former case, `uhci_qh::qh_hp' is set to `qh_next->qh_self' */
	struct uhci_ostd     *qh_tds;    /* [0..1][owned] Chain of TDs used by this queue */
	struct aio_handle    *qh_aio;    /* [1..1][const] The associated AIO handle. */
};

struct uhci_aio_data {
	REF struct uhci_osqh       *ud_osqh;       /* [1..1][const] The Queue head associated with this request. */
	REF struct uhci_controller *ud_ctrl;       /* [1..1][const] The associated USB controller. */
	union {
		struct vm_dmalock       ud_dmalock;    /* [valid_if(!UHCI_AIO_FSERVED && UHCI_AIO_FONEDMA)] Single DMA lock */
		struct vm_dmalock      *ud_dmalockvec; /* [valid_if(!UHCI_AIO_FSERVED && !UHCI_AIO_FONEDMA)][0..1][owned] Vector of DMA locks
		                                        * NOTE: This vector is terminated by a sentinel DMA
		                                        *       lock with its `dl_part' pointer set to `NULL' */
	};
#define UHCI_AIO_FNORMAL        0x0000         /* Normal AIO flags */
#define UHCI_AIO_FSERVED        0x0004         /* FLAG: This handle has been serviced. */
#define UHCI_AIO_FONEDMA        0x0008         /* [const] FLAG: `ud_dmalock' is used, as opposed to `hd_dmalockvec'. */
	uintptr_t                   ud_flags;      /* [lock(ud_ctrl->uc_lock)] Set of `UHCI_AIO_F*' */
	size_t                      ud_retsize;    /* Total amount of transferred data (output argument) */
};


/* Allocate/Free OSTD/OSQH descriptors. */
FUNDEF WUNUSED ATTR_RETNONNULL ATTR_MALLOC struct uhci_ostd *FCALL uhci_ostd_alloc(void) THROWS(E_BADALLOC, E_WOULDBLOCK);
FUNDEF WUNUSED ATTR_RETNONNULL ATTR_MALLOC struct uhci_osqh *FCALL uhci_osqh_alloc(void) THROWS(E_BADALLOC, E_WOULDBLOCK);
FUNDEF NOBLOCK void NOTHROW(FCALL uhci_ostd_free)(struct uhci_ostd *__restrict self);
FUNDEF NOBLOCK void NOTHROW(FCALL uhci_osqh_free)(struct uhci_osqh *__restrict self);

FUNDEF NOBLOCK void NOTHROW(FCALL uhci_osqh_destroy)(struct uhci_osqh *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct uhci_osqh, qh_refcnt, uhci_osqh_destroy)



struct uhci_controller: usb_controller {
	union uhci_iobase    uc_base;           /* I/O base address. */
	struct pci_device   *uc_pci;            /* [1..1][const] The associated PCI device. */
#define UHCI_CONTROLLER_FLAG_USESMMIO    0x0001 /* [const] The controller uses MMIO */
#define UHCI_CONTROLLER_FLAG_INTERRUPTED 0x0002 /* [const] A command-completion interrupt happened while `uc_lock' was held. */
	uintptr_t            uc_flags;          /* Controller flags (Set of `UHCI_CONTROLLER_FLAG_*'). */
	struct atomic_rwlock uc_lock;           /* Lock for sending commands to the controller. */
	alignas(UHCI_FLE_ALIGN)
	struct uhci_osqh     uc_qhstart;        /* [lock(INSERT(uc_lock))] Queue head start (Entries of `uc_framelist' first point to
	                                         * optional isochronous, and eventually to this one) Afterwards, all entires point to
	                                         * this one, allowing one-time transfer descriptors  to be scheduled following after
	                                         * this queue.
	                                         * NOTE: The hardware pointer of the last queue head always points back to `uc_qhstart'.
	                                         *       However, the software pointer of that queue head is set to `NULL'.
	                                         * NOTE: The `qh_tds' field of this queue head is always `NULL'.
	                                         * NOTE: The `qh_ep' field of this queue head is always `UHCI_QHEP_TERM'. */
	u32                 *uc_framelist;      /* [1..1][owned][const] Frame list base address. */
	u32                  uc_framelist_phys; /* [const][== pagedir_translate(uc_framelist)]. */
	u8                   uc_portnum;        /* [const] # of available ports. */
};

/* Safely release a read/write lock on `self->uc_lock' */
FUNDEF NOBLOCK void NOTHROW(FCALL uhci_controller_endread)(struct uhci_controller *__restrict self);
FUNDEF NOBLOCK void NOTHROW(FCALL uhci_controller_endwrite)(struct uhci_controller *__restrict self);

/* Schedule the given queue for execution.
 * This function initialized:
 *  - osqh->qh_hp
 *  - osqh->qh_next
 * All other fields of `osqh' must be set by the caller. */
FUNDEF void FCALL
uhci_controller_addqueue(struct uhci_controller *__restrict self,
                         REF struct uhci_osqh *__restrict osqh)
		THROWS(E_WOULDBLOCK);


#define uhci_controller_uses_mmio(self) \
	((self)->uc_flags & UHCI_CONTROLLER_FLAG_USESMMIO)
#define uhci_rdb(self, reg)                                                     \
	(uhci_controller_uses_mmio(self) ? readb((self)->uc_base.uc_mmbase + (reg)) \
	                                 : inb((self)->uc_base.uc_iobase + (reg)))
#define uhci_rdw(self, reg)                                                     \
	(uhci_controller_uses_mmio(self) ? readw((self)->uc_base.uc_mmbase + (reg)) \
	                                 : inw((self)->uc_base.uc_iobase + (reg)))
#define uhci_rdl(self, reg)                                                     \
	(uhci_controller_uses_mmio(self) ? readl((self)->uc_base.uc_mmbase + (reg)) \
	                                 : inl((self)->uc_base.uc_iobase + (reg)))
#define uhci_wrb(self, reg, val)                                                      \
	(uhci_controller_uses_mmio(self) ? writeb((self)->uc_base.uc_mmbase + (reg), val) \
	                                 : outb((self)->uc_base.uc_iobase + (reg), val))
#define uhci_wrw(self, reg, val)                                                      \
	(uhci_controller_uses_mmio(self) ? writew((self)->uc_base.uc_mmbase + (reg), val) \
	                                 : outw((self)->uc_base.uc_iobase + (reg), val))
#define uhci_wrl(self, reg, val)                                                      \
	(uhci_controller_uses_mmio(self) ? writel((self)->uc_base.uc_mmbase + (reg), val) \
	                                 : outl((self)->uc_base.uc_iobase + (reg), val))


DECL_END

#endif /* !GUARD_MODUSB_UHCI_H */
