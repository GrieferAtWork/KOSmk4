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
#include <kernel/fs/fnode.h>
#include <kernel/fs/fdirnode.h>
#include <kernel/types.h>

#include <kos/io.h>

#ifdef __CC__
DECL_BEGIN

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


struct fsuper_ops {
	/* NOTE: filesystem-specific operators (if needed) go here... */
#define _fsuper_ops_firstfield(prefix)  prefix##destroy /* TODO */
#define fsuper_ops_as_fdirnode_ops(ops) ((struct fdirnode_ops const *)&(ops)->_fdirnode_ops_firstfield(so_))
#define fsuper_ops_as_fnode_ops(ops)    ((struct fnode_ops const *)&(ops)->_fnode_ops_firstfield(so_))
#define fsuper_ops_as_mfile_ops(ops)    ((struct mfile_ops const *)&(ops)->_mfile_ops_firstfield(so_))
#define FSUPER_OPS_FIELDS(prefix, T)                            \
	/* [0..1] Gather information about the filesystem.       \
	 * The caller has already initialized:       \
	 *   - f_type    (== self->fs_feat.sf_magic)       \
	 *   - f_bsize   (== 1 << self->fs_root.mf_blockshift)       \
	 *   - f_blocks  (== fs_dev ? fs_dev->mf_filesize >> self->fs_root.mf_blockshift : 0)       \
	 *   - f_namelen (== self->fs_feat.sf_name_max)       \
	 *   - f_frsize  (== 1 << self->fs_root.mf_blockshift)       \
	 *   - f_flags   (== 1 << self->fs_root.mf_blockshift)       \
	__syscall_ulong_t f_flags;    /* Mount flags (set of `ST_*' from <sys/statvfs.h>) */
	__syscall_ulong_t f_spare[4]; /* ??? */
	 * This function must initialize:       \
	 *   - f_bfree        \
	 *   - f_bavail       \
	 *   - f_files        \
	 *   - f_ffree        \
	 *   - f_fsid        \
	 */       \
	NONNULL((1)) void                                           \
	(KCALL *prefix##statfs)(struct fsuper * __restrict self,    \
	                        USER CHECKED struct statfs *result) \
			THROWS(E_IOERROR, E_SEGFAULT, ...);                 \
	                                                            \
	FDIRNODE_OPS_FIELDS(prefix, struct fdirnode)

	/* Operators... */
	FSUPER_OPS_FIELDS(so_, struct fsuper);
	/* NOTE: root-directory-type-specific operators go here... */
};

struct fsuper {
	/* More fields of custom (fs-specific) `fsuper' sub-classes go here. */

	/* TODO: fsuper fields: changed nodes */
	/* TODO: fsuper fields: fnode LLRB-tree (by node INO number) */
	/* TODO: fsuper fields:  */
	REF struct blkdev *fs_dev;  /* [0..1][const] Underlying block-device. (if any) */
	struct fsuperfeat  fs_feat; /* Filesystem features. */
	struct fdirnode    fs_root; /* Filesystem root. */
	/* More fields of custom `fdirnode' sub-classes go here. */
};

/* Return a pointer to superblock-node operators of `self' */
#define fsuper_getops(self)                                               \
	((struct fsuper_ops const *)((byte_t const *)(self)->fs_root.mf_ops - \
	                             __builtin_offsetof(struct fsuper_ops,    \
	                                                _fdirnode_ops_firstfield(so_))))

/* Return a pointer to the filesystem superblock, given a pointer to its root directory.
 * This function may be used by custom implementations for `fs_root.mo_ops' */
#define fsuper_from_root(root) \
	__COMPILER_CONTAINER_OF(root, struct fsuper, fs_root)



DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FSUPER_H */
