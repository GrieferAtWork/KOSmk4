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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_IOBM_C
#define GUARD_KERNEL_CORE_ARCH_I386_IOBM_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman/phys.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <sched/cpu.h>
#include <sched/pertask.h>
#include <sched/task.h>
#include <sched/x86/iobm.h>
#include <sched/x86/tss.h>

#include <hybrid/align.h>
#include <atomic.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

/* [0..1][lock(WRITE_ONCE)]
 * The I/O permissions bitmap of the calling thread.
 * Lazily allocated during `ioperm()' and `#PF' (s.a. documentation in <sched/tss.h>) */
PUBLIC ATTR_PERTASK ATTR_ALIGN(REF struct ioperm_bitmap *) this_x86_ioperm_bitmap = NULL;

/* [0..1][lock(THIS_CPU && !PREEMPTION_ENABLED())]
 * The I/O  permissions  bitmap  currently active  within  the  calling  CPU.
 * Set to `NULL' during preemption; Filled in during the first #PF that ended
 * up being caused by  the CPU trying to  access the I/O permissions  bitmap. */
PUBLIC ATTR_PERCPU struct ioperm_bitmap *thiscpu_x86_ioperm_bitmap = NULL;

DEFINE_PERTASK_FINI(fini_this_ioperm_bitmap);
PRIVATE NOBLOCK ATTR_USED NONNULL((1)) void
NOTHROW(KCALL fini_this_ioperm_bitmap)(struct task *__restrict self) {
	REF struct ioperm_bitmap *iob;
	iob = FORTASK(self, this_x86_ioperm_bitmap);
	if (iob) {
		assert(iob->ib_share >= 1);
		atomic_dec(&iob->ib_share);
		decref_likely(iob);
	}
}



/* Destroy the given I/O permissions bitmap. */
PUBLIC NOBLOCK void
NOTHROW(FCALL ioperm_bitmap_destroy)(struct ioperm_bitmap *__restrict self) {
	assert(PERCPU(thiscpu_x86_ioperm_bitmap) != self);
	page_free_for(page_usage.pu_x86_iobm, physaddr2page(self->ib_pages), 2);
	kfree(self);
}

PUBLIC ATTR_BLOCKLIKE_GFP(flags) ATTR_MALLOC ATTR_RETNONNULL WUNUSED
REF struct ioperm_bitmap *KCALL ioperm_bitmap_allocf(gfp_t flags) THROWS(E_BADALLOC) {
	physpage_t iob;
	REF struct ioperm_bitmap *result;
	result = (REF struct ioperm_bitmap *)kmalloc(sizeof(struct ioperm_bitmap), flags);
	iob    = page_malloc_for(page_usage.pu_x86_iobm, 2);
	if unlikely(iob == PHYSPAGE_INVALID) {
		kfree(result);
		THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 2 * PAGESIZE);
	}

	/* Fill both pages of memory with all ones (indicating that I/O access is denied) */
	result->ib_pages  = physpage2addr(iob);
	result->ib_refcnt = 1;
	result->ib_share  = 1;
	memsetphyspages(result->ib_pages, 0xff, 2 * PAGESIZE);
	return result;
}

PUBLIC ATTR_BLOCKLIKE_GFP(flags) ATTR_MALLOC WUNUSED
REF struct ioperm_bitmap *NOTHROW(KCALL ioperm_bitmap_allocf_nx)(gfp_t flags) {
	physpage_t iob;
	REF struct ioperm_bitmap *result;
	result = (REF struct ioperm_bitmap *)kmalloc_nx(sizeof(struct ioperm_bitmap), flags);
	if likely(result) {
		iob = page_malloc_for(page_usage.pu_x86_iobm, 2);
		if unlikely(iob == PHYSPAGE_INVALID) {
			kfree(result);
			return NULL;
		}

		/* Fill both pages of memory with all ones (indicating that I/O access is denied) */
		result->ib_pages  = physpage2addr(iob);
		result->ib_refcnt = 1;
		result->ib_share  = 1;
		memsetphyspages(result->ib_pages, 0xff, 2 * PAGESIZE);
	}
	return result;
}

/* Allocate a new io permissions bitmap with all permission bits set to disallow access. */
PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct ioperm_bitmap *KCALL
ioperm_bitmap_alloc(void) THROWS(E_BADALLOC) {
	return ioperm_bitmap_allocf(GFP_LOCKED | GFP_PREFLT);
}




/* Create a copy of the given I/O permissions bitmap. */
PUBLIC ATTR_BLOCKLIKE_GFP(flags) ATTR_MALLOC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct ioperm_bitmap *KCALL
ioperm_bitmap_copyf(struct ioperm_bitmap const *__restrict self, gfp_t flags) THROWS(E_BADALLOC) {
	physpage_t iob;
	REF struct ioperm_bitmap *result;
	result = (REF struct ioperm_bitmap *)kmalloc(sizeof(struct ioperm_bitmap), flags);
	iob = page_malloc_for(page_usage.pu_x86_iobm, 2);
	if unlikely(iob == PHYSPAGE_INVALID) {
		kfree(result);
		THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 2 * PAGESIZE);
	}

	/* Copy I/O permission bits. */
	result->ib_pages  = physpage2addr(iob);
	result->ib_refcnt = 1;
	result->ib_share  = 1;
	copypagesinphys(result->ib_pages, self->ib_pages, 2 * PAGESIZE);
	return result;
}

PUBLIC ATTR_BLOCKLIKE_GFP(flags) ATTR_MALLOC WUNUSED NONNULL((1)) REF struct ioperm_bitmap *
NOTHROW(KCALL ioperm_bitmap_copyf_nx)(struct ioperm_bitmap const *__restrict self, gfp_t flags) {
	physpage_t iob;
	REF struct ioperm_bitmap *result;
	result = (REF struct ioperm_bitmap *)kmalloc_nx(sizeof(struct ioperm_bitmap), flags);
	if likely(result) {
		iob = page_malloc_for(page_usage.pu_x86_iobm, 2);
		if unlikely(iob == PHYSPAGE_INVALID) {
			kfree(result);
			return NULL;
		}

		/* Copy I/O permission bits. */
		result->ib_pages  = physpage2addr(iob);
		result->ib_refcnt = 1;
		result->ib_share  = 1;
		copypagesinphys(result->ib_pages, self->ib_pages, 2 * PAGESIZE);
	}
	return result;
}

PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct ioperm_bitmap *KCALL
ioperm_bitmap_copy(struct ioperm_bitmap const *__restrict self) THROWS(E_BADALLOC) {
	return ioperm_bitmap_copyf(self, GFP_LOCKED | GFP_PREFLT);
}



LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ioperm_bitmap_maskbyte)(struct ioperm_bitmap *__restrict self,
                                      size_t byte_index, u8 byte_mask, u8 byte_flag) {
	u8 *byte, oldval;
	struct mptram pt = MPTRAM_INIT;
	byte = mptram_map(&pt, self->ib_pages + byte_index);
	do {
		oldval = atomic_read(byte);
	} while (!atomic_cmpxch_weak(byte, oldval, (oldval & byte_mask) | byte_flag));
	mptram_fini(&pt);
}

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ioperm_bitmap_maskbyte_c)(struct ioperm_bitmap *__restrict self,
                                        size_t byte_index, shift_t minbit,
                                        shift_t bitcnt, bool turn_on) {
	u8 bitmask;
	assert((minbit + bitcnt) <= 8);
	bitmask = (u8)(((1 << bitcnt) - 1) << minbit);
	ioperm_bitmap_maskbyte(self, byte_index, ~bitmask,
	                       turn_on ? 0 : bitmask);
}

/* Turn permission bits for a given range on/off. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ioperm_bitmap_setrange)(struct ioperm_bitmap *__restrict self,
                                      u16 minport, u16 maxport, bool turn_on) {
	size_t minbyte, maxbyte;
	shift_t minbit;
	assert(!wasdestroyed(self));
	assert(maxport >= minport);
	minbyte = FLOORDIV(minport, 8);
	maxbyte = CEILDIV(maxport + 1, 8) - 1;
	assert(maxbyte >= minbyte);

	/* Special case: only a single byte is getting modified. */
	if (maxbyte == minbyte) {
		shift_t bitcnt;
		minbit = minport & 7;
		bitcnt = (maxport - minport) + 1;

		/* Update the bitmap mask. */
		ioperm_bitmap_maskbyte_c(self, minbyte,
		                         minbit, bitcnt,
		                         turn_on);
		return;
	}

	/* Update the bitsets for the first and last affected bitset byte */
	minbit = minport & 7;
	ioperm_bitmap_maskbyte_c(self, minbyte, minbit, 8 - minbit, turn_on);
	ioperm_bitmap_maskbyte_c(self, maxbyte, 0, (maxport & 7) + 1, turn_on);

	/* Fill in all intermediate bytes. */
	if (minbyte + 1 < maxbyte) {
		memsetphys(self->ib_pages + minbyte + 1,
		           turn_on ? 0x00 : 0xff,
		           (maxbyte - minbyte) - 1);
	}
}




INTDEF byte_t __x86_iob_empty_base[];
PUBLIC struct ioperm_bitmap ioperm_bitmap_empty = {
	.ib_refcnt = 1, /* _ioperm_bitmap_empty */
	.ib_share  = 2, /* Prevent modifications */
	{{
		(uintptr_t)__x86_iob_empty_base - KERNEL_CORE_BASE
#if __SIZEOF_PHYSADDR_T__ > __SIZEOF_POINTER__
		,
		0
#endif /* __SIZEOF_PHYSADDR_T__ > __SIZEOF_POINTER__ */
	}}
};



INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_iobm)(void) {
	/* Fill  the  contents of  the empty  IOB vector  with all  FFh bytes,
	 * thus setting the access permissions of all I/O ports as restricted. */
	memsetb(__x86_iob_empty_base, UINT8_C(0xff), 8192);

	/* Prepare the IOB region for lazy memory mappings. */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (!pagedir_prepare(__x86_iob_empty_base, 2 * PAGESIZE))
		kernel_panic(FREESTR("Failed to prepare bootcpu.tss.iob"));
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Unmap the initial IOB of the boot CPU. */
	pagedir_unmap(__x86_iob_empty_base, 2 * PAGESIZE);
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_IOBM_C */
