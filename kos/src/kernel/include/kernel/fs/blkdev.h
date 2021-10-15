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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_BLKDEV_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_BLKDEV_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/devfs.h>

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

	/* TODO: doubly-linked list with weak references to partitions. (always empty for partitions) */
	/* NOTE: block-device partitions can easily be detected via `mf_ops', which points to `blkpart_ops',
	 *       since all block-device partitions can be implemented via a single, common set of operators. */
	unsigned int         bd_max_retry;  /* How often to re-attempt I/O, not counting the first attempt.
	                                     * Set to 0xff to allow infinite retries.
	                                     * TODO: The ATA driver needs to make use of this! */
};

/* Return a pointer to character-device operators of `self' */
#define blkdev_getops(self) \
	((struct blkdev_ops const *)__COMPILER_REQTYPE(struct blkdev const *, self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)

/* Check if `self' is a `struct blkpart' */
#define blkdev_ispart(self) (blkdev_getops(self) == &blkpart_ops)
#define blkdev_aspart(self) ((struct blkpart *)__COMPILER_REQTYPE(struct blkdev *, self))

/* Return the sector shift/size/count of the block device. */
#define blkdev_getsectorshift(self) ((self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_blockshift)
#define blkdev_getsectorsize(self)  ((size_t)1 << blkdev_getsectorshift(self))
#define blkdev_getsectorcount(self) (__atomic64_val((self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_filesize) >> blkdev_getsectorshift(self))

/* Read/Write whole sectors */
#define blkdev_rdsectors(self, addr, buf, num_bytes, aio) \
	((*__COMPILER_REQTYPE(struct blkdev const *, self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops->mo_loadblocks)(_fnode_asfile(_fdevnode_asnode(_device_asdevnode(_blkdev_asdev(self)))), addr, buf, num_bytes, aio))
#define blkdev_wrsectors(self, addr, buf, num_bytes, aio) \
	((*__COMPILER_REQTYPE(struct blkdev const *, self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops->mo_saveblocks)(_fnode_asfile(_fdevnode_asnode(_device_asdevnode(_blkdev_asdev(self)))), addr, buf, num_bytes, aio))


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags  (pre-initialized to `MFILE_F_FIXEDFILESIZE')
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_blockshift
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_part_amask
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_filesize  (to the total device size in bytes)
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_ino  (as `devfs_devnode_makeino(S_IFBLK, dn_devno)')
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_mode (with something or'd with S_IFBLK)
 *  - self->_blkdev_dev_ _device_devnode_ dn_devno
 *  - self->_blkdev_dev_ dv_driver
 *  - self->_blkdev_dev_ dv_dirent
 *  - self->_blkdev_dev_ dv_byname_node
 * @param: struct blkdev     *self: Block device to initialize.
 * @param: struct blkdev_ops *ops:  Block device operators. */
#define _blkdev_init(self, ops)                                                                           \
	(_device_init(_blkdev_asdev(self), &(ops)->bdo_dev),                                                  \
	 (self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags = MFILE_F_FIXEDFILESIZE, \
	 (self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_parts = __NULLPTR,             \
	 (self)->bd_max_retry                                                        = BLKDEV_MAX_RETRY_DEFAULT)
#define _blkdev_cinit(self, ops)                                                                                \
	(_device_cinit(_blkdev_asdev(self), &(ops)->bdo_dev),                                                       \
	 (self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags = MFILE_F_FIXEDFILESIZE,       \
	 __hybrid_assert((self)->_blkdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_parts == __NULLPTR), \
	 (self)->bd_max_retry = BLKDEV_MAX_RETRY_DEFAULT)

/* Finalize a partially initialized `struct blkdev' (as initialized by `_blkdev_init()') */
#define _blkdev_fini(self) _device_fini(_blkdev_asdev(self))


/* >> FUNDEF void KCALL blkdev_repart(struct blkdev *__restrict self);
 * TODO: (also used to implement `')
 *   - Step #0: If `self' is a partition, return immediately.
 *   - Step #1: Assign device IDs and names to partitions (same scheme as the old FS used)
 *   - Step #2: Decode headers and construct new partition objects.
 *   - Step #3: Acquire locks to:
 *               - TODO_PARTITION_INFO_TABLES_LOCK
 *               - self->TODO_PARTITIONS_LIST_LOCK
 *               - devfs_byname_lock
 *               - devfs.rs_sup.fs_nodeslock
 *               - devfs.rs_dat.rdd_treelock
 *               - fallnodes_lock
 *   - Step #4: Clear `self->TODO_PARTITIONS_LIST' and:
 *               - tryincref() every partition. Those for which this
 *                 fails are  immediately discarded  from the  list.
 *              Remove all old partitions from:
 *               - TODO_PARTITION_INFO_TABLES
 *               - devfs_byname_list
 *               - devfs.rs_sup.fs_nodes
 *               - fallnodes_list
 *               - Also clear `MFILE_FN_GLOBAL_REF' and decref_nokill(partition) if it was set
 *   - Step #5: Register all of the new partitions:
 *               - self->TODO_PARTITIONS_LIST    -- Sort by partition start offset
 *               - devfs_byname_list             -- If same-named file already exists here (or in `devfs.rs_dat.rdd_tree'),
 *                                                  then simply don't add to the tree, but instead set:
 *                                                  >> `dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED'
 *               - devfs.rs_sup.fs_nodes         -- If another node with the same INO  exists, keep on adding +1 to  the
 *                                                  device's dev_t, before generating a new INO until no more collisions
 *                                                  happen.
 *               - fallnodes_list                -- Also set `MFILE_FN_GLOBAL_REF' for the new partition and incref() it
 *   - Step #6: Release locks from:
 *               - TODO_PARTITION_INFO_TABLES_LOCK
 *               - self->TODO_PARTITIONS_LIST_LOCK
 *               - devfs_byname_lock
 *               - devfs.rs_sup.fs_nodeslock
 *               - devfs.rs_dat.rdd_treelock
 *               - fallnodes_lock
 *   - Step #7: Drop references from all of the old partitions
 */




/************************************************************************/
/* Block device partition                                               */
/************************************************************************/

struct blkpart
#ifndef __WANT_FS_INLINE_STRUCTURES
    : blkdev                      /* Underlying block-device */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct blkdev         bp_blk; /* Underlying block-device */
#define _blkpart_asblk(x) &(x)->bp_blk
#define _blkpart_blk_     bp_blk.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _blkpart_asblk(x) x
#define _blkpart_blk_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	REF struct blkdev    *bp_master; /* [1..1][const] Underlying master device. */
	/* TODO: Partition info fields. (for all of the by-* global tables)
	 *
	 * Additionally,  each of these should also come with an LLRBTREE_NODE, one
	 * which can be marked as rb_lhs == BLKPART_BYINFO_DELETED to indicate that
	 * the partition has been unlinked from the global info tables. The destroy
	 * operator  of `blkpart_ops' then  checks if global  info tables are still
	 * bound, and if they are, will use lockops to remove itself from them. */
};


/* Operators used for block device partitions */
DATDEF struct blkdev_ops const blkpart_ops;

/* TODO: TODO_PARTITION_INFO_TABLES -- Global tables for partitions.
 * Each of these contains self-clearing-on-destroy pointers to individual partitions:
 *       /dev/disk/by-id/        -- Symlinks for block-devices
 *       /dev/disk/by-label/     -- Symlinks for block-devices
 *       /dev/disk/by-partlabel/ -- Symlinks for block-devices
 *       /dev/disk/by-partuuid/  -- Symlinks for block-devices
 *       /dev/disk/by-path/      -- Symlinks for block-devices
 *       /dev/disk/by-uuid/      -- Symlinks for block-devices
 *
 * On that note, also add support for:
 *       /dev/block/             -- Contains symlinks for the /dev device, such as 8:0 -> ../sda
 *       /dev/char/              -- Contains symlinks for the /dev device, such as 1:1 -> ../mem
 *       /dev/cpu/[id]/cpuid     -- A readable file to access `cpuid' data for a given CPU.
 * All of these should be implemented in `devfs.c' by dynamic means (similar to how /proc/ works)
 * Also  note that unlike the root directory, these special sub-directories are _NOT_ writable on
 * KOS. The files found within cannot be renamed, moved, deleted, etc. and no custom files can be
 * created  either. Only the root directory, and  any dynamically created sub-directory is usable
 * for the purpose of RAMFS.
 *
 * TODO: The  devfs root directory node should have INO=1.  Because we use mask &7 for encoding
 *       different  INO namespaces (&7=0 for RAMFS, and &7=7 for by-name devices), we also need
 *       one more namespace for special directories like root, and another for dynamic files as
 *       those described above!
 *
 * NOTE: All of these special INodes actually _DONT_ appear in `devfs.rs_sup.fs_nodes'! This  can
 *       be achieved because INode access within the new fs is not done via `super_opennode' with
 *       the  associated inode number,  but instead via `fdirent_opennode()',  which hides all of
 *       the association details for fdirent->fnode mapping from prying eyes. Technically, it  is
 *       actually possible to create a filesystem that  _NEVER_ makes use of `fs_nodes', and  the
 *       only  reason why unique inode number ~should~ still be assigned is for the sake of user-
 *       space  and programs that rely on the POSIX-guarantied unique-ness of stat::st_dev:st_ino
 *
 */



DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_BLKDEV_H */
