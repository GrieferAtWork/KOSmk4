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
#include <kernel/fs/fdirnode.h>
#include <kernel/fs/fnode.h>
#include <kernel/mman/mfile.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <asm/os/statvfs.h>
#include <kos/io.h>

#ifndef REF_IF
#define REF_IF __REF_IF
#endif /* !REF_IF */

#ifdef __CC__
DECL_BEGIN

/* Convert flags:
 *    MFILE_F_READONLY  -->  ST_RDONLY
 *    MFILE_FS_NOSUID   -->  ST_NOSUID
 *    MFILE_FS_NOEXEC   -->  ST_NOEXEC
 *    MFILE_F_NOATIME   -->  ST_NOATIME */
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
	pos_t   sf_symlink_max;        /* [const] Max length of text contained within symbolic links */
	nlink_t sf_link_max;           /* [const] Max # links a file may have */
	u32     sf_magic;              /* [const] Filesystem ~magic~ (one of the constants from `<linux/magic.h>') */
	u32     sf_rec_incr_xfer_size; /* [const] Buffer size increments for efficient disk transfer operations */
	u32     sf_rec_max_xfer_size;  /* [const] Max buffer size for efficient disk transfer operations */
	u32     sf_rec_min_xfer_size;  /* [const] Min buffer size for efficient disk transfer operations */
	u32     sf_rec_xfer_align;     /* [const] Required in-memory buffer alignment for efficient disk transfer operations */
	u16     sf_name_max;           /* [const] Max # chars in a file name */
	u8      sf_filesizebits;       /* [const] Max # of bits in a file's size field (usually 64 or 32) */
};
#define fsuperfeat_hassymlink(self) ((self)->sf_symlink_max != 0)
#define fsuperfeat_hashrdlink(self) ((self)->sf_link_max > 1)

struct fdirnode;
struct fdirent;

struct fsuper_ops {
	/* NOTE: filesystem-specific operators (if needed) go here... */
#define _fsuper_ops_firstfield(prefix)  prefix##opennode
#define fsuper_ops_as_fdirnode_ops(ops) ((struct fdirnode_ops const *)&(ops)->_fdirnode_ops_firstfield(so_))
#define fsuper_ops_as_fnode_ops(ops)    ((struct fnode_ops const *)&(ops)->_fnode_ops_firstfield(so_))
#define fsuper_ops_as_mfile_ops(ops)    ((struct mfile_ops const *)&(ops)->_mfile_ops_firstfield(so_))
#define FSUPER_OPS_FIELDS(prefix, T)                                                      \
	/* [0..1] Flush unwritten changes to disk and/or disk buffers */                      \
	ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fnode *                               \
	(KCALL *prefix##sync)(T *__restrict self)                                             \
			THROWS(E_IOERROR, ...);                                                       \
	                                                                                      \
	/* [0..1] Clear filesystem superblock caches */                                       \
	NOBLOCK NONNULL((1)) void                                                             \
	/*NOTHROW*/ (KCALL *prefix##clearcache)(T *__restrict self);                          \
	                                                                                      \
	/* [0..1] Gather information about the filesystem.                                    \
	 * The caller has already initialized:                                                \
	 *   - f_type    (== self->fs_feat.sf_magic)                                          \
	 *   - f_bsize   (== 1 << self->fs_root.mf_blockshift)                                \
	 *   - f_blocks  (== fs_dev ? fs_dev->mf_filesize >> self->fs_root.mf_blockshift : 0) \
	 *   - f_namelen (== self->fs_feat.sf_name_max)                                       \
	 *   - f_frsize  (== 1 << self->fs_root.mf_blockshift)                                \
	 *   - f_flags   (== statvfs_flags_from_mfile_flags(self->fs_root.mf_flags))          \
	 * This function must initialize:                                                     \
	 *   - f_bfree                                                                        \
	 *   - f_bavail                                                                       \
	 *   - f_files                                                                        \
	 *   - f_ffree                                                                        \
	 *   - f_fsid */                                                                      \
	NONNULL((1)) void                                                                     \
	(KCALL *prefix##statfs)(T *__restrict self,                                           \
	                        USER CHECKED struct statfs *result)                           \
			THROWS(E_IOERROR, E_SEGFAULT, ...);                                           \
	                                                                                      \
	FDIRNODE_OPS_FIELDS(prefix, struct fdirnode)

	/* Operators... */
	FSUPER_OPS_FIELDS(so_, struct fsuper);
	/* NOTE: root-directory-type-specific operators go here... */
};


#ifndef __fnode_slist_defined
#define __fnode_slist_defined 1
SLIST_HEAD(fnode_slist, fnode);
#endif /* !__fnode_slist_defined */

/* Special value for `struct fsuper::fs_changed'. When set, further
 * changed parts are no longer traced, and `fnode'-s will no longer
 * be added to the changed-node list. This value is assigned as part
 * of unmounting a superblock, which is also includes deleting all
 * files still opened within the superblock's node-tree, thus also
 * causing all loaded files to be deleted. */
#define FSUPER_NODES_DELETED ((struct fnode *)-1)

struct fsuper_lockop; /* from "fsuper-lockop.h" */
#ifndef __fsuper_lockop_defined
#define __fsuper_lockop_defined
SLIST_HEAD(fsuper_lockop_slist, fsuper_lockop);
#endif /* !__fsuper_lockop_defined */

struct vmount; /* Mounting point descriptor. */
#ifndef __vmount_list_defined
#define __vmount_list_defined
LIST_HEAD(vmount_list, vmount);
#endif /* !__vmount_list_defined */


struct fsuper {
	/* More fields of custom (fs-specific) `fsuper' sub-classes go here. */
	REF_IF([*].mf_flags & MFILE_F_PERSISTENT)
	LLRBTREE_ROOT(struct fnode) fs_nodes;         /* [0..n][lock(fs_nodeslock)] Tree of known nodes (ordered by INO number)
	                                               * This tree holds a reference to any file that has the `MFILE_F_PERSISTENT'
	                                               * flag set. When set to `FSUPER_NODES_DELETED', no further file-nodes can
	                                               * be opened, and `fsuper_opennode()' will throw `E_FSERROR_DELETED'. */
	struct atomic_rwlock        fs_nodeslock;     /* Lock for `fs_nodes' */
	struct fsuper_lockop_slist  fs_nodeslockops;  /* [lock(ATOMIC)] Pending lock-operations for `fs_nodeslock' */
	struct vmount_list          fs_mounts;        /* [0..n][lock(fs_mountslock)] List of mounting points of this superblock.
	                                               * When this list becomes empty, `fsuper_delete()' is automatically called. */
	struct atomic_rwlock        fs_mountslock;    /* Lock for `fs_mounts' */
	struct fsuper_lockop_slist  fs_mountslockops; /* [lock(ATOMIC)] Pending lock-operations for `fs_mountslock' */
	REF struct ffilesys        *fs_sys;           /* [1..1][const] fs-descriptor of this superblock. */
	REF struct blkdev          *fs_dev;           /* [0..1][const] Underlying block-device. (if any) */
	struct fsuperfeat           fs_feat;          /* Filesystem features. */
	struct REF fnode_slist      fs_changed;       /* [0..n][lock(ATOMIC)][const_if(FSUPER_NODES_DELETED)]
	                                               * List of changed node (set to DELETED during unmount)
	                                               * Note that for ramfs filesystems, this list will always
	                                               * be marked as DELETED, in order to prevent the tracking
	                                               * of changed files, since there'd be no point in tracking
	                                               * them if one can't write them do any backing storage! */
	struct fdirnode             fs_root;          /* Filesystem root. NOTE: The `mf_flags' field of this
	                                               * struct also contains all of the `MFILE_FS_*' flags. */
	/* More fields of custom `fdirnode' sub-classes go here. */
};

/* Reference count control simply uses `fs_root' as basis.
 * Note that fields of `struct fsuper' grow upwards so that custom sub-classes of `fdirnode'
 * can simply be used in order to implement `fs_root', allowing for binary compatibility in
 * terms of fsuper field offsets between all possible variants. */
#define fsuper_destroy(self) mfile_destroy(&(self)->fs_root)
DEFINE_REFCOUNT_FUNCTIONS(struct fsuper, fs_root.mf_refcnt, fsuper_destroy)


/* Return a pointer to superblock-node operators of `self' */
#define fsuper_getops(self)                                               \
	((struct fsuper_ops const *)((byte_t const *)(self)->fs_root.mf_ops - \
	                             __builtin_offsetof(struct fsuper_ops,    \
	                                                _fdirnode_ops_firstfield(so_))))

/* Return a pointer to the filesystem superblock, given a pointer to its root directory.
 * This function may be used by custom implementations for `fs_root.mo_ops' */
#define fsuper_from_root(root) \
	__COMPILER_CONTAINER_OF(root, struct fsuper, fs_root)


/* Mark `self' as deleted (should be called when all
 * mounting points using `self' have gone away):
 *  - For all nodes in `self->fs_nodes':
 *    - Call `mfile_delete()'
 *    - Clear the `MFILE_F_PERSISTENT' and `MFILE_FN_GLOBAL_REF' flags
 *    - Remove the fnode from the global list of file-nodes
 *  - Mark the `fs_nodes' and `fs_changed' as `FSUPER_NODES_DELETED',
 *    and drop references from all changed files that were captured.
 * Note that the caller should first invoke `fsuper_sync()' to ensure
 * that any unwritten changes are written to disk.
 *
 * Anything from the above that couldn't be done via synchronously via
 * non-blocking operations will instead be completed asynchronously,
 * meaning that the caller should let the superblock cleanup itself as
 * required locks become available... */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fsuper_delete)(struct fsuper *__restrict self);


/* Open a file-node, given its containing directory and directory entry */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct fnode *KCALL
fsuper_opennode(struct fsuper *__restrict self,
                struct fdirnode *__restrict dir,
                struct fdirent *__restrict name)
		THROWS(E_IOERROR, E_BADALLOC, ...);



DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FSUPER_H */
