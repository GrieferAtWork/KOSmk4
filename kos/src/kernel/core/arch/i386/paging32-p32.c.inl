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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_PAGING32_P32_C_INL
#define GUARD_KERNEL_CORE_ARCH_I386_PAGING32_P32_C_INL 1
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

#include "paging32-com.h"

DECL_BEGIN


STATIC_ASSERT(sizeof(struct p32_pdir) == P32_PDIR_SIZE);
STATIC_ASSERT(sizeof(struct p32_pdir) == 4096);
STATIC_ASSERT(sizeof(union p32_pdir_e2) == 4);
STATIC_ASSERT(sizeof(union p32_pdir_e1) == 4);
STATIC_ASSERT(P32_PDIR_E1_IDENTITY_BASE == P32_VM_KERNEL_PDIR_IDENTITY_BASE);
STATIC_ASSERT(P32_PDIR_E2_IDENTITY_BASE == (P32_PDIR_E1_IDENTITY_BASE + (P32_PDIR_VEC2INDEX(P32_PDIR_E1_IDENTITY_BASE) * P32_PDIR_E1_SIZE)));



/* Initialize the given page directory.
 * The caller is required to allocate the page directory
 * controller itself, which must be aligned and sized
 * according to `PAGEDIR_ALIGN' and `PAGEDIR_SIZE'. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p32_pagedir_init)(VIRT struct p32_pdir *__restrict self,
                                PHYS vm_phys_t phys_self) {
	/* Assert some constants assumed below. */
	STATIC_ASSERT(P32_PDIR_VEC2INDEX(KERNEL_BASE) == 768);
	STATIC_ASSERT(P32_PDIR_VEC1INDEX(KERNEL_BASE) == 0);
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
			page_free(VM_ADDR2PAGE((vm_phys_t)(e2.p_word & P32_PAGE_FVECTOR)), 1);
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
	vm_vpage_t tramp;
	uintptr_t backup;
	assert(vec2 < 1024);
	assert(vec1_prepare_start < 1024);
	assert(vec1_prepare_size != 0);
	assert(vec1_prepare_start + vec1_prepare_size > vec1_prepare_start);
	assert(vec1_prepare_start + vec1_prepare_size <= 1024);
	assertf(vec2 < P32_PDIR_VEC2INDEX(KERNEL_BASE),
	        "The caller must ensure that no kernel-space addresses get here");
	e2_p = &P32_PDIR_E2_IDENTITY[vec2];
again:
	e2.p_word = ATOMIC_READ(e2_p->p_word);
	if (!e2.p_vec1.v_present) {
		/* Not present */
		new_e1_vector = page_malloc(1);
		if unlikely(new_e1_vector == PAGEPTR_INVALID)
			return false;
		/* Initialize the inner vector.
		 * We can safely make use of our trampoline, since kernel-space is always prepared. */
		tramp  = THIS_TRAMPOLINE_PAGE;
		backup = p32_pagedir_push_mapone(tramp, new_e1_vector,
		                                 PAGEDIR_MAP_FWRITE);
		pagedir_syncone(tramp);
		e1_p = (union p32_pdir_e1 *)VM_PAGE2ADDR(tramp);
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
		p32_pagedir_pop_mapone(tramp, backup);
		/* Map the new vector. */
		new_e2_word = VM_PAGE2ADDR((u32)new_e1_vector) |
		              P32_PAGE_FPRESENT | P32_PAGE_FWRITE | P32_PAGE_FACCESSED;
#if 0 /* This is always the case: Kernel-space always has all vectors allocated. */
		if (vec2 < P32_PDIR_VEC2INDEX(KERNEL_BASE))
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
		new_e1_vector = page_malloc(1);
		if unlikely(new_e1_vector == PAGEPTR_INVALID)
			return false;
		e1.p_word = e2.p_word & ~(P32_PAGE_F4MIB | P32_PAGE_FPAT_4MIB);
		if (e2.p_word & P32_PAGE_FPAT_4MIB)
			e1.p_word |= P32_PAGE_FPAT_4KIB;
		tramp  = THIS_TRAMPOLINE_PAGE;
		backup = p32_pagedir_push_mapone(tramp, new_e1_vector,
		                                 PAGEDIR_MAP_FWRITE);
		pagedir_syncone(tramp);
		e1_p = (union p32_pdir_e1 *)VM_PAGE2ADDR(tramp);
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
		p32_pagedir_pop_mapone(tramp, backup);
		COMPILER_WRITE_BARRIER();
		new_e2_word  = VM_PAGE2ADDR((u32)new_e1_vector);
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
	assertf(vec2 < P32_PDIR_VEC2INDEX(KERNEL_BASE),
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
		page_free(VM_ADDR2PAGE((vm_phys_t)(e2.p_word & P32_PAGE_FVECTOR)), 1);
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
NOTHROW(FCALL p32_pagedir_prepare_mapone)(VIRT vm_vpage_t virt_page) {
	unsigned int vec2, vec1;
	if unlikely(virt_page >= (vm_vpage_t)KERNEL_BASE_PAGE)
		return true;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(virt_page);
	return p32_pagedir_prepare_impl_widen(vec2, vec1, 1);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unprepare_mapone)(VIRT vm_vpage_t virt_page) {
	unsigned int vec2, vec1;
	if unlikely(virt_page >= (vm_vpage_t)KERNEL_BASE_PAGE)
		return;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(virt_page);
	p32_pagedir_unprepare_impl_flatten(vec2, vec1, 1);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p32_pagedir_prepare_map)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_end;
	unsigned int vec2;
	if unlikely(virt_page >= (vm_vpage_t)KERNEL_BASE_PAGE)
		return true;
	assert(virt_page + num_pages >= virt_page);
	if unlikely(virt_page + num_pages > (vm_vpage_t)KERNEL_BASE_PAGE)
		num_pages = (size_t)((vm_vpage_t)KERNEL_BASE_PAGE - virt_page);
	switch (num_pages) {
	case 0:
		return true;
	case 1:
		return p32_pagedir_prepare_mapone(virt_page);
	default:
		break;
	}
	vec2_min = P32_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec2_max = P32_PDIR_VEC2INDEX_VPAGE(virt_page + num_pages - 1);
	vec1_min = P32_PDIR_VEC1INDEX_VPAGE(virt_page);
	/* Prepare within the same 4MiB region. */
	if likely(vec2_min == vec2_max)
		return p32_pagedir_prepare_impl_widen(vec2_min, vec1_min, num_pages);
	vec1_end = P32_PDIR_VEC1INDEX_VPAGE(virt_page + num_pages);
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
NOTHROW(FCALL p32_pagedir_prepare_map_keep)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_end;
	if unlikely(virt_page >= (vm_vpage_t)KERNEL_BASE_PAGE)
		return true;
	assert(virt_page + num_pages >= virt_page);
	if unlikely(virt_page + num_pages > (vm_vpage_t)KERNEL_BASE_PAGE)
		num_pages = (size_t)((vm_vpage_t)KERNEL_BASE_PAGE - virt_page);
	switch (num_pages) {
	case 0:
		return true;
	case 1:
		return p32_pagedir_prepare_mapone(virt_page);
	default:
		break;
	}
	vec2_min = P32_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec2_max = P32_PDIR_VEC2INDEX_VPAGE(virt_page + num_pages - 1);
	vec1_min = P32_PDIR_VEC1INDEX_VPAGE(virt_page);
	/* Prepare within the same 4MiB region. */
	if likely(vec2_min == vec2_max)
		return p32_pagedir_prepare_impl_widen(vec2_min, vec1_min, num_pages);
	vec1_end = P32_PDIR_VEC1INDEX_VPAGE(virt_page + num_pages);
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
NOTHROW(FCALL p32_pagedir_unprepare_map)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_end;
	if unlikely(virt_page >= (vm_vpage_t)KERNEL_BASE_PAGE)
		return;
	assert(virt_page + num_pages >= virt_page);
	if unlikely(virt_page + num_pages > (vm_vpage_t)KERNEL_BASE_PAGE)
		num_pages = (size_t)((vm_vpage_t)KERNEL_BASE_PAGE - virt_page);
	switch (num_pages) {
	case 0:
		return;
	case 1:
		p32_pagedir_unprepare_mapone(virt_page);
		return;
	default:
		break;
	}
	vec2_min = P32_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec2_max = P32_PDIR_VEC2INDEX_VPAGE(virt_page + num_pages - 1);
	vec1_min = P32_PDIR_VEC1INDEX_VPAGE(virt_page);
	/* Unprepare within the same 4MiB region. */
	if likely(vec2_min == vec2_max) {
		p32_pagedir_unprepare_impl_flatten(vec2_min, vec1_min, num_pages);
		return;
	}
	vec1_end = P32_PDIR_VEC1INDEX_VPAGE(virt_page + num_pages);
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
	        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1) + (PAGESIZE - 1)));
	assertf(!(e2.p_word & P32_PAGE_F4MIB),
	        "Page %p...%p exists as a present 4MiB page #%u"
	        "Page vector #%u for page %p...%p isn't allocated",
	        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1)),
	        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1) + (PAGESIZE - 1)),
	        (unsigned int)vec2);
	if (vec2 < P32_PDIR_VEC2INDEX(KERNEL_BASE)) {
		union p32_pdir_e1 e1;
		e1 = P32_PDIR_E1_IDENTITY[vec2][vec1];
		assertf(e1.p_word & P32_PAGE_FPREPARED || P32_PDIR_E1_ISHINT(e1.p_word),
		        "Page %p...%p [vec2=%u,vec1=%u] hasn't been prepared",
		        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1)),
		        (uintptr_t)(P32_PDIR_VECADDR(vec2, vec1) + (PAGESIZE - 1)),
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
NOTHROW(FCALL p32_pagedir_encode_4kib)(PHYS vm_vpage_t dest_page,
                                       PHYS vm_ppage_t phys_page, u16 perm) {
	u32 result;
	assertf(!(perm & ~PAGEDIR_MAP_FMASK),
	        "Invalid page permissions: %#.4I16x", perm);
	assertf(phys_page <= (vm_ppage_t)VM_ADDR2PAGE(0xfffff000),
	        "Page cannot be mapped: %I64p",
	        (u64)VM_PPAGE2ADDR(phys_page));
	result  = (u32)VM_PPAGE2ADDR(phys_page);
#if PAGEDIR_MAP_FMASK == 0xf
	result |= p32_pageperm_matrix[perm];
#else
	result |= p32_pageperm_matrix[perm & 0xf];
#endif
	if (dest_page >= (vm_vpage_t)KERNEL_BASE_PAGE)
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
NOTHROW(FCALL p32_pagedir_maphintone)(VIRT vm_vpage_t virt_page,
                                      VIRT /*ALIGNED(P32_PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	unsigned int vec2, vec1;
	assertf(virt_page <= VM_VPAGE_MAX, "Invalid page %I64p", (u64)virt_page);
	assert(IS_ALIGNED((uintptr_t)hint, P32_PAGEDIR_MAPHINT_ALIGNMENT));
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(virt_page);
	p32_pagedir_set_e1_word(vec2, vec1, (u32)(uintptr_t)hint | P32_PAGE_FISAHINT);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_maphint)(VIRT vm_vpage_t virt_page, size_t num_pages,
                                   VIRT /*ALIGNED(P32_PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	size_t i;
	u32 e1_word;
	assertf(virt_page <= VM_VPAGE_MAX, "Invalid page range %I64p...%I64p", (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages >= virt_page, "Invalid page %I64p...%I64p", (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages <= VM_VPAGE_MAX, "Invalid page %I64p...%I64ps", (u64)virt_page, (u64)virt_page + num_pages - 1);
	assert(IS_ALIGNED((uintptr_t)hint, P32_PAGEDIR_MAPHINT_ALIGNMENT));
	e1_word = (u32)(uintptr_t)hint | P32_PAGE_FISAHINT;
	for (i = 0; i < num_pages; ++i) {
		unsigned int vec2, vec1;
		vm_vpage_t effective_virt_page = virt_page + i;
		vec2 = P32_PDIR_VEC2INDEX_VPAGE(effective_virt_page);
		vec1 = P32_PDIR_VEC1INDEX_VPAGE(effective_virt_page);
		p32_pagedir_set_e1_word(vec2, vec1, e1_word);
	}
}

/* Return the given of the given page, or NULL if no hint has been mapped. */
INTERN NOBLOCK WUNUSED void *
NOTHROW(FCALL p32_pagedir_gethint)(VIRT vm_vpage_t virt_page) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(virt_page);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if unlikely(!(word & P32_PAGE_FPRESENT))
		return NULL; /* Not mapped */
	if unlikely(word & P32_PAGE_F4MIB)
		return NULL; /* 4MiB page */
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(virt_page);
	word = ATOMIC_READ(P32_PDIR_E1_IDENTITY[vec2][vec1].p_word);
	if unlikely(!P32_PDIR_E1_ISHINT(word))
		return NULL;
	return (void *)(uintptr_t)(word & P32_PAGE_FHINT);
}

/* Create/delete a page-directory mapping.
 * @param: perm: A set of `PAGEDIR_MAP_F*' detailing how memory should be mapped. */
INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_mapone)(VIRT vm_vpage_t virt_page,
                                  PHYS vm_ppage_t phys_page, u16 perm) {
	u32 e1_word;
	unsigned int vec2, vec1;
	e1_word = p32_pagedir_encode_4kib(virt_page, phys_page, perm);
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(virt_page);
	p32_pagedir_set_e1_word(vec2, vec1, e1_word);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_map)(VIRT vm_vpage_t virt_page, size_t num_pages,
                               PHYS vm_ppage_t phys_page, u16 perm) {
	size_t i;
	u32 e1_word;
	assertf(virt_page <= VM_VPAGE_MAX, "Invalid page range %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages >= virt_page, "Invalid page %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages <= VM_VPAGE_MAX, "Invalid page %I64p...%I64ps",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	e1_word = p32_pagedir_encode_4kib(virt_page, phys_page, perm);
	for (i = 0; i < num_pages; ++i) {
		unsigned int vec2, vec1;
		vm_vpage_t effective_virt_page = virt_page + i;
		vec2 = P32_PDIR_VEC2INDEX_VPAGE(effective_virt_page);
		vec1 = P32_PDIR_VEC1INDEX_VPAGE(effective_virt_page);
		p32_pagedir_set_e1_word(vec2, vec1, e1_word);
		e1_word += 4096;
	}
}

/* Special variants of `pagedir_mapone()' that should be used to
 * temporary override the mapping of a single, prepared page.
 * These functions are mainly intended for use with `_this_trampoline_page', allowing
 * each thread to push/pop its trampoline page, with doing so actually being an atomic
 * operation in the sense that the data is entirely thread-private, while modifications
 * do not require any kind of lock.
 * NOTE: If the page had been mapped, `pagedir_pop_mapone()' will automatically sync the page. */
INTERN NOBLOCK WUNUSED p32_pagedir_pushval_t
NOTHROW(FCALL p32_pagedir_push_mapone)(VIRT vm_vpage_t virt_page,
                                       PHYS vm_ppage_t phys_page, u16 perm) {
	u32 e1_word, result;
	unsigned int vec2, vec1;
	e1_word = p32_pagedir_encode_4kib(virt_page, phys_page, perm);
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(virt_page);
	result = p32_pagedir_xch_e1_word(vec2, vec1, e1_word);
#if 0
	if (result & P32_PAGE_FPRESENT)
		pagedir_syncone(virt_page); /* The old mapping was also present (explicitly refresh the page). */
#endif
	return result;
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_pop_mapone)(VIRT vm_vpage_t virt_page,
                                      p32_pagedir_pushval_t backup) {
	u32 old_word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(virt_page);
	old_word = p32_pagedir_xch_e1_word(vec2, vec1, (u32)backup);
	if (old_word & P32_PAGE_FPRESENT)
		pagedir_syncone(virt_page); /* The old mapping was also present (explicitly refresh the page). */
}

/* Unmap pages from the given address range. (requires that the given area be prepared) */
INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unmapone)(VIRT vm_vpage_t virt_page) {
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(virt_page);
	p32_pagedir_set_e1_word(vec2, vec1,
	                        P32_PAGE_ABSENT | P32_PAGE_FPREPARED);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unmap)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	size_t i;
	assertf(virt_page <= VM_VPAGE_MAX, "Invalid page range %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages >= virt_page, "Invalid page %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages <= VM_VPAGE_MAX, "Invalid page %I64p...%I64ps",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	for (i = 0; i < num_pages; ++i) {
		unsigned int vec2, vec1;
		vm_vpage_t effective_virt_page = virt_page + i;
		vec2 = P32_PDIR_VEC2INDEX_VPAGE(effective_virt_page);
		vec1 = P32_PDIR_VEC1INDEX_VPAGE(effective_virt_page);
		p32_pagedir_set_e1_word(vec2, vec1,
		                        P32_PAGE_ABSENT | P32_PAGE_FPREPARED);
	}
}

/* Remove write-permissions from the given address range. (requires that the given area be prepared) */
INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unwriteone)(VIRT vm_vpage_t virt_page) {
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(virt_page);
	p32_pagedir_andl_e1_word(vec2, vec1, ~P32_PAGE_FWRITE);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unwrite)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	size_t i;
	assertf(virt_page <= VM_VPAGE_MAX, "Invalid page range %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages >= virt_page, "Invalid page %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages <= VM_VPAGE_MAX, "Invalid page %I64p...%I64ps",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	for (i = 0; i < num_pages; ++i) {
		unsigned int vec2, vec1;
		vm_vpage_t effective_virt_page = virt_page + i;
		vec2 = P32_PDIR_VEC2INDEX_VPAGE(effective_virt_page);
		vec1 = P32_PDIR_VEC1INDEX_VPAGE(effective_virt_page);
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
	for (vec2 = 0; vec2 < P32_PDIR_VEC2INDEX(KERNEL_BASE); ++vec2) {
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
	unsigned int vec2, free_count = 0;
	u32 free_pages[64];
	/* Map all pages before the share-segment as absent. */
	for (vec2 = 0; vec2 < P32_PDIR_VEC2INDEX(KERNEL_BASE); ++vec2) {
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
		do {
			--free_count;
			page_freeone((pageptr_t)free_pages[free_count]);
		} while (free_count);
	}
}

/* Translate a virtual address into its physical counterpart. */
INTERN NOBLOCK WUNUSED PHYS vm_phys_t
NOTHROW(FCALL p32_pagedir_translate)(VIRT vm_virt_t virt_addr) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX(virt_addr);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	assertf(word & P32_PAGE_FPRESENT, "Page at %p is not mapped", virt_addr);
	if unlikely(word & P32_PAGE_F4MIB)
		return (vm_phys_t)((word & P32_PAGE_FADDR_4MIB) | P32_PDIR_PAGEINDEX_4MIB(virt_addr));
	vec1 = P32_PDIR_VEC1INDEX(virt_addr);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	assertf(word & P32_PAGE_FPRESENT, "Page at %p is not mapped", virt_addr);
	return (vm_phys_t)((word & P32_PAGE_FADDR_4KIB) | P32_PDIR_PAGEINDEX_4KIB(virt_addr));
}

/* Check if the given page is mapped. */
INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p32_pagedir_ismapped)(VIRT vm_vpage_t vpage) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(vpage);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if (!(word & P32_PAGE_FPRESENT))
		return false;
	if unlikely(word & P32_PAGE_F4MIB)
		return true;
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(vpage);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	return (word & P32_PAGE_FPRESENT) != 0;
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p32_pagedir_iswritable)(VIRT vm_vpage_t vpage) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(vpage);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if (!(word & P32_PAGE_FPRESENT))
		return false;
	if unlikely(word & P32_PAGE_F4MIB)
		return (word & P32_PAGE_FWRITE) != 0;
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(vpage);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	return (word & (P32_PAGE_FWRITE | P32_PAGE_FPRESENT)) ==
	       /*   */ (P32_PAGE_FWRITE | P32_PAGE_FPRESENT);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p32_pagedir_isuseraccessible)(VIRT vm_vpage_t vpage) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(vpage);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if (!(word & P32_PAGE_FPRESENT))
		return false;
	if unlikely(word & P32_PAGE_F4MIB)
		return (word & P32_PAGE_FUSER) != 0;
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(vpage);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	return (word & (P32_PAGE_FUSER | P32_PAGE_FPRESENT)) ==
	       /*   */ (P32_PAGE_FUSER | P32_PAGE_FPRESENT);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p32_pagedir_isuserwritable)(VIRT vm_vpage_t vpage) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(vpage);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if (!(word & P32_PAGE_FPRESENT))
		return false;
	if unlikely(word & P32_PAGE_F4MIB)
		return (word & (P32_PAGE_FUSER | P32_PAGE_FWRITE)) ==
		       /*   */ (P32_PAGE_FUSER | P32_PAGE_FWRITE);
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(vpage);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	return (word & (P32_PAGE_FUSER | P32_PAGE_FPRESENT | P32_PAGE_FWRITE)) ==
	       /*   */ (P32_PAGE_FUSER | P32_PAGE_FPRESENT | P32_PAGE_FWRITE);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p32_pagedir_haschanged)(VIRT vm_vpage_t vpage) {
	u32 word;
	unsigned int vec2, vec1;
	/* TODO: Figure out a better design for this function
	 *       The current system is written under the assumption that 4MiB pages don't exist... */
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(vpage);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if (!(word & P32_PAGE_FPRESENT))
		return false;
	if unlikely(word & P32_PAGE_F4MIB)
		return true; /* 4MiB pages aren't supported for this purpose */
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(vpage);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	return (word & (P32_PAGE_FDIRTY | P32_PAGE_FPRESENT)) ==
	       /*   */ (P32_PAGE_FDIRTY | P32_PAGE_FPRESENT);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unsetchanged)(VIRT vm_vpage_t vpage) {
	u32 word;
	unsigned int vec2, vec1;
	/* TODO: Figure out a better design for this function
	 *       The current system is written under the assumption that 4MiB pages don't exist... */
	vec2 = P32_PDIR_VEC2INDEX_VPAGE(vpage);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	if (!(word & P32_PAGE_FPRESENT))
		return;
	if unlikely(word & P32_PAGE_F4MIB)
		return; /* 4MiB pages aren't supported for this purpose */
	vec1 = P32_PDIR_VEC1INDEX_VPAGE(vpage);
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
LOCAL u32 KCALL vm_readphys32_small_aligned(PHYS u32 src) {
	u32 result;
	vm_vpage_t tramp = THIS_TRAMPOLINE_PAGE;
	pagedir_pushval_t backup;
	backup = pagedir_push_mapone(tramp,
	                             (vm_ppage_t)VM_ADDR2PAGE(src),
	                             PAGEDIR_MAP_FREAD);
	pagedir_syncone(tramp);
	result = *(u32 *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(src & (PAGESIZE - 1)));
	pagedir_pop_mapone(tramp, backup);
	return result;
}

LOCAL NONNULL((1)) void KCALL
vm_copyfromphys_small_aligned(void *__restrict dst,
                              PHYS u32 src,
                              size_t num_bytes) {
	vm_vpage_t tramp = THIS_TRAMPOLINE_PAGE;
	pagedir_pushval_t backup;
	backup = pagedir_push_mapone(tramp,
	                             (vm_ppage_t)VM_ADDR2PAGE(src),
	                             PAGEDIR_MAP_FREAD);
	pagedir_syncone(tramp);
	memcpy(dst, (void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(src & (PAGESIZE - 1))), num_bytes);
	pagedir_pop_mapone(tramp, backup);
}

LOCAL NONNULL((2)) void KCALL
vm_copytophys_small_aligned(PHYS u32 dst,
                            void const *__restrict src,
                            size_t num_bytes) {
	vm_vpage_t tramp = THIS_TRAMPOLINE_PAGE;
	pagedir_pushval_t backup;
	backup = pagedir_push_mapone(tramp,
	                             (vm_ppage_t)VM_ADDR2PAGE(dst),
	                             PAGEDIR_MAP_FREAD);
	pagedir_syncone(tramp);
	memcpy((void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(dst & (PAGESIZE - 1))), src, num_bytes);
	pagedir_pop_mapone(tramp, backup);
}


INTERN NOBLOCK PHYS vm_phys_t
NOTHROW(KCALL pagedir_translate_p)(VIRT pagedir_t *__restrict self, VIRT vm_virt_t virt_addr) {
	u32 result;
	result = self->p_e2[X86_PDIR_VEC2INDEX(virt_addr)].p_data;
	if (result & X86_PAGE_F4MIB)
		return (vm_phys_t)((result & X86_PAGE_FADDR) | X86_PDIR_PAGEINDEX_4MIB(virt_addr));
	assertf(result & X86_PAGE_FPRESENT, "Page at %p is not mapped", virt_addr);
	result = vm_readphys32_small_aligned((result & X86_PAGE_FADDR) + X86_PDIR_VEC1INDEX(virt_addr) * 4);
	return (vm_phys_t)((result & X86_PAGE_FADDR) | X86_PDIR_PAGEINDEX_4KIB(virt_addr));
}

INTERN NOBLOCK bool
NOTHROW(KCALL pagedir_ismapped_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	u32 temp;
	unsigned int vec2;
	vec2 = X86_PDIR_VEC2INDEX_VPAGE(vpage);
	temp = self->p_e2[vec2].p_data;
	if (!(temp & X86_PAGE_FPRESENT))
		return false;
	if (temp & X86_PAGE_F4MIB)
		return true;
	temp = vm_readphys32_small_aligned((temp & X86_PAGE_FADDR) + X86_PDIR_VEC1INDEX_VPAGE(vpage) * 4);
	return !!(temp & X86_PAGE_FPRESENT);
}

INTERN NOBLOCK bool
NOTHROW(KCALL pagedir_iswritable_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	u32 temp;
	unsigned int vec2;
	vec2 = X86_PDIR_VEC2INDEX_VPAGE(vpage);
	temp = self->p_e2[vec2].p_data;
	if (!(temp & X86_PAGE_FPRESENT))
		return false;
	if (temp & X86_PAGE_F4MIB)
		return temp & X86_PAGE_FWRITE;
	temp = vm_readphys32_small_aligned((temp & X86_PAGE_FADDR) + X86_PDIR_VEC1INDEX_VPAGE(vpage) * 4);
	return (temp & (X86_PAGE_FWRITE | X86_PAGE_FPRESENT)) == (X86_PAGE_FWRITE | X86_PAGE_FPRESENT);
}

INTERN NOBLOCK bool
NOTHROW(KCALL pagedir_isuseraccessible_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	u32 temp;
	unsigned int vec2;
	vec2 = X86_PDIR_VEC2INDEX_VPAGE(vpage);
	temp = self->p_e2[vec2].p_data;
	if (!(temp & X86_PAGE_FPRESENT))
		return false;
	if (temp & X86_PAGE_F4MIB)
		return temp & X86_PAGE_FUSER;
	temp = vm_readphys32_small_aligned((temp & X86_PAGE_FADDR) + X86_PDIR_VEC1INDEX_VPAGE(vpage) * 4);
	return (temp & (X86_PAGE_FUSER | X86_PAGE_FPRESENT)) == (X86_PAGE_FUSER | X86_PAGE_FPRESENT);
}

INTERN NOBLOCK bool
NOTHROW(KCALL pagedir_isuserwritable_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	u32 temp;
	unsigned int vec2;
	vec2 = X86_PDIR_VEC2INDEX_VPAGE(vpage);
	temp = self->p_e2[vec2].p_data;
	if (!(temp & X86_PAGE_FPRESENT))
		return false;
	if (temp & X86_PAGE_F4MIB)
		return (temp & (X86_PAGE_FUSER | X86_PAGE_FWRITE)) == (X86_PAGE_FUSER | X86_PAGE_FWRITE);
	temp = vm_readphys32_small_aligned((temp & X86_PAGE_FADDR) + X86_PDIR_VEC1INDEX_VPAGE(vpage) * 4);
	return (temp & (X86_PAGE_FUSER | X86_PAGE_FPRESENT | X86_PAGE_FWRITE)) == (X86_PAGE_FUSER | X86_PAGE_FPRESENT | X86_PAGE_FWRITE);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(KCALL pagedir_haschanged_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	u32 temp;
	unsigned int vec2;
	vec2 = X86_PDIR_VEC2INDEX_VPAGE(vpage);
	temp = self->p_e2[vec2].p_data;
	if (!(temp & X86_PAGE_FPRESENT))
		return false;
	if (temp & X86_PAGE_F4MIB)
		return !!(temp & X86_PAGE_FDIRTY);
	temp = vm_readphys32_small_aligned((temp & X86_PAGE_FADDR) + X86_PDIR_VEC1INDEX_VPAGE(vpage) * 4);
	return (temp & (X86_PAGE_FDIRTY | X86_PAGE_FPRESENT)) == (X86_PAGE_FDIRTY | X86_PAGE_FPRESENT);
}

INTERN NOBLOCK void
NOTHROW(KCALL pagedir_unsetchanged_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t vpage) {
	u32 temp, *e1;
	unsigned int vec2;
	pagedir_pushval_t backup;
	vm_vpage_t tramp;
	vec2 = X86_PDIR_VEC2INDEX_VPAGE(vpage);
	temp = self->p_e2[vec2].p_data;
	if (!(temp & X86_PAGE_FPRESENT))
		return;
	if (temp & X86_PAGE_F4MIB) {
		if (temp & X86_PAGE_FDIRTY)
			__asm__ __volatile__("andl %1, %0"
			                     : "+m"(self->p_e2[vec2].p_data)
			                     : "i"(~X86_PAGE_FDIRTY)
			                     : "cc");
		return;
	}
	tramp  = THIS_TRAMPOLINE_PAGE;
	backup = pagedir_push_mapone(tramp, (vm_ppage_t)VM_ADDR2PAGE(temp),
	                             PAGEDIR_MAP_FWRITE);
	pagedir_syncone(tramp);
	e1 = &((union x86_pdir_e2 *)tramp)[X86_PDIR_VEC1INDEX_VPAGE(vpage)].p_flag;
	if ((*e1 & (X86_PAGE_FDIRTY | X86_PAGE_FPRESENT)) == (X86_PAGE_FDIRTY | X86_PAGE_FPRESENT)) {
		__asm__ __volatile__("andl %1, %0"
		                     : "+m"(*e1)
		                     : "i"(~X86_PAGE_FDIRTY)
		                     : "cc");
	}
	pagedir_pop_mapone(tramp, backup);
}

/* TODO: Add dedicated implementations for all of these: */
INTERN NOBLOCK WUNUSED bool NOTHROW(KCALL pagedir_prepare_mapone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page);
INTERN NOBLOCK void NOTHROW(KCALL pagedir_unprepare_mapone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page);
INTERN NOBLOCK void NOTHROW(KCALL pagedir_maphintone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/void *hint);
INTERN NOBLOCK void NOTHROW(KCALL pagedir_mapone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page, PHYS vm_ppage_t phys_page, u16 perm);
INTERN NOBLOCK void NOTHROW(KCALL pagedir_unmapone_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page);
INTERN NOBLOCK WUNUSED bool NOTHROW(KCALL pagedir_prepare_map_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page, size_t num_pages);
INTERN NOBLOCK void NOTHROW(KCALL pagedir_unprepare_map_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page, size_t num_pages);
INTERN NOBLOCK void NOTHROW(KCALL pagedir_maphint_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page, size_t num_pages, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/void *hint);
INTERN NOBLOCK void NOTHROW(KCALL pagedir_map_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page, size_t num_pages, PHYS vm_ppage_t phys_page, u16 perm);
INTERN NOBLOCK void NOTHROW(KCALL pagedir_unmap_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page, size_t num_pages);
INTERN NOBLOCK void NOTHROW(KCALL pagedir_unwrite_p)(VIRT pagedir_t *__restrict self, VIRT vm_vpage_t virt_page, size_t num_pages);


#endif /* !__OPTIMIZE_SIZE__ */
#endif


DECL_END

#endif /* !CONFIG_NO_PAGING_P32 */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_PAGING32_P32_C_INL */
