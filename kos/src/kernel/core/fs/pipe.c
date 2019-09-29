/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FS_PIPE_C
#define GUARD_KERNEL_CORE_FS_PIPE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/pipe.h>
#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <kernel/driver-param.h>

#include <hybrid/atomic.h>

#include <kos/hop.h>
#include <kos/syscalls.h>
#include <sys/stat.h>
#include <sys/uio.h>

#include <errno.h>
#include <unistd.h>

#include <libbuffer/ringbuffer.h>

DECL_BEGIN

/* The max pipe buffer size which may be set by an unprivileged process. */
PUBLIC size_t pipe_max_bufsize_unprivileged = RINGBUFFER_DEFAULT_LIMIT * 8;
DEFINE_KERNEL_COMMANDLINE_OPTION(pipe_max_bufsize_unprivileged,
                                 KERNEL_COMMANDLINE_OPTION_TYPE_SIZE_T,
                                 "pipe-max-size");



/* Create a new pipe object. */
PUBLIC ATTR_RETNONNULL ATTR_MALLOC WUNUSED REF struct pipe *KCALL
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
PUBLIC ATTR_RETNONNULL ATTR_MALLOC WUNUSED REF struct pipe_reader *KCALL
pipe_reader_create(struct pipe *__restrict self) THROWS(E_BADALLOC) {
	REF struct pipe_reader *result;
	result = (REF struct pipe_reader *)kmalloc(sizeof(REF struct pipe_reader),
	                                           GFP_NORMAL);
	result->pr_refcnt = 1;
	result->pr_pipe   = incref(self);
	ATOMIC_FETCHINC(self->p_rdcnt);
	return result;
}

PUBLIC ATTR_RETNONNULL ATTR_MALLOC WUNUSED REF struct pipe_writer *KCALL
pipe_writer_create(struct pipe *__restrict self) THROWS(E_BADALLOC) {
	REF struct pipe_writer *result;
	result = (REF struct pipe_writer *)kmalloc(sizeof(REF struct pipe_writer),
	                                           GFP_NORMAL);
	result->pw_refcnt = 1;
	result->pw_pipe   = incref(self);
	ATOMIC_FETCHINC(self->p_wrcnt);
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


PRIVATE size_t KCALL
user_set_pipe_limit(struct pipe *__restrict self,
                    size_t new_lim) {
	size_t result;
	if (new_lim > 0x10000)
		new_lim = 0x10000; /* XXX: This could be done better... */
	result = ATOMIC_XCH(self->p_buffer.rb_limit, new_lim);
	if (new_lim == 0) {
		sig_broadcast(&self->p_buffer.rb_nempty);
		sig_broadcast(&self->p_buffer.rb_nfull);
	}
	return result;
}

INTERN syscall_slong_t KCALL
handle_pipe_hop(struct pipe *__restrict self,
                syscall_ulong_t cmd,
                USER UNCHECKED void *arg,
                iomode_t mode) {
	syscall_ulong_t used_cmd;
	used_cmd = cmd;
again:
	switch (used_cmd) {

	case HOP_PIPE_STAT: {
		size_t struct_size;
		USER CHECKED struct hop_pipe_stat *data;
		size_t ps_rdtotal; /* Total number of bytes read since the pipe buffer was last defragmented (which must be done before it can be re-allocated) */
		size_t ps_avail;   /* Number of bytes currently available for reading */
		size_t ps_bufcur;  /* Current buffer size of the pipe */
		size_t ps_buflim;  /* Max buffer size of the pipe */
		validate_writable(arg, sizeof(struct hop_pipe_stat));
		data        = (struct hop_pipe_stat *)arg;
		struct_size = ATOMIC_READ(data->ps_struct_size);
		if (struct_size != sizeof(struct hop_pipe_stat))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_pipe_stat), struct_size);
		COMPILER_BARRIER();
		sync_read(&self->p_buffer.rb_lock);
		ps_rdtotal = self->p_buffer.rb_rdtot;
		ps_avail   = self->p_buffer.rb_avail;
		ps_bufcur  = self->p_buffer.rb_size;
		ps_buflim  = ATOMIC_READ(self->p_buffer.rb_limit);
		sync_endread(&self->p_buffer.rb_lock);
		COMPILER_BARRIER();
		data->ps_rdtotal = (u64)ps_rdtotal;
		data->ps_avail   = (u64)ps_avail;
		data->ps_bufcur  = (u64)ps_bufcur;
		data->ps_buflim  = (u64)ps_buflim;
	} break;

	case HOP_PIPE_GETLIM: /* [OUT:uint64_t *result] Return the max allocated size of the pipe. */
		validate_writable(arg, sizeof(u64));
		*(u64 *)arg = (u64)ATOMIC_READ(self->p_buffer.rb_limit);
		break;

	case HOP_PIPE_SETLIM: /* [size_t value] Set the max allocated pipe size to `value'. */
		user_set_pipe_limit(self, (size_t)arg);
		break;

	case HOP_PIPE_XCHLIM: {
		/* [IN|OUT:uint64_t *value] Exchange the old max allocated pipe size with `*value'. */
		u64 *value;
		size_t temp;
		value = (u64 *)arg;
		validate_writable(value, sizeof(*value));
		temp = (size_t)ATOMIC_READ(*value);
		temp = user_set_pipe_limit(self, temp);
		ATOMIC_WRITE(*value, temp);
	} break;

	case HOP_PIPE_WRITESOME: {
		USER CHECKED struct hop_pipe_writesome *data;
		size_t struct_size;
		USER UNCHECKED void *buf;
		size_t buflen;
		if ((mode & IO_ACCMODE) == IO_RDONLY)
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_WRITE, mode);
		validate_writable(arg, sizeof(struct hop_pipe_writesome));
		data        = (struct hop_pipe_writesome *)arg;
		struct_size = ATOMIC_READ(data->pws_struct_size);
		if (struct_size != sizeof(struct hop_pipe_writesome))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_pipe_writesome), struct_size);
		COMPILER_BARRIER();
		buf    = ATOMIC_READ(data->pws_buf);
		buflen = ATOMIC_READ(data->pws_buflen);
		validate_readable(buf, buflen);
		buflen = mode & IO_NONBLOCK
		         ? ringbuffer_write_nonblock(&self->p_buffer, buf, buflen)
		         : ringbuffer_writesome(&self->p_buffer, buf, buflen);
		ATOMIC_WRITE(data->pws_written, buflen);
	} break;


	case HOP_PIPE_VWRITESOME: {
		USER CHECKED struct hop_pipe_vwritesome *data;
		size_t i, struct_size, result, temp;
		USER UNCHECKED struct iovec const *buf;
		size_t buflen;
		if ((mode & IO_ACCMODE) == IO_RDONLY)
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_WRITE, mode);
		validate_writable(arg, sizeof(struct hop_pipe_vwritesome));
		data        = (struct hop_pipe_vwritesome *)arg;
		struct_size = ATOMIC_READ(data->pvws_struct_size);
		if (struct_size != sizeof(struct hop_pipe_vwritesome))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_pipe_vwritesome), struct_size);
		COMPILER_BARRIER();
		buf    = ATOMIC_READ(data->pvws_buf);
		buflen = ATOMIC_READ(data->pvws_bufcnt);
		validate_readablem(buf, buflen, sizeof(struct iovec));
		result = 0;
		for (i = 0; i < buflen; ++i) {
			struct iovec ent;
			ent.iov_base = ATOMIC_READ(buf[i].iov_base);
			ent.iov_len  = ATOMIC_READ(buf[i].iov_len);
			validate_readable(ent.iov_base, ent.iov_len);
			temp = result || mode & IO_NONBLOCK
			       ? ringbuffer_write_nonblock(&self->p_buffer, ent.iov_base, ent.iov_len)
			       : ringbuffer_writesome(&self->p_buffer, ent.iov_base, ent.iov_len);
			result += temp;
			if (temp < ent.iov_len)
				break;
		}
		ATOMIC_WRITE(data->pvws_written, result);
	} break;

	case HOP_PIPE_SKIPDATA: {
		USER CHECKED struct hop_pipe_skipdata *data;
		size_t struct_size;
		size_t result, new_rdpos;
		if ((mode & IO_ACCMODE) == IO_WRONLY)
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_READ, mode);
		validate_writable(arg, sizeof(struct hop_pipe_skipdata));
		data        = (struct hop_pipe_skipdata *)arg;
		struct_size = ATOMIC_READ(data->psd_struct_size);
		if (struct_size != sizeof(struct hop_pipe_skipdata))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_pipe_skipdata), struct_size);
		COMPILER_BARRIER();
		result = ringbuffer_skipread(&self->p_buffer,
		                             ATOMIC_READ(*(size_t *)&data->psd_num_bytes),
		                             &new_rdpos);
		ATOMIC_WRITE(data->psd_rdpos, new_rdpos);
		ATOMIC_WRITE(data->psd_skipped, result);
	} break;

	case HOP_PIPE_UNREAD: {
		USER CHECKED struct hop_pipe_unread *data;
		size_t struct_size;
		size_t result, new_rdpos;
		if ((mode & IO_ACCMODE) == IO_WRONLY)
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_READ, mode);
		validate_writable(arg, sizeof(struct hop_pipe_unread));
		data        = (struct hop_pipe_unread *)arg;
		struct_size = ATOMIC_READ(data->pur_struct_size);
		if (struct_size != sizeof(struct hop_pipe_unread))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_pipe_unread), struct_size);
		COMPILER_BARRIER();
		result = ringbuffer_unread(&self->p_buffer,
		                           ATOMIC_READ(*(size_t *)&data->pur_num_bytes),
		                           &new_rdpos);
		ATOMIC_WRITE(data->pur_rdpos, new_rdpos);
		ATOMIC_WRITE(data->pur_unread, result);
	} break;

	case HOP_PIPE_UNWRITE: {
		USER CHECKED struct hop_pipe_unwrite *data;
		size_t struct_size;
		size_t result, new_wrpos;
		if ((mode & IO_ACCMODE) == IO_RDONLY)
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_WRITE, mode);
		validate_writable(arg, sizeof(struct hop_pipe_unwrite));
		data        = (struct hop_pipe_unwrite *)arg;
		struct_size = ATOMIC_READ(data->puw_struct_size);
		if (struct_size != sizeof(struct hop_pipe_unwrite))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_pipe_unwrite), struct_size);
		COMPILER_BARRIER();
		result = ringbuffer_unread(&self->p_buffer,
		                           ATOMIC_READ(*(size_t *)&data->puw_num_bytes),
		                           &new_wrpos);
		ATOMIC_WRITE(data->puw_wrpos, new_wrpos);
		ATOMIC_WRITE(data->puw_unwritten, result);
	} break;

	case HOP_PIPE_SETWRITTEN: {
		USER CHECKED u64 *data;
		size_t temp;
		validate_writable(arg, sizeof(u64));
		data = (USER CHECKED u64 *)arg;
		temp = ATOMIC_READ(*(size_t *)data);
		temp = ringbuffer_setwritten(&self->p_buffer, temp);
		ATOMIC_WRITE(*data, temp);
	} break;

	case HOP_PIPE_OPEN_PIPE: {
		struct handle temp;
		temp.h_type = HANDLE_TYPE_PIPE;
		temp.h_mode = mode;
		temp.h_data = self;
		handle_installhop((struct hop_openfd *)arg, temp);
	} break;

	case HOP_PIPE_CREATE_READER: {
		struct handle temp;
		temp.h_type = HANDLE_TYPE_PIPE_READER;
		temp.h_mode = (mode & ~IO_ACCMODE) | IO_RDONLY;
		ATOMIC_FETCHINC(self->p_rdcnt); /* Prevent the PIPE from being closed on error */
		TRY {
			temp.h_data = pipe_reader_create(self);
			FINALLY_DECREF((struct pipe_reader *)temp.h_data);
			handle_installhop((struct hop_openfd *)arg, temp);
		} EXCEPT {
			ATOMIC_FETCHDEC(self->p_rdcnt);
			RETHROW();
		}
		ATOMIC_FETCHDEC(self->p_rdcnt);
	} break;

	case HOP_PIPE_CREATE_WRITER: {
		struct handle temp;
		temp.h_type = HANDLE_TYPE_PIPE_WRITER;
		temp.h_mode = (mode & ~IO_ACCMODE) | IO_WRONLY;
		ATOMIC_FETCHINC(self->p_wrcnt); /* Prevent the PIPE from being closed on error */
		TRY {
			temp.h_data = pipe_writer_create(self);
			FINALLY_DECREF((struct pipe_writer *)temp.h_data);
			handle_installhop((struct hop_openfd *)arg, temp);
		} EXCEPT {
			ATOMIC_FETCHDEC(self->p_wrcnt);
			RETHROW();
		}
		ATOMIC_FETCHDEC(self->p_wrcnt);
	} break;

	default:
		if (used_cmd == cmd) {
			if ((cmd >> 16) == HANDLE_TYPE_PIPE_READER ||
			    (cmd >> 16) == HANDLE_TYPE_PIPE_WRITER) {
				/* Alias all `HANDLE_TYPE_PIPE' commands within the PIPE_READER and PIPE_WRITER namespaces. */
				used_cmd &= 0xffff;
				used_cmd |= HANDLE_TYPE_PIPE << 16;
				goto again;
			}
		}
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}




INTERN size_t KCALL
handle_pipe_read(struct pipe *__restrict self,
                 USER CHECKED void *dst,
                 size_t num_bytes, iomode_t mode) {
	return mode & IO_NONBLOCK
	       ? ringbuffer_read_nonblock(&self->p_buffer, dst, num_bytes)
	       : ringbuffer_read(&self->p_buffer, dst, num_bytes);
}

INTERN size_t KCALL
handle_pipe_write(struct pipe *__restrict self,
                  USER CHECKED void const *src,
                  size_t num_bytes, iomode_t mode) {
	return mode & IO_NONBLOCK
	       ? ringbuffer_write_nonblock(&self->p_buffer, src, num_bytes)
	       : ringbuffer_write(&self->p_buffer, src, num_bytes);
}

INTERN size_t KCALL
handle_pipe_readv(struct pipe *__restrict self,
                  struct aio_buffer *__restrict dst,
                  size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		if unlikely(!ent.ab_size)
			continue;
		temp = result || mode & IO_NONBLOCK
		       ? ringbuffer_read_nonblock(&self->p_buffer, ent.ab_base, ent.ab_size)
		       : ringbuffer_read(&self->p_buffer, ent.ab_base, ent.ab_size);
		result += temp;
		if (temp < ent.ab_size)
			break;
	}
	return result;
}

INTERN size_t KCALL
handle_pipe_writev(struct pipe *__restrict self,
                   struct aio_buffer *__restrict src,
                   size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		if unlikely(!ent.ab_size)
			continue;
		temp = mode & IO_NONBLOCK
		       ? ringbuffer_write_nonblock(&self->p_buffer, ent.ab_base, ent.ab_size)
		       : ringbuffer_write(&self->p_buffer, ent.ab_base, ent.ab_size);
		result += temp;
		if (temp < ent.ab_size)
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
	result->st_dev            = 0;
	result->st_ino            = 0;
	result->st_mode           = S_IFIFO;
	result->st_nlink          = 1;
	result->st_uid            = 0;
	result->st_gid            = 0;
	result->st_rdev           = 0;
	result->st_size           = size;
	result->st_blksize        = 1;
	result->st_blocks         = size;
	result->st_atim32.tv_sec  = 0;
	result->st_atim32.tv_nsec = 0;
	result->st_mtim32.tv_sec  = 0;
	result->st_mtim32.tv_nsec = 0;
	result->st_ctim32.tv_sec  = 0;
	result->st_ctim32.tv_nsec = 0;
	result->st_atim64.tv_sec  = 0;
	result->st_atim64.tv_nsec = 0;
	result->st_mtim64.tv_sec  = 0;
	result->st_mtim64.tv_nsec = 0;
	result->st_ctim64.tv_sec  = 0;
	result->st_ctim64.tv_nsec = 0;
}

INTERN poll_mode_t KCALL
handle_pipe_poll(struct pipe *__restrict self, poll_mode_t what) {
	return ringbuffer_poll(&self->p_buffer, what);
}




/* Handle operators for pipe reader / pipe writer wrappers. */
INTERN size_t KCALL
handle_pipe_reader_read(struct pipe_reader *__restrict self,
                        USER CHECKED void *dst, size_t num_bytes, iomode_t mode) {
	return handle_pipe_read(self->pr_pipe, dst, num_bytes, mode);
}

INTERN size_t KCALL
handle_pipe_reader_readv(struct pipe_reader *__restrict self,
                         struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
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

INTERN poll_mode_t KCALL
handle_pipe_reader_poll(struct pipe_reader *__restrict self, poll_mode_t what) {
	return ringbuffer_poll(&self->pr_pipe->p_buffer, what & POLLIN);
}

INTERN syscall_slong_t KCALL
handle_pipe_reader_hop(struct pipe_reader *__restrict self,
                       syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) {
	return handle_pipe_hop(self->pr_pipe, cmd, arg, (mode & ~IO_ACCMODE) | IO_RDONLY);
}

INTERN size_t KCALL
handle_pipe_writer_write(struct pipe_writer *__restrict self,
                         USER CHECKED void const *src, size_t num_bytes, iomode_t mode) {
	return handle_pipe_write(self->pw_pipe, src, num_bytes, mode);
}

INTERN size_t KCALL
handle_pipe_writer_writev(struct pipe_writer *__restrict self,
                          struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
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

INTERN poll_mode_t KCALL
handle_pipe_writer_poll(struct pipe_writer *__restrict self, poll_mode_t what) {
	return ringbuffer_poll(&self->pw_pipe->p_buffer, what & POLLOUT);
}

INTERN syscall_slong_t KCALL
handle_pipe_writer_hop(struct pipe_writer *__restrict self,
                       syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) {
	return handle_pipe_hop(self->pw_pipe, cmd, arg, (mode & ~IO_ACCMODE) | IO_WRONLY);
}

INTERN size_t KCALL
handle_pipe_reader_aread(struct pipe_reader *__restrict self,
                         USER CHECKED void *dst, size_t num_bytes,
                         iomode_t mode, struct aio_multihandle *__restrict UNUSED(aio)) {
	return handle_pipe_read(self->pr_pipe, dst, num_bytes, mode);
}

INTERN size_t KCALL
handle_pipe_reader_areadv(struct pipe_reader *__restrict self,
                          struct aio_buffer *__restrict dst, size_t num_bytes,
                          iomode_t mode, struct aio_multihandle *__restrict UNUSED(aio)) {
	return handle_pipe_readv(self->pr_pipe, dst, num_bytes, mode);
}

INTERN size_t KCALL
handle_pipe_writer_awrite(struct pipe_writer *__restrict self,
                          USER CHECKED void const *src, size_t num_bytes,
                          iomode_t mode, struct aio_multihandle *__restrict UNUSED(aio)) {
	return handle_pipe_write(self->pw_pipe, src, num_bytes, mode);
}

INTERN size_t KCALL
handle_pipe_writer_awritev(struct pipe_writer *__restrict self,
                           struct aio_buffer *__restrict src, size_t num_bytes,
                           iomode_t mode, struct aio_multihandle *__restrict UNUSED(aio)) {
	return handle_pipe_writev(self->pw_pipe, src, num_bytes, mode);
}

#if 0
INTERN syscall_slong_t KCALL
handle_pipe_ioctl(struct pipe *__restrict self,
                  syscall_ulong_t cmd,
                  USER UNCHECKED void *arg,
                  iomode_t mode) {
	return 0;
}
INTERN syscall_slong_t KCALL
handle_pipe_reader_ioctl(struct pipe_reader *__restrict self,
                         syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) {
	return handle_pipe_ioctl(self->pr_pipe, cmd, arg, (mode & ~IO_ACCMODE) | IO_RDONLY);
}
INTERN syscall_slong_t KCALL
handle_pipe_writer_ioctl(struct pipe_writer *__restrict self,
                         syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) {
	return handle_pipe_ioctl(self->pw_pipe, cmd, arg, (mode & ~IO_ACCMODE) | IO_WRONLY);
}
#endif


STATIC_ASSERT(IO_CLOEXEC == IO_FROM_OPENFLAG(O_CLOEXEC));
STATIC_ASSERT(IO_CLOFORK == IO_FROM_OPENFLAG(O_CLOFORK));
STATIC_ASSERT(IO_NONBLOCK == IO_FROM_OPENFLAG(O_NONBLOCK));

DEFINE_SYSCALL2(errno_t, pipe2,
                USER UNCHECKED fd_t *, pipedes,
                oflag_t, flags) {
	REF struct pipe *p;
	REF struct handle r;
	REF struct handle w;
	unsigned int rfd, wfd;
	validate_writable(pipedes, 2 * sizeof(fd_t));
	VALIDATE_FLAGSET(flags,
	                 O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT,
	                 E_INVALID_ARGUMENT_CONTEXT_PIPE2_FLAGS);
	if (flags & O_DIRECT)
		THROW(E_NOT_IMPLEMENTED_TODO); /* Packet-mode pipe */
	/* Create a new pipe, pipe-reader and pipe-writer */
	p = pipe_create();
	FINALLY_DECREF_UNLIKELY(p);
	r.h_type = HANDLE_TYPE_PIPE_READER;
	r.h_mode = IO_RDONLY | IO_FROM_OPENFLAG(flags & (O_CLOEXEC | O_CLOFORK | O_NONBLOCK));
	r.h_data = pipe_reader_create(p);
	FINALLY_DECREF_UNLIKELY((struct pipe_reader *)r.h_data);
	w.h_type = HANDLE_TYPE_PIPE_WRITER;
	w.h_mode = IO_WRONLY | IO_FROM_OPENFLAG(flags & (O_CLOEXEC | O_CLOFORK | O_NONBLOCK));
	w.h_data = pipe_writer_create(p);
	FINALLY_DECREF_UNLIKELY((struct pipe_writer *)w.h_data);
	/* Install the reader/writer handlers. */
	rfd = handle_install(THIS_HANDLE_MANAGER, r);
	TRY {
		wfd = handle_install(THIS_HANDLE_MANAGER, w);
		TRY {
			COMPILER_WRITE_BARRIER();
			pipedes[0] = rfd;
			pipedes[1] = wfd;
			COMPILER_WRITE_BARRIER();
		} EXCEPT {
			handle_tryclose_nosym(wfd, THIS_HANDLE_MANAGER);
			RETHROW();
		}
	} EXCEPT {
		handle_tryclose_nosym(rfd, THIS_HANDLE_MANAGER);
		RETHROW();
	}
	return -EOK;
}

#ifdef __NR_pipe
DEFINE_SYSCALL1(errno_t, pipe, USER UNCHECKED fd_t *, pipedes) {
	return sys_pipe2(pipedes, 0);
}
#endif /* __NR_pipe */


DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_PIPE_C */
