/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODIDE_ATA_C
#define GUARD_MODIDE_ATA_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "ata.h"
/**/

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/driver-callbacks.h>
#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/entropy.h>
#include <kernel/except.h>
#include <kernel/isr.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/map.h>
#include <kernel/printk.h>
#include <sched/cpu.h>
#include <sched/tsc.h>

#include <hybrid/minmax.h>
#include <hybrid/sched/preemption.h>

#include <hw/bus/pci.h>
#include <kos/except.h>
#include <kos/except/reason/io.h>
#include <linux/hdreg.h>
#include <sys/mkdev.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libpciaccess/pciaccess.h>

/**/
#include <kernel/x86/pic.h> /* TODO: Non-portable! */

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/************************************************************************/
/* Driver parameters                                                    */
/************************************************************************/
#ifdef BUILDING_KERNEL_CORE
ATTR_FREEBSS
#endif /* BUILDING_KERNEL_CORE */
DEFINE_CMDLINE_FLAG_VAR(ide_nodma, "ide_nodma");



/************************************************************************/
/* Hardware helpers                                                     */
/************************************************************************/
typedef u32 AtaError_t; /* ATA error  */
#define ATA_ERROR(error, reason) (EXCEPT_SUBCLASS(EXCEPT_CODEOF(error)) | ((reason) << 16))
#define ATA_ERROR_OK             0x0000
#define ATA_EXCEPT_CLASS(x)      E_IOERROR
#define ATA_EXCEPT_SUBCLASS(x)   ((x)&0xffff)
#define ATA_ERROR_REASON(x)      (((x) >> 16) & 0xffff)

/* ATA specifies a 400ns delay after drive switching,
 * often implemented as 4 Alternative Status queries.
 * XXX: This can probably be optimized away in certain
 *      cases where we  don't have  to wait,  possibly
 *      by detecting modern hardware... */
#define AtaBus_HW_SelectDelay_P(ctrlio) \
	(inb(ctrlio), inb(ctrlio), inb(ctrlio), inb(ctrlio))
#define AtaBus_HW_SelectDelay(self) \
	AtaBus_HW_SelectDelay_P((self)->ab_ctrlio)


/* @param: status: Set of `ATA_DCR_*' */
LOCAL NOBLOCK AtaError_t
NOTHROW(FCALL ATA_HW_GetErrorFromStatusRegister)(u8 status) {
	if ((status & (ATA_DCR_ERR | ATA_DCR_DF)) == (ATA_DCR_ERR | ATA_DCR_DF))
		return ATA_ERROR(E_IOERROR_ERRORBIT, E_IOERROR_REASON_ATA_DCR_ERR_DF);
	return ATA_ERROR(E_IOERROR_ERRORBIT,
	                 status & ATA_DCR_ERR ? E_IOERROR_REASON_ATA_DCR_ERR
	                                      : E_IOERROR_REASON_ATA_DCR_DF);
}

PRIVATE NOBLOCK AtaError_t
NOTHROW(FCALL AtaBus_HW_WaitForBusy_P)(port_t ctrlio, ktime_t timeout_BSY) {
	u8 status;
	ktime_t abs_timeout;
	status = inb(ctrlio);
	if (!(status & ATA_DCR_BSY))
		return ATA_ERROR_OK;
	if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF))
		return ATA_HW_GetErrorFromStatusRegister(status);
	abs_timeout = ktime();
	abs_timeout += timeout_BSY;
	while ((status = inb(ctrlio)) & ATA_DCR_BSY) {
		if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF))
			return ATA_HW_GetErrorFromStatusRegister(status);
		if unlikely(ktime() >= abs_timeout)
			return ATA_ERROR(E_IOERROR_TIMEOUT, E_IOERROR_REASON_ATA_DCR_BSY);
		preemption_tryyield();
		io_delay();
	}
	return ATA_ERROR_OK;
}

/* Wait for `!ATA_DCR_BSY', but time out eventually. */
PRIVATE NOBLOCK AtaError_t
NOTHROW(FCALL AtaBus_HW_WaitForBusy)(AtaBus *__restrict self) {
	return AtaBus_HW_WaitForBusy_P(self->ab_ctrlio, self->ab_timeout_BSY);
}

/* Wait for `ATA_DCR_DRQ', but time out eventually. */
PRIVATE NOBLOCK AtaError_t
NOTHROW(FCALL AtaBus_HW_WaitForDrq)(AtaBus *__restrict self) {
	u8 status;
	ktime_t abs_timeout;
	if (((status = inb(self->ab_ctrlio)) & ATA_DCR_BSY) == 0) {
		abs_timeout = ktime();
		abs_timeout += self->ab_timeout_BSY;
		while ((status = inb(self->ab_ctrlio)) & ATA_DCR_BSY) {
			if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF))
				return ATA_HW_GetErrorFromStatusRegister(status);
			if unlikely(ktime() >= abs_timeout)
				return ATA_ERROR(E_IOERROR_TIMEOUT, E_IOERROR_REASON_ATA_DCR_BSY);
			preemption_tryyield();
			io_delay();
		}
	}
	if (status & (ATA_DCR_ERR | ATA_DCR_DF))
		return ATA_HW_GetErrorFromStatusRegister(status);
	if (status & ATA_DCR_DRQ)
		return ATA_ERROR_OK;
	abs_timeout = ktime();
	abs_timeout += self->ab_timeout_DRQ;
	for (;;) {
		preemption_tryyield();
		io_delay();
		status = inb(self->ab_ctrlio);
		if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF))
			return ATA_HW_GetErrorFromStatusRegister(status);
		if unlikely(ktime() >= abs_timeout)
			return ATA_ERROR(E_IOERROR_TIMEOUT, E_IOERROR_REASON_ATA_DCR_BSY);
		if (status & ATA_DCR_DRQ)
			break;
	}
	return ATA_ERROR_OK;
}

/* Reset the given bus on a hardware-level. */
#define AtaBus_HW_ResetBus(self) AtaBus_HW_ResetBus_P((self)->ab_ctrlio)
PRIVATE NOBLOCK void
NOTHROW(FCALL AtaBus_HW_ResetBus_P)(port_t ctrlio) {
	outb(ctrlio, ATA_CTRL_SRST);
	AtaBus_HW_SelectDelay_P(ctrlio);
	outb(ctrlio, 0);
	AtaBus_HW_SelectDelay_P(ctrlio);
}

/* Same as `AtaBus_HW_ResetBus()', but re-initialize DMA afterwards. */
PRIVATE NOBLOCK void
NOTHROW(FCALL AtaBus_HW_ResetBusAndInitializeDMA)(AtaBus *__restrict self) {
	physaddr_t phys;
	AtaBus_HW_ResetBus(self);
	/* Re-set the PRDT address. */
	phys = pagedir_translate(self->ab_prdt);
	assert(phys <= (physaddr_t)UINT32_MAX);
	outl(self->ab_dmaio + DMA_PRIMARY_PRDT, (u32)phys);
}
#define AtaBus_HW_ResetBusAuto(self) \
	((self)->ab_dmaio == (port_t)-1  \
	 ? AtaBus_HW_ResetBus(bus)       \
	 : AtaBus_HW_ResetBusAndInitializeDMA(bus))






/************************************************************************/
/* DMA handling                                                         */
/************************************************************************/
#if ATA_AIO_HANDLE_FWRITING == 1
#define DMA_RW_COMMAND(aio_flags)          dma_rw_command[(aio_flags)&1]
#define DMA_RW_COMMAND_EXT(aio_flags)      dma_rw_command_ext[(aio_flags)&1]
#define DMA_DMA_COMMAND(aio_flags)         dma_dma_command[(aio_flags)&1]
#define DMA_DMA_COMMAND_ENABLED(aio_flags) dma_dma_command_enabled[(aio_flags)&1]
PRIVATE u8 const dma_rw_command[2] = { ATA_COMMAND_READ_DMA, ATA_COMMAND_WRITE_DMA };
PRIVATE u8 const dma_rw_command_ext[2] = { ATA_COMMAND_READ_DMA_EXT, ATA_COMMAND_WRITE_DMA_EXT };
PRIVATE u8 const dma_dma_command[2] = { DMA_COMMAND_FREADMODE, 0 };
PRIVATE u8 const dma_dma_command_enabled[2] = { DMA_COMMAND_FENABLED | DMA_COMMAND_FREADMODE, DMA_COMMAND_FENABLED };
#else /* ATA_AIO_HANDLE_FWRITING == 1 */
#define DMA_RW_COMMAND(aio_flags)          ((aio_flags)&ATA_AIO_HANDLE_FWRITING ? ATA_COMMAND_WRITE_DMA : ATA_COMMAND_READ_DMA)
#define DMA_RW_COMMAND_EXT(aio_flags)      ((aio_flags)&ATA_AIO_HANDLE_FWRITING ? ATA_COMMAND_WRITE_DMA_EXT : ATA_COMMAND_READ_DMA_EXT)
#define DMA_DMA_COMMAND(aio_flags)         ((aio_flags)&ATA_AIO_HANDLE_FWRITING ? 0 : DMA_COMMAND_FREADMODE)
#define DMA_DMA_COMMAND_ENABLED(aio_flags) ((aio_flags)&ATA_AIO_HANDLE_FWRITING ? DMA_COMMAND_FENABLED : (DMA_COMMAND_FENABLED | DMA_COMMAND_FREADMODE))
#endif /* ATA_AIO_HANDLE_FWRITING != 1 */

PRIVATE NOBLOCK NONNULL((1)) void NOTHROW(KCALL AtaDrive_DmaAioHandle_Fini)(struct aio_handle *__restrict self);
PRIVATE NOBLOCK NONNULL((1)) void NOTHROW(KCALL AtaDrive_DmaAioHandle_Cancel)(struct aio_handle *__restrict self);
PRIVATE NOBLOCK NONNULL((1)) unsigned int NOTHROW(KCALL AtaDrive_DmaAioHandle_Progress)(struct aio_handle *__restrict self, struct aio_handle_stat *__restrict stat);

/* Type used for DMA-AIO handles. */
PRIVATE struct aio_handle_type const AtaDrive_DmaAioHandleType = {
	.ht_fini     = &AtaDrive_DmaAioHandle_Fini,
	.ht_cancel   = &AtaDrive_DmaAioHandle_Cancel,
	.ht_progress = &AtaDrive_DmaAioHandle_Progress,
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL AtaDrive_DmaAioHandle_Fini)(struct aio_handle *__restrict self) {
	AtaAIOHandleData *data;
	data = (AtaAIOHandleData *)self->ah_data;
	assertf(data->hd_bufaddr == 0,
	        "This should have been set to 0 when "
	        "the operation was started or canceled!");
	/* NOTE: DMA locks will have already been released during completion/cancel! */
	decref_unlikely(data->hd_drive);
}

/* Cancel the currently active hardware-level DMA operation */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL AtaBus_HW_CancelDma)(AtaBus *__restrict self) {
	u8 dma_status;
	assert((atomic_read(&self->ab_state) & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_INDMA);
	assert(atomic_read(&self->ab_aio_current) == NULL);
	ATA_VERBOSE("[ata] Cancel active DMA on IDE ("
	            "bus:%#" PRIxN(__SIZEOF_PORT_T__) ","
	            "ctrl:%#" PRIxN(__SIZEOF_PORT_T__) ","
	            "dma:%#" PRIxN(__SIZEOF_PORT_T__) ")\n",
	            self->ab_busio, self->ab_ctrlio, self->ab_dmaio);
	do {
		outb(self->ab_dmaio + DMA_PRIMARY_COMMAND, 0);
	} while (inb(self->ab_dmaio + DMA_PRIMARY_STATUS) & DMA_STATUS_FDMARUNNING);

	/* If the ATA already asserted an interrupt, clear that interrupt now, so
	 * our interrupt handler won't get  confused and possibly think that  our
	 * interrupt was related to the follow-up DMA descriptor.
	 * If we detect an interrupt here, clearing it immediately will still leave
	 * a sporadic interrupt to be fired, but that's OK. */
	dma_status = inb(self->ab_dmaio + DMA_PRIMARY_STATUS);
	if (dma_status & DMA_STATUS_FINTERRUPTED) {
		outb(self->ab_dmaio + DMA_PRIMARY_STATUS,
		     DMA_STATUS_FDMARUNNING |
		     DMA_STATUS_FINTERRUPTED);
	}

	/* Also read from the normal status port, which is something one can
	 * do to (sometimes) prevent the  ATA bus from firing an  interrupt. */
	inb(self->ab_dmaio + ATA_STATUS);
}

/* Remove the specific `handle' from `*pchain', and write a pointer to
 * the last element of `*pchain', irregardless of `handle' having been
 * removed.
 * @return: true:  `handle' was removed
 * @return: false: `handle' could not be found. */
PRIVATE NOBLOCK NOPREEMPT bool
NOTHROW(KCALL AioHandleChain_RemoveSpecific)(/*in|out*/ struct aio_handle **__restrict pchain,
                                             /*   out*/ struct aio_handle **__restrict pchain_last,
                                             /*in    */ struct aio_handle *__restrict handle) {
	struct aio_handle **piter, *iter;
	piter = pchain;
	iter  = *piter;
	if likely(iter) {
		for (;;) {
			if (iter == handle) {
				/* found it! */
				iter = iter->ah_next;
				*piter = iter;
				if (!iter) {
					/* last  element was removed. The new last element is it's predecessor,
					 * or a NULL-pointer if the removed element was also the first element. */
					if (piter == pchain) {
						assert(*pchain == NULL);
						iter = NULL;
					} else {
						iter = container_of(piter, struct aio_handle, ah_next);
					}
				} else {
					/* Walk until we find the last element in the chain. */
					while (iter->ah_next)
						iter = iter->ah_next;
				}
				*pchain_last = iter;
				return true;
			}
			/* Continue until we encounter the end of the chain. */
			if (!iter->ah_next)
				break;
			piter = &iter->ah_next;
			iter  = *piter;
		}
	}
	*pchain_last = iter;
	return false;
}

/* Forward declarations... */
PRIVATE NOBLOCK void NOTHROW(KCALL AtaBus_TryStartNextDmaOperation)(AtaBus *__restrict self);
PRIVATE NOBLOCK void NOTHROW(FCALL AtaBus_StartNextDmaOperation)(AtaBus *__restrict self);


/* Implementation of the `RESTORE_ALL()' function from <kernel/aio.h> */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) void
NOTHROW(KCALL AtaBus_RestorePendingAioHandles)(AtaBus *__restrict self,
                                               struct aio_handle *first,
                                               struct aio_handle *last) {
	struct aio_handle *next;
	do {
		next = atomic_read(&self->ab_aio_pending);
		atomic_write(&last->ah_next, next);
	} while (!atomic_cmpxch_weak(&self->ab_aio_pending,
	                             next, first));
#if 0 /* We have no AIO-avail signal, because we don't use an async-worker! */
	if (!next)
		sig_broadcast_nopr(&self->d_aio_avail);
#endif
}



/* Remove a specific, given `handle' from the chain of pending handles of `self'.
 * The caller must have already cleared the command descriptor of `handle' before
 * calling this function, and preemption must be disabled.
 * HINT: This function implements the `d_aio_pending.REMOVE' operation from <kernel/aio.h> */
PRIVATE NOBLOCK NOPREEMPT void
NOTHROW(KCALL AtaBus_RemoveSpecificPendingAioHandle_NoPR)(AtaBus *__restrict self,
                                                          struct aio_handle *__restrict handle) {
	struct aio_handle *chain, *last;
	bool removed;
#ifndef CONFIG_NO_SMP
again:
#endif /* !CONFIG_NO_SMP */
	chain   = atomic_xch(&self->ab_aio_pending, NULL);
	removed = AioHandleChain_RemoveSpecific(&chain, &last, handle);
	/* Restore the remaining elements. */
	assert((chain != NULL) == (last != NULL));
	if (chain) {
		AtaBus_RestorePendingAioHandles(self, chain, last);
		/* Try to start a new DMA operation, using the (re-)added AIO handles. */
		AtaBus_TryStartNextDmaOperation(self);
	}
#ifndef CONFIG_NO_SMP
	if (!removed) {
		preemption_tryyield_nopr();
		goto again;
	}
#else /* !CONFIG_NO_SMP */
	assert(removed);
#endif /* CONFIG_NO_SMP */
}

/* Cancel a DMA-AIO handle (s.a. <kernel/aio.h>:[aio_cancel(aio)]) */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL AtaDrive_DmaAioHandle_Cancel)(struct aio_handle *__restrict self) {
	AtaAIOHandleData *data;
	PHYS u32 bufaddr;
	preemption_flag_t was;
	AtaBus *bus;
	data = (AtaAIOHandleData *)self->ah_data;
	bus  = data->hd_drive->ad_bus;
	/* Try to clear the command descriptor. (for which we use the PRD buffer pointer) */
	preemption_pushoff(&was);
	bufaddr = atomic_xch(&data->hd_bufaddr, NULL);
	if (bufaddr != 0) { /* Canceled before started */
		/* Remove  the entry from  pending AIO. Having successfully
		 * cleared the command-pointer, we know that our AIO handle
		 * hasn't been, and no longer  can be started (though  it's
		 * still  apart of the pending chain, from which we need to
		 * remove it now) */
		AtaBus_RemoveSpecificPendingAioHandle_NoPR(bus, self);
		goto do_cancel;
	}

	/* If the cmd-pointer was already cleared, then the AIO operation
	 * is either  current  in  progress, or  has  already  completed. */
	if (atomic_cmpxch(&bus->ab_aio_current, self, NULL)) {

		/* Cancel the currently in-progress AIO operation on a hardware-level. */
		AtaBus_HW_CancelDma(bus);

		/* At this point, the DMA operation has been canceled, but our software bus
		 * controller is still in cancel mode (state == INDMA && current ==  NULL),
		 * so we have to resume  execution by trying to  load the next pending  AIO
		 * handle, or switching to READY when no other pending handles exist.
		 *
		 * Luckily, all of this can be done for us by `AtaBus_StartNextDmaOperation()' */
		AtaBus_StartNextDmaOperation(bus);

		goto do_cancel;
	}

	/* And we're finished! */
	preemption_pop(&was);
	return;
do_cancel:
	aio_handle_complete_nopr(self, AIO_COMPLETION_CANCEL);
	preemption_pop(&was);
}

/* Return the # of bytes that have already been transferred as part
 * of the currently in-progress AIO operation. If no AIO  operation
 * is currently in progress, the return value is weakly undefined. */
PRIVATE NOBLOCK size_t
NOTHROW(FCALL AtaBus_HW_GetDmaProgress)(AtaBus *__restrict self) {
	/* TODO: Research if there  some way of  determining
	 *       how much of a DMA operation is already done */
	COMPILER_IMPURE();
	(void)self;
	return 0;
}

PRIVATE NOBLOCK NONNULL((1)) unsigned int
NOTHROW(KCALL AtaDrive_DmaAioHandle_Progress)(struct aio_handle *__restrict self,
                                              struct aio_handle_stat *__restrict stat) {
	AtaAIOHandleData *data = (AtaAIOHandleData *)self->ah_data;
	AtaBus *bus;
	assert(self->ah_type == &AtaDrive_DmaAioHandleType);
	stat->hs_total = ((size_t)data->hd_io_sectors[0] |
	                  (size_t)data->hd_io_sectors[1]) <<
	                 AtaDrive_GetSectorShift(data->hd_drive);
	bus = data->hd_drive->ad_bus;
	if (atomic_read(&bus->ab_aio_current) == self) {
		/* Query the hardware for how far we've already come. */
hw_progress:
		stat->hs_completed = AtaBus_HW_GetDmaProgress(bus);
		if (atomic_read(&bus->ab_aio_current) == self) {
			if unlikely(stat->hs_completed > stat->hs_total)
				stat->hs_completed = stat->hs_total; /* Ensure consistency */
			return AIO_PROGRESS_STATUS_INPROGRESS;
		}
	}
	if (atomic_read(&data->hd_bufaddr) == 0) {
		/* Check for race condition: The hardware just started working with us. */
		if (atomic_read(&bus->ab_aio_current) == self)
			goto hw_progress;
		/* We're not the current handle, but we were started at one point.
		 * This means  that  we've  either  been  completed  or  canceled. */
		stat->hs_completed = stat->hs_total;
		return AIO_PROGRESS_STATUS_COMPLETED;
	}
	stat->hs_completed = 0;
	return AIO_PROGRESS_STATUS_PENDING;
}



/* Select a pending AIO handle and try to start it.
 *
 * For  this purpose, the handle's `hd_bufaddr' field is zeroed out after
 * being copied to `*p_bufaddr'. This must be done in order to atomically
 * write-back  the fact that the AIO operation has been started, changing
 * the behavior of the AIO handle's cancel operation to account for  this
 * fact.
 *
 * When no AIO handles are available at the moment, this function simply
 * returns `NULL' */
PRIVATE NOBLOCK NOPREEMPT struct aio_handle *
NOTHROW(KCALL AtaBus_ActivateAioHandle_NoPR)(AtaBus *__restrict self,
                                             PHYS u32 *__restrict p_bufaddr) {
	struct aio_handle *chain, **piter, *iter;
	chain = atomic_xch(&self->ab_aio_pending, NULL);
	if (!chain)
		return NULL;
	/* Find an AIO handle for which we can steal the command
	 * descriptor, which we  implement as  the handle's  PRD
	 * pointer field. */
	piter = &chain;
	for (;;) {
		AtaAIOHandleData *data;
		PHYS u32 iter_prd;
		iter = *piter;
		/* Try to activate this handle. */
		data = (AtaAIOHandleData *)iter->ah_data;
		/* Must set `ab_aio_current' _before_ we  tell the handle that  we've
		 * started  it, since  the AIO-CANCEL  operation assumes  that a NULL
		 * command descriptor means that `ab_aio_current == handle' indicates
		 * that the handle's operation is currently in service, with breaking
		 * that link being the first  step in canceling the operation,  while
		 * equality  not holding  true means  that the  operation has already
		 * completed. */
		atomic_write(&self->ab_aio_current, iter);
		iter_prd = atomic_xch(&data->hd_bufaddr, NULL);
		if likely(iter_prd != 0) {
			/* Got it! */
			*p_bufaddr = iter_prd;
			/* Unlink `iter' from the chain. */
			*piter = iter->ah_next;
			/* Restore the chain */
			if (iter->ah_next) {
				struct aio_handle *next;
				next = iter->ah_next;
				while (next->ah_next)
					next = next->ah_next;
				AtaBus_RestorePendingAioHandles(self, chain, next);
			} else if unlikely(chain) {
				struct aio_handle *prev;
				prev = container_of(piter, struct aio_handle, ah_next);
				AtaBus_RestorePendingAioHandles(self, chain, prev);
			}
			return iter;
		}
		if (!iter->ah_next)
			break;
		piter = &iter->ah_next;
		iter  = *piter;
	}
	AtaBus_RestorePendingAioHandles(self, chain, iter);
	atomic_write(&self->ab_aio_current, NULL); /* Indicate a CANCEL state. */
	return NULL;
}

/* Complete the given AIO handle with an ATA error code. */
PRIVATE NOBLOCK ATTR_COLD NONNULL((1)) void
NOTHROW(FCALL AtaDrive_DmaAioHandle_CompleteWithError)(struct aio_handle *__restrict self,
                                                       AtaError_t error) {
	struct exception_data old_data;
	struct exception_data *mydata = &THIS_EXCEPTION_DATA;
	memcpy(&old_data, mydata, sizeof(struct exception_data));
	bzero(mydata, sizeof(struct exception_data));
	mydata->e_code = EXCEPT_CODE(ATA_EXCEPT_CLASS(error), ATA_EXCEPT_SUBCLASS(error));
	mydata->e_args.e_ioerror.i_subsystem = E_IOERROR_SUBSYSTEM_HARDDISK;
	mydata->e_args.e_ioerror.i_reason    = ATA_ERROR_REASON(error);
	COMPILER_BARRIER();
	aio_handle_complete(self, AIO_COMPLETION_FAILURE);
	COMPILER_BARRIER();
	memcpy(mydata, &old_data, sizeof(struct exception_data));
}


/* Same as `AtaBus_HW_StartDma()', but assume that `self->ab_prdt' is already initialized. */
PRIVATE NOBLOCK bool
NOTHROW(FCALL AtaBus_HW_StartDirectDma)(AtaBus *__restrict self,
                                        struct aio_handle *__restrict handle) {
	unsigned int reset_counter = 0;
	AtaError_t error;
	AtaAIOHandleData *data;
	data = (AtaAIOHandleData *)handle->ah_data;
	assert((atomic_read(&self->ab_state) & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_INDMA);
#ifndef NDEBUG
	{
		struct aio_handle *current;
		current = atomic_read(&self->ab_aio_current);
		/* Can be NULL if we've already been canceled. */
		assert(current == handle || current == NULL);
	}
#endif /* !NDEBUG */
again:
	ATA_VERBOSE("[ata] Starting %s-DMA operation [lba=%" PRIu64 "] [sector_count=%" PRIu16 "] "
	            "[prd0:%" PRIp32 "+%" PRIu32 "]\n",
	            data->hd_flags & ATA_AIO_HANDLE_FWRITING ? "Write" : "Read",
	            (u64)((u64)data->hd_io_lbaaddr[0] |
	                  (u64)data->hd_io_lbaaddr[1] << 8 |
	                  (u64)data->hd_io_lbaaddr[2] << 16 |
	                  (u64)data->hd_io_lbaaddr[3] << 24 |
	                  (u64)data->hd_io_lbaaddr[4] << 32 |
	                  (u64)data->hd_io_lbaaddr[5] << 40),
	            (u16)((u16)data->hd_io_sectors[0] |
	                  (u16)data->hd_io_sectors[1] << 8),
	            self->ab_prdt[0].p_bufaddr,
	            self->ab_prdt[0].p_bufsize
	            ? (u32)self->ab_prdt[0].p_bufsize
	            : (u32)0x10000);
	assert(data->hd_drive->ad_bus == self);
	assert(self->ab_dmaio != (port_t)-1);
	assert(handle->ah_type == &AtaDrive_DmaAioHandleType);

	/* Configure DMA */
	outb(self->ab_dmaio + DMA_PRIMARY_COMMAND,
	     DMA_DMA_COMMAND(data->hd_flags));
	outb(self->ab_dmaio + DMA_PRIMARY_STATUS,
	     DMA_STATUS_FDMARUNNING |
	     DMA_STATUS_FTRANSPORT_FAILURE |
	     DMA_STATUS_FINTERRUPTED);

	/* Wait for BSY to go away. */
	error = AtaBus_HW_WaitForBusy(self);
	if unlikely(error != ATA_ERROR_OK)
		goto handle_io_error;

	/* Figure out how we should instantiate the DMA operation. */
	assert(data->hd_drive->ad_drive == ATA_DRIVE_MASTER ||
	       data->hd_drive->ad_drive == ATA_DRIVE_SLAVE);
	if (data->hd_io_sectors[1] || (data->hd_io_lbaaddr[3] & 0xf0) ||
	    data->hd_io_lbaaddr[4] || data->hd_io_lbaaddr[5]) {
		/* Configure for LBA48 */
		ATA_VERBOSE("[ata] Start dma (lba48+%s)\n",
		            data->hd_flags & ATA_AIO_HANDLE_FWRITING ? "write" : "read");
		outb(self->ab_busio + ATA_DRIVE_SELECT, data->hd_drive->ad_drive);
		AtaBus_HW_SelectDelay(self);
		outb(self->ab_busio + ATA_SECTOR_COUNT, data->hd_io_sectors[1]);
		outb(self->ab_busio + ATA_ADDRESS1, data->hd_io_lbaaddr[3]);
		outb(self->ab_busio + ATA_ADDRESS2, data->hd_io_lbaaddr[4]);
		outb(self->ab_busio + ATA_ADDRESS3, data->hd_io_lbaaddr[5]);
		outb(self->ab_busio + ATA_SECTOR_COUNT, data->hd_io_sectors[0]);
		outb(self->ab_busio + ATA_ADDRESS1, data->hd_io_lbaaddr[0]);
		outb(self->ab_busio + ATA_ADDRESS2, data->hd_io_lbaaddr[1]);
		outb(self->ab_busio + ATA_ADDRESS3, data->hd_io_lbaaddr[2]);
		outb(self->ab_busio + ATA_COMMAND, DMA_RW_COMMAND_EXT(data->hd_flags));
	} else {
		/* Configure for LBA28 (which can be done faster than 48, so use it if possible) */
		ATA_VERBOSE("[ata] Start dma (lba28+%s)\n",
		            data->hd_flags & ATA_AIO_HANDLE_FWRITING ? "write" : "read");
		outb(self->ab_busio + ATA_DRIVE_SELECT,
		     (0xe0 | (data->hd_drive->ad_drive - ATA_DRIVE_MASTER)) |
		     (data->hd_io_lbaaddr[3] & 0xf));
		AtaBus_HW_SelectDelay_P(self->ab_ctrlio);
		outb(self->ab_busio + ATA_SECTOR_COUNT, data->hd_io_sectors[0]);
		outb(self->ab_busio + ATA_ADDRESS1, data->hd_io_lbaaddr[0]);
		outb(self->ab_busio + ATA_ADDRESS2, data->hd_io_lbaaddr[1]);
		outb(self->ab_busio + ATA_ADDRESS3, data->hd_io_lbaaddr[2]);
		outb(self->ab_busio + ATA_COMMAND, DMA_RW_COMMAND(data->hd_flags));
	}
	error = AtaBus_HW_WaitForBusy(self);
	if unlikely(error != ATA_ERROR_OK)
		goto handle_io_error;

	/* This following outb() is what actually activates hardware-DMA */
	outb(self->ab_dmaio + DMA_PRIMARY_COMMAND,
	     DMA_DMA_COMMAND_ENABLED(data->hd_flags));

	/* At this point the DMA operation has started! */
	return true;
handle_io_error:

	/* Always reset the bus (even if merely done for the next access) */
	printk(KERN_ERR "[ata] Reseting IDE on DMA-I/O error code "
	                "%#" PRIx16 ":%#" PRIx16 ":%#" PRIx16 " ("
	                "bus:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                "ctrl:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                "dma:%#" PRIxN(__SIZEOF_PORT_T__) ")\n",
	       (u16)ATA_EXCEPT_CLASS(error),
	       (u16)ATA_EXCEPT_SUBCLASS(error),
	       (u16)ATA_ERROR_REASON(error),
	       self->ab_busio,
	       self->ab_ctrlio,
	       self->ab_dmaio);

	/* Reset and re-initialize the BUS and its DMA controller. */
	AtaBus_HW_ResetBusAndInitializeDMA(self);

	/* Re-attempt initialization a couple of times. */
	if (reset_counter < self->ab_dma_retry) {
		++reset_counter;
		goto again;
	}

	/* Complete the given AIO handle with the error code. */
	AtaDrive_DmaAioHandle_CompleteWithError(handle, error);

	/* Tell our caller that we weren't able to launch an AIO operation. */
	self->ab_aio_current = NULL;
	return false;
}

/* Start a hardware-level DMA operation for the given `handle'
 * @return: true:  DMA has been initiated
 * @return: false: The handle was canceled before DMA could begin (try the next handle!) */
PRIVATE NOBLOCK bool
NOTHROW(FCALL AtaBus_HW_StartDma)(AtaBus *__restrict self,
                                  struct aio_handle *__restrict handle,
                                  PHYS u32 bufaddr) {
	AtaAIOHandleData *data;
	data = (AtaAIOHandleData *)handle->ah_data;

	/* Copy the PRDT into the bus's buffer. */
	self->ab_prdt[0].p_bufaddr = bufaddr;
	self->ab_prdt[0].p_bufsize = data->hd_bufsize;
	self->ab_prdt[0].p_flags   = PRD_FLAST;

	/* Start the DMA operation. */
	return AtaBus_HW_StartDirectDma(self, handle);
}

/* Start the next pending DMA operation (if there is one). Otherwise,
 * switch the bus's state ATA_BUS_STATE_INDMA -> ATA_BUS_STATE_READY.
 * If there are pending WANTPIO requests, always switch to READY, and
 * signal a single waiting thread. */
PRIVATE NOBLOCK void
NOTHROW(FCALL AtaBus_StartNextDmaOperation)(AtaBus *__restrict self) {
	struct aio_handle *handle;
	PHYS u32 bufaddr;
	uintptr_t state;
again:
	state = atomic_read(&self->ab_state);
	assert((state & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_INDMA);

	/* Check if we're to switch to PIO mode. */
	if ((state & ATA_BUS_STATE_WANTPIO) != 0) {
		if (!atomic_cmpxch_weak(&self->ab_state,
		                        state,
		                        (state & ~ATA_BUS_STATE_MASK) |
		                        ATA_BUS_STATE_READY))
			goto again;

		/* Wake-up up to one waiting thread. */
		sig_send(&self->ab_ready);
		return;
	}

	/* Check for further pending DMA handles. */
#ifndef __OPTIMIZE_SIZE__
	if unlikely(atomic_read(&self->ab_aio_pending) == NULL)
		goto no_handles;
#define WANT_no_handles
#endif /* !__OPTIMIZE_SIZE__ */
	{
		preemption_flag_t was;
		preemption_pushoff(&was);
		handle = AtaBus_ActivateAioHandle_NoPR(self, &bufaddr);
		preemption_pop(&was);
	}

	if unlikely(!handle) {
		uintptr_t state;
#ifdef WANT_no_handles
#undef WANT_no_handles
no_handles:
#endif /* WANT_no_handles */
		/* No available handles. -> Switch to READY
		 * and check  for pending  AIO once  again. */
#if ATA_BUS_STATE_READY == 0
		atomic_and(&self->ab_state, ~ATA_BUS_STATE_MASK);
#else /* ATA_BUS_STATE_READY == 0 */
		do {
			state = atomic_read(&self->ab_state);
		} while (!atomic_cmpxch_weak(&self->ab_state, state,
		                             (state & ~ATA_BUS_STATE_MASK) |
		                             ATA_BUS_STATE_READY));
#endif /* ATA_BUS_STATE_READY != 0 */
		if (atomic_read(&self->ab_aio_pending) != NULL) {
			preemption_tryyield();
			if (atomic_read(&self->ab_aio_pending) != NULL) {
				for (;;) {
					/* Try once again to start a DMA operation. */
					state = atomic_read(&self->ab_state);
					if ((state & ATA_BUS_STATE_MASK) != ATA_BUS_STATE_READY)
						break;
					if (atomic_cmpxch_weak(&self->ab_state, state,
					                       (state & ~ATA_BUS_STATE_MASK) |
					                       ATA_BUS_STATE_INDMA))
						goto again;
				}
			}
		}
		return;
	}

	/* Start the DMA operation on a hardware-level. */
	if (!AtaBus_HW_StartDma(self, handle, bufaddr))
		goto again;
}

/* Same as `AtaBus_StartNextDmaOperation()', but only do so if the bus's
 * state can  be  switched  ATA_BUS_STATE_READY  ->  ATA_BUS_STATE_INDMA */
PRIVATE NOBLOCK void
NOTHROW(KCALL AtaBus_TryStartNextDmaOperation)(AtaBus *__restrict self) {
	uintptr_t state;
	do {
		state = atomic_read(&self->ab_state);
		if ((state & ATA_BUS_STATE_MASK) != ATA_BUS_STATE_READY)
			return; /* Bus isn't ready */
	}
#if ATA_BUS_STATE_READY == 0
	while (!atomic_cmpxch_weak(&self->ab_state, state,
	                           state | ATA_BUS_STATE_INDMA));
#else /* ATA_BUS_STATE_READY == 0 */
	while (!atomic_cmpxch_weak(&self->ab_state, state,
	                           (state & ~ATA_BUS_STATE_MASK) |
	                           ATA_BUS_STATE_INDMA));
#endif /* ATA_BUS_STATE_READY != 0 */
	AtaBus_StartNextDmaOperation(self);
}

/* Append the given `handle' onto the chain of pending AIO operations. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL AtaBus_AppendDmaAioHandle)(AtaBus *__restrict self,
                                         struct aio_handle *__restrict handle) {
	struct aio_handle *next;
	assert(handle->ah_type == &AtaDrive_DmaAioHandleType);
	assert(self->ab_dmaio != (port_t)-1);
	do {
		next = atomic_read(&self->ab_aio_pending);
		atomic_write(&handle->ah_next, next);
	} while (!atomic_cmpxch_weak(&self->ab_aio_pending,
	                             next, handle));
	/* If this is the first pending operation, try to initiate DMA */
	if (!next)
		AtaBus_TryStartNextDmaOperation(self);
}








/************************************************************************/
/* Interrupt handlers                                                   */
/************************************************************************/

/* Return the interrupt handler to use for `AtaBus *self' */
#define AtaBus_HW_GetInterruptHandler(self) \
	((self)->ab_dmaio != (port_t)-1         \
	 ? &AtaBus_HW_DmaInterruptHandler       \
	 : &AtaBus_HW_InterruptHandler)

PRIVATE NOBLOCK NOPREEMPT void
NOTHROW(FCALL seed_entropy)(void) {
	entropy_giveint_nopr(tsc_get(THIS_CPU), 1);
}

/* Handle an unexpected ATA interrupt. */
PRIVATE NOBLOCK NOPREEMPT bool
NOTHROW(FCALL AtaBus_HW_UnexpectedInterrupt)(AtaBus *__restrict self) {
	printk(KERN_WARNING "[ata] Unexpected IDE interrupt ("
	                    "bus:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                    "ctrl:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                    "dma:%#" PRIxN(__SIZEOF_PORT_T__) ")\n",
	       self->ab_busio, self->ab_ctrlio, self->ab_dmaio);
	return true;
}

/* Complete successfully. */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL AtaDrive_DmaAioHandle_Complete_NoPR)(struct aio_handle *__restrict self) {
	COMPILER_BARRIER();
	aio_handle_complete_nopr(self, AIO_COMPLETION_SUCCESS);
	COMPILER_BARRIER();
}

/* Interrupt handler for ATA BUS controllers. */
PRIVATE NOBLOCK NOPREEMPT bool
NOTHROW(FCALL AtaBus_HW_InterruptHandler)(AtaBus *__restrict self) {
	u8 status;
	seed_entropy();
	/* BUS without DMA support */
	status = inb(self->ab_busio + ATA_STATUS);
	ATA_VERBOSE("[ata] IDE interrupt on "
	            "bus:%#" PRIxN(__SIZEOF_PORT_T__) ","
	            "ctrl:%#" PRIxN(__SIZEOF_PORT_T__) " "
	            "[bus_status=%#.2" PRIx8 "]\n",
	            self->ab_busio, self->ab_ctrlio, status);
	switch (atomic_read(&self->ab_state)) {

	case ATA_BUS_STATE_INPIO:
		/* Broadcast the PIO interrupt handler. */
		sig_altbroadcast(&self->ab_piointr, ATA_PIOINTR_ALT_ENCODE(status));
		break;

	default:
		return AtaBus_HW_UnexpectedInterrupt(self);
	}
	return true;
}

/* Same as `AtaBus_HW_InterruptHandler()', but used if the bus supports DMA */
PRIVATE NOBLOCK NOPREEMPT bool
NOTHROW(FCALL AtaBus_HW_DmaInterruptHandler)(AtaBus *__restrict self) {
	u8 status, dma_status;
	dma_status = inb(self->ab_dmaio + DMA_PRIMARY_STATUS);
	if (!(dma_status & DMA_STATUS_FINTERRUPTED))
		return false; /* This bus didn't assert an interrupt */
	seed_entropy();
	outb(self->ab_dmaio + DMA_PRIMARY_STATUS,
	     DMA_STATUS_FDMARUNNING |
	     DMA_STATUS_FINTERRUPTED);
	status = inb(self->ab_busio + ATA_STATUS); /* Must always be read... */
	ATA_VERBOSE("[ata] IDE interrupt on "
	            "bus:%#" PRIxN(__SIZEOF_PORT_T__) ","
	            "ctrl:%#" PRIxN(__SIZEOF_PORT_T__) ","
	            "dma:%#" PRIxN(__SIZEOF_PORT_T__) " "
	            "[bus_status=%#.2" PRIx8 ",dma_status=%#.2" PRIx8 "]\n",
	            self->ab_busio, self->ab_ctrlio, self->ab_dmaio,
	            status, dma_status);
	switch (atomic_read(&self->ab_state) & ATA_BUS_STATE_MASK) {

	case ATA_BUS_STATE_INDMA: {
		struct aio_handle *handle;
		/* A DMA operation has been completed. */
		handle = atomic_xch(&self->ab_aio_current, NULL);
		if unlikely(!handle) {
			/* This can happen if the handle is currently being  canceled,
			 * but the cancel request itself was made before we could tell
			 * hardware that DMA should be stopped. */
			break;
		}

		if (dma_status & DMA_STATUS_FTRANSPORT_FAILURE) {
			AtaDrive_DmaAioHandle_CompleteWithError(handle,
			                                        ATA_ERROR(E_IOERROR_ERRORBIT,
			                                                  E_IOERROR_REASON_ATA_DMA_ERR));
		} else {
			ATA_VERBOSE("[ata] Signal DMA success on "
			            "bus:%#" PRIxN(__SIZEOF_PORT_T__) ","
			            "ctrl:%#" PRIxN(__SIZEOF_PORT_T__) ","
			            "dma:%#" PRIxN(__SIZEOF_PORT_T__) "\n",
			            self->ab_busio, self->ab_ctrlio, self->ab_dmaio);
			/* Indicate a successful completion of the data transfer */
			AtaDrive_DmaAioHandle_Complete_NoPR(handle);
		}
		/* Start the next pending DMA operation, or switch state to READY. */
		AtaBus_StartNextDmaOperation(self);
	}	break;

	case ATA_BUS_STATE_INPIO:
		/* Broadcast the bus status. */
		sig_altbroadcast_nopr(&self->ab_piointr, ATA_PIOINTR_ALT_ENCODE(status));
		break;

	default:
		return AtaBus_HW_UnexpectedInterrupt(self);
	}
	return true;
}








/************************************************************************/
/* PIO Bus locking                                                      */
/************************************************************************/

/* Acquire/release a PIO lock for the given ata bus, allowing
 * the  caller to  perform bus  I/O using  PIO data channels. */
PRIVATE NONNULL((1)) void FCALL
AtaBus_LockPIO(AtaBus *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	uintptr_t state;
again:
	state = atomic_read(&self->ab_state);

	/* Check if we can directly switch to PIO mode. */
	if ((state & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_READY) {
#if ATA_BUS_STATE_READY == 0
		if (atomic_cmpxch_weak(&self->ab_state,
		                       state,
		                       state | ATA_BUS_STATE_INPIO))
			return;
#else /* ATA_BUS_STATE_READY == 0 */
		if (atomic_cmpxch_weak(&self->ab_state,
		                       state,
		                       (state & ~ATA_BUS_STATE_MASK) |
		                       ATA_BUS_STATE_INPIO))
			return;
#endif /* ATA_BUS_STATE_READY != 0 */
	}

	/* Increment the PIO request counter. */
	if (!atomic_cmpxch_weak(&self->ab_state,
	                        state,
	                        state + ATA_BUS_STATE_ONEPIO))
		goto again;

	/* Wait for the bus to become ready. */
	TRY {
again_waitfor:
		/* Wait for PIO to become available. */
		task_waitwhile(&self->ab_ready,
		               (state = atomic_read(&self->ab_state),
		                (state & ATA_BUS_STATE_MASK) != ATA_BUS_STATE_READY));

		/* Atomically switch to PIO mode, and release our PIO request ticket. */
#if ATA_BUS_STATE_READY == 0
		if (!atomic_cmpxch_weak(&self->ab_state,
		                        state,
		                        (state - ATA_BUS_STATE_ONEPIO) |
		                        ATA_BUS_STATE_INPIO))
			goto again_waitfor;
#else /* ATA_BUS_STATE_READY == 0 */
		if (!atomic_cmpxch_weak(&self->ab_state,
		                        state,
		                        ((state - ATA_BUS_STATE_ONEPIO) & ~ATA_BUS_STATE_MASK) |
		                        ATA_BUS_STATE_INPIO))
			goto again_waitfor;
#endif /* ATA_BUS_STATE_READY != 0 */
	} EXCEPT {
		atomic_sub(&self->ab_state, ATA_BUS_STATE_ONEPIO);
		RETHROW();
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL AtaBus_UnlockPIO)(AtaBus *__restrict self) {
	uintptr_t state;
	uintptr_t new_state;
again:
	state = atomic_read(&self->ab_state);
	assert((state & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_INPIO);

	/* If there are more PIO requests, switch back to ready,
	 * rather than resuming  by trying to  service more  DMA
	 * operations. */
	if ((state & ATA_BUS_STATE_WANTPIO) != 0) {
		if (!atomic_cmpxch_weak(&self->ab_state,
		                        state,
		                        (state & ~ATA_BUS_STATE_MASK) |
		                        ATA_BUS_STATE_READY))
			goto again;

		/* Wake-up up to one waiting thread. */
		sig_send(&self->ab_ready);
		return;
	}

	/* Check if there are pending AIO operations that can  be
	 * completed using DMA. If there are, then switch the bus
	 * into DMA-mode, and service them. */
	if (atomic_read(&self->ab_aio_pending) != NULL) {
		if (!atomic_cmpxch_weak(&self->ab_state,
		                        state,
		                        (state & ~ATA_BUS_STATE_MASK) |
		                        ATA_BUS_STATE_INDMA))
			goto again;
do_start_dma:
		AtaBus_StartNextDmaOperation(self);
		return;
	}

	/* Nothing to do. - Switch to READY and re-check for pending
	 * AIO operations that may have  appeared in the mean  time. */
	new_state = (state & ~ATA_BUS_STATE_MASK) | ATA_BUS_STATE_READY;
	if (!atomic_cmpxch_weak(&self->ab_state, state, new_state))
		goto again;
	if unlikely(atomic_read(&self->ab_aio_pending) != NULL) {
		/* Try to switch back to INDMA */
		if (atomic_cmpxch(&self->ab_state, new_state,
		                  (state & ~ATA_BUS_STATE_MASK) |
		                  ATA_BUS_STATE_INDMA))
			goto do_start_dma;
	} else {
		/* Nothing  else to  do. -  Broadcast to  everyone that may
		 * still be listening that the bus is ready for whatever... */
		sig_broadcast(&self->ab_ready);
	}
}






/************************************************************************/
/* ATA Drive operators                                                  */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL AtaDrive_Destroy)(struct mfile *__restrict self) {
	AtaDrive *me = mfile_asata(self);
	decref_unlikely(me->ad_bus);
	blkdev_v_destroy(me);
}

PRIVATE NONNULL((1)) void KCALL
AtaDrive_Sync(struct mfile *__restrict self)
		THROWS(...) {
	AtaDrive *me = mfile_asata(self);
	if (me->ad_features & ATA_DRIVE_FEATURE_F_FLUSH) {
		AtaBus_LockPIO(me->ad_bus);
		RAII_FINALLY { AtaBus_UnlockPIO(me->ad_bus); };

		/* TODO */
		(void)ATA_COMMAND_CACHE_FLUSH;
		COMPILER_IMPURE();
	}
}

PRIVATE struct mfile_stream_ops const atadrive_v_stream_ops = {
	.mso_ioctl = &blkdev_v_ioctl,
	.mso_tryas = &blkdev_v_tryas,
	.mso_sync  = &AtaDrive_Sync,
};


/* Low-level ATA I/O functions. */
#ifdef __INTELLISENSE__
PRIVATE NONNULL((1, 5)) void KCALL AtaDrive_RdSectorsCHS(struct mfile *__restrict self, pos_t addr, physaddr_t buf, size_t num_bytes, struct aio_multihandle *__restrict aio);
PRIVATE NONNULL((1, 5)) void KCALL AtaDrive_WrSectorsCHS(struct mfile *__restrict self, pos_t addr, physaddr_t buf, size_t num_bytes, struct aio_multihandle *__restrict aio);
PRIVATE NONNULL((1, 5)) void KCALL AtaDrive_RdSectorsLBA28(struct mfile *__restrict self, pos_t addr, physaddr_t buf, size_t num_bytes, struct aio_multihandle *__restrict aio);
PRIVATE NONNULL((1, 5)) void KCALL AtaDrive_WrSectorsLBA28(struct mfile *__restrict self, pos_t addr, physaddr_t buf, size_t num_bytes, struct aio_multihandle *__restrict aio);
PRIVATE NONNULL((1, 5)) void KCALL AtaDrive_RdSectorsLBA48(struct mfile *__restrict self, pos_t addr, physaddr_t buf, size_t num_bytes, struct aio_multihandle *__restrict aio);
PRIVATE NONNULL((1, 5)) void KCALL AtaDrive_WrSectorsLBA48(struct mfile *__restrict self, pos_t addr, physaddr_t buf, size_t num_bytes, struct aio_multihandle *__restrict aio);
PRIVATE NONNULL((1, 5)) void KCALL AtaDrive_RdSectorsDMA(struct mfile *__restrict self, pos_t addr, physaddr_t buf, size_t num_bytes, struct aio_multihandle *__restrict aio);
PRIVATE NONNULL((1, 5)) void KCALL AtaDrive_WrSectorsDMA(struct mfile *__restrict self, pos_t addr, physaddr_t buf, size_t num_bytes, struct aio_multihandle *__restrict aio);
#else /* __INTELLISENSE__ */
DECL_END
#define DEFINE_AtaDrive_RdSectorsCHS
#include "ataio.c.inl"
#define DEFINE_AtaDrive_WrSectorsCHS
#include "ataio.c.inl"
#define DEFINE_AtaDrive_RdSectorsLBA28
#include "ataio.c.inl"
#define DEFINE_AtaDrive_WrSectorsLBA28
#include "ataio.c.inl"
#define DEFINE_AtaDrive_RdSectorsLBA48
#include "ataio.c.inl"
#define DEFINE_AtaDrive_WrSectorsLBA48
#include "ataio.c.inl"
#define DEFINE_AtaDrive_RdSectorsDMA
#include "ataio.c.inl"
#define DEFINE_AtaDrive_WrSectorsDMA
#include "ataio.c.inl"
DECL_BEGIN
#endif /* !__INTELLISENSE__ */







/************************************************************************/
/* Operator tables                                                      */
/************************************************************************/
#define INITIALIZE_DRIVE_OPS(rd, wr)                     \
	{                                                    \
		.bdo_dev = {{{                                   \
			.no_file = {                                 \
				.mo_destroy    = &AtaDrive_Destroy,      \
				.mo_loadblocks = rd,                     \
				.mo_saveblocks = wr,                     \
				.mo_changed    = &blkdev_v_changed,      \
				.mo_stream     = &atadrive_v_stream_ops, \
			},                                           \
			.no_wrattr = &blkdev_v_wrattr                \
		}}},                                             \
	}
PRIVATE struct blkdev_ops const AtaDrive_DmaOps   = INITIALIZE_DRIVE_OPS(&AtaDrive_RdSectorsDMA, &AtaDrive_WrSectorsDMA);
PRIVATE struct blkdev_ops const AtaDrive_ChsOps   = INITIALIZE_DRIVE_OPS(&AtaDrive_RdSectorsCHS, &AtaDrive_WrSectorsCHS);
PRIVATE struct blkdev_ops const AtaDrive_Lba28Ops = INITIALIZE_DRIVE_OPS(&AtaDrive_RdSectorsLBA28, &AtaDrive_WrSectorsLBA28);
PRIVATE struct blkdev_ops const AtaDrive_Lba48Ops = INITIALIZE_DRIVE_OPS(&AtaDrive_RdSectorsLBA48, &AtaDrive_WrSectorsLBA48);
#undef INITIALIZE_DRIVE_OPS







/************************************************************************/
/* Initialization                                                       */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL AtaBus_Destroy)(struct refcountable *__restrict self) {
	AtaBus *me = (AtaBus *)self;
	hisr_unregister((isr_function_t)AtaBus_HW_GetInterruptHandler(me), me);
	if (me->ab_dmaio != (port_t)-1)
		mman_unmap_kram(me->ab_prdt, PAGESIZE);
	_AtaBus_Free(me);
}

PRIVATE ATTR_FREETEXT ATTR_NOINLINE bool KCALL
AtaInit_InitializeDrive(struct ata_ports *__restrict ports,
                        /*(in|out)_opt*/ REF AtaBus **__restrict p_bus,
                        u8 drive_id, bool is_primary_bus,
                        bool is_default_ide) {
	AtaBus *bus = *p_bus;
	AtaDrive *drive;
	u8 initial_status;
	struct hd_driveid specs;
	assert(drive_id == ATA_DRIVE_MASTER ||
	       drive_id == ATA_DRIVE_SLAVE);
	printk(FREESTR(KERN_INFO "[ata] Attempting to initialize %s %s ATA device {"
	                         "bus:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                         "ctl:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                         "dma:%#" PRIxN(__SIZEOF_PORT_T__) "} (default_ide: %u)\n"),
	       is_primary_bus ? FREESTR("primary") : FREESTR("secondary"),
	       drive_id == ATA_DRIVE_MASTER ? FREESTR("master") : FREESTR("slave"),
	       ports->a_bus, ports->a_ctrl,
	       ports->a_dma, is_default_ide ? 1 : 0);

	/* Check for a floating bus. */
	initial_status = inb(ports->a_bus + ATA_STATUS);
	if (initial_status == 0xff)
		return false; /* Floating bus */
	ATA_VERBOSE("[ata] initial_status: %#" PRIx8 "\n", initial_status);

	/* Do a soft reset on both ATA device control ports. */
	AtaBus_HW_ResetBus_P(ports->a_ctrl);

	/* Select the requested drive. */
	outb(ports->a_bus + ATA_DRIVE_SELECT, drive_id);
	AtaBus_HW_SelectDelay_P(ports->a_ctrl);

	/* Wait for the command to be acknowledged. */
	if (AtaBus_HW_WaitForBusy_P(ports->a_ctrl, relktime_from_seconds(3)) != ATA_ERROR_OK)
		return false;

	/* Allocate the bus controller (if necessary) */
	if (bus == NULL) {
		bus = _AtaBus_Alloc();
		bus->rca_refcnt     = 1;
		bus->rca_destroy    = &AtaBus_Destroy;
		bus->ab_state       = ATA_BUS_STATE_READY;
		bus->ab_aio_pending = NULL;
		bus->ab_aio_current = NULL;
		sig_init(&bus->ab_ready);
		sig_init(&bus->ab_piointr);
		DBG_memset(&bus->ab_prdt, 0xcc, sizeof(bus->ab_prdt));
		bus->ab_busio       = ports->a_bus;
		bus->ab_ctrlio      = ports->a_ctrl;
		bus->ab_dmaio       = ports->a_dma;
		bus->ab_dma_retry   = 3;
		bus->ab_pio_retry   = 3;
		bus->ab_timeout_BSY = relktime_from_seconds(3);
		bus->ab_timeout_DRQ = relktime_from_seconds(3);
		bus->ab_timeout_dat = relktime_from_seconds(2);
		if (bus->ab_dmaio != (port_t)-1) {
			physaddr_t phys;
			/* Allocate `ab_prdt' */
			TRY {
				/* Must allocate in 32-bit space (because the PRD register is only 32 bits large) */
				PAGEDIR_PAGEALIGNED void *addr;
				addr = mman_map_kram(MHINT_GETADDR(KERNEL_MHINT_DEVICE), PAGESIZE,
				                     gfp_from_mapflags(MHINT_GETMODE(KERNEL_MHINT_DEVICE)) |
				                     GFP_LOCKED | GFP_PREFLT | GFP_MAP_32BIT);
				/* Remember the address */
				bus->ab_prdt = (PAGEDIR_PAGEALIGNED AtaPRD *)addr;
			} EXCEPT {
				kfree(bus);
				RETHROW();
			}

			/* Tell the bus where the PRD is located. */
			phys = pagedir_translate(bus->ab_prdt);
			assert(phys <= (physaddr_t)UINT32_MAX);
			outl(bus->ab_dmaio + DMA_PRIMARY_PRDT, (u32)phys);
		}
		TRY {
			/* The BUS structure must be registered alongside an interrupt registration. */
			hisr_register_at(is_primary_bus ? X86_INTNO_PIC2_ATA1 /* TODO: Non-portable! */
			                                : X86_INTNO_PIC2_ATA2,
			                 (isr_function_t)AtaBus_HW_GetInterruptHandler(bus),
			                 bus);
		} EXCEPT {
			AtaBus_Destroy(bus);
			RETHROW();
		}
		*p_bus = bus; /* Inherit reference */
	}

	/* Construct and initialize a new ATA drive for this bus. */
	{
		/* Get a PIO lock on this bus. */
		AtaBus_LockPIO(bus);
		RAII_FINALLY { AtaBus_UnlockPIO(bus); };
		if (AtaBus_HW_WaitForBusy(bus) != ATA_ERROR_OK)
			return false;
		task_connect(&bus->ab_piointr);

		/* Ask for specifications about the drive we want to load (IDENTIFY) */
		TRY {
			outb(bus->ab_busio + ATA_DRIVE_SELECT,
			     0xa0 + (drive_id - ATA_DRIVE_MASTER));
			AtaBus_HW_SelectDelay_P(ports->a_ctrl);
			outb(bus->ab_busio + ATA_ADDRESS1, 0);
			outb(bus->ab_busio + ATA_ADDRESS2, 0);
			outb(bus->ab_busio + ATA_ADDRESS3, 0);
			outb(bus->ab_busio + ATA_COMMAND, ATA_COMMAND_IDENTIFY);
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
		if (!task_trywait()) {
			struct sig *signal;
			u8 status;
			status = inb(bus->ab_ctrlio);
			if (status == 0) {
				signal = task_receiveall();
				if unlikely(signal)
					goto got_identify_signal;
				/* Drive doesn't exist (graceful exit) */
				printk(FREESTR(KERN_INFO "[ata] No drive connected [status:0]\n"));
				goto reset_bus_and_fail;
			}
			if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF)) {
				task_disconnectall();
				goto reset_bus_and_fail;
			}
			if (!task_waitfor(ktime() + relktime_from_seconds(2))) {
				printk(FREESTR(KERN_ERR "[ata] Timeout while waiting for ATA_COMMAND_IDENTIFY "
				                        "[status={then:%#" PRIx8 ",now:%#" PRIx8 "}]\n"),
				       status, inb(bus->ab_ctrlio));
reset_bus_and_fail:
				AtaBus_HW_ResetBusAuto(bus);
				return false;
			}
		}
got_identify_signal:
		if (AtaBus_HW_WaitForDrq(bus) != ATA_ERROR_OK)
			goto reset_bus_and_fail;
		insw(bus->ab_busio + ATA_DATA, &specs, 256);
		outb(bus->ab_busio + ATA_FEATURES, 0); /* ??? */
	}

	/* Fix specifications to properly represent implications. */

	/* If we don't have a DMA port, it doesn't matter what the specs say! */
	if (bus->ab_dmaio == (port_t)-1)
		specs.capability &= ~HD_DRIVEID_CAPABILITY_DMA;

	/* Without 28-bit LBA, there can't be 48-bit. */
	if (!(specs.capability & HD_DRIVEID_CAPABILITY_LBA))
		specs.command_set_2 &= ~HD_DRIVEID_COMMAND_SET_2_LBA48;

	/* Even if 48-bit LBA is supported, we don't want to use it if 28 bits are enough. */
	if ((specs.capability & HD_DRIVEID_CAPABILITY_LBA) &&
	    (u64)specs.lba_capacity_2 == (u64)specs.lba_capacity &&
	    specs.lba_capacity < (u32)1 << 28)
		specs.command_set_2 &= ~HD_DRIVEID_COMMAND_SET_2_LBA48;

	/* Allocate a new drive object. */
	drive = _AtaDrive_Alloc();

	/* Figure out which set of operators to use. */
	{
		struct blkdev_ops const *ops;
		if (specs.command_set_2 & HD_DRIVEID_COMMAND_SET_2_LBA48) {
			ops                    = &AtaDrive_Lba48Ops;
			drive->ad_sector_count = specs.lba_capacity_2;
		} else if (specs.capability & HD_DRIVEID_CAPABILITY_LBA) {
			ops                    = &AtaDrive_Lba28Ops;
			drive->ad_sector_count = specs.lba_capacity;
		} else {
			ops                    = &AtaDrive_ChsOps;
			drive->ad_sector_count = (uint64_t)(uint8_t)specs.heads *
			                         (uint64_t)(uint16_t)specs.cyls *
			                         (uint64_t)(uint8_t)specs.sectors;
		}

		/* Remember non-DMA fallback operators. */
#ifdef ATADRIVE_HAVE_PIO_IOSECTORS
		drive->ad_pio_rdsectors = ops->bdo_dev.do_node.dvno_node.no_file.mo_loadblocks;
		drive->ad_pio_wrsectors = ops->bdo_dev.do_node.dvno_node.no_file.mo_saveblocks;
#endif /* ATADRIVE_HAVE_PIO_IOSECTORS */

		/* If DMA is supported, use it! */
		if (specs.capability & HD_DRIVEID_CAPABILITY_DMA)
			ops = &AtaDrive_DmaOps;
		_blkdev_init(drive, ops);
	}

	/* Initialize blkdev fields */
	drive->mf_part_amask = MAX(PAGESIZE, 1 << DEFAULT_ATA_SECTOR_SHIFT) - 1;
	drive->mf_blockshift = DEFAULT_ATA_SECTOR_SHIFT;

	/* 2-byte (1 == log2(2)) alignment is all ATA needs (I think...)
	 *
	 * As far as I can  tell, this could actually  be set to `0',  but
	 * I still set it to `1' (2-byte alignment) so that when not doing
	 * DMA transfers, we're  operating on  properly aligned  addresses
	 * during our  insw() /  outsw(), and  don't have  to worry  about
	 * some individual word needing to be written to 2 pages (iow:  we
	 * can use `insphysw()' and `outsphysw()' directly, both of  which
	 * have (and document) a 2-byte alignment requirement). */
	drive->mf_iobashift = 1;

	atomic64_init(&drive->mf_filesize, drive->ad_sector_count << AtaDrive_GetSectorShift(drive));
	drive->dv_driver = incref(&drv_self);
	drive->fn_mode   = S_IFBLK | 0644;
	LIST_ENTRY_UNBOUND_INIT(&drive->fn_allnodes);                            /* Initialized later (by `blkdev_repart_and_register()') */
	DBG_memset(&drive->fn_supent, 0xcc, sizeof(drive->fn_supent));           /* *ditto* */
	drive->fn_supent.rb_rhs = FSUPER_NODES_DELETED;                          /* *ditto* */
	DBG_memset(&drive->fn_ino, 0xcc, sizeof(drive->fn_ino));                 /* *ditto* */
	DBG_memset(&drive->dn_devno, 0xcc, sizeof(drive->dn_devno));             /* *ditto* */
	drive->dv_dirent = NULL;                                                 /* *ditto* */
	DBG_memset(&drive->dv_byname_node, 0xcc, sizeof(drive->dv_byname_node)); /* *ditto* */
	drive->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;                    /* *ditto* */

	/* Initialize stuff relating to `AtaDrive' */
	drive->ad_bus                   = (REF AtaBus *)incref(bus);
	drive->ad_drive                 = drive_id;
	drive->ad_chs_number_of_heads   = (u8)specs.heads;
	drive->ad_chs_cylinders         = (u16)specs.cyls;
	drive->ad_chs_sectors_per_track = (u8)specs.sectors;
	drive->ad_features              = ATA_DRIVE_FEATURE_F_NORMAL;
	if (specs.command_set_2 & HD_DRIVEID_COMMAND_SET_2_FLUSH)
		drive->ad_features |= ATA_DRIVE_FEATURE_F_FLUSH;
	FINALLY_DECREF_UNLIKELY(drive);

	/* Fill in ATA serial information. */
#define ata_setserial(dst, src)                                   \
	do {                                                          \
		static_assert(sizeof(dst) == sizeof(src) + sizeof(char)); \
		*(char *)mempcpy(dst, src, sizeof(src)) = '\0';           \
	}	__WHILE0
	ata_setserial(drive->bd_rootinfo.br_ata_serial_no, specs.serial_no);
	ata_setserial(drive->bd_rootinfo.br_ata_fw_rev, specs.fw_rev);
	ata_setserial(drive->bd_rootinfo.br_ata_model, specs.model);
#undef ata_setserial

	/* Assign the devno & devfs filename for the device. */
	{
		dev_t devno;
		REF struct devdirent *name;
		bool is_master = drive_id == ATA_DRIVE_MASTER;
		if (is_default_ide) {
			devno = makedev((is_primary_bus ? 3 : 22),
			                (is_master /**/ ? 0 : 64));
			name  = devdirent_newf("hd%c",
			                       (is_primary_bus ? 'a' : 'c') +
			                       (is_master /**/ ? 0 : 1));
		} else {
			devno = makedev(MKDEV_MAJOR_AUTO, 0);
			name  = devdirent_newf("hdX"
			                       "%" PRIxN(__SIZEOF_PORT_T__) "."
			                       "%" PRIxN(__SIZEOF_PORT_T__) "."
			                       "%" PRIxN(__SIZEOF_PORT_T__) "."
			                       "%c",
			                       ports->a_bus,
			                       ports->a_ctrl,
			                       ports->a_dma,
			                       is_master ? 'm' : 's');
		}
		/* Initialize device fields relating to devfs integration. */
		drive->dn_devno         = devno;
		drive->dv_dirent        = name; /* Inherit reference */
		drive->fn_ino           = devfs_devnode_makeino(S_IFBLK, devno);
		name->dd_dirent.fd_ino = drive->fn_ino;
		awref_init(&name->dd_dev, drive);
	}

	/* Register + repart the new drive. */
	blkdev_repart_and_register(drive);
	return true;
}

PRIVATE ATTR_FREETEXT ATTR_NOINLINE bool KCALL
AtaInit_TryInitializeDrive(struct ata_ports *__restrict ports,
                           /*(in|out)_opt*/ REF AtaBus **__restrict p_bus,
                           u8 drive_id, bool is_primary_bus,
                           bool is_default_ide) {
	bool result;
	TRY {
		result = AtaInit_InitializeDrive(ports, p_bus, drive_id,
		                                 is_primary_bus, is_default_ide);
	} EXCEPT {
		except_class_t cls = except_class();
		if (EXCEPTCLASS_ISRTLPRIORITY(cls))
			RETHROW();
		except_printf("Initializing ATA device");
		result = false;
	}
	return result;
}



PRIVATE ATTR_FREETEXT ATTR_NOINLINE bool KCALL
AtaInit_InitializeAta(struct ata_ports *__restrict ports,
                      bool is_primary_bus,
                      bool is_default_ide) {
	bool result;
	REF AtaBus *bus = NULL;
	RAII_FINALLY { xdecref_unlikely(bus); };
	result = AtaInit_TryInitializeDrive(ports, &bus, ATA_DRIVE_MASTER, is_primary_bus, is_default_ide);
	result |= AtaInit_TryInitializeDrive(ports, &bus, ATA_DRIVE_SLAVE, is_primary_bus, is_default_ide);
	return result;
}

PRIVATE ATTR_FREETEXT ATTR_NOINLINE bool KCALL
AtaInit_InitializeIde(struct ide_ports *__restrict self, bool is_default_ide) {
	struct ata_ports a;
	bool result;
	printk(FREESTR(KERN_INFO "[ata] Attempting to initialize IDE device {"
	                         "pbus:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                         "pctl:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                         "sbus:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                         "sctl:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                         "dma:%#" PRIxN(__SIZEOF_PORT_T__) "} "
	                         "(default_ide: %u)\n"),
	       self->i_primary_bus, self->i_primary_ctrl,
	       self->i_secondary_bus, self->i_secondary_ctrl,
	       self->i_dma_ctrl, is_default_ide ? 1 : 0);

	/* Initialize the primary ata device. */
	a.a_bus  = self->i_primary_bus;
	a.a_ctrl = self->i_primary_ctrl;
	a.a_dma  = self->i_dma_ctrl;
	result   = AtaInit_InitializeAta(&a, true, is_default_ide);

	/* Initialize the secondary ata devices. */
	a.a_bus  = self->i_secondary_bus;
	a.a_ctrl = self->i_secondary_ctrl;
	a.a_dma  = self->i_dma_ctrl;
	if (a.a_dma != (port_t)-1)
		a.a_dma += (DMA_SECONDARY_COMMAND - DMA_PRIMARY_COMMAND);
	result |= AtaInit_InitializeAta(&a, false, is_default_ide);
	return result;
}


/* @return: true:  Primary IDE device found.
 * @return: false: Secondary IDE device found, or initialization failed. */
PRIVATE ATTR_FREETEXT ATTR_NOINLINE bool KCALL
AtaInit_LoadPciIDE(struct pci_device *__restrict dev) {
	bool result = false;
	struct ide_ports i;
	if (dev->pd_regions[0].pmr_size == 0) {
		i.i_primary_bus = ATA_DEFAULT_PRIMARY_BUS;
		result          = true;
	} else {
		if (!dev->pd_regions[0].pmr_is_IO) {
			printk(FREESTR(KERN_WARNING "[ata] PCI IDE device at %" PRIp32 " uses a "
			                            "memory mapping for BAR0 (primary bus)\n"),
			       dev->pd_addr);
			return false;
		}
		i.i_primary_bus = (port_t)dev->pd_regions[0].pmr_addr;
		if (i.i_primary_bus == ATA_DEFAULT_PRIMARY_BUS)
			result = true;
	}
	if (dev->pd_regions[1].pmr_size == 0) {
		i.i_primary_ctrl = ATA_DEFAULT_PRIMARY_CTRL;
		result           = true;
	} else {
		if (!dev->pd_regions[1].pmr_is_IO) {
			printk(FREESTR(KERN_WARNING "[ata] PCI IDE device at %" PRIp32 " uses a "
			                            "memory mapping for BAR1 (primary control)\n"),
			       dev->pd_addr);
			return false;
		}
		i.i_primary_ctrl = (port_t)dev->pd_regions[1].pmr_addr;
		if (i.i_primary_ctrl == ATA_DEFAULT_PRIMARY_CTRL)
			result = true;
	}
	if (dev->pd_regions[2].pmr_size == 0) {
		i.i_secondary_bus = ATA_DEFAULT_SECONDARY_BUS;
		result            = true;
	} else {
		if (!dev->pd_regions[2].pmr_is_IO) {
			printk(FREESTR(KERN_WARNING "[ata] PCI IDE device at %" PRIp32 " uses a "
			                            "memory mapping for BAR2 (secondary bus)\n"),
			       dev->pd_addr);
			return false;
		}
		i.i_secondary_bus = (port_t)dev->pd_regions[2].pmr_addr;
		if (i.i_secondary_bus == ATA_DEFAULT_SECONDARY_BUS)
			result = true;
	}
	if (dev->pd_regions[3].pmr_size == 0) {
		i.i_secondary_ctrl = ATA_DEFAULT_SECONDARY_CTRL;
		result             = true;
	} else {
		if (!dev->pd_regions[3].pmr_is_IO) {
			printk(FREESTR(KERN_WARNING "[ata] PCI IDE device at %" PRIp32 " uses a "
			                            "memory mapping for BAR3 (secondary control)\n"),
			       dev->pd_addr);
			return false;
		}
		i.i_secondary_ctrl = (port_t)dev->pd_regions[3].pmr_addr;
		if (i.i_secondary_ctrl == ATA_DEFAULT_SECONDARY_CTRL)
			result = true;
	}
	i.i_dma_ctrl = (port_t)-1;

	/* Check if this IDE may support DMA mode. */
	if (!ide_nodma && dev->pd_regions[4].pmr_is_IO && dev->pd_regions[4].pmr_size >= 16) {
		i.i_dma_ctrl = (port_t)dev->pd_regions[4].pmr_addr;
		pci_device_cfg_writel(dev, PCI_DEV4,
		                      (pci_device_cfg_readl(dev, PCI_DEV4) & ~(PCI_CDEV4_NOIRQ)) |
		                      (PCI_CDEV4_BUSMASTER | PCI_CDEV4_ALLOW_MEMWRITE));
	}
	if (!AtaInit_InitializeIde(&i, result))
		result = false;
	return result;
}


#ifdef BUILDING_KERNEL_CORE
INTERN ATTR_FREETEXT void KCALL kernel_initialize_ide_driver(void)
#else /* BUILDING_KERNEL_CORE */
PRIVATE DRIVER_INIT ATTR_FREETEXT void KCALL AtaInit(void)
#endif /* !BUILDING_KERNEL_CORE */
{
	bool has_primary = false;
	struct pci_device *dev;
	/* Search for IDE PCI devices. */
	PCI_FOREACH_DEVICE_CLASS (dev, PCI_DEV8_CLASS_STORAGE, 1) {
		has_primary |= AtaInit_LoadPciIDE(dev);
	}
	if (!has_primary) {
		/* Check for an IDE device at the default location. */
		struct ide_ports i;
		i.i_primary_bus    = ATA_DEFAULT_PRIMARY_BUS;
		i.i_primary_ctrl   = ATA_DEFAULT_PRIMARY_CTRL;
		i.i_secondary_bus  = ATA_DEFAULT_SECONDARY_BUS;
		i.i_secondary_ctrl = ATA_DEFAULT_SECONDARY_CTRL;
		i.i_dma_ctrl       = (port_t)-1;
		AtaInit_InitializeIde(&i, true);
	}
}

DECL_END

#endif /* !GUARD_MODIDE_ATA	_C */
