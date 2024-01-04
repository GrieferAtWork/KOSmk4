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
#ifdef __INTELLISENSE__
#include "ata.c"
//#define   DEFINE_AtaDrive_RdSectorsCHS
//#define DEFINE_AtaDrive_RdSectorsLBA28
//#define DEFINE_AtaDrive_RdSectorsLBA48
#define DEFINE_AtaDrive_RdSectorsDMA
//#define   DEFINE_AtaDrive_WrSectorsCHS
//#define DEFINE_AtaDrive_WrSectorsLBA28
//#define DEFINE_AtaDrive_WrSectorsLBA48
//#define DEFINE_AtaDrive_WrSectorsDMA
#endif /* __INTELLISENSE__ */

#include <kernel/aio.h>
#include <kernel/mman/phys.h>

#if ((defined(DEFINE_AtaDrive_RdSectorsCHS) +   \
      defined(DEFINE_AtaDrive_WrSectorsCHS) +   \
      defined(DEFINE_AtaDrive_RdSectorsLBA28) + \
      defined(DEFINE_AtaDrive_WrSectorsLBA28) + \
      defined(DEFINE_AtaDrive_RdSectorsLBA48) + \
      defined(DEFINE_AtaDrive_WrSectorsLBA48) + \
      defined(DEFINE_AtaDrive_RdSectorsDMA) +   \
      defined(DEFINE_AtaDrive_WrSectorsDMA)) != 1)
#error "Must #define exactly one of these macros"
#endif /* ... */

DECL_BEGIN

#if defined(DEFINE_AtaDrive_RdSectorsCHS)
#define LOCAL_IS_RD
#define LOCAL_IS_CHS
#define LOCAL_AtaDrive_IO AtaDrive_RdSectorsCHS
#elif defined(DEFINE_AtaDrive_RdSectorsLBA28)
#define LOCAL_IS_RD
#define LOCAL_IS_LBA
#define LOCAL_IS_LBA28
#define LOCAL_AtaDrive_IO AtaDrive_RdSectorsLBA28
#elif defined(DEFINE_AtaDrive_RdSectorsLBA48)
#define LOCAL_IS_RD
#define LOCAL_IS_LBA
#define LOCAL_IS_LBA48
#define LOCAL_AtaDrive_IO AtaDrive_RdSectorsLBA48
#elif defined(DEFINE_AtaDrive_RdSectorsDMA)
#define LOCAL_IS_RD
#define LOCAL_IS_DMA
#define LOCAL_AtaDrive_IO AtaDrive_RdSectorsDMA
#elif defined(DEFINE_AtaDrive_WrSectorsCHS)
#define LOCAL_IS_WR
#define LOCAL_IS_CHS
#define LOCAL_AtaDrive_IO AtaDrive_WrSectorsCHS
#elif defined(DEFINE_AtaDrive_WrSectorsLBA28)
#define LOCAL_IS_WR
#define LOCAL_IS_LBA
#define LOCAL_IS_LBA28
#define LOCAL_AtaDrive_IO AtaDrive_WrSectorsLBA28
#elif defined(DEFINE_AtaDrive_WrSectorsLBA48)
#define LOCAL_IS_WR
#define LOCAL_IS_LBA
#define LOCAL_IS_LBA48
#define LOCAL_AtaDrive_IO AtaDrive_WrSectorsLBA48
#elif defined(DEFINE_AtaDrive_WrSectorsDMA)
#define LOCAL_IS_WR
#define LOCAL_IS_DMA
#define LOCAL_AtaDrive_IO AtaDrive_WrSectorsDMA
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

#ifdef LOCAL_IS_LBA48
#define LOCAL_MAX_SECTORS_PER_TRANSFER   0xffff
#define LOCAL_MAX_SECTORS_PER_TRANSFER_T u16
#elif defined(LOCAL_IS_LBA28)
#define LOCAL_MAX_SECTORS_PER_TRANSFER   0xff
#define LOCAL_MAX_SECTORS_PER_TRANSFER_T u8
#elif defined(LOCAL_IS_CHS)
#define LOCAL_MAX_SECTORS_PER_TRANSFER   0xff
#define LOCAL_MAX_SECTORS_PER_TRANSFER_T u8
#endif /* ... */

#ifdef LOCAL_IS_RD
#define LOCAL_CMD_RW_CHS       ATA_COMMAND_READ_SECTORS
#define LOCAL_CMD_RW_PIO       ATA_COMMAND_READ_PIO
#define LOCAL_CMD_RW_PIO_EXT   ATA_COMMAND_READ_PIO_EXT
#define LOCAL_ad_pio_IOsectors ad_pio_rdsectors
#define LOCAL_HANDLE_FLAGS     ATA_AIO_HANDLE_FNORMAL
#elif defined(LOCAL_IS_WR)
#define LOCAL_CMD_RW_CHS       ATA_COMMAND_WRITE_SECTORS
#define LOCAL_CMD_RW_PIO       ATA_COMMAND_WRITE_PIO
#define LOCAL_CMD_RW_PIO_EXT   ATA_COMMAND_WRITE_PIO_EXT
#define LOCAL_ad_pio_IOsectors ad_pio_wrsectors
#define LOCAL_HANDLE_FLAGS     ATA_AIO_HANDLE_FWRITING
#endif /* ... */



/************************************************************************/
/* Data-transfer helper functions                                       */
/************************************************************************/
#ifndef LOCAL_IS_DMA
#ifdef LOCAL_IS_RD
#define LOCAL_AtaBus_IoDataSectors AtaBus_RdDataSectors
#ifndef ATABUS_RDDATASECTORS_DEFINED
#define ATABUS_RDDATASECTORS_DEFINED
#define DEFINE_AtaBus_IoDataSectors
#endif /* !ATABUS_RDDATASECTORS_DEFINED */
#elif defined(LOCAL_IS_WR)
#define LOCAL_AtaBus_IoDataSectors AtaBus_WrDataSectors
#ifndef ATABUS_WRDATASECTORS_DEFINED
#define ATABUS_WRDATASECTORS_DEFINED
#define DEFINE_AtaBus_IoDataSectors
#endif /* !ATABUS_WRDATASECTORS_DEFINED */
#endif /* ... */

#ifdef DEFINE_AtaBus_IoDataSectors
#undef DEFINE_AtaBus_IoDataSectors
#if defined(LOCAL_IS_RD)
#define LOCAL_inoutsphysw insphysw
#elif defined(LOCAL_IS_WR)
#define LOCAL_inoutsphysw outsphysw
#endif /* ... */

LOCAL WUNUSED NONNULL((1, 2)) AtaError_t KCALL
LOCAL_AtaBus_IoDataSectors(AtaBus *__restrict bus,
                           AtaDrive *__restrict drive,
                           physaddr_t buf, u16 num_sectors) {
	(void)drive;
	TRY {
		for (;;) {
			struct sig *signal;
			u8 status; /* Set of `ATA_DCR_*' */
			AtaError_t error;
			ATA_VERBOSE("[ata] Begin waiting on data transfer to become ready\n");
			assert(num_sectors);
			signal = task_trywait();
			if (!signal) {
				ktime_t timeout;
				timeout = ktime();
				timeout += relktime_from_nanoseconds(bus->ab_timeout_dat);
				signal = task_waitfor(timeout);
				if unlikely(!signal)
					return ATA_ERROR(E_IOERROR_TIMEOUT, E_IOERROR_REASON_ATA_SECTOR_WAIT);
			}
			status = ATA_PIOINTR_ALT_DECODE(signal);
			if (status & (ATA_DCR_ERR | ATA_DCR_DF))
				return ATA_HW_GetErrorFromStatusRegister(status);
			if (num_sectors != 1) /* Re-connect for the next sector */
				task_connect(&bus->ab_piointr);
			error = AtaBus_HW_WaitForDrq(bus);
			if unlikely(error != ATA_ERROR_OK)
				return error;
			LOCAL_inoutsphysw(bus->ab_busio + ATA_DATA, buf,
			                  AtaDrive_GetSectorSize(drive) / 2);
			if (num_sectors == 1)
				break;
			buf += AtaDrive_GetSectorSize(drive);
			--num_sectors;
		}
	} EXCEPT {
		/* Must reset the bus, so-as to abort the current I/O operation. */
		task_disconnectall();
		printk(KERN_NOTICE "[ata] Reseting IDE to abort PIO-I/O operation ("
		                   "bus:%#" PRIxN(__SIZEOF_PORT_T__) ","
		                   "ctrl:%#" PRIxN(__SIZEOF_PORT_T__) ","
		                   "dma:%#" PRIxN(__SIZEOF_PORT_T__) ")\n",
		       bus->ab_busio, bus->ab_ctrlio, bus->ab_dmaio);
		AtaBus_HW_ResetBusAuto(bus);
		RETHROW();
	}
	assert(!task_wasconnected());
	return ATA_ERROR_OK;
}
#undef LOCAL_inoutsphysw
#endif /* DEFINE_AtaBus_IoDataSectors */

#endif /* !LOCAL_IS_DMA */




PRIVATE NONNULL((1, 5)) void KCALL
LOCAL_AtaDrive_IO(struct mfile *__restrict self, pos_t addr,
                  physaddr_t buf, size_t num_bytes,
                  struct aio_multihandle *__restrict aio) {
	AtaDrive *me = mfile_asata(self);
	AtaBus *bus  = me->ad_bus;
#ifdef LOCAL_IS_DMA
	uint64_t lba;
	size_t num_sectors;
	u16 part_sectors;
	AtaAIOHandleData *data;
	struct aio_handle *hand;

	(void)aio; /* Unused (without DMA, we can't do async disk transfers) */

	/* Convert absolute position/count into sector-based index/count */
	assertf((buf & 1) == 0, "Unaligned `buf = %#" PRIx64 "'", (uint64_t)buf);
	assertf((addr & AtaDrive_GetSectorMask(me)) == 0, "Unaligned `addr = %#" PRIx64 "'", (uint64_t)addr);
	assertf((num_bytes & AtaDrive_GetSectorMask(me)) == 0, "Unaligned `num_bytes = %#" PRIxSIZ "'", num_bytes);
	lba         = (uint64_t)addr >> AtaDrive_GetSectorShift(me);
	num_sectors = num_bytes >> AtaDrive_GetSectorShift(me);
	assertf(num_sectors != 0, "Specs say num_bytes != 0, and w/ alignment this means this should never happen");

	/* Assert that I/O is in-bounds */
	assertf(lba + num_sectors > lba &&
	        lba + num_sectors <= me->ad_sector_count,
	        "lba                 = %" PRIu64 "\n"
	        "num_sectors         = %" PRIuSIZ "\n"
	        "lba+num_sectors     = %" PRIu64 "\n"
	        "me->ad_sector_count = %" PRIu64 "\n",
	        lba, num_sectors, lba + num_sectors,
	        me->ad_sector_count);

#if 0
	if unlikely(!PREEMPTION_ENABLED()) {
		/* TODO: Perform I/O without use of interrupts
		 *       If  we  managed to  get this  working, that  would be  huge, because
		 *       it would mean that we could just disable preemption in single-thread
		 *       situations such as the debugger or GDBstub driver in order to access
		 *       the disk.
		 *       I know that it's possible to do this (you can poll-wait for disk access),
		 *       but it might  be complicated  to implement given  the fact  that our  ATA
		 *       driver is  designed around  the idea  of asynchronous  DMA transfer  with
		 *       interrupt-driven  PIO  as fallback  (so  we'd need  a  fall-fall-back for
		 *       poll-driven PIO access)
		 * TODO: Check to see if we can perform the PREEMPTION_ENABLED() check later,
		 *       since testing this is one of the more expensive operations since  we
		 *       can only access EFLAGS.IF by pushing it onto the stack... */
	}
#endif

#ifdef ATADRIVE_HAVE_PIO_IOSECTORS
	/* DMA can only transfer into 32-bit physical addresses. */
	if unlikely(buf + num_bytes > ((uint64_t)UINT32_MAX + 1)) {
		(*me->LOCAL_ad_pio_IOsectors)(me, addr, buf, num_bytes, aio);
		return;
	}
#endif /* ATADRIVE_HAVE_PIO_IOSECTORS */


next_chunk:
	/* Allocate an AIO handle. */
	hand = aio_multihandle_allochandle(aio);
	data = (AtaAIOHandleData *)hand->ah_data;

	/* Figure out the max # of sectors to transfer.
	 *
	 * According to the  specs, `buf' is  not allowed to  cross a 64K  boundary,
	 * meaning that `(buf & 0xffff0000) == ((buf + num_bytes - 1) & 0xffff0000)'
	 *
	 * We enforce this by only  allowing transfer sizes up  to the start of  the
	 * next 64K boundary. This check also enforces that we never try to transfer
	 * more than 64K bytes at once (which is another restriction independent  of
	 * the dont-cross-64K-boundary requirement)
	 *
	 * HINT: `maxio' is the # of bytes from `buf' until the next 64K bound. */
	{
		u32 maxio    = 0x10000 - ((u16)buf & 0xffff);
		part_sectors = (u16)(maxio >> AtaDrive_GetSectorShift(me));
		if likely(part_sectors > num_sectors)
			part_sectors = num_sectors;
	}

	/* Set DMA flags (this also selects read vs. write) */
	data->hd_flags = LOCAL_HANDLE_FLAGS;

	/* Try to switch from READY --> INDMA to immediately start a DMA I/O operation. */
	for (;;) {
		uintptr_t state, newstate;
		state = atomic_read(&bus->ab_state);
		if ((state & ATA_BUS_STATE_MASK) != ATA_BUS_STATE_READY)
			break; /* The bus isn't ready to start DMAing immediately. */

#if ATA_BUS_STATE_READY == 0
		newstate = state | ATA_BUS_STATE_INDMA;
#else /* ATA_BUS_STATE_READY == 0 */
		newstate = (state & ~ATA_BUS_STATE_MASK) | ATA_BUS_STATE_INDMA;
#endif /* ATA_BUS_STATE_READY != 0 */
		if (!atomic_cmpxch_weak(&bus->ab_state, state, newstate))
			continue;
		assert(bus->ab_aio_current == NULL);

		/* Directly fill in  the bus's PRD  buffer, rather than  creating
		 * our own buffer that would later get copied ontop of the bus's. */
		bus->ab_prdt[0].p_bufaddr = (PHYS uint32_t)buf;
		bus->ab_prdt[0].p_bufsize = part_sectors << AtaDrive_GetSectorShift(me);
		bus->ab_prdt[0].p_flags   = PRD_FLAST;

		ATA_VERBOSE("[ata] Setup initial dma\n");
		aio_handle_init(hand, &AtaDrive_DmaAioHandleType);
		data->hd_drive = (REF AtaDrive *)incref(me);
		AtaAIOHandleData_SetLbaAndSectors(data, lba, part_sectors);

		/* Indicate that AIO has already been activated. */
		data->hd_bufaddr = 0;

		/* Start  the DMA  operation, and  handle any  potential initialization failure.
		 * NOTE: Do a direct start, since we've already initialized the PRD as in-place. */
		bus->ab_aio_current = hand;
		if (!AtaBus_HW_StartDirectDma(bus, hand)) {
			assert((atomic_read(&bus->ab_state) & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_INDMA);
			AtaBus_StartNextDmaOperation(bus);
		}
		goto done_part_sectors;
	}

	/* The bus isn't in a  ready state. - Setup  `hand' as a pending  DMA
	 * operation, and schedule it for execution at a later point in time. */
	data->hd_bufaddr = (PHYS uint32_t)buf;
	data->hd_bufsize = part_sectors << AtaDrive_GetSectorShift(me);

	/* Initialize additional stuff... */
	aio_handle_init(hand, &AtaDrive_DmaAioHandleType);
	data->hd_drive = (REF AtaDrive *)incref(me);
	AtaAIOHandleData_SetLbaAndSectors(data, lba, part_sectors);

	/* Schedule the AIO handle as a pending I/O operation of the bus. */
	AtaBus_AppendDmaAioHandle(bus, hand);

	/* Check if we need more than one AIO operation. */
done_part_sectors:
	if unlikely(part_sectors < num_sectors) {
		num_sectors -= part_sectors;
		lba += part_sectors;
		buf += (size_t)part_sectors << AtaDrive_GetSectorShift(me);
		goto next_chunk;
	}
#else /* LOCAL_IS_DMA */
	unsigned int reset_counter = 0;
	AtaError_t error;
	uint64_t lba;
	size_t num_sectors;
	(void)aio; /* Unused (without DMA, we can't do async disk transfers) */

	/* Convert absolute position/count into sector-based index/count */
	assertf((buf & 1) == 0, "Unaligned `buf = %#" PRIx64 "'", (uint64_t)buf);
	assertf((addr & AtaDrive_GetSectorMask(me)) == 0, "Unaligned `addr = %#" PRIx64 "'", (uint64_t)addr);
	assertf((num_bytes & AtaDrive_GetSectorMask(me)) == 0, "Unaligned `num_bytes = %#" PRIxSIZ "'", num_bytes);
	lba         = (uint64_t)addr >> AtaDrive_GetSectorShift(me);
	num_sectors = num_bytes >> AtaDrive_GetSectorShift(me);
	assertf(num_sectors != 0, "Specs say num_bytes != 0, and w/ alignment this means this should never happen");

	/* Must operate while holding a bus-lock */
	AtaBus_LockPIO(bus);
	RAII_FINALLY {
		AtaBus_UnlockPIO(bus);
	};

again_service_io:
	for (;;) {
		LOCAL_MAX_SECTORS_PER_TRANSFER_T part_sectors;
		assert(!task_wasconnected());

		/* Figure out how many sectors to transfer. */
		part_sectors = LOCAL_MAX_SECTORS_PER_TRANSFER;
		if ((size_t)part_sectors > num_sectors)
			part_sectors = (LOCAL_MAX_SECTORS_PER_TRANSFER_T)num_sectors;

		/* Wait for BUSY to go away. */
		error = AtaBus_HW_WaitForBusy(bus);
		if unlikely(error != ATA_ERROR_OK)
			goto err_io_error;

		/* Start receiving interrupts. */
		task_connect(&bus->ab_piointr);
		TRY {
#ifdef LOCAL_IS_CHS
			/* CHS addressing */
			u32 temp;
			u8 sector, head, max_count;
			u16 cylinder;
			temp      = (u32)((u32)lba / (u8)me->ad_chs_sectors_per_track);
			sector    = (u8)(((u32)lba % (u8)me->ad_chs_sectors_per_track) + 1);
			head      = (u8)((u32)temp % (u8)me->ad_chs_number_of_heads);
			cylinder  = (u16)((u32)temp / (u8)me->ad_chs_number_of_heads);
			max_count = me->ad_chs_sectors_per_track - sector;
			if (part_sectors > max_count)
				part_sectors = (LOCAL_MAX_SECTORS_PER_TRANSFER_T)max_count;
			outb(bus->ab_busio + ATA_DRIVE_SELECT,
			     (me->ad_drive + (0xe0 - ATA_DRIVE_MASTER)) | (head & 0xf));
			AtaBus_HW_SelectDelay(bus);
			outb(bus->ab_busio + ATA_SECTOR_COUNT, part_sectors);
			outb(bus->ab_busio + ATA_ADDRESS1, (u8)sector);
			outb(bus->ab_busio + ATA_ADDRESS2, (u8)cylinder);
			outb(bus->ab_busio + ATA_ADDRESS3, (u8)(cylinder >> 8));
			outb(bus->ab_busio + ATA_COMMAND, LOCAL_CMD_RW_CHS);
#else /* LOCAL_IS_CHS */

			/* LBA28 or LBA48 */
#ifdef LOCAL_IS_LBA48
			outb(bus->ab_busio + ATA_DRIVE_SELECT, me->ad_drive);
			AtaBus_HW_SelectDelay(bus);
			outb(bus->ab_busio + ATA_SECTOR_COUNT, (u8)(part_sectors >> 8));
			outb(bus->ab_busio + ATA_ADDRESS1, (u8)(lba >> 24));
			outb(bus->ab_busio + ATA_ADDRESS2, (u8)(lba >> 32));
			outb(bus->ab_busio + ATA_ADDRESS3, (u8)(lba >> 40));
#elif defined(LOCAL_IS_LBA28)
			outb(bus->ab_busio + ATA_DRIVE_SELECT,
			     (0xe0 | (me->ad_drive - ATA_DRIVE_MASTER)) |
			     ((u8)(lba >> 24) & 0xf));
			AtaBus_HW_SelectDelay(bus);
#else /* ... */
#error "Unsupported method"
#endif /* !... */
			outb(bus->ab_busio + ATA_SECTOR_COUNT, (u8)part_sectors);
			outb(bus->ab_busio + ATA_ADDRESS1, (u8)(lba));
			outb(bus->ab_busio + ATA_ADDRESS2, (u8)(lba >> 8));
			outb(bus->ab_busio + ATA_ADDRESS3, (u8)(lba >> 16));
#ifdef LOCAL_IS_LBA48
			outb(bus->ab_busio + ATA_COMMAND, LOCAL_CMD_RW_PIO_EXT);
#elif defined(LOCAL_IS_LBA28)
			outb(bus->ab_busio + ATA_COMMAND, LOCAL_CMD_RW_PIO);
#else /* ... */
#error "Unsupported method"
#endif /* !... */
#endif /* !LOCAL_IS_CHS */
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}

		/* Transfer sectors! */
		error = LOCAL_AtaBus_IoDataSectors(bus, me, buf, part_sectors);
		assert(!task_wasconnected());
		if unlikely(error != ATA_ERROR_OK)
			goto err_io_error;

		/* Check for transfer completion, and update pointers */
		if (part_sectors >= num_sectors)
			break;
		num_sectors -= part_sectors;
		lba += part_sectors;
		buf += (size_t)part_sectors << AtaDrive_GetSectorShift(me);
	}
	return;
err_io_error:
	/* Always reset the bus (even if merely done for the next access) */
	assert(!task_wasconnected());
	printk(KERN_ERR "Reseting IDE on PIO-I/O error code "
	                "%#" PRIx16 ":%#" PRIx16 ":%#" PRIx16 " ("
	                "bus:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                "ctrl:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                "dma:%#" PRIxN(__SIZEOF_PORT_T__) ")\n",
	       (u16)ATA_EXCEPT_CLASS(error),
	       (u16)ATA_EXCEPT_SUBCLASS(error),
	       (u16)ATA_ERROR_REASON(error),
	       bus->ab_busio,
	       bus->ab_ctrlio,
	       bus->ab_dmaio);

	/* Reset the bus */
	AtaBus_HW_ResetBusAuto(bus);

	/* Check if we should try again! */
	if (reset_counter < bus->ab_pio_retry) {
		++reset_counter;
		goto again_service_io;
	}

	/* Throw an I/O error exception */
	except_thrown(EXCEPT_CODE(ATA_EXCEPT_CLASS(error), ATA_EXCEPT_SUBCLASS(error)),
	              2, E_IOERROR_SUBSYSTEM_HARDDISK, ATA_ERROR_REASON(error));
#endif /* !LOCAL_IS_DMA */
}

#undef LOCAL_AtaBus_IoDataSectors

#undef LOCAL_CMD_RW_CHS
#undef LOCAL_CMD_RW_PIO
#undef LOCAL_CMD_RW_PIO_EXT
#undef LOCAL_ad_pio_IOsectors
#undef LOCAL_HANDLE_FLAGS

#undef LOCAL_MAX_SECTORS_PER_TRANSFER
#undef LOCAL_MAX_SECTORS_PER_TRANSFER_T

#undef LOCAL_IS_RD
#undef LOCAL_IS_WR
#undef LOCAL_IS_CHS
#undef LOCAL_IS_LBA
#undef LOCAL_IS_LBA28
#undef LOCAL_IS_LBA48
#undef LOCAL_IS_DMA
#undef LOCAL_AtaDrive_IO


DECL_END

#undef DEFINE_AtaDrive_RdSectorsCHS
#undef DEFINE_AtaDrive_WrSectorsCHS
#undef DEFINE_AtaDrive_RdSectorsLBA28
#undef DEFINE_AtaDrive_WrSectorsLBA28
#undef DEFINE_AtaDrive_RdSectorsLBA48
#undef DEFINE_AtaDrive_WrSectorsLBA48
#undef DEFINE_AtaDrive_RdSectorsDMA
#undef DEFINE_AtaDrive_WrSectorsDMA
