/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "mpart-ll.c"
#define DEFINE_mpart_ll_writemem
#define DEFINE_mpart_ll_bzeromemcc
#endif /* __INTELLISENSE__ */

#include <kernel/mman/phys.h>

DECL_BEGIN

#ifdef DEFINE_mpart_ll_writemem
/* Low-level write to  the backing memory  of the  given
 * part. Requires that  `MPART_ST_INMEM(self->mp_state)'
 * The caller must ensure that `offset...+=num_bytes' is
 * in-bounds of the given mem-part! */
PUBLIC NONNULL((1)) void KCALL
mpart_ll_writemem(struct mpart *__restrict self,
                  mpart_reladdr_t offset,
                  NCX void const *src,
                  size_t num_bytes)
		THROWS(E_SEGFAULT)
#define LOCAL_doio(part_physaddr, num_bytes, request_offset) \
	copytophys(part_physaddr, (byte_t const *)(src) + request_offset, num_bytes)
#elif defined(DEFINE_mpart_ll_bzeromemcc)
/* Low-level bzero-if-!page_iszero() the given address range.
 * The  caller must ensure that `offset...+=num_bytes' is in-
 * bounds of the given mem-part! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mpart_ll_bzeromemcc)(struct mpart *__restrict self,
                                   mpart_reladdr_t offset,
                                   size_t num_bytes)
#define LOCAL_doio(part_physaddr, num_bytes, request_offset) \
	bzerophyscc(part_physaddr, num_bytes)
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
{
	/* >> #define LOCAL_doio(part_physaddr, num_bytes, request_offset)
	 * @param: physaddr_t part_physaddr:  Physical address associated with `self'
	 * @param: size_t     num_bytes:      Total # of bytes to perform I/O upon.
	 * @param: size_t     request_offset: Offset  (in bytes) from the given `offset'
	 *                                    argument, such that the part-relative byte
	 *                                    at `offset + request_offset'  maps to  the
	 *                                    physical address `part_physaddr' */
	assert(MPART_ST_INMEM(self->mp_state));
	assert((offset + num_bytes) >= offset);
	assert((offset + num_bytes) <= mpart_getsize(self));
	if (self->mp_state == MPART_ST_MEM) {
		/* Simple case: Physical memory is linear, meaning we can perform
		 *              the  requested  I/O operation  in a  single pass! */
		LOCAL_doio(physpage2addr(self->mp_mem.mc_start) + offset,
		           num_bytes, 0);
	} else {
		/* Complicated case: physical memory is scattered, so we must find
		 * the correct mem-chunk(s) that the operation should be performed
		 * upon! */
		size_t i;
		physaddr_t caddr;
		size_t csize;
		mpart_reladdr_t rel_offset;
		rel_offset = offset;
		for (i = 0;; ++i) {
			assert(i < self->mp_mem_sc.ms_c);
			csize = self->mp_mem_sc.ms_v[i].mc_size * PAGESIZE;
			if (rel_offset < csize)
				break; /* Found the first chunk to perform I/O upon */
			rel_offset -= csize;
		}
		caddr = physpage2addr(self->mp_mem_sc.ms_v[i].mc_start);

		/* Account for the remaining offset at the start of the chunk. */
		caddr += rel_offset;
		csize -= rel_offset;
		rel_offset = 0; /* Re-use `rel_offset' as the request-relative offset. */
		for (;;) {
			if (csize > num_bytes)
				csize = num_bytes;

			/* Perform I/O on this part of the chunk. */
			LOCAL_doio(caddr, csize, rel_offset);
			if (csize >= num_bytes)
				break;
			rel_offset += csize;
			num_bytes -= csize;

			/* Continue on with the next chunk. */
			++i;
			assert(i < self->mp_mem_sc.ms_c);
			caddr = physpage2addr(self->mp_mem_sc.ms_v[i].mc_start);
			csize = self->mp_mem_sc.ms_v[i].mc_size * PAGESIZE;
		}
	}
}
#undef LOCAL_doio

DECL_END

#undef DEFINE_mpart_ll_bzeromemcc
#undef DEFINE_mpart_ll_writemem
