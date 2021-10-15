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
#ifndef GUARD_KERNEL_INCLUDE_DEV_BLOCK_H
#define GUARD_KERNEL_INCLUDE_DEV_BLOCK_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>
#include <sched/rwlock.h>

#include <hybrid/__altint.h>
#include <hybrid/sequence/atree.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/guid.h>

DECL_BEGIN

#ifdef __CC__
/* BLOCK DEVICE API (With an ABI designed for DMA support) */
struct block_device;
struct iov_buffer;
struct iov_physbuffer;
__HYBRID_ALTINT_TYPEDEF(u64, lba_t, false); /* LinearBlockAddress */

struct block_device_type {
	/* [0..1] Finalizer callback.
	 * NOTE: In  order to ensure  a safe cleanup, this  function (while required to
	 *       be async-safe) will always be executed in the context of the boot CPU.
	 * Since the boot CPU is meant to be responsible for serving any and all device
	 * interrupts, by disabling  preemption within this  finalizer, you can  safely
	 * modify  data structures that are used locklessly by such interrupt handlers. */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/ (KCALL *dt_fini)(struct block_device *__restrict self);
	/* [1..1] Read function.
	 * NOTE: Errors  may  propagated  by  calling  `aio->ah_func'  with `AIO_COMPLETION_FAILURE'
	 *       Errors that are thrown by this function are automatically passed to `aio->ah_func'.
	 * @assume(num_sectors != 0);
	 * @param: self:        The block device being addressed.
	 * @param: dst:         The buffer target address.
	 * @param: addr:        The LBA index of the first sector from which to starting reading.
	 * @param: num_sectors: The amount of sectors to read. - Also specifies the target buffer as
	 *                      consisting of a total of `num_sectors * self->bd_sector_size' bytes.
	 * @param: aio:         ASYNC I/O completion handle. */
	NONNULL((1, 5))
	void (KCALL *dt_read)(struct block_device *__restrict self,
	                      USER CHECKED void *dst, size_t num_sectors,
	                      lba_t addr, /*out*/ struct aio_handle *__restrict aio)
			THROWS(E_IOERROR, E_BADALLOC, ...);
	NONNULL((1, 5))
	void (KCALL *dt_read_phys)(struct block_device *__restrict self,
	                           physaddr_t dst, size_t num_sectors,
	                           lba_t addr, /*out*/ struct aio_handle *__restrict aio)
			THROWS(E_IOERROR, E_BADALLOC, ...);
	NONNULL((1, 5))
	void (KCALL *dt_readv)(struct block_device *__restrict self,
	                       struct iov_buffer *__restrict buf, size_t num_sectors,
	                       lba_t addr, /*out*/ struct aio_handle *__restrict aio)
			THROWS(E_IOERROR, E_BADALLOC, ...);
	NONNULL((1, 5))
	void (KCALL *dt_readv_phys)(struct block_device *__restrict self,
	                            struct iov_physbuffer *__restrict buf, size_t num_sectors,
	                            lba_t addr, /*out*/ struct aio_handle *__restrict aio)
			THROWS(E_IOERROR, E_BADALLOC, ...);
	/* [1..1] Write function.
	 * Same as `dt_read', but used for writing data instead.
	 * NOTE: Errors  may  propagated  by  calling  `aio->ah_func'  with `AIO_COMPLETION_FAILURE'
	 *       Errors that are thrown by this function are automatically passed to `aio->ah_func'.
	 * NOTE: The caller is responsible to check the `BLOCK_DEVICE_FLAG_READONLY' flag,
	 *       and  trigger  an   `E_IOERROR_READONLY'  error  if   that  bit  is   set.
	 * @assume(num_sectors != 0); */
	NONNULL((1, 5))
	void (KCALL *dt_write)(struct block_device *__restrict self,
	                       USER CHECKED void const *src, size_t num_sectors,
	                       lba_t addr, /*out*/ struct aio_handle *__restrict aio)
			THROWS(E_IOERROR, E_BADALLOC, ...);
	NONNULL((1, 5))
	void (KCALL *dt_write_phys)(struct block_device *__restrict self,
	                            physaddr_t src, size_t num_sectors,
	                            lba_t addr, /*out*/ struct aio_handle *__restrict aio)
			THROWS(E_IOERROR, E_BADALLOC, ...);
	NONNULL((1, 5))
	void (KCALL *dt_writev)(struct block_device *__restrict self,
	                        struct iov_buffer *__restrict buf, size_t num_sectors,
	                        lba_t addr, /*out*/ struct aio_handle *__restrict aio)
			THROWS(E_IOERROR, E_BADALLOC, ...);
	NONNULL((1, 5))
	void (KCALL *dt_writev_phys)(struct block_device *__restrict self,
	                             struct iov_physbuffer *__restrict buf, size_t num_sectors,
	                             lba_t addr, /*out*/ struct aio_handle *__restrict aio)
			THROWS(E_IOERROR, E_BADALLOC, ...);
	/* [0..1] Perform a misc. ioctl() command on this block device.
	 * @param: partition: The actual partition on which the ioctl() was performed.
	 *                    In case the command was  invoked on the primary  device,
	 *                    this argument will be equal to `self' */
	NONNULL((1))
	syscall_slong_t (KCALL *dt_ioctl)(struct block_device *__restrict self,
	                                  struct block_device *__restrict partition, syscall_ulong_t cmd,
	                                  USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
};

#endif /* __CC__ */

#ifndef BLOCK_DEVICE_FLAG_NORMAL
#define BLOCK_DEVICE_FLAG_NORMAL    0x0000 /* Normal block-device flags. */
#define BLOCK_DEVICE_FLAG_READONLY  0x0001 /* Read-only device / partition (attempting to write will cause `E_IOERROR_READONLY' to be thrown). */
#define BLOCK_DEVICE_FLAG_PARTITION 0x8000 /* [const] This one's a partition */
#endif /* !BLOCK_DEVICE_FLAG_NORMAL */

#ifdef __CC__
struct block_device_partition;
struct inode;
struct fdirent;

#define __BLKDEV_FIELDS                                                                                                      \
	REF refcnt_t                   bd_refcnt;       /* Reference counter */                                                              \
	size_t                         bd_heapsize;     /* [const] Allocated heap-size of this block-device. */                              \
	struct block_device_type       bd_type;         /* [1..1][const] Block device type + callbacks. */                                   \
	ATREE_NODE_SINGLE(struct blkdev, dev_t)                                                                                  \
	                               bd_devlink;      /* [lock(WRITE_ONCE)] Device number / tree (`DEV_UNSET' if unset). */                \
	REF struct inode              *bd_devfs_inode;  /* [lock(WRITE_ONCE)][0..1] Device INode under /dev, or NULL if not created */       \
	REF struct fdirent    *bd_devfs_entry;  /* [lock(WRITE_ONCE)][1..1][valid_if(bd_devfs_inode)] Directory entry under /dev */  \
	pos_t                          bd_total_bytes;  /* [!0][const] The total number of bytes (== bd_sector_count * bd_sector_size). */   \
	lba_t                          bd_sector_count; /* [!0][const] Number of available sectors. */                                       \
	size_t                         bd_sector_size;  /* [!0][const] Size of a single sector (in bytes). */                                \
	uintptr_half_t                 bd_flags;        /* Block device flags (Set of `BD_F*') */                                            \
	char                           bd_name[16];     /* [const] Name of the device (auto-generated when unset during device registration) \
	                                                 * This is the name by which the device can be discovered within the `/dev' directory. */



struct blkdev {
	__BLKDEV_FIELDS
};
#endif /* __CC__ */



#define BD_MAX_CACHE_SECTORS       16 /* Max # of sectors to cache for use by `block_device_(read|write|sync)()' */
#define BD_CACHED_SECTOR_FNORMAL   0x0000 /* Normal cached sector flags. */
#define BD_CACHED_SECTOR_FPRESENT  0x0001 /* This sector cache is present. */
#define BD_CACHED_SECTOR_FCHANGED  0x0002 /* The contents of this sector have been changed. */
#define BD_CACHED_SECTOR_FFLUSHING 0x0004 /* The sector is currently being flushed (don't modify until this was unset). */

#ifdef __CC__
struct bd_cached_sector {
	uintptr_t           cs_flags; /* Cached sector flags (Set of `BD_CACHED_SECTOR_F*') */
#if __SIZEOF_POINTER__ < 8
	uintptr_t           cs_pad[(8-sizeof(void *)) / sizeof(void *)]; /* ... */
#endif /* __SIZEOF_POINTER__ < 8 */
	lba_t               cs_addr;  /* LBA number of the cached sector. */
};



SLIST_HEAD(block_device_partition_list, block_device_partition);
struct block_device
#ifdef __cplusplus
	: blkdev
#endif /* __cplusplus */
{
#ifndef __cplusplus
	__BLKDEV_FIELDS
#endif /* !__cplusplus */
	struct block_device_partition_list   bd_parts;      /* [0..1][lock(bd_parts_lock)] Sub-partitions of this device.
	                                                     * NOTE: Always   `NULL'   for   partitions   devices!
	                                                     *       Attempting to sub-partition another partition
	                                                     *       will simply simply adjust offsets, and create
	                                                     *       the new partition as part of the main device. */
	WEAK struct block_device_partition  *bd_delparts;   /* [0..1] Chain of  partitions  that  should  be  deleted.
	                                                     * Whenever  a lock to `bd_parts_lock' should be acquired,
	                                                     * this chain must be cleared. In the case of a read-lock,
	                                                     * this attempt must be made  after a try-upgrade, and  in
	                                                     * the case of a write-lock always. */
	struct atomic_rwlock                 bd_parts_lock; /* Lock for sub-partitions of this device. */
	guid_t                               bd_guid;       /* Disk GUID (set during auto-partitioning) */
	struct rwlock                        bd_cache_lock; /* Lock for `bd_cache' */
	struct bd_cached_sector              bd_cache[BD_MAX_CACHE_SECTORS]; /* [lock(bd_cache_lock)] Cache for `block_device_(read|write)()' */
	unsigned int                         bd_cache_cnxt; /* Next cache slot to reset and re-use. */
	size_t                               bd_cache_size; /* [const][!0] Allocated heap size of `bd_cache_base' */
	/* TODO: Make so that `bd_cache_base' is allocated in continuous memory,
	 *       and  store its physical  base address here  in order to improve
	 *       performance when interfacing with DMA. */
	byte_t                              *bd_cache_base; /* [lock(bd_cache_lock)][const]
	                                                     * [1..BD_MAX_CACHE_SECTORS * bd_cache_ssiz]
	                                                     * [owned][== mnode_getminaddr(&bd_cache_node)]
	                                                     * Base   address   for   the   sector   cache. */
	size_t                               bd_cache_ssiz; /* [const][!0][>= bd_sector_size]    offset    between    sectors    in     `bd_cache_base'.
	                                                     * Cached data for cache-index `i' can then be found at `bd_cache_base + i * bd_cache_ssiz',
	                                                     * where `i' is an index into `bd_cache' */
	u8                                   bd_max_retry;  /* How often to re-attempt I/O, not counting the first attempt.
	                                                     * Set to 0xff to allow infinite retries.
	                                                     * TODO: The ATA driver needs to make use of this! */
	u8                                   bd_pad[sizeof(void *)-1]; /* ... */
};


/* Acquire / release a read/write lock to part-list of a given block-device. */
FUNDEF NONNULL((1)) void KCALL block_device_acquire_partlock_read(struct block_device *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) void KCALL block_device_acquire_partlock_write(struct block_device *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(KCALL block_device_acquire_partlock_tryread)(struct block_device *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(KCALL block_device_acquire_partlock_trywrite)(struct block_device *__restrict self);



struct block_device_partition
#ifdef __cplusplus
	: blkdev
#endif /* __cplusplus */
{
#ifndef __cplusplus
	__BLKDEV_FIELDS
#endif /* !__cplusplus */
	REF struct block_device       *bp_master;    /* [1..1][const] The master device for which this is a partition. */
	SLIST_ENTRY(block_device_partition)
	                               bp_parts;     /* [lock(bp_master->bd_parts_lock)] Chain of partitions. */
	pos_t                          bp_minaddr;   /* [const][== bp_min * bd_sector_size] Starting position of this partition. */
	lba_t                          bp_min;       /* [const][<= bp_max] Starting LBA of this partition. */
	lba_t                          bp_max;       /* [const][>= bp_min] Ending LBA of this partition. */
	char                           bp_label[63]; /* [const] User-assigned label for the partition. (set during auto-partitioning) */
	u8                             bp_sysid;     /* [const] Partition system ID (used by MBR; `0' if unknown) */
	guid_t                         bp_typeguid;  /* [const] Disk type GUID. (set during auto-partitioning) Used by EFI partitions. */
	guid_t                         bp_partguid;  /* [const] Disk partition GUID. (set during auto-partitioning) */
};
#undef __BLKDEV_FIELDS

/* The functions used by partition block devices. */
FUNDEF NONNULL((1, 5)) void KCALL block_device_partition_read(struct block_device *__restrict self, USER CHECKED void *dst, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void KCALL block_device_partition_write(struct block_device *__restrict self, USER CHECKED void const *src, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void KCALL block_device_partition_readv(struct block_device *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void KCALL block_device_partition_writev(struct block_device *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void KCALL block_device_partition_read_phys(struct block_device *__restrict self, physaddr_t dst, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void KCALL block_device_partition_write_phys(struct block_device *__restrict self, physaddr_t src, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void KCALL block_device_partition_readv_phys(struct block_device *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void KCALL block_device_partition_writev_phys(struct block_device *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1)) syscall_slong_t KCALL block_device_partition_ioctl(struct block_device *__restrict self, struct block_device *__restrict partition, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);


/* Destroy a given block device. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL block_device_destroy)(struct blkdev *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct blkdev, bd_refcnt, block_device_destroy)

/* Allocate and initialize a new block device.
 * The   caller    must   still    initialize:
 *   >> return->bd_type;
 *   >> return->bd_total_bytes;
 *   >> return->bd_sector_count;
 * As well as optionally:
 *   >> return->bd_name
 * This function will initialize the following memory to non-zero values:
 *   >> return->bd_max_retry = 2;
 */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct block_device *KCALL
block_device_alloc(size_t sector_size DFL(512),
                   size_t structure_size DFL(sizeof(struct block_device)))
		THROWS(E_BADALLOC, E_WOULDBLOCK);

/* Returns the device number of `self', or `DEV_UNSET' if not set. */
#define block_device_devno(self) ((self)->bd_devlink.a_vaddr)

/* Lookup  a block device associated with `devno'  and return a reference to it.
 * When no block device is associated that device number, return `NULL' instead. */
FUNDEF WUNUSED REF struct blkdev *KCALL
block_device_lookup(dev_t devno) THROWS(E_WOULDBLOCK);

/* Same as `block_device_lookup()', but return `NULL'
 * if  the  lookup  would have  caused  an exception. */
FUNDEF WUNUSED REF struct blkdev *
NOTHROW(KCALL block_device_lookup_nx)(dev_t devno);

/* Lookup a block device, given its `name`, with is its default filename
 * as will appear in the /dev/ directory, and may optionally be prefixed
 * by a string `/dev/' that is stripped before comparison.
 * Alternatively, the given `name' may also be in the form of `MAJOR:MINOR',
 * an  encoding that is  always attempted first by  attempting to decode the
 * given name using `scanf("%u:%u")'
 * >> block_device_lookup_name("3:64");      // MKDEV(3, 64)
 * >> block_device_lookup_name("/dev/hdc1"); // MKDEV(22, 0) + 1
 * >> block_device_lookup_name("hda2");      // MKDEV(3, 0)  + 2
 * This function is mainly intended for decoding device names from commandline
 * arguments, such as  the kernel's `boot=<NAME>'  option which overrides  the
 * kernel's boot partition (in case the kernel can't auto-detect its partition
 * properly).
 * @return: NULL: No device matching `name' exists. */
FUNDEF WUNUSED REF struct blkdev *KCALL
block_device_lookup_name(USER CHECKED char const *name)
		THROWS(E_WOULDBLOCK, E_SEGFAULT);
#ifdef __cplusplus
extern "C++" {
FUNDEF WUNUSED REF struct blkdev *KCALL
block_device_lookup(USER CHECKED char const *name)
		THROWS(E_WOULDBLOCK, E_SEGFAULT)
		ASMNAME("block_device_lookup_name");
}
#endif /* __cplusplus */


/* Unregister  the  given  block-device  from  the  block-device-id  tree,  as  well as
 * removing its auto-generated entry from `/dev' (should that entry have been created).
 * @return: true:  Successfully unregistered the given.
 * @return: false: The device was never registered to begin with. */
FUNDEF NONNULL((1)) bool KCALL
block_device_unregister(struct blkdev *__restrict self)
		THROWS(E_WOULDBLOCK);

/* Register a block device with a fixed device number.
 * NOTE: When empty, `bd_name' will be set to `"%.2x:%.2x" % (MAJOR(devno),MINOR(devno))'
 * NOTE: This function will also cause the device to appear in `/dev' (unless the device's name is already taken) */
FUNDEF NONNULL((1)) void KCALL
block_device_register(struct blkdev *__restrict self, dev_t devno)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Automatically register the given block-device, assigning it an auto-generated device ID.
 * If `self'  is a  partition (s.a.  `block_device_ispartition()'), assign  based on  other
 * preexisting   partitions   `MKDEV(MAJOR(bp_master),LOWEST_UNUSED_MINOR)',   or    assign
 * `MKDEV(MAJOR(bp_master),MINOR(bp_master) + 1)'.
 * All other devices are assigned some unique major device number `>= DEV_MAJOR_AUTO' with MINOR set to `0'.
 * NOTE:   When   empty,    `bd_name'   will   be    set   to    `"%.2x:%.2x" % (MAJOR(devno),MINOR(devno))'
 * NOTE: This function will also cause the device to appear in `/dev' (unless the device's name is already taken) */
FUNDEF NONNULL((1)) void KCALL
block_device_register_auto(struct blkdev *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Check if `self' is a partition. */
#define block_device_ispartition(self) \
	((self)->bd_type.dt_read == &block_device_partition_read)

/* Create a new sub-partition for `master', placing it as the given address.
 * Following this, automatically register the new partition with `block_device_register_auto()',
 * after assigning the name `"%s%u" % (master->bd_name,MINOR(block_device_devno(return)) - MINOR(block_device_devno(master)))'.
 * NOTE: If another partition with the same `part_min' and `part_max', no new
 *       partition is created, and that  partition will be returned  instead.
 * @param: part_label:    The name of the partition, or `NULL'
 * @param: part_sysid:    The partition system ID, or `0'
 * @param: part_typeguid: The partition type GUID, or `NULL'
 * @param: part_partguid: The partition GUID, or `NULL' */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct block_device_partition *KCALL
block_device_makepart(struct blkdev *__restrict master,
                      lba_t part_min, lba_t part_max,
                      char const *part_label DFL(__NULLPTR),
                      size_t part_label_size DFL(0),
                      u8 part_sysid DFL(0),
                      guid_t const *part_typeguid DFL(__NULLPTR),
                      guid_t const *part_partguid DFL(__NULLPTR),
                      uintptr_half_t flags DFL(BLOCK_DEVICE_FLAG_NORMAL))
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...);


/* Automatically parse the MBR/EFI tables of the disk, and try to partition if accordingly.
 * If one of the partitions  found have the ACTIVE/BOOTABLE flag  set, a reference to  that
 * partition is returned to the  caller. If more than one  partition has that flag set,  or
 * if none of them do, `NULL' is returned instead, though the function has still succeeded.
 * NOTE: The caller should invoke `block_device_delparts' in the master partition beforehand.
 * NOTE: When `self' is a partition itself, its contents will still be parsed for partition
 *       tables like they usually would, though new  partitions will still be added to  the
 *       master device, as `block_device_makepart()' is used to create them. */
FUNDEF NONNULL((1)) void KCALL
block_device_autopart(struct blkdev *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK);
FUNDEF WUNUSED NONNULL((1)) REF struct block_device_partition *KCALL
block_device_autopart_ex(struct blkdev *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK);

/* Delete (unregister + unlink) all partitions of `self' */
FUNDEF NONNULL((1)) void KCALL
block_device_delparts(struct block_device *__restrict self)
		THROWS(E_WOULDBLOCK);


/* Read/write data to/from a block device or partition.
 * NOTE: Attempting  to  read  outside  of  the  valid  device  LBA  bounds  will  yield  all  zeros.
 * NOTE: Attempting to write outside of the valid device LBA bounds will cause `E_IOERROR_BADBOUNDS'.
 * NOTE: `completed' is guarantied to get executed, even if an exception is thrown. */
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_aread_sector)(struct blkdev *__restrict self, USER CHECKED void *dst, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_awrite_sector)(struct blkdev *__restrict self, USER CHECKED void const *src, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_aread_phys_sector)(struct blkdev *__restrict self, physaddr_t dst, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_awrite_phys_sector)(struct blkdev *__restrict self, physaddr_t src, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_areadv_sector)(struct blkdev *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_awritev_sector)(struct blkdev *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_areadv_phys_sector)(struct blkdev *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_awritev_phys_sector)(struct blkdev *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_aread)(struct blkdev *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_awrite)(struct blkdev *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_aread_phys)(struct blkdev *__restrict self, physaddr_t dst, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_awrite_phys)(struct blkdev *__restrict self, physaddr_t src, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_areadv)(struct blkdev *__restrict self, struct iov_buffer *__restrict buf, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_awritev)(struct blkdev *__restrict self, struct iov_buffer *__restrict buf, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_areadv_phys)(struct blkdev *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL block_device_awritev_phys)(struct blkdev *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);
FUNDEF NONNULL((1)) void KCALL block_device_read_sync(struct blkdev *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC,E_SEGFAULT,...);
FUNDEF NONNULL((1)) void KCALL block_device_write_sync(struct blkdev *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,E_SEGFAULT,...);
FUNDEF NONNULL((1)) void KCALL block_device_read_phys_sync(struct blkdev *__restrict self, physaddr_t dst, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1)) void KCALL block_device_write_phys_sync(struct blkdev *__restrict self, physaddr_t src, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);
FUNDEF NONNULL((1)) void KCALL block_device_readv_sync(struct blkdev *__restrict self, struct iov_buffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC,E_SEGFAULT,...);
FUNDEF NONNULL((1)) void KCALL block_device_writev_sync(struct blkdev *__restrict self, struct iov_buffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,E_SEGFAULT,...);
FUNDEF NONNULL((1)) void KCALL block_device_readv_phys_sync(struct blkdev *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1)) void KCALL block_device_writev_phys_sync(struct blkdev *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);

/* High-level  read/write  to/from  a  block-device,  on  a  per-byte   basis.
 * These functions are mainly intended for use by file-system drivers, as well
 * as for creating disk partitions.  - Regular user-space access usually  goes
 * through the VM data-block mapping interface,  which is backed by some  sort
 * of system  which will  call  though to  `block_device_a(read|write)()',  if
 * not `block_device_a(read|write)_sector()'. */
FUNDEF NONNULL((1)) void KCALL block_device_read(struct blkdev *__restrict self, VIRT CHECKED void *dst, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1)) void KCALL block_device_write(struct blkdev *__restrict self, VIRT CHECKED void const *src, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);
FUNDEF NONNULL((1)) void KCALL block_device_read_phys(struct blkdev *__restrict self, physaddr_t dst, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1)) void KCALL block_device_write_phys(struct blkdev *__restrict self, physaddr_t src, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);
FUNDEF NONNULL((1, 2)) void KCALL block_device_readv(struct blkdev *__restrict self, struct iov_buffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 2)) void KCALL block_device_writev(struct blkdev *__restrict self, struct iov_buffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);
FUNDEF NONNULL((1, 2)) void KCALL block_device_readv_phys(struct blkdev *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC,...);
FUNDEF NONNULL((1, 2)) void KCALL block_device_writev_phys(struct blkdev *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,...);


/* Synchronous all cached sectors that have been modified by prior calls to `block_device_write()'
 * @return: * : The number of dirty sectors that were synced. */
FUNDEF NONNULL((1)) size_t KCALL block_device_sync(struct blkdev *__restrict self)
		THROWS(E_IOERROR, E_IOERROR_READONLY, E_BADALLOC, ...);

/* TODO: `block_device_sync_a()' (same as `block_device_sync()', but is done asynchronously) */


/* TODO: Get rid of `boot_partition'. Determining the root filesystem should
 *       only make use of indicators taken from devices known at that point,
 *       and fill in at some earlier point in time.
 *       After that, the ~boot_partition~ should be determined via:
 *           vfs_kernel->root->inode->super->device */
/* [0..1] The  block  device  / partition  from  which the  kernel  was booted.
 * Set to `(struct blkdev *)-1' if indeterminate during early boot. */
DATDEF REF struct blkdev *boot_partition;
#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_BLOCK_H */
