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
#ifdef __INTELLISENSE__
#include "mfile-rw.c"
#define DEFINE_mfile_vioreadv
#endif /* __INTELLISENSE__ */

#include <kernel/iovec.h>
#include <kernel/mman/mfile.h>

#include <assert.h>
#include <stddef.h>

#include <libvio/api.h>
#include <libvio/access.h>

#ifdef LIBVIO_CONFIG_ENABLED
DECL_BEGIN

#if defined(DEFINE_mfile_vioread)
#define LOCAL_buffer_t     NCX void *
#define LOCAL_mfile_vio_rw mfile_vioread
#elif defined(DEFINE_mfile_viowrite)
#define LOCAL_buffer_t     NCX void const *
#define LOCAL_mfile_vio_rw mfile_viowrite
#elif defined(DEFINE_mfile_vioread_p)
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_buffer_t     physaddr_t
#define LOCAL_mfile_vio_rw mfile_vioread_p
#elif defined(DEFINE_mfile_viowrite_p)
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_buffer_t     physaddr_t
#define LOCAL_mfile_vio_rw mfile_viowrite_p
#elif defined(DEFINE_mfile_vioreadv)
#define LOCAL_BUFFER_IS_IOVEC
#define LOCAL_buffer_t     struct iov_buffer const *__restrict
#define LOCAL_mfile_vio_rw mfile_vioreadv
#elif defined(DEFINE_mfile_viowritev)
#define LOCAL_BUFFER_IS_IOVEC
#define LOCAL_buffer_t     struct iov_buffer const *__restrict
#define LOCAL_mfile_vio_rw mfile_viowritev
#elif defined(DEFINE_mfile_vioreadv_p)
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_IS_IOVEC
#define LOCAL_buffer_t     struct iov_physbuffer const *__restrict
#define LOCAL_mfile_vio_rw mfile_vioreadv_p
#elif defined(DEFINE_mfile_viowritev_p)
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_IS_IOVEC
#define LOCAL_buffer_t     struct iov_physbuffer const *__restrict
#define LOCAL_mfile_vio_rw mfile_viowritev_p
#else /* ... */
#error "Bad configuration"
#endif /* !... */

PUBLIC BLOCKING NONNULL((1)) void KCALL
LOCAL_mfile_vio_rw(struct mfile *__restrict self,
                   LOCAL_buffer_t buffer,
#ifdef LOCAL_BUFFER_IS_IOVEC
                   size_t buf_offset,
#endif /* LOCAL_BUFFER_IS_IOVEC */
                   size_t num_bytes, pos_t offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	struct vioargs args;
	args.va_ops = self->mf_ops->mo_vio;
	assert(args.va_ops);
	args.va_acmap_page   = NULL;
	args.va_acmap_offset = 0;
	args.va_state        = NULL;
	args.va_file         = self;
#if defined(DEFINE_mfile_vioread)
	vio_copyfromvio(&args, (vio_addr_t)offset, buffer, num_bytes);
#elif defined(DEFINE_mfile_viowrite)
	vio_copytovio(&args, (vio_addr_t)offset, buffer, num_bytes);
#elif defined(DEFINE_mfile_vioread_p)
	vio_copyfromvio_to_phys(&args, (vio_addr_t)offset, (__physaddr_t)buffer, num_bytes);
#elif defined(DEFINE_mfile_viowrite_p)
	vio_copytovio_from_phys(&args, (vio_addr_t)offset, (__physaddr_t)buffer, num_bytes);
#elif defined(LOCAL_BUFFER_IS_IOVEC)
	{
#ifdef LOCAL_BUFFER_IS_PHYS
		struct iov_physentry ent;
		IOV_PHYSBUFFER_FOREACH(ent, buffer)
#else /* LOCAL_BUFFER_IS_PHYS */
		struct iov_entry ent;
		IOV_BUFFER_FOREACH(ent, buffer)
#endif /* !LOCAL_BUFFER_IS_PHYS */
		{
			if (buf_offset) {
				if (buf_offset >= ent.ive_size) {
					buf_offset -= ent.ive_size;
					continue;
				}
				ent.ive_base += buf_offset;
				ent.ive_size -= buf_offset;
				buf_offset = 0;
			}
			if (ent.ive_size > num_bytes)
				ent.ive_size = num_bytes;
#ifdef DEFINE_mfile_vioreadv
			vio_copyfromvio(&args, (vio_addr_t)offset, ent.ive_base, ent.ive_size);
#elif defined(DEFINE_mfile_viowritev)
			vio_copytovio(&args, (vio_addr_t)offset, ent.ive_base, ent.ive_size);
#elif defined(DEFINE_mfile_vioreadv_p)
			vio_copyfromvio_to_phys(&args, (vio_addr_t)offset, (__physaddr_t)ent.ive_base, ent.ive_size);
#elif defined(DEFINE_mfile_viowritev_p)
			vio_copytovio_from_phys(&args, (vio_addr_t)offset, (__physaddr_t)ent.ive_base, ent.ive_size);
#endif /* ... */
			if (ent.ive_size >= num_bytes)
				break;
			num_bytes -= ent.ive_size;
			offset += ent.ive_size;
		}
	}
#else /* ... */
#error "Bad configuration"
#endif /* !... */
}


#undef LOCAL_BUFFER_IS_PHYS
#undef LOCAL_BUFFER_IS_IOVEC
#undef LOCAL_buffer_t
#undef LOCAL_mfile_vio_rw

DECL_END
#endif /* LIBVIO_CONFIG_ENABLED */

#undef DEFINE_mfile_vioread
#undef DEFINE_mfile_viowrite
#undef DEFINE_mfile_vioread_p
#undef DEFINE_mfile_viowrite_p
#undef DEFINE_mfile_vioreadv
#undef DEFINE_mfile_viowritev
#undef DEFINE_mfile_vioreadv_p
#undef DEFINE_mfile_viowritev_p
