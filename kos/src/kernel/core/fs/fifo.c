/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FS_SPECIAL_FIFO_C
#define GUARD_KERNEL_CORE_FS_SPECIAL_FIFO_C 1

#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <fs/fifo.h>
#include <fs/node.h>
#include <fs/special-node.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <sched/posix-signal.h>
#include <sched/signal.h>

#include <hybrid/atomic.h>

#include <kos/except/inval.h>
#include <sys/stat.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

DEFINE_HANDLE_REFCNT_FUNCTIONS(fifo_user, struct fifo_user)

#define fifo_buffer(user) (&(user)->fu_fifo->f_fifo.ff_buffer)


INTDEF WUNUSED NONNULL((1)) size_t KCALL
handle_fifo_user_read(struct fifo_user *__restrict self,
                      USER CHECKED void *dst,
                      size_t num_bytes, iomode_t mode)
		THROWS(...) {
	size_t result;
	struct fifo_node *fifo = self->fu_fifo;
again:
	result = ringbuffer_read_nonblock(&fifo->f_fifo.ff_buffer,
	                                  dst, num_bytes);
	if (!result) {
		if unlikely(!num_bytes)
			goto done;
		/* Buffer is empty. */
		if (!ATOMIC_READ(fifo->f_fifo.ff_wrcnt))
			goto done; /* End-of-file */
		if (mode & IO_NONBLOCK) {
			if (!(mode & IO_NODATAZERO))
				THROW(E_WOULDBLOCK_WAITFORSIGNAL); /* No space available. */
			goto done;
		}
		task_connect(&fifo->f_fifo.ff_buffer.rb_nempty);
		/* Retry reading data, now that we're being interlocked. */
		result = ringbuffer_read_nonblock(&fifo->f_fifo.ff_buffer,
		                                  dst, num_bytes);
		if unlikely(result) {
			task_disconnectall();
			goto done;
		}
		/* Check if these are still readers out there. */
		if unlikely(!ATOMIC_READ(fifo->f_fifo.ff_wrcnt)) {
			task_disconnectall();
			goto done; /* End-of-file */
		}
		/* Wait for more data to arrive. */
		task_waitfor();
		goto again;
	}
done:
	return result;
}

INTDEF WUNUSED NONNULL((1)) size_t KCALL
handle_fifo_user_write(struct fifo_user *__restrict self,
                       USER CHECKED void const *src,
                       size_t num_bytes, iomode_t mode)
		THROWS(...) {
	size_t result;
	struct fifo_node *fifo = self->fu_fifo;
again:
	if (!ATOMIC_READ(fifo->f_fifo.ff_rdcnt)) {
no_readers:
		/* Posix requires that we raise(SIGPIPE) in this scenario... */
		task_raisesignalthread(THIS_TASK, SIGPIPE);
		/* If SIGPIPE is being ignored, we must instead throw some
		 * exception that causes user-space to set errno=EPIPE. */
		THROW(E_INVALID_ARGUMENT_BAD_STATE,
			  E_INVALID_ARGUMENT_CONTEXT_WRITE_FIFO_NO_READERS);
	}
	result = ringbuffer_write_nonblock(&fifo->f_fifo.ff_buffer,
	                                   src, num_bytes);
	if (!result) {
		if unlikely(!num_bytes)
			goto done;
		/* Buffer is full. */
		if (mode & IO_NONBLOCK) {
			if (!(mode & IO_NODATAZERO))
				THROW(E_WOULDBLOCK_WAITFORSIGNAL); /* No space available. */
			goto done;
		}
		if (!ATOMIC_READ(fifo->f_fifo.ff_rdcnt))
			goto no_readers;
		task_connect(&fifo->f_fifo.ff_buffer.rb_nfull);
		/* Retry writing data, now that we're being interlocked. */
		result = ringbuffer_write_nonblock(&fifo->f_fifo.ff_buffer,
		                                   src, num_bytes);
		if unlikely(result) {
			task_disconnectall();
			goto done;
		}
		/* Check if these are still readers out there. */
		if unlikely(!ATOMIC_READ(fifo->f_fifo.ff_rdcnt)) {
			task_disconnectall();
			goto no_readers;
		}
		/* Wait for space to become available. */
		task_waitfor();
		goto again;
	}
done:
	return result;
}

INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL
handle_fifo_user_readv(struct fifo_user *__restrict self,
                       struct aio_buffer *__restrict dst,
                       size_t num_bytes, iomode_t mode)
		THROWS(...) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	struct fifo_node *fifo = self->fu_fifo;
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
again_read_ent:
		temp = ringbuffer_read_nonblock(&fifo->f_fifo.ff_buffer,
		                                ent.ab_base,
		                                ent.ab_size);
		result += temp;
		if (temp < ent.ab_size) {
			/* Buffer is empty. */
			if (result)
				break;
			if (mode & IO_NONBLOCK) {
				if (!(mode & IO_NODATAZERO))
					THROW(E_WOULDBLOCK_WAITFORSIGNAL); /* No space available. */
				break;
			}
			if (!ATOMIC_READ(fifo->f_fifo.ff_wrcnt))
				break; /* End-of-file */
			task_connect(&fifo->f_fifo.ff_buffer.rb_nempty);
			/* Retry reading data, now that we're being interlocked. */
			temp = ringbuffer_read_nonblock(&fifo->f_fifo.ff_buffer,
			                                ent.ab_base,
			                                ent.ab_size);
			if unlikely(temp) {
				task_disconnectall();
				result += temp;
				if (temp == ent.ab_size)
					continue; /* Write further segments. */
				break;
			}
			/* Check if these are still readers out there. */
			if unlikely(!ATOMIC_READ(fifo->f_fifo.ff_wrcnt)) {
				task_disconnectall();
				break; /* End-of-file */
			}
			/* Wait for more data to arrive. */
			task_waitfor();
			goto again_read_ent;
		}
	}
	return result;
}


INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL
handle_fifo_user_writev(struct fifo_user *__restrict self,
                        struct aio_buffer *__restrict src,
                        size_t num_bytes, iomode_t mode)
		THROWS(...) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	struct fifo_node *fifo = self->fu_fifo;
	(void)num_bytes;
	if (!ATOMIC_READ(fifo->f_fifo.ff_rdcnt)) {
no_readers:
		/* Posix requires that we raise(SIGPIPE) in this scenario... */
		task_raisesignalthread(THIS_TASK, SIGPIPE);
		/* If SIGPIPE is being ignored, we must instead throw some
		 * exception that causes user-space to set errno=EPIPE. */
		THROW(E_INVALID_ARGUMENT_BAD_STATE,
			  E_INVALID_ARGUMENT_CONTEXT_WRITE_FIFO_NO_READERS);
	}
	AIO_BUFFER_FOREACH(ent, src) {
again_write_ent:
		temp = ringbuffer_write_nonblock(&fifo->f_fifo.ff_buffer,
		                                 ent.ab_base,
		                                 ent.ab_size);
		result += temp;
		if (temp < ent.ab_size) {
			/* Buffer is full. */
			if (result)
				break;
			if (mode & IO_NONBLOCK) {
				if (!(mode & IO_NODATAZERO))
					THROW(E_WOULDBLOCK_WAITFORSIGNAL); /* No space available. */
				break;
			}
			if (!ATOMIC_READ(fifo->f_fifo.ff_rdcnt))
				goto no_readers;
			task_connect(&fifo->f_fifo.ff_buffer.rb_nfull);
			/* Retry writing data, now that we're being interlocked. */
			temp = ringbuffer_write_nonblock(&fifo->f_fifo.ff_buffer,
			                                 ent.ab_base,
			                                 ent.ab_size);
			if unlikely(temp) {
				task_disconnectall();
				result += temp;
				if (temp == ent.ab_size)
					continue; /* Write further segments. */
				break;
			}
			/* Check if these are still readers out there. */
			if unlikely(!ATOMIC_READ(fifo->f_fifo.ff_rdcnt)) {
				task_disconnectall();
				goto no_readers;
			}
			/* Wait for space to become available. */
			task_waitfor();
			/* Verify that there are still readers. */
			if unlikely(!ATOMIC_READ(fifo->f_fifo.ff_rdcnt))
				goto no_readers;
			goto again_write_ent;
		}
	}
	return result;
}

INTDEF NONNULL((1)) void KCALL
handle_fifo_user_truncate(struct fifo_user *__restrict self,
                          pos_t new_size)
		THROWS(...) {
	ringbuffer_setwritten(fifo_buffer(self),
	                      (size_t)new_size);
}

INTDEF NONNULL((1)) void KCALL
handle_fifo_user_stat(struct fifo_user *__restrict self,
                      USER CHECKED struct stat *result)
		THROWS(...) {
	size_t size;
	size = ATOMIC_READ(fifo_buffer(self)->rb_avail);
	memset(result, 0, sizeof(*result));
	result->st_mode    = S_IFIFO;
	result->st_nlink   = 1;
	result->st_size    = size;
	result->st_blksize = 1;
	result->st_blocks  = size;
}

INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_fifo_user_poll(struct fifo_user *__restrict self,
                      poll_mode_t what)
		THROWS(...) {
	return ringbuffer_poll(fifo_buffer(self), what);
}

INTDEF NONNULL((1)) syscall_slong_t KCALL
handle_fifo_user_hop(struct fifo_user *__restrict self,
                     syscall_ulong_t cmd,
                     USER UNCHECKED void *arg, iomode_t mode)
		THROWS(...) {
	(void)self;
	(void)cmd;
	(void)arg;
	(void)mode;
	/* TODO */
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
	      cmd);
	return 0;
}





PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fifo_user_destroy)(struct fifo_user *__restrict self) {
	REF struct fifo_node *fifo;
	fifo = self->fu_fifo;
	if (IO_CANREAD(self->fu_accmode)) {
		if (ATOMIC_FETCHDEC(fifo->f_fifo.ff_rdcnt) == 1)
			sig_broadcast(&fifo->f_fifo.ff_buffer.rb_nfull);
	}
	if (IO_CANWRITE(self->fu_accmode)) {
		if (ATOMIC_FETCHDEC(fifo->f_fifo.ff_wrcnt) == 1)
			sig_broadcast(&fifo->f_fifo.ff_buffer.rb_nempty);
	}
	decref(fifo);
	xdecref(self->fu_dirent);
	xdecref(self->fu_path);
}


/* Create a reader/writer for the given `pipe'
 * NOTE: If applicable, the caller should fill in `fu_path' and/or
 *       `fu_dirent' directly after calling this function.
 * @param: iomode: Set of `IO_ACCMODE | IO_NONBLOCK'
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_OPEN_FIFO_WRITER_NO_READERS: [...] */
PUBLIC ATTR_RETNONNULL ATTR_MALLOC WUNUSED NONNULL((1)) REF struct fifo_user *FCALL
fifo_user_create(struct fifo_node *__restrict self, iomode_t iomode)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_STATE) {
	REF struct fifo_user *result;
	assert(!task_isconnected());
	assert((iomode & ~(IO_ACCMODE | IO_NONBLOCK)) == 0);
	result = (REF struct fifo_user *)kmalloc(sizeof(struct fifo_user),
	                                         GFP_NORMAL);
	/* Register a new reader/writer/both */
	TRY {
		switch (iomode & IO_ACCMODE) {

		case IO_RDONLY:
			for (;;) {
				if (ATOMIC_READ(self->f_fifo.ff_wrcnt) != 0)
					break;
				/* Opening a fifo as non-blocking for reading always succeeds. */
				if (iomode & IO_NONBLOCK)
					break;
				task_connect(&self->f_fifo.ff_buffer.rb_nempty);
				if (ATOMIC_READ(self->f_fifo.ff_wrcnt) != 0) {
					task_disconnectall();
					break;
				}
				/* Wait for writers to show up */
				task_waitfor();
			}
			if (ATOMIC_FETCHINC(self->f_fifo.ff_rdcnt) == 0)
				sig_broadcast(&self->f_fifo.ff_buffer.rb_nfull);
			break;

		case IO_WRONLY:
			for (;;) {
				if (ATOMIC_READ(self->f_fifo.ff_rdcnt) != 0)
					break;
				/* POSIX says that without any readers, opening a FIFO in
				 * non-block mode should have us throw some kind of error
				 * that will result in `ENXIO' */
				if (iomode & IO_NONBLOCK) {
					THROW(E_INVALID_ARGUMENT_BAD_STATE,
					      E_INVALID_ARGUMENT_CONTEXT_OPEN_FIFO_WRITER_NO_READERS);
				}
				task_connect(&self->f_fifo.ff_buffer.rb_nfull);
				if (ATOMIC_READ(self->f_fifo.ff_rdcnt) != 0) {
					task_disconnectall();
					break;
				}
				/* Wait for readers to show up */
				task_waitfor();
			}
			if (ATOMIC_FETCHINC(self->f_fifo.ff_wrcnt) == 0)
				sig_broadcast(&self->f_fifo.ff_buffer.rb_nempty);
			break;

		default:
			if (ATOMIC_FETCHINC(self->f_fifo.ff_rdcnt) == 0)
				sig_broadcast(&self->f_fifo.ff_buffer.rb_nfull);
			if (ATOMIC_FETCHINC(self->f_fifo.ff_wrcnt) == 0)
				sig_broadcast(&self->f_fifo.ff_buffer.rb_nempty);
			break;
		}
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	/* Fill in fields of the new FIFO user object. */
	result->fu_refcnt  = 1;
	result->fu_fifo    = (REF struct fifo_node *)incref(self);
	result->fu_accmode = iomode & IO_ACCMODE;
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_SPECIAL_FIFO_C */
