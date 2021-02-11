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
#ifndef GUARD_MODIDE_DMA_C
#define GUARD_MODIDE_DMA_C 1
#define _KOS_SOURCE 1

#include "ata.h"
/**/

#include <kernel/compiler.h>

#include <hybrid/atomic.h>

#include <sys/io.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN


#if ATA_AIO_HANDLE_FWRITING == 1
#define DMA_RW_COMMAND(aio_flags)          dma_rw_command[(aio_flags)&1]
#define DMA_RW_COMMAND_EXT(aio_flags)      dma_rw_command_ext[(aio_flags)&1]
#define DMA_DMA_COMMAND(aio_flags)         dma_dma_command[(aio_flags)&1]
#define DMA_DMA_COMMAND_ENABLED(aio_flags) dma_dma_command_enabled[(aio_flags)&1]
PRIVATE u8 const dma_rw_command[2] = {
	[0]                       = ATA_COMMAND_READ_DMA,
	[ATA_AIO_HANDLE_FWRITING] = ATA_COMMAND_WRITE_DMA
};
PRIVATE u8 const dma_rw_command_ext[2] = {
	[0]                       = ATA_COMMAND_READ_DMA_EXT,
	[ATA_AIO_HANDLE_FWRITING] = ATA_COMMAND_WRITE_DMA_EXT
};
PRIVATE u8 const dma_dma_command[2] = {
	[0]                       = DMA_COMMAND_FREADMODE,
	[ATA_AIO_HANDLE_FWRITING] = 0
};
PRIVATE u8 const dma_dma_command_enabled[2] = {
	[0]                       = DMA_COMMAND_FENABLED | DMA_COMMAND_FREADMODE,
	[ATA_AIO_HANDLE_FWRITING] = DMA_COMMAND_FENABLED
};
#else /* ATA_AIO_HANDLE_FWRITING == 1 */
#define DMA_RW_COMMAND(aio_flags)        \
	((aio_flags)&ATA_AIO_HANDLE_FWRITING \
	 ? ATA_COMMAND_WRITE_DMA             \
	 : ATA_COMMAND_READ_DMA)
#define DMA_RW_COMMAND_EXT(aio_flags)    \
	((aio_flags)&ATA_AIO_HANDLE_FWRITING \
	 ? ATA_COMMAND_WRITE_DMA_EXT         \
	 : ATA_COMMAND_READ_DMA_EXT)
#define DMA_DMA_COMMAND(aio_flags)       \
	((aio_flags)&ATA_AIO_HANDLE_FWRITING \
	 ? 0                                 \
	 : DMA_COMMAND_FREADMODE)
#define DMA_DMA_COMMAND_ENABLED(aio_flags)       \
	((aio_flags)&ATA_AIO_HANDLE_FWRITING \
	 ? DMA_COMMAND_FENABLED              \
	 : DMA_COMMAND_FENABLED | DMA_COMMAND_FREADMODE)
#endif /* ATA_AIO_HANDLE_FWRITING != 1 */



/* Start a hardware-level DMA operation for the given `handle'
 * @return: true:  DMA has been initiated
 * @return: false: The handle was canceled before DMA could begin (try the next handle!) */
INTERN NOBLOCK bool
NOTHROW(FCALL AtaBus_HW_StartDma)(AtaBus *__restrict self,
                                  struct aio_handle *__restrict handle,
                                  union ata_aio_prd prd) {
	AtaAIOHandleData *data;
	data = (AtaAIOHandleData *)handle->ah_data;

	/* Copy the PRDT into the bus's buffer. */
	if (data->hd_flags & ATA_AIO_HANDLE_FONEPRD) {
		self->ab_prdt[0].p_bufaddr = prd.hd_prd0_bufaddr;
		self->ab_prdt[0].p_bufsize = data->hd_prd0_bufsize;
		self->ab_prdt[0].p_flags   = PRD_FLAST;
	} else {
		assert(data->hd_prd_count <= ATA_PRD_MAXCOUNT);
		memcpy(self->ab_prdt,
		       prd.hd_prd_vector,
		       data->hd_prd_count,
		       sizeof(AtaPRD));
		/* We've inherited the vector when we activated the AIO handle. */
		kfree(prd.hd_prd_vector);
	}

	/* Start the DMA operation. */
	return AtaBus_HW_StartDirectDma(self, handle);
}

/* Same as `AtaBus_HW_StartDma()', but assume that `self->ab_prdt' is already initialized. */
INTERN NOBLOCK bool
NOTHROW(FCALL AtaBus_HW_StartDirectDma)(AtaBus *__restrict self,
                                        struct aio_handle *__restrict handle) {
	unsigned int reset_counter = 0;
	AtaError_t error;
	AtaAIOHandleData *data;
	data = (AtaAIOHandleData *)handle->ah_data;
	assert((ATOMIC_READ(self->ab_state) & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_INDMA);
#ifndef NDEBUG
	{
		struct aio_handle *current;
		current = ATOMIC_READ(self->ab_aio_current);
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
	       (u16)ATA_ERROR_CLASS(error),
	       (u16)ATA_ERROR_SUBCLASS(error),
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

/* Cancel the currently active hardware-level DMA operation */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL AtaBus_HW_CancelDma)(AtaBus *__restrict self) {
	u8 dma_status;
	assert((ATOMIC_READ(self->ab_state) & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_INDMA);
	assert(ATOMIC_READ(self->ab_aio_current) == NULL);
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


/* Return the # of bytes that have already been transfered as part
 * of the currently in-progress AIO operation. If no AIO operation
 * is currently in progress, the return value is weakly undefined. */
INTERN NOBLOCK size_t
NOTHROW(FCALL AtaBus_HW_GetDmaProgress)(AtaBus *__restrict self) {
	/* TODO: Research if there  some way of  determining
	 *       how much of a DMA operation is already done */
	COMPILER_IMPURE();
	(void)self;
	return 0;
}


DECL_END

#endif /* !GUARD_MODIDE_DMA_C */
