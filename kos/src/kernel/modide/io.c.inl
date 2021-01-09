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
#ifdef __INTELLISENSE__
#include "io.c"
#define DEFINE_RW_Read
//#define DEFINE_RW_Write

#define DEFINE_DATA_Virt
//#define DEFINE_DATA_Phys
//#define DEFINE_DATA_VirtVector
//#define DEFINE_DATA_PhysVector

//#define DEFINE_IOMETHOD_Dma
#define DEFINE_IOMETHOD_Chs
//#define DEFINE_IOMETHOD_Lba28
//#define DEFINE_IOMETHOD_Lba48
#endif /* __INTELLISENSE__ */

#include <kernel/iovec.h>

#include <hybrid/atomic.h>

#include <sys/io.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#ifndef PP_CAT5
#define __PP_PRIVATE_CAT5(a, b, c, d, e) a##b##c##d##e
#define PP_CAT5(a, b, c, d, e)           __PP_PRIVATE_CAT5(a, b, c, d, e)
#endif /* !PP_CAT5 */

#if (defined(DEFINE_RW_Read) + defined(DEFINE_RW_Write)) != 1
#error "Exactly 1 I/O operation must be defined"
#endif /* DEFINE_RW_... */

#if (defined(DEFINE_DATA_Virt) +   \
     defined(DEFINE_DATA_Phys) +   \
     defined(DEFINE_DATA_VirtVector) + \
     defined(DEFINE_DATA_PhysVector)) != 1
#error "Exactly 1 I/O data type must be defined"
#endif /* DEFINE_DATA_... */

#if (defined(DEFINE_IOMETHOD_Dma) +   \
     defined(DEFINE_IOMETHOD_Chs) +   \
     defined(DEFINE_IOMETHOD_Lba28) + \
     defined(DEFINE_IOMETHOD_Lba48)) != 1
#error "Exactly 1 I/O method must be defined"
#endif /* DEFINE_IOMETHOD_... */

DECL_BEGIN

#ifdef DEFINE_RW_Read
#define _ATA_RW_Name Read
#elif defined(DEFINE_RW_Write)
#define _ATA_RW_Name Write
#endif /* DEFINE_RW_... */

#ifdef DEFINE_DATA_Virt
#define _ATA_DATA_Name /* nothing */
#elif defined(DEFINE_DATA_Phys)
#define _ATA_DATA_Name Phys
#elif defined(DEFINE_DATA_VirtVector)
#define _ATA_DATA_Name Vector
#elif defined(DEFINE_DATA_PhysVector)
#define _ATA_DATA_Name VectorPhys
#endif /* DEFINE_DATA_... */

#ifdef DEFINE_IOMETHOD_Dma
#define _ATA_IOMETHOD_Name Dma
#elif defined(DEFINE_IOMETHOD_Chs)
#define _ATA_IOMETHOD_Name Chs
#elif defined(DEFINE_IOMETHOD_Lba28)
#define _ATA_IOMETHOD_Name Lba28
#elif defined(DEFINE_IOMETHOD_Lba48)
#define _ATA_IOMETHOD_Name Lba48
#endif /* DEFINE_IOMETHOD_... */

#ifdef DEFINE_DATA_Virt
#define _ATA_DATA_IS_VIRTUAL
#ifdef DEFINE_RW_Read
#define _ATA_DATA_TYPE USER CHECKED byte_t *
#elif defined(DEFINE_RW_Write)
#define _ATA_DATA_TYPE USER CHECKED byte_t const *
#endif /* DEFINE_RW_... */
#elif defined(DEFINE_DATA_Phys)
#define _ATA_DATA_IS_PHYSICAL
#define _ATA_DATA_TYPE physaddr_t
#elif defined(DEFINE_DATA_VirtVector)
#define _ATA_DATA_IS_VIRTUAL
#define _ATA_DATA_ENTRY                  struct aio_buffer_entry
#define _ATA_DATA_TYPE                   struct aio_buffer *__restrict
#define _ATA_DATA_VECTOR                 struct aio_buffer
#define _ATA_DATA_VECTOR_INIT_VIEW_AFTER aio_buffer_init_view_after
#elif defined(DEFINE_DATA_PhysVector)
#define _ATA_DATA_IS_PHYSICAL
#define _ATA_DATA_ENTRY                  struct aio_pbuffer_entry
#define _ATA_DATA_TYPE                   struct aio_pbuffer *__restrict
#define _ATA_DATA_VECTOR                 struct aio_pbuffer
#define _ATA_DATA_VECTOR_INIT_VIEW_AFTER aio_pbuffer_init_view_after
#endif /* DEFINE_DATA_... */

#ifdef DEFINE_IOMETHOD_Dma
#define _ATA_DRIVETYPE AtaDmaDrive
#else /* DEFINE_IOMETHOD_Dma */
#define _ATA_DRIVETYPE AtaDrive
#endif /* !DEFINE_IOMETHOD_Dma */

#if defined(_ATA_DATA_ENTRY) && defined(_ATA_DATA_IS_PHYSICAL)
#define _ATA_INITIALIZE_PRD_FROM_BUF(prd_buf, prd_siz, buf, num_bytes, handle) \
	AtaPRD_InitFromPhysVector(prd_buf, prd_siz, buf, num_bytes)
#elif defined(_ATA_DATA_IS_PHYSICAL)
#define _ATA_INITIALIZE_PRD_FROM_BUF(prd_buf, prd_siz, buf, num_bytes, handle) \
	AtaPRD_InitFromPhys(prd_buf, prd_siz, buf, num_bytes)
#elif defined(_ATA_DATA_ENTRY)
#ifdef DEFINE_RW_Read
#define _ATA_INITIALIZE_PRD_FROM_BUF(prd_buf, prd_siz, buf, num_bytes, handle) \
	AtaPRD_InitFromVirtVector(prd_buf, prd_siz, buf, num_bytes, handle, false)
#elif defined(DEFINE_RW_Write)
#define _ATA_INITIALIZE_PRD_FROM_BUF(prd_buf, prd_siz, buf, num_bytes, handle) \
	AtaPRD_InitFromVirtVector(prd_buf, prd_siz, buf, num_bytes, handle, true)
#endif /* ... */
#else /* ... */
#ifdef DEFINE_RW_Read
#define _ATA_INITIALIZE_PRD_FROM_BUF(prd_buf, prd_siz, buf, num_bytes, handle) \
	AtaPRD_InitFromVirt(prd_buf, prd_siz, buf, num_bytes, handle, true)
#elif defined(DEFINE_RW_Write)
#define _ATA_INITIALIZE_PRD_FROM_BUF(prd_buf, prd_siz, buf, num_bytes, handle) \
	AtaPRD_InitFromVirt(prd_buf, prd_siz, (void *)(buf), num_bytes, handle, false)
#endif /* ... */
#endif /* !... */

#ifdef DEFINE_RW_Read
#define _ATA_RW_HANDLE_FLAGS_ONEPRD ATA_AIO_HANDLE_FONEPRD
#define _ATA_RW_HANDLE_FLAGS        ATA_AIO_HANDLE_FNORMAL
#elif defined(DEFINE_RW_Write)
#define _ATA_RW_HANDLE_FLAGS_ONEPRD (ATA_AIO_HANDLE_FONEPRD | ATA_AIO_HANDLE_FWRITING)
#define _ATA_RW_HANDLE_FLAGS        (ATA_AIO_HANDLE_FNORMAL | ATA_AIO_HANDLE_FWRITING)
#endif /* ... */

#ifdef DEFINE_RW_Read
#define _ATA_LOWLEVEL_RW_CHS     ATA_COMMAND_READ_SECTORS
#define _ATA_LOWLEVEL_RW_PIO     ATA_COMMAND_READ_PIO
#define _ATA_LOWLEVEL_RW_PIO_EXT ATA_COMMAND_READ_PIO_EXT
#elif defined(DEFINE_RW_Write)
#define _ATA_LOWLEVEL_RW_CHS     ATA_COMMAND_WRITE_SECTORS
#define _ATA_LOWLEVEL_RW_PIO     ATA_COMMAND_WRITE_PIO
#define _ATA_LOWLEVEL_RW_PIO_EXT ATA_COMMAND_WRITE_PIO_EXT
#endif /* ... */

#ifdef DEFINE_IOMETHOD_Dma
/* ... */
#elif defined(DEFINE_IOMETHOD_Lba48)
#define _ATA_MAX_SECTORS_PER_TRANSFER   0xffff
#define _ATA_MAX_SECTORS_PER_TRANSFER_T u16
#elif defined(DEFINE_IOMETHOD_Lba28)
#define _ATA_MAX_SECTORS_PER_TRANSFER   0xff
#define _ATA_MAX_SECTORS_PER_TRANSFER_T u8
#elif defined(DEFINE_IOMETHOD_Chs)
#define _ATA_MAX_SECTORS_PER_TRANSFER   0xff /* ??? */
#define _ATA_MAX_SECTORS_PER_TRANSFER_T u8
#endif



/* ATA I/O functions (DMA) */
INTERN NONNULL((1, 5)) void KCALL
PP_CAT5(AtaDrive_, _ATA_IOMETHOD_Name, Drive, _ATA_RW_Name, _ATA_DATA_Name)(_ATA_DRIVETYPE *__restrict self,
                                                                            _ATA_DATA_TYPE buf,
                                                                            size_t num_sectors,
                                                                            lba_t addr,
                                                                            struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	AtaBus *bus = self->ad_bus;
#ifdef DEFINE_IOMETHOD_Dma
	AtaAIOHandleData *data = (AtaAIOHandleData *)aio->ah_data;
	size_t prd_count;
	AtaPRD prd0;
	if unlikely(num_sectors > 0xffff)
		goto service_without_dma;
#if 0
	if unlikely(!PREEMPTION_ENABLED()) {
		/* TODO: Perform I/O without use of interrupts
		 *       If we managed to get this working, that would be huge, because
		 *       it would mean that we could just disable preemption in single-thread
		 *       situations such as the debugger or GDBstub driver in order to access
		 *       the disk.
		 *       I know that it's possible to do this (you can poll-wait for disk access),
		 *       but it might be complicated to implement given the fact that our ATA
		 *       driver is designed around the idea of asynchronous DMA transfer with
		 *       interrupt-driven PIO as fallback (so we'd need a fall-fall-back for
		 *       poll-driven PIO access)
		 * TODO: Check to see if we can perform the PREEMPTION_ENABLED() check later,
		 *       since testing this is one of the more expensive operations since we
		 *       can only access EFLAGS.IF by pushing it onto the stack... */
	}
#endif
	for (;;) {
		uintptr_t state, newstate;
		/* Try to switch from READ --> INDMA to immediately start a DMA I/O operation. */
		state = ATOMIC_READ(bus->ab_state);
		if ((state & ATA_BUS_STATE_MASK) != ATA_BUS_STATE_READY)
			break; /* The bus isn't ready to start DMAing immediately. */
#if ATA_BUS_STATE_READY == 0
		newstate = state | ATA_BUS_STATE_INDMA;
#else /* ATA_BUS_STATE_READY == 0 */
		newstate = (state & ~ATA_BUS_STATE_MASK) | ATA_BUS_STATE_INDMA;
#endif /* ATA_BUS_STATE_READY != 0 */
		if (!ATOMIC_CMPXCH_WEAK(bus->ab_state,
		                        state, newstate))
			continue;
		assert(bus->ab_aio_current == NULL);

		/* NOTE: The `ATA_AIO_HANDLE_FONEPRD' flag doesn't matter in this
		 *       case, since we completely by-pass the in-handle PRD buffer,
		 *       and directly fill in the bus's PRD buffer! */
		data->hd_flags = _ATA_RW_HANDLE_FLAGS;

		/* Directly fill in the bus's PRD buffer, rather than creating
		 * our own buffer that would later get copied ontop of the bus's. */
		prd_count = _ATA_INITIALIZE_PRD_FROM_BUF(bus->ab_prdt,
		                                         ATA_PRD_MAXCOUNT,
		                                         buf,
		                                         num_sectors * ATA_SECTOR_SIZE(self),
		                                         data);

		if unlikely(!prd_count || prd_count > ATA_PRD_MAXCOUNT) {
			/* Request contains non-canonical memory. */
			AtaBus_StartNextDmaOperation(bus);
			goto service_without_dma;
		}

		ATA_VERBOSE("[ata] Setup initial dma\n");
		aio_handle_init(aio, &AtaDrive_DmaAioHandleType);
		data->hd_drive = (REF AtaDrive *)incref(self);
		AtaAIOHandleData_SetAddrAndSectors(data, addr, num_sectors);
#ifdef _ATA_DATA_IS_PHYSICAL
		data->hd_dmalockvec = NULL;
		assert(!(data->hd_flags & ATA_AIO_HANDLE_FONEDMA));
#endif /* _ATA_DATA_IS_PHYSICAL */

		/* Indicate that AIO has already been activated. */
		data->hd_prd.hd_prd_vector = NULL;

		/* Start the DMA operation, and handle any potential initialization failure.
		 * NOTE: Do a direct start, since we've already initialized the PRD as in-place. */
		bus->ab_aio_current = aio;
		if (!AtaBus_HW_StartDirectDma(bus, aio)) {
			assert((ATOMIC_READ(bus->ab_state) & ATA_BUS_STATE_MASK) == ATA_BUS_STATE_INDMA);
			AtaBus_StartNextDmaOperation(bus);
		}
		return;
	}
	/* The bus isn't in a ready state. - Setup `aio' as a pending DMA
	 * operation, and schedule it for execution at a later point in time. */
	data->hd_flags = _ATA_RW_HANDLE_FLAGS_ONEPRD;
	prd_count = _ATA_INITIALIZE_PRD_FROM_BUF(&prd0, 1, buf,
	                                         num_sectors *
	                                         ATA_SECTOR_SIZE(self),
	                                         data);
	if (prd_count == 1) {
		/* Only a single PRD is required. */
		data->hd_prd.hd_prd0_bufaddr = prd0.p_bufaddr;
		data->hd_prd0_bufsize        = prd0.p_bufsize;
		/* NOTE: The ONEPRD flag was already set by
		 * `data->hd_flags = _ATA_RW_HANDLE_FLAGS_ONEPRD' above */
	} else {
		AtaPRD *prdv;
		size_t new_prd_count;
		if unlikely(!prd_count || prd_count > ATA_PRD_MAXCOUNT)
			goto service_without_dma;
		/* Need multiple PRDs */
		prdv = (AtaPRD *)kmalloc(prd_count * sizeof(AtaPRD),
		                         GFP_LOCKED | GFP_PREFLT);
again_init_prdv:
		data->hd_flags = _ATA_RW_HANDLE_FLAGS; /* NOTE: This also clears the ONEPRD flag! */
		new_prd_count = _ATA_INITIALIZE_PRD_FROM_BUF(prdv, prd_count, buf,
		                                             num_sectors * ATA_SECTOR_SIZE(self),
		                                             data);
		if unlikely(new_prd_count != prd_count) {
			AtaPRD *new_prdv;
			if unlikely(!new_prd_count || new_prd_count > ATA_PRD_MAXCOUNT) {
				kfree(prdv);
				goto service_without_dma;
			}
			if (new_prd_count > prd_count) {
				/* Allocate more memory for additional PRDs */
				TRY {
					new_prdv = (AtaPRD *)krealloc(prdv,
					                              new_prd_count * sizeof(AtaPRD),
					                              GFP_LOCKED | GFP_PREFLT);
				} EXCEPT {
					kfree(prdv);
					RETHROW();
				}
				prdv      = new_prdv;
				prd_count = new_prd_count;
				goto again_init_prdv;
			}
			new_prdv = (AtaPRD *)krealloc_nx(prdv,
			                                 new_prd_count * sizeof(AtaPRD),
			                                 GFP_LOCKED | GFP_PREFLT);
			if likely(new_prdv)
				prdv = new_prdv;
		}
		data->hd_prd.hd_prd_vector = prdv; /* Inherit */
		data->hd_prd_count         = new_prd_count;
	}
	/* Initialize additional stuff... */
	aio_handle_init(aio, &AtaDrive_DmaAioHandleType);
	data->hd_drive = (REF AtaDrive *)incref(self);
	AtaAIOHandleData_SetAddrAndSectors(data, addr, num_sectors);
#ifdef _ATA_DATA_IS_PHYSICAL
	data->hd_dmalockvec = NULL;
	assert(!(data->hd_flags & ATA_AIO_HANDLE_FONEDMA));
#endif /* _ATA_DATA_IS_PHYSICAL */
	/* Schedule the AIO handle as a pending I/O operation of the bus. */
	AtaBus_AppendDmaAioHandle(bus, aio);
	return;
service_without_dma:
	/* Perform a non-canonical I/O operation. */
#if defined(DEFINE_RW_Read) && defined(DEFINE_DATA_Virt)
	(*self->add_nc_read)(self, buf, num_sectors, addr, aio);
#elif defined(DEFINE_RW_Read) && defined(DEFINE_DATA_Phys)
	(*self->add_nc_read_phys)(self, buf, num_sectors, addr, aio);
#elif defined(DEFINE_RW_Read) && defined(DEFINE_DATA_VirtVector)
	(*self->add_nc_readv)(self, buf, num_sectors, addr, aio);
#elif defined(DEFINE_RW_Read) && defined(DEFINE_DATA_PhysVector)
	(*self->add_nc_readv_phys)(self, buf, num_sectors, addr, aio);
#elif defined(DEFINE_RW_Write) && defined(DEFINE_DATA_Virt)
	(*self->add_nc_write)(self, buf, num_sectors, addr, aio);
#elif defined(DEFINE_RW_Write) && defined(DEFINE_DATA_Phys)
	(*self->add_nc_write_phys)(self, buf, num_sectors, addr, aio);
#elif defined(DEFINE_RW_Write) && defined(DEFINE_DATA_VirtVector)
	(*self->add_nc_writev)(self, buf, num_sectors, addr, aio);
#elif defined(DEFINE_RW_Write) && defined(DEFINE_DATA_PhysVector)
	(*self->add_nc_writev_phys)(self, buf, num_sectors, addr, aio);
#else
#error "Unsupported configuration"
#endif
#else /* DEFINE_IOMETHOD_Dma */
#ifdef _ATA_DATA_ENTRY
	_ATA_DATA_VECTOR view, view2;
#endif /* _ATA_DATA_ENTRY */
	unsigned int reset_counter = 0;
	AtaError_t error;
	AtaBus_LockPIO(bus);
again_service_io:
	TRY {
		for (;;) {
			_ATA_MAX_SECTORS_PER_TRANSFER_T part_sectors;
			assert(!task_wasconnected());
			part_sectors = _ATA_MAX_SECTORS_PER_TRANSFER;
			if ((size_t)part_sectors > num_sectors)
				part_sectors = (_ATA_MAX_SECTORS_PER_TRANSFER_T)num_sectors;
			error = AtaBus_HW_WaitForBusy(bus);
			if unlikely(error != ATA_ERROR_OK)
				goto err_io_error;
			task_connect(&bus->ab_piointr);
			TRY {
#ifdef DEFINE_IOMETHOD_Chs
				/* CHS addressing */
				u32 temp;
				u8 sector, head, max_count;
				u16 cylinder;
				temp      = (u32)((u32)addr / (u8)self->ad_chs_sectors_per_track);
				sector    = (u8)(((u32)addr % (u8)self->ad_chs_sectors_per_track) + 1);
				head      = (u8)((u32)temp % (u8)self->ad_chs_number_of_heads);
				cylinder  = (u16)((u32)temp / (u8)self->ad_chs_number_of_heads);
				max_count = self->ad_chs_sectors_per_track - sector;
				if (part_sectors > max_count)
					part_sectors = (_ATA_MAX_SECTORS_PER_TRANSFER_T)max_count;
				outb(bus->ab_busio + ATA_DRIVE_SELECT,
				     (self->ad_drive + (0xe0 - ATA_DRIVE_MASTER)) | (head & 0xf));
				AtaBus_HW_SelectDelay(bus);
				outb(bus->ab_busio + ATA_SECTOR_COUNT, part_sectors);
				outb(bus->ab_busio + ATA_ADDRESS1, (u8)sector);
				outb(bus->ab_busio + ATA_ADDRESS2, (u8)cylinder);
				outb(bus->ab_busio + ATA_ADDRESS3, (u8)(cylinder >> 8));
				outb(bus->ab_busio + ATA_COMMAND, _ATA_LOWLEVEL_RW_CHS);
#else /* DEFINE_IOMETHOD_Chs */
				/* LBA28 or LBA48 */
#ifdef DEFINE_IOMETHOD_Lba48
				outb(bus->ab_busio + ATA_DRIVE_SELECT, self->ad_drive);
				AtaBus_HW_SelectDelay(bus);
				outb(bus->ab_busio + ATA_SECTOR_COUNT, (u8)(part_sectors >> 8));
				outb(bus->ab_busio + ATA_ADDRESS1, (u8)(addr >> 24));
				outb(bus->ab_busio + ATA_ADDRESS2, (u8)(addr >> 32));
				outb(bus->ab_busio + ATA_ADDRESS3, (u8)(addr >> 40));
#elif defined(DEFINE_IOMETHOD_Lba28)
				outb(bus->ab_busio + ATA_DRIVE_SELECT,
				     (0xe0 | (self->ad_drive - ATA_DRIVE_MASTER)) |
				     ((u8)(addr >> 24) & 0xf));
				AtaBus_HW_SelectDelay(bus);
#else /* ... */
#error "Unsupported method"
#endif /* !... */
				outb(bus->ab_busio + ATA_SECTOR_COUNT, (u8)part_sectors);
				outb(bus->ab_busio + ATA_ADDRESS1, (u8)(addr));
				outb(bus->ab_busio + ATA_ADDRESS2, (u8)(addr >> 8));
				outb(bus->ab_busio + ATA_ADDRESS3, (u8)(addr >> 16));
#ifdef DEFINE_IOMETHOD_Lba48
				outb(bus->ab_busio + ATA_COMMAND, _ATA_LOWLEVEL_RW_PIO_EXT);
#elif defined(DEFINE_IOMETHOD_Lba28)
				outb(bus->ab_busio + ATA_COMMAND, _ATA_LOWLEVEL_RW_PIO);
#else /* ... */
#error "Unsupported method"
#endif /* !... */
#endif /* !DEFINE_IOMETHOD_Chs */
			} EXCEPT {
				task_disconnectall();
				RETHROW();
			}

			/* Transfer sectors! */
			error = PP_CAT4(AtaBus_, _ATA_RW_Name, DataSectors, _ATA_DATA_Name)(bus, self, buf,
			                                                                    part_sectors);
			assert(!task_wasconnected());
			if unlikely(error != ATA_ERROR_OK)
				goto err_io_error;

			/* Check for transfer completion, and update pointers */
			if (part_sectors >= num_sectors)
				break;
			num_sectors -= part_sectors;
			addr += (lba_t)part_sectors;
#ifdef _ATA_DATA_ENTRY
			if (buf == &view) {
				_ATA_DATA_VECTOR_INIT_VIEW_AFTER(&view2, &view,
				                                 (size_t)part_sectors *
				                                 ATA_SECTOR_SIZE(self));
				buf = &view2;
			} else {
				_ATA_DATA_VECTOR_INIT_VIEW_AFTER(&view, buf,
				                                 (size_t)part_sectors *
				                                 ATA_SECTOR_SIZE(self));
				buf = &view;
			}
#else /* _ATA_DATA_ENTRY */
			buf += (size_t)part_sectors * ATA_SECTOR_SIZE(self);
#endif /* !_ATA_DATA_ENTRY */
		}
	} EXCEPT {
		AtaBus_UnlockPIO(bus);
		RETHROW();
	}
	AtaBus_UnlockPIO(bus);
	/* Indicate AIO completion to the caller. */
	aio_handle_init(aio, &aio_noop_type);
	aio_handle_complete(aio, AIO_COMPLETION_SUCCESS);
	return;
err_io_error:
	/* Always reset the bus (even if merely done for the next access) */
	assert(!task_wasconnected());
	printk(KERN_ERR "Reseting IDE on PIO-I/O error code "
	                "%#" PRIx16 ":%#" PRIx16 ":%#" PRIx16 " ("
	                "bus:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                "ctrl:%#" PRIxN(__SIZEOF_PORT_T__) ","
	                "dma:%#" PRIxN(__SIZEOF_PORT_T__) ")\n",
	       (u16)ATA_ERROR_CLASS(error),
	       (u16)ATA_ERROR_SUBCLASS(error),
	       (u16)ATA_ERROR_REASON(error),
	       bus->ab_busio,
	       bus->ab_ctrlio,
	       bus->ab_dmaio);
	/* Reset the bus */
	AtaBus_HW_ResetBusAuto(bus);
	if (reset_counter < bus->ab_pio_retry) {
		/* Try again! */
		++reset_counter;
		goto again_service_io;
	}

	/* Release the PIO-lock. */
	AtaBus_UnlockPIO(bus);

	/* Initialize the AIO handle using the generic, no-op type. */
	aio_handle_init(aio, &aio_noop_type);

	/* Handle the ATA error via AIO */
	AioHandle_CompleteWithAtaError(aio, error);
#endif /* !DEFINE_IOMETHOD_Dma */
}

#undef _ATA_LOWLEVEL_RW_CHS
#undef _ATA_LOWLEVEL_RW_PIO
#undef _ATA_LOWLEVEL_RW_PIO_EXT
#undef _ATA_INITIALIZE_PRD_FROM_BUF
#undef _ATA_DRIVETYPE
#undef _ATA_RW_Name
#undef _ATA_DATA_Name
#undef _ATA_IOMETHOD_Name
#undef _ATA_DATA_ENTRY
#undef _ATA_DATA_TYPE
#undef _ATA_DATA_VECTOR
#undef _ATA_DATA_VECTOR_INIT_VIEW_AFTER
#undef _ATA_DATA_IS_VIRTUAL
#undef _ATA_DATA_IS_PHYSICAL
#undef _ATA_RW_HANDLE_FLAGS_ONEPRD
#undef _ATA_RW_HANDLE_FLAGS
#undef _ATA_MAX_SECTORS_PER_TRANSFER_T
#undef _ATA_MAX_SECTORS_PER_TRANSFER

DECL_END

#undef DEFINE_RW_Read
#undef DEFINE_RW_Write

#undef DEFINE_DATA_Virt
#undef DEFINE_DATA_Phys
#undef DEFINE_DATA_VirtVector
#undef DEFINE_DATA_PhysVector

#undef DEFINE_IOMETHOD_Dma
#undef DEFINE_IOMETHOD_Chs
#undef DEFINE_IOMETHOD_Lba28
#undef DEFINE_IOMETHOD_Lba48

