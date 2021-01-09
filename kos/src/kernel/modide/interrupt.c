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
#ifndef GUARD_MODIDE_INTERRUPT_C
#define GUARD_MODIDE_INTERRUPT_C 1
#define _KOS_SOURCE 1

#include "ata.h"
/**/

#include <kernel/compiler.h>

#include <kernel/isr.h>

#include <hybrid/atomic.h>

#include <inttypes.h>
#include <stddef.h>

DECL_BEGIN

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

/* Same as `AtaBus_HW_InterruptHandler()', but used if the bus supports DMA */
INTERN NOBLOCK NOPREEMPT bool
NOTHROW(FCALL AtaBus_HW_DmaInterruptHandler)(AtaBus *__restrict self) {
	u8 status, dma_status;
	dma_status = inb(self->ab_dmaio + DMA_PRIMARY_STATUS);
	if (!(dma_status & DMA_STATUS_FINTERRUPTED))
		return false; /* This bus didn't assert an interrupt */
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
	switch (ATOMIC_READ(self->ab_state) & ATA_BUS_STATE_MASK) {

	case ATA_BUS_STATE_INDMA: {
		struct aio_handle *handle;
		/* A DMA operation has been completed. */
		handle = ATOMIC_XCH(self->ab_aio_current, NULL);
		if unlikely(!handle) {
			/* This can happen if the handle is currently being canceled,
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

/* Interrupt handler for ATA BUS controllers. */
INTERN NOBLOCK NOPREEMPT bool
NOTHROW(FCALL AtaBus_HW_InterruptHandler)(AtaBus *__restrict self) {
	u8 status;
	/* BUS without DMA support */
	status = inb(self->ab_busio + ATA_STATUS);
	ATA_VERBOSE("[ata] IDE interrupt on "
	            "bus:%#" PRIxN(__SIZEOF_PORT_T__) ","
	            "ctrl:%#" PRIxN(__SIZEOF_PORT_T__) " "
	            "[bus_status=%#.2" PRIx8 "]\n",
	            self->ab_busio, self->ab_ctrlio, status);
	switch (ATOMIC_READ(self->ab_state)) {

	case ATA_BUS_STATE_INPIO:
		/* Broadcast the PIO interrupt handler. */
		sig_altbroadcast(&self->ab_piointr, ATA_PIOINTR_ALT_ENCODE(status));
		break;

	default:
		return AtaBus_HW_UnexpectedInterrupt(self);
	}
	return true;
}

DECL_END

#endif /* !GUARD_MODIDE_INTERRUPT_C */
