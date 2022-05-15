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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FSUPER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FSUPER_H 1

#include <kernel/compiler.h>

#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/mman/mfile.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-lock.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <asm/os/statvfs.h>
#include <kos/lockop.h>
#include <linux/fs.h> /* FSLABEL_MAX */

#ifndef REF_IF
#define REF_IF __REF_IF
#endif /* !REF_IF */

#ifdef __CC__
DECL_BEGIN

/* Convert flags:
 *    - MFILE_F_READONLY    --> ST_RDONLY
 *    - MFILE_FS_NOSUID     --> ST_NOSUID
 *    - MFILE_FS_NOEXEC     --> ST_NOEXEC
 *    - MFILE_F_NOATIME     --> ST_NOATIME
 *    - MFILE_FN_NODIRATIME --> ST_NODIRATIME
 *    - MFILE_F_RELATIME    --> ST_RELATIME */
#if (MFILE_F_READONLY == __ST_RDONLY &&        \
     MFILE_FS_NOSUID == __ST_NOSUID &&         \
     MFILE_FS_NOEXEC == __ST_NOEXEC &&         \
     MFILE_F_NOATIME == __ST_NOATIME &&        \
     MFILE_FN_NODIRATIME == __ST_NODIRATIME && \
     MFILE_F_RELATIME == __ST_RELATIME)
#define statvfs_flags_from_mfile_flags(mfile_flags)        \
	((mfile_flags) & (MFILE_F_READONLY | MFILE_FS_NOSUID | \
	                  MFILE_FS_NOEXEC | MFILE_F_NOATIME |  \
	                  MFILE_FN_NODIRATIME | MFILE_F_RELATIME))
#elif (MFILE_F_READONLY == __ST_RDONLY && \
       MFILE_FS_NOSUID == __ST_NOSUID &&  \
       MFILE_FS_NOEXEC == __ST_NOEXEC &&  \
       MFILE_F_NOATIME == __ST_NOATIME && \
       MFILE_FN_NODIRATIME == __ST_NODIRATIME)
#define statvfs_flags_from_mfile_flags(mfile_flags)         \
	(((mfile_flags) & (MFILE_F_READONLY | MFILE_FS_NOSUID | \
	                   MFILE_FS_NOEXEC | MFILE_F_NOATIME |  \
	                   MFILE_FN_NODIRATIME)) |              \
	 ((mfile_flags)&MFILE_F_RELATIME ? __ST_RELATIME : 0))
#else /* ... */
#define statvfs_flags_from_mfile_flags(mfile_flags)                \
	((((mfile_flags)&MFILE_F_READONLY) ? __ST_RDONLY : 0) |        \
	 (((mfile_flags)&MFILE_FS_NOSUID) ? __ST_NOSUID : 0) |         \
	 (((mfile_flags)&MFILE_FS_NOEXEC) ? __ST_NOEXEC : 0) |         \
	 (((mfile_flags)&MFILE_F_NOATIME) ? __ST_NOATIME : 0) |        \
	 (((mfile_flags)&MFILE_FN_NODIRATIME) ? __ST_NODIRATIME : 0) | \
	 (((mfile_flags)&MFILE_F_RELATIME) ? __ST_RELATIME : 0))
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
	u32     sf_rec_incr_xfer_size; /* [const] Buffer size increments for efficient disk transfer operations (Usually: `(u32)mfile_getblocksize(&fs_root)') */
	u32     sf_rec_max_xfer_size;  /* [const] Max buffer size for efficient disk transfer operations (Usually: `(u32)mfile_getblocksize(&fs_root)') */
	u32     sf_rec_min_xfer_size;  /* [const] Min buffer size for efficient disk transfer operations (Usually: `(u32)mfile_getblocksize(&fs_root)') */
	u32     sf_rec_xfer_align;     /* [const] Required in-memory buffer alignment for efficient disk transfer operations (Usually: `(u32)1 << mf_iobashift') */
	u16     sf_name_max;           /* [const] Max # of chars in a file name */
	shift_t sf_filesizebits;       /* [const] Max # of bits in a file's size field (usually 64 or 32) */
};
#define fsuperfeat_hassymlink(self) ((self)->sf_symlink_max != 0)
#define fsuperfeat_hashrdlink(self) ((self)->sf_link_max > 1)

struct fdirnode;
struct fdirent;

struct fsuper_ops {
	/* NOTE: filesystem-specific operators (if needed) go here... */

	/* [0..1] Get volume label. writing it as a NUL-terminated string to `buf'
	 * When not implemented by singleton filesystems, the filesystem type name
	 * will be returned during a user-space query.
	 * @return: true:  Successfully retrieved the label
	 * @return: false: This volume doesn't have a label (same as not implementing
	 *                 this  operator, except that the special singleton handling
	 *                 is skipped as well) */
	BLOCKING WUNUSED NONNULL((1)) __BOOL
	(KCALL *so_getlabel)(struct fsuper *__restrict self,
	                     USER CHECKED char buf[FSLABEL_MAX])
			THROWS(E_IOERROR, E_SEGFAULT, ...);

	/* [0..1] Set volume label, directly writing the new value to disk.
	 * @return: true:  Successfully saved the label
	 * @return: false: This volume doesn't have a label (same as not implementing this operator)
	 * @throws: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_FSLABEL_TOO_LONG:namelen: [...] */
	BLOCKING WUNUSED NONNULL((1)) __BOOL
	(KCALL *so_setlabel)(struct fsuper *__restrict self,
	                     USER CHECKED char const *name, size_t namelen)
			THROWS(E_IOERROR, E_FSERROR_READONLY, E_SEGFAULT,
			       E_INVALID_ARGUMENT_BAD_VALUE, ...);

	/* [0..1] Verify that a given uid/gid can be saved on-disk within file attributes.
	 *        When these functions aren't defined, `sf_uid_max' and `sf_gid_max' are
	 *        used for testing if some given uid/gid may be used.
	 * When validation fails (iow: these functions return `false', or when they're not
	 * defined,  some user-given uid/gid  exceeds `sf_uid_max'/`sf_gid_max'), then the
	 * associated system call chown(2) fails with an exception translating to `-EPERM'
	 * for compatibility with linux. On KOS, this exception is:
	 *   - E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_UID:uid
	 *   - E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CHOWN_UNSUPP_GID:gid */
	BLOCKING WUNUSED NONNULL((1)) __BOOL (KCALL *so_validuid)(struct fsuper *__restrict self, uid_t uid) THROWS(...);
	BLOCKING WUNUSED NONNULL((1)) __BOOL (KCALL *so_validgid)(struct fsuper *__restrict self, gid_t gid) THROWS(...);

	/* [0..1] Truncate the given `tms' to the near possible time value which
	 *        can be encoded within filesystem-specific data structure. */
	BLOCKING NONNULL((1, 2)) void (KCALL *so_truncate_atime)(struct fsuper *__restrict self, /*in|out*/ struct timespec *__restrict tms) THROWS(...);
	BLOCKING NONNULL((1, 2)) void (KCALL *so_truncate_mtime)(struct fsuper *__restrict self, /*in|out*/ struct timespec *__restrict tms) THROWS(...);
	BLOCKING NONNULL((1, 2)) void (KCALL *so_truncate_ctime)(struct fsuper *__restrict self, /*in|out*/ struct timespec *__restrict tms) THROWS(...);
	BLOCKING NONNULL((1, 2)) void (KCALL *so_truncate_btime)(struct fsuper *__restrict self, /*in|out*/ struct timespec *__restrict tms) THROWS(...);

	/* [0..1] Flush unwritten changes from fs-specific
	 *        superblock buffers to disk and/or disk buffers */
	BLOCKING NONNULL((1)) void
	(KCALL *so_sync)(struct fsuper *__restrict self)
			THROWS(E_IOERROR, ...);

	/* [0..1] Gather information about the filesystem.
	 * The caller has already initialized:
	 *   - f_type    = self->fs_feat.sf_magic;
	 *   - f_bsize   = mfile_getblocksize(&self->fs_root);
	 *   - f_blocks  = fs_dev ? fs_dev->mf_filesize >> self->fs_root.mf_blockshift : 0;
	 *   - f_namelen = self->fs_feat.sf_name_max;
	 *   - f_frsize  = mfile_getblocksize(&self->fs_root);
	 *   - f_flags   = statvfs_flags_from_mfile_flags(self->fs_root.mf_flags);
	 * This function must initialize:
	 *   - f_bfree
	 *   - f_bavail
	 *   - f_files
	 *   - f_ffree
	 *   - f_fsid */
	BLOCKING NONNULL((1)) void
	(KCALL *so_statfs)(struct fsuper *__restrict self,
	                   USER CHECKED struct statfs *result)
			THROWS(E_SEGFAULT, E_IOERROR, ...);

	/* [0..1]
	 * Called to perform additional fs-specific tasks to facilitate a safe unmount operation.
	 * If  defined, this operator is called in place of `mfile_delete_impl()' at the end of a
	 * call  to `fsuper_delete()', and must in turn complete by calling `mfile_delete_impl()'
	 * itself.
	 *
	 * In practice, this operator is used by `ramfs_super' to recursively delete files from
	 * all reachable directories,  resolving the super->dir->dirent->file->super  reference
	 * loop  that is normally used to prevent ramfs  files from being deleted the second no
	 * one is explicitly referencing them anymore. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (KCALL *so_delete)(REF struct fsuper *__restrict self);

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

struct pathmount; /* Mounting point descriptor. */
#ifndef __pathmount_list_defined
#define __pathmount_list_defined
LIST_HEAD(pathmount_list, pathmount);
#endif /* !__pathmount_list_defined */


struct fsuper {
	/* More fields of custom (fs-specific) `fsuper' sub-classes go here. */
	LLRBTREE_ROOT(fnode)        fs_nodes;         /* [0..n][lock(fs_nodeslock)] Tree of known nodes (ordered by INO  number)
	                                               * When set to `FSUPER_NODES_DELETED', no further file-nodes can be added. */
	struct atomic_rwlock        fs_nodeslock;     /* Lock for `fs_nodes' */
	Toblockop_slist(fsuper)     fs_nodeslockops;  /* [lock(ATOMIC)] Pending lock-operations for `fs_nodeslock' */
	struct pathmount_list       fs_mounts;        /* [0..n][lock(fs_mountslock)]  List of mounting points of this superblock.
	                                               * When this list becomes empty, set to `FSUPER_MOUNTS_DELETED' followed by
	                                               * `fsuper_delete()' being called.
	                                               * NOTE: Each of these is also holding another reference to `fs_sys->ffs_drv'! */
#define FSUPER_MOUNTS_DELETED ((struct pathmount *)-1) /* Marker for deleted mounting point list */
	struct atomic_rwlock        fs_mountslock;    /* Lock for `fs_mounts' */
	Toblockop_slist(fsuper)     fs_mountslockops; /* [lock(ATOMIC)] Pending lock-operations for `fs_mountslock' */
	REF struct ffilesys        *fs_sys;           /* [1..1][const] fs-descriptor of this superblock. */
	REF struct mfile           *fs_dev;           /* [0..1][const] Underlying block-device (if any). When non-NULL, this field also
	                                               * holds a reference to `mf_trunclock' in order to prevent the backing file  from
	                                               * being truncated. */
	/* [1..1][const][valid_if(fs_dev != NULL)] Load-/save-blocks operators for `fs_dev'.
	 * These operators are set such that they require alignment constraints as  required
	 * by the filesystem  itself, and map  to the  operators of `fs_dev'  such that  its
	 * constraints aren't violated either.
	 *
	 * Filesystem drivers should use these (or rather: the wrapper macros below) in order
	 * to perform aligned (O_DIRECT-style) disk I/O. */
	BLOCKING NONNULL((1, 5)) void (KCALL *fs_loadblocks)(struct mfile *__restrict self, pos_t addr, physaddr_t buf, size_t num_bytes, struct aio_multihandle *__restrict aio);
	BLOCKING NONNULL((1, 5)) void (KCALL *fs_saveblocks)(struct mfile *__restrict self, pos_t addr, physaddr_t buf, size_t num_bytes, struct aio_multihandle *__restrict aio);
	struct fsuperfeat           fs_feat;          /* [const] Filesystem features. */
	struct REF fnode_list       fs_changednodes;  /* [0..n][lock(fs_changednodes_lock)][const_if(FSUPER_NODES_DELETED)]
	                                               * List of changed node (set to FSUPER_NODES_DELETED during unmount). */
	struct atomic_lock          fs_changednodes_lock; /* Lock for `fs_changednodes' */
	Toblockop_slist(fsuper)     fs_changednodes_lops; /* Lock operators for `fs_changednodes_lock' */
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
#define fsuper_haschanged(self) \
	(__hybrid_atomic_load((self)->fs_changedsuper.le_prev, __ATOMIC_ACQUIRE) != __NULLPTR)


/* Read/Write whole filesystem sectors
 * @assume(IS_ALIGNED(buf, (size_t)1 << self->fs_root.mf_iobashift));
 * @assume(IS_ALIGNED(addr, mfile_getblocksize(&self->fs_root)));
 * @assume(IS_ALIGNED(num_bytes, mfile_getblocksize(&self->fs_root)));
 * @assume(addr + num_bytes <= self->fs_dev->mf_filesize);
 * @assume(num_bytes != 0); */
#define fsuper_dev_rdsectors_async(self, addr, buf, num_bytes, aio) \
	((*(self)->fs_loadblocks)((self)->fs_dev, addr, buf, num_bytes, aio))
#define fsuper_dev_wrsectors_async(self, addr, buf, num_bytes, aio) \
	((*(self)->fs_saveblocks)((self)->fs_dev, addr, buf, num_bytes, aio))
#define fsuper_dev_rdsectors(self, addr, buf, num_bytes) \
	mfile_dosyncio((self)->fs_dev, (self)->fs_loadblocks, addr, buf, num_bytes)
#define fsuper_dev_wrsectors(self, addr, buf, num_bytes) \
	mfile_dosyncio((self)->fs_dev, (self)->fs_saveblocks, addr, buf, num_bytes)

/* Same as `fsuper_dev_*' above, but these perform an explicit check
 * for the requested address range to actually be in-bounds. When it
 * isn't, behavior depends on `fsuper_allow_fs_oob':
 *  - When set to `false' (default), throw `E_IOERROR_BADBOUNDS'
 *  - When set to `true', out-of-bounds writes are ignored, and reads yield all zeroes.
 *    In  this case, any area that is actually in-bounds will be forwarded like normal.
 * @assume(IS_ALIGNED(buf, (size_t)1 << self->fs_root.mf_iobashift));
 * @assume(IS_ALIGNED(addr, mfile_getblocksize(&self->fs_root)));
 * @assume(IS_ALIGNED(num_bytes, mfile_getblocksize(&self->fs_root)));
 * @assume(num_bytes != 0); */
FUNDEF BLOCKING NONNULL((1, 5)) void KCALL
fsuper_dev_rdsectors_async_chk(struct fsuper *__restrict self, pos_t addr, physaddr_t buf,
                               size_t num_bytes, struct aio_multihandle *__restrict aio)
		THROWS(E_IOERROR_BADBOUNDS, ...);
FUNDEF BLOCKING NONNULL((1, 5)) void KCALL
fsuper_dev_wrsectors_async_chk(struct fsuper *__restrict self, pos_t addr, physaddr_t buf,
                               size_t num_bytes, struct aio_multihandle *__restrict aio)
		THROWS(E_IOERROR_BADBOUNDS, ...);
FUNDEF BLOCKING NONNULL((1)) void KCALL
fsuper_dev_rdsectors_chk(struct fsuper *__restrict self, pos_t addr,
                         physaddr_t buf, size_t num_bytes)
		THROWS(E_IOERROR_BADBOUNDS, ...);
FUNDEF BLOCKING NONNULL((1)) void KCALL
fsuper_dev_wrsectors_chk(struct fsuper *__restrict self, pos_t addr,
                         physaddr_t buf, size_t num_bytes)
		THROWS(E_IOERROR_BADBOUNDS, ...);


/* Default behavior for filesystem drivers attempting to perform out-of-bounds I/O
 * The value of this variable  can be controlled via  `/proc/kos/fs/allow-fs-oob'.
 * When  `true', filesystem driver disk access to out-of-bounds regions behaves as
 * though  those regions were  part of `/dev/zero', in  that writes are discarded,
 * and reads yield all zeroes. Otherwise, `E_IOERROR_BADBOUNDS' is thrown instead.
 *
 * The default for this option is `false' */
DATDEF __BOOL fsuper_allow_fs_oob;


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
	(void)(!fsuper_getops(self)->so_truncate_atime || ((*fsuper_getops(self)->so_truncate_atime)(self, tms), 0))
#define fsuper_truncate_mtime(self, tms) \
	(void)(!fsuper_getops(self)->so_truncate_mtime || ((*fsuper_getops(self)->so_truncate_mtime)(self, tms), 0))
#define fsuper_truncate_ctime(self, tms) \
	(void)(!fsuper_getops(self)->so_truncate_ctime || ((*fsuper_getops(self)->so_truncate_ctime)(self, tms), 0))
#define fsuper_truncate_btime(self, tms) \
	(void)(!fsuper_getops(self)->so_truncate_btime || ((*fsuper_getops(self)->so_truncate_btime)(self, tms), 0))




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
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_parts
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_changed
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_flags:
 *     - Initialized to `MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE'
 *       may need to be altered as appropriate.
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_iobashift
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_atime
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_mtime
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_ctime
 *  - self->fs_root._fdirnode_node_ _fnode_file_ mf_btime
 *  - self->fs_root._fdirnode_node_ fn_uid
 *  - self->fs_root._fdirnode_node_ fn_gid
 *  - self->fs_root._fdirnode_node_ fn_mode (with something or'd with S_IFDIR)
 *  - self->fs_root._fdirnode_node_ fn_ino
 *  - self->fs_root._fdirnode_node_ fn_allnodes
 * @param: struct fsuper     *self: Directory node to initialize.
 * @param: struct fsuper_ops *ops:  Directory operators.
 * @param: struct ffilesys   *fsys: File system information. */
#define _fsuper_init(self, ops, fsys)                                                          \
	(_fsuper_assert_ops_(ops) /**/                                                             \
	 ((self)->fs_nodes = _fdirnode_asnode(&(self)->fs_root)),                                  \
	 atomic_rwlock_init(&(self)->fs_nodeslock),                                                \
	 SLIST_INIT(&(self)->fs_nodeslockops),                                                     \
	 LIST_INIT(&(self)->fs_mounts),                                                            \
	 atomic_rwlock_init(&(self)->fs_mountslock),                                               \
	 SLIST_INIT(&(self)->fs_mountslockops),                                                    \
	 (self)->fs_sys = incref(fsys),                                                            \
	 atomic_lock_init(&(self)->fs_changednodes_lock),                                          \
	 SLIST_INIT(&(self)->fs_changednodes_lops),                                                \
	 LIST_INIT(&(self)->fs_changednodes),                                                      \
	 LIST_ENTRY_UNBOUND_INIT(&(self)->fs_changedsuper),                                        \
	 _fnode_init_common(_fdirnode_asnode(&(self)->fs_root)),                                   \
	 (self)->fs_root._fdirnode_node_ _fnode_file_ mf_flags = (MFILE_F_NOUSRMMAP |              \
	                                                          MFILE_F_NOUSRIO |                \
	                                                          MFILE_F_FIXEDFILESIZE),          \
	 (self)->fs_root._fdirnode_node_ _fnode_file_ mf_ops   = &(ops)->so_fdir.dno_node.no_file, \
	 atomic64_init(&(self)->fs_root._fdirnode_node_ _fnode_file_ mf_filesize, (uint64_t)-1),   \
	 (self)->fs_root._fdirnode_node_ fn_nlink         = 1,                                     \
	 (self)->fs_root._fdirnode_node_ fn_super         = (self),                                \
	 (self)->fs_root._fdirnode_node_ fn_supent.rb_lhs = __NULLPTR,                             \
	 (self)->fs_root._fdirnode_node_ fn_supent.rb_rhs = __NULLPTR)
#define _fsuper_cinit(self, ops, fsys)                                                         \
	(_fsuper_assert_ops_(ops) /**/                                                             \
	 ((self)->fs_nodes = _fdirnode_asnode(&(self)->fs_root)),                                  \
	 atomic_rwlock_cinit(&(self)->fs_nodeslock),                                               \
	 __hybrid_assert(SLIST_EMPTY(&(self)->fs_nodeslockops)),                                   \
	 __hybrid_assert(LIST_EMPTY(&(self)->fs_mounts)),                                          \
	 atomic_rwlock_cinit(&(self)->fs_mountslock),                                              \
	 __hybrid_assert(SLIST_EMPTY(&(self)->fs_mountslockops)),                                  \
	 (self)->fs_sys = incref(fsys),                                                            \
	 atomic_lock_cinit(&(self)->fs_changednodes_lock),                                         \
	 __hybrid_assert(SLIST_EMPTY(&(self)->fs_changednodes_lops)),                              \
	 __hybrid_assert(LIST_EMPTY(&(self)->fs_changednodes)),                                    \
	 LIST_ENTRY_UNBOUND_INIT(&(self)->fs_changedsuper),                                        \
	 _fnode_cinit_common(_fdirnode_asnode(&(self)->fs_root)),                                  \
	 (self)->fs_root._fdirnode_node_ _fnode_file_ mf_flags = (MFILE_F_NOUSRMMAP |              \
	                                                          MFILE_F_NOUSRIO |                \
	                                                          MFILE_F_FIXEDFILESIZE),          \
	 (self)->fs_root._fdirnode_node_ _fnode_file_ mf_ops   = &(ops)->so_fdir.dno_node.no_file, \
	 atomic64_cinit(&(self)->fs_root._fdirnode_node_ _fnode_file_ mf_filesize, (uint64_t)-1),  \
	 (self)->fs_root._fdirnode_node_ fn_nlink = 1,                                             \
	 (self)->fs_root._fdirnode_node_ fn_super = (self),                                        \
	 __hybrid_assert((self)->fs_root._fdirnode_node_ fn_supent.rb_lhs == __NULLPTR),           \
	 __hybrid_assert((self)->fs_root._fdirnode_node_ fn_supent.rb_rhs == __NULLPTR))

/* Finalize a partially initialized `struct fsuper' (as initialized by `_fsuper_init()') */
#define _fsuper_fini(self) \
	(decref_nokill((self)->fs_sys))

/* Superblock feature helper macros */
#define fsuper_hassymlink(self) fsuperfeat_hassymlink(&(self)->fs_feat)
#define fsuper_hashrdlink(self) fsuperfeat_hashrdlink(&(self)->fs_feat)


/* Helper macros for `struct fsuper::fs_changednodes_lock' */
#define _fsuper_changednodes_reap(self)      _oblockop_reap_atomic_lock(&(self)->fs_changednodes_lops, &(self)->fs_changednodes_lock, (struct fsuper *)(self))
#define fsuper_changednodes_reap(self)       oblockop_reap_atomic_lock(&(self)->fs_changednodes_lops, &(self)->fs_changednodes_lock, (struct fsuper *)(self))
#define fsuper_changednodes_mustreap(self)   oblockop_mustreap(&(self)->fs_changednodes_lops)
#define fsuper_changednodes_tryacquire(self) atomic_lock_tryacquire(&(self)->fs_changednodes_lock)
#define fsuper_changednodes_acquire(self)    atomic_lock_acquire(&(self)->fs_changednodes_lock)
#define fsuper_changednodes_acquire_nx(self) atomic_lock_acquire_nx(&(self)->fs_changednodes_lock)
#define _fsuper_changednodes_release(self)   atomic_lock_release(&(self)->fs_changednodes_lock)
#define fsuper_changednodes_release(self)    (atomic_lock_release(&(self)->fs_changednodes_lock), fsuper_changednodes_reap(self))
#define fsuper_changednodes_acquired(self)   atomic_lock_acquired(&(self)->fs_changednodes_lock)
#define fsuper_changednodes_available(self)  atomic_lock_available(&(self)->fs_changednodes_lock)
#define fsuper_changednodes_waitfor(self)    atomic_lock_waitfor(&(self)->fs_changednodes_lock)
#define fsuper_changednodes_waitfor_nx(self) atomic_lock_waitfor_nx(&(self)->fs_changednodes_lock)

/* Helper macros for `struct fsuper::fs_nodeslock' */
#define fsuper_nodes_mustreap(self)     oblockop_mustreap(&(self)->fs_nodeslockops)
#define fsuper_nodes_reap(self)         oblockop_reap_atomic_rwlock(&(self)->fs_nodeslockops, &(self)->fs_nodeslock, (struct fsuper *)(self))
#define _fsuper_nodes_reap(self)        _oblockop_reap_atomic_rwlock(&(self)->fs_nodeslockops, &(self)->fs_nodeslock, (struct fsuper *)(self))
#define fsuper_nodes_write(self)        atomic_rwlock_write(&(self)->fs_nodeslock)
#define fsuper_nodes_write_nx(self)     atomic_rwlock_write_nx(&(self)->fs_nodeslock)
#define fsuper_nodes_trywrite(self)     atomic_rwlock_trywrite(&(self)->fs_nodeslock)
#define fsuper_nodes_endwrite(self)     (atomic_rwlock_endwrite(&(self)->fs_nodeslock), fsuper_nodes_reap(self))
#define _fsuper_nodes_endwrite(self)    atomic_rwlock_endwrite(&(self)->fs_nodeslock)
#define fsuper_nodes_read(self)         atomic_rwlock_read(&(self)->fs_nodeslock)
#define fsuper_nodes_read_nx(self)      atomic_rwlock_read_nx(&(self)->fs_nodeslock)
#define fsuper_nodes_tryread(self)      atomic_rwlock_tryread(&(self)->fs_nodeslock)
#define _fsuper_nodes_endread(self)     atomic_rwlock_endread(&(self)->fs_nodeslock)
#define fsuper_nodes_endread(self)      (void)(atomic_rwlock_endread(&(self)->fs_nodeslock) && (fsuper_nodes_reap(self), 0))
#define _fsuper_nodes_end(self)         atomic_rwlock_end(&(self)->fs_nodeslock)
#define fsuper_nodes_end(self)          (void)(atomic_rwlock_end(&(self)->fs_nodeslock) && (fsuper_nodes_reap(self), 0))
#define fsuper_nodes_upgrade(self)      atomic_rwlock_upgrade(&(self)->fs_nodeslock)
#define fsuper_nodes_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->fs_nodeslock)
#define fsuper_nodes_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->fs_nodeslock)
#define fsuper_nodes_downgrade(self)    atomic_rwlock_downgrade(&(self)->fs_nodeslock)
#define fsuper_nodes_reading(self)      atomic_rwlock_reading(&(self)->fs_nodeslock)
#define fsuper_nodes_writing(self)      atomic_rwlock_writing(&(self)->fs_nodeslock)
#define fsuper_nodes_canread(self)      atomic_rwlock_canread(&(self)->fs_nodeslock)
#define fsuper_nodes_canwrite(self)     atomic_rwlock_canwrite(&(self)->fs_nodeslock)
#define fsuper_nodes_waitread(self)     atomic_rwlock_waitread(&(self)->fs_nodeslock)
#define fsuper_nodes_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->fs_nodeslock)
#define fsuper_nodes_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->fs_nodeslock)
#define fsuper_nodes_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->fs_nodeslock)

/* Helper macros for `struct fsuper::fs_mountslock' */
#define fsuper_mounts_mustreap(self)     oblockop_mustreap(&(self)->fs_mountslockops)
#define fsuper_mounts_reap(self)         oblockop_reap_atomic_rwlock(&(self)->fs_mountslockops, &(self)->fs_mountslock, (struct fsuper *)(self))
#define _fsuper_mounts_reap(self)        _oblockop_reap_atomic_rwlock(&(self)->fs_mountslockops, &(self)->fs_mountslock, (struct fsuper *)(self))
#define fsuper_mounts_write(self)        atomic_rwlock_write(&(self)->fs_mountslock)
#define fsuper_mounts_write_nx(self)     atomic_rwlock_write_nx(&(self)->fs_mountslock)
#define fsuper_mounts_trywrite(self)     atomic_rwlock_trywrite(&(self)->fs_mountslock)
#define fsuper_mounts_endwrite(self)     (atomic_rwlock_endwrite(&(self)->fs_mountslock), fsuper_mounts_reap(self))
#define _fsuper_mounts_endwrite(self)    atomic_rwlock_endwrite(&(self)->fs_mountslock)
#define fsuper_mounts_read(self)         atomic_rwlock_read(&(self)->fs_mountslock)
#define fsuper_mounts_read_nx(self)      atomic_rwlock_read_nx(&(self)->fs_mountslock)
#define fsuper_mounts_tryread(self)      atomic_rwlock_tryread(&(self)->fs_mountslock)
#define _fsuper_mounts_endread(self)     atomic_rwlock_endread(&(self)->fs_mountslock)
#define fsuper_mounts_endread(self)      (void)(atomic_rwlock_endread(&(self)->fs_mountslock) && (fsuper_mounts_reap(self), 0))
#define _fsuper_mounts_end(self)         atomic_rwlock_end(&(self)->fs_mountslock)
#define fsuper_mounts_end(self)          (void)(atomic_rwlock_end(&(self)->fs_mountslock) && (fsuper_mounts_reap(self), 0))
#define fsuper_mounts_upgrade(self)      atomic_rwlock_upgrade(&(self)->fs_mountslock)
#define fsuper_mounts_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->fs_mountslock)
#define fsuper_mounts_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->fs_mountslock)
#define fsuper_mounts_downgrade(self)    atomic_rwlock_downgrade(&(self)->fs_mountslock)
#define fsuper_mounts_reading(self)      atomic_rwlock_reading(&(self)->fs_mountslock)
#define fsuper_mounts_writing(self)      atomic_rwlock_writing(&(self)->fs_mountslock)
#define fsuper_mounts_canread(self)      atomic_rwlock_canread(&(self)->fs_mountslock)
#define fsuper_mounts_canwrite(self)     atomic_rwlock_canwrite(&(self)->fs_mountslock)
#define fsuper_mounts_waitread(self)     atomic_rwlock_waitread(&(self)->fs_mountslock)
#define fsuper_mounts_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->fs_mountslock)
#define fsuper_mounts_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->fs_mountslock)
#define fsuper_mounts_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->fs_mountslock)


/* Filenode tree operations. (caller must be holding a lock to `self->fs_nodeslock') */
#define fsuper_nodes_locate(self, ino)      fnode_tree_locate((self)->fs_nodes, ino)
#define fsuper_nodes_tryinsert(self, node)  fnode_tree_tryinsert(&(self)->fs_nodes, node)
#define fsuper_nodes_insert(self, node)     fnode_tree_insert(&(self)->fs_nodes, node)
#define fsuper_nodes_remove(self, ino)      fnode_tree_remove(&(self)->fs_nodes, ino)
#define fsuper_nodes_removenode(self, node) fnode_tree_removenode(&(self)->fs_nodes, node)


/* Reference count control simply uses `fs_root' as basis.
 * Note that fields of `struct fsuper' grow upwards so that custom sub-classes of `fdirnode'
 * can  simply be used in order to implement `fs_root', allowing for binary compatibility in
 * terms of fsuper field offsets between all possible variants. */
#define fsuper_destroy(self) mfile_destroy(_fnode_asfile(_fdirnode_asnode(&(self)->fs_root)))
DEFINE_REFCNT_FUNCTIONS(struct fsuper, fs_root._fdirnode_node_ _fnode_file_ mf_refcnt, fsuper_destroy)


/* Default operators for `struct fsuper_ops' */
FUNDEF NOBLOCK NONNULL((1)) void /* `kfree(fnode_assuper(self));' */
NOTHROW(KCALL fsuper_v_free)(struct fnode *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fsuper_v_destroy)(struct mfile *__restrict self);
#define fsuper_v_changed    fdirnode_v_changed
#define fsuper_v_open       fdirnode_v_open
#define fsuper_v_stat       fdirnode_v_stat
#define fsuper_v_ioctl      fdirnode_v_ioctl
#define fsuper_v_stream_ops fdirnode_v_stream_ops


/* Return a reference to the first non-destroyed node with a base-ino >= `pred->fn_ino'.
 * - When `pred == NULL' or `pred->fn_supent.rb_rhs == FSUPER_NODES_DELETED', return a
 *   reference to the inode with the lowest address.
 * - If no such INode exists, or the inode tree of `self' has been destroyed, return `NULL'. */
FUNDEF WUNUSED NONNULL((1)) REF struct fnode *KCALL
fsuper_nodeafter(struct fsuper *__restrict self, struct fnode *pred)
		THROWS(E_WOULDBLOCK);


/* #1: Remove `self' from the list of changed superblocks (if not done already)
 * #2: Write modified data and attributes of all changed fnode-s to disk.
 * #3: Invoke the `so_sync' operator (if defined)
 * If an exception is thrown during step #2 or #3, re-add `self' to the list of changed superblocks */
FUNDEF BLOCKING NONNULL((1)) void KCALL
fsuper_sync(struct fsuper *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...);

/* Synchronize all superblocks containing changed fnode-s (s.a. `fchangedsuper_list') */
FUNDEF BLOCKING void KCALL fsuper_syncall(void)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...);


/* Retrieve the label of the given superblock and store it in `buf'
 * @return: true:  Successfully retrieved and stored the label.
 * @return: false: `self' doesn't have a volume label. */
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL KCALL
fsuper_getlabel(struct fsuper *__restrict self,
                USER CHECKED char buf[FSLABEL_MAX])
		THROWS(E_IOERROR, E_SEGFAULT, ...);

/* Set the label of the given superblock and store it in `buf'
 * @return: true:  Successfully saved the label.
 * @return: false: `self' doesn't have a volume label.
 * @throws: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_FSLABEL_TOO_LONG:namelen: [...] */
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL KCALL
fsuper_setlabel(struct fsuper *__restrict self,
                USER CHECKED char const *name, size_t namelen)
		THROWS(E_IOERROR, E_FSERROR_READONLY, E_SEGFAULT,
		       E_INVALID_ARGUMENT_BAD_VALUE, ...);



/* Mark `self' as deleted (should be called when all
 * mounting  points  using `self'  have  gone away):
 *  - For all nodes in `self->fs_nodes':
 *    - Call `mfile_delete()'
 *    - Remove the fnode from the global list of file-nodes
 *  - Mark the `fs_nodes' and `fs_changednodes' as `FSUPER_NODES_DELETED',
 *    and  drop  references from  all  changed files  that  were captured.
 * Note that the caller should first invoke `fsuper_sync()' to ensure
 * that any unwritten changes are written to disk.
 *
 * Anything  from the  above that  couldn't be  done synchronously via
 * non-blocking operations will  instead be completed  asynchronously,
 * meaning that the caller should let the superblock cleanup itself as
 * required locks become available... */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fsuper_delete)(struct fsuper *__restrict self);

/* Internal implementation of `fsuper_delete()' (don't call this one
 * unless  you know that you're doing; otherwise, you may cause race
 * conditions that can result in data corruption) */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL fsuper_delete_strt)(struct fsuper *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fsuper_delete_impl)(struct fsuper *__restrict self);


/* Gather information about the filesystem and store that information in `*result' */
FUNDEF BLOCKING NONNULL((1, 2)) void FCALL
fsuper_statfs(struct fsuper *__restrict self,
              USER CHECKED struct statfs *result)
		THROWS(E_SEGFAULT, E_IOERROR, ...);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FSUPER_H */
