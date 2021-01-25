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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_LL_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_LL_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>

#include <kos/except.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */


/* Initialize `self->mp_state' and `self->mp_mem' or `self->mp_mem_sc', such
 * that `self' points to exactly `total_pages' pages of physical memory.
 * This function is init-only and doesn't care about locks or the whatever
 * the given `self' may point to, meaning it should not be called when `self'
 * was already fully initialized.
 * NOTE: This function assumes that `self->mp_file' has already been initialized,
 *       and will pass that value onto `mfile_alloc_physmem()'! */
PUBLIC NONNULL((1)) void KCALL
mpart_ll_allocmem(struct mpart *__restrict self,
                  size_t total_pages)
		THROWS(E_BADALLOC) {
	physpage_t pp;
	physpagecnt_t res_pages;
	struct mchunkvec cv;
	struct mchunk *vec;

	/* Try to allocate everything in one go. */
	pp = mfile_alloc_physmem(self->mp_file, total_pages, &res_pages);
	if unlikely(pp == PHYSPAGE_INVALID)
		goto err_nophys;
	assert(res_pages <= total_pages);
	if (res_pages >= total_pages) {
		self->mp_state        = MPART_ST_MEM;
		self->mp_mem.mc_start = pp;
		self->mp_mem.mc_size  = res_pages;
		goto done;
	}
	/* Must allocate pages into a page-vector. */
	cv.ms_c = 1;
	TRY {
#ifndef __OPTIMIZE_SIZE__
		cv.ms_v = (struct mchunk *)kmalloc_nx(4 * sizeof(struct mchunk),
		                                      GFP_LOCKED | GFP_PREFLT);
		if (!cv.ms_v)
#endif /* !__OPTIMIZE_SIZE__ */
		{
			cv.ms_v = (struct mchunk *)kmalloc(2 * sizeof(struct mchunk),
			                                   GFP_LOCKED | GFP_PREFLT);
		}
	} EXCEPT {
		page_ccfree(pp, res_pages);
		RETHROW();
	}
	cv.ms_v[0].mc_start = pp;
	cv.ms_v[0].mc_size  = res_pages;
	for (;;) {
		total_pages -= res_pages;
		pp = mfile_alloc_physmem(self->mp_file, total_pages, &res_pages);
		if unlikely(pp == PHYSPAGE_INVALID)
			goto err_nophys_v;
		assert(res_pages <= total_pages);
		/* Check if the vector has to be extended. */
		if ((cv.ms_c + 1) * sizeof(struct mchunk) > kmalloc_usable_size(cv.ms_v)) {
			size_t new_alloc = cv.ms_c * 2;
			vec = (struct mchunk *)krealloc_nx(cv.ms_v,
			                                   new_alloc * sizeof(struct mchunk),
			                                   GFP_LOCKED | GFP_PREFLT);
			if unlikely(!vec) {
				new_alloc = cv.ms_c + 1;
				TRY {
					vec = (struct mchunk *)krealloc(cv.ms_v,
					                                new_alloc * sizeof(struct mchunk),
					                                GFP_LOCKED | GFP_PREFLT);
				} EXCEPT {
					while (cv.ms_c) {
						--cv.ms_c;
						page_ccfree(cv.ms_v[cv.ms_c].mc_start,
						            cv.ms_v[cv.ms_c].mc_size);
					}
					kfree(cv.ms_v);
					RETHROW();
				}
			}
			cv.ms_v = vec;
		}
		/* Append the new mem-chunk to the vector. */
		cv.ms_v[cv.ms_c].mc_start = pp;
		cv.ms_v[cv.ms_c].mc_size  = res_pages;
		++cv.ms_c;
		if (res_pages >= total_pages)
			break;
	}

	/* Try to release unused entries from the chunk-vector. */
	vec = (struct mchunk *)krealloc_nx(cv.ms_v,
	                                   cv.ms_c * sizeof(struct mchunk),
	                                   GFP_LOCKED | GFP_PREFLT);
	if likely(vec != NULL)
		cv.ms_v = vec;

	/* Write-back results */
	self->mp_state       = MPART_ST_MEM_SC;
	self->mp_mem_sc.ms_v = cv.ms_v;
	self->mp_mem_sc.ms_c = cv.ms_c;
done:
	return;
err_nophys_v:
	while (cv.ms_c) {
		--cv.ms_c;
		page_ccfree(cv.ms_v[cv.ms_c].mc_start,
		            cv.ms_v[cv.ms_c].mc_size);
	}
	kfree(cv.ms_v);
err_nophys:
	THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, total_pages * PAGESIZE);
}



/* Free backing memory using `page_free()'. When an mchunkvec was used,
 * also kfree that vector. Requires that `MPART_ST_INMEM(self->mp_state)' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mpart_ll_freemem)(struct mpart *__restrict self) {
	if (self->mp_state == MPART_ST_MEM) {
		page_free(self->mp_mem.mc_start,
		          self->mp_mem.mc_size);
	} else {
		size_t i;
		assert(self->mp_state == MPART_ST_MEM_SC);
		for (i = 0; i < self->mp_mem_sc.ms_c; ++i) {
			page_free(self->mp_mem_sc.ms_v[i].mc_start,
			          self->mp_mem_sc.ms_v[i].mc_size);
		}
		kfree(self->mp_mem_sc.ms_v);
	}
}

/* Free backing memory using `page_ccfree()'. When an mchunkvec was used,
 * also kfree that vector. Requires that `MPART_ST_INMEM(self->mp_state)' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mpart_ll_ccfreemem)(struct mpart *__restrict self) {
	if (self->mp_state == MPART_ST_MEM) {
		page_ccfree(self->mp_mem.mc_start,
		            self->mp_mem.mc_size);
	} else {
		size_t i;
		assert(self->mp_state == MPART_ST_MEM_SC);
		for (i = 0; i < self->mp_mem_sc.ms_c; ++i) {
			page_ccfree(self->mp_mem_sc.ms_v[i].mc_start,
			            self->mp_mem_sc.ms_v[i].mc_size);
		}
		kfree(self->mp_mem_sc.ms_v);
	}
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_LL_C */
