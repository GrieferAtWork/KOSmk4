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
#ifndef GUARD_KERNEL_CORE_FILESYS_FIFOHANDLE_C
#define GUARD_KERNEL_CORE_FILESYS_FIFOHANDLE_C 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/fifohandle.h>
#include <kernel/fs/fifonode.h>
#include <kernel/fs/notify.h>
#include <kernel/fs/path.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <sched/cred.h>
#include <sched/rpc.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <kos/except/reason/illop.h>
#include <kos/kernel/handle.h> /* HANDLE_TYPE_FIFOHANDLE */
#include <sys/stat.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

/************************************************************************/
/* HANDLE_TYPE_FIFOHANDLE                                                */
/************************************************************************/
DEFINE_HANDLE_REFCNT_FUNCTIONS(fifohandle, struct fifohandle);

/* Handle operators */
INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_fifohandle_read(struct fifohandle *__restrict self, USER CHECKED void *dst,
                       size_t num_bytes, iomode_t mode) THROWS(...) {
	return ffifonode_v_read(self->fu_fifo, dst, num_bytes, mode);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_fifohandle_write(struct fifohandle *__restrict self, USER CHECKED void const *src,
                        size_t num_bytes, iomode_t mode) THROWS(...) {
	return ffifonode_v_write(self->fu_fifo, src, num_bytes, mode);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_fifohandle_readv(struct fifohandle *__restrict self,
                        struct iov_buffer *__restrict dst,
                        size_t num_bytes, iomode_t mode) THROWS(...) {
	return ffifonode_v_readv(self->fu_fifo, dst, num_bytes, mode);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_fifohandle_writev(struct fifohandle *__restrict self,
                         struct iov_buffer *__restrict src,
                         size_t num_bytes, iomode_t mode) THROWS(...) {
	return ffifonode_v_writev(self->fu_fifo, src, num_bytes, mode);
}

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_fifohandle_ioctl(struct fifohandle *__restrict self, ioctl_t cmd,
                        USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	return mfile_uioctl(self->fu_fifo, cmd, arg, mode);
}

INTERN NONNULL((1)) void KCALL
handle_fifohandle_truncate(struct fifohandle *__restrict self,
                           pos_t new_size) THROWS(...) {
	ffifonode_v_truncate(self->fu_fifo, new_size);
}

INTERN NONNULL((1)) void KCALL
handle_fifohandle_stat(struct fifohandle *__restrict self,
                       USER CHECKED struct stat *result) THROWS(...) {
	mfile_ustat(self->fu_fifo, result);
}

INTERN NONNULL((1)) void KCALL
handle_fifohandle_pollconnect(struct fifohandle *__restrict self,
                              poll_mode_t what) THROWS(...) {
	struct ringbuffer *rb = &self->fu_fifo->ff_buffer;
	if (what & POLLINMASK)
		ringbuffer_pollconnect_read(rb);
	if (what & POLLOUTMASK)
		ringbuffer_pollconnect_write(rb);
}

INTERN WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_fifohandle_polltest(struct fifohandle *__restrict self,
                           poll_mode_t what) {
	poll_mode_t result = 0;
	struct ringbuffer *rb = &self->fu_fifo->ff_buffer;
	if ((what & POLLINMASK) && ringbuffer_canread(rb))
		result |= POLLINMASK;
	if ((what & POLLOUTMASK) && ringbuffer_canwrite(rb))
		result |= POLLOUTMASK;
	return result;
}

INTERN NONNULL((1)) REF void *KCALL
handle_fifohandle_tryas(struct fifohandle *__restrict self,
                        uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	switch (wanted_type) {
	case HANDLE_TYPE_MFILE: return incref(self->fu_fifo);
	case HANDLE_TYPE_DIRENT: return xincref(self->fu_dirent);
	case HANDLE_TYPE_PATH: return xincref(self->fu_path);
	default: break;
	}
	return mfile_utryas(self->fu_fifo, wanted_type);
}


/* Object destructor */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fifohandle_destroy)(struct fifohandle *__restrict self) {
	REF struct ffifonode *fifo;
	fifo = self->fu_fifo;
	if (IO_CANREAD(self->fu_accmode)) {
		if (ATOMIC_FETCHDEC(fifo->ff_rdcnt) == 1)
			sig_broadcast(&fifo->ff_buffer.rb_nfull);
	}
	if (IO_CANWRITE(self->fu_accmode)) {
		if (ATOMIC_FETCHDEC(fifo->ff_wrcnt) == 1)
			sig_broadcast(&fifo->ff_buffer.rb_nempty);
		mfile_inotify_closewr(self->fu_fifo); /* Post `IN_CLOSE_WRITE' */
	} else {
		mfile_inotify_closero(self->fu_fifo); /* Post `IN_CLOSE_NOWRITE' */
	}
	decref(fifo);
	xdecref(self->fu_dirent);
	xdecref(self->fu_path);
	kfree(self);
}

/* Create a reader/writer for the given fifo `self'
 * NOTE: If  applicable,  the  caller  should  fill  in `fu_path'
 *       and/or `fu_dirent' directly after calling this function.
 * @param: iomode: Set of `IO_ACCMODE | IO_NONBLOCK' (other bits are silently ignored)
 * @throw: E_ILLEGAL_IO_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_OPEN_FIFO_WRITER_WITHOUT_READERS: [...] */
PUBLIC BLOCKING ATTR_MALLOC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fifohandle *FCALL
fifohandle_new(struct ffifonode *__restrict self, iomode_t iomode,
               struct path *access_path, struct fdirent *access_dent)
		THROWS(E_BADALLOC, E_ILLEGAL_IO_OPERATION, ...) {
	REF struct fifohandle *result;
	assert(!task_wasconnected());
	result = (REF struct fifohandle *)kmalloc(sizeof(struct fifohandle),
	                                          GFP_NORMAL);
	/* Register a new reader/writer/both */
	TRY {
		switch (iomode & IO_ACCMODE) {

		case IO_RDONLY:
			for (;;) {
				if (ATOMIC_READ(self->ff_wrcnt) != 0)
					break;
				/* Opening a fifo as non-blocking for reading always succeeds. */
				if (iomode & IO_NONBLOCK)
					break;
				task_connect_for_poll(&self->ff_buffer.rb_nempty);
				if (ATOMIC_READ(self->ff_wrcnt) != 0) {
					task_disconnectall();
					break;
				}
				/* Wait for writers to show up */
				task_waitfor();
			}
			if (ATOMIC_FETCHINC(self->ff_rdcnt) == 0)
				sig_broadcast(&self->ff_buffer.rb_nfull);
			break;

		case IO_WRONLY:
			for (;;) {
				if (ATOMIC_READ(self->ff_rdcnt) != 0)
					break;
				/* POSIX says that without any readers, opening a FIFO in
				 * non-block mode should have us throw some kind of error
				 * that will result in `ENXIO' */
				if (iomode & IO_NONBLOCK) {
					THROW(E_ILLEGAL_IO_OPERATION,
					      E_ILLEGAL_OPERATION_CONTEXT_OPEN_FIFO_WRITER_WITHOUT_READERS);
				}
				task_connect_for_poll(&self->ff_buffer.rb_nfull);
				if (ATOMIC_READ(self->ff_rdcnt) != 0) {
					task_disconnectall();
					break;
				}
				/* Wait for readers to show up */
				task_waitfor();
			}
			if (ATOMIC_FETCHINC(self->ff_wrcnt) == 0)
				sig_broadcast(&self->ff_buffer.rb_nempty);
			break;

		default:
			if (ATOMIC_FETCHINC(self->ff_rdcnt) == 0)
				sig_broadcast(&self->ff_buffer.rb_nfull);
			if (ATOMIC_FETCHINC(self->ff_wrcnt) == 0)
				sig_broadcast(&self->ff_buffer.rb_nempty);
			break;
		}
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Fill in fields of the new FIFO user object. */
	result->fu_refcnt  = 1;
	result->fu_fifo    = (REF struct ffifonode *)incref(self);
	result->fu_accmode = iomode & IO_ACCMODE;
	result->fu_path    = xincref(access_path);
	result->fu_dirent  = xincref(access_dent);
	mfile_inotify_opened(result->fu_fifo); /* Post `IN_OPEN' */
	return result;
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_FIFOHANDLE_C */
