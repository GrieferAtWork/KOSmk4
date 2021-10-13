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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FSUPER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FSUPER_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/mman/mfile.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-lock.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <asm/os/statvfs.h>
#include <kos/io.h>
#include <kos/lockop.h>

#ifndef REF_IF
#define REF_IF __REF_IF
#endif /* !REF_IF */

#ifdef __CC__
DECL_BEGIN

/* Convert flags:
 *    - MFILE_F_READONLY  -->  ST_RDONLY
 *    - MFILE_FS_NOSUID   -->  ST_NOSUID
 *    - MFILE_FS_NOEXEC   -->  ST_NOEXEC
 *    - MFILE_F_NOATIME   -->  ST_NOATIME */
#if (MFILE_F_READONLY == __ST_RDONLY && \
     MFILE_FS_NOSUID == __ST_NOSUID &&  \
     MFILE_FS_NOEXEC == __ST_NOEXEC &&  \
     MFILE_F_NOATIME == __ST_NOATIME)
#define statvfs_flags_from_mfile_flags(mfile_flags)        \
	((mfile_flags) & (MFILE_F_READONLY | MFILE_FS_NOSUID | \
	                  MFILE_FS_NOEXEC | MFILE_F_NOATIME))
#else /* ... */
#define statvfs_flags_from_mfile_flags(mfile_flags)         \
	((((mfile_flags)&MFILE_F_READONLY) ? __ST_RDONLY : 0) | \
	 (((mfile_flags)&MFILE_FS_NOSUID) ? __ST_NOSUID : 0) |  \
	 (((mfile_flags)&MFILE_FS_NOEXEC) ? __ST_NOEXEC : 0) |  \
	 (((mfile_flags)&MFILE_F_NOATIME) ? __ST_NOATIME : 0))
#endif /* !... */


struct fsuper;
struct statfs;

struct fsuperfeat {
	pos_t   sf_filesize_max;       /* [const] Max possible file size (no `mf_filesize' can ever be larger than this) */
	uid_t   sf_uid_max;            /* [const][valid_if(!:so_validuid)] Max supported UID value (if set, use `so_validuid' to check valid values) */
	gid_t   sf_gid_max;            /* [const][valid_if(!:so_validgid)] Max supported GID value (if set, use `so_validgid' to check valid values) */
	pos_t   sf_symlink_max;        /* [const] Max length of text contained within symbolic links */
	nlink_t sf_link_max;           /* [const] Max # of links a file may have */
	u32     sf_magic;              /* [const] Filesystem ~magic~ (one of the constants from `<linux/magic.h>') */
	u32     sf_rec_incr_xfer_size; /* [const] Buffer size increments for efficient disk transfer operations */
	u32     sf_rec_max_xfer_size;  /* [const] Max buffer size for efficient disk transfer operations */
	u32     sf_rec_min_xfer_size;  /* [const] Min buffer size for efficient disk transfer operations */
	u32     sf_rec_xfer_align;     /* [const] Required in-memory buffer alignment for efficient disk transfer operations */
	u16     sf_name_max;           /* [const] Max # of chars in a file name */
	u8      sf_filesizebits;       /* [const] Max # of bits in a file's size field (usually 64 or 32) */
};
#define fsuperfeat_hassymlink(self) ((self)->sf_symlink_max != 0)
#define fsuperfeat_hashrdlink(self) ((self)->sf_link_max > 1)

struct fdirnode;
struct fdirent;

struct fsuper_ops {
	/* NOTE: filesystem-specific operators (if needed) go here... */

	/* [0..1] Verify that a given uid/gid can be saved on-disk within file attributes.
	 *        When these functions aren't defined, `sf_uid_max' and `sf_gid_max' are
	 *        used for testing if some given uid/gid may be used.
	 * When validation fails (iow: these functions return `false', or when they're not
	 * defined,  some user-given uid/gid  exceeds `sf_uid_max'/`sf_gid_max'), then the
	 * associated system call chown(2) fails with an exception translating to `-EPERM'
	 * for compatibility with linux. On KOS, this exception is:
	 *   - E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_UID:uid
	 *   - E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_GID:gid */
	WUNUSED NONNULL((1)) __BOOL (KCALL *so_validuid)(struct fsuper *__restrict self, uid_t uid) THROWS(...);
	WUNUSED NONNULL((1)) __BOOL (KCALL *so_validgid)(struct fsuper *__restrict self, gid_t gid) THROWS(...);

	/* [0..1] Truncate the given `tms' to the near possible time value which
	 *        can be encoded within filesystem-specific data structure. */
	NONNULL((1, 2)) void (KCALL *so_truncate_atime)(struct fsuper *__restrict self, /*in|out*/ struct timespec *__restrict tms) THROWS(...);
	NONNULL((1, 2)) void (KCALL *so_truncate_mtime)(struct fsuper *__restrict self, /*in|out*/ struct timespec *__restrict tms) THROWS(...);
	NONNULL((1, 2)) void (KCALL *so_truncate_ctime)(struct fsuper *__restrict self, /*in|out*/ struct timespec *__restrict tms) THROWS(...);

	/* [0..1] Flush unwritten changes from fs-specific
	 *        superblock buffers to disk and/or disk buffers */
	ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fnode *
	(KCALL *so_sync)(struct fsuper *__restrict self)
			THROWS(E_IOERROR, ...);

	/* [0..1] Clear filesystem superblock caches */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (KCALL *so_clearcache)(struct fsuper *__restrict self);

	/* [0..1] Gather information about the filesystem.
	 * The caller has already initialized:
	 *   - f_type    (== self->fs_feat.sf_magic)
	 *   - f_bsize   (== 1 << self->fs_root.mf_blockshift)
	 *   - f_blocks  (== fs_dev ? fs_dev->mf_filesize >> self->fs_root.mf_blockshift : 0)
	 *   - f_namelen (== self->fs_feat.sf_name_max)
	 *   - f_frsize  (== 1 << self->fs_root.mf_blockshift)
	 *   - f_flags   (== statvfs_flags_from_mfile_flags(self->fs_root.mf_flags))
	 * This function must initialize:
	 *   - f_bfree
	 *   - f_bavail
	 *   - f_files
	 *   - f_ffree
	 *   - f_fsid */
	NONNULL((1)) void
	(KCALL *so_statfs)(struct fsuper *__restrict self,
	                        USER CHECKED struct statfs *result)
			THROWS(E_IOERROR, E_SEGFAULT, ...);

	struct fdirnode_ops so_fdir; /* FDirNode operators */

	/* NOTE: root-directory-type-specific operators go here... */
};


#ifndef __fnode_list_defined
#define __fnode_list_defined
LIST_HEAD(fnode_list, fnode);
#endif /* !__fnode_list_defined */

/* Special  value  for `struct fsuper::fs_changednodes'.  When set,
 * further changed parts are no  longer traced, and `fnode'-s  will
 * no  longer  be added  to the  changed-node  list. This  value is
 * assigned  as  part of  unmounting  a superblock,  which  is also
 * includes deleting all files still opened within the superblock's
 * node-tree,  thus also  causing all  loaded files  to be deleted. */
#define FSUPER_NODES_DELETED ((struct fnode *)-1)

struct vmount; /* Mounting point descriptor. */
#ifndef __vmount_list_defined
#define __vmount_list_defined
LIST_HEAD(vmount_list, vmount);
#endif /* !__vmount_list_defined */


struct fsuper {
	/* More fields of custom (fs-specific) `fsuper' sub-classes go here. */
	REF_IF([*].mf_flags & MFILE_F_PERSISTENT)
	LLRBTREE_ROOT(fnode)        fs_nodes;         /* [0..n][lock(fs_nodeslock)] Tree of  known nodes (ordered  by INO  number)
	                                               * This tree holds a reference to any file that has the `MFILE_F_PERSISTENT'
	                                               * flag set. When set to  `FSUPER_NODES_DELETED', no further file-nodes  can
	                                               * be added. */
	struct atomic_rwlock        fs_nodeslock;     /* Lock for `fs_nodes' */
	Toblockop_slist(fsuper)     fs_nodeslockops;  /* [lock(ATOMIC)] Pending lock-operations for `fs_nodeslock' */
	struct vmount_list          fs_mounts;        /* [0..n][lock(fs_mountslock)]  List of mounting points of this superblock.
	                                               * When this list becomes empty, `fsuper_delete()' is automatically called. */
	struct atomic_rwlock        fs_mountslock;    /* Lock for `fs_mounts' */
	Toblockop_slist(fsuper)     fs_mountslockops; /* [lock(ATOMIC)] Pending lock-operations for `fs_mountslock' */
	REF struct ffilesys        *fs_sys;           /* [1..1][const] fs-descriptor of this superblock. */
	REF struct blkdev          *fs_dev;           /* [0..1][const] Underlying block-device. (if any) */
	struct fsuperfeat           fs_feat;          /* [const] Filesystem features. */
	struct atomic_lock          fs_changednodes_lock; /* Lock for `fs_changednodes' */
	Toblockop_slist(fsuper)     fs_changednodes_lops; /* Lock operators for `fs_changednodes_lock' */
	struct REF fnode_list       fs_changednodes;  /* [0..n][lock(fs_changednodes_lock)][const_if(FSUPER_NODES_DELETED)]
	                                               * List  of   changed   node   (set  to   DELETED   during   unmount)
	                                               * Note  that   for  ramfs   filesystems,  this   list  will   always
	                                               * be  marked  as   DELETED,  in  order   to  prevent  the   tracking
	                                               * of  changed  files,  since  there'd   be  no  point  in   tracking
	                                               * them if one can't write them do any backing storage! */
#ifdef __WANT_FSUPER__fs_changedsuper_lop
	union {
		LIST_ENTRY(REF fsuper)  fs_changedsuper;  /* [0..1][lock(fchangedsuper_lock)] Entry in the list of changed superblocks. */
		struct lockop          _fs_changedsuper_lop; /* Used internally... */
	};
#else /* __WANT_FSUPER__fs_changedsuper_lop */
	LIST_ENTRY(REF fsuper)      fs_changedsuper;  /* [0..1][lock(fchangedsuper_lock)] Entry in the list of changed superblocks. */
#endif /* !__WANT_FSUPER__fs_changedsuper_lop */

	struct fdirnode             fs_root;          /* Filesystem root. NOTE: The `mf_flags' field of this
	                                               * struct also contains all of the `MFILE_FS_*' flags. */
	/* More fields of custom `fdirnode' sub-classes go here. */
};

/* Helper function to asynchronously add a given super-block to the list of changed superblocks.
 * @return: true:  Superblock was added to the changed list, or will be added asynchronously.
 * @return: false: Superblock was already added to the changed list, or a async request to
 *                 perform the addition has already been enqueued. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL fsuper_add2changed)(struct fsuper *__restrict self);

/* Check if `self' is part of the list of changed superblocks, or is being added to it asynchronously. */
#define fsuper_haschanged(self) (__hybrid_atomic_load((self)->fs_changedsuper.le_prev, __ATOMIC_ACQUIRE) != __NULLPTR)



/* Return a pointer to superblock-node operators of `self' */
#define fsuper_getops(self)                                                                                               \
	__COMPILER_CONTAINER_OF(__COMPILER_REQTYPE(struct fsuper const *, self)->fs_root._fdirnode_node_ _fnode_file_ mf_ops, \
	                        struct fsuper_ops, so_fdir.dno_node.no_file)
#define _fsuper_assert_ops_(ops) \
	_fnode_assert_ops_(&(ops)->so_fdir.dno_node)


/* Check if a given uid/gid can be encoded by the filesystem `self' */
#define fsuper_validuid(self, uid)                                                     \
	(fsuper_getops(self)->so_validuid ? (*fsuper_getops(self)->so_validuid)(self, uid) \
	                                  : (uid) <= (self)->fs_feat.sf_uid_max)
#define fsuper_validgid(self, gid)                                                     \
	(fsuper_getops(self)->so_validgid ? (*fsuper_getops(self)->so_validgid)(self, gid) \
	                                  : (gid) <= (self)->fs_feat.sf_gid_max)

/* Truncate the given `tms' to the near possible time value which
 * can be  encoded  within  filesystem-specific  data  structure. */
#define fsuper_truncate_atime(self, tms) \
	(void)(fsuper_getops(self)->so_truncate_atime && ((*fsuper_getops(self)->so_truncate_atime)(self, tms), 0))
#define fsuper_truncate_mtime(self, tms) \
	(void)(fsuper_getops(self)->so_truncate_mtime && ((*fsuper_getops(self)->so_truncate_mtime)(self, tms), 0))
#define fsuper_truncate_ctime(self, tms) \
	(void)(fsuper_getops(self)->so_truncate_ctime && ((*fsuper_getops(self)->so_truncate_ctime)(self, tms), 0))




/* Initialize common+basic fields. The caller must still initialize:
 *  - self->fs_dev
 *  - self->fs_feat.sf_filesize_max
 *  - self->fs_feat.sf_symlink_max
 *  - self->fs_feat.sf_link_max
 *  - self->fs_feat.sf_magic
 *  - self->fs_feat.sf_rec_incr_xfer_size
 *  - self->fs_feat.sf_rec_max_xfer_size
 *  - self->fs_feat.sf_rec_min_xfer_size
 *  - self->fs_feat.sf_rec_xfer_align
 *  - self->fs_feat.sf_name_max
 *  - self->fs_feat.sf_filesizebits
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_flags:
 *     - Initialized to `MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE'
 *       may need to be altered as appropriate.
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_atime
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_mtime
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_ctime
 *  - self->fs_root._fdirnode_node_ fn_uid
 *  - self->fs_root._fdirnode_node_ fn_gid
 *  - self->fs_root._fdirnode_node_ fn_mode (with something or'd with S_IFDIR)
 *  - self->fs_root._fdirnode_node_ fn_ino
 *  - self->fs_root._fdirnode_node_ fn_allnodes
 * @param: struct fsuper     *self: Directory node to initialize.
 * @param: struct fsuper_ops *ops:  Directory operators.
 * @param: struct ffilesys   *fsys: File system information. */
#define _fdirnode_init(self, ops, fsys)                                                           \
	(_fsuper_assert_ops_(ops) /**/                                                                \
	 ((self)->fs_nodes = _fdirnode_asnode(&(self)->fs_root)),                                     \
	 atomic_rwlock_init(&(self)->fs_nodeslock),                                                   \
	 SLIST_INIT(&(self)->fs_nodeslockops),                                                        \
	 LIST_INIT(&(self)->fs_mounts),                                                               \
	 atomic_rwlock_init(&(self)->fs_mountslock),                                                  \
	 SLIST_INIT(&(self)->fs_mountslockops),                                                       \
	 (self)->fs_sys = incref(fsys),                                                               \
	 atomic_lock_init(&(self)->fs_changednodes_lock),                                             \
	 SLIST_INIT(&(self)->fs_changednodes_lops),                                                   \
	 LIST_INIT(&(self)->fs_changednodes),                                                         \
	 LIST_ENTRY_UNBOUND_INIT(&(self)->fs_changedsuper),                                           \
	 _fnode_init_common(_fdirnode_asnode(&(self)->fs_root)),                                      \
	 (self)->fs_root._fdirnode_node_ _fnode_file_ mf_parts    = MFILE_PARTS_ANONYMOUS,            \
	 (self)->fs_root._fdirnode_node_ _fnode_file_ mf_flags    = (MFILE_F_NOUSRMMAP |              \
	                                                             MFILE_F_NOUSRIO |                \
	                                                             MFILE_F_FIXEDFILESIZE),          \
	 (self)->fs_root._fdirnode_node_ _fnode_file_ mf_ops      = &(ops)->so_fdir.dno_node.no_file, \
	 (self)->fs_root._fdirnode_node_ _fnode_file_ mf_filesize = (pos_t)-1,                        \
	 (self)->fs_root._fdirnode_node_ fn_nlink                 = 1,                                \
	 (self)->fs_root._fdirnode_node_ fn_super                 = (self),                           \
	 (self)->fs_root._fdirnode_node_ fn_supent.rb_lhs         = __NULLPTR,                        \
	 (self)->fs_root._fdirnode_node_ fn_supent.rb_rhs         = __NULLPTR,                        \
	 (self)->fs_root.dn_parent                                = __NULLPTR)
#define _fdirnode_cinit(self, ops, fsys)                                                          \
	(_fsuper_assert_ops_(ops) /**/                                                                \
	 ((self)->fs_nodes = _fdirnode_asnode(&(self)->fs_root)),                                     \
	 atomic_rwlock_cinit(&(self)->fs_nodeslock),                                                  \
	 __hybrid_assert(SLIST_EMPTY(&(self)->fs_nodeslockops)),                                      \
	 __hybrid_assert(LIST_EMPTY(&(self)->fs_mounts)),                                             \
	 atomic_rwlock_cinit(&(self)->fs_mountslock),                                                 \
	 __hybrid_assert(SLIST_EMPTY(&(self)->fs_mountslockops)),                                     \
	 (self)->fs_sys = incref(fsys),                                                               \
	 atomic_lock_cinit(&(self)->fs_changednodes_lock),                                            \
	 __hybrid_assert(SLIST_EMPTY(&(self)->fs_changednodes_lops)),                                 \
	 __hybrid_assert(LIST_EMPTY(&(self)->fs_changednodes)),                                       \
	 LIST_ENTRY_UNBOUND_INIT(&(self)->fs_changedsuper),                                           \
	 _fnode_cinit_common(_fdirnode_asnode(&(self)->fs_root)),                                     \
	 (self)->fs_root._fdirnode_node_ _fnode_file_ mf_parts    = MFILE_PARTS_ANONYMOUS,            \
	 (self)->fs_root._fdirnode_node_ _fnode_file_ mf_flags    = (MFILE_F_NOUSRMMAP |              \
	                                                             MFILE_F_NOUSRIO |                \
	                                                             MFILE_F_FIXEDFILESIZE),          \
	 (self)->fs_root._fdirnode_node_ _fnode_file_ mf_ops      = &(ops)->so_fdir.dno_node.no_file, \
	 (self)->fs_root._fdirnode_node_ _fnode_file_ mf_filesize = (pos_t)-1,                        \
	 (self)->fs_root._fdirnode_node_ fn_nlink                 = 1,                                \
	 (self)->fs_root._fdirnode_node_ fn_super                 = (self),                           \
	 __hybrid_assert((self)->fs_root._fdirnode_node_ fn_supent.rb_lhs == __NULLPTR),              \
	 __hybrid_assert((self)->fs_root._fdirnode_node_ fn_supent.rb_rhs == __NULLPTR),              \
	 __hybrid_assert((self)->fs_root.dn_parent == __NULLPTR))

/* Finalize a partially initialized `struct fsuper' (as initialized by `_fdirnode_init()') */
#define _fsuper_fini(self) \
	(decref_nokill((self)->fs_sys))

/* Superblock feature helper macros */
#define fsuper_hassymlink(self) fsuperfeat_hassymlink(&(self)->fs_feat)
#define fsuper_hashrdlink(self) fsuperfeat_hashrdlink(&(self)->fs_feat)


/* Helper macros for `struct fsuper::fs_changednodes_lock' */
#define _fsuper_changednodes_reap(self)           _oblockop_reap_atomic_lock(&(self)->fs_changednodes_lops, &(self)->fs_changednodes_lock, self)
#define fsuper_changednodes_reap(self)            oblockop_reap_atomic_lock(&(self)->fs_changednodes_lops, &(self)->fs_changednodes_lock, self)
#define fsuper_changednodes_mustreap(self)        oblockop_mustreap(&(self)->fs_changednodes_lops)
#define fsuper_changednodes_lock_tryacquire(self) atomic_lock_tryacquire(&(self)->fs_changednodes_lock)
#define fsuper_changednodes_lock_acquire(self)    atomic_lock_acquire(&(self)->fs_changednodes_lock)
#define fsuper_changednodes_lock_acquire_nx(self) atomic_lock_acquire_nx(&(self)->fs_changednodes_lock)
#define _fsuper_changednodes_lock_release(self)   atomic_lock_release(&(self)->fs_changednodes_lock)
#define fsuper_changednodes_lock_release(self)    (atomic_lock_release(&(self)->fs_changednodes_lock), fsuper_changednodes_reap(self))
#define fsuper_changednodes_lock_acquired(self)   atomic_lock_acquired(&(self)->fs_changednodes_lock)
#define fsuper_changednodes_lock_available(self)  atomic_lock_available(&(self)->fs_changednodes_lock)

/* Helper macros for `struct fsuper::fs_nodeslock' */
#define fsuper_nodeslock_mustreap(self)   oblockop_mustreap(&(self)->fs_nodeslockops)
#define fsuper_nodeslock_reap(self)       oblockop_reap_atomic_rwlock(&(self)->fs_nodeslockops, &(self)->fs_nodeslock, self)
#define _fsuper_nodeslock_reap(self)      _oblockop_reap_atomic_rwlock(&(self)->fs_nodeslockops, &(self)->fs_nodeslock, self)
#define fsuper_nodeslock_write(self)      atomic_rwlock_write(&(self)->fs_nodeslock)
#define fsuper_nodeslock_write_nx(self)   atomic_rwlock_write_nx(&(self)->fs_nodeslock)
#define fsuper_nodeslock_trywrite(self)   atomic_rwlock_trywrite(&(self)->fs_nodeslock)
#define fsuper_nodeslock_endwrite(self)   (atomic_rwlock_endwrite(&(self)->fs_nodeslock), fsuper_nodeslock_reap(self))
#define _fsuper_nodeslock_endwrite(self)  atomic_rwlock_endwrite(&(self)->fs_nodeslock)
#define fsuper_nodeslock_read(self)       atomic_rwlock_read(&(self)->fs_nodeslock)
#define fsuper_nodeslock_read_nx(self)    atomic_rwlock_read_nx(&(self)->fs_nodeslock)
#define fsuper_nodeslock_tryread(self)    atomic_rwlock_tryread(&(self)->fs_nodeslock)
#define _fsuper_nodeslock_endread(self)   atomic_rwlock_endread(&(self)->fs_nodeslock)
#define fsuper_nodeslock_endread(self)    (void)(atomic_rwlock_endread(&(self)->fs_nodeslock) && (fsuper_nodeslock_reap(self), 0))
#define _fsuper_nodeslock_end(self)       atomic_rwlock_end(&(self)->fs_nodeslock)
#define fsuper_nodeslock_end(self)        (void)(atomic_rwlock_end(&(self)->fs_nodeslock) && (fsuper_nodeslock_reap(self), 0))
#define fsuper_nodeslock_upgrade(self)    atomic_rwlock_upgrade(&(self)->fs_nodeslock)
#define fsuper_nodeslock_upgrade_nx(self) atomic_rwlock_upgrade_nx(&(self)->fs_nodeslock)
#define fsuper_nodeslock_tryupgrade(self) atomic_rwlock_tryupgrade(&(self)->fs_nodeslock)
#define fsuper_nodeslock_downgrade(self)  atomic_rwlock_downgrade(&(self)->fs_nodeslock)
#define fsuper_nodeslock_reading(self)    atomic_rwlock_reading(&(self)->fs_nodeslock)
#define fsuper_nodeslock_writing(self)    atomic_rwlock_writing(&(self)->fs_nodeslock)
#define fsuper_nodeslock_canread(self)    atomic_rwlock_canread(&(self)->fs_nodeslock)
#define fsuper_nodeslock_canwrite(self)   atomic_rwlock_canwrite(&(self)->fs_nodeslock)

/* Helper macros for `struct fsuper::fs_mountslock' */
#define fsuper_mountslock_mustreap(self)   oblockop_mustreap(&(self)->fs_mountslockops)
#define fsuper_mountslock_reap(self)       oblockop_reap_atomic_rwlock(&(self)->fs_mountslockops, &(self)->fs_mountslock, self)
#define _fsuper_mountslock_reap(self)      _oblockop_reap_atomic_rwlock(&(self)->fs_mountslockops, &(self)->fs_mountslock, self)
#define fsuper_mountslock_write(self)      atomic_rwlock_write(&(self)->fs_mountslock)
#define fsuper_mountslock_write_nx(self)   atomic_rwlock_write_nx(&(self)->fs_mountslock)
#define fsuper_mountslock_trywrite(self)   atomic_rwlock_trywrite(&(self)->fs_mountslock)
#define fsuper_mountslock_endwrite(self)   (atomic_rwlock_endwrite(&(self)->fs_mountslock), fsuper_mountslock_reap(self))
#define _fsuper_mountslock_endwrite(self)  atomic_rwlock_endwrite(&(self)->fs_mountslock)
#define fsuper_mountslock_read(self)       atomic_rwlock_read(&(self)->fs_mountslock)
#define fsuper_mountslock_read_nx(self)    atomic_rwlock_read_nx(&(self)->fs_mountslock)
#define fsuper_mountslock_tryread(self)    atomic_rwlock_tryread(&(self)->fs_mountslock)
#define _fsuper_mountslock_endread(self)   atomic_rwlock_endread(&(self)->fs_mountslock)
#define fsuper_mountslock_endread(self)    (void)(atomic_rwlock_endread(&(self)->fs_mountslock) && (fsuper_mountslock_reap(self), 0))
#define _fsuper_mountslock_end(self)       atomic_rwlock_end(&(self)->fs_mountslock)
#define fsuper_mountslock_end(self)        (void)(atomic_rwlock_end(&(self)->fs_mountslock) && (fsuper_mountslock_reap(self), 0))
#define fsuper_mountslock_upgrade(self)    atomic_rwlock_upgrade(&(self)->fs_mountslock)
#define fsuper_mountslock_upgrade_nx(self) atomic_rwlock_upgrade_nx(&(self)->fs_mountslock)
#define fsuper_mountslock_tryupgrade(self) atomic_rwlock_tryupgrade(&(self)->fs_mountslock)
#define fsuper_mountslock_downgrade(self)  atomic_rwlock_downgrade(&(self)->fs_mountslock)
#define fsuper_mountslock_reading(self)    atomic_rwlock_reading(&(self)->fs_mountslock)
#define fsuper_mountslock_writing(self)    atomic_rwlock_writing(&(self)->fs_mountslock)
#define fsuper_mountslock_canread(self)    atomic_rwlock_canread(&(self)->fs_mountslock)
#define fsuper_mountslock_canwrite(self)   atomic_rwlock_canwrite(&(self)->fs_mountslock)


/* Filenode tree operations. (caller must be holding a lock to `self->fs_nodeslock') */
#define fsuper_nodes_locate(self, ino)      fnode_tree_locate((self)->fs_nodes, ino)
#define fsuper_nodes_insert(self, node)     fnode_tree_insert(&(self)->fs_nodes, node)
#define fsuper_nodes_remove(self, ino)      fnode_tree_remove(&(self)->fs_nodes, ino)
#define fsuper_nodes_removenode(self, node) fnode_tree_removenode(&(self)->fs_nodes, node)


/* Reference count control simply uses `fs_root' as basis.
 * Note that fields of `struct fsuper' grow upwards so that custom sub-classes of `fdirnode'
 * can  simply be used in order to implement `fs_root', allowing for binary compatibility in
 * terms of fsuper field offsets between all possible variants. */
#define fsuper_destroy(self) mfile_destroy(_fnode_asfile(_fdirnode_asnode(&(self)->fs_root)))
DEFINE_REFCOUNT_FUNCTIONS(struct fsuper, fs_root._fdirnode_node_ _fnode_file_ mf_refcnt, fsuper_destroy)


/* Default operators for `struct fsuper_ops' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fsuper_v_destroy)(struct mfile *__restrict self);



/* #1: Remove `self' from the list of changed superblocks (if not done already)
 * #2: Write modified data and attributes of all changed fnode-s to disk.
 * #3: Invoke the `so_sync' operator (if defined)
 * If an exception is thrown during step #2 or #3, re-add `self' to the list of changed superblocks */
FUNDEF NONNULL((1)) void KCALL
fsuper_sync(struct fsuper *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...);

/* Synchronize all superblocks containing changed fnode-s (s.a. `fchangedsuper_list') */
FUNDEF void KCALL fsuper_syncall(void)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...);




/* Mark `self' as deleted (should be called when all
 * mounting  points  using `self'  have  gone away):
 *  - For all nodes in `self->fs_nodes':
 *    - Call `mfile_delete()'
 *    - Clear the `MFILE_F_PERSISTENT' and `MFILE_FN_GLOBAL_REF' flags
 *    - Remove the fnode from the global list of file-nodes
 *  - Mark the `fs_nodes' and `fs_changednodes' as `FSUPER_NODES_DELETED',
 *    and  drop  references from  all  changed files  that  were captured.
 * Note that the caller should first invoke `fsuper_sync()' to ensure
 * that any unwritten changes are written to disk.
 *
 * Anything from the above that couldn't be done via synchronously via
 * non-blocking operations will  instead be completed  asynchronously,
 * meaning that the caller should let the superblock cleanup itself as
 * required locks become available... */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fsuper_delete)(struct fsuper *__restrict self);




DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FSUPER_H */
