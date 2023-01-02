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
#ifndef GUARD_KERNEL_CORE_MISC_PIPE_C
#define GUARD_KERNEL_CORE_MISC_PIPE_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/driver-param.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/pipe.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/posix-signal.h> /* task_raisesignalthread */
#include <sched/rpc.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/except/reason/inval.h>
#include <kos/ioctl/pipe.h>
#include <kos/nopf.h>
#include <kos/syscalls.h>
#include <sys/stat.h>
#include <sys/uio.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include <libbuffer/ringbuffer.h>

DECL_BEGIN

/* The max pipe buffer size which may be set by an unprivileged process. */
PUBLIC size_t pipe_max_bufsize_unprivileged = RINGBUFFER_DEFAULT_LIMIT * 8;
DEFINE_KERNEL_COMMANDLINE_OPTION(pipe_max_bufsize_unprivileged,
                                 KERNEL_COMMANDLINE_OPTION_TYPE_SIZE_T,
                                 "pipe-max-size");



/* Create a new pipe object. */
PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct pipe *KCALL
pipe_create(size_t limit) THROWS(E_BADALLOC) {
	REF struct pipe *result;
	result = (REF struct pipe *)kmalloc(sizeof(struct pipe), GFP_NORMAL);
	result->p_refcnt = 1;
	result->p_rdcnt  = 0;
	result->p_wrcnt  = 0;
	ringbuffer_init_ex(&result->p_buffer, limit);
	return result;
}

/* Create a reader/writer for the given `pipe' */
PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct pipe_reader *KCALL
pipe_reader_create(struct pipe *__restrict self) THROWS(E_BADALLOC) {
	REF struct pipe_reader *result;
	result = (REF struct pipe_reader *)kmalloc(sizeof(REF struct pipe_reader),
	                                           GFP_NORMAL);
	result->pr_refcnt = 1;
	result->pr_pipe   = incref(self);
	ATOMIC_INC(self->p_rdcnt);
	return result;
}

PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct pipe_writer *KCALL
pipe_writer_create(struct pipe *__restrict self) THROWS(E_BADALLOC) {
	REF struct pipe_writer *result;
	result = (REF struct pipe_writer *)kmalloc(sizeof(REF struct pipe_writer),
	                                           GFP_NORMAL);
	result->pw_refcnt = 1;
	result->pw_pipe   = incref(self);
	ATOMIC_INC(self->p_wrcnt);
	return result;
}



PUBLIC NOBLOCK void
NOTHROW(KCALL pipe_destroy)(struct pipe *__restrict self) {
	/* Finalize the ring buffer. */
	ringbuffer_fini(&self->p_buffer);
	/* Free the pipe object. */
	kfree(self);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL pipe_reader_destroy)(struct pipe_reader *__restrict self) {
	REF struct pipe *p = self->pr_pipe;
	/* Free the pipe wrapper. */
	kfree(self);
	/* Close the pipe if all readers go away */
	if (ATOMIC_DECFETCH(p->p_rdcnt) == 0)
		ringbuffer_close(&p->p_buffer);
	/* Decref() the associated pipe. */
	decref(p);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL pipe_writer_destroy)(struct pipe_writer *__restrict self) {
	REF struct pipe *p = self->pw_pipe;
	/* Free the pipe wrapper. */
	kfree(self);
	/* Close the pipe if all writers go away */
	if (ATOMIC_DECFETCH(p->p_wrcnt) == 0)
		ringbuffer_close(&p->p_buffer);
	/* Decref() the associated pipe. */
	decref(p);
}


/* Define reference control handler operators. */
DEFINE_HANDLE_REFCNT_FUNCTIONS(pipe, struct pipe);
DEFINE_HANDLE_REFCNT_FUNCTIONS(pipe_reader, struct pipe_reader);
DEFINE_HANDLE_REFCNT_FUNCTIONS(pipe_writer, struct pipe_writer);

DEFINE_INTERN_ALIAS(handle_pipe_writer_tryas, handle_pipe_reader_tryas);
INTERN NONNULL((1)) REF void *KCALL
handle_pipe_reader_tryas(struct pipe_reader *__restrict self,
                         uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	switch (wanted_type) {

	case HANDLE_TYPE_PIPE:
		return incref(self->pr_pipe);

	default: break;
	}
	return NULL;
}



INTERN size_t KCALL /* INTERN because used in "user/handle.c" */
ringbuffer_set_pipe_limit(struct ringbuffer *__restrict self,
                          size_t new_lim) {
	size_t result;
	if (new_lim > pipe_max_bufsize_unprivileged) {
		for (;;) {
			result = ATOMIC_READ(self->rb_limit);
			/* When trying to set some limit greater than the max-unprivileged-buffer-size
			 * limit, the caller needs `CAP_SYS_RESOURCE'  capabilities, or the new  limit
			 * must be lower than the previous limit. */
			if (new_lim > result)
				require(CAP_SYS_RESOURCE);
			if (ATOMIC_CMPXCH_WEAK(self->rb_limit, result, new_lim))
				break;
		}
	} else {
		result = ATOMIC_XCH(self->rb_limit, new_lim);
	}
	if (new_lim == 0) {
		sig_broadcast(&self->rb_nempty);
		sig_broadcast(&self->rb_nfull);
	}
	return result;
}




INTERN ATTR_NORETURN void KCALL pipe_throw_broken_pipe(void) {
	/* Posix requires that we raise(SIGPIPE) in this scenario... */
	task_raisesignalthread(THIS_TASK, SIGPIPE);
	task_serve();

	/* If SIGPIPE is being ignored, we must instead throw some
	 * exception that  causes user-space  to set  errno=EPIPE. */
	THROW(E_BROKEN_PIPE);
}

INTERN size_t KCALL
handle_pipe_read(struct pipe *__restrict self,
                 USER CHECKED void *dst,
                 size_t num_bytes, iomode_t mode) {
	size_t result;
	if (mode & IO_NONBLOCK) {
		result = ringbuffer_read_nonblock(&self->p_buffer, dst, num_bytes);
		if (!result && num_bytes && !(mode & IO_NODATAZERO) && !ringbuffer_closed(&self->p_buffer))
			THROW(E_WOULDBLOCK_WAITFORSIGNAL); /* No data available. */
	} else {
		result = ringbuffer_read(&self->p_buffer, dst, num_bytes);
	}
	return result;
}

INTERN size_t KCALL
handle_pipe_write(struct pipe *__restrict self,
                  USER CHECKED void const *src,
                  size_t num_bytes, iomode_t mode) {
	size_t result;
	if (mode & IO_NONBLOCK) {
		result = ringbuffer_write_nonblock(&self->p_buffer, src, num_bytes);
	} else {
		result = ringbuffer_write(&self->p_buffer, src, num_bytes);
	}
	if (!result && num_bytes) {
		if (ringbuffer_closed(&self->p_buffer))
			pipe_throw_broken_pipe(); /* Pipe has been broken. */
		if (/*(mode & IO_NONBLOCK) && */!(mode & IO_NODATAZERO))
			THROW(E_WOULDBLOCK_WAITFORSIGNAL); /* No space available. */
	}
	return result;
}

INTERN size_t KCALL
handle_pipe_readv(struct pipe *__restrict self,
                  struct iov_buffer *__restrict dst,
                  size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct iov_entry ent;
	(void)num_bytes;
	IOV_BUFFER_FOREACH(ent, dst) {
		if (result) {
			temp = ringbuffer_read_nonblock(&self->p_buffer, ent.ive_base, ent.ive_size);
		} else if (mode & IO_NONBLOCK) {
			temp = ringbuffer_read_nonblock(&self->p_buffer, ent.ive_base, ent.ive_size);
			if (!temp && ent.ive_size && !(mode & IO_NODATAZERO) && !ringbuffer_closed(&self->p_buffer))
				THROW(E_WOULDBLOCK_WAITFORSIGNAL); /* No data available. */
		} else {
			temp = ringbuffer_read(&self->p_buffer, ent.ive_base, ent.ive_size);
		}
		result += temp;
		if (temp < ent.ive_size)
			break;
	}
	return result;
}

INTERN size_t KCALL
handle_pipe_writev(struct pipe *__restrict self,
                   struct iov_buffer *__restrict src,
                   size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct iov_entry ent;
	(void)num_bytes;
	IOV_BUFFER_FOREACH(ent, src) {
		if (result) {
			temp = ringbuffer_write_nonblock(&self->p_buffer, ent.ive_base, ent.ive_size);
		} else {
			if (mode & IO_NONBLOCK) {
				temp = ringbuffer_write_nonblock(&self->p_buffer, ent.ive_base, ent.ive_size);
			} else {
				temp = ringbuffer_write(&self->p_buffer, ent.ive_base, ent.ive_size);
			}
			if (!temp && ent.ive_size) {
				if (ringbuffer_closed(&self->p_buffer))
					pipe_throw_broken_pipe(); /* Pipe has been broken. */
				if (/*(mode & IO_NONBLOCK) && */ !(mode & IO_NODATAZERO))
					THROW(E_WOULDBLOCK_WAITFORSIGNAL); /* No space available. */
			}
		}
		result += temp;
		if (temp < ent.ive_size)
			break;
	}
	return result;
}

INTERN void KCALL
handle_pipe_truncate(struct pipe *__restrict self,
                     pos_t new_size) {
	ringbuffer_setwritten(&self->p_buffer,
	                      (size_t)new_size);
}

INTERN void KCALL
handle_pipe_stat(struct pipe *__restrict self,
                 USER CHECKED struct stat *result) {
	size_t size;
	size = ATOMIC_READ(self->p_buffer.rb_avail);
	bzero(result, sizeof(*result));
	result->st_mode    = S_IFIFO;
	result->st_nlink   = 1;
	result->st_size    = size;
	result->st_blksize = 1;
	result->st_blocks  = size;
}

INTERN void KCALL
handle_pipe_pollconnect(struct pipe *__restrict self, poll_mode_t what) {
	if (what & POLLINMASK)
		ringbuffer_pollconnect_read(&self->p_buffer);
	if (what & POLLOUTMASK)
		ringbuffer_pollconnect_write(&self->p_buffer);
}

INTERN poll_mode_t KCALL
handle_pipe_polltest(struct pipe *__restrict self, poll_mode_t what) {
	poll_mode_t result = 0;
	if ((what & POLLINMASK) && ringbuffer_canread(&self->p_buffer))
		result |= POLLINMASK;
	if ((what & POLLOUTMASK) && ringbuffer_canwrite(&self->p_buffer))
		result |= POLLOUTMASK;
	return result;
}




/* Handle operators for pipe reader / pipe writer wrappers. */
INTERN size_t KCALL
handle_pipe_reader_read(struct pipe_reader *__restrict self,
                        USER CHECKED void *dst,
                        size_t num_bytes, iomode_t mode) {
	return handle_pipe_read(self->pr_pipe, dst, num_bytes, mode);
}

INTERN size_t KCALL
handle_pipe_reader_readv(struct pipe_reader *__restrict self,
                         struct iov_buffer *__restrict dst,
                         size_t num_bytes, iomode_t mode) {
	return handle_pipe_readv(self->pr_pipe, dst, num_bytes, mode);
}


INTERN pos_t KCALL
handle_pipe_reader_seek(struct pipe_reader *__restrict self,
                        off_t offset, unsigned int whence) {
	if (whence != SEEK_CUR)
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE, whence); /* Only allow SEEK_CUR */
	return (pos_t)ringbuffer_rseek(&self->pr_pipe->p_buffer, (ssize_t)offset);
}

INTERN void KCALL
handle_pipe_reader_stat(struct pipe_reader *__restrict self,
                        USER CHECKED struct stat *result) {
	handle_pipe_stat(self->pr_pipe, result);
}

INTERN void KCALL
handle_pipe_reader_pollconnect(struct pipe_reader *__restrict self,
                               poll_mode_t UNUSED(what)) {
	ringbuffer_pollconnect_read(&self->pr_pipe->p_buffer);
}

INTERN poll_mode_t KCALL
handle_pipe_reader_polltest(struct pipe_reader *__restrict self,
                            poll_mode_t what) {
	poll_mode_t result = 0;
	struct ringbuffer *rb = &self->pr_pipe->p_buffer;
	if ((what & POLLINMASK) && ringbuffer_canread(rb))
		result |= POLLINMASK;
	if (ringbuffer_closed(rb))
		result |= POLLHUP;
	return result;
}

INTERN size_t KCALL
handle_pipe_writer_write(struct pipe_writer *__restrict self,
                         USER CHECKED void const *src,
                         size_t num_bytes, iomode_t mode) {
	return handle_pipe_write(self->pw_pipe, src, num_bytes, mode);
}

INTERN size_t KCALL
handle_pipe_writer_writev(struct pipe_writer *__restrict self,
                          struct iov_buffer *__restrict src,
                          size_t num_bytes, iomode_t mode) {
	return handle_pipe_writev(self->pw_pipe, src, num_bytes, mode);
}

INTERN pos_t KCALL
handle_pipe_writer_seek(struct pipe_writer *__restrict self,
                        off_t offset, unsigned int whence) {
	if (whence != SEEK_CUR)
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE, whence); /* Only allow SEEK_CUR */
	return (pos_t)ringbuffer_wseek(&self->pw_pipe->p_buffer, (ssize_t)offset);
}

INTERN void KCALL
handle_pipe_writer_truncate(struct pipe_writer *__restrict self,
                            pos_t new_size) {
	ringbuffer_setwritten(&self->pw_pipe->p_buffer, (size_t)new_size);
}

INTERN void KCALL
handle_pipe_writer_stat(struct pipe_writer *__restrict self,
                        USER CHECKED struct stat *result) {
	handle_pipe_stat(self->pw_pipe, result);
}

INTERN void KCALL
handle_pipe_writer_pollconnect(struct pipe_writer *__restrict self,
                               poll_mode_t UNUSED(what)) {
	ringbuffer_pollconnect_write(&self->pw_pipe->p_buffer);
}

INTERN poll_mode_t KCALL
handle_pipe_writer_polltest(struct pipe_writer *__restrict self, poll_mode_t what) {
	poll_mode_t result = 0;
	struct ringbuffer *rb = &self->pw_pipe->p_buffer;
	if ((what & POLLOUTMASK) && ringbuffer_canwrite(rb))
		result |= POLLOUTMASK;
	if (ringbuffer_closed(rb))
		result |= POLLHUP;
	return result;
}

/* Return -EINVAL if `cmd' isn't recognized. */
INTERN BLOCKING NONNULL((1)) syscall_slong_t KCALL
ringbuffer_ioctl(struct ringbuffer *__restrict self, ioctl_t cmd,
                 USER UNCHECKED void *arg, iomode_t mode) {
	switch (cmd) {

	case PIPE_IOC_PEEK: {
		USER CHECKED struct pipe_peek *info;
		USER CHECKED byte_t *buf;
		size_t offset, count, total;
		if unlikely(!IO_CANREAD(mode))
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_READ, mode);
		info = (USER CHECKED struct pipe_peek *)arg;
		validate_readwrite(info, sizeof(*info));
		COMPILER_READ_BARRIER();
		buf    = (USER CHECKED byte_t *)info->pp_buf;
		offset = (size_t)info->pp_bufof;
		count  = (size_t)info->pp_bufsz;
		COMPILER_READ_BARRIER();
		validate_writable(buf, count);

		/* Peek pipe data */
again_peek:
		ringbuffer_lock_read(self);
		total = self->rb_avail;
		if (total > offset) {
			size_t temp, error;
			size_t copy_size = total - offset;
			size_t high_base = self->rb_rptr + offset;
			if (copy_size > count)
				copy_size = count;
			high_base %= self->rb_size;
			temp = self->rb_size - high_base;
			if (temp > copy_size)
				temp = copy_size;
			error = memcpy_nopf(buf, self->rb_data + high_base, temp);
			if (error != 0) {
				byte_t next_byte;
				size_t ok;
handle_copy_error:
				ok = temp - error;
				assert(ok < count);
				next_byte = self->rb_data[high_base + ok];
				ringbuffer_lock_endread(self);
				buf += ok;
				offset += ok;
				count -= ok;
				assert(count);
				*buf++ = next_byte;
				++offset;
				--count;
				goto again_peek;
			}
			if (temp < copy_size) {
				buf += temp;
				offset += temp;
				count -= temp;

				/* Copy from low memory */
				temp  = copy_size - temp;
				error = memcpy_nopf(buf, self->rb_data, temp);
				if (error != 0) {
					high_base = 0;
					goto handle_copy_error;
				}
			}
		}
		ringbuffer_lock_endread(self);
		COMPILER_WRITE_BARRIER();
		info->pp_bufsz = total;
		return 0;
	}	break;

	default:
		break;
	}
	switch (_IO_WITHSIZE(cmd, 0)) {

	case _IO_WITHSIZE(PIPE_IOC_CLOSED, 0):
		return ioctl_intarg_setbool(cmd, arg, ringbuffer_closed(self));
	case _IO_WITHSIZE(PIPE_IOC_READABLE, 0):
		if unlikely(!IO_CANREAD(mode))
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_READ, mode);
		return ioctl_intarg_setsize(cmd, arg, ATOMIC_READ(self->rb_avail));
	case _IO_WITHSIZE(PIPE_IOC_DISCARD, 0): {
		size_t count;
		if unlikely(!IO_CANREAD(mode))
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_READ, mode);
		count = ioctl_intarg_getsize(cmd, arg);
		count = ringbuffer_skipread(self, count, NULL);
		return ioctl_intarg_setsize(cmd, arg, count);
	}	break;

	default:
		break;
	}
	return -EINVAL;
}

INTERN BLOCKING NONNULL((1)) syscall_slong_t KCALL
handle_pipe_ioctl(struct pipe *__restrict self, ioctl_t cmd,
                  USER UNCHECKED void *arg, iomode_t mode) {
	syscall_slong_t result;
	result = ringbuffer_ioctl(&self->p_buffer, cmd, arg, mode);
	if (result == -EINVAL) {
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return result;
}

INTERN BLOCKING NONNULL((1)) syscall_slong_t KCALL
handle_pipe_reader_ioctl(struct pipe_reader *__restrict self, ioctl_t cmd,
                         USER UNCHECKED void *arg, iomode_t mode) {
	return handle_pipe_ioctl(self->pr_pipe, cmd, arg, (mode & ~IO_ACCMODE) | IO_RDONLY);
}

INTERN BLOCKING NONNULL((1)) syscall_slong_t KCALL
handle_pipe_writer_ioctl(struct pipe_writer *__restrict self, ioctl_t cmd,
                         USER UNCHECKED void *arg, iomode_t mode) {
	return handle_pipe_ioctl(self->pw_pipe, cmd, arg, (mode & ~IO_ACCMODE) | IO_WRONLY);
}

static_assert(IO_CLOEXEC == IO_FROM_OPENFLAG(O_CLOEXEC));
static_assert(IO_CLOFORK == IO_FROM_OPENFLAG(O_CLOFORK));
static_assert(IO_NONBLOCK == IO_FROM_OPENFLAG(O_NONBLOCK));





/************************************************************************/
/* pipe2(), pipe()                                                      */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_PIPE2) || \
     defined(__ARCH_WANT_SYSCALL_PIPE) ||  \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PIPE))
PRIVATE errno_t KCALL
sys_pipe2_impl(USER UNCHECKED fd_t *pipedes, oflag_t flags) {
	struct handle_install_data rinstall;
	struct handle_install_data winstall;
	fd_t rfd, wfd;
	REF struct pipe *obj_pipe;
	REF struct pipe_reader *obj_reader;
	REF struct pipe_writer *obj_writer;

	validate_writable(pipedes, 2 * sizeof(fd_t));
	VALIDATE_FLAGSET(flags,
	                 O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT,
	                 E_INVALID_ARGUMENT_CONTEXT_PIPE2_FLAGS);

	/* Allocate handles. */
	rfd = handles_install_begin(&rinstall);
	TRY {
		wfd = handles_install_begin(&winstall);
		TRY {
			iomode_t mode;
			/* Write handle values to user-space. */
			COMPILER_WRITE_BARRIER();
			pipedes[0] = rfd;
			pipedes[1] = wfd;
			COMPILER_WRITE_BARRIER();

			if (flags & O_DIRECT)
				THROW(E_NOT_IMPLEMENTED_TODO); /* Packet-mode pipe */

			/* Create objects. */
			obj_pipe = pipe_create();
			FINALLY_DECREF_UNLIKELY(obj_pipe);
			obj_reader = pipe_reader_create(obj_pipe);
			FINALLY_DECREF_UNLIKELY(obj_reader);
			obj_writer = pipe_writer_create(obj_pipe);
			FINALLY_DECREF_UNLIKELY(obj_writer);

			/* Install objects -- POINT OF NO RETURN */
			mode = IO_FROM_OPENFLAG(flags & (O_CLOEXEC | O_CLOFORK | O_NONBLOCK));
			handles_install_commit(&rinstall, obj_reader, IO_RDONLY | mode);
			handles_install_commit(&winstall, obj_writer, IO_WRONLY | mode);
		} EXCEPT {
			handles_install_rollback(&winstall);
			RETHROW();
		}
	} EXCEPT {
		handles_install_rollback(&rinstall);
		RETHROW();
	}
	return -EOK;
}
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_PIPE2
DEFINE_SYSCALL2(errno_t, pipe2,
                USER UNCHECKED fd_t *, pipedes,
                oflag_t, flags) {
	return sys_pipe2_impl(pipedes, flags);
}
#endif /* __ARCH_WANT_SYSCALL_PIPE2 */

#ifdef __ARCH_WANT_SYSCALL_PIPE
DEFINE_SYSCALL1(errno_t, pipe, USER UNCHECKED fd_t *, pipedes) {
	return sys_pipe2_impl(pipedes, 0);
}
#endif /* __ARCH_WANT_SYSCALL_PIPE */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PIPE
DEFINE_COMPAT_SYSCALL1(errno_t, pipe, USER UNCHECKED fd_t *, pipedes) {
	return sys_pipe2_impl(pipedes, 0);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PIPE */


DECL_END

#endif /* !GUARD_KERNEL_CORE_MISC_PIPE_C */
