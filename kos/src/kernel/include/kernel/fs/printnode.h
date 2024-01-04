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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_PRINTNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_PRINTNODE_H 1

#include <kernel/compiler.h>

#include <kernel/fs/regnode.h>
#include <bits/crt/format-printer.h>
#include <kernel/types.h>

/*
 * Special sub-class for regular files: Printed Nodes
 *
 * These are special  files populated with  dynamically
 * printed file contents (by means of format-printing),
 * and are mainly used for the implementation of  /proc
 *
 * Printed nodes can be mmap'd, in which case mappings
 * are  dynamically initialized by means of the node's
 * content printer.
 *
 * The main purpose of these files however, is to  open
 * them  (which will produce a filehandle wrapper), and
 * then do a normal read, which will invoke `pno_print'
 * to  generate the file contents, completely bypassing
 * any I/O buffers (as are needed when using mmap)
 *
 * Also note that printed nodes don't have known file
 * sizes: the mfile size field is fixed at 2^64-1, and
 * using stat yields `0'
 *
 */

#ifdef __CC__
DECL_BEGIN

#ifndef __pformatprinter_defined
#define __pformatprinter_defined
typedef __pformatprinter pformatprinter;
typedef __pformatgetc pformatgetc;
typedef __pformatungetc pformatungetc;
#endif /* !__pformatprinter_defined */


struct printnode;
struct printnode_ops {
	struct fregnode_ops pno_reg; /* FNode operators */

	/* [1..1] Print the contents of this file to `printer'.
	 * @param: offset_hint: When non-zero, this specifies a  hint for the file  position
	 *                      starting at which data passed to `printer' becomes relevant.
	 *                      This is done such that `printer' will ignore and never deref
	 *                      the first `offset_hint' bytes of data it is passed,  meaning
	 *                      that you could do this:
	 *                      >> (*printer)(arg, (char *)1234, offset_hint);
	 *                      >> (*printer)(arg, "Foo", 3);
	 *                      and the kernel wouldn't crash. Like the name implies,  this
	 *                      is merely a hint, but can be used to speed up printing sub-
	 *                      strings  of  print-nodes in  cases where  (re-)printing the
	 *                      whole file would be unnecessary.
	 * NOTE: This callback is allowed to return as soon as `printer' returns a negative
	 *       value. Once `printer' has returned a negative value, further calls may  be
	 *       assumed to also return negative values. (iow: it's not necessary to  check
	 *       the return value after  every call) In this  regard, this function can  be
	 *       implemented a little more relaxed when compared to "normal" pformatprinter
	 *       conventions. */
	BLOCKING NONNULL_T((1, 2)) void
	(KCALL *pno_print)(struct printnode *__restrict self,
	                   pformatprinter printer, void *arg,
	                   pos_t offset_hint)
			THROWS(...);

	/* More operators would go here... */
};

struct printnode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fregnode               /* Underlying regular file */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fregnode pn_node; /* Underlying regular file */
#define _printnode_asreg(x) &(x)->pn_node
#define _printnode_reg_     pn_node.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _printnode_asreg(x) x
#define _printnode_reg_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
};

/* Return a pointer to regular-node operators of `self' */
#define printnode_getops(self) \
	((struct printnode_ops const *)__COMPILER_REQTYPE(struct printnode const *, self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_ops)
#define _printnode_assert_ops_(ops) \
	_fregnode_assert_ops_(&(ops)->pno_reg)


/* Helper macros */
#define fregnode_asprintnode(self) ((struct printnode *)(self))
#define fnode_asprintnode(self)    fregnode_asprintnode(fnode_asreg(self))
#define mfile_asprintnode(self)    fregnode_asprintnode(mfile_asreg(self))


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_atime
 *  - self->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_mtime
 *  - self->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_ctime
 *  - self->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_btime
 *  - self->_printnode_reg_ _fregnode_node_ fn_uid
 *  - self->_printnode_reg_ _fregnode_node_ fn_gid
 *  - self->_printnode_reg_ _fregnode_node_ fn_allnodes
 *  - self->_printnode_reg_ _fregnode_node_ fn_supent
 *  - self->_printnode_reg_ _fregnode_node_ fn_nlink
 *  - self->_printnode_reg_ _fregnode_node_ fn_ino
 *  - self->_printnode_reg_ _fregnode_node_ fn_mode (with something or'd with S_IFREG)
 * @param: struct printnode     *self:  Regular node to initialize.
 * @param: struct printnode_ops *ops:   Regular file operators.
 * @param: struct fsuper        *super: Filesystem superblock. */
#define _printnode_init(self, ops, super)                                                                                      \
	(_printnode_assert_ops_(ops) _fnode_init_common(_fregnode_asnode(_printnode_asreg(self))),                                 \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_parts             = MFILE_PARTS_ANONYMOUS,                        \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_changed.slh_first = MFILE_PARTS_ANONYMOUS,                        \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_flags = ((super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags & \
	                                                                  (MFILE_F_DELETED | MFILE_F_NOATIME | MFILE_F_NOMTIME)) | \
	                                                                 MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE,                 \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_ops        = &(ops)->pno_reg.rno_node.no_file,                    \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_blockshift = PAGESHIFT,                                           \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_iobashift  = 0,                                                   \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_part_amask = PAGEMASK,                                            \
	 atomic64_init(&(self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_filesize, (uint64_t)-1),                           \
	 (self)->_printnode_reg_ _fregnode_node_ fn_super = incref(super))
#define _printnode_cinit(self, ops, super)                                                                                     \
	(_printnode_assert_ops_(ops) _fnode_cinit_common(_fregnode_asnode(_printnode_asreg(self))),                                \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_parts             = MFILE_PARTS_ANONYMOUS,                        \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_changed.slh_first = MFILE_PARTS_ANONYMOUS,                        \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_flags = ((super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags & \
	                                                                  (MFILE_F_DELETED | MFILE_F_NOATIME | MFILE_F_NOMTIME)) | \
	                                                                 MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE,                 \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_ops        = &(ops)->pno_reg.rno_node.no_file,                    \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_blockshift = PAGESHIFT,                                           \
	 __hybrid_assert((self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_iobashift == 0),                                  \
	 (self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_part_amask = PAGEMASK,                                            \
	 atomic64_cinit(&(self)->_printnode_reg_ _fregnode_node_ _fnode_file_ mf_filesize, (uint64_t)-1),                          \
	 (self)->_printnode_reg_ _fregnode_node_ fn_super = incref(super))
/* Finalize a partially initialized `struct printnode' (as initialized by `_printnode_init()') */
#define _printnode_fini(self) decref_nokill((self)->_printnode_reg_ _fregnode_node_ fn_super)


/* Default operators for `struct printnode_ops' */
#define printnode_v_destroy fregnode_v_destroy
#define printnode_v_changed fregnode_v_changed
#define printnode_v_wrattr  fnode_v_wrattr_noop
#define printnode_v_ioctl   fregnode_v_ioctl
FUNDEF NONNULL((1)) void KCALL /* Writes `0' into `st_size' and `st_blocks' */
printnode_v_stat(struct mfile *__restrict self,
                 NCX struct stat *result)
		THROWS(E_SEGFAULT);
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL /* Populates `dst' via `pno_print' */
printnode_v_pread(struct mfile *__restrict self, NCX void *dst,
                  size_t num_bytes, pos_t addr, iomode_t mode)
		THROWS(E_SEGFAULT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
printnode_v_preadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst,
                   size_t num_bytes, pos_t addr, iomode_t mode)
		THROWS(E_SEGFAULT, ...);
DATDEF struct mfile_stream_ops const printnode_v_stream_ops;
FUNDEF BLOCKING NONNULL((1, 5)) void KCALL /* Populates `buf' via `pno_print' */
printnode_v_loadblocks(struct mfile *__restrict self, pos_t addr,
                       physaddr_t buf, size_t num_bytes,
                       struct aio_multihandle *__restrict aio)
		THROWS(...);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_PRINTNODE_H */
