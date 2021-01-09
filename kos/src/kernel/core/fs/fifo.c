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
#include <sched/cred.h>
#include <sched/posix-signal.h>
#include <sched/signal.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/inval.h>
#include <kos/hop/pipe.h>
#include <sys/stat.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

DEFINE_HANDLE_REFCNT_FUNCTIONS(fifo_user, struct fifo_user);

INTDEF syscall_slong_t KCALL
ringbuffer_pipe_hop(struct ringbuffer *__restrict self,
                    syscall_ulong_t cmd,
                    USER UNCHECKED void *arg,
                    iomode_t mode);

/* Perform a generic HOP() operation for objects that point to FIFOs.
 * Called from:
 *    - HANDLE_TYPE_DATABLOCK   (When describing a `struct fifo_node *')
 *    - HANDLE_TYPE_FILE
 *    - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE
 *    - HANDLE_TYPE_FIFO_USER
 * This hop-backend implements command codes normally reserved for pipe
 * objects, thus allowing user-space to make use of pipe hop commands
 * with FIFO objects. */
INTERN syscall_slong_t KCALL
fifo_hop(struct fifo_node *__restrict self, syscall_ulong_t cmd,
         USER UNCHECKED void *arg, iomode_t mode) {
	switch (cmd) {

	case HOP_PIPE_OPEN_PIPE: {
		struct handle temp;
		if ((mode & IO_ACCMODE) != IO_RDWR)
			require(CAP_PIPE_OPEN_CONTROLLER);
		temp.h_type = HANDLE_TYPE_DATABLOCK;
		temp.h_mode = mode;
		temp.h_data = self;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

#if 0 /* TODO */
	case HOP_PIPE_CREATE_READER: {
		struct handle temp;
		unsigned int result;
		require(CAP_PIPE_CREATE_WRAPPERS);
		temp.h_type = HANDLE_TYPE_PIPE_READER;
		temp.h_mode = (mode & ~IO_ACCMODE) | IO_RDONLY;
		ATOMIC_INC(self->p_rdcnt); /* Prevent the PIPE from being closed on error */
		TRY {
			temp.h_data = pipe_reader_create(self);
			FINALLY_DECREF((struct pipe_reader *)temp.h_data);
			result = handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
		} EXCEPT {
			ATOMIC_DEC(self->p_rdcnt);
			RETHROW();
		}
		ATOMIC_DEC(self->p_rdcnt);
		return result;
	}	break;

	case HOP_PIPE_CREATE_WRITER: {
		struct handle temp;
		unsigned int result;
		require(CAP_PIPE_CREATE_WRAPPERS);
		temp.h_type = HANDLE_TYPE_PIPE_WRITER;
		temp.h_mode = (mode & ~IO_ACCMODE) | IO_WRONLY;
		ATOMIC_INC(self->p_wrcnt); /* Prevent the PIPE from being closed on error */
		TRY {
			temp.h_data = pipe_writer_create(self);
			FINALLY_DECREF((struct pipe_writer *)temp.h_data);
			result = handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
		} EXCEPT {
			ATOMIC_DEC(self->p_wrcnt);
			RETHROW();
		}
		ATOMIC_DEC(self->p_wrcnt);
		return result;
	}	break;
#endif

	default:
		/* Execute generic pipe-HOPs on our ring-buffer. */
		return ringbuffer_pipe_hop(&self->f_fifo.ff_buffer, cmd, arg, mode);
	}
	return 0;
}




#define fifo_buffer(user) (&(user)->fu_fifo->f_fifo.ff_buffer)
INTERN WUNUSED NONNULL((1)) size_t KCALL
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
		TRY {
			result = ringbuffer_read_nonblock(&fifo->f_fifo.ff_buffer,
			                                  dst, num_bytes);
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
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

INTERN WUNUSED NONNULL((1)) size_t KCALL
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
		TRY {
			result = ringbuffer_write_nonblock(&fifo->f_fifo.ff_buffer,
			                                   src, num_bytes);
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
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

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
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
			TRY {
				temp = ringbuffer_read_nonblock(&fifo->f_fifo.ff_buffer,
				                                ent.ab_base, ent.ab_size);
			} EXCEPT {
				task_disconnectall();
				RETHROW();
			}
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


INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
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
			TRY {
				temp = ringbuffer_write_nonblock(&fifo->f_fifo.ff_buffer,
				                                 ent.ab_base, ent.ab_size);
			} EXCEPT {
				task_disconnectall();
				RETHROW();
			}
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

INTERN NONNULL((1)) void KCALL
handle_fifo_user_truncate(struct fifo_user *__restrict self,
                          pos_t new_size)
		THROWS(...) {
	ringbuffer_setwritten(fifo_buffer(self),
	                      (size_t)new_size);
}

INTERN NONNULL((1)) void KCALL
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

INTERN NONNULL((1)) void KCALL
handle_fifo_user_pollconnect(struct fifo_user *__restrict self,
                             poll_mode_t what)
		THROWS(...) {
	struct ringbuffer *rb = fifo_buffer(self);
	if (what & POLLINMASK)
		ringbuffer_pollconnect_read(rb);
	if (what & POLLOUTMASK)
		ringbuffer_pollconnect_write(rb);
}

INTERN WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_fifo_user_polltest(struct fifo_user *__restrict self,
                          poll_mode_t what)
		THROWS(...) {
	poll_mode_t result = 0;
	struct ringbuffer *rb = fifo_buffer(self);
	if ((what & POLLINMASK) && ringbuffer_canread(rb))
		result |= POLLINMASK;
	if ((what & POLLOUTMASK) && ringbuffer_canwrite(rb))
		result |= POLLOUTMASK;
	return result;
}

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_fifo_user_hop(struct fifo_user *__restrict self,
                     syscall_ulong_t cmd,
                     USER UNCHECKED void *arg, iomode_t mode)
		THROWS(...) {
	/* Service generic FIFO HOP commands. */
	return fifo_hop(self->fu_fifo, cmd, arg, mode);
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
	kfree(self);
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
	assert(!task_wasconnected());
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
				task_connect_for_poll(&self->f_fifo.ff_buffer.rb_nempty);
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
				task_connect_for_poll(&self->f_fifo.ff_buffer.rb_nfull);
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
	result->fu_path    = NULL;
	result->fu_dirent  = NULL;
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_SPECIAL_FIFO_C */
