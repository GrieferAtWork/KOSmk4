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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_LNKNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_LNKNODE_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/node.h>
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

struct path;
struct handle;
struct fdirent;
struct flnknode;

struct flnknode_ops {
	struct fnode_ops lno_node; /* FNode operators */

	/* [1..1] Copy the symlink text of a link-node into the given buffer.
	 * NOTE: When `lno_linkstr' is implemented, this function may simply
	 *       be assigned as  `&flnknode_v_readlink_default', which  uses
	 *       the alternate operator in order to implement this one.
	 * NOTE: No trailing NUL character is written by this function.
	 * @return: * : The required buffer size. (EXCLUDING a terminating NUL-character)
	 * @throw: E_SEGFAULT: The given user-buffer is faulty.
	 * @throw: E_IOERROR:  Failed to read data from disk. */
	WUNUSED NONNULL((1)) size_t
	(KCALL *lno_readlink)(struct flnknode *__restrict self,
	                      USER CHECKED /*utf-8*/ char *buf,
	                      size_t bufsize)
			THROWS(E_SEGFAULT, E_IOERROR, ...);

	/* [0..1] Helper function to (possibly lazily) load the link text of `self'
	 *        into the kernel and return a pointer to the NUL-terminated string
	 *        representing the link's text. The returned pointer remains  valid
	 *        until  `self' is eventually destroyed (iow: as long as the caller
	 *        maintains their reference to `self')
	 *
	 * Following a call to this function, the returned string's length can be read
	 * from  `self->_flnknode_node_ _fnode_file_ mf_filesize',  which  was  either
	 * already initialized, or will have  been initialized by this function.  Note
	 * that in  this respect,  this function  differs from  `lno_readlink',  which
	 * doesn't  impose any requirements on the value of `mf_filesize', but instead
	 * returns the required buffer size (which is equal to what this function must
	 * write to `mf_filesize') directly.
	 *
	 * NOTE: Following the lazy initialization done by this function, `mf_filesize'
	 *       becomes [const], meaning that for  flnknode files, that field must  be
	 *       considered    `[lock(WRITE_ONCE)][valid_if(WAS_CALLED(lno_linkstr))]'.
	 *       Also, the `mf_trunclock' field is `[valid_if(false)]'.
	 *
	 * This operator is optional and need not necessarily be implemented, but
	 * if implemented, it must never return `NULL'! */
	/*ATTR_PURE*/ ATTR_RETNONNULL WUNUSED NONNULL((1)) char const *
	(KCALL *lno_linkstr)(struct flnknode *__restrict self)
			THROWS(E_IOERROR, E_BADALLOC, ...);

	/* [0..1] Optional helper function that is used when open(2) is called with
	 *        this  symbolic link being the last component of the given path.
	 *        When this operator returns `false', the behavior is the same as
	 *        when it isn't provided at all.
	 * This function should fill `result->h_data' and `result->h_type' with the
	 * object which should be opened if the link `self' were dereferenced. When
	 * this operator isn't implement or returns `false', use `lno_linkstr'  and
	 * `lno_readlink'  to do a  normal filesystem path walk  to follow the link
	 * contents.
	 *
	 * This operator is mainly needed to implement the special dup()-behavior
	 * of `open("/proc/[pid]/fd/[no]")' */
	WUNUSED NONNULL((1, 2, 3, 4)) __BOOL
	(KCALL *lno_openlink)(struct flnknode *__restrict self,
	                      struct handle *__restrict result,
	                      struct path *__restrict access_path,
	                      struct fdirent *__restrict access_dent)
			THROWS(E_IOERROR, E_BADALLOC, ...);
};


/* Default implementation for  `flnknode_ops::lno_readlink' that may  be used  when
 * the alternate `lno_linkstr' operator is implemented, in which case said operator
 * is invoked before the returned string is copied into the supplied buffer. */
FUNDEF WUNUSED NONNULL((1)) size_t KCALL
flnknode_v_readlink_default(struct flnknode *__restrict self,
                            USER CHECKED /*utf-8*/ char *buf,
                            size_t bufsize)
			THROWS(E_SEGFAULT, E_IOERROR, ...);


struct flnknode
#ifdef __cplusplus
    : fnode                          /* Underlying file-node */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct fnode         ln_node;    /* Underlying file-node */
#define _flnknode_node_     ln_node.
#define _flnknode_asnode(x) &(x)->ln_node
#else /* !__cplusplus */
#define _flnknode_node_     /* nothing */
#define _flnknode_asnode(x) x
#endif /* __cplusplus */
};


/* Return a pointer to link-node operators of `self' */
#define flnknode_getops(self)                                                                                       \
	__COMPILER_CONTAINER_OF(__COMPILER_REQTYPE(struct flnknode const *, self)->_flnknode_node_ _fnode_file_ mf_ops, \
	                        struct flnknode_ops, lno_node.no_file)
#define _flnknode_assert_ops_(ops) \
	_fnode_assert_ops_(&(ops)->lno_node)


/* Helper wrappers for invocation of flnknode operators. */
#define flnknode_readlink(self, buf, bufsize) \
	((*flnknode_getops(self)->lno_readlink)(self, buf, bufsize))
#define flnknode_haslinkstr(self) (flnknode_getops(self)->lno_linkstr != __NULLPTR) /* Check if available */
#define flnknode_getlinkstr(self) ((*flnknode_getops(self)->lno_linkstr)(self))     /* Return link string */
#define flnknode_getlinklen(self) (__COMPILER_READ_BARRIER(), (size_t)__atomic64_val((self)->_flnknode_node_ _fnode_file_ mf_filesize))



/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_flnknode_node_ _fnode_file_ mf_filesize
 *  - self->_flnknode_node_ _fnode_file_ mf_atime
 *  - self->_flnknode_node_ _fnode_file_ mf_mtime
 *  - self->_flnknode_node_ _fnode_file_ mf_ctime
 *  - self->_flnknode_node_ fn_uid
 *  - self->_flnknode_node_ fn_gid
 *  - self->_flnknode_node_ fn_allnodes
 *  - self->_flnknode_node_ fn_supent
 *  - self->_flnknode_node_ fn_nlink
 *  - self->_flnknode_node_ fn_ino
 *  - self->_flnknode_node_ fn_mode (with something or'd with S_IFLNK)
 * @param: struct flnknode     *self:   Directory node to initialize.
 * @param: struct flnknode_ops *ops:    Directory operators.
 * @param: struct fsuper       *super:  Filesystem superblock. */
#define _flnknode_init(self, ops, super)                                                                       \
	(_flnknode_assert_ops_(ops) _fnode_init_common(_flnknode_asnode(self)),                                    \
	 (self)->_flnknode_node_ _fnode_file_ mf_parts = MFILE_PARTS_ANONYMOUS,                                    \
	 (self)->_flnknode_node_ _fnode_file_ mf_flags = ((super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags & \
	                                                  (MFILE_F_DELETED | MFILE_F_PERSISTENT |                  \
	                                                   MFILE_F_NOATIME | MFILE_F_NOMTIME)) |                   \
	                                                 MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |                \
	                                                 MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO,                      \
	 (self)->_flnknode_node_ _fnode_file_ mf_ops        = &(ops)->lno_node.no_file,                            \
	 (self)->_flnknode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fnode_file_ mf_blockshift,         \
	 (self)->_flnknode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fnode_file_ mf_part_amask,         \
	 (self)->_flnknode_node_ fn_super                   = incref(super))
#define _flnknode_cinit(self, ops, super)                                                                      \
	(_flnknode_assert_ops_(ops) _fnode_cinit_common(_flnknode_asnode(self)),                                   \
	 (self)->_flnknode_node_ _fnode_file_ mf_parts = MFILE_PARTS_ANONYMOUS,                                    \
	 (self)->_flnknode_node_ _fnode_file_ mf_flags = ((super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags & \
	                                                  (MFILE_F_DELETED | MFILE_F_PERSISTENT |                  \
	                                                   MFILE_F_NOATIME | MFILE_F_NOMTIME)) |                   \
	                                                 MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |                \
	                                                 MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO,                      \
	 (self)->_flnknode_node_ _fnode_file_ mf_ops        = &(ops)->lno_node.no_file,                            \
	 (self)->_flnknode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fnode_file_ mf_blockshift,         \
	 (self)->_flnknode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fnode_file_ mf_part_amask,         \
	 (self)->_flnknode_node_ fn_super                   = incref(super))

/* Finalize a partially initialized `struct flnknode' (as initialized by `_flnknode_init()') */
#define _flnknode_fini(self) \
	(decref_nokill((self)->_flnknode_node_ fn_super))

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_LNKNODE_H */
