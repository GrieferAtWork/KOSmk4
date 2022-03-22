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
#ifndef GUARD_MODUSB_UHCI_H
#define GUARD_MODUSB_UHCI_H 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <drivers/usb.h>
#include <kernel/malloc.h>
#include <kernel/mman/dma.h>
#include <kernel/types.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <bits/os/timespec.h>
#include <hw/usb/uhci.h>
#include <sys/io.h>
#include <sys/mmio.h>

#include <stdalign.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

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
		mdma_lock_t             ud_dmalock;    /* [valid_if(!UHCI_AIO_FSERVED && UHCI_AIO_FONEDMA)] Single DMA lock */
		mdma_lock_t            *ud_dmalockvec; /* [valid_if(!UHCI_AIO_FSERVED && !UHCI_AIO_FONEDMA)][0..1][owned] Vector of DMA locks
		                                        * NOTE: This vector is  terminated by  a sentinel  DMA
		                                        *       lock with its `mdl_part' pointer set to `NULL' */
	};
#define UHCI_AIO_FNORMAL        0x0000         /* Normal AIO flags */
#define UHCI_AIO_FSERVED        0x0004         /* FLAG: This handle has been serviced. */
#define UHCI_AIO_FONEDMA        0x0008         /* [const] FLAG: `ud_dmalock' is used, as opposed to `hd_dmalockvec'. */
	uintptr_t                   ud_flags;      /* [lock(ud_ctrl->uc_lock)] Set of `UHCI_AIO_F*' */
	size_t                      ud_retsize;    /* Total amount of transferred data (output argument) */
};


/* Allocate/Free OSTD/OSQH descriptors. */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED struct uhci_ostd *FCALL uhci_ostd_alloc(void) THROWS(E_BADALLOC, E_WOULDBLOCK);
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED struct uhci_osqh *FCALL uhci_osqh_alloc(void) THROWS(E_BADALLOC, E_WOULDBLOCK);
FUNDEF NOBLOCK void NOTHROW(FCALL uhci_ostd_free)(struct uhci_ostd *__restrict self);
FUNDEF NOBLOCK void NOTHROW(FCALL uhci_osqh_free)(struct uhci_osqh *__restrict self);

FUNDEF NOBLOCK void NOTHROW(FCALL uhci_osqh_destroy)(struct uhci_osqh *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct uhci_osqh, qh_refcnt, uhci_osqh_destroy)


struct uhci_interrupt;
struct uhci_interrupt_frameentry {
	REF struct uhci_interrupt *ife_next;    /* [0..1][lock(:uc_lock)] Next interrupt on this frame. */
	void                      *ife_buf;     /* [0..?|ALLOC(ui_bufsize)][owned][const] Buffer base address. */
	size_t                     ife_bufsize; /* [const] Allocated buffer size (as returned by `heap_alloc_untraced()')
	                                         * NOTE: The least significant bit of this field is used to indicate a kram-based buffer (1=vpage; 0=heap). */
	struct uhci_ostd          *ife_tdsf;    /* [1..1][owned][const] First TD entry describing this interrupt's data */
	struct uhci_ostd          *ife_tdsl;    /* [1..1][const] Last TD entry describing this interrupt's data */
};

struct uhci_interrupt: usb_interrupt {
#define UHCI_INTERRUPT_FLAG_ISOCHRONOUS USB_INTERRUPT_FLAG_CTRL(0) /* This interrupt is only checked on specific frames. */
#define UHCI_INTERRUPT_FLAG_FLIPDBIT    USB_INTERRUPT_FLAG_CTRL(1) /* The total number of TDs is uneven, and their data-toggle
	                                                                * bits must be flipped before they can be used again.
	                                                                * NOTE: Never set when `UHCI_INTERRUPT_FLAG_ISOCHRONOUS' is set. */
	u32                                      ui_initcs;    /* [const] Initial CS value for TDs */
	union {
		struct {
			struct uhci_interrupt_frameentry ui_reg;       /* [valid_if(!UHCI_INTERRUPT_FLAG_ISOCHRONOUS)] Next interrupt. */
			u32                              ui_td0_phys;  /* [valid_if(!UHCI_INTERRUPT_FLAG_ISOCHRONOUS)][const]
			                                                * [== ui_qh ? ui_qh->qh_self | UHCI_QHHP_QHTD : ui_reg.ife_tdsf->td_self] */
			u32                             *ui_td1_next;  /* [valid_if(!UHCI_INTERRUPT_FLAG_ISOCHRONOUS)][const]
			                                                * [== ui_qh ? &ui_qh->qh_hp : &ui_reg.ife_tdsl->td_lp] */
			struct uhci_osqh                *ui_qh;        /* [0..1][owned][const] First queue head used to describe this interrupt. */
			size_t                           ui_hits;      /* Number of times that this interrupt got hit (used for self-optimization) */
		};
		struct uhci_interrupt_frameentry    *ui_iso[1024]; /* [0..1][valid_if(UHCI_INTERRUPT_FLAG_ISOCHRONOUS)] Frame list */
	};
	COMPILER_FLEXIBLE_ARRAY(struct uhci_interrupt_frameentry, ui_isobuf); /* Buffer into which `ui_iso' points. */
};


/* UHCI Scheduling model:
 *
 *
 * Frame-List (for n in 0..1023)
 *
 * n: uc_framelist[n] -> uc_intiso[n]->ui_iso[n].ife_next->...
 *                    -> uc_intreg->ui_reg.ife_next->...
 *                    -> uc_qhstart
 *                    -> uc_qhstart.qh_next->...
 *                    -> uc_intreg
 *
 * As such:
 *   - Every frame begins with ISO interrupt handlers
 *   - Following those, interrupt handlers triggered on every frame are polled
 *   - Following those, the stub uc_qhstart queue head is reached
 *   - uc_qhstart then points to any number of one-time transmissions
 *     created using `usb_controller_transfer()'
 *   - Finally, the frame loops back on itself by back to interrupt handlers
 *     polled every frame.
 *
 * With all of this in mind, the scheduling used by KOS pretty much mirrors the example
 * included  within the UHCI  specifications (Figure 4.  Example Schedule), as included
 * on page #6 (ftp://ftp.netbsd.org/pub/NetBSD/misc/blymn/uhci11d.pdf)
 *
 * IMPORTANT NOTE ABOUT UHCI:
 *   - You only get interrupts about devices attaching/detaching when `UHCI_USBCMD_EGSM' is set!
 *   - As such, plug-and-play requires a background daemon (`uhci_powerctl_cb') that handles all
 *     of  the attach/detach, as well as the delayed setting of `UHCI_USBCMD_EGSM', as that flag
 *     indicates a sort-of suspension mode for the controller.
 *     I'm not entirely sure what really gets suspended by that flag on real hardware. - In QEMU
 *     it only seems to affect the  delivery of device change interrupts,  so I may be wrong  in
 *     thinking that the  flag should  be cleared before  any USB  transmissions are  performed.
 *     However, according  to  the  UHCI  specs:  `No USB transactions occurs during this time',
 *     referring to any  time that  the aforementioned  flag is set.  So I'd  assume you're  not
 *     supposed to have  that flag  remain enabled  while doing any  sort of  traffic (which  is
 *     what I went with in this implementation by the way...)
 *  -> Essentially, when `UHCI_USBCMD_EGSM' is  set, the controller may  fire an interrupt with  the
 *     `UHCI_USBSTS_RD' status flag set, which indicates that the connectivity status of some device
 *     changed, or that a  USB device caused an  interrupt (which I assume  includes stuff like  you
 *     pressing a key on a USB keyboard, but definitely includes device attach/detach)
 *  -> This is then handled by setting  the `UHCI_CONTROLLER_FLAG_RESDECT' flag below, and  broadcasting
 *     the  `uc_resdec'  signal,  waking  up  the  `uhci_powerctl_cb'  and  causing  it  to  clear   the
 *     `UHCI_USBCMD_EGSM' flag (which by the way is kept in sync with `UHCI_CONTROLLER_FLAG_SUSPENDED'),
 *     before  enumerating the  root hub  ports (`UHCI_PORTSC(0 ... uc_portnum - 1)')  and checking each
 *     of them for the `UHCI_PORTSC_CSC' flag.
 *  -> There  also exists a timeout before `UHCI_CONTROLLER_FLAG_SUSPENDED' automatically gets set once
 *     again, which is also handled by `uhci_powerctl_cb' and is done in relation to the amount of time
 *     that has passed since the last interrupt (of any kind)
 * ...
 * This all could have been sooo much simpler if it was possible to detect device attach/detach
 * while   still  keeping  the   UHCI  controller  turned  on   in  its  normal  configuration.
 */

struct uhci_controller: usb_controller {
	union uhci_iobase          uc_base;           /* I/O base address. */
	struct pci_device         *uc_pci;            /* [1..1][const] The associated PCI device. */
#define UHCI_CONTROLLER_FLAG_USESMMIO    0x0001   /* [const] The controller uses MMIO */
#define UHCI_CONTROLLER_FLAG_INTERRUPTED 0x0002   /* [const] A command-completion interrupt happened while `uc_lock' was held. */
#define UHCI_CONTROLLER_FLAG_RESDECT     0x0004   /* [lock(ATOMIC,INTERLOCKED(uc_resdec))] A resume-detect interrupt happened. */
#define UHCI_CONTROLLER_FLAG_SUSPENDED   0x0008   /* [lock(uc_lock)] The controller is currently suspended. */
	uintptr_t                  uc_flags;          /* Controller flags (Set of `UHCI_CONTROLLER_FLAG_*'). */
	struct sig                 uc_resdec;         /* Signal broadcast when the `UHCI_CONTROLLER_FLAG_RESDECT' flag
	                                               * is  set,  or  `UHCI_CONTROLLER_FLAG_SUSPENDED'  is   cleared,
	                                               * or `uc_qhlast' is set to `NULL'. */
	struct async              *uc_egsm;           /* [1..1][owned] EGSM daemon. */
	struct atomic_rwlock       uc_lock;           /* Lock for sending commands to the controller. */
	REF struct uhci_interrupt *uc_intreg;         /* [lock(uc_lock)][0..1] Chain of interrupts checked every frame (w/o `UHCI_INTERRUPT_FLAG_ISOCHRONOUS').
	                                               * NOTE: The  HW-next  pointer of  last  TD of  the  last entry  of  this chain  points  to `uc_qhstart'! */
	REF struct uhci_interrupt *uc_intiso[1024];   /* [lock(uc_lock)][0..1][*] Chains of interrupts checked only on certain frames (w/ `UHCI_INTERRUPT_FLAG_ISOCHRONOUS').
	                                               * NOTE: The  HW-next  pointer  of  last  TD of  the  last  entry  of  each of  these  chains  points  to `uc_qhstart'! */
	size_t                     uc_iisocount;      /* [lock(uc_lock)] Number of interrupt descriptors chains through `uc_intiso'.
	                                               * NOTE: Interrupts chained more  than once  also count more  than once  here. */
	struct uhci_osqh          *uc_qhlast;         /* [lock(uc_lock)][0..1] The last queue head in the `uc_qhstart.qh_next' chain. */
#ifndef CONFIG_NO_SMP
	struct atomic_rwlock       uc_lastint_lock;   /* SMP-lock for accessing `uc_lastint'. */
#endif /* !CONFIG_NO_SMP */
	ktime_t                    uc_lastint;        /* Timestamp for the time when the last interrupt happened. */
	unsigned int               uc_suspdelay;      /* Delay (in milliseconds) before the controller is suspended. */
	alignas(UHCI_FLE_ALIGN)
	struct uhci_osqh           uc_qhstart;        /* [lock(INSERT(uc_lock))] Queue head start (Entries of `uc_framelist' first point to
	                                               * optional isochronous, and eventually to this one) Afterwards, all entries point to
	                                               * this one, allowing one-time transfer  descriptors to be scheduled following  after
	                                               * this queue.
	                                               * NOTE: The hardware pointer of the last queue head always points back
	                                               *       to  `uc_qhstart',  or   `uc_intreg'  if   that  is   non-NULL.
	                                               *       However, the software pointer of that queue head is set to `NULL'.
	                                               * NOTE: The  `qh_tds'  field  of  this  queue  head  is  always  `NULL'.
	                                               * NOTE: The `qh_ep' field of this queue head is always `UHCI_QHEP_TERM'. */
	u32                       *uc_framelist;      /* [lock(uc_lock)][1..1][owned][const] Frame list base address. */
	u32                        uc_framelist_phys; /* [const][== pagedir_translate(uc_framelist)]. */
	u16                        uc_framelast;      /* [lock(uc_lock)] The value  of `UHCI_FRNUM'  during the  last
	                                               * interrupt where ISO interrupts where checked for completion. */
	u8                         uc_portnum;        /* [const] # of available ports. */
};

/* Cast a given object into a `struct usb_controller' */
#define usb_controller_asuhci(self) ((struct uhci_controller *)(self))
#define chrdev_asuhci(self)         usb_controller_asuhci(chrdev_as_usb_controller(self))
#define device_asuhci(self)         usb_controller_asuhci(device_as_usb_controller(self))
#define fnode_asuhci(self)          usb_controller_asuhci(fnode_as_usb_controller(self))
#define mfile_asuhci(self)          usb_controller_asuhci(mfile_as_usb_controller(self))

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
	(uhci_controller_uses_mmio(self) ? peekb((self)->uc_base.uc_mmbase + (reg)) \
	                                 : inb((self)->uc_base.uc_iobase + (reg)))
#define uhci_rdw(self, reg)                                                     \
	(uhci_controller_uses_mmio(self) ? peekw((self)->uc_base.uc_mmbase + (reg)) \
	                                 : inw((self)->uc_base.uc_iobase + (reg)))
#define uhci_rdl(self, reg)                                                     \
	(uhci_controller_uses_mmio(self) ? peekl((self)->uc_base.uc_mmbase + (reg)) \
	                                 : inl((self)->uc_base.uc_iobase + (reg)))
#define uhci_wrb(self, reg, val)                                                     \
	(uhci_controller_uses_mmio(self) ? pokeb((self)->uc_base.uc_mmbase + (reg), val) \
	                                 : outb((self)->uc_base.uc_iobase + (reg), val))
#define uhci_wrw(self, reg, val)                                                     \
	(uhci_controller_uses_mmio(self) ? pokew((self)->uc_base.uc_mmbase + (reg), val) \
	                                 : outw((self)->uc_base.uc_iobase + (reg), val))
#define uhci_wrl(self, reg, val)                                                     \
	(uhci_controller_uses_mmio(self) ? pokel((self)->uc_base.uc_mmbase + (reg), val) \
	                                 : outl((self)->uc_base.uc_iobase + (reg), val))


DECL_END

#endif /* !GUARD_MODUSB_UHCI_H */
