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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_P32_C_INL
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_P32_C_INL 1
#define _KOS_SOURCE 1
#define __VM_INTERNAL_EXCLUDE_PAGEDIR 1
#define __OMIT_PAGING_CONSTANT_P_WRAPPERS 1

#include <kernel/compiler.h>

#include <kernel/arch/paging32-p32.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <assert.h>
#include <string.h>

#ifndef CONFIG_NO_PAGING_P32

#include "paging.h"
#include "paging32-com.h"

DECL_BEGIN

STATIC_ASSERT(sizeof(struct p32_pdir) == P32_PDIR_SIZE);
STATIC_ASSERT(sizeof(struct p32_pdir) == 4096);
STATIC_ASSERT(sizeof(union p32_pdir_e2) == 4);
STATIC_ASSERT(sizeof(union p32_pdir_e1) == 4);
STATIC_ASSERT(P32_PDIR_E1_IDENTITY_BASE == P32_VM_KERNEL_PDIR_IDENTITY_BASE);
STATIC_ASSERT(P32_PDIR_E2_IDENTITY_BASE == (P32_PDIR_E1_IDENTITY_BASE + (P32_PDIR_VEC2INDEX(P32_PDIR_E1_IDENTITY_BASE) * P32_PDIR_E1_SIZE)));

/* Return the physical page ID of a given physical address. */
#define ppageof(paddr) (pageptr_t)((paddr) / PAGESIZE)

/* Initialize the given page directory.
 * The caller is required to allocate the page directory
 * controller itself, which must be aligned and sized
 * according to `PAGEDIR_ALIGN' and `PAGEDIR_SIZE'. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p32_pagedir_init)(VIRT struct p32_pdir *__restrict self,
                                PHYS vm_phys_t phys_self) {
	/* Assert some constants assumed below. */
	STATIC_ASSERT(P32_PDIR_VEC2INDEX(KERNELSPACE_BASE) == 768);
	STATIC_ASSERT(P32_PDIR_VEC1INDEX(KERNELSPACE_BASE) == 0);
	STATIC_ASSERT(P32_PDIR_VEC2INDEX(P32_VM_KERNEL_PDIR_IDENTITY_BASE) == 1023);
	STATIC_ASSERT(P32_PDIR_VEC1INDEX(P32_VM_KERNEL_PDIR_IDENTITY_BASE) == 0);
	assert(IS_ALIGNED((uintptr_t)self, PAGESIZE));
	assert(IS_ALIGNED(phys_self, PAGESIZE));

	/* Map all pages before the share-segment as absent. */
	memsetl(self->p_e2, P32_PAGE_ABSENT, 768);

	/* Copy P2 pointers that are shared with the kernel. */
	memcpyl(&self->p_e2[768], &P32_PDIR_E2_IDENTITY[768], 1023 - 768);

	/* Create the identity mapping */
	self->p_e2[1023].p_word = ((u32)phys_self |
	                           (P32_PAGE_FACCESSED | P32_PAGE_FWRITE |
	                            P32_PAGE_FPRESENT));
}

/* Finalize a given page directory. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p32_pagedir_fini)(VIRT struct p32_pdir *__restrict self) {
	unsigned int vec2;
	/* Free all dynamically allocated E1 vectors below the kernel-share segment. */
	for (vec2 = 0; vec2 < 768; ++vec2) {
		union p32_pdir_e2 e2 = self->p_e2[vec2];
		if (P32_PDIR_E2_ISVEC1(e2.p_word))
			page_freeone(ppageof(e2.p_word & P32_PAGE_FVECTOR));
	}
}



LOCAL NOBLOCK void
NOTHROW(FCALL p32_pagedir_set_prepared)(union p32_pdir_e1 *__restrict e1_p) {
	u32 word;
	for (;;) {
		word = ATOMIC_READ(e1_p->p_word);
		if unlikely(P32_PDIR_E1_ISHINT(word))
			break; /* Special case: Hint */
		if likely(ATOMIC_CMPXCH_WEAK(e1_p->p_word, word, word | P32_PAGE_FPREPARED))
			break;
	}
}


LOCAL NOBLOCK void
NOTHROW(FCALL p32_pagedir_unset_prepared)(union p32_pdir_e1 *__restrict e1_p) {
	u32 word;
	for (;;) {
		word = ATOMIC_READ(e1_p->p_word);
		if unlikely(P32_PDIR_E1_ISHINT(word))
			break; /* Special case: Hint */
		assert(word & P32_PAGE_FPREPARED);
		if likely(ATOMIC_CMPXCH_WEAK(e1_p->p_word, word, word & ~P32_PAGE_FPREPARED))
			break;
	}
}



/* Try to widen a 4MiB mapping to a 1024*4KiB vector of linear memory
 * Alternatively, if the specified vector is absent, pre-allocate it.
 * @return: false: Failed to allocate physical memory */
PRIVATE NOBLOCK bool
NOTHROW(FCALL p32_pagedir_prepare_impl_widen)(unsigned int vec2,
                                              unsigned int vec1_prepare_start,
                                              unsigned int vec1_prepare_size) {
	union p32_pdir_e2 e2, *e2_p;
	union p32_pdir_e1 e1, *e1_p;
	pageptr_t new_e1_vector;
	u32 new_e2_word;
	unsigned int vec1;
	uintptr_t backup;
	assert(vec2 < 1024);
	assert(vec1_prepare_start < 1024);
	assert(vec1_prepare_size != 0);
	assert(vec1_prepare_start + vec1_prepare_size > vec1_prepare_start);
	assert(vec1_prepare_start + vec1_prepare_size <= 1024);
	assertf(vec2 < P32_PDIR_VEC2INDEX(KERNELSPACE_BASE),
	        "The caller must ensure that no kernel-space addresses get here");
	e2_p = &P32_PDIR_E2_IDENTITY[vec2];
again:
	e2.p_word = ATOMIC_READ(e2_p->p_word);
	if (!e2.p_vec1.v_present) {
		/* Not present */
		new_e1_vector = page_mallocone32();
		if unlikely(new_e1_vector == PAGEPTR_INVALID)
			return false;
		/* Initialize the inner vector.
		 * We can safely make use of our trampoline, since kernel-space is always prepared. */
		e1_p   = (union p32_pdir_e1 *)THIS_TRAMPOLINE_BASE;
		backup = p32_pagedir_push_mapone(e1_p, page2addr(new_e1_vector),
		                                 PAGEDIR_MAP_FWRITE);
		pagedir_syncone(e1_p);
		COMPILER_WRITE_BARRIER();
		/* If the 4MiB entry was marked as prepared, always mark every entry
		 * within the E1-vector as prepared. */
		if (vec1_prepare_size == 1024 || (e2.p_word & P32_PAGE_FPREPARED)) {
			assert(vec1_prepare_size == 1024 ? vec1_prepare_start == 0 : true);
			memsetl(e1_p, P32_PAGE_FPREPARED, 1024);
		} else {
			memsetl(&e1_p[0], P32_PAGE_ABSENT, vec1_prepare_start);
			memsetl(&e1_p[vec1_prepare_start], P32_PAGE_FPREPARED, vec1_prepare_size);
			memsetl(&e1_p[vec1_prepare_start + vec1_prepare_size], P32_PAGE_ABSENT,
			        1024 - (vec1_prepare_start + vec1_prepare_size));
		}
		COMPILER_WRITE_BARRIER();
		p32_pagedir_pop_mapone(e1_p, backup);
		/* Map the new vector. */
		new_e2_word = page2addr32(new_e1_vector) |
		              P32_PAGE_FPRESENT | P32_PAGE_FWRITE | P32_PAGE_FACCESSED;
#if 0 /* This is always the case: Kernel-space always has all vectors allocated. */
		if (vec2 < P32_PDIR_VEC2INDEX(KERNELSPACE_BASE))
#endif
		{
			/* Allow user-space access of stuff that will eventually mapped by this page. */
			new_e2_word |= P32_PAGE_FUSER;
		}
atomic_set_new_e2_word_or_free_new_e1_vector:
		if unlikely(!ATOMIC_CMPXCH(e2_p->p_word, e2.p_word, new_e2_word)) {
			page_free(new_e1_vector, 1);
			goto again;
		}
	} else if (e2.p_4mib.d_4mib_1) {
		/* Convert a 4MiB mapping to 1024*4KiB pages
		 * Because the mapping may be getting used _right_ _now_, we have
		 * to be careful about how we go about initializing the vector.
		 * Because the process has to be atomic, we use our thread-local
		 * temporary mapping trampoline to temporarily map the new page
		 * for initialization (Because the trampoline always uses
		 * `P32_PAGE_FNOFLATTEN' when mapping, it is always prepared) */
		new_e1_vector = page_mallocone32();
		if unlikely(new_e1_vector == PAGEPTR_INVALID)
			return false;
		e1.p_word = e2.p_word & ~(P32_PAGE_F4MIB | P32_PAGE_FPAT_4MIB);
		if (e2.p_word & P32_PAGE_FPAT_4MIB)
			e1.p_word |= P32_PAGE_FPAT_4KIB;
		e1_p   = (union p32_pdir_e1 *)THIS_TRAMPOLINE_BASE;
		backup = p32_pagedir_push_mapone(e1_p, page2addr(new_e1_vector),
		                                 PAGEDIR_MAP_FWRITE);
		pagedir_syncone(e1_p);
		if (vec1_prepare_size == 1024) {
			assert(vec1_prepare_start == 0);
			e1.p_word |= P32_PAGE_FPREPARED;
			for (vec1 = 0; vec1 < 1024; ++vec1) {
				e1_p[vec1] = e1;
				e1.p_word += 4096;
			}
		} else {
			for (vec1 = 0; vec1 < 1024; ++vec1) {
				e1_p[vec1] = e1;
				e1.p_word += 4096;
			}
			/* Mark specific pages as prepared */
			for (vec1 = vec1_prepare_start;
			     vec1 < vec1_prepare_start + vec1_prepare_size; ++vec1)
				e1_p[vec1].p_word |= P32_PAGE_FPREPARED;
		}
		p32_pagedir_pop_mapone(e1_p, backup);
		COMPILER_WRITE_BARRIER();
		new_e2_word  = page2addr32(new_e1_vector);
		new_e2_word |= P32_PAGE_FPRESENT | P32_PAGE_FWRITE;
		new_e2_word |= e2.p_word & (P32_PAGE_FUSER | P32_PAGE_FPWT |
		                            P32_PAGE_FPCD | P32_PAGE_FACCESSED |
		                            P32_PAGE_FGLOBAL);
		/* Make sure that the vector was allocated and is active */
		goto atomic_set_new_e2_word_or_free_new_e1_vector;
	} else {
		/* Already a fully allocated vector (nothing to do here) */
		pflag_t was;
		assert(P32_PDIR_E2_ISVEC1(e2.p_word));
		e1_p = P32_PDIR_E1_IDENTITY[vec2];

		/* The first page needs to be marked under special conditions. */
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was);
		/* With a prepare-first token held, check if our e2 control work is still correct.
		 * If some other thread flattened the vector in the mean time, that control word
		 * will have changed. */
		if unlikely(e2.p_word != ATOMIC_READ(e2_p->p_word)) {
			X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
			goto again;
		}
		p32_pagedir_set_prepared(&e1_p[vec1_prepare_start]);
		X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);

		/* Mark all of the other pages. */
		for (vec1 = vec1_prepare_start + 1;
		     vec1 < vec1_prepare_start + vec1_prepare_size; ++vec1)
			p32_pagedir_set_prepared(&e1_p[vec1]);
	}
	return true;
}



LOCAL NOBLOCK bool
NOTHROW(KCALL p32_pagedir_can_flatten_e1_vector)(union p32_pdir_e1 e1_p[1024],
                                                 u32 *__restrict new_e2_word,
                                                 unsigned int still_prepared_vec2) {
	unsigned int vec1;
	union p32_pdir_e1 e1;
	e1.p_word = ATOMIC_READ(e1_p[0].p_word);
	if (still_prepared_vec2 == 0) {
		assert(e1.p_word & P32_PAGE_FPREPARED || P32_PDIR_E1_ISHINT(e1.p_word));
		if (!P32_PDIR_E1_ISHINT(e1.p_word))
			e1.p_word &= ~P32_PAGE_FPREPARED;
	}
	if (e1.p_word & P32_PAGE_FPRESENT) {
		union p32_pdir_e1 iter, flag;
		if __untraced(!HAVE_4MIB_PAGES)
			return false; /* Would need 4MiB pages to flatten present vector. */
		if likely(!P32_IS_4MIB_ALIGNED(e1.p_word & P32_PAGE_FADDR_4KIB))
			return false; /* Physical starting address isn't 4MiB aligned. */
		if (e1.p_word & P32_PAGE_FPREPARED)
			return false; /* Cannot flatten prepared pages. */
		if (P32_PDIR_E1_ISHINT(e1.p_word))
			return false; /* Cannot flatten hints. */
		/* Check if we can form a linear page of memory. */
		flag.p_word = 0;
		iter.p_word = e1.p_word & ~(P32_PAGE_FACCESSED | P32_PAGE_FDIRTY);
		for (vec1 = 1; vec1 < 1024; ++vec1) {
			e1.p_word = ATOMIC_READ(e1_p[vec1].p_word);
			if __untraced(vec1 == still_prepared_vec2 && !P32_PDIR_E1_ISHINT(e1.p_word))
				e1.p_word &= ~P32_PAGE_FPREPARED;
			flag.p_word |= e1.p_word & (P32_PAGE_FACCESSED | P32_PAGE_FDIRTY);
			if (iter.p_word != (e1.p_word & ~(P32_PAGE_FACCESSED | P32_PAGE_FDIRTY)))
				return false; /* Non-linear memory, or different page attributes/meta-data */
			assert(!(e1.p_word & P32_PAGE_FPREPARED) || P32_PDIR_E1_ISHINT(e1.p_word));
			iter.p_word += 4096;
		}
		e1.p_word |= flag.p_word;
		if (e1.p_word & P32_PAGE_FPAT_4KIB) {
#if P32_PAGE_FPAT_4KIB != P32_PAGE_F4MIB
			e1.p_word &= ~P32_PAGE_FPAT_4KIB;
#endif
			e1.p_word |= P32_PAGE_FPAT_4MIB;
		}
		e1.p_word |= P32_PAGE_F4MIB;
		*new_e2_word = e1.p_word;
		return true;
	}
	if (e1.p_word != P32_PAGE_ABSENT)
		return false; /* Non-present, but with meta-data (hint/prepared) -> Cannot flatten. */
	/* Check if all entires are marked as ABSENT */
	for (vec1 = 1; vec1 < 1024; ++vec1) {
		e1.p_word = ATOMIC_READ(e1_p[vec1].p_word);
		if (vec1 == still_prepared_vec2 && !P32_PDIR_E1_ISHINT(e1.p_word))
			e1.p_word &= ~P32_PAGE_FPREPARED;
		if (e1.p_word != P32_PAGE_ABSENT)
			return false; /* Non-present, but with meta-data (hint/prepared) -> Cannot flatten. */
	}
	*new_e2_word = P32_PAGE_ABSENT;
	return true;
}


/* Try to flatten 1024*4KiB of linear memory to a 4MiB mapping */
PRIVATE NOBLOCK void
NOTHROW(FCALL p32_pagedir_unprepare_impl_flatten)(unsigned int vec2,
                                                  unsigned int vec1_unprepare_start,
                                                  unsigned int vec1_unprepare_size) {
	union p32_pdir_e1 *e1_p;
	union p32_pdir_e2 e2, *e2_p;
	unsigned int vec1;
	uintptr_t old_version;
	u32 new_e2_word;
	bool can_flatten;
	assert(vec2 < 1024);
	assert(vec1_unprepare_start < 1024);
	assert(vec1_unprepare_size != 0);
	assert(vec1_unprepare_start + vec1_unprepare_size > vec1_unprepare_start);
	assert(vec1_unprepare_start + vec1_unprepare_size <= 1024);
	assertf(vec2 < P32_PDIR_VEC2INDEX(KERNELSPACE_BASE),
	        "The caller must ensure that no kernel-space addresses get here");
	e2_p = &P32_PDIR_E2_IDENTITY[vec2];
	e2.p_word = ATOMIC_READ(e2_p->p_word);
	if (!(e2.p_word & P32_PAGE_FPRESENT))
		return; /* Not present */
	assertf(!(e2.p_word & P32_PAGE_F4MIB),
	        "A 4MiB page couldn't have been prepared (only 4KiB pages can be)");
	/* Check if the 4KiB vector can be merged.
	 * NOTE: We are guarantied that accessing the E1-vector is OK, because
	 *       the caller guaranties that at least some part of the vector is
	 *       still marked as prepared, meaning that no other thread is able
	 *       to fully free() the vector until we've cleared all of our marked
	 *       bits. */
	e1_p = P32_PDIR_E1_IDENTITY[vec2];
	for (vec1 = vec1_unprepare_start + 1;
	     vec1 < vec1_unprepare_start + vec1_unprepare_size; ++vec1) {
		assertf(ATOMIC_READ(e1_p[vec1].p_word) & P32_PAGE_FPREPARED,
		        "Attempted to unprepare page %p...%p as part of "
		        "%p...%p, but that page wasn't marked as prepared",
		        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1)),
		        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1 + 1) - 1),
		        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1_unprepare_start)),
		        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1_unprepare_start + vec1_unprepare_size) - 1));
		p32_pagedir_unset_prepared(&e1_p[vec1]);
	}
	/* Read the current prepare-version _before_ we check if flattening is
	 * possible. - That way, other threads are allowed to increment the version,
	 * and forcing us to check again further below. */
	old_version = ATOMIC_READ(x86_pagedir_prepare_version);
	can_flatten = p32_pagedir_can_flatten_e1_vector(e1_p, &new_e2_word, vec1_unprepare_start);
	p32_pagedir_unset_prepared(&e1_p[vec1_unprepare_start]);
	if unlikely(can_flatten) {
		pflag_t was;
		bool must_restart;
again_try_exchange_e2_word:
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_WRITE(was);
		if unlikely(old_version != ATOMIC_READ(x86_pagedir_prepare_version))
			must_restart = true;
		else if unlikely(!ATOMIC_CMPXCH(e2_p->p_word, e2.p_word, new_e2_word)) {
			must_restart = true;
		}
		X86_PAGEDIR_PREPARE_LOCK_RELEASE_WRITE(was);
		if unlikely(must_restart) {
			/* Check again if the vector can be flattened.
			 * Note that we need a read-lock to to the prepare-lock in
			 * order to prevent the vector from being freed while we do this */
			X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ_NOVER(was);
			/* Re-load the E2 control word in case it has changed. */
			e2.p_word = ATOMIC_READ(e2_p->p_word);
			if (!(e2.p_word & P32_PAGE_FPRESENT) || (e2.p_word & P32_PAGE_F4MIB)) {
				can_flatten = false; /* Not present, or already a 4MiB mapping */
			} else {
				/* Re-load the active version number before
				 * we check if flatten is (still) possible. */
				old_version = ATOMIC_READ(x86_pagedir_prepare_version);
				can_flatten = p32_pagedir_can_flatten_e1_vector(e1_p, &new_e2_word, 1024);
			}
			X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
			if unlikely(!can_flatten)
				return;
			goto again_try_exchange_e2_word;
		}
		/* Successfully merged the vector.
		 * At this point, all that's left is to free the vector. */
		page_freeone(ppageof(e2.p_word & P32_PAGE_FVECTOR));
	}
}




/* Prepare the page directory for a future map() operation.
 * The full cycle of a single mapping then looks like this:
 * >> p32_pagedir_prepare_map(...);
 * >> p32_pagedir_map(...);
 * >> p32_pagedir_unmap(...);
 * >> p32_pagedir_unprepare_map(...);
 * NOTE: `p32_pagedir_prepare_map_keep()' is the same as `p32_pagedir_prepare_map()', but
 *        will not undo already successfully made preparations after a later one fails.
 *        This will include the undoing of redundant preparations of the given range that
 *        were made in prior calls.
 * @return: true:  Successfully allocated structures required for creating mappings.
 * @return: false: Insufficient physical memory to change mappings. */
INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p32_pagedir_prepare_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	if unlikely((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE)
		return true;
	vec2 = P32_PDIR_VEC2INDEX(addr);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	return p32_pagedir_prepare_impl_widen(vec2, vec1, 1);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unprepare_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	if unlikely((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE)
		return;
	vec2 = P32_PDIR_VEC2INDEX(addr);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	p32_pagedir_unprepare_impl_flatten(vec2, vec1, 1);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p32_pagedir_prepare_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED size_t num_bytes) {
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_end;
	unsigned int vec2;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	if unlikely((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE)
		return true;
	if unlikely((byte_t *)addr + num_bytes > (byte_t *)KERNELSPACE_BASE)
		num_bytes = (size_t)((byte_t *)KERNELSPACE_BASE - (byte_t *)addr);
	if (!num_bytes)
		return true;
	if (num_bytes == 4096)
		return p32_pagedir_prepare_mapone(addr);
	vec2_min = P32_PDIR_VEC2INDEX(addr);
	vec2_max = P32_PDIR_VEC2INDEX((byte_t *)addr + num_bytes - 1);
	vec1_min = P32_PDIR_VEC1INDEX(addr);
	/* Prepare within the same 4MiB region. */
	if likely(vec2_min == vec2_max)
		return p32_pagedir_prepare_impl_widen(vec2_min, vec1_min, num_bytes / 4096);
	vec1_end = P32_PDIR_VEC1INDEX((byte_t *)addr + num_bytes);
	/* Prepare the partial range of the first 4MiB region. */
	if unlikely(!p32_pagedir_prepare_impl_widen(vec2_min, vec1_min, 1024 - vec1_min))
		goto err_0;
	/* Prepare the partial range of the last 4MiB region. */
	if unlikely(!p32_pagedir_prepare_impl_widen(vec2_max, 0, vec1_end))
		goto err_1;
	if unlikely(vec2_min + 1 < vec2_max) {
		/* Now _fully_ prepare all of the intermediate 4MiB regions. */
		for (vec2 = vec2_min + 1; vec2 < vec2_max; ++vec2) {
			if unlikely(!p32_pagedir_prepare_impl_widen(vec2, 0, 1024))
				goto err_2;
		}
	}
	return true;
err_2:
	while (vec2 > vec2_min + 1) {
		--vec2;
		p32_pagedir_unprepare_impl_flatten(vec2, 0, 1024);
	}
	p32_pagedir_unprepare_impl_flatten(vec2_max, 0, vec1_end);
err_1:
	p32_pagedir_unprepare_impl_flatten(vec2_min, vec1_min, 1024 - vec1_min);
err_0:
	return false;
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p32_pagedir_prepare_map_keep)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                            PAGEDIR_PAGEALIGNED size_t num_bytes) {
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_end;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	if unlikely((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE)
		return true;
	if unlikely((byte_t *)addr + num_bytes > (byte_t *)KERNELSPACE_BASE)
		num_bytes = (size_t)((byte_t *)KERNELSPACE_BASE - (byte_t *)addr);
	if (!num_bytes)
		return true;
	if (num_bytes == 4096)
		return p32_pagedir_prepare_mapone(addr);
	vec2_min = P32_PDIR_VEC2INDEX(addr);
	vec2_max = P32_PDIR_VEC2INDEX((byte_t *)addr + num_bytes - 1);
	vec1_min = P32_PDIR_VEC1INDEX(addr);
	/* Prepare within the same 4MiB region. */
	if likely(vec2_min == vec2_max)
		return p32_pagedir_prepare_impl_widen(vec2_min, vec1_min, num_bytes / 4096);
	vec1_end = P32_PDIR_VEC1INDEX((byte_t *)addr + num_bytes);
	/* Prepare the partial range of the first 4MiB region. */
	if unlikely(!p32_pagedir_prepare_impl_widen(vec2_min, vec1_min, 1024 - vec1_min))
		goto err;
	/* Prepare the partial range of the last 4MiB region. */
	if unlikely(!p32_pagedir_prepare_impl_widen(vec2_max, 0, vec1_end))
		goto err;
	if unlikely(vec2_min + 1 < vec2_max) {
		unsigned int vec2;
		/* Now _fully_ prepare all of the intermediate 4MiB regions. */
		for (vec2 = vec2_min + 1; vec2 < vec2_max; ++vec2) {
			if unlikely(!p32_pagedir_prepare_impl_widen(vec2, 0, 1024))
				goto err;
		}
	}
	return true;
err:
	return false;
}



INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unprepare_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                         PAGEDIR_PAGEALIGNED size_t num_bytes) {
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_end;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	if unlikely((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE)
		return;
	if unlikely((byte_t *)addr + num_bytes > (byte_t *)KERNELSPACE_BASE)
		num_bytes = (size_t)((byte_t *)KERNELSPACE_BASE - (byte_t *)addr);
	if (!num_bytes)
		return;
	if (num_bytes == 4096) {
		p32_pagedir_unprepare_mapone(addr);
		return;
	}
	vec2_min = P32_PDIR_VEC2INDEX(addr);
	vec2_max = P32_PDIR_VEC2INDEX((byte_t *)addr + num_bytes - 1);
	vec1_min = P32_PDIR_VEC1INDEX(addr);
	/* Unprepare within the same 4MiB region. */
	if likely(vec2_min == vec2_max) {
		p32_pagedir_unprepare_impl_flatten(vec2_min, vec1_min, num_bytes / 4096);
		return;
	}
	vec1_end = P32_PDIR_VEC1INDEX((byte_t *)addr + num_bytes);
	/* Unprepare the partial range of the first 4MiB region. */
	p32_pagedir_unprepare_impl_flatten(vec2_min, vec1_min, 1024 - vec1_min);
	/* Unprepare the partial range of the last 4MiB region. */
	p32_pagedir_unprepare_impl_flatten(vec2_max, 0, vec1_end);
	if unlikely(vec2_min + 1 < vec2_max) {
		unsigned int vec2;
		/* Now fully unprepare all of the intermediate 4MiB regions. */
		for (vec2 = vec2_min + 1; vec2 < vec2_max; ++vec2)
			p32_pagedir_unprepare_impl_flatten(vec2, 0, 1024);
	}
}


#ifdef NDEBUG
#define p32_pagedir_assert_e1_word_prepared(vec2, vec1, e1_word) (void)0
#else /* NDEBUG */
LOCAL NOBLOCK void
NOTHROW(FCALL p32_pagedir_assert_e1_word_prepared)(unsigned int vec2,
                                                   unsigned int vec1,
                                                   u32 e1_word) {
	union p32_pdir_e2 e2;
	assert(vec1 < 1024);
	assert(vec2 < 1024);
	assertf((e1_word & P32_PAGE_FPREPARED) || P32_PDIR_E1_ISHINT(e1_word),
	        "Cannot set invalid E1 word %I32p for prepared entry",
	        (u32)e1_word);
	e2 = P32_PDIR_E2_IDENTITY[vec2];
	assertf(e2.p_word & P32_PAGE_FPRESENT,
	        "Page vector #%u for page %p...%p isn't allocated",
	        (unsigned int)vec2,
	        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1)),
	        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1) + PAGESIZE - 1));
	assertf(!(e2.p_word & P32_PAGE_F4MIB),
	        "Page %p...%p exists as a present 4MiB page #%u"
	        "Page vector #%u for page %p...%p isn't allocated",
	        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1)),
	        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1) + PAGESIZE - 1),
	        (unsigned int)vec2);
	if (vec2 < P32_PDIR_VEC2INDEX(KERNELSPACE_BASE)) {
		union p32_pdir_e1 e1;
		e1 = P32_PDIR_E1_IDENTITY[vec2][vec1];
		assertf(e1.p_word & P32_PAGE_FPREPARED || P32_PDIR_E1_ISHINT(e1.p_word),
		        "Page %p...%p [vec2=%u,vec1=%u] hasn't been prepared",
		        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1)),
		        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1) + PAGESIZE - 1),
		        vec2, vec1);
	}
}
#endif /* !NDEBUG */


LOCAL NOBLOCK void
NOTHROW(FCALL p32_pagedir_set_e1_word)(unsigned int vec2,
                                       unsigned int vec1,
                                       u32 e1_word) {
	p32_pagedir_assert_e1_word_prepared(vec2, vec1, e1_word);
	COMPILER_WRITE_BARRIER();
	P32_PDIR_E1_IDENTITY[vec2][vec1].p_word = e1_word;
	COMPILER_WRITE_BARRIER();
}

LOCAL NOBLOCK void
NOTHROW(FCALL p32_pagedir_andl_e1_word)(unsigned int vec2,
                                        unsigned int vec1,
                                        u32 e1_kept_bits_mask) {
	p32_pagedir_assert_e1_word_prepared(vec2, vec1, e1_kept_bits_mask);
	ATOMIC_FETCHAND(P32_PDIR_E1_IDENTITY[vec2][vec1].p_word, e1_kept_bits_mask);
}

LOCAL NOBLOCK u32
NOTHROW(FCALL p32_pagedir_xch_e1_word)(unsigned int vec2,
                                       unsigned int vec1,
                                       u32 e1_word) {
	p32_pagedir_assert_e1_word_prepared(vec2, vec1, e1_word);
	return ATOMIC_XCH(P32_PDIR_E1_IDENTITY[vec2][vec1].p_word, e1_word);
}


PRIVATE u32 const p32_pageperm_matrix[16] = {
#define COMMON_PRESENT (P32_PAGE_FACCESSED | P32_PAGE_FDIRTY | P32_PAGE_FPRESENT)
	[(0)]                                                                              = P32_PAGE_FPREPARED,
	[(PAGEDIR_MAP_FEXEC)]                                                              = P32_PAGE_FPREPARED | COMMON_PRESENT,
	[(PAGEDIR_MAP_FWRITE)]                                                             = P32_PAGE_FPREPARED | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FEXEC)]                                         = P32_PAGE_FPREPARED | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_MAP_FREAD)]                                                              = P32_PAGE_FPREPARED | COMMON_PRESENT,
	[(PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FEXEC)]                                          = P32_PAGE_FPREPARED | COMMON_PRESENT,
	[(PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE)]                                         = P32_PAGE_FPREPARED | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FEXEC)]                     = P32_PAGE_FPREPARED | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_MAP_FUSER)]                                                              = P32_PAGE_FPREPARED | COMMON_PRESENT | P32_PAGE_FUSER,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FEXEC)]                                          = P32_PAGE_FPREPARED | COMMON_PRESENT | P32_PAGE_FUSER,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FWRITE)]                                         = P32_PAGE_FPREPARED | COMMON_PRESENT | P32_PAGE_FWRITE | P32_PAGE_FUSER,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FEXEC)]                     = P32_PAGE_FPREPARED | COMMON_PRESENT | P32_PAGE_FWRITE | P32_PAGE_FUSER,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FREAD)]                                          = P32_PAGE_FPREPARED | COMMON_PRESENT | P32_PAGE_FUSER,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FEXEC)]                      = P32_PAGE_FPREPARED | COMMON_PRESENT | P32_PAGE_FUSER,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE)]                     = P32_PAGE_FPREPARED | COMMON_PRESENT | P32_PAGE_FWRITE | P32_PAGE_FUSER,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FEXEC)] = P32_PAGE_FPREPARED | COMMON_PRESENT | P32_PAGE_FWRITE | P32_PAGE_FUSER,
#undef COMMON_PRESENT
};

LOCAL NOBLOCK u32
NOTHROW(FCALL p32_pagedir_encode_4kib)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                                       u16 perm) {
	u32 result;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	assertf(IS_ALIGNED(phys, 4096), "phys = " FORMAT_VM_PHYS_T, phys);
	assertf(!(perm & ~PAGEDIR_MAP_FMASK),
	        "Invalid page permissions: %#.4I16x", perm);
#if __SIZEOF_VM_PHYS_T__ > 4
	assertf(phys <= (vm_phys_t)0xfffff000,
	        "Address cannot be mapped under p32: " FORMAT_VM_PHYS_T,
	        phys);
#endif /* __SIZEOF_VM_PHYS_T__ > 4 */
	result  = (u32)phys;
#if PAGEDIR_MAP_FMASK == 0xf
	result |= p32_pageperm_matrix[perm];
#else /* PAGEDIR_MAP_FMASK == 0xf */
	result |= p32_pageperm_matrix[perm & 0xf];
#endif /* PAGEDIR_MAP_FMASK != 0xf */
	if ((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE)
		result |= USED_P32_PAGE_FGLOBAL;
	return result;
}




/* Set a mapping hint for pages apart of the given virtual memory range.
 * Mapping hints are overwritten once a page has been mapped, and when
 * not specified, will default to `NULL'.
 * Their main purpose is to be accessible through atomic means, allowing
 * them to be used by the PAGE_FAULT handler, while still ensuring that
 * access remains non-blocking. */
INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_maphintone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      VIRT /*ALIGNED(P32_PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	unsigned int vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	assertf(IS_ALIGNED((uintptr_t)hint, P32_PAGEDIR_MAPHINT_ALIGNMENT), "hint = %p", hint);
	vec2 = P32_PDIR_VEC2INDEX(addr);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	p32_pagedir_set_e1_word(vec2, vec1, (u32)(uintptr_t)hint | P32_PAGE_FISAHINT);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_maphint)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes,
                                   VIRT /*ALIGNED(P32_PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	size_t i;
	u32 e1_word;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	assertf(IS_ALIGNED((uintptr_t)hint, P32_PAGEDIR_MAPHINT_ALIGNMENT), "hint = %p", hint);
	e1_word = (u32)(uintptr_t)hint | P32_PAGE_FISAHINT;
	for (i = 0; i < num_bytes; i += 4096) {
		unsigned int vec2, vec1;
		byte_t *effective_addr = (byte_t *)addr + i;
		vec2 = P32_PDIR_VEC2INDEX(effective_addr);
		vec1 = P32_PDIR_VEC1INDEX(effective_addr);
		p32_pagedir_set_e1_word(vec2, vec1, e1_word);
	}
}

/* Return the given of the given page, or NULL if no hint has been mapped. */
INTERN NOBLOCK WUNUSED void *
NOTHROW(FCALL p32_pagedir_gethint)(VIRT void *addr) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX(addr);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if unlikely(!(word & P32_PAGE_FPRESENT))
		return NULL; /* Not mapped */
	if unlikely(word & P32_PAGE_F4MIB)
		return NULL; /* 4MiB page */
	vec1 = P32_PDIR_VEC1INDEX(addr);
	word = ATOMIC_READ(P32_PDIR_E1_IDENTITY[vec2][vec1].p_word);
	if unlikely(!P32_PDIR_E1_ISHINT(word))
		return NULL;
	return (void *)(uintptr_t)(word & P32_PAGE_FHINT);
}

/* Create/delete a page-directory mapping.
 * @param: perm: A set of `PAGEDIR_MAP_F*' detailing how memory should be mapped. */
INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                                  u16 perm) {
	u32 e1_word;
	unsigned int vec2, vec1;
	e1_word = p32_pagedir_encode_4kib(addr, phys, perm);
	vec2 = P32_PDIR_VEC2INDEX(addr);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	p32_pagedir_set_e1_word(vec2, vec1, e1_word);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes,
                               PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                                u16 perm) {
	size_t i;
	u32 e1_word;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	e1_word = p32_pagedir_encode_4kib(addr, phys, perm);
	for (i = 0; i < num_bytes; i += 4096) {
		unsigned int vec2, vec1;
		byte_t *effective_addr = (byte_t *)addr + i;
		vec2 = P32_PDIR_VEC2INDEX(effective_addr);
		vec1 = P32_PDIR_VEC1INDEX(effective_addr);
		p32_pagedir_set_e1_word(vec2, vec1, e1_word);
		e1_word += 4096;
	}
}

/* Special variants of `pagedir_mapone()' that should be used to
 * temporary override the mapping of a single, prepared page.
 * These functions are mainly intended for use with `this_trampoline_page', allowing
 * each thread to push/pop its trampoline page, with doing so actually being an atomic
 * operation in the sense that the data is entirely thread-private, while modifications
 * do not require any kind of lock.
 * NOTE: If the page had been mapped, `pagedir_pop_mapone()' will automatically sync the page. */
INTERN NOBLOCK WUNUSED p32_pagedir_pushval_t
NOTHROW(FCALL p32_pagedir_push_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                                       u16 perm) {
	u32 e1_word, result;
	unsigned int vec2, vec1;
	e1_word = p32_pagedir_encode_4kib(addr, phys, perm);
	vec2 = P32_PDIR_VEC2INDEX(addr);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	result = p32_pagedir_xch_e1_word(vec2, vec1, e1_word);
	return result;
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_pop_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      p32_pagedir_pushval_t backup) {
	u32 old_word;
	unsigned int vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	vec2 = P32_PDIR_VEC2INDEX(addr);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	old_word = p32_pagedir_xch_e1_word(vec2, vec1, (u32)backup);
	if (old_word & P32_PAGE_FPRESENT)
		pagedir_syncone(addr); /* The old mapping was also present (explicitly refresh the page). */
}

/* Unmap pages from the given address range. (requires that the given area be prepared) */
INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unmapone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	vec2 = P32_PDIR_VEC2INDEX(addr);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	p32_pagedir_set_e1_word(vec2, vec1,
	                        P32_PAGE_ABSENT |
	                        P32_PAGE_FPREPARED);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unmap)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes) {
	size_t i;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	for (i = 0; i < num_bytes; i += 4096) {
		unsigned int vec2, vec1;
		byte_t *effective_addr = (byte_t *)addr + i;
		vec2 = P32_PDIR_VEC2INDEX(effective_addr);
		vec1 = P32_PDIR_VEC1INDEX(effective_addr);
		p32_pagedir_set_e1_word(vec2, vec1,
		                        P32_PAGE_ABSENT |
		                        P32_PAGE_FPREPARED);
	}
}

/* Remove write-permissions from the given address range. (requires that the given area be prepared) */
INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unwriteone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	vec2 = P32_PDIR_VEC2INDEX(addr);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	p32_pagedir_andl_e1_word(vec2, vec1, ~P32_PAGE_FWRITE);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unwrite)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes) {
	size_t i;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	for (i = 0; i < num_bytes; i += 4096) {
		unsigned int vec2, vec1;
		byte_t *effective_addr = (byte_t *)addr + i;
		vec2 = P32_PDIR_VEC2INDEX(effective_addr);
		vec1 = P32_PDIR_VEC1INDEX(effective_addr);
		p32_pagedir_andl_e1_word(vec2, vec1, ~P32_PAGE_FWRITE);
	}
}

/* Unmap the entirety of user-space.
 * NOTE: Unlike all other unmap() functions, this one guaranties that it
 *       can perform the task without needing to allocate more memory! */
INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unmap_userspace)(struct vm *__restrict sync_vm) {
	unsigned int vec2, free_count = 0;
	u32 free_pages[64];
	/* Map all pages before the share-segment as absent. */
	for (vec2 = 0; vec2 < P32_PDIR_VEC2INDEX(KERNELSPACE_BASE); ++vec2) {
		union p32_pdir_e2 e2;
		u32 pageptr;
again_read_word:
		e2.p_word = ATOMIC_READ(P32_PDIR_E2_IDENTITY[vec2].p_word);
		if likely(!(e2.p_word & P32_PAGE_FPRESENT))
			continue; /* Not allocated */
		/* Delete this vector. */
		if unlikely(!ATOMIC_CMPXCH_WEAK(P32_PDIR_E2_IDENTITY[vec2].p_word, e2.p_word, P32_PAGE_ABSENT))
			goto again_read_word;
		if unlikely(e2.p_word & P32_PAGE_F4MIB)
			continue; /* 4MiB page. */
		pageptr = e2.p_word >> P32_PAGE_SHIFT;
		if unlikely(free_count >= COMPILER_LENOF(free_pages)) {
			/* Must sync memory before we can actually delete pages.
			 * Otherwise, other CPUs may still be using the mappings after
			 * they've already been re-designated as general-purpose RAM, at
			 * which point they'd start reading garbage, or corrupt pointers. */
			vm_syncall_locked(sync_vm);
			page_freeone((pageptr_t)pageptr);
			do {
				--free_count;
				page_freeone((pageptr_t)free_pages[free_count]);
			} while (free_count);
		} else {
			free_pages[free_count++] = (u32)pageptr;
		}
	}
	/* Free any remaining pages. */
	if (free_count) {
		vm_syncall_locked(sync_vm);
		do {
			--free_count;
			page_freeone((pageptr_t)free_pages[free_count]);
		} while (free_count);
	}
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unmap_userspace_nosync)(void) {
	unsigned int vec2;
	/* Map all pages before the share-segment as absent. */
	for (vec2 = 0; vec2 < P32_PDIR_VEC2INDEX(KERNELSPACE_BASE); ++vec2) {
		union p32_pdir_e2 e2;
		u32 pageptr;
again_read_word:
		e2.p_word = ATOMIC_READ(P32_PDIR_E2_IDENTITY[vec2].p_word);
		if likely(!(e2.p_word & P32_PAGE_FPRESENT))
			continue; /* Not allocated */
		/* Delete this vector. */
		if unlikely(!ATOMIC_CMPXCH_WEAK(P32_PDIR_E2_IDENTITY[vec2].p_word, e2.p_word, P32_PAGE_ABSENT))
			goto again_read_word;
		if unlikely(e2.p_word & P32_PAGE_F4MIB)
			continue; /* 4MiB page. */
		pageptr = e2.p_word >> P32_PAGE_SHIFT;
		page_freeone((pageptr_t)pageptr);
	}
}

/* Translate a virtual address into its physical counterpart. */
INTERN NOBLOCK ATTR_PURE WUNUSED PHYS vm_phys_t
NOTHROW(FCALL p32_pagedir_translate)(VIRT void *addr) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX(addr);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	assertf(word & P32_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	if unlikely(word & P32_PAGE_F4MIB)
		return (vm_phys_t)((word & P32_PAGE_FADDR_4MIB) | P32_PDIR_PAGEINDEX_4MIB(addr));
	vec1 = P32_PDIR_VEC1INDEX(addr);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	assertf(word & P32_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	return (vm_phys_t)((word & P32_PAGE_FADDR_4KIB) | P32_PDIR_PAGEINDEX_4KIB(addr));
}

/* Check if the given page is mapped. */
INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL p32_pagedir_ismapped)(VIRT void *addr) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX(addr);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if (!(word & P32_PAGE_FPRESENT))
		return false;
	if unlikely(word & P32_PAGE_F4MIB)
		return true;
	vec1 = P32_PDIR_VEC1INDEX(addr);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	return (word & P32_PAGE_FPRESENT) != 0;
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL p32_pagedir_iswritable)(VIRT void *addr) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX(addr);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if (!(word & P32_PAGE_FPRESENT))
		return false;
	if unlikely(word & P32_PAGE_F4MIB)
		return (word & P32_PAGE_FWRITE) != 0;
	vec1 = P32_PDIR_VEC1INDEX(addr);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	return (word & (P32_PAGE_FWRITE | P32_PAGE_FPRESENT)) ==
	       /*   */ (P32_PAGE_FWRITE | P32_PAGE_FPRESENT);
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL p32_pagedir_isuseraccessible)(VIRT void *addr) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX(addr);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if (!(word & P32_PAGE_FPRESENT))
		return false;
	if unlikely(word & P32_PAGE_F4MIB)
		return (word & P32_PAGE_FUSER) != 0;
	vec1 = P32_PDIR_VEC1INDEX(addr);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	return (word & (P32_PAGE_FUSER | P32_PAGE_FPRESENT)) ==
	       /*   */ (P32_PAGE_FUSER | P32_PAGE_FPRESENT);
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL p32_pagedir_isuserwritable)(VIRT void *addr) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX(addr);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if (!(word & P32_PAGE_FPRESENT))
		return false;
	if unlikely(word & P32_PAGE_F4MIB)
		return (word & (P32_PAGE_FUSER | P32_PAGE_FWRITE)) ==
		       /*   */ (P32_PAGE_FUSER | P32_PAGE_FWRITE);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	return (word & (P32_PAGE_FUSER | P32_PAGE_FPRESENT | P32_PAGE_FWRITE)) ==
	       /*   */ (P32_PAGE_FUSER | P32_PAGE_FPRESENT | P32_PAGE_FWRITE);
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL p32_pagedir_haschanged)(VIRT void *addr) {
	u32 word;
	unsigned int vec2, vec1;
	/* TODO: Figure out a better design for this function
	 *       The current system is written under the assumption that 4MiB pages don't exist... */
	vec2 = P32_PDIR_VEC2INDEX(addr);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if (!(word & P32_PAGE_FPRESENT))
		return false;
	if unlikely(word & P32_PAGE_F4MIB)
		return true; /* 4MiB pages aren't supported for this purpose */
	vec1 = P32_PDIR_VEC1INDEX(addr);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	return (word & (P32_PAGE_FDIRTY | P32_PAGE_FPRESENT)) ==
	       /*   */ (P32_PAGE_FDIRTY | P32_PAGE_FPRESENT);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unsetchanged)(VIRT void *addr) {
	u32 word;
	unsigned int vec2, vec1;
	/* TODO: Figure out a better design for this function
	 *       The current system is written under the assumption that 4MiB pages don't exist... */
	vec2 = P32_PDIR_VEC2INDEX(addr);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if (!(word & P32_PAGE_FPRESENT))
		return;
	if unlikely(word & P32_PAGE_F4MIB)
		return; /* 4MiB pages aren't supported for this purpose */
	vec1 = P32_PDIR_VEC1INDEX(addr);
	do {
		word = ATOMIC_READ(P32_PDIR_E1_IDENTITY[vec2][vec1].p_word);
		if unlikely((word & (P32_PAGE_FPRESENT | P32_PAGE_FDIRTY)) ==
		            /*   */ (P32_PAGE_FPRESENT | P32_PAGE_FDIRTY))
			return;
	} while (!ATOMIC_CMPXCH_WEAK(P32_PDIR_E1_IDENTITY[vec2][vec1].p_word,
	                             word, word & ~P32_PAGE_FDIRTY));
}


#if 0 /* TODO */
#ifndef __OPTIMIZE_SIZE__

INTERN NOBLOCK ATTR_PURE WUNUSED PHYS vm_phys_t
NOTHROW(KCALL pagedir_translate_p)(VIRT pagedir_t *__restrict self,
                                   VIRT void *virt_addr) {
	u32 result;
	result = self->pd_p32.p_e2[P32_PDIR_VEC2INDEX(virt_addr)].p_word;
	if (result & P32_PAGE_F4MIB)
		return (vm_phys_t)((result & P32_PAGE_FADDR_4MIB) | P32_PDIR_PAGEINDEX_4MIB(virt_addr));
	assertf(result & P32_PAGE_FPRESENT, "Page at %p is not mapped", virt_addr);
	result = vm_readphysl((vm_phys_t)((result & P32_PAGE_FADDR_4KIB) + P32_PDIR_VEC1INDEX(virt_addr) * 4));
	return (vm_phys_t)((result & P32_PAGE_FADDR_4KIB) | P32_PDIR_PAGEINDEX_4KIB(virt_addr));
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(KCALL pagedir_ismapped_p)(VIRT pagedir_t *__restrict self, VIRT pageid_t vpage) {
	u32 temp;
	unsigned int vec2;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(vpage);
	temp = self->pd_p32.p_e2[vec2].p_word;
	if (!(temp & P32_PAGE_FPRESENT))
		return false;
	if (temp & P32_PAGE_F4MIB)
		return true;
	temp = vm_readphysl((temp & P32_PAGE_FADDR_4KIB) + P32_PDIR_VEC1INDEX_VPAGE(vpage) * 4);
	return !!(temp & P32_PAGE_FPRESENT);
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(KCALL pagedir_iswritable_p)(VIRT pagedir_t *__restrict self, VIRT pageid_t vpage) {
	u32 temp;
	unsigned int vec2;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(vpage);
	temp = self->pd_p32.p_e2[vec2].p_word;
	if (!(temp & P32_PAGE_FPRESENT))
		return false;
	if (temp & P32_PAGE_F4MIB)
		return temp & P32_PAGE_FWRITE;
	temp = vm_readphys32_small_aligned((temp & P32_PAGE_FADDR_4KIB) + P32_PDIR_VEC1INDEX_VPAGE(vpage) * 4);
	return (temp & (P32_PAGE_FWRITE | P32_PAGE_FPRESENT)) == (P32_PAGE_FWRITE | P32_PAGE_FPRESENT);
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(KCALL pagedir_isuseraccessible_p)(VIRT pagedir_t *__restrict self, VIRT pageid_t vpage) {
	u32 temp;
	unsigned int vec2;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(vpage);
	temp = self->pd_p32.p_e2[vec2].p_word;
	if (!(temp & P32_PAGE_FPRESENT))
		return false;
	if (temp & P32_PAGE_F4MIB)
		return temp & P32_PAGE_FUSER;
	temp = vm_readphys32_small_aligned((temp & P32_PAGE_FADDR_4KIB) + P32_PDIR_VEC1INDEX_VPAGE(vpage) * 4);
	return (temp & (P32_PAGE_FUSER | P32_PAGE_FPRESENT)) == (P32_PAGE_FUSER | P32_PAGE_FPRESENT);
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(KCALL pagedir_isuserwritable_p)(VIRT pagedir_t *__restrict self, VIRT pageid_t vpage) {
	u32 temp;
	unsigned int vec2;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(vpage);
	temp = self->pd_p32.p_e2[vec2].p_word;
	if (!(temp & P32_PAGE_FPRESENT))
		return false;
	if (temp & P32_PAGE_F4MIB)
		return (temp & (P32_PAGE_FUSER | P32_PAGE_FWRITE)) == (P32_PAGE_FUSER | P32_PAGE_FWRITE);
	temp = vm_readphys32_small_aligned((temp & P32_PAGE_FADDR_4KIB) + P32_PDIR_VEC1INDEX_VPAGE(vpage) * 4);
	return (temp & (P32_PAGE_FUSER | P32_PAGE_FPRESENT | P32_PAGE_FWRITE)) == (P32_PAGE_FUSER | P32_PAGE_FPRESENT | P32_PAGE_FWRITE);
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(KCALL pagedir_haschanged_p)(VIRT pagedir_t *__restrict self, VIRT pageid_t vpage) {
	u32 temp;
	unsigned int vec2;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(vpage);
	temp = self->pd_p32.p_e2[vec2].p_word;
	if (!(temp & P32_PAGE_FPRESENT))
		return false;
	if (temp & P32_PAGE_F4MIB)
		return !!(temp & P32_PAGE_FDIRTY);
	temp = vm_readphys32_small_aligned((temp & P32_PAGE_FADDR_4KIB) + P32_PDIR_VEC1INDEX_VPAGE(vpage) * 4);
	return (temp & (P32_PAGE_FDIRTY | P32_PAGE_FPRESENT)) == (P32_PAGE_FDIRTY | P32_PAGE_FPRESENT);
}

#endif /* !__OPTIMIZE_SIZE__ */
#endif


DECL_END

#endif /* !CONFIG_NO_PAGING_P32 */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_P32_C_INL */
