/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODNE2K_NE2K_C
#define GUARD_MODNE2K_NE2K_C 1
#define _KOS_SOURCE 1

#include "ne2k.h"

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/isr.h>
#include <kernel/mman.h>
#include <kernel/printk.h>
#include <kernel/x86/pic.h> /* X86_INTERRUPT_PIC1_BASE (TODO: Non-portable) */
#include <sched/async.h>
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hw/bus/pci.h>
#include <hw/net/ne2k.h>
#include <kos/except/reason/io.h>
#include <linux/if_ether.h>
#include <netinet/in.h>
#include <sys/io.h>
#include <sys/mkdev.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <libpciaccess/pciaccess.h>

#if 1
#define NE2K_DEBUG(...) printk(KERN_DEBUG __VA_ARGS__)
#else
#define NE2K_DEBUG(...) (void)0
#endif

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/* Returns `true' if the first transit handle got added. */
PRIVATE NOBLOCK bool
NOTHROW(KCALL Ne2k_RestorePendingTxChain)(Ne2kDevice *__restrict self,
                                          struct aio_handle *__restrict chain) {
	struct aio_handle *old_chain;
	struct aio_handle *last_entry;
	assert(chain);
	last_entry = chain;
	while (last_entry->ah_next)
		last_entry = last_entry->ah_next;
	do {
		old_chain = atomic_read(&self->nk_tranit);
		atomic_write(&last_entry->ah_next, old_chain);
	} while (!atomic_cmpxch_weak(&self->nk_tranit, old_chain, chain));
	return old_chain == NULL;
}

/* Returns `true' if the first transit handle got added. */
PRIVATE NOBLOCK bool
NOTHROW(KCALL Ne2k_AddTransitAio)(Ne2kDevice *__restrict self,
                                  struct aio_handle *__restrict aio) {
	struct aio_handle *next;
	do {
		next = atomic_read(&self->nk_tranit);
		atomic_write(&aio->ah_next, next);
	} while (!atomic_cmpxch_weak(&self->nk_tranit, next, aio));
	return next == NULL;
}


/* Switch state to IDLE (or TX_UPLOAD/RX_DNLOAD if pending, with respect to REQUIO)
 * @return: false: The given `old_state_word' didn't match `self->nk_state.ns_word' */
PRIVATE NOBLOCK bool
NOTHROW(KCALL Ne2k_SwitchToIdleMode)(Ne2kDevice *__restrict self,
                                     uintptr_t old_state_word) {
	bool result;
	Ne2kState old_state, new_state;
	bool tx_possible;
	old_state.ns_word = old_state_word;

	/* Always switch to IDLE-mode if there are UIO requests */
	if ((old_state.ns_flags & NE2K_FLAG_REQUIO) != 0)
		goto switch_to_idle;

	/* Check if RX or TX (or both) are possible. */
	tx_possible = atomic_read(&self->nk_tranit) != NULL;

	/* Try to switch to TX-mode. */
	if (tx_possible) {
		/* Check if RX is also possible. */
		if (old_state.ns_flags & NE2K_FLAG_RXPEND) {
			/* Check what the RX/TX-latch has to say */
			if (old_state.ns_flags & NE2K_FLAG_RXLTCH)
				goto switch_to_rx; /* Do an RX operation instead. */
		}
/*switch_to_tx:*/
		new_state.ns_state = NE2K_STATE_TX_UPLOAD;
		new_state.ns_flags = old_state.ns_flags;
		if (new_state.ns_flags & NE2K_FLAG_RXPEND)
			new_state.ns_flags ^= NE2K_FLAG_RXLTCH;
		result = atomic_cmpxch(&self->nk_state.ns_word,
		                       old_state.ns_word,
		                       new_state.ns_word);
		if (result) {
			NE2K_DEBUG("[ne2k] TX possible (switch to TX_UPLOAD)\n");
			sig_broadcast(&self->nk_stpkld);
		}
		return result;
	}

	/* Try to switch to RX-mode. */
	if (old_state.ns_flags & NE2K_FLAG_RXPEND) {
switch_to_rx:
		new_state.ns_state = NE2K_STATE_RX_DNLOAD;
		new_state.ns_flags = old_state.ns_flags & ~NE2K_FLAG_RXPEND;
		if (tx_possible)
			new_state.ns_flags ^= NE2K_FLAG_RXLTCH;
		result = atomic_cmpxch(&self->nk_state.ns_word,
		                       old_state.ns_word,
		                       new_state.ns_word);
		if (result) {
			NE2K_DEBUG("[ne2k] RX possible (switch to RX_DNLOAD)\n");
			sig_broadcast(&self->nk_stpkld);
		}
		return result;
	}

switch_to_idle:
	/* Fallback: switch to the actual IDLE-mode */
	new_state.ns_state = NE2K_STATE_IDLE;
	new_state.ns_flags = old_state.ns_flags;
	result = atomic_cmpxch(&self->nk_state.ns_word,
	                       old_state.ns_word,
	                       new_state.ns_word);
	if (result) {
		NE2K_DEBUG("[ne2k] Nothing to do (switch to IDLE)\n");
		sig_broadcast(&self->nk_stidle);
	}
	return result;
}


#if 0 /* (currently) unused */
/* Try to acquire the UIO lock of `self'. */
PRIVATE bool KCALL Ne2k_TryAcquireUIO(Ne2kDevice *__restrict self) {
	Ne2kState old_state, new_state;
	do {
		old_state.ns_word = atomic_read(&self->nk_state.ns_word);
		if (old_state.ns_state != NE2K_STATE_IDLE &&
		    old_state.ns_state != NE2K_STATE_OFF)
			return false; /* Can only switch to UIO from IDLE or OFF */
		new_state.ns_state = NE2K_STATE_UIO;
		new_state.ns_flags = old_state.ns_flags;
	} while (!atomic_cmpxch_weak(&self->nk_state.ns_word,
	                             old_state.ns_word,
	                             new_state.ns_word));
	return true;
}
#endif

PRIVATE NOBLOCK void
NOTHROW(KCALL Ne2k_DecrementReqUio)(Ne2kDevice *__restrict self) {
	Ne2kState old_state, new_state;
	do {
		old_state.ns_word = atomic_read(&self->nk_state.ns_word);
		new_state.ns_word = old_state.ns_word;
		assert((new_state.ns_flags & NE2K_FLAG_REQUIO) != 0);
		new_state.ns_flags -= NE2K_FLAG_REQUIO1;
	} while (!atomic_cmpxch_weak(&self->nk_state.ns_word,
	                             old_state.ns_word,
	                             new_state.ns_word));
}

/* Acquire the UIO lock of `self'. */
PRIVATE void KCALL Ne2k_AcquireUIO(Ne2kDevice *__restrict self) {
	Ne2kState old_state, new_state;
again:
	old_state.ns_word = atomic_read(&self->nk_state.ns_word);
	if (old_state.ns_state == NE2K_STATE_IDLE ||
	    old_state.ns_state == NE2K_STATE_OFF) {
		/* Can only switch to UIO from IDLE or OFF */
		new_state.ns_state = NE2K_STATE_UIO;
		new_state.ns_flags = old_state.ns_flags;
		if unlikely(!atomic_cmpxch_weak(&self->nk_state.ns_word,
		                                old_state.ns_word,
		                                new_state.ns_word))
			goto again;
		/* Successfully acquired! */
		return;
	}
	/* Increment the `REQUIO' counter to get the NIC to switch into IDLE mode. */
	new_state.ns_word = old_state.ns_word;
	if unlikely((new_state.ns_flags & NE2K_FLAG_REQUIO) == NE2K_FLAG_REQUIO) {
		/* Cannot increment REQUIO (try to yield to get the counter to come down...) */
		task_yield();
		goto again;
	}
	new_state.ns_flags += NE2K_FLAG_REQUIO1;
	if unlikely(!atomic_cmpxch_weak(&self->nk_state.ns_word,
	                                old_state.ns_word,
	                                new_state.ns_word))
		goto again;
	TRY {
		/* Connect to the IDLE-signal. */
		task_connect(&self->nk_stidle);

		/* Check again if we can switch into UIO-mode. */
again_second_check:
		old_state.ns_word = atomic_read(&self->nk_state.ns_word);
		if unlikely(old_state.ns_state == NE2K_STATE_IDLE ||
		            old_state.ns_state == NE2K_STATE_OFF) {
			new_state.ns_state = NE2K_STATE_UIO;
			new_state.ns_flags = old_state.ns_flags;
			assert((new_state.ns_flags & NE2K_FLAG_REQUIO) != 0);
			new_state.ns_flags -= NE2K_FLAG_REQUIO1;
			if unlikely(!atomic_cmpxch_weak(&self->nk_state.ns_word,
			                                old_state.ns_word,
			                                new_state.ns_word))
				goto again_second_check;
			task_disconnectall();
			return;
		}

		/* Wait for the NIC to switch to IDLE or OFF */
		task_waitfor();

	} EXCEPT {
		Ne2k_DecrementReqUio(self);
		RETHROW();
	}
again_check_after:
	old_state.ns_word = atomic_read(&self->nk_state.ns_word);
	if likely(old_state.ns_state == NE2K_STATE_IDLE ||
	          old_state.ns_state == NE2K_STATE_OFF) {
		new_state.ns_state = NE2K_STATE_UIO;
		new_state.ns_flags = old_state.ns_flags;
		assert((new_state.ns_flags & NE2K_FLAG_REQUIO) != 0);
		new_state.ns_flags -= NE2K_FLAG_REQUIO1;
		if unlikely(!atomic_cmpxch_weak(&self->nk_state.ns_word,
		                                old_state.ns_word,
		                                new_state.ns_word))
			goto again_check_after;
		/* Got it! */
		return;
	}
	new_state.ns_word = old_state.ns_word;
	assert((new_state.ns_flags & NE2K_FLAG_REQUIO) != 0);
	new_state.ns_flags -= NE2K_FLAG_REQUIO1;
	if unlikely(!atomic_cmpxch_weak(&self->nk_state.ns_word,
	                                old_state.ns_word,
	                                new_state.ns_word))
		goto again_check_after;
	/* Start over... */
	goto again;
}


/* Release the UIO lock of `self'. */
PRIVATE NOBLOCK void
NOTHROW(KCALL Ne2k_ReleaseUIO)(Ne2kDevice *__restrict self) {
	if (self->nd_ifflags & IFF_UP) {
		Ne2kState old_state;
		do {
			old_state.ns_word = atomic_read(&self->nk_state.ns_word);
			assert(old_state.ns_state == NE2K_STATE_UIO ||
			       old_state.ns_state == NE2K_STATE_UIO_NOINT);
		} while (!Ne2k_SwitchToIdleMode(self, old_state.ns_word));
	} else {
		/* Switch to off-mode. */
#ifdef NDEBUG
		atomic_write(&self->nk_state.ns_state, NE2K_STATE_OFF);
#else /* NDEBUG */
		Ne2kState old_state, new_state;
		do {
			old_state.ns_word  = atomic_read(&self->nk_state.ns_word);
			assert(old_state.ns_state == NE2K_STATE_UIO ||
			       old_state.ns_state == NE2K_STATE_UIO_NOINT);
			new_state.ns_state = NE2K_STATE_OFF;
			new_state.ns_flags = old_state.ns_flags;
		} while (!atomic_cmpxch_weak(&self->nk_state.ns_word,
		                             old_state.ns_word,
		                             new_state.ns_word));
#endif /* !NDEBUG */
		/* Broadcast thta we've just set the device into OFF-mode */
		sig_broadcast(&self->nk_stidle);
	}
}




/* @param: tsr: Set of `ENISR_*' */
PRIVATE NOBLOCK NOPREEMPT ATTR_NOINLINE void
NOTHROW(FCALL Ne2k_HandleAioTxError)(Ne2kDevice *__restrict self,
                                     struct aio_handle *__restrict aio,
                                     u8 tsr) {
	struct exception_data old_error;
	struct exception_data *my_error;
	(void)self;
	printk(KERN_WARNING "[ne2k] Transmit error: %.2I8x\n", tsr);
	my_error = except_data();
	memcpy(&old_error, my_error, sizeof(old_error));
	bzero(my_error, sizeof(*my_error));
	my_error->e_code                       = EXCEPT_CODEOF(E_IOERROR_ERRORBIT);
	my_error->e_args.e_ioerror.i_subsystem = E_IOERROR_SUBSYSTEM_NET;
	my_error->e_args.e_ioerror.i_reason    = E_IOERROR_REASON_NE2K_TXTSR;
	my_error->e_args.e_pointers[2]         = tsr;
	/* Indicate AIO completion with error. */
	aio_handle_complete_nopr(aio, AIO_COMPLETION_FAILURE);
	memcpy(my_error, &old_error, sizeof(old_error));
}


PRIVATE NOBLOCK NOPREEMPT bool
NOTHROW(FCALL Ne2k_InterruptHandler)(void *arg) {
	Ne2kDevice *me;
	Ne2kState state;
	u8 status;
	me = (Ne2kDevice *)arg;
	state.ns_word = atomic_read(&me->nk_state.ns_word);
	if unlikely(state.ns_state == NE2K_STATE_UIO_NOINT ||
	            state.ns_state == NE2K_STATE_OFF)
		return false; /* Must be some other device... */
	/* Select page #0 */
	outb(E8390_CMD(me->nk_iobase), E8390_NODMA | E8390_START | E8390_PAGE0);
	/* Read the interrupt status register. */
	status = inb(EN0_ISR(me->nk_iobase));
	if (!(status & ENISR_ALL))
		return false; /* Not our interrupt... */
	NE2K_DEBUG("[ne2k] Interrupt: %p: %#.2I8x!\n", me, status);
	if (state.ns_state == NE2K_STATE_UIO) {
		/* Interrupt during user-IO (broadcast the result on `nk_uioint') */
handle_uio:
		outb(EN0_ISR(me->nk_iobase), status); /* Acknowledge the interrupt. */
		sig_altbroadcast(&me->nk_uioint, NE2K_UIOINT_ENCODE_ISR(status));
		return true;
	}
	if (status & (ENISR_RX | ENISR_RX_ERR)) {
		/* Disable RX interrupts. */
		outb(EN0_IMR(me->nk_iobase), ENISR_ALL & ~(ENISR_RX));
switch_state_after_rx:
		if likely(!(state.ns_flags & NE2K_FLAG_RXPEND)) {
			/* Set the RXPEND flag */
			Ne2kState new_state;
			new_state.ns_word = state.ns_word;
			new_state.ns_flags |= NE2K_FLAG_RXPEND;
			/* if the NIC  is currently in  IDLE-mode, switch to  RX_DNLOAD
			 * mode in order to have the async-worker download packet data. */
			if (state.ns_state == NE2K_STATE_IDLE)
				new_state.ns_state = NE2K_STATE_RX_DNLOAD;
			if unlikely(!atomic_cmpxch(&me->nk_state.ns_word,
			                           state.ns_word,
			                           new_state.ns_word)) {
				state.ns_word = atomic_read(&me->nk_state.ns_word);
				if unlikely(state.ns_state == NE2K_STATE_UIO_NOINT ||
				            state.ns_state == NE2K_STATE_OFF)
					return true; /* Shouldn't happen... */
				if unlikely(state.ns_state == NE2K_STATE_UIO)
					goto handle_uio;
				if unlikely(state.ns_flags & NE2K_FLAG_RXPEND)
					goto warn_rx_set;
				goto switch_state_after_rx;
			}
			/* Broadcast that a packet should now be downloaded. */
			if (new_state.ns_state == NE2K_STATE_RX_DNLOAD)
				sig_broadcast_nopr(&me->nk_stpkld);
		} else {
warn_rx_set:
			printk(KERN_WARNING "[ne2k] RX-interrupt with RXPEND already set\n");
		}
		/* Don't acknowledge the receive signal below.
		 * It will only be acknowledged once the data loader job has finished. */
		status &= ~(ENISR_RX | ENISR_RX_ERR);
	}

	if (status & (ENISR_TX | ENISR_TX_ERR)) {
		u8 transmit_status;
		struct aio_handle *aio;
		if unlikely(state.ns_state != NE2K_STATE_TX_PKSEND) {
warn_tx_bad_state:
			printk(KERN_WARNING "[ne2k] TX-interrupt when not sending a packet\n");
			goto done_tx;
		}
		/* If the send operation got canceled  at any point before now,  `nk_current'
		 * would have been set to `NULL'. By clearing it to NULL here, we essentially
		 * force `aio_cancel()' to wait until we've signaled the exit status. */
		aio = atomic_xch(&me->nk_current, NULL);
		COMPILER_READ_BARRIER();
		if likely(aio) {
			/* Signal completion or error. */
			if (status & ENISR_TX_ERR) {
				transmit_status = inb(EN0_TSR(me->nk_iobase));
			} else {
				transmit_status = ENISR_TX; /* Successful transmission. */
			}
			if (transmit_status & ENISR_TX) {
				/* Transmit was successful. */
				aio_handle_complete_nopr(aio, AIO_COMPLETION_SUCCESS);
			} else {
				/* Transmit failed. */
				Ne2k_HandleAioTxError(me, aio, transmit_status);
			}
		}

		/* Switch to IDLE mode. */
		while unlikely(!Ne2k_SwitchToIdleMode(me, state.ns_word)) {
			/* This should really only happen due to REQUIO */
			state.ns_word = atomic_read(&me->nk_state.ns_word);
			if unlikely(state.ns_state != NE2K_STATE_TX_PKSEND) {
				if unlikely(state.ns_state == NE2K_STATE_UIO_NOINT ||
				            state.ns_state == NE2K_STATE_OFF)
					return true; /* Shouldn't happen... */
				if unlikely(state.ns_state == NE2K_STATE_UIO)
					goto handle_uio; /* Shouldn't happen... */
				goto warn_tx_bad_state;
			}
		}
	}
done_tx:
	if unlikely(status & ENISR_OVER) {
		printk(KERN_ERR "[ne2k] Receiver overwrote the ring (what now?)\n");
	}
	if unlikely(status & ENISR_COUNTERS) {
		me->nd_stat.nds_rx_frame_errors += inb(EN0_COUNTER0(me->nk_iobase));
		me->nd_stat.nds_rx_crc_errors   += inb(EN0_COUNTER1(me->nk_iobase));
		me->nd_stat.nds_rx_miss_errors  += inb(EN0_COUNTER2(me->nk_iobase));
	}
	/* Acknowledge all handled signals. */
	if (status)
		outb(EN0_ISR(me->nk_iobase), status);
	return true;
}

struct ne2k_upload_printer_data {
	port_t nup_dataport; /* [const] Data output port. */
	u8     nup_half;     /* Half-word */
	bool   nup_hashalf;  /* Half-word-valid */
};

PRIVATE void KCALL
Ne2k_PrintData(struct ne2k_upload_printer_data *__restrict self,
               NCX void const *data, size_t num_bytes) {
	if unlikely(self->nup_hashalf) {
		union {
			u16 w;
			u8 b[2];
		} word;
		if unlikely(!num_bytes)
			return;
		word.b[0] = self->nup_half;
		word.b[1] = *(byte_t *)data;
		data = (byte_t *)data + 1;
		--num_bytes;
		outw(self->nup_dataport, word.w);
		self->nup_hashalf = false;
	}
	outsw(self->nup_dataport, data, num_bytes / 2);
	if unlikely(num_bytes & 1) {
		self->nup_half = ((byte_t *)data)[num_bytes - 1];
		self->nup_hashalf = true;
	}
}

PRIVATE void KCALL
Ne2k_UploadPacket(port_t dataport,
                  struct nic_packet const *__restrict self,
                  struct mman *__restrict payload_mm) {
	struct ne2k_upload_printer_data d;
	d.nup_dataport = dataport;
	d.nup_hashalf  = false;
#define PRINT_SEGMENT(p, s) Ne2k_PrintData(&d, p, s)
	{
		REF struct mman *oldmm;
		/* The payload must be printed from the perspective of `payload_mm'! */
		oldmm = task_xchmman(payload_mm);
		RAII_FINALLY { task_setmman_inherit(oldmm); };
		nic_packet_print(self, PRINT_SEGMENT);
	}
#undef PRINT_SEGMENT
	if unlikely(d.nup_hashalf) {
		union {
			u16 w;
			u8 b[2];
		} word;
		word.b[0] = d.nup_half;
		word.b[1] = 0;
		outw(dataport, word.w);
	}
}

PRIVATE void KCALL
Ne2k_WaitForRemoteDmaComplete(Ne2kDevice *__restrict self) {
	u8 status;
	status = inb(EN0_ISR(self->nk_iobase));
	if (!(status & ENISR_RDC)) {
		struct timespec timeout;
		timeout = realtime();
		timeout.add_milliseconds(400);
		while (!((status = inb(EN0_ISR(self->nk_iobase))) & ENISR_RDC)) {
			if (realtime() > timeout) {
				printk(KERN_ERR "[ne2k] Timeout waiting for remote-dma-complete on card at %#I16x\n",
				       self->nk_iobase);
				THROW(E_IOERROR_TIMEOUT,
				      E_IOERROR_SUBSYSTEM_NET,
				      E_IOERROR_REASON_NE2K_WAIT4RDMA);
			}
			task_tryyield_or_pause();
		}
	}
	/* Acknowledge remote DMA completion. */
	outb(EN0_ISR(self->nk_iobase), ENISR_RDC);
}



/************************************************************************/
/* async-worker                                                         */
/************************************************************************/
PRIVATE NONNULL((1)) unsigned int FCALL
Ne2k_HandleSendTimeout(void *__restrict arg) {
	Ne2kState state;
	Ne2kDevice *me;
	me            = (Ne2kDevice *)arg;
	state.ns_word = atomic_read(&me->nk_state.ns_word);
	/* Check if we're still waiting for a packet to be sent */
	if (state.ns_state != NE2K_STATE_TX_PKSEND)
		goto done;
	/* Check if the current send operation has really timed out.
	 * There is a chance that we got here due to a previous send
	 * operation that didn't time out, before once again finding
	 * ourselves waiting for (another) packet to be sent. */
	if (ktime() < me->nk_cursendtmo)
		goto done;
	printk(KERN_ERR "[ne2k] Watchdog send timeout (TODO)\n");
	/* TODO: Do   the  equivalent  of  aio_cancel()  for  Ne2k,
	 *       however indicate a TIMEOUT-error as the reason for
	 *       completion.
	 * NOTE: To facilitate  TX_PKSEND  timeouts,  we  need  a  new  NIC
	 *       state  `NE2K_STATE_TX_PKSEND_TIMEOUT'  that  we  can   set
	 *       here in  order to  perform  the necessary  cleanup  before
	 *       resetting the device and calling `Ne2k_SwitchToIdleMode()'
	 *       This is required  to handle the  race condition where  the
	 *       send might complete  after timing out,  in which case  the
	 *       interrupt  handler  can't  be  responsible  for  signaling
	 *       transmit completion. */
done:
	return ASYNC_RESUME;
}


PRIVATE NONNULL((1)) ktime_t FCALL
Ne2k_AsyncConnect(void *__restrict arg) {
	Ne2kDevice *me;
	me = (Ne2kDevice *)arg;
	task_connect_for_poll(&me->nk_stpkld);
	return KTIME_INFINITE;
}

/* Switch from TX_UPLOAD to TX_PKSEND */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL Ne2k_SwitchToTxPkSendMode)(Ne2kDevice *__restrict self) {
	Ne2kState old_state, new_state;
	do {
		old_state.ns_word = atomic_read(&self->nk_state.ns_word);
		assert(old_state.ns_state == NE2K_STATE_TX_UPLOAD);
		new_state.ns_state = NE2K_STATE_TX_PKSEND;
		new_state.ns_flags = old_state.ns_flags;
		{
			ktime_t send_timeout;
			send_timeout = ktime();
			send_timeout += relktime_from_seconds(2); /* TODO: Make this configurable! */
			COMPILER_WRITE_BARRIER();
			self->nk_cursendtmo = send_timeout;
			COMPILER_WRITE_BARRIER();
		}
	} while (!atomic_cmpxch_weak(&self->nk_state.ns_word,
	                             old_state.ns_word,
	                             new_state.ns_word));
}

PRIVATE NONNULL((1)) unsigned int FCALL
Ne2k_AsyncWork(void *__restrict arg) {
	Ne2kState state;
	Ne2kDevice *me;
	me = (Ne2kDevice *)arg;
again:
	state.ns_word = atomic_read(&me->nk_state.ns_word);
	if (state.ns_state == NE2K_STATE_TX_UPLOAD) {
		WEAK struct aio_handle *aio;
		Ne2kAIOHandleData *aio_data;
		REF struct nic_packet *packet;
		REF struct mman *packet_mm;
		size_t aligned_size;
		NE2K_DEBUG("[ne2k:async] Begin TX_UPLOAD\n");
		assert(PREEMPTION_ENABLED());
		/* Remove one handle  from `nk_tranit'  and make sure  that that  handle's
		 * `pd_packet'  field  is  non-NULL  (by  clearing  that  field  ourself).
		 * This has to be  done in this manner  to ensure proper interaction  with
		 * aio_cancel(),  and  also  has  to  be  done  with  preemption disabled,
		 * since  aio_cancel() will  wait for  us to  re-add just-canceled handles
		 * to the pending chain (so that it can remove them from that chain itself
		 * to  prevent  any race  conditions  related to  accessing  dead handles) */
		PREEMPTION_DISABLE();
		aio = atomic_xch(&me->nk_tranit, NULL);
		if unlikely(!aio) {
			/* No more pending packets. ->  Try to switch to  IDLE
			 * mode, but loop back to handle the case of RX_DNLOAD */
tx_switch_to_idle:
			PREEMPTION_ENABLE();
			NE2K_DEBUG("[ne2k:async] No in-transit packets (try switching to IDLE)\n");
			Ne2k_SwitchToIdleMode(me, state.ns_word);
			goto again;
		}
		/* Find the first handle with a non-NULL packet field. */
		aio_data = Ne2kAIOHandleData_Of(aio);
		assert(aio_data->pd_device == me);
		packet = atomic_xch(&aio_data->pd_packet, NULL); /* Inherit reference */
		if unlikely(!packet) {
			/* This AIO handle is currently being canceled.
			 * With that in mind, we must ensure that `aio' gets re-added to the
			 * chain of pending AIO handles, and we have to look for another AIO
			 * send operation to service. */
			WEAK struct aio_handle **pused_aio, *used_aio;
			pused_aio = &aio->ah_next;
			for (;;) {
				used_aio = *pused_aio;
				if unlikely(!used_aio) {
					/* No handles exist that aren't being canceled... */
/*tx_restore_all_and_switch_to_idle:*/
					Ne2k_RestorePendingTxChain(me, aio);
					goto tx_switch_to_idle;
				}
				packet = atomic_xch(&aio_data->pd_packet, NULL); /* Inherit reference */
				if unlikely(!packet) {
					/* Not this one, either... */
					pused_aio = &used_aio->ah_next;
					continue;
				}
				break;
			}
			/* Unlink `used_aio' */
			*pused_aio = used_aio->ah_next;
			/* Insert the AIO handle who's packet we've managed to take at the front. */
			used_aio->ah_next = aio->ah_next;
			aio->ah_next      = used_aio;
			/* Continue working with `used_aio' */
			aio = used_aio;
		}
		packet_mm = aio_data->pd_payloadmm; /* Inherit reference */
		DBG_memset(&aio_data->pd_payloadmm, 0xcc, sizeof(aio_data->pd_payloadmm));
		COMPILER_WRITE_BARRIER();
		/* This field gets cleared by aio_cancel() if the operation should get canceled
		 * at any point after */
		me->nk_current = aio;
		COMPILER_WRITE_BARRIER();

		/* Restore all other pending AIO handles. */
		if (aio->ah_next)
			Ne2k_RestorePendingTxChain(me, aio->ah_next);
		DBG_memset(&aio->ah_next, 0xcc, sizeof(aio->ah_next));

		PREEMPTION_ENABLE();

		TRY {
			/* Upload packet data */
			aligned_size = nic_packet_size(packet);
			if unlikely(aligned_size & 1)
				++aligned_size;
			if unlikely(aligned_size > (size_t)(me->nk_tx_end - me->nk_tx_start) * 256) {
				THROW(E_IOERROR_BADBOUNDS,
				      E_IOERROR_SUBSYSTEM_NET,
				      E_IOERROR_REASON_NE2K_PACKETSIZE,
				      aligned_size);
			}
			NE2K_DEBUG("[ne2k:async] Upload packet (size=%" PRIuSIZ ")\n", aligned_size);

			/* Perform a read-before-write. */
			outb(E8390_CMD(me->nk_iobase), E8390_PAGE0 | E8390_RREAD | E8390_START);
			outb(EN0_RCNTLO(me->nk_iobase), 1);
			outb(E8390_CMD(me->nk_iobase), E8390_PAGE0 | E8390_NODMA | E8390_START);
			outb(EN0_ISR(me->nk_iobase), ENISR_RDC); /* ACK remote-dma-completed for the read */
			outb(EN0_RCNTLO(me->nk_iobase), (u16)aligned_size & 0xff);
			outb(EN0_RCNTHI(me->nk_iobase), (u16)aligned_size >> 8);
			outb(EN0_RSARLO(me->nk_iobase), 0);
			outb(EN0_RSARHI(me->nk_iobase), me->nk_tx_start);
			outb(E8390_CMD(me->nk_iobase), E8390_PAGE0 | E8390_RWRITE | E8390_START);

			TRY {
				/* Copy packet data onto the NIC. */
				Ne2k_UploadPacket(NE_DATAPORT(me->nk_iobase),
				                  packet, packet_mm);

				/* Wait for the card to ACK the DMA completion. */
				Ne2k_WaitForRemoteDmaComplete(me);
			} EXCEPT {
				/* Stop the upload process (XXX: Is this how you would do that?) */
				outb(E8390_CMD(me->nk_iobase), E8390_PAGE0 | E8390_NODMA | E8390_STOP);
				RETHROW();
			}
		} EXCEPT {
			decref_likely(packet);
			decref_unlikely(packet_mm);
			/* Change NIC states to mirror what would have happened on success.
			 * Doing this simplifies  what has to  be done within  aio_cancel() */
			Ne2k_SwitchToTxPkSendMode(me);
			PREEMPTION_DISABLE();
			aio = atomic_xch(&me->nk_current, NULL);
			/* Indicate error-completion. */
			if likely(aio)
				aio_handle_complete(aio, AIO_COMPLETION_FAILURE);
			PREEMPTION_ENABLE();
			/* Switch to IDLE mode. */
			while unlikely(!Ne2k_SwitchToIdleMode(me, state.ns_word)) {
				/* This should really only happen due to REQUIO */
				state.ns_word = atomic_read(&me->nk_state.ns_word);
				assert(state.ns_state == NE2K_STATE_TX_PKSEND);
			}
			goto again;
		}
		decref_likely(packet);
		decref_unlikely(packet_mm);

		/* Check once again if the operation was canceled.
		 * This must be done in case there was a cancel during the upload
		 * process, in which case we wouldn't want to send a packet after
		 * it  has been canceled at a point  in time when that cancel was
		 * still possible. */
		if (atomic_read(&me->nk_current) == NULL) {
			while unlikely(!Ne2k_SwitchToIdleMode(me, state.ns_word)) {
				/* This should really only happen due to REQUIO */
				state.ns_word = atomic_read(&me->nk_state.ns_word);
				assert(state.ns_state == NE2K_STATE_TX_UPLOAD);
			}
			goto again;
		}

		NE2K_DEBUG("[ne2k:async] Transmit packet (size=%" PRIuSIZ ") and switch to TX_PKSEND\n", aligned_size);
		/* Set-up transmission information. */
		outb(E8390_CMD(me->nk_iobase), E8390_NODMA | E8390_START);
		outb(EN0_TPSR(me->nk_iobase), me->nk_tx_start);
		outb(EN0_TCNTLO(me->nk_iobase), (u16)aligned_size & 0xff);
		outb(EN0_TCNTHI(me->nk_iobase), (u16)aligned_size >> 8);

		/* Switch to TX_PKSEND mode */
		Ne2k_SwitchToTxPkSendMode(me);

		/* Initiate the transmission */
		outb(E8390_CMD(me->nk_iobase), E8390_TRANS | E8390_NODMA | E8390_START);
	} else if (state.ns_state == NE2K_STATE_RX_DNLOAD) {
		for (;;) {
			struct e8390_pkt_hdr hdr;
			u8 cpage, npage;
			u16 hibytes;
			struct nic_rpacket *packet;
			/* Signal start. */
			outb(E8390_CMD(me->nk_iobase), E8390_PAGE1 | E8390_NODMA | E8390_START);
			/* Stop if the current read-header is where the next package will eventually be. */
			cpage = inb(EN1_CURPAG(me->nk_iobase));
			npage = me->nk_rx_nxt;
			if (cpage == npage)
				break;

			/* Read the package header. */
			outb(E8390_CMD(me->nk_iobase), E8390_PAGE0 | E8390_NODMA | E8390_START);
			outb(EN0_RCNTLO(me->nk_iobase), sizeof(hdr) & 0xff); /* Only read the header (for now). */
			outb(EN0_RCNTHI(me->nk_iobase), (sizeof(hdr) >> 8) & 0xff);
			outb(EN0_RSARLO(me->nk_iobase), 0); /* Start reading at the page base address. */
			outb(EN0_RSARHI(me->nk_iobase), npage);
			outb(E8390_CMD(me->nk_iobase), E8390_PAGE0 | E8390_RREAD | E8390_START); /* initiate the read. */
			insw(NE_DATAPORT(me->nk_iobase), &hdr, sizeof(hdr) / 2);
			if unlikely(hdr.ph_count < sizeof(hdr) + ETH_ZLEN ||
			            hdr.ph_count > sizeof(hdr) + (ETH_FRAME_LEN + ETH_FCS_LEN)) {
				/* Header too small (shouldn't happen) */
				printk(KERN_WARNING "[ne2k] Received packet has a bad size (%" PRIu16 " bytes)\n",
				       hdr.ph_count);
				++me->nd_stat.nds_rx_length_errors;
				me->nk_rx_nxt = hdr.ph_next;
				break;
			}
			/* Allocate a buffer for the packet. */
			hdr.ph_count -= sizeof(hdr);
			packet = nic_rpacket_alloc(hdr.ph_count);
			/* Figure out how much to read from low/high memory. */
			hibytes = (me->nk_rx_end - cpage) * 256;
			if (hdr.ph_count <= hibytes) {
				u16 used_hibytes;
				/* Only need to read from high memory. */
				outb(E8390_CMD(me->nk_iobase), E8390_NODMA | E8390_START);
				used_hibytes = hdr.ph_count;
				if (used_hibytes & 1)
					++used_hibytes;
				outb(EN0_RCNTLO(me->nk_iobase), used_hibytes & 0xff);
				outb(EN0_RCNTHI(me->nk_iobase), used_hibytes >> 16);
				outb(EN0_RSARLO(me->nk_iobase), sizeof(hdr)); /* Read data after the package header. */
				outb(EN0_RSARHI(me->nk_iobase), npage);
				outb(E8390_CMD(me->nk_iobase), E8390_RREAD | E8390_START); /* Initiate the read. */
				insw(NE_DATAPORT(me->nk_iobase), packet->rp_data, hdr.ph_count / 2);
				/* Also read the last byte. */
				if (hdr.ph_count & 1) {
					union {
						u8 b[2];
						u16 w;
					} last;
					last.w = inw(NE_DATAPORT(me->nk_iobase));
					packet->rp_data[hdr.ph_count - 1] = last.b[0];
				}
			} else {
				u16 lobytes;
				u16 used_bytes;

				/* Read from high memory. */
				outb(E8390_CMD(me->nk_iobase), E8390_NODMA | E8390_START);
				used_bytes = hibytes;
				if (used_bytes & 1)
					++used_bytes;
				outb(EN0_RCNTLO(me->nk_iobase), used_bytes & 0xff);
				outb(EN0_RCNTHI(me->nk_iobase), used_bytes >> 16);
				outb(EN0_RSARLO(me->nk_iobase), sizeof(hdr)); /* Read data after the package header. */
				outb(EN0_RSARHI(me->nk_iobase), npage);
				outb(E8390_CMD(me->nk_iobase), E8390_RREAD | E8390_START); /* Initiate the read. */
				insw(NE_DATAPORT(me->nk_iobase), packet->rp_data, hibytes / 2);
				/* Also read the last byte. */
				if (hibytes & 1) {
					union {
						u8 b[2];
						u16 w;
					} last;
					last.w = inw(NE_DATAPORT(me->nk_iobase));
					packet->rp_data[hibytes - 1] = last.b[0];
				}

				/* Read from low memory. */
				lobytes = hdr.ph_count - hibytes;
				outb(E8390_CMD(me->nk_iobase), E8390_NODMA | E8390_START);
				used_bytes = lobytes;
				if (used_bytes & 1)
					++used_bytes;
				outb(EN0_RCNTLO(me->nk_iobase), used_bytes & 0xff);
				outb(EN0_RCNTHI(me->nk_iobase), used_bytes >> 16);
				outb(EN0_RSARLO(me->nk_iobase), 0); /* Read data from the start of the receive buffer. */
				outb(EN0_RSARHI(me->nk_iobase), me->nk_rx_start);
				outb(E8390_CMD(me->nk_iobase), E8390_RREAD | E8390_START); /* Initiate the read. */
				insw(NE_DATAPORT(me->nk_iobase), packet->rp_data + hibytes, lobytes / 2);
				/* Also read the last byte. */
				if (lobytes & 1) {
					union {
						u8 b[2];
						u16 w;
					} last;
					last.w = inw(NE_DATAPORT(me->nk_iobase));
					packet->rp_data[hdr.ph_count - 1] = last.b[0];
				}
			}

			/* Update the boundary pointer. */
			outb(E8390_CMD(me->nk_iobase), E8390_PAGE0 | E8390_NODMA | E8390_START);
			outb(EN0_BOUNDARY(me->nk_iobase),
			     hdr.ph_next == me->nk_rx_start ? me->nk_rx_end - 1
			                                    : hdr.ph_next - 1);
			me->nk_rx_nxt = hdr.ph_next;

			/* Route the packet. */
			nicdev_routepacket(me, packet, hdr.ph_count);
		}
		/* Clear the RX-PENDING bit. */
		atomic_and(&me->nk_state.ns_flags, ~NE2K_FLAG_RXPEND);
		COMPILER_BARRIER();
		/* Re-enable packet-receive interrupts */
		outb(E8390_CMD(me->nk_iobase), E8390_PAGE0 | E8390_NODMA | E8390_START);
		outb(EN0_ISR(me->nk_iobase), ENISR_RX | ENISR_RX_ERR);
		outb(EN0_IMR(me->nk_iobase), ENISR_ALL);
		COMPILER_BARRIER();
		/* Switch the card back into IDLE-mode. */
		while unlikely(!Ne2k_SwitchToIdleMode(me, state.ns_word)) {
			/* This should really only happen due to REQUIO */
			state.ns_word = atomic_read(&me->nk_state.ns_word);
			assert(state.ns_state == NE2K_STATE_RX_DNLOAD);
		}
		goto again;
	}
	return ASYNC_RESUME;
}

PRIVATE NONNULL((1)) bool FCALL
Ne2k_AsyncTest(void *__restrict arg) {
	Ne2kState state;
	Ne2kDevice *me;
	me            = (Ne2kDevice *)arg;
	state.ns_word = atomic_read(&me->nk_state.ns_word);
	/* The async worker responds to TX_UPLOAD and RX_DNLOAD */
	if (state.ns_state == NE2K_STATE_TX_UPLOAD ||
	    state.ns_state == NE2K_STATE_RX_DNLOAD)
		return true;
	return false;
}


PRIVATE struct async_worker_ops const Ne2k_AsyncWorkerCallbacks = {
	.awo_async   = ASYNC_WORKER_OPS_INIT_BASE,
	.awo_connect = &Ne2k_AsyncConnect,
	.awo_test    = &Ne2k_AsyncTest,
	.awo_work    = &Ne2k_AsyncWork,
	.awo_time    = &Ne2k_HandleSendTimeout,
};

PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL Ne2k_SwitchToTxUploadMode)(Ne2kDevice *__restrict self) {
	Ne2kState old_state, new_state;
	do {
		old_state.ns_word = atomic_read(&self->nk_state.ns_word);
		if (old_state.ns_state != NE2K_STATE_IDLE) {
			/* Can only switch from IDLE to TX_UPLOAD
			 * NOTE: This also covers the case of the
			 *       current state being OFF! */
			NE2K_DEBUG("[ne2k] Cannot switch to TX_UPLOAD: Not in IDLE (state=%u)\n",
			           old_state.ns_state);
			return false;
		}
		if ((old_state.ns_flags & NE2K_FLAG_REQUIO) != 0) {
			NE2K_DEBUG("[ne2k] Cannot switch to TX_UPLOAD: UIO requests exist (REQUIO=%u)\n",
			           (old_state.ns_flags & NE2K_FLAG_REQUIO) >> NE2K_FLAG_REQUIO_SHIFT);
			return false; /* Don't switch to TX_UPLOAD if there are UIO requests. */
		}
		new_state.ns_state = NE2K_STATE_TX_UPLOAD;
		new_state.ns_flags = old_state.ns_flags;
	} while (!atomic_cmpxch_weak(&self->nk_state.ns_word,
	                             old_state.ns_word,
	                             new_state.ns_word));
	NE2K_DEBUG("[ne2k] Switch to TX_UPLOAD\n");
	/* Since we were responsible for switching the NIC into TX_UPLOAD-mode,
	 * we  must also broadcast `nk_stpkld' in order to get the async-worker
	 * to service our outbound packet. */
	sig_broadcast(&self->nk_stpkld);
	return true;
}




PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL Ne2k_TxAioFini)(struct aio_handle *__restrict self) {
	Ne2kAIOHandleData *aio_data;
	aio_data = Ne2kAIOHandleData_Of(self);
	decref_unlikely(aio_data->pd_device);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL Ne2k_TxAioCancel)(struct aio_handle *__restrict self) {
	Ne2kAIOHandleData *aio_data;
	Ne2kDevice *me;
	REF struct nic_packet *packet;
	aio_data = Ne2kAIOHandleData_Of(self);
	me       = aio_data->pd_device;
	/* First step: Clear the `pd_packet' field.
	 *   - If we set to NULL by doing this:
	 *      - The AIO handle is (or was) pending in `nk_current'
	 *      - The upload process is (or was) about to be started
	 *   - If already NULL, then:
	 *      - The AIO handle had already been canceled before
	 *      - The packet is currently, or has already been uploaded */
	packet = atomic_xch(&aio_data->pd_packet, NULL);
	if (packet != NULL) {
		bool did_find;
		WEAK struct aio_handle *transit, **piter, *iter;
		decref_likely(packet);
		decref_unlikely(aio_data->pd_payloadmm);
again_poll_transit:
		/* In this case, we've  already stopped the AIO  before it could even  start.
		 * However, we must still account  for the possibility that the  async-worker
		 * may  have already removed  our AIO handle from  `nk_tranit', in which case
		 * it will put  it back as  soon as  possible. Also note  that precisely  for
		 * this case, the async-worker takes the AIO handle with preemption disabled,
		 * thus ensuring that we can't  get here from inside  of that piece of  code,
		 * meaning  that from  our perspective, we  are allowed to  poll-wait for our
		 * packet to re-appear.
		 * Also note that we must also account of new packets having appeared after
		 * the async-worker (temporarily) removed ours, so a non-NULL chain doesn't
		 * necessarily mean that our packet cannot be somewhere inside! */
		transit = atomic_xch(&me->nk_tranit, NULL);
		if unlikely(!transit) {
			/* Definite indicator that the async-worker is checking for packets! */
			task_tryyield_or_pause();
			goto again_poll_transit;
		}
		/* Check  if our packet can be found within the `transit' chain we've just stolen.
		 * If  it's not in there, then `transit' is a chain of packets that were scheduled
		 * for sending _after_ the async-worker did its atomic_xch() &of AIO handles which
		 * includes ours, such that we have to wait for it to put our handle back into the
		 * chain of those that are pending. */
		piter    = &transit;
		did_find = false;
		while ((iter = *piter) != NULL) {
			if (iter == self) {
				/* There we are! */
				did_find = true;
				/* Unlink our handle from the chain of pending ones. */
				*piter = iter->ah_next;
				break;
			}
			piter = &iter->ah_next;
		}
		/* Check for special case: Our AIO handle was the only one. */
		if (!transit) {
			assert(did_find);
			goto done_unschedule;
		}
		/* _always_ restore the (possibly updated) transit list. */
		if (Ne2k_RestorePendingTxChain(me, transit)) {
			/* Handle the case where the NIC switched to IDLE mode in the mean time. */
			Ne2k_SwitchToTxUploadMode(me);
		}
		if (did_find)
			goto done_unschedule;
		goto again_poll_transit;
	}
	/* With aio_cancel() prior to packet uploading having started  now
	 * handled, move on to handling it for the case where uploading or
	 * sending is currently in progress. */
	if (atomic_cmpxch(&me->nk_current, self, NULL)) {
		/* XXX: If the async-worker is currently in  the process of uploading packet  data
		 *      to  the NIC, then we have to get  it to stop doing so. Technically, we can
		 *      just let it do whatever in this scenario, since kernel-space packet header
		 *      memory is reference  counted, meaning that  the async-worker won't  access
		 *      arbitrary kernel-space memory.  However, it may  access user-space  memory
		 *      at  a point in time when doing so may cause a SEGFAULT (i.e. if the async-
		 *      worker is currently uploading, and we return to user-space, at which point
		 *      user-space munmap()s the  memory from which  the async-worker is  reading)
		 *      The same also applies to the case of kernel-space memory appearing  within
		 *      the payload, in which  case we may  upload arbitrary data  to the NIC,  or
		 *      SEGFAULT prior to  upload completion.  However since we  check for  cancel
		 *      once  again before  starting the  SEND-process, such  arbitrary data would
		 *      never actually leave the NIC's internal buffer...
		 * Now this may  seem like  a problem, but  it really  isn't because if  this were  to
		 * happen, then yes:  the async-worker  would experience  a SEGFAULT,  and would  stop
		 * uploading  data.  However,  the  exception  will  be  propagated,  and  immediately
		 * handled inside of `Ne2k_AsyncWork()', where it will be discarded since `nk_current'
		 * would already be NULL at that point.
		 * In other words: In the  specific case  of NIC-device-related  AIO, this  is a  problem
		 *                 that solves itself, meaning that this would _only_ be an optimization,
		 *                 rather than a bug-fix!
		 * The only kind-of questionable corner-case is VIO, where this situation could result
		 * in arbitrary  VIO memory  reads being  performed, so  I'd call  that a  maybe-look-
		 * into-fixing-this-at-some-point? */

		/* The simple case: If we've managed to clear  the current-field with our AIO  handle,
		 *                  then that means that our AIO operation is (or was) being performed
		 *                  at this (or that) very moment.
		 * By having exchanged the current-handle with our own, the completion-interrupt will
		 * not  invoke our completion function, and we also know that it hadn't invoked it at
		 * any point in the past! */
		goto done_unschedule;
	}
	/* The last possible 2 cases:
	 *   #1: Our AIO handle has already been completed, as in:
	 *       the Ne2k interrupt handler  has already invoked `ah_func'  with
	 *       either a SUCCESS or FAILURE condition. In this case, we mustn't
	 *       do anything and return.
	 *   #2: The Ne2k interrupt handler has already captured our AIO handle
	 *       via `atomic_xch(&me->nk_current, NULL)', but has yet to invoke
	 *       our AIO handle's completion function.
	 * In either case, we know:
	 *   - Our completion function has either  already been invoked, or is  going
	 *     to be invoked from a NOPREEMPT context that has already begun, meaning
	 *     that if it hasn't already  been invoked at this  point, it will be  in
	 *     such a manner that we can safely wait for this to happen.
	 *   - The AIO handle will not complete with a CANCEL status, and we aren't
	 *     even the  ones  responsible  for  setting  that  completion  status.
	 *
	 * With all  of  this  in  mind,  we don't  actually  have  to  do  anything!
	 * Once the  caller  invokes  `aio_handle_fini()', they  will  implicitly  be
	 * waiting for the AIO handle to be  completed, and us getting to this  point
	 * implicitly  means that this  wait will be  non-blocking since (like stated
	 * above), the only path where the handle hasn't already completed is the one
	 * where another CPU is completing  it _right_ _now_ with interrupts  already
	 * disabled! */

	return;
done_unschedule:
	/* Signal the cancel status if the handle wasn't completed before. */
	aio_handle_complete(self, AIO_COMPLETION_CANCEL);
}

static_assert(sizeof(Ne2kAIOHandleData) <= (AIO_HANDLE_DRIVER_POINTER_COUNT * sizeof(void *)));
PRIVATE struct aio_handle_type Ne2k_TxAioType = {
	.ht_fini   = &Ne2k_TxAioFini,
	.ht_cancel = &Ne2k_TxAioCancel,
};


PRIVATE void KCALL
Ne2k_SendPacket(struct nicdev *__restrict self,
                struct nic_packet *__restrict packet,
                /*out*/ struct aio_handle *__restrict aio) {
	Ne2kDevice *me = nicdev_asne2k(self);
	Ne2kAIOHandleData *aio_data;
	aio_data = Ne2kAIOHandleData_Of(aio);
	/* Fill in AIO data fields required for sending the packet. */
	aio_data->pd_payloadmm = incref(THIS_MMAN);
	aio_data->pd_packet    = incref(packet);
	aio_data->pd_device    = (Ne2kDevice *)incref(me);
	aio_handle_init(aio, &Ne2k_TxAioType);
	/* Register the AIO descriptor as in-transit. */
	if (Ne2k_AddTransitAio(me, aio)) {
		/* First in-transit added. (try to switch from IDLE to TX_PKSEND) */
		Ne2k_SwitchToTxUploadMode(me);
	}
}

PRIVATE uintptr_t KCALL
Ne2k_ApplyFlagsUnlocked(Ne2kDevice *__restrict self,
                        uintptr_t flags)
		THROWS(E_IOERROR) {
	u8 temp;
	unsigned int i;
	Ne2k_ResetCard(self->nk_iobase);
	self->nk_rx_nxt = self->nk_rx_start;
	if (!(flags & IFF_UP))
		return flags & ~IFF_RUNNING;

	/* Acknowledge interrupts. (From `Ne2k_ResetCard()') */
	outb(EN0_ISR(self->nk_iobase), 0xff);
	outb(E8390_CMD(self->nk_iobase), E8390_PAGE0 | E8390_STOP | E8390_NODMA);

	/* Set word-wide mode & enable loop-back. */
	outb(EN0_DCFG(self->nk_iobase), ENDCFG_FT1 | ENDCFG_LS | ENDCFG_WTS);

	/* Clear count registers. */
	outb(EN0_RCNTLO(self->nk_iobase), 0);
	outb(EN0_RCNTHI(self->nk_iobase), 0);

	/* Configure receive-mode */
	temp = 0;
	if (flags & IFF_LOOPBACK)
		temp |= ERXCR_MON;
	if (flags & IFF_PROMISC) { /* Accept all packages. */
		temp |= ERXCR_AR | ERXCR_AB | ERXCR_AM | ERXCR_PRO;
	} else {
		if (flags & IFF_ALLMULTI)
			temp |= ERXCR_AM;
		if (flags & IFF_BROADCAST)
			temp |= ERXCR_AB; /* Accept broadcast packages. */
	}
	outb(EN0_RXCR(self->nk_iobase), temp);

	/* Disable loopback for all packages. */
	outb(EN0_TXCR(self->nk_iobase), ETXCR_LOOPBACK_INTERN);

	/* Configure the card's receive buffer. */
	outb(EN0_BOUNDARY(self->nk_iobase), self->nk_rx_nxt);
	outb(EN0_STARTPG(self->nk_iobase), self->nk_rx_start);
	outb(EN0_STOPPG(self->nk_iobase), self->nk_rx_end);

	/* Acknowledge anything that may still be dangling. */
	outb(EN0_ISR(self->nk_iobase), 0xff);

	/* Enable all the interrupts that we are handling. */
	outb(EN0_IMR(self->nk_iobase), ENISR_ALL);

	/* Switch to page 1. */
	outb(E8390_CMD(self->nk_iobase), E8390_PAGE1 | E8390_STOP | E8390_NODMA);

	/* Configure the hardware address to listen for. */
	for (i = 0; i < ETH_ALEN; ++i)
		outb(EN1_PHYS_SHIFT(self->nk_iobase, i), self->nd_addr.na_hwmac[i]);
	for (i = 0; i < 8; ++i) /* XXX: Multicast? */
		outb(EN1_MULT_SHIFT(self->nk_iobase, i), 0xff);
	/* Still being in page #1, set the next-package pointer. */
	outb(EN1_CURPAG(self->nk_iobase), self->nk_rx_nxt);

	/* Finally, turn on the card. */
	outb(E8390_CMD(self->nk_iobase), E8390_PAGE0 | E8390_NODMA | E8390_START);

	/* And disable loopback, allowing for outgoing packages. */
	if (!(flags & IFF_LOOPBACK))
		outb(EN0_TXCR(self->nk_iobase), ETXCR_LOOPBACK_NORMAL);

	flags |= IFF_RUNNING;
	return flags;
}

PRIVATE bool KCALL
Ne2k_SetFlags(struct nicdev *__restrict self,
              uintptr_t old_flags, uintptr_t new_flags) {
	Ne2kDevice *me = nicdev_asne2k(self);
	assert(!(new_flags & IFF_STATUS));
	assert((old_flags & IFF_CONST) == (new_flags & IFF_CONST));
	if unlikely(atomic_read(&self->nd_ifflags) != old_flags)
		return false;
	/* Acquire the UIO lock. */
	Ne2k_AcquireUIO(me);
	if unlikely(atomic_read(&self->nd_ifflags) != old_flags) {
		Ne2k_ReleaseUIO(me);
		return false;
	}
	TRY {
		new_flags = Ne2k_ApplyFlagsUnlocked(me, new_flags);
	} EXCEPT {
		Ne2k_ReleaseUIO(me);
		RETHROW();
	}
	COMPILER_WRITE_BARRIER();
	self->nd_ifflags = new_flags;
	COMPILER_WRITE_BARRIER();
	/* XXX: Register/delete HISR  and ASYNC_WORKER  callbacks
	 *      on-the-fly based on the state of the `IFF_UP'-bit
	 *      When the NIC is turned off, then */
	Ne2k_ReleaseUIO(me);
	return true;
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL Ne2k_Destroy)(struct mfile *__restrict self) {
	Ne2kDevice *me = mfile_asne2k(self);
	hisr_unregister(&Ne2k_InterruptHandler, me);
	unregister_async_worker(&Ne2k_AsyncWorkerCallbacks, self);
	nicdev_v_destroy(me);
}

PRIVATE struct nicdev_ops const Ne2k_NICDeviceOps = {
	.nd_cdev = {{{{
		.no_file = {
			.mo_destroy = &Ne2k_Destroy,
			.mo_changed = &nicdev_v_changed,
			.mo_stream  = &nicdev_v_stream_ops,
		},
		.no_wrattr = &nicdev_v_wrattr,
	}}}},
	.nd_send     = &Ne2k_SendPacket,
	.nd_setflags = &Ne2k_SetFlags,
};



PRIVATE ATTR_FREERODATA struct {
	u8 off;
	u8 val;
} const Ne2k_StartupSequence[] = {
	{ EN0_ISR(0),    0xff }, /* Acknowledge interrupts. (From `Ne2k_ResetCard()') */
	{ E8390_CMD(0),  E8390_PAGE0 | E8390_NODMA | E8390_STOP },
	{ EN0_DCFG(0),   ENDCFG_FT1 | ENDCFG_LS | ENDCFG_WTS }, /* Set word-wide mode. */
	{ EN0_RCNTLO(0), 0 },                                   /* Clear count registers. */
	{ EN0_RCNTHI(0), 0 },                                   /* ... */
	{ EN0_IMR(0),    0 },                                   /* Mask completion irq. */
	{ EN0_ISR(0),    0xff },                                /* ... */
	{ EN0_RXCR(0),   ERXCR_MON },                           /* Enable monitoring mode (Don't receive packages for now). */
	{ EN0_TXCR(0),   ETXCR_LOOPBACK_INTERN },               /* Set loopback mode to intern (Don't send packages for now). */
	/* At this point, we'll be trying to read the first couple bytes of PROM. */
	{ EN0_RCNTLO(0), NE_PROM_SIZE & 0xff },                 /* Setup a couple of bytes for reading. */
	{ EN0_RCNTHI(0), (NE_PROM_SIZE & 0xff00) >> 8 },        /* ... */
	{ EN0_RSARLO(0), 0 },                         /* Select DMA 0x0000 for reading. */
	{ EN0_RSARHI(0), 0 },                         /* ... */
	{ E8390_CMD(0),  E8390_RREAD | E8390_START }, /* Execute a remote read. */
};


PRIVATE ATTR_FREETEXT bool KCALL
Ne2k_ProbePciDevice(struct pci_device *__restrict dev) THROWS(...) {
	port_t iobase;
	unsigned int i;
	byte_t prom[NE_PROM_SIZE];
	REF Ne2kDevice *self;
	if (dev->pd_irq < 0)
		return false;
	if (!dev->pd_regions[0].pmr_is_IO)
		return false;
	if (dev->pd_regions[0].pmr_size < 0xff)
		return false;
	iobase = (port_t)dev->pd_regions[0].pmr_addr;
	printk(FREESTR(KERN_INFO "[ne2k] Found NE2K(%p) at %#I16x (pci:%#I32x)\n"),
	       dev, iobase, dev->pd_addr);
	Ne2k_ResetCard(iobase);
	/* Execute a sequence of startup instructions. */
	for (i = 0; i < lengthof(Ne2k_StartupSequence); ++i) {
		outb(iobase +
		     Ne2k_StartupSequence[i].off,
		     Ne2k_StartupSequence[i].val);
	}

	/* Read PROM. */
	for (i = 0; i < NE_PROM_SIZE; i++)
		prom[i] = inb(NE_DATAPORT(iobase));
	outb(E8390_CMD(iobase), E8390_PAGE1 | E8390_NODMA | E8390_STOP);

	NE2K_DEBUG("[ne2k] PROM:\n%$[hex]\n", sizeof(prom), prom);

	/* Construct the device. */
	self = (REF Ne2kDevice *)kmalloc(sizeof(Ne2kDevice), GFP_CALLOC);
	_nicdev_cinit(self, &Ne2k_NICDeviceOps);
	self->fn_mode   = S_IFCHR | 0644;
	self->dv_driver = incref(&drv_self);
	TRY {
		sig_cinit(&self->nk_stidle);
		sig_cinit(&self->nk_stpkld);
		sig_cinit(&self->nk_uioint);
		self->nk_state.ns_state = NE2K_STATE_UIO_NOINT;
		self->nk_state.ns_flags = NE2K_FLAG_NORMAL;
		self->nk_pcidev = dev;
		self->nk_iobase = iobase;
		memcpy(self->nd_addr.na_hwmac, prom, ETH_ALEN);
		self->nd_ifflags   = IFF_BROADCAST | IFF_MULTICAST;
		self->nk_tx_start  = 64;
		self->nk_tx_end    = 70;
		self->nk_rx_start  = 70;
		self->nk_rx_end    = 128;

		/* set-up IRQ handling. */
		hisr_register_at(X86_INTERRUPT_PIC1_BASE + dev->pd_irq, /* TODO: Non-portable */
		                 &Ne2k_InterruptHandler, self);

		/* Reset the NIC */
		Ne2k_ResetCard(self->nk_iobase);
		self->nk_rx_nxt = self->nk_rx_start;

		/* Switch to OFF-mode. (the IF can be enabled via `Ne2k_SetFlags()') */
#ifdef NDEBUG
		atomic_write(&self->nk_state.ns_state, NE2K_STATE_OFF);
#else /* NDEBUG */
		{
			uintptr_half_t old_state;
			old_state = atomic_xch(&self->nk_state.ns_state, NE2K_STATE_OFF);
			assert(old_state == NE2K_STATE_UIO_NOINT);
		}
#endif /* !NDEBUG */

		/* Register the async-worker */
#ifdef NDEBUG
		register_async_worker(&Ne2k_AsyncWorkerCallbacks, self);
#else /* NDEBUG */
		{
			bool ok;
			ok = register_async_worker(&Ne2k_AsyncWorkerCallbacks, self);
			assert(ok);
		}
#endif /* !NDEBUG */

		/* Register device. */
		TRY {
			device_registerf(self, makedev(MKDEV_MAJOR_AUTO, 0),
			                 "ne2k.pci.%" PRIx32,
			                 dev->pd_addr);
		} EXCEPT {
			unregister_async_worker(&Ne2k_AsyncWorkerCallbacks, self);
			RETHROW();
		}
	} EXCEPT {
		decref_nokill(&drv_self);
		_nicdev_fini(self);
		kfree(self);
		RETHROW();
	}
	FINALLY_DECREF_UNLIKELY(self);


	/* XXX: Collect a list of devices, then use some kind of config
	 *      to determine which one should  be used as the  default! */
	nicdev_setdefault(self);

#if 1 /* XXX: Remove me (only here for testing) */
	{
		uintptr_t old_flags;
		do {
			old_flags = atomic_read(&self->nd_ifflags);
			if (old_flags & IFF_UP)
				break;
			/* Turn the NIC on. */
		} while (Ne2k_SetFlags(self, old_flags, old_flags | IFF_UP));
	}
#endif

	return true;
}

PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL Ne2k_InitDriver(void) {
	struct pci_device *dev;
	PCI_FOREACH_DEVICE_CLASS (dev, PCI_DEV8_CLASS_NETWORK, PCI_DEV8_CLASS_NOCLASS) {
		TRY {
			Ne2k_ProbePciDevice(dev);
		} EXCEPT {
			except_class_t cls = except_class();
			if (EXCEPTCLASS_ISRTLPRIORITY(cls))
				RETHROW();
			except_printf(FREESTR("Initializing ne2k at pci:%#I32x"),
			              dev->pd_addr);
		}
	}
}


DECL_END

#endif /* !GUARD_MODNE2K_NE2K_C */
