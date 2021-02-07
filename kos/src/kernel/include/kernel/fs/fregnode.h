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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FREGNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FREGNODE_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/fnode.h>
#include <kernel/types.h>

#include <kos/io.h>

#ifdef __CC__
DECL_BEGIN

struct fregnode;
struct fregnode_ops {
	FNODE_OPS_FIELDS(rno_, struct fregnode);
#define FREGNODE_OPS_FIELDS(prefix, T)   FNODE_OPS_FIELDS(prefix, T)
#define _fregnode_ops_firstfield(prefix) _fnode_ops_firstfield(prefix)
#define _fregnode_ops_extract(ops)       ((struct fregnode_ops const *)&(ops)->_fregnode_ops_firstfield(rno_))
#define fregnode_ops_as_fnode_ops(ops)   ((struct fnode_ops const *)&(ops)->_fnode_ops_firstfield(rno_))
#define fregnode_ops_as_mfile_ops(ops)   ((struct mfile_ops const *)&(ops)->_mfile_ops_firstfield(rno_))
	/* More operators would go here... */
};


struct fregnode
#ifdef __cplusplus
    : fnode                            /* Underlying file-node */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct fnode           rn_file;    /* Underlying file-node */
#endif /* !__cplusplus */
};

/* Return a pointer to regular-node operators of `self' */
#define fregnode_getops(self) \
	((struct fregnode_ops const *)__COMPILER_REQTYPE(struct fregnode const *, self)->mf_ops)

/* Initialize common+basic fields. The caller must still initialize:
 *  - mf_filesize, mf_atime, mf_mtime, mf_ctime
 *  - fn_allnodes, fn_supent, fn_nlink, fn_ino, fn_mode (with something or'd with S_IFREG)
 * @param: struct fregnode     *self:   Regular node to initialize.
 * @param: struct fregnode_ops *ops:    Regular file operators.
 * @param: struct fsuper       *super:  Filesystem superblock. */
#define _fregnode_init(self, ops, super)                        \
	(_mfile_init_common(self),                                  \
	 (self)->mf_parts = __NULLPTR,                              \
	 (self)->mf_flags = (super)->mf_flags &                     \
	                    (MFILE_F_DELETED | MFILE_F_PERSISTENT | \
	                     MFILE_F_READONLY | MFILE_F_NOATIME |   \
	                     MFILE_F_NOMTIME),                      \
	 (self)->mf_ops        = fregnode_ops_as_mfile_ops(ops),    \
	 (self)->mf_blockshift = (super)->mf_blockshift,            \
	 (self)->mf_part_amask = (super)->mf_part_amask,            \
	 (self)->fn_super      = incref(super))
#define _fregnode_cinit(self, ops, super)                       \
	(_mfile_cinit_common(self),                                 \
	 __hybrid_assert((self)->mf_parts == __NULLPTR),            \
	 (self)->mf_flags = (super)->mf_flags &                     \
	                    (MFILE_F_DELETED | MFILE_F_PERSISTENT | \
	                     MFILE_F_READONLY | MFILE_F_NOATIME |   \
	                     MFILE_F_NOMTIME),                      \
	 (self)->mf_ops        = fregnode_ops_as_mfile_ops(ops),    \
	 (self)->mf_blockshift = (super)->mf_blockshift,            \
	 (self)->mf_part_amask = (super)->mf_part_amask,            \
	 (self)->fn_super      = incref(super))
/* Finalize a partially initialized `struct fregnode' (as initialized by `_fregnode_init()') */
#define _fregnode_fini(self) decref_nokill((self)->fn_super)

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FREGNODE_H */
