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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FIFONODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FIFONODE_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/node.h>
#include <kernel/types.h>

#include <kos/io.h>

#include <libbuffer/ringbuffer.h>

#ifdef __CC__
DECL_BEGIN

struct ffifonode;
struct ffifonode_ops {
	struct fnode_ops fno_node; /* FNode operators */
	/* More operators would go here... */
};

struct ffifonode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fnode                /* Underlying file-node */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fnode ff_node;  /* Underlying file-node */
#define _ffifonode_asnode(x) &(x)->ff_node
#define _ffifonode_node_     ff_node.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _ffifonode_asnode(x) x
#define _ffifonode_node_    /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	/* Fifo semantics for read/write/open/close:
	 *
	 * >> open() {
	 * >>     if ((mode & O_ACCMODE) == O_RDONLY) {
	 * >>         for (;;) {
	 * >>             if (ff_wrcnt != 0)
	 * >>                 break;
	 * >>             if (mode & O_NONBLOCK)
	 * >>                 break;
	 * >>             task_connect_for_poll(&ff_buffer.rb_nempty);
	 * >>             if (ff_wrcnt != 0)
	 * >>                 break;
	 * >>             task_waitfor();
	 * >>         }
	 * >>         CREATE_READER();
	 * >>         if (++ff_rdcnt == 1) // atomic!
	 * >>             sig_broadcast(&ff_buffer.rb_nfull);
	 * >>     } else if ((mode & O_ACCMODE) == O_WRONLY) {
	 * >>         for (;;) {
	 * >>             if (ff_rdcnt != 0)
	 * >>                 break;
	 * >>             if (mode & O_NONBLOCK)
	 * >>                 THROW(ERROR_FOR(ENXIO));
	 * >>             task_connect_for_poll(&ff_buffer.rb_nfull);
	 * >>             if (ff_rdcnt != 0)
	 * >>                 break;
	 * >>             task_waitfor();
	 * >>         }
	 * >>         CREATE_WRITER();
	 * >>         if (++ff_wrcnt == 1) // atomic!
	 * >>             sig_broadcast(&ff_buffer.rb_nempty);
	 * >>     } else {
	 * >>         CREATE_READ_WRITE();
	 * >>         if (++ff_rdcnt == 1) // atomic!
	 * >>             sig_broadcast(&ff_buffer.rb_nfull);
	 * >>         if (++ff_wrcnt == 1) // atomic!
	 * >>             sig_broadcast(&ff_buffer.rb_nempty);
	 * >>     }
	 * >> }
	 *
	 * >> read() {
	 * >> again:
	 * >>     TRYREAD();
	 * >>     if (did_read_something)
	 * >>         return;
	 * >>     if (!ff_wrcnt)
	 * >>         return 0; // EOF
	 * >>     if (iomode & IO_NONBLOCK)
	 * >>         return -EWOULDBLOCK;
	 * >>     task_connect(&ff_buffer.rb_nempty);
	 * >>     TRYREAD();
	 * >>     if (did_read_something)
	 * >>         return;
	 * >>     if (!ff_wrcnt)
	 * >>         return 0; // EOF
	 * >>     task_waitfor(); // Wait for more data, or all writers to disconnect
	 * >>     goto again;
	 * >> }
	 *
	 * >> write() {
	 * >> again:
	 * >>     if (!ff_rdcnt) {
	 * >> no_readers:
	 * >>         raise(SIGPIPE);
	 * >>         return -EPIPE;
	 * >>     }
	 * >>     TRYWRITE();
	 * >>     if (did_write_something)
	 * >>         return;
	 * >>     if (iomode & IO_NONBLOCK)
	 * >>         return -EWOULDBLOCK;
	 * >>     if (!ff_rdcnt)
	 * >>         goto no_readers;
	 * >>     task_connect(&ff_buffer.rb_nfull);
	 * >>     TRYWRITE();
	 * >>     if (did_write_something)
	 * >>         return;
	 * >>     if (!ff_rdcnt)
	 * >>         goto no_readers;
	 * >>     task_waitfor(); // Wait for more data, or all writers to disconnect
	 * >>     goto again;
	 * >> }
	 *
	 *
	 * >> close() {
	 * >>     if (IS_READER) {
	 * >>         if (--ff_rdcnt == 0) // !atomic
	 * >>             sig_broadcast(&ff_buffer.rb_nfull);
	 * >>     }
	 * >>     if (IS_WRITER) {
	 * >>         if (--ff_wrcnt == 0) // !atomic
	 * >>             sig_broadcast(&ff_buffer.rb_nempty);
	 * >>     }
	 * >> }
	 */
	struct ringbuffer ff_buffer; /* The pipe's buffer. */
	WEAK refcnt_t     ff_rdcnt;  /* [lock(ATOMIC)] # of fifo readers (see above) */
	WEAK refcnt_t     ff_wrcnt;  /* [lock(ATOMIC)] # of fifo writers (see above) */
};


/* Return a pointer to fifoice-node operators of `self' */
#define ffifonode_getops(self) \
	((struct ffifonode_ops const *)__COMPILER_REQTYPE(struct ffifonode const *, self)->_ffifonode_node_ _fnode_file_ mf_ops)
#define _ffifonode_assert_ops_(ops) \
	_fnode_assert_ops_(&(ops)->fno_node)

struct path;
struct fdirent;
struct handle;

/* Default operator for opening ffifonode files. This will construct
 * a  `struct fifo_user' (HANDLE_TYPE_FIFO_USER) object and write it
 * back to `hand'. */
FUNDEF NONNULL((1, 2)) void KCALL
ffifonode_v_open(struct mfile *__restrict self,
                 struct handle *__restrict hand,
                 struct path *access_path,
                 struct fdirent *access_dent)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_STATE);
FUNDEF WUNUSED NONNULL((1)) size_t KCALL
ffifonode_v_read(struct mfile *__restrict self, USER CHECKED void *dst,
                 size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL
ffifonode_v_readv(struct mfile *__restrict self, struct iov_buffer *__restrict dst,
                  size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF WUNUSED NONNULL((1)) size_t KCALL
ffifonode_v_write(struct mfile *__restrict self, USER CHECKED void const *src,
                  size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL
ffifonode_v_writev(struct mfile *__restrict self, struct iov_buffer *__restrict src,
                   size_t num_bytes, iomode_t mode) THROWS(...);
/* Does `ringbuffer_setwritten()' */
FUNDEF NONNULL((1)) void KCALL
ffifonode_v_truncate(struct mfile *__restrict self, pos_t new_size)
		THROWS(...);
/* Fills in `st_size' with `mfile_asfifo(self)->ff_buffer.rb_avail' */
FUNDEF NONNULL((1)) void KCALL
ffifonode_v_stat(struct mfile *__restrict self,
                 USER CHECKED struct stat *result)
		THROWS(...);
/* Implements some `HOP_PIPE_OPEN_*' commands */
FUNDEF NONNULL((1)) syscall_slong_t KCALL
ffifonode_v_hop(struct mfile *__restrict self, syscall_ulong_t cmd,
                USER UNCHECKED void *arg, iomode_t mode)
		THROWS(...);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ffifonode_v_destroy)(struct mfile *__restrict self);


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_ffifonode_node_ _fnode_file_ mf_atime
 *  - self->_ffifonode_node_ _fnode_file_ mf_mtime
 *  - self->_ffifonode_node_ _fnode_file_ mf_ctime
 *  - self->_ffifonode_node_ fn_uid
 *  - self->_ffifonode_node_ fn_gid
 *  - self->_ffifonode_node_ fn_allnodes
 *  - self->_ffifonode_node_ fn_supent
 *  - self->_ffifonode_node_ fn_nlink
 *  - self->_ffifonode_node_ fn_ino
 *  - self->_ffifonode_node_ fn_mode (with something or'd with S_IFIFO)
 * @param: struct ffifonode     *self:  Regular node to initialize.
 * @param: struct ffifonode_ops *ops:   Regular file operators.
 * @param: struct fsuper        *super: Filesystem superblock. */
#define _ffifonode_init(self, ops, super)                                                                               \
	(_ffifonode_assert_ops_(ops) _fnode_init_common(_ffifonode_asnode(self)),                                           \
	 atomic64_init(&(self)->_ffifonode_node_ _fnode_file_ mf_filesize, 0),                                              \
	 (self)->_ffifonode_node_ _fnode_file_ mf_parts = MFILE_PARTS_ANONYMOUS,                                            \
	 (self)->_ffifonode_node_ _fnode_file_ mf_flags = ((super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags &         \
	                                                   (MFILE_F_DELETED | MFILE_F_PERSISTENT |                          \
	                                                    MFILE_F_NOATIME | MFILE_F_NOMTIME)) |                           \
	                                                  MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |                        \
	                                                  MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO,                              \
	 (self)->_ffifonode_node_ _fnode_file_ mf_ops        = &(ops)->fno_node.no_file,                                    \
	 (self)->_ffifonode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_ffifonode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 (self)->_ffifonode_node_ fn_super                   = incref(super),                                               \
	 ringbuffer_init(&(self)->ff_buffer),                                                                               \
	 (self)->ff_rdcnt = 0,                                                                                              \
	 (self)->ff_wrcnt = 0)
#define _ffifonode_cinit(self, ops, super)                                                                              \
	(_ffifonode_assert_ops_(ops) _fnode_cinit_common(_ffifonode_asnode(self)),                                          \
	 atomic64_cinit(&(self)->_ffifonode_node_ _fnode_file_ mf_filesize, 0),                                             \
	 (self)->_ffifonode_node_ _fnode_file_ mf_parts = MFILE_PARTS_ANONYMOUS,                                            \
	 (self)->_ffifonode_node_ _fnode_file_ mf_flags = ((super)->fs_root._fdirnode_node_ _fnode_file_ mf_flags &         \
	                                                   (MFILE_F_DELETED | MFILE_F_PERSISTENT |                          \
	                                                    MFILE_F_NOATIME | MFILE_F_NOMTIME)) |                           \
	                                                  MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |                        \
	                                                  MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO,                              \
	 (self)->_ffifonode_node_ _fnode_file_ mf_ops        = &(ops)->fno_node.no_file,                                    \
	 (self)->_ffifonode_node_ _fnode_file_ mf_blockshift = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift, \
	 (self)->_ffifonode_node_ _fnode_file_ mf_part_amask = (super)->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask, \
	 (self)->_ffifonode_node_ fn_super                   = incref(super),                                               \
	 ringbuffer_cinit(&(self)->ff_buffer),                                                                              \
	 __hybrid_assert((self)->ff_rdcnt == 0),                                                                            \
	 __hybrid_assert((self)->ff_wrcnt == 0))

/* Finalize a partially initialized `struct ffifonode' (as initialized by `_ffifonode_init()') */
#define _ffifonode_fini(self) decref_nokill((self)->_ffifonode_node_ fn_super)




struct fifo_user {
	/* HANDLE:HANDLE_TYPE_FIFO_USER */
	WEAK refcnt_t         fu_refcnt;  /* Reference counter */
	REF struct ffifonode *fu_fifo;    /* [1..1][const] The associated fifo. */
	REF struct path      *fu_path;    /* [0..1][const] The path from which `fr_fifo' was opened. */
	REF struct fdirent   *fu_dent;    /* [0..1][const] The directory entry associated with `fr_fifo' that was used to open the fifo. */
	iomode_t              fu_accmode; /* [const] Original I/O mode with which this fifo user was opened (masked by IO_ACCMODE). */
};

FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL fifo_user_destroy)(struct fifo_user *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct fifo_user, fu_refcnt, fifo_user_destroy)

/* Create a reader/writer for the given fifo `self'
 * NOTE: If  applicable,  the caller  should fill  in `fu_path'
 *       and/or `fu_dent' directly after calling this function.
 * @param: iomode: Set of `IO_ACCMODE | IO_NONBLOCK' (other bits are silently ignored)
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_OPEN_FIFO_WRITER_NO_READERS: [...] */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fifo_user *FCALL
fifo_user_create(struct ffifonode *__restrict self, iomode_t iomode,
                 struct path *access_path, struct fdirent *access_dent)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_STATE);


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FIFONODE_H */
