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
#ifndef GUARD_KERNEL_INCLUDE_FS_FIFO_H
#define GUARD_KERNEL_INCLUDE_FS_FIFO_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <libbuffer/ringbuffer.h>

DECL_BEGIN

#ifdef __CC__

struct fifo_node;

struct fifo {
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
	 * >> close(READER) {
	 * >>     if (IS_READER) {
	 * >>         if (--ff_rdcnt == 0) // !atomic
	 * >>             sig_broadcast(&ff_buffer.rb_nfull);
	 * >>     }
	 * >>     if (IS_WRITER) {
	 * >>         if (--ff_wrcnt == 0) // !atomic
	 * >>             sig_broadcast(&ff_buffer.rb_nempty);
	 * >>     }
	 * >> }
	 *
	 */
	struct ringbuffer ff_buffer; /* The pipe's buffer. */
	WEAK refcnt_t     ff_rdcnt;  /* # of fifo readers (see above) */
	WEAK refcnt_t     ff_wrcnt;  /* # of fifo writers (see above) */
};
#define fifo_init(self)                   \
	(ringbuffer_init(&(self)->ff_buffer), \
	 (self)->ff_rdcnt = 0,                \
	 (self)->ff_wrcnt = 0)
#define fifo_fini(self) \
	ringbuffer_fini(&(self)->ff_buffer)

#ifdef CONFIG_BUILDING_KERNEL_CORE
/* Perform a generic HOP() operation for objects that point to FIFOs.
 * Called from:
 *    - HANDLE_TYPE_MFILE   (When describing a `struct fifo_node *')
 *    - HANDLE_TYPE_FILEHANDLE
 *    - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE
 *    - HANDLE_TYPE_FIFO_USER
 * This hop-backend implements command codes normally reserved for pipe
 * objects, thus allowing user-space to  make use of pipe hop  commands
 * with FIFO objects. */
INTDEF syscall_slong_t KCALL
fifo_hop(struct fifo_node *__restrict self, syscall_ulong_t cmd,
         USER UNCHECKED void *arg, iomode_t mode);
#endif /* CONFIG_BUILDING_KERNEL_CORE */



struct fifo_user {
	/* HANDLE:HANDLE_TYPE_FIFO_USER */
	WEAK refcnt_t               fu_refcnt;  /* Reference counter */
	REF struct fifo_node       *fu_fifo;    /* [1..1][const] The associated fifo. */
	REF struct path            *fu_path;    /* [0..1][const] The path from which `fr_fifo' was opened. */
	REF struct directory_entry *fu_dirent;  /* [0..1][const] The directory entry associated with `fr_fifo' that was used to open the fifo. */
	iomode_t                    fu_accmode; /* [const] Original I/O mode with which this fifo user was opened (masked by IO_ACCMODE). */
};

FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL fifo_user_destroy)(struct fifo_user *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct fifo_user, fu_refcnt, fifo_user_destroy)

/* Create a reader/writer for the given `pipe'
 * NOTE: If applicable, the caller should fill in `fu_path' and/or
 *       `fu_dirent'   directly   after  calling   this  function.
 * @param: iomode: Set of `IO_ACCMODE | IO_NONBLOCK'
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_OPEN_FIFO_WRITER_NO_READERS: [...] */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fifo_user *FCALL
fifo_user_create(struct fifo_node *__restrict self, iomode_t iomode)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_STATE);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_FS_FIFO_H */
