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
#include "mpart-map.c"
#define DEFINE_mpart_mmap_force
//#define DEFINE_mpart_mmap_force_p
#endif /* __INTELLISENSE__ */

#include <debugger/rt.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>

DECL_BEGIN

#ifdef DEFINE_mpart_mmap_force_p
/* Similar to `mpart_mmap_p()', but force the given `prot' for all pages, no
 * matter  what the block-status  bitset of `self' might  say of the matter. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_mmap_force_p)(struct mpart const *__restrict self, pagedir_phys_t pdir,
                                  PAGEDIR_PAGEALIGNED void *addr,
                                  PAGEDIR_PAGEALIGNED size_t size,
                                  PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                                  pagedir_prot_t prot)
#define LOCAL_pagedir_map(addr, num_bytes, phys) \
	pagedir_map_p(pdir, addr, num_bytes, phys, prot)
#define LOCAL_pagedir_unmap(addr, num_bytes) \
	pagedir_unmap_p(pdir, addr, num_bytes)
#elif defined(DEFINE_mpart_mmap_force)
/* Same as `mpart_mmap_force_p()', but always map into the current page directory. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_mmap_force)(struct mpart const *__restrict self,
                                PAGEDIR_PAGEALIGNED void *addr,
                                PAGEDIR_PAGEALIGNED size_t size,
                                PAGEDIR_PAGEALIGNED mpart_reladdr_t offset,
                                pagedir_prot_t prot)
#define LOCAL_pagedir_map(addr, num_bytes, phys) \
	pagedir_map(addr, num_bytes, phys, prot)
#define LOCAL_pagedir_unmap pagedir_unmap
#else /* ... */
#error "Bad configuration"
#endif /* !... */
{
	assert(IS_ALIGNED((uintptr_t)addr, PAGESIZE));
	assert(IS_ALIGNED(size, PAGESIZE));
	assert(IS_ALIGNED(offset, PAGESIZE));
	assert((offset + size) >= offset);
	switch (__builtin_expect(self->mp_state, MPART_ST_MEM)) {

	case MPART_ST_MEM: {
		/* Simplest case: we can just directly map the proper sub-range! */
		physaddr_t baseaddr;
		assertf((offset + size) <= self->mp_mem.mc_size * PAGESIZE,
		        "offset:               %#" PRIxSIZ "\n"
		        "size:                 %#" PRIxSIZ "\n"
		        "self->mp_mem.mc_size: %#" PRIxSIZ,
		        offset, size, self->mp_mem.mc_size);
		assert(self->mp_mem.mc_start != PHYSPAGE_INVALID);
		baseaddr = physpage2addr(self->mp_mem.mc_start);
		LOCAL_pagedir_map(addr, size, baseaddr + offset);
	}	break;

	case MPART_ST_MEM_SC: {
		size_t i;
		struct mchunk *vec;
		vec = self->mp_mem_sc.ms_v;
		for (i = 0;; ++i) {
			size_t chunk_size;
			assert(i < self->mp_mem_sc.ms_c);
			chunk_size = (size_t)vec[i].mc_size << PAGESHIFT;
			if (offset >= chunk_size) {
				/* Uninteresting chunk... */
				offset -= chunk_size;
				continue;
			}
			chunk_size -= offset;
			if (chunk_size > size)
				chunk_size = size;

			/* Map (the requested sub-range of) this chunk */
			assert(vec[i].mc_start != PHYSPAGE_INVALID);
			LOCAL_pagedir_map(addr, chunk_size,
			                  physpage2addr(vec[i].mc_start) +
			                  offset);
			if (chunk_size >= size)
				break;
			addr = (byte_t *)addr + chunk_size;
			size -= chunk_size;
			offset = 0;
		}
	}	break;


	default:
		/* Other part-types can't be mapped into memory... */
		LOCAL_pagedir_unmap(addr, size);
		break;
	}
}

#undef LOCAL_pagedir_unmap
#undef LOCAL_pagedir_map

DECL_END

#undef DEFINE_mpart_mmap
#undef DEFINE_mpart_mmap_p
