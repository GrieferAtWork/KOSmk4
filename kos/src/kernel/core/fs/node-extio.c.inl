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
#ifdef __INTELLISENSE__
#include "node.c"
//#define DEFINE_IO_PHYS 1
//#define DEFINE_IO_VECTOR 1
//#define DEFINE_IO_ASYNC 1
//#define DEFINE_IO_KERNEL 1
#endif /* __INTELLISENSE__ */

#include <fs/node.h>
#include <kernel/swap.h>

#include <hybrid/overflow.h>

DECL_BEGIN

#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
#define FUNC0(x)   x##v_phys
#elif defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_KERNEL)
#define FUNC0(x)   x##kv
#elif defined(DEFINE_IO_VECTOR)
#define FUNC0(x)   x##v
#elif defined(DEFINE_IO_KERNEL)
#define FUNC0(x)   x##k
#elif defined(DEFINE_IO_PHYS)
#define FUNC0(x)   x##_phys
#else
#define FUNC0(x)   x
#endif

#ifndef INODE_READ_LOCKED_DEFINED
#define INODE_READ_LOCKED_DEFINED 1
INTDEF NONNULL((1)) void (KCALL inode_read_locked)(struct inode *__restrict self, CHECKED USER void *dst, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
INTDEF NONNULL((1, 2)) void (KCALL inode_read_lockedk)(struct inode *__restrict self, void *__restrict dst, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
INTDEF NONNULL((1)) void (KCALL inode_read_lockedp)(struct inode *__restrict self, physaddr_t dst, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,...);
INTDEF NONNULL((1, 2)) void (KCALL inode_read_lockedv)(struct inode *__restrict self, struct aio_buffer *__restrict buf, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
INTDEF NONNULL((1, 2)) void (KCALL inode_read_lockedvp)(struct inode *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
INTDEF NONNULL((1, 5)) void NOTHROW(KCALL inode_aread_locked)(struct inode *__restrict self, CHECKED USER void *dst, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
INTDEF NONNULL((1, 2, 5)) void NOTHROW(KCALL inode_aread_lockedk)(struct inode *__restrict self, void *__restrict dst, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
INTDEF NONNULL((1, 5)) void NOTHROW(KCALL inode_aread_lockedp)(struct inode *__restrict self, physaddr_t dst, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,...);
INTDEF NONNULL((1, 2, 5)) void NOTHROW(KCALL inode_aread_lockedv)(struct inode *__restrict self, struct aio_buffer *__restrict buf, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
INTDEF NONNULL((1, 2, 5)) void NOTHROW(KCALL inode_aread_lockedvp)(struct inode *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
#endif /* !INODE_READ_LOCKED_DEFINED */

#ifdef DEFINE_IO_ASYNC
PUBLIC
#if defined(DEFINE_IO_VECTOR) || defined(DEFINE_IO_KERNEL)
    NONNULL((1, 2, 5))
#else
    NONNULL((1, 5))
#endif
    void
NOTHROW(KCALL FUNC0(inode_areadall))(struct inode *__restrict self,
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
                                     struct aio_pbuffer *__restrict buf,
#elif defined(DEFINE_IO_VECTOR)
                                     struct aio_buffer *__restrict buf,
#elif defined(DEFINE_IO_PHYS)
                                     physaddr_t buf,
#elif defined(DEFINE_IO_KERNEL)
                                     void *__restrict buf,
#else
                                     CHECKED USER void *buf,
#endif
                                     size_t num_bytes,
                                     pos_t file_position,
                                     struct aio_multihandle *__restrict aio)
#else /* DEFINE_IO_ASYNC */
PUBLIC
#if defined(DEFINE_IO_VECTOR) || defined(DEFINE_IO_KERNEL)
    NONNULL((1, 2))
#else
    NONNULL((1))
#endif
    void
(KCALL FUNC0(inode_readall))(struct inode *__restrict self,
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
                             struct aio_pbuffer *__restrict buf,
#elif defined(DEFINE_IO_VECTOR)
                             struct aio_buffer *__restrict buf,
#elif defined(DEFINE_IO_PHYS)
                             physaddr_t buf,
#elif defined(DEFINE_IO_KERNEL)
                             void *__restrict buf,
#else
                             CHECKED USER void *buf,
#endif
                             size_t num_bytes,
                             pos_t file_position)
#endif /* !DEFINE_IO_ASYNC */
#ifdef DEFINE_IO_ASYNC
		THROWS_INDIRECT(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR_BADBOUNDS, E_IOERROR, E_SEGFAULT, ...)
#else /* DEFINE_IO_ASYNC */
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR_BADBOUNDS, E_IOERROR, E_SEGFAULT, ...)
#endif /* !DEFINE_IO_ASYNC */
{
#ifdef DEFINE_IO_ASYNC
	TRY
#endif /* DEFINE_IO_ASYNC */
	{
		pos_t file_end;
		/* Check for overflow and truncate as needed. */
		if unlikely(OVERFLOW_UADD(file_position, num_bytes, &file_end))
			goto throw_bad_bounds;
again:
		rwlock_read(&self->db_lock);
		TRY {
again_check_size:
			if unlikely(file_end > self->i_filesize) {
				if likely(!(self->i_flags & INODE_FATTRLOADED)) {
					inode_loadattr(self);
					goto again_check_size;
				}
				rwlock_endread(&self->db_lock);
				goto throw_bad_bounds;
			}
#ifdef DEFINE_IO_ASYNC
			FUNC0(inode_aread_locked)(self,
			                          buf,
			                          num_bytes,
			                          file_position,
			                          aio);
#else /* DEFINE_IO_ASYNC */
			FUNC0(inode_read_locked)(self,
			                         buf,
			                         num_bytes,
			                         file_position);
#endif /* !DEFINE_IO_ASYNC */
		} EXCEPT {
			if (rwlock_endread(&self->db_lock))
			    goto again;
			RETHROW();
		}
		rwlock_endread(&self->db_lock);
		return;
throw_bad_bounds:
		THROW(E_IOERROR_BADBOUNDS, (uintptr_t)E_IOERROR_SUBSYSTEM_FILE);
	}
#ifdef DEFINE_IO_ASYNC
	EXCEPT {
		aio_multihandle_fail(aio);
	}
#endif /* DEFINE_IO_ASYNC */
}


DECL_END

#undef FUNC0
#undef DEFINE_IO_VECTOR
#undef DEFINE_IO_PHYS
#undef DEFINE_IO_ASYNC
#undef DEFINE_IO_KERNEL
