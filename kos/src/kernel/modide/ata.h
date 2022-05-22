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
#ifndef GUARD_MODIDE_ATA_H
#define GUARD_MODIDE_ATA_H 1

#include <kernel/compiler.h>

#include <kernel/fs/blkdev.h>
#include <kernel/malloc.h>
#include <kernel/refcountable.h>
#include <kernel/types.h>

#include <hybrid/byteorder.h>

#include <hw/disk/ata.h>

#if 0
#include <kernel/printk.h>
#define ATA_VERBOSE(...) printk(KERN_DEBUG __VA_ARGS__)
#else
#define ATA_VERBOSE(...) (void)0
#endif

DECL_BEGIN

typedef struct ata_bus AtaBus;
typedef struct ata_drive AtaDrive;
#define mfile_asata(self)  ((AtaDrive *)(self))
#define blkdev_asata(self) ((AtaDrive *)(self))

/* The layout of the `ah_data' field of AIO handles used with ATA */
typedef struct {
	REF AtaDrive        *hd_drive;         /* [1..1][const] The drive associated with this handle. */
	PHYS u32             hd_bufaddr;       /* Physical  buffer base address. Set to 0 when the operation is started. This is
	                                        * done to satisfy the atomic was-started condition (aka. `[COMMAND_DESCRIPTOR]')
	                                        * described by <kernel/aio.h>:[async_work(device)]:[line#8]:
	                                        * >> cmd = ATOMIC_XCH(ent->ah_data[1], NULL); */
	u16                  hd_bufsize;       /* [const] Physical buffer size (in bytes) */
	u8                   hd_io_lbaaddr[6]; /* [const] 48-bit starting LBA address. */
	u8                   hd_io_sectors[2]; /* [const] 16-bit sector read count. */
	u8                   hd_flags;         /* [const] Set of `ATA_AIO_HANDLE_F*' */
#define ATA_AIO_HANDLE_FNORMAL  0x00       /* Normal AIO handle flags. */
#define ATA_AIO_HANDLE_FWRITING 0x01       /* This is a write-operation. */
} AtaAIOHandleData;

/* Fill in `hd_io_lbaaddr' and `hd_io_sectors' with `io_lbaaddr' and `io_sectors' */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
/* TODO: This *(u32 *)&-write isn't properly unaligned and needs to use UNALIGNED_SET()! */
#define AtaAIOHandleData_SetLbaAndSectors(self, io_lbaaddr, io_sectors) \
	(*(u32 *)&(self)->hd_io_lbaaddr[0] = (u32)(io_lbaaddr),             \
	 *(u16 *)&(self)->hd_io_lbaaddr[4] = (u16)((io_lbaaddr) >> 32),     \
	 *(u16 *)&(self)->hd_io_sectors[0] = (u16)(io_sectors))
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define AtaAIOHandleData_SetLbaAndSectors(self, io_lbaaddr, io_sectors) \
	((self)->hd_io_lbaaddr[0] = (u8)(io_lbaaddr),                       \
	 (self)->hd_io_lbaaddr[1] = (u8)((io_lbaaddr) >> 8),                \
	 (self)->hd_io_lbaaddr[2] = (u8)((io_lbaaddr) >> 16),               \
	 (self)->hd_io_lbaaddr[3] = (u8)((io_lbaaddr) >> 24),               \
	 (self)->hd_io_lbaaddr[4] = (u8)((io_lbaaddr) >> 32),               \
	 (self)->hd_io_lbaaddr[5] = (u8)((io_lbaaddr) >> 40),               \
	 (self)->hd_io_sectors[0] = (u8)(io_sectors),                       \
	 (self)->hd_io_sectors[1] = (u8)((io_sectors) >> 8))
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */


/* ATA Bus states. (values for `struct ata_bus::ab_state') */
#define ATA_BUS_STATE_READY    0x0000 /* Bus is ready. Transitions to:
                                       *  - ATA_BUS_STATE_INDMA: When a DMA operation is started.
                                       *  - ATA_BUS_STATE_INPIO: Do custom BUS operations. */
#define ATA_BUS_STATE_INDMA    0x0001 /* Bus is currently performing an automatic DMA operation. Transitions to:
                                       *  - ATA_BUS_STATE_READY: All available tasks have been completed.
                                       *  - ATA_BUS_STATE_READY | ATA_BUS_STATE_WANTPIO: PIO was requested. */
#define ATA_BUS_STATE_INPIO    0x0002 /* Currently in PIO-mode: DMA is disabled, and the bus is free
                                       * to  be manually used/configured. Interrupts that may happen
                                       * while doing PIO will cause `ab_piointr' to be broadcast. */
#define ATA_BUS_STATE_MASK     0x000f /* Mask for the actual state. */
#define ATA_BUS_STATE_WANTPIO (~0xf)  /* MASK: PIO mode is requested. When this mask is non-zero, the bus  will
                                       *       change its state to `ATA_BUS_STATE_READY | ATA_BUS_STATE_WANTPIO
                                       *       at the next opportune time.  When this happens, a single  thread
                                       *       waiting for  `ab_ready' will  be woken,  which may  then try  to
                                       *       switch the bus state to `ATA_BUS_STATE_INPIO'. */
#define ATA_BUS_STATE_ONEPIO   0x0010 /* A single want-pio ticket. */



struct aio_handle;
struct ata_bus: refcountable {
	WEAK uintptr_t              ab_state;       /* [lock(ATOMIC)] ATA bus state. (one of `ATA_BUS_STATE_*') */
	WEAK struct aio_handle     *ab_aio_pending; /* [0..1][lock(ATOMIC)] Chain of scheduled AIO operations. */
	WEAK struct aio_handle     *ab_aio_current; /* [0..1][clear(ON_CANCEL)] The current AIO operation. */
	struct sig                  ab_ready;       /* Signal send when the bus switches to `ATA_BUS_STATE_READY | ATA_BUS_STATE_WANTPIO' */
	struct sig                  ab_piointr;     /* Signal broadcast for interrupts while in `ATA_BUS_STATE_INPIO' */
#define ATA_PIOINTR_ALT_ENCODE(status) ((struct sig *)((uintptr_t)0x100 | (uintptr_t)(u8)(status)))
#define ATA_PIOINTR_ALT_DECODE(resp)   ((u8)((uintptr_t)(resp) & 0xff))
	PAGEDIR_PAGEALIGNED AtaPRD *ab_prdt;        /* [1..1][valid_if(ab_dmaio != (port_t)-1)][owned][const] */
	port_t                      ab_busio;       /* [const] ATA_DEFAULT_PRIMARY_BUS:  I/O port for the ATA bus. */
	port_t                      ab_ctrlio;      /* [const] ATA_DEFAULT_PRIMARY_CTRL: Device control register/Alternate status ports. */
	port_t                      ab_dmaio;       /* [const] DMA controller port (or (port_t)-1 if unsupported) (s.a. `DMA_PRIMARY_COMMAND', ...). */
	WEAK unsigned int           ab_dma_retry;   /* [default = 3] # of times to re-attempt a DMA operation before giving up. */
	WEAK unsigned int           ab_pio_retry;   /* [default = 3] # of times to re-attempt a PIO operation before giving up. */
	ktime_t                     ab_timeout_BSY; /* [default = 3 * NSEC_PER_SEC] Timeout for how long we may wait for `ATA_DCR_BSY' */
	ktime_t                     ab_timeout_DRQ; /* [default = 3 * NSEC_PER_SEC] Timeout for how long we may wait for `ATA_DCR_DRQ' */
	ktime_t                     ab_timeout_dat; /* [default = 2 * NSEC_PER_SEC] Timeout for how long we may wait for data in PIO mode. */
	/* TODO: watchdog for DMA operations? */
};
/* `GFP_LOCKED' because maybe needed for swap */
#define _AtaBus_Alloc()    ((AtaBus *)kmalloc(sizeof(AtaBus), GFP_LOCKED | GFP_PREFLT))
#define _AtaBus_Free(self) kfree(self)



/* ATA Drive features (flat values for `struct ata_drive::ad_features') */
#define ATA_DRIVE_FEATURE_F_NORMAL 0x00 /* Normal features */
#define ATA_DRIVE_FEATURE_F_FLUSH  0x01 /* The drive supports `ATA_COMMAND_CACHE_FLUSH' function */

struct ata_drive: blkdev {
	REF AtaBus  *ad_bus;                   /* [1..1][const] Associated bus. */
	uint64_t     ad_sector_count;          /* [const][== blkdev_getsectorcount(self)] */
	uint16_t     ad_chs_cylinders;         /* [const] # of cylinders for CHS addressing */
	uint8_t      ad_chs_sectors_per_track; /* [const] # of sectors per track for CHS addressing */
	uint8_t      ad_chs_number_of_heads;   /* [const] # of heads for CHS addressing */
	uint8_t      ad_drive;                 /* [const] Used drive (either `ATA_DRIVE_MASTER' or `ATA_DRIVE_SLAVE') */
	WEAK uint8_t ad_features;              /* [lock(ATOMIC)] Set of `ATA_DRIVE_FEATURE_F*' */
#if __SIZEOF_PHYSADDR_T__ > 4
	/* Need fallback operators because DAM can only transfer into 32-bit physical addresses. */
#define ATADRIVE_HAVE_PIO_IOSECTORS

	/* [1..1][const] Fallback operators for situations where DMA can't be used. */
	NONNULL_T((1, 5)) void (KCALL *ad_pio_rdsectors)(struct mfile *__restrict self, pos_t addr, physaddr_t buf, size_t num_bytes, struct aio_multihandle *__restrict aio);
	NONNULL_T((1, 5)) void (KCALL *ad_pio_wrsectors)(struct mfile *__restrict self, pos_t addr, physaddr_t buf, size_t num_bytes, struct aio_multihandle *__restrict aio);
#endif /* __SIZEOF_PHYSADDR_T__ > 4 */
};

/* `GFP_LOCKED' because maybe needed for swap */
#define _AtaDrive_Alloc()    ((AtaDrive *)kmalloc(sizeof(AtaDrive), GFP_LOCKED | GFP_PREFLT))
#define _AtaDrive_Free(self) kfree(self)

#if defined(__INTELLISENSE__) || 0
#define CONFIG_ATA_DYNAMIC_SECTOR_SIZE 1
#define AtaDrive_GetSectorSize(dev)  blkdev_getsectormask(dev)
#define AtaDrive_GetSectorMask(dev)  blkdev_getsectorsize(dev)
#define AtaDrive_GetSectorShift(dev) blkdev_getsectorshift(dev)
#else /* ... */
#define AtaDrive_GetSectorSize(dev)  DEFAULT_ATA_SECTOR_SIZE
#define AtaDrive_GetSectorMask(dev)  (DEFAULT_ATA_SECTOR_SIZE - 1)
#define AtaDrive_GetSectorShift(dev) DEFAULT_ATA_SECTOR_SHIFT
#endif /* !... */

DECL_END

#endif /* !GUARD_MODIDE_ATA_H */
