/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_DRIVERS_ATA_H
#define GUARD_KERNEL_INCLUDE_DRIVERS_ATA_H 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <kernel/cache.h>
#include <kernel/heap.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <sched/signal.h>
#include <hw/disk/ata.h>

DECL_BEGIN

#if defined(__INTELLISENSE__) || 0
#define CONFIG_ATA_DYNAMIC_SECTOR_SIZE 1
#define ATA_SECTOR_SIZE(drive) ((drive)->bd_sector_size)
#else
#define ATA_SECTOR_SIZE(drive) ((void)(drive), DEFAULT_ATA_SECTOR_SIZE)
#endif

/* Max number of continuous PRDs allowed for a single IO operation. */
#define ATA_PRD_MAXCOUNT (PAGESIZE / SIZEOF_ATAPRD)

#ifdef __CC__
struct ata_bus;
struct ata_drive;

/* The layout of the `ah_data' field of AIO handles used with ATA */
typedef struct {
	REF struct ata_drive *hd_drive;       /* [1..1][const] The drive associated with this handle. */
	union {
		struct vm_dmalock  hd_dmalock;    /* [valid_if(ATA_AIO_HANDLE_FONEDMA)] Single DMA lock */
		struct vm_dmalock *hd_dmalockvec; /* [valid_if(!ATA_AIO_HANDLE_FONEDMA)][0..1][owned] Vector of DMA locks
		                                   * NOTE: This vector is terminated by a sentinel DMA
		                                   *       lock with its `dl_part' pointer set to `NULL' */
	};
	u8                hd_io_lbaaddr[6];/* [const] 48-bit starting LBA address. */
	u8                hd_io_sectors[2];/* [const] 16-bit sector read count. */
	u16               hd_flags;        /* Set of `ATA_AIO_HANDLE_F*' */
#define ATA_AIO_HANDLE_FNORMAL  0x0000 /* Normal AIO handle flags. */
#define ATA_AIO_HANDLE_FSINGLE  0x0001 /* Only a single PRD is required for this AIO handle. */
#define ATA_AIO_HANDLE_FWRITING 0x0002 /* FLAG: This is a write-operation. */
#define ATA_AIO_HANDLE_FSERVED  0x0004 /* FLAG: This handle has been serviced. */
#define ATA_AIO_HANDLE_FONEDMA  0x0008 /* FLAG: `hd_dmalock' is used, as opposed to `hd_dmalockvec'. */
	union {
		u16           hd_prd0_bufsize; /* [valid_if(ATA_AIO_HANDLE_FSINGLE)] Physical buffer size (in bytes) */
		u16           hd_prd_count;    /* [valid_if(!ATA_AIO_HANDLE_FSINGLE)][!0] Number of required PRD entires. */
	};
#if __SIZEOF_POINTER__ > 4
	byte_t            hd_pad[__SIZEOF_POINTER__ - 4];
#endif /* __SIZEOF_POINTER__ > 4 */
	union {
		PHYS u32      hd_prd0_bufaddr; /* [valid_if(ATA_AIO_HANDLE_FSINGLE)] Physical buffer base address. */
		AtaPRD       *hd_prd_vector;   /* [valid_if(!ATA_AIO_HANDLE_FSINGLE)][hd_prd_count][owned]
		                                * The PRD vector that must set when the operation is started. */
	};
} AtaAIOHandleData;

/* Initialize a given PRD from various sources.
 * @return: <= prd_siz: SUCCESS. In this case, the return value specifies the number of encoded
 *                      PRD entries, starting at `prd_buf'.
 * @return: > prd_siz: ERROR: More than `prd_siz' PRD entires would be required for the encoding
 *                     to succeed. - In this case, the caller should re-attempt the call after
 *                     re-allocating to match a total of at least `return' AtaPRD entries passed
 *                     to `prd_buf', and update `prd_siz' accordingly.
 * @return: 0 : ERROR: The given address range cannot be encoded as a valid PRD
 *                     This can happen for any of the following reasons:
 *                   - An `E_WOULDBLOCK' error was thrown internally (`AtaPRD_InitFromVirt' / `AtaPRD_InitFromVirtVector')
 *                   - Some portion of the given address range(s) isn't mapped (`AtaPRD_InitFromVirt' / `AtaPRD_InitFromVirtVector')
 *                   - Some portion of the given address range(s) maps to VIO memory (`AtaPRD_InitFromVirt' / `AtaPRD_InitFromVirtVector')
 *                   - A physical memory region is located beyond the 32-bit PRD limit and cannot be encoded */
INTDEF WUNUSED size_t NOTHROW(KCALL AtaPRD_InitFromPhys)(AtaPRD *__restrict prd_buf, size_t prd_siz, vm_phys_t base, size_t num_bytes);
INTDEF WUNUSED size_t NOTHROW(KCALL AtaPRD_InitFromPhysVector)(AtaPRD *__restrict prd_buf, size_t prd_siz, struct aio_pbuffer *__restrict buf, size_t num_bytes);

/* Same as the Phys functions above, however also initialize `handle->hd_dmalock' / `handle->hd_dmalockvec',
 * as well as setting the `ATA_AIO_HANDLE_FONEDMA' bit should this be required.
 * @param: for_writing: When true, the target buffer is intended to be
 *                      written to, else only intended to be read from. */
INTDEF WUNUSED size_t KCALL
AtaPRD_InitFromVirt(AtaPRD *__restrict prd_buf, size_t prd_siz, CHECKED void *base,
                    size_t num_bytes, AtaAIOHandleData *__restrict handle, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
INTDEF WUNUSED size_t KCALL
AtaPRD_InitFromVirtVector(AtaPRD *__restrict prd_buf, size_t prd_siz, struct aio_buffer *__restrict buf,
                          size_t num_bytes, AtaAIOHandleData *__restrict handle, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);


INTDEF struct aio_handle_type Ata_DmaHandleType;
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL Ata_FiniDmaHandle)(struct aio_handle *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL Ata_CancelDmaHandle)(struct aio_handle *__restrict self);
INTDEF NOBLOCK NONNULL((1)) unsigned int NOTHROW(KCALL Ata_DmaHandleProgress)(struct aio_handle *__restrict self, struct aio_handle_stat *__restrict stat);


struct ata_drive
#ifdef __cplusplus
	: block_device
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct block_device d_device;                /* The underlying block-device. */
#endif /* !__cplusplus */
	struct ata_bus     *d_bus;                   /* [1..1][const] The associated ATA bus. */
	u16                 d_chs_cylinders;         /* [const] */
	u8                  d_chs_sectors_per_track; /* [const] */
	u8                  d_chs_number_of_heads;   /* [const] */
	u8                  d_drive;                 /* [const] Used drive (either `ATA_DRIVE_MASTER' or `ATA_DRIVE_SLAVE') */
#define ATA_DRIVE_FEATURE_FNORMAL 0x00 /* Normal features */
#define ATA_DRIVE_FEATURE_FFLUSH  0x01 /* The drive supports `ATA_COMMAND_CACHE_FLUSH' function */
	u8                  d_features;              /* [const] Set of `ATA_DRIVE_FEATURE_F*' */
	u8                  d_pad[2];                /* ... */
};

struct ata_dmadrive
#ifdef __cplusplus
	: ata_drive
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct ata_drive    d_drive;                 /* The underlying drive. */
#endif /* !__cplusplus */
	/* I/O functions for performing non-canonical I/O (i.e. I/O that cannot be performed through use of pure DMA) */
	NONNULL((1, 5)) void (KCALL *d_noncanon_read)(struct ata_drive *__restrict self, USER CHECKED void *dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *d_noncanon_read_phys)(struct ata_drive *__restrict self, vm_phys_t dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *d_noncanon_readv)(struct ata_drive *__restrict self, struct aio_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *d_noncanon_readv_phys)(struct ata_drive *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *d_noncanon_write)(struct ata_drive *__restrict self, USER CHECKED void const *src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *d_noncanon_write_phys)(struct ata_drive *__restrict self, vm_phys_t src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *d_noncanon_writev)(struct ata_drive *__restrict self, struct aio_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
	NONNULL((1, 5)) void (KCALL *d_noncanon_writev_phys)(struct ata_drive *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
};

/* ATA I/O functions */
INTDEF NONNULL((1, 5)) void KCALL Ata_DmaDriveRead(struct ata_dmadrive *__restrict self, USER CHECKED void *dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_DmaDriveReadPhys(struct ata_dmadrive *__restrict self, vm_phys_t dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_DmaDriveReadVector(struct ata_dmadrive *__restrict self, struct aio_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_DmaDriveReadVectorPhys(struct ata_dmadrive *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_DmaDriveWrite(struct ata_dmadrive *__restrict self, USER CHECKED void const *src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_DmaDriveWritePhys(struct ata_dmadrive *__restrict self, vm_phys_t src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_DmaDriveWriteVector(struct ata_dmadrive *__restrict self, struct aio_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_DmaDriveWriteVectorPhys(struct ata_dmadrive *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);

INTDEF NONNULL((1, 5)) void KCALL Ata_ChsDriveRead(struct ata_drive *__restrict self, USER CHECKED void *dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_ChsDriveReadPhys(struct ata_drive *__restrict self, vm_phys_t dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_ChsDriveReadVector(struct ata_drive *__restrict self, struct aio_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_ChsDriveReadVectorPhys(struct ata_drive *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_ChsDriveWrite(struct ata_drive *__restrict self, USER CHECKED void const *src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_ChsDriveWritePhys(struct ata_drive *__restrict self, vm_phys_t src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_ChsDriveWriteVector(struct ata_drive *__restrict self, struct aio_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_ChsDriveWriteVectorPhys(struct ata_drive *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba28DriveRead(struct ata_drive *__restrict self, USER CHECKED void *dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba28DriveReadPhys(struct ata_drive *__restrict self, vm_phys_t dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba28DriveReadVector(struct ata_drive *__restrict self, struct aio_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba28DriveReadVectorPhys(struct ata_drive *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba28DriveWrite(struct ata_drive *__restrict self, USER CHECKED void const *src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba28DriveWritePhys(struct ata_drive *__restrict self, vm_phys_t src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba28DriveWriteVector(struct ata_drive *__restrict self, struct aio_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba28DriveWriteVectorPhys(struct ata_drive *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba48DriveRead(struct ata_drive *__restrict self, USER CHECKED void *dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba48DriveReadPhys(struct ata_drive *__restrict self, vm_phys_t dst, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba48DriveReadVector(struct ata_drive *__restrict self, struct aio_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba48DriveReadVectorPhys(struct ata_drive *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba48DriveWrite(struct ata_drive *__restrict self, USER CHECKED void const *src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba48DriveWritePhys(struct ata_drive *__restrict self, vm_phys_t src, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba48DriveWriteVector(struct ata_drive *__restrict self, struct aio_buffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
INTDEF NONNULL((1, 5)) void KCALL Ata_Lba48DriveWriteVectorPhys(struct ata_drive *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_sectors, lba_t addr, struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);

INTDEF NONNULL((1)) syscall_slong_t KCALL
Ata_Ioctl(struct ata_drive *__restrict self,
          struct block_device *__restrict partition,
          syscall_ulong_t cmd, USER UNCHECKED void *arg,
          iomode_t mode) THROWS(...);

union ATTR_PACKED ata_bus_state_and_flags {
	uintptr_t               b_word;
	struct ATTR_PACKED {
		WEAK uintptr_half_t b_state;     /* The current bus state (One of `ATA_BUS_STATE_*') */
		WEAK uintptr_half_t b_flags;     /* Bus flags (Set of `ATA_BUS_F*') */
	};
};

#define ATA_BUSATA_BUS_STATE_AND_FLAGS(bus)      ((union ata_bus_state_and_flags *)&(bus)->b_state)
#define ATA_BUSATA_BUS_STATE_AND_FLAGS_WORD(bus) (ATA_BUSATA_BUS_STATE_AND_FLAGS(bus)->b_word)
struct ata_bus {
	struct ata_bus     *b_nextbus;   /* [0..1][const] Another bus that is bound to the same interrupt as this one. */
	WEAK uintptr_half_t b_state;     /* The current bus state (One of `ATA_BUS_STATE_*') */
#define ATA_BUS_STATE_READY        0 /* The bus is ready to start a new operation. */
#define ATA_BUS_STATE_INDMA        1 /* The bus is running in automatic mode, servicing DMA operations as they arrive.
                                      * NOTE: This state can only be entered when `b_dmaio != (port_t)-1'
                                      * NOTE: Only the DMA handler itself, or the thread that switched to this
                                      *       state are allowed to switch to any other state. */
#define ATA_BUS_STATE_INDMA_CANCEL 2 /* An intermittent state used to cancel the currently active DMA operation.
                                      * Only `ATA_BUS_STATE_INDMA' may be transitioned into this state, at which
                                      * point the caller must cancel the active DMA operation as follows:
                                      * >> do outw(bus->b_dmaio + DMA_PRIMARY_COMMAND, 0);
                                      * >> while (inw(bus->b_dmaio + DMA_PRIMARY_STATUS) & DMA_STATUS_FDMARUNNING);
                                      * Afterwards, they are required to start a new DMA operation and transition
                                      * to `ATA_BUS_STATE_INDMA', or transition to `ATA_BUS_STATE_READY' (and
                                      * broadcast `b_sigready') when no operations are pending, or when the
                                      * `ATA_BUS_FSUSPEND' bit has been set.
                                      * Interrupts that happen while in this mode are ignored! */
#define ATA_BUS_STATE_INDMA_CANCEL_INTR 3 /* Special state used to describe an interrupt happening while in `ATA_BUS_STATE_INDMA_CANCEL'-mode. */
#define ATA_BUS_STATE_INDMA_SWITCH 4 /* A temporary state used by the ATA when a DMA operation has completed.
                                      * This state is set when checking for further pending operations, as well
                                      * as while indicating completion to the currently active handle. */
#define ATA_BUS_STATE_INPIO        5 /* A single thread has acquired an exclusive lock to the BUS, presumably
                                      * for the purpose of performing PIO data access.
                                      * NOTE: Only the thread that switched to this state is allowed to switch
                                      *       to another state.
                                      * NOTE: Interrupts happening while in this mode are handled by broadcasting
                                      *       to `b_piointr', using `sig_altbroadcast()' with the value read from
                                      *      `self->b_busio + ATA_STATUS' encoded using `ATA_PIOINTR_ALT_ENCODE()',
                                      *       which can be decoded with `ATA_PIOINTR_ALT_DECODE()' */
	WEAK uintptr_half_t b_flags;     /* Bus flags (Set of `ATA_BUS_F*') */
#define ATA_BUS_FNORMAL      0x0000  /* Normal bus flags. */
#define ATA_BUS_FSUSPEND     0x0fff  /* Suspend automatic activity (this flag is set to gracefully let the bus
                                      * finish an active DMA operation, but prevent it from continuing on with
                                      * the next one, allowing the caller to switch to `ATA_BUS_STATE_INPIO'
                                      * at the next point in time when no DMA commands are active).
                                      * NOTE: This masks the number of threads awaiting suspension. */
	struct aio_handle *b_dma_current;/* [lock(PRIVATE(ATA_BUS_STATE_INDMA ||
	                                  *               ATA_BUS_STATE_INDMA_CANCEL ||
	                                  *               ATA_BUS_STATE_INDMA_SWITCH))]
	                                  * [1..1][valid_if(IN_DMA)] The AIO handle used to control the currently active DMA operation. */
	WEAK struct aio_handle *b_dma_future;/* [0..1] Linked list of pending DMA operations. */
	struct sig          b_sigready;  /* A signal that is broadcast after the bus switches its state to `ATA_BUS_STATE_READY'
	                                  * Using this signal, a thread may wait until it becomes possible  */
	struct sig          b_piointr;   /* Signal broadcast upon interrupt whilst in `ATA_BUS_STATE_INPIO'-mode */
#define ATA_PIOINTR_ALT_ENCODE(status) ((struct sig *)((uintptr_t)0x100|(uintptr_t)(u8)(status)))
#define ATA_PIOINTR_ALT_DECODE(resp)   ((u8)((uintptr_t)(resp) & 0xff))
	port_t              b_busio;     /* [const] I/O port for the ATA bus. */
	port_t              b_ctrlio;    /* [const] Device control register/Alternate status ports. */
	port_t              b_dmaio;     /* [const] DMA controller port (or (port_t)-1 if unsupported). */
	/* None of the following fields are valid when `b_dmaio == (port_t)-1' */
	u8                  b_cancel_intr_dma_status; /* [valid_if(ATA_BUS_STATE_INDMA_CANCEL_INTR)]
	                                               * Value of `DMA_PRIMARY_STATUS' during an interrupt
	                                               * that happened within `ATA_BUS_STATE_INDMA_CANCEL' */
	u8                  b_cancel_intr_bus_status; /* [valid_if(ATA_BUS_STATE_INDMA_CANCEL_INTR)]
	                                               * Value of `ATA_STATUS' during an interrupt
	                                               * that happened within `ATA_BUS_STATE_INDMA_CANCEL' */
	AtaPRD             *b_prdt;      /* [1..ATA_PRD_MAXCOUNT][valid_if(b_dmaio != (port_t)-1)][owned]
	                                  * NOTE: This pointer is allocated using `vpage_alloc_untraced()',
	                                  *       and spans a single page of physical memory. */
	/* TODO: Some kind of watchdog job that gets executed after some given
	 *       timeout when a DMA operation seems to not want to complete.
	 *       This job will be triggered to essentially cancel the current AIO
	 *       handle (if that handle hasn't changed at that point), in order
	 *       to forceably cause an I/O timeout error due to the disk not
	 *       responding. */
};

/* Acquire/release a PIO lock for the given ata bus, allowing
 * the caller to perform bus I/O using PIO data channels. */
INTDEF void KCALL AtaBus_LockPIO(struct ata_bus *__restrict self) THROWS(E_WOULDBLOCK,...);
INTDEF NOBLOCK void NOTHROW(KCALL AtaBus_UnlockPIO)(struct ata_bus *__restrict self);
#endif /* __CC__ */



DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DRIVERS_ATA_H */
