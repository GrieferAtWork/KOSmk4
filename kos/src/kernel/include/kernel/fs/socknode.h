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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_SOCKNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_SOCKNODE_H 1

#include <kernel/compiler.h>

#include <kernel/fs/node.h>
#include <kernel/types.h>

#include <network/unix-socket.h>

#ifdef __CC__
DECL_BEGIN

struct fsocknode;
struct fsocknode_ops {
	struct fnode_ops suno_node; /* FNode operators */
	/* More operators would go here... */
};

struct fsocknode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fnode                /* Underlying file-node */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fnode sun_node;  /* Underlying file-node */
#define _fsocknode_asnode(x) &(x)->sun_node
#define _fsocknode_node_     sun_node.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _fsocknode_asnode(x) x
#define _fsocknode_node_    /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	struct unix_server sun_server; /* Unix domain socket server descriptor. */
};


/* Return a pointer to sockice-node operators of `self' */
#define fsocknode_getops(self) \
	((struct fsocknode_ops const *)__COMPILER_REQTYPE(struct fsocknode const *, self)->_fsocknode_node_ _fnode_file_ mf_ops)
#define _fsocknode_assert_ops_(ops) \
	_fnode_assert_ops_(&(ops)->suno_node)

struct path;
struct fdirent;
struct handle;

/* Default operator for opening fsocknode files. This will unconditionally
 * throw:  `E_ILLEGAL_IO_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_OPEN_S_IFSOCK' */
FUNDEF NONNULL((1, 2)) void KCALL
fsocknode_v_open(struct mfile *__restrict self,
                 struct handle *__restrict hand,
                 struct path *access_path,
                 struct fdirent *access_dent,
                 oflag_t oflags)
		THROWS(E_ILLEGAL_IO_OPERATION);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fsocknode_v_destroy)(struct mfile *__restrict self);
#define fsocknode_v_changed fnode_v_changed
#define fsocknode_v_ioctl   fnode_v_ioctl


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_fsocknode_node_ _fnode_file_ mf_atime
 *  - self->_fsocknode_node_ _fnode_file_ mf_mtime
 *  - self->_fsocknode_node_ _fnode_file_ mf_ctime
 *  - self->_fsocknode_node_ _fnode_file_ mf_btime
 *  - self->_fsocknode_node_ fn_uid
 *  - self->_fsocknode_node_ fn_gid
 *  - self->_fsocknode_node_ fn_allnodes
 *  - self->_fsocknode_node_ fn_supent
 *  - self->_fsocknode_node_ fn_nlink
 *  - self->_fsocknode_node_ fn_ino
 *  - self->_fsocknode_node_ fn_mode (with something or'd with S_IFSOCK)
 * @param: struct fsocknode     *self:  Socket node to initialize.
 * @param: struct fsocknode_ops *ops:   Socket operators.
 * @param: struct fsuper        *super: Filesystem superblock. */
#define _fsocknode_init(self, ops, super)                                                                               \
	(_fsocknode_assert_ops_(ops) _fnode_init_common(_fsocknode_asnode(self)),                                           \
	 atomic64_init(&(self)->_fsocknode_node_ _fnode_file_ mf_filesize, 0),                                              \
	 (self)->_fsocknode_node_ _fnode_file_ mf_parts             = MFILE_PARTS_ANONYMOUS,                                \
	 (self)->_fsocknode_node_ _fnode_file_ mf_changed.slh_first = MFILE_PARTS_ANONYMOUS,                                \
	 (self)->_fsocknode_node_ _fnode_file_ mf_flags = ((super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags &         \
	                                                   (MFILE_F_DELETED | MFILE_F_PERSISTENT |                          \
	                                                    MFILE_F_NOATIME | MFILE_F_NOMTIME)) |                           \
	                                                  MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |                        \
	                                                  MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO,                              \
	 (self)->_fsocknode_node_ _fnode_file_ mf_ops        = &(ops)->suno_node.no_file,                                   \
	 (self)->_fsocknode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 (self)->_fsocknode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_fsocknode_node_ _fnode_file_ mf_iobashift  = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_iobashift,  \
	 (self)->_fsocknode_node_ fn_super                   = incref(super),                                               \
	 unix_server_init(&(self)->sun_server))
#define _fsocknode_cinit(self, ops, super)                                                                              \
	(_fsocknode_assert_ops_(ops) _fnode_cinit_common(_fsocknode_asnode(self)),                                          \
	 atomic64_cinit(&(self)->_fsocknode_node_ _fnode_file_ mf_filesize, 0),                                             \
	 (self)->_fsocknode_node_ _fnode_file_ mf_parts             = MFILE_PARTS_ANONYMOUS,                                \
	 (self)->_fsocknode_node_ _fnode_file_ mf_changed.slh_first = MFILE_PARTS_ANONYMOUS,                                \
	 (self)->_fsocknode_node_ _fnode_file_ mf_flags = ((super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags &         \
	                                                   (MFILE_F_DELETED | MFILE_F_PERSISTENT |                          \
	                                                    MFILE_F_NOATIME | MFILE_F_NOMTIME)) |                           \
	                                                  MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |                        \
	                                                  MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO,                              \
	 (self)->_fsocknode_node_ _fnode_file_ mf_ops        = &(ops)->suno_node.no_file,                                   \
	 (self)->_fsocknode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 (self)->_fsocknode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_fsocknode_node_ _fnode_file_ mf_iobashift  = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_iobashift,  \
	 (self)->_fsocknode_node_ fn_super                   = incref(super),                                               \
	 unix_server_cinit(&(self)->sun_server))

/* Finalize a partially initialized `struct fsocknode' (as initialized by `_fsocknode_init()') */
#define _fsocknode_fini(self) decref_nokill((self)->_fsocknode_node_ fn_super)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_SOCKNODE_H */
