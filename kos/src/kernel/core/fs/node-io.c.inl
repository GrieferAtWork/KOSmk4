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
#ifdef __INTELLISENSE__
#include "node.c"
#endif /* __INTELLISENSE__ */

#include <fs/node.h>
#include <kernel/aio.h>
#include <kernel/iovec.h>
#include <kernel/swap.h>
#include <kernel/mman/phys.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <libvio/access.h>

#ifdef __INTELLISENSE__
#undef DEFINE_IO_ASYNC
#undef DEFINE_IO_READ
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_PHYS
#undef DEFINE_IO_VECTOR
#undef DEFINE_IO_KERNEL

#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_READ 1
//#define DEFINE_IO_WRITE 1
//#define DEFINE_IO_PHYS 1
//#define DEFINE_IO_VECTOR 1
//#define DEFINE_IO_KERNEL 1
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#ifdef DEFINE_IO_READ
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
#define RW_OPERATOR f_preadv
#elif defined(DEFINE_IO_VECTOR)
#define RW_OPERATOR f_readv
#elif defined(DEFINE_IO_PHYS)
#define RW_OPERATOR f_pread
#else /* ... */
#define RW_OPERATOR f_read
#endif /* !... */
#else /* DEFINE_IO_READ */
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
#define RW_OPERATOR f_pwritev
#elif defined(DEFINE_IO_VECTOR)
#define RW_OPERATOR f_writev
#elif defined(DEFINE_IO_PHYS)
#define RW_OPERATOR f_pwrite
#else /* ... */
#define RW_OPERATOR f_write
#endif /* !... */
#endif /* !DEFINE_IO_READ */


#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
#define FUNC0(x) x##v_phys
#elif defined(DEFINE_IO_PHYS)
#define FUNC0(x) x##_phys
#elif defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_KERNEL)
#define FUNC0(x) x##kv
#elif defined(DEFINE_IO_VECTOR)
#define FUNC0(x) x##v
#elif defined(DEFINE_IO_KERNEL)
#define FUNC0(x) x##k
#else
#define FUNC0(x) x
#endif
#ifdef DEFINE_IO_READ
#define FUNC1(x) FUNC0(x##read_locked)
#else
#define FUNC1(x) FUNC0(x##write)
#endif
#ifdef DEFINE_IO_ASYNC
#define FUNC2(x) FUNC1(x##a)
#else
#define FUNC2    FUNC1
#endif



#ifdef DEFINE_IO_READ
INTERN
#else
PUBLIC
#endif
#ifdef DEFINE_IO_ASYNC
#if defined(DEFINE_IO_VECTOR) || defined(DEFINE_IO_KERNEL)
	NONNULL((1, 2, 5))
#else /* DEFINE_IO_VECTOR */
	NONNULL((1, 5))
#endif /* !DEFINE_IO_VECTOR */
#else /* DEFINE_IO_ASYNC */
#if defined(DEFINE_IO_VECTOR) || defined(DEFINE_IO_KERNEL)
	NONNULL((1, 2))
#else /* DEFINE_IO_VECTOR */
	NONNULL((1))
#endif /* !DEFINE_IO_VECTOR */
#endif /* !DEFINE_IO_ASYNC */
	void
#ifdef DEFINE_IO_ASYNC
NOTHROW(KCALL FUNC2(inode_))(struct inode *__restrict self,
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
                             struct iov_physbuffer *__restrict buf,
#elif defined(DEFINE_IO_VECTOR)
                             struct iov_buffer *__restrict buf,
#elif defined(DEFINE_IO_PHYS)
                             physaddr_t buf,
#elif defined(DEFINE_IO_READ) && defined(DEFINE_IO_KERNEL)
                             void *__restrict buf,
#elif defined(DEFINE_IO_READ)
                             CHECKED USER void *buf,
#elif defined(DEFINE_IO_KERNEL)
                             void const *__restrict buf,
#else
                             CHECKED USER void const *buf,
#endif
                             size_t num_bytes, pos_t file_position,
                             struct aio_multihandle *__restrict aio)
#else /* DEFINE_IO_ASYNC */
(KCALL FUNC2(inode_))(struct inode *__restrict self,
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
                      struct iov_physbuffer *__restrict buf,
#elif defined(DEFINE_IO_VECTOR)
                      struct iov_buffer *__restrict buf,
#elif defined(DEFINE_IO_PHYS)
                      physaddr_t buf,
#elif defined(DEFINE_IO_READ) && defined(DEFINE_IO_KERNEL)
                      void *__restrict buf,
#elif defined(DEFINE_IO_READ)
                      CHECKED USER void *buf,
#elif defined(DEFINE_IO_KERNEL)
                      void const *__restrict buf,
#else
                      CHECKED USER void const *buf,
#endif
                      size_t num_bytes,
                      pos_t file_position)
#endif /* !DEFINE_IO_ASYNC */
#ifdef DEFINE_IO_ASYNC
#ifdef DEFINE_IO_PHYS
		THROWS_INDIRECT(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...)
#else /* DEFINE_IO_PHYS */
		THROWS_INDIRECT(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, E_SEGFAULT, ...)
#endif /* !DEFINE_IO_PHYS */
#else /* DEFINE_IO_ASYNC */
#ifdef DEFINE_IO_PHYS
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...)
#else /* DEFINE_IO_PHYS */
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, E_SEGFAULT, ...)
#endif /* !DEFINE_IO_PHYS */
#endif /* !DEFINE_IO_ASYNC */
{
#ifdef DEFINE_IO_ASYNC
	TRY {
		REF struct mpart *part;
		size_t max_io_bytes;
#ifdef DEFINE_IO_VECTOR
		uintptr_t buf_offset;
#endif /* DEFINE_IO_VECTOR */
#ifndef DEFINE_IO_READ
		if unlikely(!self->i_type->it_file.RW_OPERATOR)
			THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);
		SCOPED_WRITELOCK(INODE_SCOPED_LOCK_FOR(self));
		inode_loadattr(self);
		{
			pos_t write_end;
			if (OVERFLOW_UADD(file_position, num_bytes, &write_end))
				THROW(E_FSERROR_DISK_FULL);
			if (write_end > self->i_filesize) {
				/* Extend the file's allocated size */
				if (!self->i_type->it_file.f_truncate)
					THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_TRUNC);
				TRY {
					(*self->i_type->it_file.f_truncate)(self, write_end);
				} EXCEPT {
					if (was_thrown(E_IOERROR_BADBOUNDS))
						PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_DISK_FULL));
					if (was_thrown(E_IOERROR_READONLY))
						PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_READONLY));
					RETHROW();
				}
				self->i_filesize = write_end;
				inode_changed(self, INODE_FATTRCHANGED);
			}
		}
#endif /* !DEFINE_IO_READ */
		if unlikely(self->mf_parts == MFILE_PARTS_ANONYMOUS) {
			/* The INode uses anonymous parts. -> Use read-through / write-through */
#ifdef DEFINE_IO_READ
			if (!self->i_type->it_file.RW_OPERATOR)
				THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);
			(*self->i_type->it_file.RW_OPERATOR)(self, buf, num_bytes, file_position, aio);
#else /* DEFINE_IO_READ */
			TRY {
				(*self->i_type->it_file.RW_OPERATOR)(self, buf, num_bytes, file_position, aio);
			} EXCEPT {
				if (was_thrown(E_IOERROR_BADBOUNDS))
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_DISK_FULL));
				if (was_thrown(E_IOERROR_READONLY))
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_READONLY));
				RETHROW();
			}
#endif /* !DEFINE_IO_READ */
			return;
		}
#ifdef LIBVIO_CONFIG_ENABLED
		if (mfile_getvio(self)) {
			struct vioargs args;
			args.va_ops = self->i_type->it_file.f_vio;
			assertf(args.va_ops,
			        "self               = %p\n"
			        "mfile_getvio(self) = %p\n"
			        "self->i_type       = %p\n",
			        self,
			        mfile_getvio(self),
			        self->i_type);
			args.va_file         = self;
			args.va_acmap_page   = 0;
			args.va_acmap_offset = 0;
			args.va_state        = NULL;
			/* Invoke VIO callbacks as vio_read() operations. */
#if defined(DEFINE_IO_PHYS) && !defined(DEFINE_IO_VECTOR)
#ifdef DEFINE_IO_READ
			vio_copyfromvio_to_phys(&args, file_position, buf, num_bytes);
#else /* DEFINE_IO_READ */
			vio_copytovio_from_phys(&args, file_position, buf, num_bytes);
#endif /* !DEFINE_IO_READ */
#elif defined(DEFINE_IO_VECTOR)
			{
#ifdef DEFINE_IO_PHYS
				struct iov_physentry ent;
				IOV_PHYSBUFFER_FOREACH_N(ent, buf)
#else
				struct iov_entry ent;
				IOV_BUFFER_FOREACH_N(ent, buf)
#endif
				{
					if (ent.ive_size > num_bytes)
						ent.ive_size = num_bytes;
#ifdef DEFINE_IO_PHYS
#ifdef DEFINE_IO_READ
					vio_copyfromvio_to_phys(&args, file_position, ent.ive_base, ent.ive_size);
#else /* DEFINE_IO_READ */
					vio_copytovio_from_phys(&args, file_position, ent.ive_base, ent.ive_size);
#endif /* !DEFINE_IO_READ */
#else /* DEFINE_IO_PHYS */
#ifdef DEFINE_IO_READ
					vio_copyfromvio(&args, file_position, ent.ive_base, ent.ive_size);
#else /* DEFINE_IO_READ */
					vio_copytovio(&args, file_position, ent.ive_base, ent.ive_size);
#endif /* !DEFINE_IO_READ */
#endif /* !DEFINE_IO_PHYS */
					if (ent.ive_size >= num_bytes)
						break;
					num_bytes -= ent.ive_size;
					file_position += ent.ive_size;
				}
			}
#elif defined(DEFINE_IO_READ)
			vio_copyfromvio(&args, file_position, buf, num_bytes);
#else
			vio_copytovio(&args, file_position, buf, num_bytes);
#endif
			return;
		}
#endif /* LIBVIO_CONFIG_ENABLED */
		assert(!task_wasconnected());

#ifdef DEFINE_IO_VECTOR
		buf_offset = 0;
#endif /* DEFINE_IO_VECTOR */
load_next_part:

		/* Locate the part concerning the requested IO, while trying to automatically
		 * include all of the data-pages that the IO could potentially ever  perform. */
		assert(!task_wasconnected());
		part = mfile_getpart(self,
		                     FLOOR_ALIGN(file_position, PAGESIZE),
		                     CEIL_ALIGN(num_bytes + (file_position % PAGESIZE), PAGESIZE));
		TRY {
#ifdef DEFINE_IO_VECTOR
#ifdef DEFINE_IO_PHYS
#ifdef DEFINE_IO_READ
			max_io_bytes = mpart_readv_p(part, buf, buf_offset, num_bytes, file_position);
#else /* DEFINE_IO_READ */
			max_io_bytes = mpart_writev_p(part, buf, buf_offset, num_bytes, file_position);
#endif /* !DEFINE_IO_READ */
#else /* DEFINE_IO_PHYS */
#ifdef DEFINE_IO_READ
			max_io_bytes = mpart_readv(part, buf, buf_offset, num_bytes, file_position);
#else /* DEFINE_IO_READ */
			max_io_bytes = mpart_writev(part, buf, buf_offset, num_bytes, file_position);
#endif /* !DEFINE_IO_READ */
#endif /* !DEFINE_IO_PHYS */
#else /* DEFINE_IO_VECTOR */
#ifdef DEFINE_IO_PHYS
#ifdef DEFINE_IO_READ
			max_io_bytes = mpart_read_p(part, buf, num_bytes, file_position);
#else /* DEFINE_IO_READ */
			max_io_bytes = mpart_write_p(part, buf, num_bytes, file_position);
#endif /* !DEFINE_IO_READ */
#else /* DEFINE_IO_PHYS */
#ifdef DEFINE_IO_READ
			max_io_bytes = mpart_read(part, buf, num_bytes, file_position);
#else /* DEFINE_IO_READ */
			max_io_bytes = mpart_write(part, buf, num_bytes, file_position);
#endif /* !DEFINE_IO_READ */
#endif /* !DEFINE_IO_PHYS */
#endif /* !DEFINE_IO_VECTOR */
		} EXCEPT {
			decref(part);
			RETHROW();
		}
		decref(part);

		/* Check if all requested bytes have now been read. */
		if (max_io_bytes >= num_bytes)
			return;
#ifdef DEFINE_IO_VECTOR
		buf_offset += max_io_bytes;
#elif defined(DEFINE_IO_PHYS)
		buf += max_io_bytes;
#else
		buf = (byte_t *)buf + max_io_bytes;
#endif
		file_position += max_io_bytes;
		num_bytes -= max_io_bytes;
		assert(!task_wasconnected());
		goto load_next_part;
	} EXCEPT {
		aio_multihandle_fail(aio);
	}
#else /* DEFINE_IO_ASYNC */
	struct aio_multihandle_generic hand;
	aio_multihandle_generic_init(&hand);
	assert(!task_wasconnected());
	TRY {
		TRY {
			FUNC1(inode_a)(self,
			               buf,
			               num_bytes,
			               file_position,
			               &hand);
			aio_multihandle_done(&hand);
		} EXCEPT {
			aio_multihandle_fail(&hand);
		}
		/* Wait for AIO completion */
		aio_multihandle_generic_waitfor(&hand);
		aio_multihandle_generic_checkerror(&hand);
	} EXCEPT {
		aio_multihandle_generic_fini(&hand);
		RETHROW();
	}
	aio_multihandle_generic_fini(&hand);
#endif /* !DEFINE_IO_ASYNC */
}

#ifdef DEFINE_IO_READ
#define FUNC1_READ(x) FUNC0(x##read)
#ifdef DEFINE_IO_ASYNC
#define FUNC2_READ(x) FUNC1_READ(x##a)
#else /* DEFINE_IO_ASYNC */
#define FUNC2_READ    FUNC1_READ
#endif /* !DEFINE_IO_ASYNC */


#ifdef DEFINE_IO_PHYS
#ifndef INODE_FLEX_READ_PHYS_DEFINED
#define INODE_FLEX_READ_PHYS_DEFINED 1
PRIVATE size_t KCALL
do_inode_flexread_phys(struct inode *__restrict self,
                       physaddr_t buf, size_t num_bytes,
                       pos_t file_position) {
	size_t temp, result = 0;
	pagedir_pushval_t backup;
	byte_t *tramp;
	bool is_first;
	is_first = true;
	tramp    = THIS_TRAMPOLINE;
	for (;;) {
		size_t page_bytes;
		page_bytes = PAGESIZE - (buf & PAGEMASK);
		if (page_bytes > num_bytes)
			page_bytes = num_bytes;
		if (is_first) {
			backup = pagedir_push_mapone(tramp, buf & ~PAGEMASK,
			                             PAGEDIR_PROT_WRITE);
			is_first = false;
		} else {
			pagedir_mapone(tramp, buf & ~PAGEMASK,
			               PAGEDIR_PROT_WRITE);
		}
		pagedir_syncone(tramp);
		/* Copy memory. */
		TRY {
			temp = (*self->i_type->it_file.f_flexread)(self,
			                                           tramp + ((ptrdiff_t)buf & PAGEMASK),
			                                           page_bytes, file_position);
		} EXCEPT {
			/* Try-catch is required, because `src' may be a user-buffer,
			 * in  which case access may cause an exception to be thrown. */
			pagedir_pop_mapone(tramp, backup);
			RETHROW();
		}
		result += temp;
		if (temp < page_bytes)
			break;
		if (page_bytes >= num_bytes)
			break;
		num_bytes -= page_bytes;
		buf += page_bytes;
		file_position += page_bytes;
	}
	pagedir_pop_mapone(tramp, backup);
	return result;
}

#endif /* !INODE_FLEX_READ_PHYS_DEFINED */

#endif /* DEFINE_IO_PHYS */


#ifdef DEFINE_IO_ASYNC
#ifdef DEFINE_IO_VECTOR
	NONNULL((1, 2, 5))
#else /* DEFINE_IO_VECTOR */
	NONNULL((1, 5))
#endif /* !DEFINE_IO_VECTOR */
#else /* DEFINE_IO_ASYNC */
#ifdef DEFINE_IO_VECTOR
	NONNULL((1, 2))
#else /* DEFINE_IO_VECTOR */
	NONNULL((1))
#endif /* !DEFINE_IO_VECTOR */
#endif /* !DEFINE_IO_ASYNC */
	size_t
#ifdef DEFINE_IO_ASYNC
NOTHROW(KCALL FUNC2_READ(inode_))(struct inode *__restrict self,
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
                                  struct iov_physbuffer *__restrict buf,
#elif defined(DEFINE_IO_VECTOR)
                                  struct iov_buffer *__restrict buf,
#elif defined(DEFINE_IO_PHYS)
                                  physaddr_t buf,
#else
                                  CHECKED USER void *buf,
#endif
                                  size_t num_bytes, pos_t file_position,
                                  struct aio_multihandle *__restrict aio)
#else /* DEFINE_IO_ASYNC */
(KCALL FUNC2_READ(inode_))(struct inode *__restrict self,
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
                           struct iov_physbuffer *__restrict buf,
#elif defined(DEFINE_IO_VECTOR)
                           struct iov_buffer *__restrict buf,
#elif defined(DEFINE_IO_PHYS)
                           physaddr_t buf,
#else
                           CHECKED USER void *buf,
#endif
                           size_t num_bytes,
                           pos_t file_position)
#endif /* !DEFINE_IO_ASYNC */
#ifdef DEFINE_IO_ASYNC
#ifdef DEFINE_IO_PHYS
		THROWS_INDIRECT(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...)
#else /* DEFINE_IO_PHYS */
		THROWS_INDIRECT(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, E_SEGFAULT, ...)
#endif /* !DEFINE_IO_PHYS */
#else /* DEFINE_IO_ASYNC */
#ifdef DEFINE_IO_PHYS
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...)
#else /* DEFINE_IO_PHYS */
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, E_SEGFAULT, ...)
#endif /* !DEFINE_IO_PHYS */
#endif /* !DEFINE_IO_ASYNC */
{
	pos_t file_end;
	/* Check for special case: The INode implements the flexible-read interface. */
	if (self->i_type->it_file.f_flexread) {
#if defined(DEFINE_IO_VECTOR)
		size_t temp, result = 0;
#ifdef DEFINE_IO_PHYS
		struct iov_physentry ent;
		IOV_PHYSBUFFER_FOREACH_N(ent, buf)
#else /* DEFINE_IO_PHYS */
		struct iov_entry ent;
		IOV_BUFFER_FOREACH_N(ent, buf)
#endif /* !DEFINE_IO_PHYS */
		{
#ifdef DEFINE_IO_PHYS
			temp = do_inode_flexread_phys(self,
			                              ent.ive_base,
			                              ent.ive_size,
			                              file_position);
#else /* DEFINE_IO_PHYS */
			temp = (*self->i_type->it_file.f_flexread)(self,
			                                           ent.ive_base,
			                                           ent.ive_size,
			                                           file_position);
#endif /* !DEFINE_IO_PHYS */
			result += temp;
			if (temp < ent.ive_size)
				break;
			file_position += temp;
		}
#ifdef DEFINE_IO_ASYNC
		(void)aio;
#endif /* DEFINE_IO_ASYNC */
		return result;
#elif defined(DEFINE_IO_PHYS)
#ifdef DEFINE_IO_ASYNC
		size_t result;
		result = do_inode_flexread_phys(self, buf, num_bytes, file_position);
		(void)aio;
		return result;
#else /* DEFINE_IO_ASYNC */
		return do_inode_flexread_phys(self, buf, num_bytes, file_position);
#endif /* !DEFINE_IO_ASYNC */
#else
#ifdef DEFINE_IO_ASYNC
		size_t result;
		result = (*self->i_type->it_file.f_flexread)(self, buf, num_bytes, file_position);
		(void)aio;
		return result;
#else /* DEFINE_IO_ASYNC */
		return (*self->i_type->it_file.f_flexread)(self, buf, num_bytes, file_position);
#endif /* !DEFINE_IO_ASYNC */
#endif
	}
#ifdef DEFINE_IO_ASYNC
	TRY
#endif /* DEFINE_IO_ASYNC */
	{
		/* Check for overflow and truncate as needed. */
		if unlikely(OVERFLOW_UADD(file_position, num_bytes, &file_end))
			file_end = (pos_t)-1, num_bytes = (size_t)((pos_t)-1 - file_position);
again:
		rwlock_read(__inode_lock(self));
		TRY {
again_check_size:
			if unlikely(file_end > self->i_filesize) {
				if (!(self->i_flags & INODE_FATTRLOADED)) {
					inode_loadattr(self);
					goto again_check_size;
				}
				if (file_position >= self->i_filesize) {
					rwlock_endread(__inode_lock(self));
					goto eof;
				}
				num_bytes = (size_t)(self->i_filesize - file_position);
			}
			FUNC2(inode_)(self,
			              buf,
			              num_bytes,
			              file_position
#ifdef DEFINE_IO_ASYNC
			              ,
			              aio
#endif /* DEFINE_IO_ASYNC */
			              );
		} EXCEPT {
			if (rwlock_endread(__inode_lock(self)))
				goto again;
			RETHROW();
		}
		rwlock_endread(__inode_lock(self));
		return num_bytes;
	}
#ifdef DEFINE_IO_ASYNC
	EXCEPT {
		aio_multihandle_fail(aio);
	}
	return 0;
#endif /* DEFINE_IO_ASYNC */
eof:
	/* Check if reading would have even been possible.
	 * Because if it wouldn't have been, then we must still throw an error! */
	if unlikely(!self->i_type->it_file.RW_OPERATOR)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);
	return 0;
}


#ifndef DEFINE_IO_ASYNC
#ifdef DEFINE_IO_VECTOR
    NONNULL((1, 2))
#else /* DEFINE_IO_VECTOR */
    NONNULL((1))
#endif /* !DEFINE_IO_VECTOR */
    size_t
(KCALL PP_CAT2(FUNC0(inode_read),_blocking))(struct inode *__restrict self,
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
                                             struct iov_physbuffer *__restrict buf,
#elif defined(DEFINE_IO_VECTOR)
                                             struct iov_buffer *__restrict buf,
#elif defined(DEFINE_IO_PHYS)
                                             physaddr_t buf,
#else
                                             CHECKED USER void *buf,
#endif
                                             size_t num_bytes,
                                             pos_t file_position)
#ifdef DEFINE_IO_PHYS
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...)
#else /* DEFINE_IO_PHYS */
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, E_SEGFAULT, ...)
#endif /* !DEFINE_IO_PHYS */
{
	pos_t file_end;
	/* Check for special case: The INode implements the flexible-read interface. */
	if (self->i_type->it_file.f_flexread) {
#if defined(DEFINE_IO_VECTOR)
		size_t temp, result = 0;
#ifdef DEFINE_IO_PHYS
		struct iov_physentry ent;
		IOV_PHYSBUFFER_FOREACH_N(ent, buf)
#else /* DEFINE_IO_PHYS */
		struct iov_entry ent;
		IOV_BUFFER_FOREACH_N(ent, buf)
#endif /* !DEFINE_IO_PHYS */
		{
#ifdef DEFINE_IO_PHYS
			temp = do_inode_flexread_phys(self,
			                              ent.ive_base,
			                              ent.ive_size,
			                              file_position);
#else /* DEFINE_IO_PHYS */
			temp = (*self->i_type->it_file.f_flexread)(self,
			                                           ent.ive_base,
			                                           ent.ive_size,
			                                           file_position);
#endif /* !DEFINE_IO_PHYS */
			result += temp;
			if (temp < ent.ive_size)
				break;
			file_position += temp;
		}
		return result;
#elif defined(DEFINE_IO_PHYS)
		return do_inode_flexread_phys(self, buf, num_bytes, file_position);
#else
		return (*self->i_type->it_file.f_flexread)(self, buf, num_bytes, file_position);
#endif
	}
	/* Check for overflow and truncate as needed. */
	if unlikely(OVERFLOW_UADD(file_position, num_bytes, &file_end))
		file_end = (pos_t)-1,num_bytes = (size_t)((pos_t)-1 - file_position);
again:
	rwlock_read(__inode_lock(self));
	TRY {
again_check_size:
		if unlikely(file_end > self->i_filesize) {
			if (!(self->i_flags & INODE_FATTRLOADED)) {
				inode_loadattr(self);
				goto again_check_size;
			}
			if (file_position >= self->i_filesize)
				goto wait_for_data;
			num_bytes = (size_t)(self->i_filesize - file_position);
		}
		FUNC2(inode_)(self,
		              buf,
		              num_bytes,
		              file_position
#ifdef DEFINE_IO_ASYNC
		              ,
		              aio
#endif /* DEFINE_IO_ASYNC */
		              );
	} EXCEPT {
		if (rwlock_endread(__inode_lock(self)))
			goto again;
		RETHROW();
	}
	rwlock_endread(__inode_lock(self));
	return num_bytes;
wait_for_data:
	rwlock_endread(__inode_lock(self));
	for (;;) {
		task_connect_for_poll(&__inode_lock(self)->rw_chmode);
		COMPILER_READ_BARRIER();
		if (file_position < self->i_filesize) {
			COMPILER_READ_BARRIER();
			task_disconnectall();
			goto again;
		}
		COMPILER_READ_BARRIER();
		task_waitfor();
		COMPILER_READ_BARRIER();
		if (file_position < self->i_filesize)
			goto again;
		COMPILER_READ_BARRIER();
	}
}
#endif


#undef FUNC2_READ
#undef FUNC1_READ
#endif /* DEFINE_IO_READ */

#undef RW_OPERATOR

DECL_END

#undef FUNC2
#undef FUNC1
#undef FUNC0
#undef VIRT_BUF
#undef PHYS_BUF
#undef DEFINE_IO_ASYNC
#undef DEFINE_IO_VECTOR
#undef DEFINE_IO_PHYS
#undef DEFINE_IO_READ
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_KERNEL
