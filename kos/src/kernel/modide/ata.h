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
#ifndef GUARD_MODIDE_ATA_H
#define GUARD_MODIDE_ATA_H 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <dev/char.h>
#include <kernel/aio.h>
#include <kernel/cache.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/mman/dma.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/async.h>
#include <sched/signal.h>
#include <sched/tsc.h>

#include <hybrid/byteorder.h>

#include <hw/disk/ata.h>
#include <kos/except/reason/io.h>


#if 0
#define ATA_VERBOSE(...) printk(KERN_DEBUG __VA_ARGS__)
#else
#define ATA_VERBOSE(...) (void)0
#endif

DECL_BEGIN

#if defined(__INTELLISENSE__) || 0
#define CONFIG_ATA_DYNAMIC_SECTOR_SIZE 1
#define ATA_SECTOR_SIZE(dev) ((dev)->bd_sector_size)
#else
#define ATA_SECTOR_SIZE(dev) DEFAULT_ATA_SECTOR_SIZE
#endif

/* Max number of continuous PRDs allowed for a single IO operation. */
#define ATA_PRD_MAXCOUNT (PAGESIZE / SIZEOF_ATAPRD)

typedef struct ata_bus_struct AtaBus;
typedef struct ata_drive_struct AtaDrive;
typedef struct ata_dma_drive_struct AtaDmaDrive;

union ata_aio_prd {
	/* NOTE: These fields are set to `NULL'/0 when the operation is started.
	 *       This is done to satisfy the atomic was-started condition (aka. `[COMMAND_DESCRIPTOR]')
	 *       described by <kernel/aio.h>:[async_work(device)]:[line#8]:
	 *       >> cmd = ATOMIC_XCH(ent->ah_data[1], NULL); */
	PHYS u32      hd_prd0_bufaddr; /* [valid_if(ATA_AIO_HANDLE_FONEPRD)] Physical buffer base address. */
	AtaPRD       *hd_prd_vector;   /* [valid_if(!ATA_AIO_HANDLE_FONEPRD)][hd_prd_count][owned]
	                                * The PRD vector that must set when the operation is started. */
};

/* The layout of the `ah_data' field of AIO handles used with ATA */
typedef struct {
	REF AtaDrive        *hd_drive;      /* [1..1][const] The drive associated with this handle. */
	union ata_aio_prd    hd_prd;        /* PRD data and atomic-command-descriptor. */
	union {
		struct mdmalock  hd_dmalock;    /* [valid_if(ATA_AIO_HANDLE_FONEDMA)] Single DMA lock */
		struct mdmalock *hd_dmalockvec; /* [valid_if(!ATA_AIO_HANDLE_FONEDMA)][0..1][owned] Vector of DMA locks
		                                 * NOTE: This vector is  terminated by  a sentinel  DMA
		                                 *       lock with its `mdl_part' pointer set to `NULL' */
	};
	u8                hd_io_lbaaddr[6]; /* [const] 48-bit starting LBA address. */
	u8                hd_io_sectors[2]; /* [const] 16-bit sector read count. */
	u16               hd_flags;         /* [const] Set of `ATA_AIO_HANDLE_F*' */
#define ATA_AIO_HANDLE_FNORMAL  0x0000  /* Normal AIO handle flags. */
#define ATA_AIO_HANDLE_FWRITING 0x0001  /* This is a write-operation. */
#define ATA_AIO_HANDLE_FONEPRD  0x0002  /* Only a single PRD is required for this AIO handle. */
#define ATA_AIO_HANDLE_FONEDMA  0x0004  /* `hd_dmalock' is used, as opposed to `hd_dmalockvec'. */
	union {
		u16           hd_prd0_bufsize;  /* [valid_if(ATA_AIO_HANDLE_FONEPRD)] Physical buffer size (in bytes) */
		u16           hd_prd_count;     /* [valid_if(!ATA_AIO_HANDLE_FONEPRD)][!0] Number of required PRD entires. */
	};
} AtaAIOHandleData;

/* Fill in `hd_io_lbaaddr' and `hd_io_sectors' with `addr' and `num_sectors' */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define AtaAIOHandleData_SetAddrAndSectors(self, addr, num_sectors) \
	(*(u32 *)&(self)->hd_io_lbaaddr[0] = (u32)(addr),               \
	 *(u16 *)&(self)->hd_io_lbaaddr[4] = (u16)((addr) >> 32),       \
	 *(u16 *)&(self)->hd_io_sectors[0] = (u16)(num_sectors))
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define AtaAIOHandleData_SetAddrAndSectors(self, addr, num_sectors) \
	((self)->hd_io_lbaaddr[0] = (u8)(addr),                         \
	 (self)->hd_io_lbaaddr[1] = (u8)((addr) >> 8),                  \
	 (self)->hd_io_lbaaddr[2] = (u8)((addr) >> 16),                 \
	 (self)->hd_io_lbaaddr[3] = (u8)((addr) >> 24),                 \
	 (self)->hd_io_lbaaddr[4] = (u8)((addr) >> 32),                 \
	 (self)->hd_io_lbaaddr[5] = (u8)((addr) >> 40),                 \
	 (self)->hd_io_sectors[0] = (u8)(num_sectors),                  \
	 (self)->hd_io_sectors[1] = (u8)((num_sectors) >> 8))
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */



#define ATA_BUS_STATE_READY    0x0000 /* Bus is ready. Transitions to:
                                       *   - ATA_BUS_STATE_INDMA: When a DMA operation is started.
                                       *   - ATA_BUS_STATE_INPIO: Do custom BUS operations.
                                       */
#define ATA_BUS_STATE_INDMA    0x0001 /* Bus is currently performing an automatic DMA operation. Transitions to:
                                       *   - ATA_BUS_STATE_READY: All available tasks have been completed.
                                       *   - ATA_BUS_STATE_READY | ATA_BUS_STATE_WANTPIO: PIO was requested. */
#define ATA_BUS_STATE_INPIO    0x0002 /* Currently in PIO-mode: DMA is disabled, and the bus is free
                                       * to  be manually used/configured. Interrupts that may happen
                                       * while doing PIO will cause `ab_piointr' to be broadcast. */
#define ATA_BUS_STATE_MASK     0x000f /* Mask for the actual state. */
#define ATA_BUS_STATE_WANTPIO (~0xf)  /* MASK: PIO mode is requested. When this mask is non-zero, the bus will change
                                       *       its   state   to   `ATA_BUS_STATE_READY | ATA_BUS_STATE_WANTPIO'    at
                                       *       the  next opportune time.  When this happens,  a single thread waiting
                                       *       for `ab_ready' will  be woken, which  may then try  to switch the  bus
                                       *       state to `ATA_BUS_STATE_INPIO'. */
#define ATA_BUS_STATE_ONEPIO   0x0010 /* A single want-pio ticket. */


struct ata_bus_struct: chrdev {
	WEAK uintptr_t          ab_state;       /* [lock(ATOMIC)] ATA bus state. (one of `ATA_BUS_STATE_*') */
	WEAK struct aio_handle *ab_aio_pending; /* [0..1][lock(ATOMIC)] Chain of scheduled AIO operations. */
	WEAK struct aio_handle *ab_aio_current; /* [0..1][clear(ON_CANCEL)] The current AIO operation. */
	struct sig              ab_ready;       /* Signal send when the bus switches to `ATA_BUS_STATE_READY | ATA_BUS_STATE_WANTPIO' */
	struct sig              ab_piointr;     /* Signal broadcast for interrupts while in `ATA_BUS_STATE_INPIO' */
#define ATA_PIOINTR_ALT_ENCODE(status) ((struct sig *)((uintptr_t)0x100 | (uintptr_t)(u8)(status)))
#define ATA_PIOINTR_ALT_DECODE(resp)   ((u8)((uintptr_t)(resp) & 0xff))
	AtaPRD                 *ab_prdt;        /* [1..ATA_PRD_MAXCOUNT][valid_if(b_dmaio != (port_t)-1)][owned]
	                                         * NOTE: This pointer is allocated using `vpage_alloc_untraced()',
	                                         *       and   spans   a   single   page   of   physical   memory. */
	port_t                  ab_busio;       /* [const] ATA_DEFAULT_PRIMARY_BUS:  I/O port for the ATA bus. */
	port_t                  ab_ctrlio;      /* [const] ATA_DEFAULT_PRIMARY_CTRL: Device control register/Alternate status ports. */
	port_t                  ab_dmaio;       /* [const] DMA controller port (or (port_t)-1 if unsupported) (s.a. `DMA_PRIMARY_COMMAND', ...). */
	WEAK unsigned int       ab_dma_retry;   /* [default = 3] # of times to re-attempt a DMA operation before giving up. */
	WEAK unsigned int       ab_pio_retry;   /* [default = 3] # of times to re-attempt a PIO operation before giving up. */
	ktime_t                 ab_timeout_BSY; /* [default = 3 * NSEC_PER_SEC] Timeout for how long we may wait for `ATA_DCR_BSY' */
	ktime_t                 ab_timeout_DRQ; /* [default = 3 * NSEC_PER_SEC] Timeout for how long we may wait for `ATA_DCR_DRQ' */
	ktime_t                 ab_timeout_dat; /* [default = 2 * NSEC_PER_SEC] Timeout for how long we may wait for data in PIO mode. */
	/* TODO: watchdog for DMA operations? */
};

struct ata_drive_struct: block_device {
	REF AtaBus         *ad_bus;                   /* [1..1][const] The bus that this drive is attached to. */
	u16                 ad_chs_cylinders;         /* [const] # of cylinders for CHS addressing */
	u8                  ad_chs_sectors_per_track; /* [const] # of sectors per track for CHS addressing */
	u8                  ad_chs_number_of_heads;   /* [const] # of heads for CHS addressing */
	u8                  ad_drive;                 /* [const] Used drive (either `ATA_DRIVE_MASTER' or `ATA_DRIVE_SLAVE') */
#define ATA_DRIVE_FEATURE_FNORMAL 0x00            /* Normal features */
#define ATA_DRIVE_FEATURE_FFLUSH  0x01            /* The drive supports `ATA_COMMAND_CACHE_FLUSH' function (TODO: Currently unused) */
	u8                  ad_features;              /* [const] Set of `ATA_DRIVE_FEATURE_F*' */
};

struct ata_dma_drive_struct: ata_drive_struct {
	/* I/O functions for performing non-canonical I/O (i.e. I/O that cannot be performed through use of pure DMA) */
	NONNULL((1, 5)) void (KCALL *add_nc_read)(AtaDrive *__restrict self, USER CHECKED byte_t *dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *add_nc_read_phys)(AtaDrive *__restrict self, physaddr_t dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *add_nc_readv)(AtaDrive *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *add_nc_readv_phys)(AtaDrive *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *add_nc_write)(AtaDrive *__restrict self, USER CHECKED byte_t const *src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *add_nc_write_phys)(AtaDrive *__restrict self, physaddr_t src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *add_nc_writev)(AtaDrive *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *add_nc_writev_phys)(AtaDrive *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
};

/* Type used for DMA-AIO handles. */
INTDEF struct aio_handle_type AtaDrive_DmaAioHandleType;

/* Append the given `handle' onto the chain of pending AIO operations. */
INTDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL AtaBus_AppendDmaAioHandle)(AtaBus *__restrict self,
                                         struct aio_handle *__restrict handle);

/* ATA I/O functions (DMA) */
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_DmaDriveRead(AtaDmaDrive *__restrict self, USER CHECKED byte_t *dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_DmaDriveReadPhys(AtaDmaDrive *__restrict self, physaddr_t dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_DmaDriveReadVector(AtaDmaDrive *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_DmaDriveReadVectorPhys(AtaDmaDrive *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_DmaDriveWrite(AtaDmaDrive *__restrict self, USER CHECKED byte_t const *src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_DmaDriveWritePhys(AtaDmaDrive *__restrict self, physaddr_t src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_DmaDriveWriteVector(AtaDmaDrive *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_DmaDriveWriteVectorPhys(AtaDmaDrive *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);

/* ATA I/O functions (non-DMA) */
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_ChsDriveRead(AtaDrive *__restrict self, USER CHECKED byte_t *dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_ChsDriveReadPhys(AtaDrive *__restrict self, physaddr_t dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_ChsDriveReadVector(AtaDrive *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_ChsDriveReadVectorPhys(AtaDrive *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_ChsDriveWrite(AtaDrive *__restrict self, USER CHECKED byte_t const *src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_ChsDriveWritePhys(AtaDrive *__restrict self, physaddr_t src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_ChsDriveWriteVector(AtaDrive *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_ChsDriveWriteVectorPhys(AtaDrive *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba28DriveRead(AtaDrive *__restrict self, USER CHECKED byte_t *dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba28DriveReadPhys(AtaDrive *__restrict self, physaddr_t dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba28DriveReadVector(AtaDrive *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba28DriveReadVectorPhys(AtaDrive *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba28DriveWrite(AtaDrive *__restrict self, USER CHECKED byte_t const *src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba28DriveWritePhys(AtaDrive *__restrict self, physaddr_t src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba28DriveWriteVector(AtaDrive *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba28DriveWriteVectorPhys(AtaDrive *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba48DriveRead(AtaDrive *__restrict self, USER CHECKED byte_t *dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba48DriveReadPhys(AtaDrive *__restrict self, physaddr_t dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba48DriveReadVector(AtaDrive *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba48DriveReadVectorPhys(AtaDrive *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba48DriveWrite(AtaDrive *__restrict self, USER CHECKED byte_t const *src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba48DriveWritePhys(AtaDrive *__restrict self, physaddr_t src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba48DriveWriteVector(AtaDrive *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL AtaDrive_Lba48DriveWriteVectorPhys(AtaDrive *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);

/* Device I/O control callback for ATA drive objects. */
INTDEF NONNULL((1)) syscall_slong_t KCALL
AtaDrive_Ioctl(AtaDrive *__restrict self,
               struct block_device *__restrict partition,
               syscall_ulong_t cmd, USER UNCHECKED void *arg,
               iomode_t mode) THROWS(...);

/* Acquire/release a PIO lock for the given ata bus, allowing
 * the  caller to  perform bus  I/O using  PIO data channels. */
INTDEF NONNULL((1)) void FCALL AtaBus_LockPIO(AtaBus *__restrict self) THROWS(E_WOULDBLOCK, ...);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL AtaBus_UnlockPIO)(AtaBus *__restrict self);

/* Start a hardware-level DMA operation for the given `handle'
 * @return: true:  DMA has been initiated
 * @return: false: The handle was canceled before DMA could begin (try the next handle!) */
INTDEF NOBLOCK bool
NOTHROW(FCALL AtaBus_HW_StartDma)(AtaBus *__restrict self,
                                  struct aio_handle *__restrict handle,
                                  union ata_aio_prd prd);

/* Same as `AtaBus_HW_StartDma()', but assume that `self->ab_prdt' is already initialized. */
INTDEF NOBLOCK bool
NOTHROW(FCALL AtaBus_HW_StartDirectDma)(AtaBus *__restrict self,
                                        struct aio_handle *__restrict handle);

/* Cancel the currently active hardware-level DMA operation */
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL AtaBus_HW_CancelDma)(AtaBus *__restrict self);

/* Return the # of bytes that have already been transfered as part
 * of the currently in-progress AIO operation. If no AIO operation
 * is currently in progress, the return value is weakly undefined. */
INTDEF NOBLOCK size_t
NOTHROW(FCALL AtaBus_HW_GetDmaProgress)(AtaBus *__restrict self);

/* Interrupt handler for ATA BUS controllers. */
INTDEF NOBLOCK NOPREEMPT bool
NOTHROW(FCALL AtaBus_HW_InterruptHandler)(AtaBus *__restrict self);

/* Same as `AtaBus_HW_InterruptHandler()', but used if the bus supports DMA */
INTDEF NOBLOCK NOPREEMPT bool
NOTHROW(FCALL AtaBus_HW_DmaInterruptHandler)(AtaBus *__restrict self);

/* Return the interrupt handler to use for `AtaBus *self' */
#define AtaBus_HW_GetInterruptHandler(self) \
	((self)->ab_dmaio != (port_t)-1         \
	 ? &AtaBus_HW_DmaInterruptHandler       \
	 : &AtaBus_HW_InterruptHandler)

/* Start the next pending DMA operation (if there is one). Otherwise,
 * switch the bus's state ATA_BUS_STATE_INDMA -> ATA_BUS_STATE_READY.
 * If there are pending WANTPIO requests, always switch to READY, and
 * signal a single waiting thread. */
INTDEF NOBLOCK void
NOTHROW(FCALL AtaBus_StartNextDmaOperation)(AtaBus *__restrict self);



/* Initialize a given PRD from various sources.
 * @return: <= prd_siz: SUCCESS. In this case, the return value specifies the number of encoded
 *                      PRD entries, starting at `prd_buf'.
 * @return: > prd_siz: ERROR: More than `prd_siz' PRD entires would be required for the encoding
 *                     to  succeed. - In this case, the  caller should re-attempt the call after
 *                     re-allocating to match a total of at least `return' AtaPRD entries passed
 *                     to `prd_buf', and update `prd_siz' accordingly.
 * @return: 0 : ERROR: The given address range cannot be encoded as a valid PRD
 *                     This can  happen  for  any  of  the  following  reasons:
 *                   - An `E_WOULDBLOCK' error was thrown internally (`AtaPRD_InitFromVirt' / `AtaPRD_InitFromVirtVector')
 *                   - Some portion of the given address range(s) isn't mapped (`AtaPRD_InitFromVirt' / `AtaPRD_InitFromVirtVector')
 *                   - Some portion of the given address range(s) maps to VIO memory (`AtaPRD_InitFromVirt' / `AtaPRD_InitFromVirtVector')
 *                   - A physical memory region is located beyond the 32-bit PRD limit and cannot be encoded */
INTDEF WUNUSED size_t
NOTHROW(KCALL AtaPRD_InitFromPhys)(AtaPRD *__restrict prd_buf, size_t prd_siz,
                                   physaddr_t base, size_t num_bytes);
INTDEF WUNUSED size_t
NOTHROW(KCALL AtaPRD_InitFromPhysVector)(AtaPRD *__restrict prd_buf, size_t prd_siz,
                                         struct iov_physbuffer *__restrict buf, size_t num_bytes);

/* Same as the Phys functions above, however also initialize `handle->hd_dmalock' / `handle->hd_dmalockvec',
 * as well as setting the `ATA_AIO_HANDLE_FONEDMA' bit should this be required.
 * @param: for_writing: When true, the target buffer is intended to  be
 *                      written to, else only intended to be read from. */
INTDEF WUNUSED size_t KCALL
AtaPRD_InitFromVirt(AtaPRD *__restrict prd_buf, size_t prd_siz, CHECKED void *base,
                    size_t num_bytes, AtaAIOHandleData *__restrict handle, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
INTDEF WUNUSED size_t KCALL
AtaPRD_InitFromVirtVector(AtaPRD *__restrict prd_buf, size_t prd_siz, struct iov_buffer *__restrict buf,
                          size_t num_bytes, AtaAIOHandleData *__restrict handle, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);



typedef u32 AtaError_t; /* ATA error  */
#define ATA_ERROR(error, reason) (ERROR_SUBCLASS(ERROR_CODEOF(error)) | ((reason) << 16))
#define ATA_ERROR_OK             0x0000
#define ATA_ERROR_CLASS(x)       E_IOERROR
#define ATA_ERROR_SUBCLASS(x)    ((x)&0xffff)
#define ATA_ERROR_REASON(x)      (((x) >> 16) & 0xffff)

/* Complete the given AIO handle with an ATA error code. */
INTDEF NOBLOCK ATTR_COLD NONNULL((1)) void
NOTHROW(FCALL AtaDrive_DmaAioHandle_CompleteWithError)(struct aio_handle *__restrict self,
                                                       AtaError_t error);

/* Complete the given, generic AIO handle with an ATA error code. */
INTDEF NOBLOCK ATTR_COLD NONNULL((1)) void
NOTHROW(FCALL AioHandle_CompleteWithAtaError)(struct aio_handle *__restrict self,
                                              AtaError_t error);

/* Complete successfully. */
INTDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL AtaDrive_DmaAioHandle_Complete_NoPR)(struct aio_handle *__restrict self);


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

/* Wait for `!ATA_DCR_BSY', but time out eventually. */
INTDEF NOBLOCK AtaError_t NOTHROW(FCALL AtaBus_HW_WaitForBusy_P)(port_t ctrlio, ktime_t timeout_BSY);
INTDEF NOBLOCK AtaError_t NOTHROW(FCALL AtaBus_HW_WaitForBusy)(AtaBus *__restrict self);

/* Wait for `ATA_DCR_DRQ', but time out eventually. */
INTDEF NOBLOCK AtaError_t
NOTHROW(FCALL AtaBus_HW_WaitForDrq)(AtaBus *__restrict self);

/* Reset the given bus on a hardware-level. */
INTDEF NOBLOCK void NOTHROW(FCALL AtaBus_HW_ResetBus_P)(port_t ctrlio);
#define AtaBus_HW_ResetBus(self) AtaBus_HW_ResetBus_P((self)->ab_ctrlio)

/* Same as `AtaBus_HW_ResetBus()', but re-initialize DMA afterwards. */
INTDEF NOBLOCK void
NOTHROW(FCALL AtaBus_HW_ResetBusAndInitializeDMA)(AtaBus *__restrict self);

#define AtaBus_HW_ResetBusAuto(self) \
	((self)->ab_dmaio == (port_t)-1  \
	 ? AtaBus_HW_ResetBus(bus)       \
	 : AtaBus_HW_ResetBusAndInitializeDMA(bus))


DECL_END

#endif /* !GUARD_MODIDE_ATA_H */
