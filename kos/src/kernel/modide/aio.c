/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODIDE_AIO_C
#define GUARD_MODIDE_AIO_C 1
#define _KOS_SOURCE 1

#include "ata.h"
/**/

#include <kernel/compiler.h>
#include <kernel/vm.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

STATIC_ASSERT(sizeof(AtaAIOHandleData) <=
             (AIO_HANDLE_DRIVER_POINTER_COUNT * sizeof(void *)));

/* Release held DMA locks of `self' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL AtaDrive_DmaAioHandle_ReleaseDmaLocks)(struct aio_handle *__restrict self) {
	AtaAIOHandleData *data;
	assert(self->ah_type == &AtaDrive_DmaAioHandleType);
	data = (AtaAIOHandleData *)self->ah_data;
	if (data->hd_flags & ATA_AIO_HANDLE_FONEDMA) {
		vm_dmalock_release(&data->hd_dmalock);
	} else if (data->hd_dmalockvec) {
		struct vm_dmalock *iter;
		for (iter = data->hd_dmalockvec; iter->dl_part; ++iter)
			vm_dmalock_release(iter);
		kfree(data->hd_dmalockvec);
	}
#ifndef NDEBUG
	memset(&data->hd_dmalock, 0xcc, sizeof(data->hd_dmalock));
#endif /* !NDEBUG */
}

/* Complete the given, generic AIO handle with an ATA error code. */
INTERN ATTR_COLD NOBLOCK NONNULL((1)) void
NOTHROW(FCALL AioHandle_CompleteWithAtaError)(struct aio_handle *__restrict self,
                                              AtaError_t error) {
	struct exception_data old_data;
	struct exception_data *mydata = &THIS_EXCEPTION_DATA;
	memcpy(&old_data, mydata, sizeof(struct exception_data));
	memset(mydata, 0, sizeof(struct exception_data));
	mydata->e_code = ERROR_CODE(ATA_ERROR_CLASS(error), ATA_ERROR_SUBCLASS(error));
	mydata->e_args.e_ioerror.i_subsystem = E_IOERROR_SUBSYSTEM_HARDDISK;
	mydata->e_args.e_ioerror.i_reason    = ATA_ERROR_REASON(error);
	COMPILER_BARRIER();
	aio_handle_complete(self, AIO_COMPLETION_FAILURE);
	COMPILER_BARRIER();
	memcpy(mydata, &old_data, sizeof(struct exception_data));
}

/* Complete the given AIO handle with an ATA error code. */
INTERN ATTR_COLD NOBLOCK NONNULL((1)) void
NOTHROW(FCALL AtaDrive_DmaAioHandle_CompleteWithError)(struct aio_handle *__restrict self,
                                                       AtaError_t error) {
	/* Release DMA locks before calling the completion function. */
	AtaDrive_DmaAioHandle_ReleaseDmaLocks(self);

	/* Handle the error. */
	AioHandle_CompleteWithAtaError(self, error);
}

/* Complete successfully. */
INTERN NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL AtaDrive_DmaAioHandle_Complete_NoPR)(struct aio_handle *__restrict self) {
	/* Release DMA locks before calling the completion function. */
	AtaDrive_DmaAioHandle_ReleaseDmaLocks(self);
	COMPILER_BARRIER();
	aio_handle_complete_nopr(self, AIO_COMPLETION_SUCCESS);
	COMPILER_BARRIER();
}



/* Implementation of the `RESTORE_ALL()' function from <kernel/aio.h> */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) void
NOTHROW(KCALL AtaBus_RestorePendingAioHandles)(AtaBus *__restrict self,
                                               struct aio_handle *first,
                                               struct aio_handle *last) {
	struct aio_handle *next;
	do {
		next = ATOMIC_READ(self->ab_aio_pending);
		ATOMIC_WRITE(last->ah_next, next);
	} while (!ATOMIC_CMPXCH_WEAK(self->ab_aio_pending,
	                             next, first));
#if 0 /* We have no AIO-avail signal, because we don't use an async-worker! */
	if (!next)
		sig_broadcast_nopr(&self->d_aio_avail);
#endif
}

/* Select a pending AIO handle and try to start it.
 * For this purpose, the handle's `hd_prd' field is zeroed
 * out after being copied to `*prd'. This must be done in
 * order to atomically write-back the fact that the AIO
 * operation has been started, changing the behavior of
 * the AIO handle's cancel operation to account for this
 * fact.
 * When no AIO handles are available at the moment, this
 * function simply returns `NULL' */
PRIVATE NOBLOCK NOPREEMPT struct aio_handle *
NOTHROW(KCALL AtaBus_ActivateAioHandle_NoPR)(AtaBus *__restrict self,
                                             union ata_aio_prd *__restrict prd) {
	struct aio_handle *chain, **piter, *iter;
	chain = ATOMIC_XCH(self->ab_aio_pending, NULL);
	if (!chain)
		return NULL;
	/* Find an AIO handle for which we can steal the command
	 * descriptor, which we implement as the handle's PRD
	 * pointer field. */
	piter = &chain;
	for (;;) {
		AtaAIOHandleData *data;
		AtaPRD *iter_prd;
		iter = *piter;
		/* Try to activate this handle. */
		data = (AtaAIOHandleData *)iter->ah_data;
		/* Must set `ab_aio_current' _before_ we tell the handle that we've
		 * started it, since the AIO-CANCEL operation assumes that a NULL
		 * command descriptor means that `ab_aio_current == handle' indicates
		 * that the handle's operation is currently in service, with breaking
		 * that link being the first step in canceling the operation, while
		 * equality not holding true means that the operation has already
		 * completed. */
		ATOMIC_WRITE(self->ab_aio_current, iter);
		iter_prd = ATOMIC_XCH(data->hd_prd.hd_prd_vector, NULL);
		if likely(iter_prd != NULL) {
			/* Got it! */
			prd->hd_prd_vector = iter_prd;
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
	ATOMIC_WRITE(self->ab_aio_current, NULL); /* Indicate a CANCEL state. */
	return NULL;
}


/* Start the next pending DMA operation (if there is one). Otherwise,
 * switch the bus's state ATA_BUS_STATE_INDMA -> ATA_BUS_STATE_READY.
 * If there are pending WANTPIO requests, always switch to READY, and
 * signal a single waiting thread. */
INTERN NOBLOCK void
NOTHROW(FCALL AtaBus_StartNextDmaOperation)(AtaBus *__restrict self) {
	struct aio_handle *handle;
	union ata_aio_prd prd;
	uintptr_t state;
again:
	state = ATOMIC_READ(self->ab_state);
	assert((state & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_INDMA);
	/* Check if we're to switch to PIO mode. */
	if ((state & ATA_BUS_STATE_WANTPIO) != 0) {
		if (!ATOMIC_CMPXCH_WEAK(self->ab_state,
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
	if unlikely(ATOMIC_READ(self->ab_aio_pending) == NULL)
		goto no_handles;
#endif /* !__OPTIMIZE_SIZE__ */
	{
		pflag_t was;
		was    = PREEMPTION_PUSHOFF();
		handle = AtaBus_ActivateAioHandle_NoPR(self, &prd);
		PREEMPTION_POP(was);
	}
	if unlikely(!handle) {
		uintptr_t state;
#ifndef __OPTIMIZE_SIZE__
no_handles:
#endif /* !__OPTIMIZE_SIZE__ */
		/* No available handles. -> Switch to READY
		 * and check for pending AIO once again. */
#if ATA_BUS_STATE_READY == 0
		ATOMIC_AND(self->ab_state, ~ATA_BUS_STATE_MASK);
#else /* ATA_BUS_STATE_READY == 0 */
		do {
			state = ATOMIC_READ(self->ab_state);
		} while (!ATOMIC_CMPXCH_WEAK(self->ab_state, state,
		                             (state & ~ATA_BUS_STATE_MASK) |
		                             ATA_BUS_STATE_READY));
#endif /* ATA_BUS_STATE_READY != 0 */
		if (ATOMIC_READ(self->ab_aio_pending) != NULL) {
			task_tryyield_or_pause();
			if (ATOMIC_READ(self->ab_aio_pending) != NULL) {
				for (;;) {
					/* Try once again to start a DMA operation. */
					state = ATOMIC_READ(self->ab_state);
					if ((state & ATA_BUS_STATE_MASK) != ATA_BUS_STATE_READY)
						break;
					if (ATOMIC_CMPXCH_WEAK(self->ab_state, state,
					                       (state & ~ATA_BUS_STATE_MASK) |
					                       ATA_BUS_STATE_INDMA))
						goto again;
				}
			}
		}
		return;
	}
	/* Start the DMA operation on a hardware-level. */
	if (!AtaBus_HW_StartDma(self, handle, prd))
		goto again;
}


/* Same as `AtaBus_StartNextDmaOperation()', but only do so if the bus's
 * state can be switched ATA_BUS_STATE_READY -> ATA_BUS_STATE_INDMA */
PRIVATE NOBLOCK void
NOTHROW(KCALL AtaBus_TryStartNextDmaOperation)(AtaBus *__restrict self) {
	uintptr_t state;
	do {
		state = ATOMIC_READ(self->ab_state);
		if ((state & ATA_BUS_STATE_MASK) != ATA_BUS_STATE_READY)
			return; /* Bus isn't ready */
	}
#if ATA_BUS_STATE_READY == 0
	while (!ATOMIC_CMPXCH_WEAK(self->ab_state, state,
	                           state | ATA_BUS_STATE_INDMA));
#else /* ATA_BUS_STATE_READY == 0 */
	while (!ATOMIC_CMPXCH_WEAK(self->ab_state, state,
	                           (state & ~ATA_BUS_STATE_MASK) |
	                           ATA_BUS_STATE_INDMA));
#endif /* ATA_BUS_STATE_READY != 0 */
	AtaBus_StartNextDmaOperation(self);
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
					/* last element was removed. The new last element is it's predecessor,
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
	chain   = ATOMIC_XCH(self->ab_aio_pending, NULL);
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
		task_pause();
		goto again;
	}
#else /* !CONFIG_NO_SMP */
	assert(removed);
#endif /* CONFIG_NO_SMP */
}




/* Acquire/release a PIO lock for the given ata bus, allowing
 * the caller to perform bus I/O using PIO data channels. */
INTERN NONNULL((1)) void FCALL
AtaBus_LockPIO(AtaBus *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	uintptr_t state;
again:
	state = ATOMIC_READ(self->ab_state);
	/* Check if we can directly switch to PIO mode. */
	if ((state & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_READY) {
#if ATA_BUS_STATE_READY == 0
		if (ATOMIC_CMPXCH_WEAK(self->ab_state,
		                       state,
		                       state | ATA_BUS_STATE_INPIO))
			return;
#else /* ATA_BUS_STATE_READY == 0 */
		if (ATOMIC_CMPXCH_WEAK(self->ab_state,
		                       state,
		                       (state & ~ATA_BUS_STATE_MASK) |
		                       ATA_BUS_STATE_INPIO))
			return;
#endif /* ATA_BUS_STATE_READY != 0 */
	}
	/* Increment the PIO request counter. */
	if (!ATOMIC_CMPXCH_WEAK(self->ab_state,
	                        state,
	                        state + ATA_BUS_STATE_ONEPIO))
		goto again;
	/* Wait for the bus to become ready. */
	TRY {
again_waitfor:
		for (;;) {
			state = ATOMIC_READ(self->ab_state);
			if ((state & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_READY)
				break;
			task_connect(&self->ab_ready);
			state = ATOMIC_READ(self->ab_state);
			if unlikely((state & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_READY) {
				task_disconnectall();
				break;
			}
			/* Wait for PIO to become available. */
			task_waitfor();
		}
		/* Atomically switch to PIO mode, and release our PIO request ticket. */
#if ATA_BUS_STATE_READY == 0
		if (!ATOMIC_CMPXCH_WEAK(self->ab_state,
		                        state,
		                        (state - ATA_BUS_STATE_ONEPIO) |
		                        ATA_BUS_STATE_INPIO))
			goto again_waitfor;
#else /* ATA_BUS_STATE_READY == 0 */
		if (!ATOMIC_CMPXCH_WEAK(self->ab_state,
		                        state,
		                        ((state - ATA_BUS_STATE_ONEPIO) & ~ATA_BUS_STATE_MASK) |
		                        ATA_BUS_STATE_INPIO))
			goto again_waitfor;
#endif /* ATA_BUS_STATE_READY != 0 */
	} EXCEPT {
		ATOMIC_SUB(self->ab_state, ATA_BUS_STATE_ONEPIO);
		RETHROW();
	}
}

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL AtaBus_UnlockPIO)(AtaBus *__restrict self) {
	uintptr_t state;
	uintptr_t new_state;
again:
	state = ATOMIC_READ(self->ab_state);
	assert((state & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_INPIO);
	/* If there are more PIO requests, switch back to ready,
	 * rather than resuming by trying to service more DMA
	 * operations. */
	if ((state & ATA_BUS_STATE_WANTPIO) != 0) {
		if (!ATOMIC_CMPXCH_WEAK(self->ab_state,
		                        state,
		                        (state & ~ATA_BUS_STATE_MASK) |
		                        ATA_BUS_STATE_READY))
			goto again;
		/* Wake-up up to one waiting thread. */
		sig_send(&self->ab_ready);
		return;
	}
	/* Check if there are pending AIO operations that can be
	 * completed using DMA. If there are, then switch the bus
	 * into DMA-mode, and service them. */
	if (ATOMIC_READ(self->ab_aio_pending) != NULL) {
		if (!ATOMIC_CMPXCH_WEAK(self->ab_state,
		                        state,
		                        (state & ~ATA_BUS_STATE_MASK) |
		                        ATA_BUS_STATE_INDMA))
			goto again;
do_start_dma:
		AtaBus_StartNextDmaOperation(self);
		return;
	}
	/* Nothing to do. - Switch to READY and re-check for pending
	 * AIO operations that may have appeared in the mean time. */
	new_state = (state & ~ATA_BUS_STATE_MASK) | ATA_BUS_STATE_READY;
	if (!ATOMIC_CMPXCH_WEAK(self->ab_state, state, new_state))
		goto again;
	if unlikely(ATOMIC_READ(self->ab_aio_pending) != NULL) {
		/* Try to switch back to INDMA */
		if (ATOMIC_CMPXCH(self->ab_state, new_state,
		                  (state & ~ATA_BUS_STATE_MASK) |
		                  ATA_BUS_STATE_INDMA))
			goto do_start_dma;
	} else {
		/* Nothing else to do. - Broadcast to everyone that may
		 * still be listening that the bus is ready for whatever... */
		sig_broadcast(&self->ab_ready);
	}
}


/* Append the given `handle' onto the chain of pending AIO operations. */
INTERN NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL AtaBus_AppendDmaAioHandle)(AtaBus *__restrict self,
                                         struct aio_handle *__restrict handle) {
	struct aio_handle *next;
	assert(handle->ah_type == &AtaDrive_DmaAioHandleType);
	assert(self->ab_dmaio != (port_t)-1);
	do {
		next = ATOMIC_READ(self->ab_aio_pending);
		ATOMIC_WRITE(handle->ah_next, next);
	} while (!ATOMIC_CMPXCH_WEAK(self->ab_aio_pending,
	                             next, handle));
	/* If this is the first pending operation, try to initiate DMA */
	if (!next)
		AtaBus_TryStartNextDmaOperation(self);
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL AtaDrive_DmaAioHandle_Fini)(struct aio_handle *__restrict self) {
	AtaAIOHandleData *data;
	data = (AtaAIOHandleData *)self->ah_data;
	assertf(data->hd_prd.hd_prd_vector == NULL,
	        "This should have been set to NULL when "
	        "the operation was started or canceled!");
	/* NOTE: DMA locks will have already been released during completion/cancel! */
	decref_unlikely(data->hd_drive);
}

/* Cancel a DMA-AIO handle (s.a. <kernel/aio.h>:[aio_cancel(aio)]) */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL AtaDrive_DmaAioHandle_Cancel)(struct aio_handle *__restrict self) {
	AtaAIOHandleData *data;
	union ata_aio_prd prd;
	pflag_t was;
	AtaBus *bus;
	data = (AtaAIOHandleData *)self->ah_data;
	bus  = data->hd_drive->ad_bus;
	/* Try to clear the command descriptor. (for which we use the PRD buffer pointer) */
	was = PREEMPTION_PUSHOFF();
	prd.hd_prd_vector = ATOMIC_XCH(data->hd_prd.hd_prd_vector, NULL);
	if (prd.hd_prd_vector != NULL) {
		/* Cancelled before started */
		if (!(data->hd_flags & ATA_AIO_HANDLE_FONEPRD))
			kfree(prd.hd_prd_vector);
		/* Remove the entry from pending AIO. Having successfully
		 * cleared the command-pointer, we know that our AIO handle
		 * hasn't been, and no longer can be started (though it's
		 * still apart of the pending chain, from which we need to
		 * remove it now) */
		AtaBus_RemoveSpecificPendingAioHandle_NoPR(bus, self);
		goto do_cancel;
	}

	/* If the cmd-pointer was already cleared, then the AIO operation
	 * is either current in progress, or has already completed. */
	if (ATOMIC_CMPXCH(bus->ab_aio_current, self, NULL)) {

		/* Cancel the currently in-progress AIO operation on a hardware-level. */
		AtaBus_HW_CancelDma(bus);

		/* At this point, the DMA operation has been canceled, but our software bus
		 * controller is still in cancel mode (state == INDMA && current == NULL),
		 * so we have to resume execution by trying to load the next pending AIO
		 * handle, or switching to READY when no other pending handles exist.
		 *
		 * Luckily, all of this can be done for us by `AtaBus_StartNextDmaOperation()' */
		AtaBus_StartNextDmaOperation(bus);

		goto do_cancel;
	}

	/* And we're finished! */
	PREEMPTION_POP(was);
	return;
do_cancel:
	AtaDrive_DmaAioHandle_ReleaseDmaLocks(self);
	aio_handle_complete_nopr(self, AIO_COMPLETION_CANCEL);
	PREEMPTION_POP(was);
}


PRIVATE NOBLOCK NONNULL((1)) unsigned int
NOTHROW(KCALL AtaDrive_DmaAioHandle_Progress)(struct aio_handle *__restrict self,
                                              struct aio_handle_stat *__restrict stat) {
	AtaAIOHandleData *data = (AtaAIOHandleData *)self->ah_data;
	AtaBus *bus;
	assert(self->ah_type == &AtaDrive_DmaAioHandleType);
	stat->hs_total = ((size_t)data->hd_io_sectors[0] |
	                  (size_t)data->hd_io_sectors[1]) *
	                 ATA_SECTOR_SIZE(data->hd_drive);
	bus = data->hd_drive->ad_bus;
	if (ATOMIC_READ(bus->ab_aio_current) == self) {
		/* Query the hardware for how far we've already come. */
hw_progress:
		stat->hs_completed = AtaBus_HW_GetDmaProgress(bus);
		if (ATOMIC_READ(bus->ab_aio_current) == self) {
			if unlikely(stat->hs_completed > stat->hs_total)
				stat->hs_completed = stat->hs_total; /* Ensure consistency */
			return AIO_PROGRESS_STATUS_INPROGRESS;
		}
	}
	if (ATOMIC_READ(data->hd_prd.hd_prd_vector) == NULL) {
		/* Check for race condition: The hardware just started working with us. */
		if (ATOMIC_READ(bus->ab_aio_current) == self)
			goto hw_progress;
		/* We're not the current handle, but we were started at one point.
		 * This means that we've either been completed or canceled. */
		stat->hs_completed = stat->hs_total;
		return AIO_PROGRESS_STATUS_COMPLETED;
	}
	stat->hs_completed = 0;
	return AIO_PROGRESS_STATUS_PENDING;
}


/* Type used for DMA-AIO handles. */
INTERN struct aio_handle_type AtaDrive_DmaAioHandleType = {
	/* .ht_fini     = */ &AtaDrive_DmaAioHandle_Fini,
	/* .ht_cancel   = */ &AtaDrive_DmaAioHandle_Cancel,
	/* .ht_progress = */ &AtaDrive_DmaAioHandle_Progress,
};



DECL_END

#endif /* !GUARD_MODIDE_AIO_C */
