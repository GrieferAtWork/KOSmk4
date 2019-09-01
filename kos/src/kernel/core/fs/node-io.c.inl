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
#ifdef __INTELLISENSE__
#include "node.c"
#endif

#include <fs/node.h>
#include <kernel/swap.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include "../memory/vm/vm-partapi.h"

#ifdef __INTELLISENSE__
#undef IO_ASYNC
#undef IO_READ
#undef IO_WRITE
#undef IO_PHYS
#undef IO_VECTOR
#undef IO_KERNEL

//#define IO_ASYNC 1
#define IO_READ 1
//#define IO_WRITE 1
#define IO_PHYS 1
#define IO_VECTOR 1
//#define IO_KERNEL 1
#endif

DECL_BEGIN

#if defined(IO_VECTOR) && defined(IO_PHYS)
#define FUNC0(x) x##v_phys
#elif defined(IO_PHYS)
#define FUNC0(x) x##_phys
#elif defined(IO_VECTOR) && defined(IO_KERNEL)
#define FUNC0(x) x##kv
#elif defined(IO_VECTOR)
#define FUNC0(x) x##v
#elif defined(IO_KERNEL)
#define FUNC0(x) x##k
#else
#define FUNC0(x) x
#endif
#ifdef IO_READ
#define FUNC1(x) FUNC0(x##read_locked)
#else
#define FUNC1(x) FUNC0(x##write)
#endif
#ifdef IO_ASYNC
#define FUNC2(x) FUNC1(x##a)
#else
#define FUNC2    FUNC1
#endif


#ifndef INODE_PARTIO_DEFINED
#define INODE_PARTIO_DEFINED 1
INTDEF NONNULL((1, 2)) void KCALL
inode_do_load_datapart_pages(struct inode *__restrict self,
                             struct vm_datapart *__restrict part,
                             size_t partrelative_pageno,
                             size_t num_data_pages,
                             struct aio_multihandle *__restrict aio);
INTDEF NONNULL((1, 2)) void KCALL
inode_do_load_datapart_pages_sync(struct inode *__restrict self,
                                  struct vm_datapart *__restrict part,
                                  size_t partrelative_pageno,
                                  size_t num_data_pages);
INTDEF NONNULL((1, 2)) void KCALL
inode_do_save_datapart_pages(struct inode *__restrict self,
                             struct vm_datapart *__restrict part,
                             size_t partrelative_pageno,
                             size_t num_data_pages,
                             struct aio_multihandle *__restrict aio);
#endif /* !INODE_PARTIO_DEFINED */



#ifdef IO_READ
INTERN
#else
PUBLIC
#endif
#ifdef IO_ASYNC
#if defined(IO_VECTOR) || defined(IO_KERNEL)
    NONNULL((1, 2, 5))
#else /* IO_VECTOR */
    NONNULL((1, 5))
#endif /* !IO_VECTOR */
#else /* IO_ASYNC */
#if defined(IO_VECTOR) || defined(IO_KERNEL)
    NONNULL((1, 2))
#else /* IO_VECTOR */
    NONNULL((1))
#endif /* !IO_VECTOR */
#endif /* !IO_ASYNC */
    void
#ifdef IO_ASYNC
NOTHROW(KCALL FUNC2(inode_))(struct inode *__restrict self,
#if defined(IO_VECTOR) && defined(IO_PHYS)
                             struct aio_pbuffer *__restrict buf,
#elif defined(IO_VECTOR)
                             struct aio_buffer *__restrict buf,
#elif defined(IO_PHYS)
                             vm_phys_t buf,
#elif defined(IO_READ) && defined(IO_KERNEL)
                             void *__restrict buf,
#elif defined(IO_READ)
                             CHECKED USER void *buf,
#elif defined(IO_KERNEL)
                             void const *__restrict buf,
#else
                             CHECKED USER void const *buf,
#endif
                             size_t num_bytes, pos_t file_position,
                             struct aio_multihandle *__restrict aio)
#else /* IO_ASYNC */
(KCALL FUNC2(inode_))(struct inode *__restrict self,
#if defined(IO_VECTOR) && defined(IO_PHYS)
                      struct aio_pbuffer *__restrict buf,
#elif defined(IO_VECTOR)
                      struct aio_buffer *__restrict buf,
#elif defined(IO_PHYS)
                      vm_phys_t buf,
#elif defined(IO_READ) && defined(IO_KERNEL)
                      void *__restrict buf,
#elif defined(IO_READ)
                      CHECKED USER void *buf,
#elif defined(IO_KERNEL)
                      void const *__restrict buf,
#else
                      CHECKED USER void const *buf,
#endif
                      size_t num_bytes,
                      pos_t file_position)
#endif /* !IO_ASYNC */
#ifdef IO_ASYNC
#ifdef IO_PHYS
		THROWS_INDIRECT(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...)
#else /* IO_PHYS */
		THROWS_INDIRECT(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, E_SEGFAULT, ...)
#endif /* !IO_PHYS */
#else /* IO_ASYNC */
#ifdef IO_PHYS
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...)
#else /* IO_PHYS */
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, E_SEGFAULT, ...)
#endif /* !IO_PHYS */
#endif /* !IO_ASYNC */
{
#ifdef IO_ASYNC
	TRY {
		struct vm_datapart *part;
		size_t max_io_bytes;
#ifdef IO_VECTOR
		uintptr_t buf_offset;
#endif
#ifndef IO_READ
		SCOPED_WRITELOCK((struct vm_datablock *)self);
#ifdef IO_PHYS
		if unlikely(!self->i_type->it_file.f_pwritev)
			THROW(E_FSERROR_UNSUPPORTED_OPERATION,(uintptr_t)E_FILESYSTEM_OPERATION_WRITE);
#elif defined(IO_VECTOR)
		if unlikely(!self->i_type->it_file.f_writev)
			THROW(E_FSERROR_UNSUPPORTED_OPERATION,(uintptr_t)E_FILESYSTEM_OPERATION_WRITE);
#elif defined(IO_PHYS)
		if unlikely(!self->i_type->it_file.f_pwrite)
			THROW(E_FSERROR_UNSUPPORTED_OPERATION,(uintptr_t)E_FILESYSTEM_OPERATION_WRITE);
#else
		if unlikely(!self->i_type->it_file.f_write)
			THROW(E_FSERROR_UNSUPPORTED_OPERATION,(uintptr_t)E_FILESYSTEM_OPERATION_WRITE);
#endif
		inode_loadattr(self);
		{
			pos_t write_end;
			if (OVERFLOW_UADD(file_position, num_bytes, &write_end))
				THROW(E_FSERROR_DISK_FULL);
			if (write_end > self->i_filesize) {
				/* Extend the file's allocated size */
				if (!self->i_type->it_file.f_truncate)
					THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_TRUNC);
				TRY {
					(*self->i_type->it_file.f_truncate)(self, write_end);
				} EXCEPT {
					if (was_thrown(E_IOERROR_BADBOUNDS))
						PERTASK_SET(_this_exception_info.ei_code, ERROR_CODEOF(E_FSERROR_DISK_FULL));
					if (was_thrown(E_IOERROR_READONLY))
						PERTASK_SET(_this_exception_info.ei_code, ERROR_CODEOF(E_FSERROR_READONLY));
					RETHROW();
				}
				self->i_filesize = write_end;
				inode_changed(self, INODE_FATTRCHANGED);
			}
		}
#endif
		if unlikely(self->db_parts == VM_DATABLOCK_ANONPARTS) {
			/* The INode uses anonymous parts. -> Use read-through / write-through */
#ifdef IO_READ
#if defined(IO_VECTOR) && defined(IO_PHYS)
			if (!self->i_type->it_file.f_preadv)
				THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_READ);
			(*self->i_type->it_file.f_preadv)(self, buf, num_bytes, file_position, aio);
#elif defined(IO_VECTOR)
			if (!self->i_type->it_file.f_readv)
				THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_READ);
			(*self->i_type->it_file.f_readv)(self, buf, num_bytes, file_position, aio);
#elif defined(IO_PHYS)
			if (!self->i_type->it_file.f_pread)
				THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_READ);
			(*self->i_type->it_file.f_pread)(self, buf, num_bytes, file_position, aio);
#else
			if (!self->i_type->it_file.f_read)
				THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_READ);
			(*self->i_type->it_file.f_read)(self, buf, num_bytes, file_position, aio);
#endif
#else
			TRY {
#if defined(IO_VECTOR) && defined(IO_PHYS)
				(*self->i_type->it_file.f_pwritev)(self, buf, num_bytes, file_position, aio);
#elif defined(IO_VECTOR)
				(*self->i_type->it_file.f_writev)(self, buf, num_bytes, file_position, aio);
#elif defined(IO_PHYS)
				(*self->i_type->it_file.f_pwrite)(self, buf, num_bytes, file_position, aio);
#else
				(*self->i_type->it_file.f_write)(self, buf, num_bytes, file_position, aio);
#endif
			} EXCEPT {
				if (was_thrown(E_IOERROR_BADBOUNDS))
					PERTASK_SET(_this_exception_info.ei_code, (error_code_t)E_FSERROR_DISK_FULL);
				if (was_thrown(E_IOERROR_READONLY))
					PERTASK_SET(_this_exception_info.ei_code, (error_code_t)E_FSERROR_READONLY);
				RETHROW();
			}
#endif
			return;
		}
#ifdef CONFIG_VIO
		if (self->db_vio) {
			struct vio_args args;
			args.va_type = self->i_type->it_file.f_vio;
			assert(args.va_type);
			args.va_block           = self;
			args.va_part            = NULL;
			args.va_access_pageaddr = 0;
			args.va_access_partoff  = 0;
			args.va_state           = NULL;
			/* Invoke VIO callbacks as vio_read() operations. */
#if defined(IO_PHYS) && !defined(IO_VECTOR)
#ifdef IO_READ
			vio_copyfromvio_to_phys(&args, buf, file_position, num_bytes);
#else  /* IO_READ */
			vio_copytovio_from_phys(&args, file_position, buf, num_bytes);
#endif /* !IO_READ */
#elif defined(IO_VECTOR)
			{
#ifdef IO_PHYS
				struct aio_pbuffer_entry ent;
				AIO_PBUFFER_FOREACH_N(ent, buf)
#else
				struct aio_buffer_entry ent;
				AIO_BUFFER_FOREACH_N(ent, buf)
#endif
				{
					if (ent.ab_size > num_bytes)
						ent.ab_size = num_bytes;
#ifdef IO_PHYS
#ifdef IO_READ
					vio_copyfromvio_to_phys(&args,
					                        ent.ab_base,
					                        file_position,
					                        ent.ab_size);
#else  /* IO_READ */
					vio_copytovio_from_phys(&args,
					                        ent.ab_base,
					                        file_position,
					                        ent.ab_size);
#endif /* !IO_READ */
#else  /* IO_PHYS */
#ifdef IO_READ
					vio_copyfromvio(&args,
					                (byte_t *)ent.ab_base,
					                file_position,
					                ent.ab_size);
#else  /* IO_READ */
					vio_copytovio(&args,
					              file_position,
					              (byte_t *)ent.ab_base,
					              ent.ab_size);
#endif /* !IO_READ */
#endif /* !IO_PHYS */
					if (ent.ab_size >= num_bytes)
						break;
					num_bytes -= ent.ab_size;
					file_position += ent.ab_size;
				}
			}
#elif defined(IO_READ)
			vio_copyfromvio(&args, buf, file_position, num_bytes);
#else
			vio_copytovio(&args, file_position, buf, num_bytes);
#endif
			return;
		}
#endif /* CONFIG_VIO */

#ifdef IO_VECTOR
		buf_offset = 0;
#endif
load_next_part:

		/* Locate the part concerning the requested IO, while trying to automatically
		 * include all of the data-pages that the IO could potentially ever perform. */
		part = vm_datablock_locatepart(self,
		                               (vm_vpage64_t)(file_position / pagedir_pagesize()),
		                               CEILDIV(num_bytes + (file_position % pagedir_pagesize()), pagedir_pagesize()));
		TRY {
			vm_daddr_t part_offset = (vm_daddr_t)(file_position - vm_datapart_startbyte(part));
#ifdef IO_VECTOR
#ifdef IO_PHYS
			struct aio_pbuffer view;
			aio_pbuffer_init_view_after(&view, buf, buf_offset);
#else
			struct aio_buffer view;
			aio_buffer_init_view_after(&view, buf, buf_offset);
#endif
#ifdef IO_READ
			max_io_bytes = FUNC0(vm_datapart_read)(part, &view, part_offset);
#else  /* IO_READ */
			max_io_bytes = FUNC0(vm_datapart_write)(part, &view, num_bytes, part_offset);
#endif /* !IO_READ */
#elif defined(IO_KERNEL)
#ifdef IO_READ
			max_io_bytes = vm_datapart_read_unsafe(part, buf, num_bytes, part_offset);
#else  /* IO_READ */
			max_io_bytes = vm_datapart_write_unsafe(part, buf, num_bytes, num_bytes, part_offset);
#endif /* !IO_READ */
#else
#ifdef IO_READ
			max_io_bytes = FUNC0(vm_datapart_read)(part, buf, num_bytes, part_offset);
#else  /* IO_READ */
			max_io_bytes = FUNC0(vm_datapart_write)(part, buf, num_bytes, num_bytes, part_offset);
#endif /* !IO_READ */
#endif
		} EXCEPT {
			decref(part);
			RETHROW();
		}
		decref(part);

		/* Check if all requested bytes have now been read. */
		if (max_io_bytes >= num_bytes)
			return;
#ifdef IO_VECTOR
		buf_offset += max_io_bytes;
#elif defined(IO_PHYS)
		buf += max_io_bytes;
#else
		buf = (byte_t *)buf + max_io_bytes;
#endif
		file_position += max_io_bytes;
		num_bytes -= max_io_bytes;
		goto load_next_part;
	} EXCEPT {
		aio_multihandle_fail(aio);
	}
#else /* IO_ASYNC */
	struct aio_multihandle_generic hand;
	aio_multihandle_generic_init(&hand);
	FUNC1(inode_a)(self,
	               buf,
	               num_bytes,
	               file_position,
	               &hand);
	aio_multihandle_done(&hand);
	/* Wait for AIO completion */
	TRY {
		aio_multihandle_generic_waitfor(&hand);
		aio_multihandle_generic_checkerror(&hand);
	} EXCEPT {
		aio_multihandle_fini(&hand);
		RETHROW();
	}
	aio_multihandle_fini(&hand);
#endif /* !IO_ASYNC */
}

#ifdef IO_READ
#define FUNC1_READ(x) FUNC0(x##read)
#ifdef IO_ASYNC
#define FUNC2_READ(x) FUNC1_READ(x##a)
#else
#define FUNC2_READ    FUNC1_READ
#endif

#ifdef IO_ASYNC
#ifdef IO_VECTOR
    NONNULL((1, 2, 5))
#else /* IO_VECTOR */
    NONNULL((1, 5))
#endif /* !IO_VECTOR */
#else /* IO_ASYNC */
#ifdef IO_VECTOR
    NONNULL((1, 2))
#else /* IO_VECTOR */
    NONNULL((1))
#endif /* !IO_VECTOR */
#endif /* !IO_ASYNC */
    size_t
#ifdef IO_ASYNC
NOTHROW(KCALL FUNC2_READ(inode_))(struct inode *__restrict self,
#if defined(IO_VECTOR) && defined(IO_PHYS)
                                  struct aio_pbuffer *__restrict buf,
#elif defined(IO_VECTOR)
                                  struct aio_buffer *__restrict buf,
#elif defined(IO_PHYS)
                                  vm_phys_t buf,
#else
                                  CHECKED USER void *buf,
#endif
                                  size_t num_bytes, pos_t file_position,
                                  struct aio_multihandle *__restrict aio)
#else /* IO_ASYNC */
(KCALL FUNC2_READ(inode_))(struct inode *__restrict self,
#if defined(IO_VECTOR) && defined(IO_PHYS)
                           struct aio_pbuffer *__restrict buf,
#elif defined(IO_VECTOR)
                           struct aio_buffer *__restrict buf,
#elif defined(IO_PHYS)
                           vm_phys_t buf,
#else
                           CHECKED USER void *buf,
#endif
                           size_t num_bytes,
                           pos_t file_position)
#endif /* !IO_ASYNC */
#ifdef IO_ASYNC
#ifdef IO_PHYS
		THROWS_INDIRECT(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...)
#else /* IO_PHYS */
		THROWS_INDIRECT(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, E_SEGFAULT, ...)
#endif /* !IO_PHYS */
#else /* IO_ASYNC */
#ifdef IO_PHYS
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...)
#else /* IO_PHYS */
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, E_SEGFAULT, ...)
#endif /* !IO_PHYS */
#endif /* !IO_ASYNC */
{
	pos_t file_end;
#ifdef IO_ASYNC
	TRY
#endif
	{
		/* Check for overflow and truncate as needed. */
		if unlikely(OVERFLOW_UADD(file_position, num_bytes, &file_end))
			file_end = (pos_t)-1, num_bytes = (size_t)((pos_t)-1 - file_position);
again:
		rwlock_read(&self->db_lock);
		TRY {
again_check_size:
			if unlikely(file_end > self->i_filesize) {
				if (!(self->i_flags & INODE_FATTRLOADED)) {
					inode_loadattr(self);
					goto again_check_size;
				}
				if (file_position >= self->i_filesize) {
					rwlock_endread(&self->db_lock);
					return 0;
				}
				num_bytes = (size_t)(self->i_filesize - file_position);
			}
			FUNC2(inode_)(self,
			              buf,
			              num_bytes,
			              file_position
#ifdef IO_ASYNC
			              , aio
#endif
			              );
		} EXCEPT {
			if (rwlock_endread(&self->db_lock))
				goto again;
			RETHROW();
		}
		rwlock_endread(&self->db_lock);
		return num_bytes;
	}
#ifdef IO_ASYNC
	EXCEPT {
		aio_multihandle_fail(aio);
	}
	return 0;
#endif
}


#ifndef IO_ASYNC
#ifdef IO_VECTOR
    NONNULL((1, 2))
#else /* IO_VECTOR */
    NONNULL((1))
#endif /* !IO_VECTOR */
    size_t
(KCALL PP_CAT2(FUNC0(inode_read),_blocking))(struct inode *__restrict self,
#if defined(IO_VECTOR) && defined(IO_PHYS)
                                             struct aio_pbuffer *__restrict buf,
#elif defined(IO_VECTOR)
                                             struct aio_buffer *__restrict buf,
#elif defined(IO_PHYS)
                                             vm_phys_t buf,
#else
                                             CHECKED USER void *buf,
#endif
                                             size_t num_bytes,
                                             pos_t file_position)
#ifdef IO_PHYS
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...)
#else /* IO_PHYS */
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, E_SEGFAULT, ...)
#endif /* !IO_PHYS */
{
	pos_t file_end;
	/* Check for overflow and truncate as needed. */
	if unlikely(OVERFLOW_UADD(file_position, num_bytes, &file_end))
		file_end = (pos_t)-1,num_bytes = (size_t)((pos_t)-1 - file_position);
again:
	rwlock_read(&self->db_lock);
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
#ifdef IO_ASYNC
		              , aio
#endif
		              );
	} EXCEPT {
		if (rwlock_endread(&self->db_lock))
			goto again;
		RETHROW();
	}
	rwlock_endread(&self->db_lock);
	return num_bytes;
wait_for_data:
	rwlock_endread(&self->db_lock);
	for (;;) {
		task_connect(&self->db_lock.rw_chmode);
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
#endif /* IO_READ */


DECL_END

#undef FUNC2
#undef FUNC1
#undef FUNC0
#undef VIRT_BUF
#undef PHYS_BUF
#undef IO_ASYNC
#undef IO_VECTOR
#undef IO_PHYS
#undef IO_READ
#undef IO_WRITE
#undef IO_KERNEL
