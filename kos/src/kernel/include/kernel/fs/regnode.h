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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_REGNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_REGNODE_H 1

#include <kernel/compiler.h>

#include <kernel/fs/node.h>
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

struct fregnode;
struct fregnode_ops {
	struct fnode_ops rno_node; /* FNode operators */
	/* More operators would go here... */
};


struct fregnode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fnode               /* Underlying file-node */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fnode rn_node; /* Underlying file-node */
#define _fregnode_asnode(x) &(x)->rn_node
#define _fregnode_node_     rn_node.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _fregnode_asnode(x) x
#define _fregnode_node_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
};

/* Return a pointer to regular-node operators of `self' */
#define fregnode_getops(self) \
	((struct fregnode_ops const *)__COMPILER_REQTYPE(struct fregnode const *, self)->_fregnode_node_ _fnode_file_ mf_ops)
#define _fregnode_assert_ops_(ops) \
	_fnode_assert_ops_(&(ops)->rno_node)


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_fregnode_node_ _fnode_file_ mf_filesize
 *  - self->_fregnode_node_ _fnode_file_ mf_atime
 *  - self->_fregnode_node_ _fnode_file_ mf_mtime
 *  - self->_fregnode_node_ _fnode_file_ mf_ctime
 *  - self->_fregnode_node_ _fnode_file_ mf_btime
 *  - self->_fregnode_node_ fn_uid
 *  - self->_fregnode_node_ fn_gid
 *  - self->_fregnode_node_ fn_allnodes
 *  - self->_fregnode_node_ fn_supent
 *  - self->_fregnode_node_ fn_nlink
 *  - self->_fregnode_node_ fn_ino
 *  - self->_fregnode_node_ fn_mode (with something or'd with S_IFREG)
 * @param: struct fregnode     *self:   Regular node to initialize.
 * @param: struct fregnode_ops *ops:    Regular file operators.
 * @param: struct fsuper       *super:  Filesystem superblock. */
#define _fregnode_init(self, ops, super)                                                                               \
	(_fregnode_assert_ops_(ops) _fnode_init_common(_fregnode_asnode(self)),                                            \
	 (self)->_fregnode_node_ _fnode_file_ mf_parts = __NULLPTR,                                                        \
	 SLIST_INIT(&(self)->_fregnode_node_ _fnode_file_ mf_changed),                                                     \
	 (self)->_fregnode_node_ _fnode_file_ mf_flags = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags &          \
	                                                 (MFILE_F_DELETED | MFILE_F_PERSISTENT |                           \
	                                                  MFILE_F_READONLY | MFILE_F_NOATIME |                             \
	                                                  MFILE_F_NOMTIME),                                                \
	 (self)->_fregnode_node_ _fnode_file_ mf_ops        = &(ops)->rno_node.no_file,                                    \
	 (self)->_fregnode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 (self)->_fregnode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_fregnode_node_ _fnode_file_ mf_iobashift  = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_iobashift,  \
	 (self)->_fregnode_node_ fn_super                   = incref(super))
#define _fregnode_cinit(self, ops, super)                                                                              \
	(_fregnode_assert_ops_(ops) _fnode_cinit_common(_fregnode_asnode(self)),                                           \
	 __hybrid_assert((self)->mf_parts == __NULLPTR),                                                                   \
	 __hybrid_assert(SLIST_EMPTY(&(self)->mf_changed)),                                                                \
	 (self)->_fregnode_node_ _fnode_file_ mf_flags = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags &          \
	                                                 (MFILE_F_DELETED | MFILE_F_PERSISTENT |                           \
	                                                  MFILE_F_READONLY | MFILE_F_NOATIME |                             \
	                                                  MFILE_F_NOMTIME),                                                \
	 (self)->_fregnode_node_ _fnode_file_ mf_ops        = &(ops)->rno_node.no_file,                                    \
	 (self)->_fregnode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 (self)->_fregnode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_fregnode_node_ _fnode_file_ mf_iobashift  = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_iobashift,  \
	 (self)->_fregnode_node_ fn_super                   = incref(super))
/* Finalize a partially initialized `struct fregnode' (as initialized by `_fregnode_init()') */
#define _fregnode_fini(self) decref_nokill((self)->_fregnode_node_ fn_super)


/* Default operators for `struct fdirnode_ops' */
#define fregnode_v_destroy fnode_v_destroy
#define fregnode_v_changed fnode_v_changed
#define fregnode_v_ioctl   fnode_v_ioctl

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_REGNODE_H */
