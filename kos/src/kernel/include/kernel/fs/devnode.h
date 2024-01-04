/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVNODE_H 1

#include <kernel/compiler.h>

#include <kernel/fs/node.h>
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

struct fdevnode;
struct fdevnode_ops {
	struct fnode_ops dvno_node; /* FNode operators */
	/* More operators would go here... */
};

struct fdevnode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fnode                /* Underlying file-node */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fnode dn_node;  /* Underlying file-node */
#define _fdevnode_asnode(x) &(x)->dn_node
#define _fdevnode_node_     dn_node.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _fdevnode_asnode(x) x
#define _fdevnode_node_    /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	dev_t        dn_devno; /* [const] Device number. */
};


/* Return a pointer to device-node operators of `self' */
#define fdevnode_getops(self) \
	((struct fdevnode_ops const *)__COMPILER_REQTYPE(struct fdevnode const *, self)->_fdevnode_node_ _fnode_file_ mf_ops)
#define _fdevnode_assert_ops_(ops) \
	_fnode_assert_ops_(&(ops)->dvno_node)

#define fdevnode_getdevno(self) ((self)->dn_devno)


struct path;
struct fdirent;
struct handle;

/* Default  operator  for opening  fdevnode files.  This will
 * lookup the associated `dn_devno' within `devfs' and return
 * the file that one points to. */
FUNDEF NONNULL((1, 2)) void KCALL
fdevnode_v_open(struct mfile *__restrict self,
                struct handle *__restrict hand,
                struct path *access_path,
                struct fdirent *access_dent,
                oflag_t oflags)
		THROWS(E_WOULDBLOCK, E_NO_DEVICE);
#define fdevnode_v_changed fnode_v_changed
#define fdevnode_v_destroy fnode_v_destroy
#define fdevnode_v_ioctl   fnode_v_ioctl


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_fdevnode_node_ _fnode_file_ mf_atime
 *  - self->_fdevnode_node_ _fnode_file_ mf_mtime
 *  - self->_fdevnode_node_ _fnode_file_ mf_ctime
 *  - self->_fdevnode_node_ _fnode_file_ mf_btime
 *  - self->_fdevnode_node_ fn_uid
 *  - self->_fdevnode_node_ fn_gid
 *  - self->_fdevnode_node_ fn_allnodes
 *  - self->_fdevnode_node_ fn_supent
 *  - self->_fdevnode_node_ fn_nlink
 *  - self->_fdevnode_node_ fn_ino
 *  - self->_fdevnode_node_ fn_mode (with something or'd with S_IFCHR or S_IFBLK)
 *  - self->dn_devno
 * @param: struct fdevnode     *self:  Device node to initialize.
 * @param: struct fdevnode_ops *ops:   Device node operators.
 * @param: struct fsuper       *super: Filesystem superblock. */
#define _fdevnode_init(self, ops, super)                                                                               \
	(_fdevnode_assert_ops_(ops) _fnode_init_common(_fdevnode_asnode(self)),                                            \
	 (self)->_fdevnode_node_ _fnode_file_ mf_parts             = MFILE_PARTS_ANONYMOUS,                                \
	 (self)->_fdevnode_node_ _fnode_file_ mf_changed.slh_first = MFILE_PARTS_ANONYMOUS,                                \
	 atomic64_init(&(self)->_fdevnode_node_ _fnode_file_ mf_filesize, 0),                                              \
	 (self)->_fdevnode_node_ _fnode_file_ mf_flags = ((super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags &         \
	                                                  (MFILE_F_DELETED | MFILE_F_PERSISTENT |                          \
	                                                   MFILE_F_READONLY | MFILE_F_NOATIME |                            \
	                                                   MFILE_F_NOMTIME)) |                                             \
	                                                 MFILE_F_FIXEDFILESIZE,                                            \
	 (self)->_fdevnode_node_ _fnode_file_ mf_ops        = &(ops)->dvno_node.no_file,                                   \
	 (self)->_fdevnode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 (self)->_fdevnode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_fdevnode_node_ _fnode_file_ mf_iobashift  = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_iobashift,  \
	 (self)->_fdevnode_node_ fn_super                   = incref(super))
#define _fdevnode_cinit(self, ops, super)                                                                              \
	(_fdevnode_assert_ops_(ops) _fnode_cinit_common(_fdevnode_asnode(self)),                                           \
	 (self)->_fdevnode_node_ _fnode_file_ mf_parts             = MFILE_PARTS_ANONYMOUS,                                \
	 (self)->_fdevnode_node_ _fnode_file_ mf_changed.slh_first = MFILE_PARTS_ANONYMOUS,                                \
	 atomic64_cinit(&(self)->_fdevnode_node_ _fnode_file_ mf_filesize, 0),                                             \
	 (self)->_fdevnode_node_ _fnode_file_ mf_flags = ((super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags &         \
	                                                  (MFILE_F_DELETED | MFILE_F_PERSISTENT |                          \
	                                                   MFILE_F_READONLY | MFILE_F_NOATIME |                            \
	                                                   MFILE_F_NOMTIME)) |                                             \
	                                                 MFILE_F_FIXEDFILESIZE,                                            \
	 (self)->_fdevnode_node_ _fnode_file_ mf_ops        = &(ops)->dvno_node.no_file,                                   \
	 (self)->_fdevnode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 (self)->_fdevnode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_fdevnode_node_ _fnode_file_ mf_iobashift  = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_iobashift,  \
	 (self)->_fdevnode_node_ fn_super                   = incref(super))
/* Finalize a partially initialized `struct fdevnode' (as initialized by `_fdevnode_init()') */
#define _fdevnode_fini(self) decref_nokill((self)->_fdevnode_node_ fn_super)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVNODE_H */
