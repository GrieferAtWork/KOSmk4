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
#ifndef GUARD_KERNEL_CORE_FILESYS_FIFONODE_C
#define GUARD_KERNEL_CORE_FILESYS_FIFONODE_C 1

#include <kernel/compiler.h>

#include <fs/vfs.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/fifohandle.h>
#include <kernel/fs/fifonode.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/iovec.h>
#include <sched/cred.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/hop/pipe.h>
#include <kos/kernel/handle.h> /* HANDLE_TYPE_FIFOHANDLE */
#include <sys/stat.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

/* Default operator for opening ffifonode files. This will  construct
 * a `struct fifohandle' (HANDLE_TYPE_FIFOHANDLE) object and write it
 * back to `hand'. */
PUBLIC BLOCKING NONNULL((1, 2)) void KCALL
ffifonode_v_open(struct mfile *__restrict self,
                 struct handle *__restrict hand,
                 struct path *access_path,
                 struct fdirent *access_dent)
		THROWS(E_BADALLOC, E_INVALID_ARGUMENT_BAD_STATE, ...) {
	struct ffifonode *me;
	REF struct fifohandle *obj;
	assert(hand->h_data == self);
	me  = mfile_asfifo(self);
	obj = fifohandle_new(me, hand->h_mode, access_path, access_dent);

	/* Write-back the new object */
	hand->h_data = obj; /* Inherit reference */
	hand->h_type = HANDLE_TYPE_FIFOHANDLE;

	/* Old reference from `hand->h_data' */
	decref_nokill(self);
}

PUBLIC BLOCKING WUNUSED NONNULL((1)) size_t KCALL
ffifonode_v_read(struct mfile *__restrict self, USER CHECKED void *dst,
                 size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	struct ffifonode *me = mfile_asfifo(self);
again:
	result = ringbuffer_read_nonblock(&me->ff_buffer,
	                                  dst, num_bytes);
	if (!result) {
		if unlikely(!num_bytes)
			goto done;
		/* Buffer is empty. */
		if (!ATOMIC_READ(me->ff_wrcnt))
			goto done; /* End-of-file */
		if (mode & IO_NONBLOCK) {
			if (!(mode & IO_NODATAZERO))
				THROW(E_WOULDBLOCK_WAITFORSIGNAL); /* No space available. */
			goto done;
		}
		task_connect(&me->ff_buffer.rb_nempty);
		/* Retry reading data, now that we're being interlocked. */
		TRY {
			result = ringbuffer_read_nonblock(&me->ff_buffer,
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
		if unlikely(!ATOMIC_READ(me->ff_wrcnt)) {
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

PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
ffifonode_v_readv(struct mfile *__restrict self, struct iov_buffer *__restrict dst,
                  size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t temp, result = 0;
	struct iov_entry ent;
	struct ffifonode *me = mfile_asfifo(self);
	(void)num_bytes;
	IOV_BUFFER_FOREACH(ent, dst) {
again_read_ent:
		temp = ringbuffer_read_nonblock(&me->ff_buffer,
		                                ent.ive_base,
		                                ent.ive_size);
		result += temp;
		if (temp < ent.ive_size) {
			/* Buffer is empty. */
			if (result)
				break;
			if (mode & IO_NONBLOCK) {
				if (!(mode & IO_NODATAZERO))
					THROW(E_WOULDBLOCK_WAITFORSIGNAL); /* No space available. */
				break;
			}
			if (!ATOMIC_READ(me->ff_wrcnt))
				break; /* End-of-file */
			task_connect(&me->ff_buffer.rb_nempty);
			/* Retry reading data, now that we're being interlocked. */
			TRY {
				temp = ringbuffer_read_nonblock(&me->ff_buffer,
				                                ent.ive_base, ent.ive_size);
			} EXCEPT {
				task_disconnectall();
				RETHROW();
			}
			if unlikely(temp) {
				task_disconnectall();
				result += temp;
				if (temp == ent.ive_size)
					continue; /* Write further segments. */
				break;
			}
			/* Check if these are still readers out there. */
			if unlikely(!ATOMIC_READ(me->ff_wrcnt)) {
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

PUBLIC BLOCKING WUNUSED NONNULL((1)) size_t KCALL
ffifonode_v_write(struct mfile *__restrict self, USER CHECKED void const *src,
                  size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	struct ffifonode *me = mfile_asfifo(self);
again:
	if (!ATOMIC_READ(me->ff_rdcnt)) {
no_readers:
		/* Posix requires that we raise(SIGPIPE) in this scenario... */
		task_raisesignalthread(THIS_TASK, SIGPIPE);
		task_serve();

		/* If SIGPIPE is being ignored, we must instead throw some
		 * exception that  causes user-space  to set  errno=EPIPE. */
		THROW(E_INVALID_ARGUMENT_BAD_STATE,
			  E_INVALID_ARGUMENT_CONTEXT_WRITE_FIFO_NO_READERS);
	}
	result = ringbuffer_write_nonblock(&me->ff_buffer,
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
		if (!ATOMIC_READ(me->ff_rdcnt))
			goto no_readers;
		task_connect(&me->ff_buffer.rb_nfull);
		/* Retry writing data, now that we're being interlocked. */
		TRY {
			result = ringbuffer_write_nonblock(&me->ff_buffer,
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
		if unlikely(!ATOMIC_READ(me->ff_rdcnt)) {
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

PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
ffifonode_v_writev(struct mfile *__restrict self, struct iov_buffer *__restrict src,
                   size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t temp, result = 0;
	struct iov_entry ent;
	struct ffifonode *me = mfile_asfifo(self);
	(void)num_bytes;
	if (!ATOMIC_READ(me->ff_rdcnt)) {
no_readers:
		/* Posix requires that we raise(SIGPIPE) in this scenario... */
		task_raisesignalthread(THIS_TASK, SIGPIPE);
		task_serve();

		/* If SIGPIPE is being ignored, we must instead throw some
		 * exception that  causes user-space  to set  errno=EPIPE. */
		THROW(E_INVALID_ARGUMENT_BAD_STATE,
			  E_INVALID_ARGUMENT_CONTEXT_WRITE_FIFO_NO_READERS);
	}
	IOV_BUFFER_FOREACH(ent, src) {
again_write_ent:
		temp = ringbuffer_write_nonblock(&me->ff_buffer,
		                                 ent.ive_base,
		                                 ent.ive_size);
		result += temp;
		if (temp < ent.ive_size) {
			/* Buffer is full. */
			if (result)
				break;
			if (mode & IO_NONBLOCK) {
				if (!(mode & IO_NODATAZERO))
					THROW(E_WOULDBLOCK_WAITFORSIGNAL); /* No space available. */
				break;
			}
			if (!ATOMIC_READ(me->ff_rdcnt))
				goto no_readers;
			task_connect(&me->ff_buffer.rb_nfull);
			/* Retry writing data, now that we're being interlocked. */
			TRY {
				temp = ringbuffer_write_nonblock(&me->ff_buffer,
				                                 ent.ive_base, ent.ive_size);
			} EXCEPT {
				task_disconnectall();
				RETHROW();
			}
			if unlikely(temp) {
				task_disconnectall();
				result += temp;
				if (temp == ent.ive_size)
					continue; /* Write further segments. */
				break;
			}
			/* Check if these are still readers out there. */
			if unlikely(!ATOMIC_READ(me->ff_rdcnt)) {
				task_disconnectall();
				goto no_readers;
			}
			/* Wait for space to become available. */
			task_waitfor();
			/* Verify that there are still readers. */
			if unlikely(!ATOMIC_READ(me->ff_rdcnt))
				goto no_readers;
			goto again_write_ent;
		}
	}
	return result;
}


/* Does `ringbuffer_setwritten()' */
PUBLIC NONNULL((1)) void KCALL
ffifonode_v_truncate(struct mfile *__restrict self, pos_t new_size)
		THROWS(E_WOULDBLOCK) {
	struct ffifonode *me = mfile_asfifo(self);
	ringbuffer_setwritten(&me->ff_buffer, (size_t)new_size);
}

/* Fills in `st_size' with `mfile_asfifo(self)->ff_buffer.rb_avail' */
PUBLIC NONNULL((1)) void KCALL
ffifonode_v_stat(struct mfile *__restrict self,
                 USER CHECKED struct stat *result)
		THROWS(E_SEGFAULT) {
	struct ffifonode *me;
	size_t avail;
	me    = mfile_asfifo(self);
	avail = ATOMIC_READ(me->ff_buffer.rb_avail);
	result->st_size = (typeof(result->st_size))avail;
}

INTDEF syscall_slong_t KCALL /* From "pipe.c" */
ringbuffer_pipe_hop(struct ringbuffer *__restrict self,
                    syscall_ulong_t cmd,
                    USER UNCHECKED void *arg,
                    iomode_t mode);

/* Implements some `HOP_PIPE_OPEN_*' commands */
PUBLIC NONNULL((1)) syscall_slong_t KCALL
ffifonode_v_hop(struct mfile *__restrict self, syscall_ulong_t cmd,
                USER UNCHECKED void *arg, iomode_t mode)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	struct ffifonode *me = mfile_asfifo(self);
	switch (cmd) {

	case HOP_PIPE_OPEN_PIPE: {
		struct handle temp;
		if ((mode & IO_ACCMODE) != IO_RDWR)
			require(CAP_PIPE_OPEN_CONTROLLER);
		temp.h_type = HANDLE_TYPE_MFILE;
		temp.h_mode = mode;
		temp.h_data = me;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case HOP_PIPE_CREATE_READER: {
		struct handle temp;
		require(CAP_PIPE_CREATE_WRAPPERS);
		temp.h_type = HANDLE_TYPE_FIFOHANDLE;
		temp.h_mode = (mode & ~IO_ACCMODE) | IO_RDONLY;
		temp.h_data = fifohandle_new(me, temp.h_mode, NULL, NULL);
		FINALLY_DECREF_UNLIKELY((REF struct fifohandle *)temp.h_data);
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case HOP_PIPE_CREATE_WRITER: {
		struct handle temp;
		require(CAP_PIPE_CREATE_WRAPPERS);
		temp.h_type = HANDLE_TYPE_FIFOHANDLE;
		temp.h_mode = (mode & ~IO_ACCMODE) | IO_WRONLY;
		temp.h_data = fifohandle_new(me, temp.h_mode, NULL, NULL);
		FINALLY_DECREF_UNLIKELY((REF struct fifohandle *)temp.h_data);
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	default:
		break;
	}
	/* Execute generic pipe-HOPs on our ring-buffer. */
	return ringbuffer_pipe_hop(&me->ff_buffer, cmd, arg, mode);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ffifonode_v_destroy)(struct mfile *__restrict self) {
	struct ffifonode *me;
	me = mfile_asfifo(self);
	/* Finalize the FIFO buffer. */
	ringbuffer_fini(&me->ff_buffer);
	fnode_v_destroy(self);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_FIFONODE_C */
