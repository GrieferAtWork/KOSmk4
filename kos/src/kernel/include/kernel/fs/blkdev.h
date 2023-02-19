/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_BLKDEV_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_BLKDEV_H 1

#include <kernel/compiler.h>

#include <kernel/fs/devfs.h>

#include <hybrid/__unaligned.h>
#include <hybrid/sched/atomic-lock.h>

#include <kos/uuid.h>
#include <kos/lockop.h>

#include <libc/string.h>

#ifdef __CC__
DECL_BEGIN

#ifndef REF_IF
#define REF_IF __REF_IF
#endif /* !REF_IF */

/* For block-devices, we simply use the mfile blockshift to encode sector-size.
 * That way, for a block device to  function as expected, only 2 operators  are
 * needed: `mo_loadblocks' and `mo_saveblocks'.
 *
 * With this in mind, block devices are actually _REQUIRED_ to provide these
 * operators (as you can tell by the macros below assuming their  presence).
 *
 * As  such, all block devices are inherently mmap-able, and should user-space
 * open(2)  a block device, they, too, are  able to mmap(2) them _always_! But
 * do  be careful, since the buffers of  files opened within a filesystem that
 * is  mounted on-top  of some given  block-device will _NOT_  be updated when
 * doing something like this. So block device memory access should be reserved
 * for situations where  out-of-band data  is modified (such  as file  control
 * structures), but not the actual file contents.
 *
 * To access the raw data of the block-device you have 2 options:
 *   - mfile_read() / mfile_write()
 *     Pro: alignment doesn't matter, and I/O is buffered (w/ lazy syncing via `fsuper_syncall()')
 *     Con: I/O is buffered and this method should _NOT_ be used to access file data
 *     >> Use this method for accessing out-of-band data (such as directory files)
 *
 *   - blkdev_rdsectors() / blkdev_wrsectors()
 *     Pro: async support (via AIO), direct disk access
 *     Con: alignment  is important;  reads/writes can  only happen  in whole sectors;
 *          must manually check for `MFILE_F_READONLY' before using blkdev_wrsectors()
 *     >> Use this method for accessing file data
 */

struct blkdev;
struct blkdev_ops {
	struct device_ops bdo_dev; /* Device operators */

	/* More operators would go here... */
};


/* Default value for `struct blkdev::bd_max_retry' */
#ifndef BLKDEV_MAX_RETRY_DEFAULT
#define BLKDEV_MAX_RETRY_DEFAULT 2
#endif /* !BLKDEV_MAX_RETRY_DEFAULT */

struct blkdev;
LIST_HEAD(blkdev_list, blkdev);
struct blkdev
#ifndef __WANT_FS_INLINE_STRUCTURES
    : device                     /* Underlying device */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct device        bd_dev; /* Underlying device */
#define _blkdev_asdev(x) &(x)->bd_dev
#define _blkdev_dev_     bd_dev.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _blkdev_asdev(x) x
#define _blkdev_dev_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	union {

		/* Device root information. */
		struct {
			struct atomic_lock      br_partslock;         /* Lock for `br_parts' */
			Toblockop_slist(blkdev) br_partslops;         /* Lock operations for `br_partslock' */
			struct blkdev_list      br_parts;             /* [0..n][lock(br_partslock)] Weak references to sub-partition of this device. */
			unsigned int            br_max_retry;         /* [lock(ATOMIC)] How often to re-attempt I/O, not counting the first attempt. */
			char                    br_ata_serial_no[21]; /* [const] NUL-termianted string (`struct hd_driveid::serial_no', or empty if unknown or N/A) */
			char                    br_ata_fw_rev[9];     /* [const] NUL-termianted string (`struct hd_driveid::fw_rev', or empty if unknown or N/A) */
			char                    br_ata_model[41];     /* [const] NUL-termianted string (`struct hd_driveid::model', or empty if unknown or N/A) */
			byte_t                  br_mbr_diskuid[10];   /* [lock(br_partslock)] MBR disk uid (`struct mbr_sector::mbr_diskuid', or all zeroes if unknown or N/A) */
			uuid_t                  br_efi_uuid;          /* [lock(br_partslock)] EFI disk UUID (`struct efi_descriptor::gpt_uuid', or all zeroes if unknown or N/A) */
		} bd_rootinfo; /* [valid_if(blkdev_isroot(this))] */
#define blkdev_get_mbr_disksig(self) \
	__hybrid_unaligned_get32(&(self)->bd_rootinfo.br_mbr_diskuid[4])

		/* Device partition information. */
		struct {
			REF struct blkdev  *bp_master;        /* [1..1][const] Underlying master device. */
			LIST_ENTRY(blkdev)  bp_partlink;      /* [0..1][lock(bp_master->bd_rootinfo.br_partslock)] Link in list of partitions */
#if __SIZEOF_POS_T__ > __SIZEOF_POINTER__
			void              *_bp_pad;           /* ... */
#endif /* __SIZEOF_POS_T__ > __SIZEOF_POINTER__ */
#ifdef __WANT_BLKDEV_bd_partinfo__bp_blkdevlop
			union {
				struct {
					pos_t       bp_partstart;     /* [const] Starting offset of partition. */
					minor_t     bp_partno;        /* [const] Partition index (position of this part in `bp_master->bd_rootinfo.br_parts') */
					uint8_t     bp_mbr_sysno;     /* [const] MBR system ID (`struct mbr_partition_common::pt_sysid', or `0' if unknown or N/A) */
					char        bp_efi_name[109]; /* [const] NUL-termianted string (`struct efi_partition::p_name', or empty if unknown or N/A) */
					uint8_t     bp_active;        /* [const] Non-zero if this partition is "active" (s.a. `PART_BOOTABLE_ACTICE', `EFI_PART_F_ACTIVE') */
					uint8_t    _bp_pad2;          /* ... */
				};
				Toblockop(blkdev)     _bp_blkdevlop;  /* Used internally during destruction... */
				Tobpostlockop(blkdev) _bp_blkdevplop; /* Used internally during destruction... */
			};
#else /* __WANT_BLKDEV_bd_partinfo__bp_blkdevlop */
			pos_t               bp_partstart;     /* [const] Starting offset of partition. */
			minor_t             bp_partno;        /* [const] Partition index (position of this part in `bp_master->bd_rootinfo.br_parts') */
			uint8_t             bp_mbr_sysno;     /* [const] MBR system ID (`struct mbr_partition_common::pt_sysid', or `0' if unknown or N/A) */
			char                bp_efi_name[109]; /* [const] NUL-termianted string (`struct efi_partition::p_name', or empty if unknown or N/A) */
			uint8_t             bp_active;        /* [const] Non-zero if this partition is "active" (s.a. `PART_BOOTABLE_ACTICE', `EFI_PART_F_ACTIVE') */
			uint8_t            _bp_pad2;          /* ... */
#endif /* !__WANT_BLKDEV_bd_partinfo__bp_blkdevlop */
			uuid_t              bp_efi_typeuuid;  /* [const] EFI part type UUID (`struct efi_partition::p_type_uuid', or all zeroes if unknown or N/A) */
			uuid_t              bp_efi_partuuid;  /* [const] EFI part type UUID (`struct efi_partition::p_part_uuid', or all zeroes if unknown or N/A) */
		} bd_partinfo; /* [valid_if(blkdev_ispart(this))] */

	};
};

/* Operators used for block device partitions */
DATDEF struct blkdev_ops const blkpart_ops;

/* Default operators for block devices */
#define blkdev_v_destroy    device_v_destroy
#define blkdev_v_changed    device_v_changed
#define blkdev_v_wrattr     device_v_wrattr
#define blkdev_v_tryas      device_v_tryas
DATDEF struct mfile_stream_ops const blkdev_v_stream_ops;

/* Implements `BLK*' ioctls from <linux/fs.h> */
FUNDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL
blkdev_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
               USER UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...);

/* Helper macros for `struct blkdev::bd_rootinfo::br_partslock' */
#define _blkdev_root_partslock_reap(self)      _oblockop_reap_atomic_lock(&(self)->bd_rootinfo.br_partslops, &(self)->bd_rootinfo.br_partslock, self)
#define blkdev_root_partslock_reap(self)       oblockop_reap_atomic_lock(&(self)->bd_rootinfo.br_partslops, &(self)->bd_rootinfo.br_partslock, self)
#define blkdev_root_partslock_mustreap(self)   oblockop_mustreap(&(self)->bd_rootinfo.br_partslops)
#define blkdev_root_partslock_tryacquire(self) atomic_lock_tryacquire(&(self)->bd_rootinfo.br_partslock)
#define blkdev_root_partslock_acquire(self)    atomic_lock_acquire(&(self)->bd_rootinfo.br_partslock)
#define blkdev_root_partslock_acquire_nx(self) atomic_lock_acquire_nx(&(self)->bd_rootinfo.br_partslock)
#define _blkdev_root_partslock_release(self)   atomic_lock_release(&(self)->bd_rootinfo.br_partslock)
#define blkdev_root_partslock_release(self)    (atomic_lock_release(&(self)->bd_rootinfo.br_partslock), blkdev_root_partslock_reap(self))
#define blkdev_root_partslock_acquired(self)   atomic_lock_acquired(&(self)->bd_rootinfo.br_partslock)
#define blkdev_root_partslock_available(self)  atomic_lock_available(&(self)->bd_rootinfo.br_partslock)
#define blkdev_root_partslock_waitfor(self)    atomic_lock_waitfor(&(self)->bd_rootinfo.br_partslock)
#define blkdev_root_partslock_waitfor_nx(self) atomic_lock_waitfor_nx(&(self)->bd_rootinfo.br_partslock)


/* Return a pointer to character-device operators of `self' */
#define blkdev_getops(self) \
	((struct blkdev_ops const *)__COMPILER_REQTYPE(struct blkdev const *, self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)

/* Check if `self' is a block-device partition or root. */
#define blkdev_ispart(self) (blkdev_getops(self) == &blkpart_ops)
#define blkdev_isroot(self) (blkdev_getops(self) != &blkpart_ops)

/* Helper macros. */
#define fdevnode_isblkpart(self) ((self)->_fdevnode_node_ _fnode_file_ mf_ops == &blkpart_ops.bdo_dev.do_node.dvno_node.no_file)
#define device_isblkpart(self)   ((self)->_device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops == &blkpart_ops.bdo_dev.do_node.dvno_node.no_file)

/* Return the sector shift/size/count of the block device. */
#define blkdev_getsectorshift(self) ((self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_blockshift)
#define blkdev_getsectorsize(self)  ((size_t)1 << blkdev_getsectorshift(self))
#define blkdev_getsectormask(self)  (blkdev_getsectorsize(self) - 1)
#define blkdev_getsectorcount(self) (_atomic64_val((self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_filesize) >> blkdev_getsectorshift(self))
#define blkdev_getsize(self)        ((pos_t)_atomic64_val((self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_filesize))

#define blkdev_part_getsectormin(self) ((uint64_t)(self)->bd_partinfo.bp_partstart >> blkdev_getsectorshift(self))
#define blkdev_part_getsectormax(self) (blkdev_part_getsectormin(self) + blkdev_getsectorcount(self) - 1)

/* Read/Write whole sectors */
#define blkdev_rdsectors_async(self, addr, buf, num_bytes, aio) \
	((*__COMPILER_REQTYPE(struct blkdev const *, self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops->mo_loadblocks)(_fnode_asfile(_fdevnode_asnode(_device_asdevnode(_blkdev_asdev(self)))), addr, buf, num_bytes, aio))
#define blkdev_wrsectors_async(self, addr, buf, num_bytes, aio) \
	((*__COMPILER_REQTYPE(struct blkdev const *, self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops->mo_saveblocks)(_fnode_asfile(_fdevnode_asnode(_device_asdevnode(_blkdev_asdev(self)))), addr, buf, num_bytes, aio))
#define blkdev_rdsectors(self, addr, buf, num_bytes)                                                                                                  \
	mfile_dosyncio(_fnode_asfile(_fdevnode_asnode(_device_asdevnode(_blkdev_asdev(self)))),                                                           \
	               __COMPILER_REQTYPE(struct blkdev const *, self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops->mo_loadblocks, \
	               addr, buf, num_bytes)
#define blkdev_wrsectors(self, addr, buf, num_bytes)                                                                                                  \
	mfile_dosyncio(_fnode_asfile(_fdevnode_asnode(_device_asdevnode(_blkdev_asdev(self)))),                                                           \
	               __COMPILER_REQTYPE(struct blkdev const *, self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops->mo_saveblocks, \
	               addr, buf, num_bytes)


#define __blkdev_init_common(self, ops)                                                                   \
	(_device_init(_blkdev_asdev(self), &(ops)->bdo_dev),                                                  \
	 (self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags = MFILE_F_FIXEDFILESIZE, \
	 (self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_parts = __NULLPTR,             \
	 SLIST_INIT(&(self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_changed))
#define __blkdev_cinit_common(self, ops)                                                                        \
	(_device_cinit(_blkdev_asdev(self), &(ops)->bdo_dev),                                                       \
	 (self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags = MFILE_F_FIXEDFILESIZE,       \
	 __hybrid_assert((self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_parts == __NULLPTR), \
	 __hybrid_assert(SLIST_EMPTY(&(self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_changed)))
#define __blkdev_fini_common(self) _device_fini(_blkdev_asdev(self))


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_part_amask
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_blockshift
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_iobashift
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_filesize  (to the total device size in bytes)
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes  # s.a. `device_registerf()'
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent    # s.a. `device_registerf()'
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_ino       # s.a. `device_registerf()'
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_mode      # Something or'd with S_IFBLK
 *  - self->_blkdev_dev_ _device_devnode_ dn_devno                     # s.a. `device_registerf()'
 *  - self->_blkdev_dev_ dv_driver                                     # As `incref(drv_self)'
 *  - self->_blkdev_dev_ dv_dirent                                     # s.a. `device_registerf()'
 *  - self->_blkdev_dev_ dv_byname_node                                # s.a. `device_registerf()'
 *  - self->bd_rootinfo.br_ata_serial_no
 *  - self->bd_rootinfo.br_ata_fw_rev
 *  - self->bd_rootinfo.br_ata_model
 * @param: struct blkdev     *self: Block device to initialize.
 * @param: struct blkdev_ops *ops:  Block device operators. */
#define _blkdev_init(self, ops)                                   \
	(__blkdev_init_common(self, ops),                             \
	 atomic_lock_init(&(self)->bd_rootinfo.br_partslock),         \
	 SLIST_INIT(&(self)->bd_rootinfo.br_partslops),               \
	 LIST_INIT(&(self)->bd_rootinfo.br_parts),                    \
	 (self)->bd_rootinfo.br_max_retry = BLKDEV_MAX_RETRY_DEFAULT, \
	 __libc_memset((self)->bd_rootinfo.br_mbr_diskuid, 0,         \
	               sizeof((self)->bd_rootinfo.br_mbr_diskuid)),   \
	 __libc_memset(&(self)->bd_rootinfo.br_efi_uuid, 0, sizeof(uuid_t)))
#define _blkdev_cinit(self, ops)                                      \
	(__blkdev_cinit_common(self, ops),                                \
	 atomic_lock_cinit(&(self)->bd_rootinfo.br_partslock),            \
	 __hybrid_assert(SLIST_EMPTY(&(self)->bd_rootinfo.br_partslops)), \
	 __hybrid_assert(LIST_EMPTY(&(self)->bd_rootinfo.br_parts)),      \
	 (self)->bd_rootinfo.br_max_retry = BLKDEV_MAX_RETRY_DEFAULT)

/* Finalize a partially initialized `struct blkdev' (as initialized by `_blkdev_init()') */
#define _blkdev_fini(self) __blkdev_fini_common(self)



/* Reconstruct/Reload partitions of `self':
 *   - Step #0: If `self' is a partition, return immediately.
 *   - Step #1: Construct new partitions and assign device IDs and names to partitions
 *   - Step #2: Acquire locks to:
 *               - self->bd_rootinfo.br_partslock
 *               - devfs_byname_lock
 *               - devfs.rs_sup.fs_nodeslock
 *               - devfs.rs_dat.rdd_lock  // read-only
 *               - fallnodes_lock
 *   - Step #3: Clear `self->bd_rootinfo.br_parts' and:
 *               - tryincref() every partition. Those for which this
 *                 fails are  immediately discarded  from the  list.
 *              Remove all old partitions from:
 *               - devfs_byname_list
 *               - devfs.rs_sup.fs_nodes
 *               - fallnodes_list
 *               - Also clear `MFILE_FN_GLOBAL_REF' and decref_nokill(partition) if it was set
 *   - Step #4: Register all of the new partitions:
 *               - self->bd_rootinfo.br_parts    -- Sort by partition start offset
 *               - devfs_byname_list             -- If same-named file already exists here (or in `devfs.rs_dat.rdd_tree'),
 *                                                  then simply don't add to the tree, but instead set:
 *                                                  >> `dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED'
 *               - devfs.rs_sup.fs_nodes         -- If another node with the same INO  exists, keep on adding +1 to  the
 *                                                  device's dev_t, before generating a new INO until no more collisions
 *                                                  happen.
 *               - fallnodes_list                -- Also set `MFILE_FN_GLOBAL_REF' for the new partition and incref() it
 *   - Step #5: Release locks from:
 *               - devfs_byname_lock
 *               - devfs.rs_sup.fs_nodeslock
 *               - devfs.rs_dat.rdd_lock  // read-only
 *               - fallnodes_lock
 *   - Step #6: Drop references from all of the old partitions
 *   - Step #7: Release lock to `self->bd_rootinfo.br_partslock' */
FUNDEF BLOCKING NONNULL((1)) void KCALL
blkdev_repart(struct blkdev *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* The  combination of `device_register()' and `blkdev_repart()', but implemented
 * in such a manner that either all of the new devices become visible at the same
 * time, or none of them do (in case of an exception).
 *
 * This prevents race conditions that would arise from the alternative:
 * >> device_register(self);
 * >> TRY {
 * >>     blkdev_repart(self);
 * >> } EXCEPT {
 * >>     // If we get here, `self' was globally visible for a short moment.
 * >>     // This can be prevented by using `blkdev_repart_and_register()'
 * >>     device_delete(self);
 * >>     RETHROW();
 * >> }
 *
 * This function assumes:
 *  - LIST_EMPTY(&self->bd_rootinfo.br_parts)
 *  - blkdev_isroot(self)
 * This function initializes (before making `self' globally visible):
 *  - self->_device_devnode_ _fdevnode_node_ fn_allnodes
 *  - self->_device_devnode_ _fdevnode_node_ fn_supent
 *  - self->dv_byname_node */
FUNDEF BLOCKING NONNULL((1)) void KCALL
blkdev_repart_and_register(struct blkdev *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_BLKDEV_H */
