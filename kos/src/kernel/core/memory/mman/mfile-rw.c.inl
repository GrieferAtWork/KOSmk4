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
#include "mfile-rw.c"
#define DEFINE_mfile_readv
#endif /* __INTELLISENSE__ */

#include <kernel/iovec.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>

#include <assert.h>
#include <stddef.h>

#include <libvio/access.h>

DECL_BEGIN

#if defined(DEFINE_mfile_read)
#define LOCAL_buffer_t     USER CHECKED void *
#define LOCAL_ubuffer_t    uintptr_t
#define LOCAL_mfile_vio_rw mfile_vio_read
#define LOCAL_mfile_rw     mfile_read
#define LOCAL_mpart_rw     mpart_read
#elif defined(DEFINE_mfile_write)
#define LOCAL_buffer_t     USER CHECKED void const *
#define LOCAL_ubuffer_t    uintptr_t
#define LOCAL_mfile_vio_rw mfile_vio_write
#define LOCAL_mfile_rw     mfile_write
#define LOCAL_mpart_rw     mpart_write
#elif defined(DEFINE_mfile_read_p)
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_buffer_t     physaddr_t
#define LOCAL_ubuffer_t    physaddr_t
#define LOCAL_mfile_vio_rw mfile_vio_read_p
#define LOCAL_mfile_rw     mfile_read_p
#define LOCAL_mpart_rw     mpart_read_p
#elif defined(DEFINE_mfile_write_p)
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_buffer_t     physaddr_t
#define LOCAL_ubuffer_t    physaddr_t
#define LOCAL_mfile_vio_rw mfile_vio_write_p
#define LOCAL_mfile_rw     mfile_write_p
#define LOCAL_mpart_rw     mpart_write_p
#elif defined(DEFINE_mfile_readv)
#define LOCAL_BUFFER_IS_AIO
#define LOCAL_BUFFER_IS_AIO_BUFFER
#define LOCAL_buffer_t     struct aio_buffer const *__restrict
#define LOCAL_mfile_vio_rw mfile_vio_readv
#define LOCAL_mfile_rw     mfile_readv
#define LOCAL_mpart_rw     mpart_readv
#elif defined(DEFINE_mfile_writev)
#define LOCAL_BUFFER_IS_AIO
#define LOCAL_BUFFER_IS_AIO_BUFFER
#define LOCAL_buffer_t     struct aio_buffer const *__restrict
#define LOCAL_mfile_vio_rw mfile_vio_writev
#define LOCAL_mfile_rw     mfile_writev
#define LOCAL_mpart_rw     mpart_writev
#elif defined(DEFINE_mfile_readv_p)
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_IS_AIO
#define LOCAL_BUFFER_IS_AIO_PBUFFER
#define LOCAL_buffer_t     struct aio_pbuffer const *__restrict
#define LOCAL_mfile_vio_rw mfile_vio_readv_p
#define LOCAL_mfile_rw     mfile_readv_p
#define LOCAL_mpart_rw     mpart_readv_p
#elif defined(DEFINE_mfile_writev_p)
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_IS_AIO
#define LOCAL_BUFFER_IS_AIO_PBUFFER
#define LOCAL_buffer_t     struct aio_pbuffer const *__restrict
#define LOCAL_mfile_vio_rw mfile_vio_writev_p
#define LOCAL_mfile_rw     mfile_writev_p
#define LOCAL_mpart_rw     mpart_writev_p
#else /* ... */
#error "Bad configuration"
#endif /* !... */

PUBLIC NONNULL((1)) void KCALL
LOCAL_mfile_vio_rw(struct mfile *__restrict self,
                   struct mpart *part,
                   LOCAL_buffer_t buffer,
#ifdef LOCAL_BUFFER_IS_AIO
                   size_t buf_offset,
#endif /* LOCAL_BUFFER_IS_AIO */
                   size_t num_bytes, pos_t offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	struct vioargs args;
	args.va_ops = mfile_getvio(self);
	assert(args.va_ops);
	args.va_acmap_page   = NULL;
	args.va_acmap_offset = 0;
	args.va_state        = NULL;
	args.va_file         = self;
	args.va_part         = part;
#if defined(DEFINE_mfile_read)
	vio_copyfromvio(&args, (vio_addr_t)offset, buffer, num_bytes);
#elif defined(DEFINE_mfile_write)
	vio_copytovio(&args, (vio_addr_t)offset, buffer, num_bytes);
#elif defined(DEFINE_mfile_read_p)
	vio_copyfromvio_to_phys(&args, (vio_addr_t)offset, (__physaddr_t)buffer, num_bytes);
#elif defined(DEFINE_mfile_write_p)
	vio_copytovio_from_phys(&args, (vio_addr_t)offset, (__physaddr_t)buffer, num_bytes);
#elif defined(LOCAL_BUFFER_IS_AIO)
	{
#ifdef LOCAL_BUFFER_IS_PHYS
		struct aio_pbuffer_entry ent;
		AIO_PBUFFER_FOREACH(ent, buffer)
#else /* LOCAL_BUFFER_IS_PHYS */
		struct aio_buffer_entry ent;
		AIO_BUFFER_FOREACH(ent, buffer)
#endif /* !LOCAL_BUFFER_IS_PHYS */
		{
			if (buf_offset) {
				if (buf_offset >= ent.ab_size) {
					buf_offset -= ent.ab_size;
					continue;
				}
				ent.ab_base += buf_offset;
				ent.ab_size -= buf_offset;
				buf_offset = 0;
			}
			if (ent.ab_size > num_bytes)
				ent.ab_size = num_bytes;
#ifdef DEFINE_mfile_readv
			vio_copyfromvio(&args, (vio_addr_t)offset, ent.ab_base, ent.ab_size);
#elif defined(DEFINE_mfile_writev)
			vio_copytovio(&args, (vio_addr_t)offset, ent.ab_base, ent.ab_size);
#elif defined(DEFINE_mfile_readv_p)
			vio_copyfromvio_to_phys(&args, (vio_addr_t)offset, (__physaddr_t)ent.ab_base, ent.ab_size);
#elif defined(DEFINE_mfile_writev_p)
			vio_copytovio_from_phys(&args, (vio_addr_t)offset, (__physaddr_t)ent.ab_base, ent.ab_size);
#endif /* ... */
			if (ent.ab_size >= num_bytes)
				break;
			num_bytes -= ent.ab_size;
			offset += ent.ab_size;
		}
	}
#else /* ... */
#error "Bad configuration"
#endif /* !... */
}

PUBLIC NONNULL((1)) void KCALL
LOCAL_mfile_rw(struct mfile *__restrict self,
               LOCAL_buffer_t buffer,
#ifdef LOCAL_BUFFER_IS_AIO
               size_t buf_offset,
#endif /* LOCAL_BUFFER_IS_AIO */
               size_t num_bytes, pos_t offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	if (self->mf_parts == MFILE_PARTS_ANONYMOUS && mfile_getvio(self) != NULL) {
		/* Directly read to/from VIO */
		LOCAL_mfile_vio_rw(self, NULL, buffer,
#ifdef LOCAL_BUFFER_IS_AIO
		                   buf_offset,
#endif /* LOCAL_BUFFER_IS_AIO */
		                   num_bytes, offset);
		return;
	}
	while (num_bytes) {
		size_t count;
		REF struct mpart *part;
		part = mfile_getpart(self, offset, num_bytes);
		FINALLY_DECREF_UNLIKELY(part);
		/* Do I/O on the part. */
		count = LOCAL_mpart_rw(part, buffer,
#ifdef LOCAL_BUFFER_IS_AIO
		                       buf_offset,
#endif /* LOCAL_BUFFER_IS_AIO */
		                       num_bytes,
		                       offset);
		assert(count <= num_bytes);
		if (count >= num_bytes)
			break;
#ifdef LOCAL_BUFFER_IS_AIO
		buf_offset += count;
#else /* LOCAL_BUFFER_IS_AIO */
		buffer = (LOCAL_buffer_t)((LOCAL_ubuffer_t)buffer + count);
#endif /* !LOCAL_BUFFER_IS_AIO */
		offset += count;
		num_bytes -= count;
	}
}

#undef LOCAL_BUFFER_IS_PHYS
#undef LOCAL_BUFFER_IS_AIO
#undef LOCAL_BUFFER_IS_AIO_BUFFER
#undef LOCAL_BUFFER_IS_AIO_PBUFFER
#undef LOCAL_ubuffer_t
#undef LOCAL_buffer_t
#undef LOCAL_mfile_vio_rw
#undef LOCAL_mfile_rw
#undef LOCAL_mpart_rw

DECL_END

#undef DEFINE_mfile_read
#undef DEFINE_mfile_write
#undef DEFINE_mfile_read_p
#undef DEFINE_mfile_write_p
#undef DEFINE_mfile_readv
#undef DEFINE_mfile_writev
#undef DEFINE_mfile_readv_p
#undef DEFINE_mfile_writev_p
