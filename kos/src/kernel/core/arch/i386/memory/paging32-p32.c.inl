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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_P32_C_INL
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_P32_C_INL 1
#define __OMIT_PAGING_CONSTANT_P_WRAPPERS
#define __WANT_MMAN_EXCLUDE_PAGEDIR
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/arch/paging32-p32.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/phys.h>
#include <kernel/mman/sync.h>
#include <kernel/paging.h>

#include <hybrid/align.h>
#include <hybrid/sched/preemption.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#ifndef CONFIG_NO_KERNEL_X86_PAGING_P32

#include "paging.h"
#include "paging32-com.h"

DECL_BEGIN

static_assert(sizeof(struct p32_pdir) == P32_PDIR_SIZE);
static_assert(sizeof(struct p32_pdir) == 4096);
static_assert(sizeof(union p32_pdir_e2) == 4);
static_assert(sizeof(union p32_pdir_e1) == 4);
static_assert(P32_PDIR_E1_IDENTITY_BASE == P32_MMAN_KERNEL_PDIR_IDENTITY_BASE);
static_assert(P32_PDIR_E2_IDENTITY_BASE == (P32_PDIR_E1_IDENTITY_BASE + (P32_PDIR_VEC2INDEX(P32_PDIR_E1_IDENTITY_BASE) * P32_PDIR_E1_SIZE)));

/* Return the physical page ID of a given physical address. */
#define ppageof(paddr) (physpage_t)((paddr) / PAGESIZE)

/* Initialize the given page directory.
 * The caller is required to allocate the page directory
 * controller itself, which  must be  aligned and  sized
 * according to `PAGEDIR_ALIGN' and `PAGEDIR_SIZE'. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p32_pagedir_init)(VIRT struct p32_pdir *__restrict self,
                                PHYS struct p32_pdir *phys_self) {
	/* Assert some constants assumed below. */
	static_assert(P32_PDIR_VEC2INDEX(KERNELSPACE_BASE) == 768);
	static_assert(P32_PDIR_VEC1INDEX(KERNELSPACE_BASE) == 0);
	static_assert(P32_PDIR_VEC2INDEX(P32_MMAN_KERNEL_PDIR_IDENTITY_BASE) == 1023);
	static_assert(P32_PDIR_VEC1INDEX(P32_MMAN_KERNEL_PDIR_IDENTITY_BASE) == 0);
	assert(IS_ALIGNED((uintptr_t)self, PAGESIZE));
	assert(IS_ALIGNED((uintptr_t)phys_self, PAGESIZE));

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
			page_freeone_for_paging(ppageof(e2.p_word & P32_PAGE_FVECTOR));
	}
}



LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p32_pagedir_set_prepared)(union p32_pdir_e1 *__restrict e1_p) {
	u32 word;
	for (;;) {
		word = atomic_read(&e1_p->p_word);
		if unlikely(P32_PDIR_E1_ISHINT(word))
			break; /* Special case: Hint */
		if likely(atomic_cmpxch_weak(&e1_p->p_word, word, word | P32_PAGE_FPREPARED))
			break;
	}
}





/* Try to widen a 4MiB mapping to a 1024*4KiB vector of linear memory
 * Alternatively, if the specified vector is absent, pre-allocate it.
 * @return: false: Failed to allocate physical memory */
PRIVATE NOBLOCK WUNUSED bool
NOTHROW(FCALL p32_pagedir_prepare_impl_widen)(unsigned int vec2,
                                              unsigned int vec1_prepare_start,
                                              unsigned int vec1_prepare_size) {
	union p32_pdir_e2 e2, *e2_p;
	union p32_pdir_e1 e1, *e1_p;
	physpage_t new_e1_vector;
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
	e2.p_word = atomic_read(&e2_p->p_word);
	if (!e2.p_vec1.v_present) {
		/* Not present */
		new_e1_vector = page_mallocone32_noblock_for_paging();
		if unlikely(new_e1_vector == PHYSPAGE_INVALID)
			return false;

		/* Initialize the inner vector.
		 * We can safely make use of our trampoline, since kernel-space is always prepared. */
		e1_p   = (union p32_pdir_e1 *)THIS_TRAMPOLINE;
		backup = p32_pagedir_push_mapone(e1_p, physpage2addr(new_e1_vector),
		                                 PAGEDIR_PROT_WRITE);
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
		new_e2_word = physpage2addr32(new_e1_vector) |
		              P32_PAGE_FPRESENT | P32_PAGE_FWRITE | P32_PAGE_FACCESSED;
#if 0 /* This is always the case: Kernel-space always has all vectors allocated. */
		if (vec2 < P32_PDIR_VEC2INDEX(KERNELSPACE_BASE))
#endif
		{
			/* Allow user-space access of stuff that will eventually mapped by this page. */
			new_e2_word |= P32_PAGE_FUSER;
		}
atomic_set_new_e2_word_or_free_new_e1_vector:
		if unlikely(!atomic_cmpxch(&e2_p->p_word, e2.p_word, new_e2_word)) {
			page_free_for_paging(new_e1_vector, 1);
			goto again;
		}
	} else if (e2.p_4mib.d_4mib_1) {
		/* Convert a 4MiB mapping to 1024*4KiB pages
		 * Because the mapping may be getting used _right_ _now_, we have
		 * to be careful about how  we go about initializing the  vector.
		 * Because  the process has to be atomic, we use our thread-local
		 * temporary mapping trampoline to  temporarily map the new  page
		 * for  initialization  (Because   the  trampoline  always   uses
		 * `P32_PAGE_FNOFLATTEN'  when  mapping, it  is  always prepared) */
		new_e1_vector = page_mallocone32_noblock_for_paging();
		if unlikely(new_e1_vector == PHYSPAGE_INVALID)
			return false;
		e1.p_word = e2.p_word & ~(P32_PAGE_F4MIB | P32_PAGE_FPAT_4MIB);
		if (e2.p_word & P32_PAGE_FPAT_4MIB)
			e1.p_word |= P32_PAGE_FPAT_4KIB;
		e1_p   = (union p32_pdir_e1 *)THIS_TRAMPOLINE;
		backup = p32_pagedir_push_mapone(e1_p, physpage2addr(new_e1_vector),
		                                 PAGEDIR_PROT_WRITE);
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
		new_e2_word  = physpage2addr32(new_e1_vector);
		new_e2_word |= P32_PAGE_FPRESENT | P32_PAGE_FWRITE;
		new_e2_word |= e2.p_word & (P32_PAGE_FUSER | P32_PAGE_FPWT |
		                            P32_PAGE_FPCD | P32_PAGE_FACCESSED |
		                            P32_PAGE_FGLOBAL);

		/* Make sure that the vector was allocated and is active */
		goto atomic_set_new_e2_word_or_free_new_e1_vector;
	} else {
		/* Already a fully allocated vector (nothing to do here) */
		preemption_flag_t was;
		assert(P32_PDIR_E2_ISVEC1(e2.p_word));
		e1_p = P32_PDIR_E1_IDENTITY[vec2];

		/* The first page needs to be marked under special conditions. */
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was);

		/* With a prepare-first token held, check if our e2 control work is still correct.
		 * If some other thread flattened the vector  in the mean time, that control  word
		 * will have changed. */
		if unlikely(e2.p_word != atomic_read(&e2_p->p_word)) {
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


/* Called after  an E1-vector  was flattened  into an  E2-entry
 * that now resides at `P32_PDIR_E2_IDENTITY[vec4][vec3][vec2]' */
PRIVATE NOBLOCK void
NOTHROW(FCALL p32_pagedir_sync_flattened_e1_vector)(unsigned int vec2) {
	/* Even  though the in-memory mapping of `P32_PDIR_VECADDR(vec4, vec3, vec2, 0..511)'
	 * didn't change, due to being flattened, the contents of our page directory identity
	 * mapping _have_ changed:
	 *     UNMAP(P32_PDIR_E1_IDENTITY[vec2][0..1023])  (This is exactly 1 page)
	 */
	void *sync_pageaddr;
	sync_pageaddr = P32_PDIR_E1_IDENTITY[vec2];
	if (vec2 >= P32_PDIR_VEC2INDEX(KERNELSPACE_BASE)) {
		/* Sync as part of the kernel MMan */
		mman_supersyncone(sync_pageaddr);
	} else {
		/* Sync as part of the current page directory. */
		pagedir_syncone_smp(sync_pageaddr);
	}
}




PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(KCALL p32_pagedir_can_flatten_e1_vector)(union p32_pdir_e1 const e1_p[1024],
                                                 u32 *__restrict new_e2_word,
                                                 unsigned int still_prepared_vec2) {
	unsigned int vec1;
	union p32_pdir_e1 e1;
	e1.p_word = atomic_read(&e1_p[0].p_word);
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
			e1.p_word = atomic_read(&e1_p[vec1].p_word);
			if __untraced(vec1 == still_prepared_vec2 && !P32_PDIR_E1_ISHINT(e1.p_word))
				e1.p_word &= ~P32_PAGE_FPREPARED;
			flag.p_word |= e1.p_word & (P32_PAGE_FACCESSED | P32_PAGE_FDIRTY);
			if (iter.p_word != (e1.p_word & ~(P32_PAGE_FACCESSED | P32_PAGE_FDIRTY)))
				return false; /* Non-linear memory, or different page attributes/meta-data */
			assert(!(e1.p_word & P32_PAGE_FPREPARED) || P32_PDIR_E1_ISHINT(e1.p_word));
			iter.p_word += 4096;
		}
		e1.p_word |= flag.p_word;
#if P32_PAGE_FPAT_4KIB != P32_PAGE_FPAT_4MIB
		if (e1.p_word & P32_PAGE_FPAT_4KIB) {
#if P32_PAGE_FPAT_4KIB != P32_PAGE_F4MIB
			e1.p_word &= ~P32_PAGE_FPAT_4KIB;
#endif /* P32_PAGE_FPAT_4KIB != P32_PAGE_F4MIB */
			e1.p_word |= P32_PAGE_FPAT_4MIB;
		}
#endif /* P32_PAGE_FPAT_4KIB != P32_PAGE_FPAT_4MIB */
		e1.p_word |= P32_PAGE_F4MIB;
		*new_e2_word = e1.p_word;
		return true;
	}
	if (e1.p_word != P32_PAGE_ABSENT)
		return false; /* Non-present, but with meta-data (hint/prepared) -> Cannot flatten. */

	/* Check if all entries are marked as ABSENT */
	for (vec1 = 1; vec1 < 1024; ++vec1) {
		e1.p_word = atomic_read(&e1_p[vec1].p_word);
		if (vec1 == still_prepared_vec2 && !P32_PDIR_E1_ISHINT(e1.p_word))
			e1.p_word &= ~P32_PAGE_FPREPARED;
		if (e1.p_word != P32_PAGE_ABSENT)
			return false; /* Present, or with meta-data (hint/prepared) -> Cannot flatten. */
	}
	*new_e2_word = P32_PAGE_ABSENT;
	return true;
}

#ifdef NDEBUG
#define p32_pagedir_unset_prepared(e1_p, vec2, vec1, vec1_unprepare_start, vec1_unprepare_size) \
	p32_pagedir_unset_prepared(e1_p)
#endif /* NDEBUG */

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p32_pagedir_unset_prepared)(union p32_pdir_e1 *__restrict e1_p
#ifndef NDEBUG
                                          ,
                                          unsigned int vec2,
                                          unsigned int vec1,
                                          unsigned int vec1_unprepare_start,
                                          unsigned int vec1_unprepare_size
#endif /* !NDEBUG */
                                          ) {
	u32 word;
	for (;;) {
		word = atomic_read(&e1_p->p_word);
		if unlikely(P32_PDIR_E1_ISHINT(word))
			break; /* Special case: Hint */
#ifndef NDEBUG
		assertf(word & P32_PAGE_FPREPARED,
		        "Attempted to unprepare page %p...%p as part of "
		        "%p...%p, but that page wasn't marked as prepared",
		        (byte_t *)P32_PDIR_VECADDR(vec2, vec1),
		        (byte_t *)P32_PDIR_VECADDR(vec2, vec1 + 1) - 1,
		        (byte_t *)P32_PDIR_VECADDR(vec2, vec1_unprepare_start),
		        (byte_t *)P32_PDIR_VECADDR(vec2, vec1_unprepare_start + vec1_unprepare_size) - 1);
#endif /* !NDEBUG */
		if likely(atomic_cmpxch_weak(&e1_p->p_word, word, word & ~P32_PAGE_FPREPARED))
			break;
	}
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
	e2.p_word = atomic_read(&e2_p->p_word);
	assertf(e2.p_word & P32_PAGE_FPRESENT,
	        "E1-Vector %u:%u-%u (%p-%p) containing pages %p-%p is not present",
	        vec2, vec1_unprepare_start, vec1_unprepare_start + vec1_unprepare_size - 1,
	        (byte_t *)P32_PDIR_VECADDR(vec2, 0),
	        (byte_t *)P32_PDIR_VECADDR(vec2 + 1, 0) - 1,
	        (byte_t *)P32_PDIR_VECADDR(vec2, vec1_unprepare_start),
	        (byte_t *)P32_PDIR_VECADDR(vec2, vec1_unprepare_start + vec1_unprepare_size) - 1);
	assertf(!(e2.p_word & P32_PAGE_F4MIB),
	        "A 4MiB page couldn't have been prepared (only 4KiB pages can be)");

	/* Check if the 4KiB vector can be merged.
	 * NOTE: We are guarantied  that accessing the  E1-vector is OK,  because
	 *       the caller guaranties that at least  some part of the vector  is
	 *       still marked as prepared, meaning  that no other thread is  able
	 *       to fully free() the vector until we've cleared all of our marked
	 *       bits. */
	e1_p = P32_PDIR_E1_IDENTITY[vec2];
	for (vec1 = vec1_unprepare_start + 1;
	     vec1 < vec1_unprepare_start + vec1_unprepare_size; ++vec1) {
		assertf(atomic_read(&e1_p[vec1].p_word) & P32_PAGE_FPREPARED,
		        "Attempted to unprepare page %p...%p as part of "
		        "%p...%p, but that page wasn't marked as prepared",
		        (byte_t *)P32_PDIR_VECADDR(vec2, vec1),
		        (byte_t *)P32_PDIR_VECADDR(vec2, vec1 + 1) - 1,
		        (byte_t *)P32_PDIR_VECADDR(vec2, vec1_unprepare_start),
		        (byte_t *)P32_PDIR_VECADDR(vec2, vec1_unprepare_start + vec1_unprepare_size) - 1);
		p32_pagedir_unset_prepared(&e1_p[vec1], vec2, vec1, vec1_unprepare_start, vec1_unprepare_size);
	}

	/* Read  the  current prepare-version  _before_  we check  if  flattening is
	 * possible. - That way, other threads are allowed to increment the version,
	 * forcing us to check again further below. */
	old_version = atomic_read(&x86_pagedir_prepare_version);
	can_flatten = p32_pagedir_can_flatten_e1_vector(e1_p, &new_e2_word, vec1_unprepare_start);
	p32_pagedir_unset_prepared(&e1_p[vec1_unprepare_start], vec2, vec1_unprepare_start,
	                           vec1_unprepare_start, vec1_unprepare_size);
	if unlikely(can_flatten) {
		preemption_flag_t was;
		bool must_restart;
again_try_exchange_e2_word:
		must_restart = false;
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_WRITE(was);
		if unlikely(old_version != atomic_read(&x86_pagedir_prepare_version)) {
			must_restart = true;
		} else if unlikely(!atomic_cmpxch(&e2_p->p_word, e2.p_word, new_e2_word)) {
			must_restart = true;
		}
		X86_PAGEDIR_PREPARE_LOCK_RELEASE_WRITE(was);
		if unlikely(must_restart) {
			/* Check again if the vector can be flattened.
			 * Note  that  we need  a read-lock  to  to the  prepare-lock in
			 * order to prevent the vector from being freed while we do this */
			X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ_NOVER(was);

			/* Re-load the E2 control word in case it has changed. */
			e2.p_word = atomic_read(&e2_p->p_word);
			if (!(e2.p_word & P32_PAGE_FPRESENT) || (e2.p_word & P32_PAGE_F4MIB)) {
				can_flatten = false; /* Not present, or already a 4MiB mapping */
			} else {
				/* Re-load the active version number before
				 * we check if flatten is (still) possible. */
				old_version = atomic_read(&x86_pagedir_prepare_version);
				can_flatten = p32_pagedir_can_flatten_e1_vector(e1_p, &new_e2_word, 1024);
			}
			X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
			if unlikely(!can_flatten)
				return;
			goto again_try_exchange_e2_word;
		}

		/* Sync if necessary. */
		p32_pagedir_sync_flattened_e1_vector(vec2);

		/* Successfully merged the vector.
		 * At this point, all that's left is to free the vector.
		 * NOTE: No need to Shoot-down anything for this, since the new,
		 *       flattened control word has identical meaning to the old
		 *       E1-vector. */
		page_freeone_for_paging(ppageof(e2.p_word & P32_PAGE_FVECTOR));
	}
}




/* Prepare the page directory for a future map() operation.
 * The full cycle of a single mapping then looks like this:
 * >> p32_pagedir_prepare(...);
 * >> p32_pagedir_map(...);
 * >> p32_pagedir_unmap(...);
 * >> p32_pagedir_unprepare(...);
 * @return: true:  Successfully allocated structures required for creating mappings.
 * @return: false: Insufficient physical memory to prepare mappings. */
INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p32_pagedir_prepareone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	bool result;
	unsigned int vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	if unlikely((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE)
		return true;
	vec2 = P32_PDIR_VEC2INDEX(addr);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	result = p32_pagedir_prepare_impl_widen(vec2, vec1, 1);
	PG_TRACE_PREPARE_IF(result, addr, PAGESIZE);
	return result;
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unprepareone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	if unlikely((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE)
		return;
	PG_TRACE_UNPREPARE(addr, PAGESIZE);
	vec2 = P32_PDIR_VEC2INDEX(addr);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	p32_pagedir_unprepare_impl_flatten(vec2, vec1, 1);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p32_pagedir_prepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
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
		return p32_pagedir_prepareone(addr);
	vec2_min = P32_PDIR_VEC2INDEX(addr);
	vec2_max = P32_PDIR_VEC2INDEX((byte_t *)addr + num_bytes - 1);
	vec1_min = P32_PDIR_VEC1INDEX(addr);

	/* Prepare within the same 4MiB region. */
	if likely(vec2_min == vec2_max) {
		bool result;
		result = p32_pagedir_prepare_impl_widen(vec2_min,
		                                        vec1_min,
		                                        num_bytes / 4096);
		PG_TRACE_PREPARE_IF(result, addr, num_bytes);
		return result;
	}
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
	PG_TRACE_PREPARE(addr, num_bytes);
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

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unprepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
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
		p32_pagedir_unprepareone(addr);
		return;
	}
	PG_TRACE_UNPREPARE(addr, num_bytes);
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
	        (byte_t *)P32_PDIR_VECADDR(vec2, vec1),
	        (byte_t *)P32_PDIR_VECADDR(vec2, vec1) + PAGESIZE - 1);
	assertf(!(e2.p_word & P32_PAGE_F4MIB),
	        "Page %p...%p exists as a present 4MiB page #%u"
	        "Page vector #%u for page %p...%p isn't allocated",
	        (byte_t *)P32_PDIR_VECADDR(vec2, vec1),
	        (byte_t *)P32_PDIR_VECADDR(vec2, vec1) + PAGESIZE - 1,
	        (unsigned int)vec2);
	if (vec2 < P32_PDIR_VEC2INDEX(KERNELSPACE_BASE)) {
		union p32_pdir_e1 e1;
		e1 = P32_PDIR_E1_IDENTITY[vec2][vec1];
		assertf(e1.p_word & P32_PAGE_FPREPARED || P32_PDIR_E1_ISHINT(e1.p_word),
		        "Page %p...%p [vec2=%u,vec1=%u] hasn't been prepared",
		        (byte_t *)P32_PDIR_VECADDR(vec2, vec1),
		        (byte_t *)P32_PDIR_VECADDR(vec2, vec1) + PAGESIZE - 1,
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
	atomic_and(&P32_PDIR_E1_IDENTITY[vec2][vec1].p_word, e1_kept_bits_mask);
}

LOCAL NOBLOCK u32
NOTHROW(FCALL p32_pagedir_xch_e1_word)(unsigned int vec2,
                                       unsigned int vec1,
                                       u32 e1_word) {
	p32_pagedir_assert_e1_word_prepared(vec2, vec1, e1_word);
	return atomic_xch(&P32_PDIR_E1_IDENTITY[vec2][vec1].p_word, e1_word);
}

#ifdef NDEBUG
#define p32_pagedir_xch_e1_word_nochk p32_pagedir_xch_e1_word
#else /* NDEBUG */
LOCAL NOBLOCK u32
NOTHROW(FCALL p32_pagedir_xch_e1_word_nochk)(unsigned int vec2,
                                             unsigned int vec1,
                                             u32 e1_word) {
	return atomic_xch(&P32_PDIR_E1_IDENTITY[vec2][vec1].p_word, e1_word);
}
#endif /* !NDEBUG */


INTERN_CONST ATTR_PAGING_READMOSTLY u32 const p32_pageprot_table[0x40] = {
#define COMMON_PRESENT (P32_PAGE_FPREPARED | P32_PAGE_FACCESSED | P32_PAGE_FDIRTY | P32_PAGE_FPRESENT)
	[(0)]                                                                                                                               = 0,
	[(PAGEDIR_PROT_EXEC)]                                                                                                               = COMMON_PRESENT,
	[(PAGEDIR_PROT_WRITE)]                                                                                                              = COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                                          = COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_READ)]                                                                                                               = COMMON_PRESENT,
	[(PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                                                                           = COMMON_PRESENT,
	[(PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                                                                          = COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                      = COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PWT)]                                                                                                            = P32_PAGE_FPWT,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_EXEC)]                                                                                        = P32_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE)]                                                                                       = P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                   = P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ)]                                                                                        = P32_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                                                    = P32_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                                                   = P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                               = P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD)]                                                                                                            = P32_PAGE_FPCD,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_EXEC)]                                                                                        = P32_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_WRITE)]                                                                                       = P32_PAGE_FPCD | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                   = P32_PAGE_FPCD | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ)]                                                                                        = P32_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                                                    = P32_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                                                   = P32_PAGE_FPCD | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                               = P32_PAGE_FPCD | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT)]                                                                                     = P32_PAGE_FPCD | P32_PAGE_FPWT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_EXEC)]                                                                 = P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE)]                                                                = P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                            = P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ)]                                                                 = P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                             = P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                            = P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                        = P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT)]                                                                                                            = P32_PAGE_FPAT_4KIB,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_EXEC)]                                                                                        = P32_PAGE_FPAT_4KIB | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_WRITE)]                                                                                       = P32_PAGE_FPAT_4KIB | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                   = P32_PAGE_FPAT_4KIB | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_READ)]                                                                                        = P32_PAGE_FPAT_4KIB | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                                                    = P32_PAGE_FPAT_4KIB | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                                                   = P32_PAGE_FPAT_4KIB | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                               = P32_PAGE_FPAT_4KIB | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT)]                                                                                     = P32_PAGE_FPAT_4KIB | P32_PAGE_FPWT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_EXEC)]                                                                 = P32_PAGE_FPAT_4KIB | P32_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE)]                                                                = P32_PAGE_FPAT_4KIB | P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                            = P32_PAGE_FPAT_4KIB | P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ)]                                                                 = P32_PAGE_FPAT_4KIB | P32_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                             = P32_PAGE_FPAT_4KIB | P32_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                            = P32_PAGE_FPAT_4KIB | P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                        = P32_PAGE_FPAT_4KIB | P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD)]                                                                                     = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_EXEC)]                                                                 = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_WRITE)]                                                                = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                            = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ)]                                                                 = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                             = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                            = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                        = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT)]                                                              = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | P32_PAGE_FPWT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_EXEC)]                                          = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE)]                                         = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                     = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ)]                                          = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                      = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                     = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)] = P32_PAGE_FPAT_4KIB | P32_PAGE_FPCD | P32_PAGE_FPWT | COMMON_PRESENT | P32_PAGE_FWRITE,
#undef COMMON_PRESENT
};

LOCAL NOBLOCK WUNUSED u32
NOTHROW(FCALL p32_pagedir_encode_4kib)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED physaddr_t phys,
                                       pagedir_prot_t prot) {
	u32 result;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	assertf(IS_ALIGNED(phys, 4096), "phys = %" PRIpN(__SIZEOF_PHYSADDR_T__), phys);
	assertf(!(prot & ~PAGEDIR_PROT_MASK),
	        "Invalid page protection: %#.4" PRIx16, prot);
#if __SIZEOF_PHYSADDR_T__ > 4
	assertf(phys <= (physaddr_t)0xfffff000,
	        "Address cannot be mapped under p32: %" PRIpN(__SIZEOF_PHYSADDR_T__),
	        phys);
#endif /* __SIZEOF_PHYSADDR_T__ > 4 */
	result  = (u32)phys;
#if PAGEDIR_PROT_MASK == 0x3f
	result |= p32_pageprot_table[prot];
#else /* PAGEDIR_PROT_MASK == 0x3f */
	result |= p32_pageprot_table[prot & 0x3f];
#endif /* PAGEDIR_PROT_MASK != 0x3f */

	/* All kernel pages have the GLOBAL bit set, and all user pages the USER bit. */
	if ((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE) {
		result |= USED_P32_PAGE_FGLOBAL;
	} else {
		result |= P32_PAGE_FUSER;
	}
	return result;
}




/* Set a mapping hint for pages apart of the given virtual memory range.
 * Mapping hints are overwritten once a  page has been mapped, and  when
 * not specified, will default to `NULL'.
 * Their main purpose is to be accessible through atomic means, allowing
 * them to be used by the PAGE_FAULT handler, while still ensuring  that
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

/* Return the hint of the given page, or NULL if no hint has been mapped. */
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
	word = atomic_read(&P32_PDIR_E1_IDENTITY[vec2][vec1].p_word);
	if unlikely(!P32_PDIR_E1_ISHINT(word))
		return NULL;
	return (void *)(uintptr_t)(word & P32_PAGE_FHINT);
}

/* Create/delete a page-directory mapping.
 * @param: prot: A set of `PAGEDIR_PROT_*' detailing how memory should be mapped. */
INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED physaddr_t phys,
                                  pagedir_prot_t prot) {
	u32 e1_word;
	unsigned int vec2, vec1;
	PG_TRACE_MAP(addr, PAGESIZE, phys, prot);
	e1_word = p32_pagedir_encode_4kib(addr, phys, prot);
	vec2 = P32_PDIR_VEC2INDEX(addr);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	p32_pagedir_set_e1_word(vec2, vec1, e1_word);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes,
                               PAGEDIR_PAGEALIGNED physaddr_t phys,
                               pagedir_prot_t prot) {
	size_t i;
	u32 e1_word;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	PG_TRACE_MAP(addr, num_bytes, phys, prot);
	e1_word = p32_pagedir_encode_4kib(addr, phys, prot);
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
 * temporary override the  mapping of a  single, prepared  page.
 * These functions are  mainly intended for  use with `this_trampoline_page',  allowing
 * each  thread to push/pop its trampoline page, with doing so actually being an atomic
 * operation in the sense that the data is entirely thread-private, while modifications
 * do not require any kind of lock.
 * NOTE: If the page had been mapped, `pagedir_pop_mapone()' will automatically sync the page. */
INTERN NOBLOCK WUNUSED p32_pagedir_pushval_t
NOTHROW(FCALL p32_pagedir_push_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED physaddr_t phys,
                                       pagedir_prot_t prot) {
	u32 e1_word, result;
	unsigned int vec2, vec1;
	PG_TRACE_MAP(addr, PAGESIZE, phys, prot);
	e1_word = p32_pagedir_encode_4kib(addr, phys, prot);
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
	old_word = p32_pagedir_xch_e1_word_nochk(vec2, vec1, (u32)backup);
	if (old_word & P32_PAGE_FPRESENT)
		pagedir_syncone(addr); /* The old mapping was also present (explicitly refresh the page). */
}

/* Unmap pages from the given address range. (requires that the given area be prepared) */
INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unmapone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	PG_TRACE_UNMAP(addr, PAGESIZE);
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
	PG_TRACE_UNMAP(addr, num_bytes);
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
NOTHROW(FCALL p32_pagedir_denywriteone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	vec2 = P32_PDIR_VEC2INDEX(addr);
	vec1 = P32_PDIR_VEC1INDEX(addr);
	p32_pagedir_andl_e1_word(vec2, vec1, ~P32_PAGE_FWRITE);
}

INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_denywrite)(PAGEDIR_PAGEALIGNED VIRT void *addr,
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
 *       can perform the task without  needing to allocate more  memory! */
INTERN NOBLOCK void
NOTHROW(FCALL p32_pagedir_unmap_userspace)(void) {
	unsigned int vec2, free_count = 0;
	u32 free_pages[64];

	/* Map all pages before the share-segment as absent. */
	for (vec2 = 0; vec2 < P32_PDIR_VEC2INDEX(KERNELSPACE_BASE); ++vec2) {
		union p32_pdir_e2 e2;
		u32 pageptr;
again_read_word:
		e2.p_word = atomic_read(&P32_PDIR_E2_IDENTITY[vec2].p_word);
		if likely(!(e2.p_word & P32_PAGE_FPRESENT))
			continue; /* Not allocated */

		/* Delete this vector. */
		if unlikely(!atomic_cmpxch_weak(&P32_PDIR_E2_IDENTITY[vec2].p_word, e2.p_word, P32_PAGE_ABSENT))
			goto again_read_word;
		if unlikely(e2.p_word & P32_PAGE_F4MIB)
			continue; /* 4MiB page. */
		pageptr = e2.p_word >> P32_PAGE_SHIFT;
		if unlikely(free_count >= lengthof(free_pages)) {
			/* Must  sync  memory  before  we  can  actually  delete   pages.
			 * Otherwise, other CPUs  may still be  using the mappings  after
			 * they've  already been re-designated as general-purpose RAM, at
			 * which point they'd start reading garbage, or corrupt pointers. */
			pagedir_syncall_smp();
			page_freeone_for_paging((physpage_t)pageptr);
			do {
				--free_count;
				page_freeone_for_paging((physpage_t)free_pages[free_count]);
			} while (free_count);
		} else {
			free_pages[free_count++] = (u32)pageptr;
		}
	}

	/* Free any remaining pages. */
	if (free_count) {
		pagedir_syncall_smp();
		do {
			--free_count;
			page_freeone_for_paging((physpage_t)free_pages[free_count]);
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
		e2.p_word = atomic_read(&P32_PDIR_E2_IDENTITY[vec2].p_word);
		if likely(!(e2.p_word & P32_PAGE_FPRESENT))
			continue; /* Not allocated */

		/* Delete this vector. */
		if unlikely(!atomic_cmpxch_weak(&P32_PDIR_E2_IDENTITY[vec2].p_word, e2.p_word, P32_PAGE_ABSENT))
			goto again_read_word;
		if unlikely(e2.p_word & P32_PAGE_F4MIB)
			continue; /* 4MiB page. */
		pageptr = e2.p_word >> P32_PAGE_SHIFT;
		page_freeone_for_paging((physpage_t)pageptr);
	}
}

/* Translate a virtual address into its physical counterpart. */
INTERN NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(1) physaddr_t
NOTHROW(FCALL p32_pagedir_translate)(VIRT void const *addr) {
	u32 word;
	unsigned int vec2, vec1;
	vec2 = P32_PDIR_VEC2INDEX(addr);
	word = P32_PDIR_E2_IDENTITY[vec2].p_word;
	assertf(word & P32_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	if unlikely(word & P32_PAGE_F4MIB)
		return (physaddr_t)((word & P32_PAGE_FADDR_4MIB) | P32_PDIR_PAGEINDEX_4MIB(addr));
	vec1 = P32_PDIR_VEC1INDEX(addr);
	word = P32_PDIR_E1_IDENTITY[vec2][vec1].p_word;
	assertf(word & P32_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	return (physaddr_t)((word & P32_PAGE_FADDR_4KIB) | P32_PDIR_PAGEINDEX_4KIB(addr));
}

/* Check if the given page is mapped. */
INTERN NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(1) bool
NOTHROW(FCALL p32_pagedir_ismapped)(VIRT void const *addr) {
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

INTERN NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(1) bool
NOTHROW(FCALL p32_pagedir_isuseraccessible)(VIRT void const *addr) {
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
		word = atomic_read(&P32_PDIR_E1_IDENTITY[vec2][vec1].p_word);
		if unlikely((word & (P32_PAGE_FPRESENT | P32_PAGE_FDIRTY)) ==
		            /*   */ (P32_PAGE_FPRESENT | P32_PAGE_FDIRTY))
			return;
	} while (!atomic_cmpxch_weak(&P32_PDIR_E1_IDENTITY[vec2][vec1].p_word,
	                             word, word & ~P32_PAGE_FDIRTY));
}


#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

/* NOTE: This function must do its own tracing of continuous page ranges.
 *       The caller is may not necessary ensure that the function is only
 *       called once for a single, continuous range.
 * @param: word: The page directory starting control word.
 *               When `P32_PAGE_FPRESENT' is set, refers to a mapped page range
 *               When `P32_PAGE_FISAHINT' is set, refers to a mapped page range */
typedef void (KCALL *p32_enumfun_t)(void *arg, void *start, size_t num_bytes, u32 word);

#define P32_PAGE_CASCADING \
	(P32_PAGE_FPRESENT | P32_PAGE_FWRITE | P32_PAGE_FUSER)

#define P32_PAGE_FPAT P32_PAGE_FPAT_4KIB
/* Convert an En | n >= 2 word into an E1 word */
PRIVATE ATTR_DBGTEXT ATTR_CONST WUNUSED u32
NOTHROW(KCALL p32_convert_en_to_e1)(u32 word) {
	assert(word & P32_PAGE_FPRESENT);
	assert(word & P32_PAGE_F4MIB);
	word &= ~P32_PAGE_F4MIB;
#if P32_PAGE_FPAT_4KIB != P32_PAGE_FPAT_4MIB
	if (word & P32_PAGE_FPAT_4MIB) {
		word &= ~P32_PAGE_FPAT_4MIB;
		word |= P32_PAGE_FPAT_4KIB;
	}
#endif /* P32_PAGE_FPAT_4KIB != P32_PAGE_FPAT_4MIB */
	return word;
}

#define P32_PDIR_E1_ISUSED(e1_word) (((e1_word) & (P32_PAGE_FPRESENT | P32_PAGE_FISAHINT | P32_PAGE_FPREPARED)) != 0)
PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
p32_enum_e1(p32_enumfun_t func, void *arg,
            unsigned int vec2, u32 mask) {
	unsigned int vec1, laststart = 0;
	union p32_pdir_e1 *e1 = P32_PDIR_E1_IDENTITY[vec2];
	union p32_pdir_e1 lastword = e1[0];
	lastword.p_word &= mask;
	for (vec1 = 1; vec1 < 1024; ++vec1) {
		union p32_pdir_e1 word;
		word = e1[vec1];
		word.p_word &= mask;
		if (P32_PDIR_E1_IS1KIB(word.p_4kib.d_present)) {
			union p32_pdir_e1 expected_word;
			expected_word = lastword;
			expected_word.p_word += (u32)(vec1 - laststart) * 4096;
			if (word.p_word != expected_word.p_word) {
docall:
				if (P32_PDIR_E1_ISUSED(lastword.p_word)) {
					(*func)(arg, P32_PDIR_VECADDR(vec2, laststart),
					        (size_t)(vec1 - laststart) * 4096,
					        lastword.p_word);
				}
				laststart = vec1;
				lastword  = word;
			}
#if 0
		} else if (P32_PDIR_E1_ISHINT(word.p_word)) {
			if (word.p_word != lastword.p_word)
				goto docall;
#endif
		} else {
			if (word.p_word != lastword.p_word)
				goto docall;
		}
	}
	if (P32_PDIR_E1_ISUSED(lastword.p_word)) {
		(*func)(arg, P32_PDIR_VECADDR(vec2, laststart),
		        (size_t)(1024 - laststart) * 4096,
		        lastword.p_word);
	}
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
p32_enum_e2(p32_enumfun_t func, void *arg, unsigned int vec2_max) {
	unsigned int vec2 = 1, laststart = 0;
	union p32_pdir_e2 *e2 = P32_PDIR_E2_IDENTITY;
	union p32_pdir_e2 word, lastword = e2[0];
	if (P32_PDIR_E2_ISVEC1(lastword.p_word)) {
		word = lastword;
		vec2 = 0;
		goto do_enum_e1;
	}
	for (; vec2 < vec2_max; ++vec2) {
		word = e2[vec2];
		if (P32_PDIR_E2_ISVEC1(word.p_word)) {
			if (P32_PDIR_E2_IS4MIB(lastword.p_word)) {
				(*func)(arg, P32_PDIR_VECADDR(laststart, 0),
				        (size_t)(vec2 - laststart) * 4096 * 1024,
				        p32_convert_en_to_e1(lastword.p_word & ~(u32)0x3ff000));
			}
do_enum_e1:
			p32_enum_e1(func, arg, vec2,
			            word.p_word | ~(u32)P32_PAGE_CASCADING);
			laststart = vec2;
			lastword  = word;
		} else if (P32_PDIR_E2_IS4MIB(word.p_word)) {
			union p32_pdir_e2 expected_word;
			expected_word = lastword;
			expected_word.p_word += (u32)(vec2 - laststart) * 4096 * 1024;
			if (word.p_word != expected_word.p_word) {
docall:
				if (P32_PDIR_E2_IS4MIB(lastword.p_word)) {
					(*func)(arg, P32_PDIR_VECADDR(laststart, 0),
					        (size_t)(vec2 - laststart) * 4096 * 1024,
					        p32_convert_en_to_e1(lastword.p_word & ~(u32)0x3ff000));
				}
				laststart = vec2;
				lastword  = word;
			}
		} else {
			if (word.p_word != lastword.p_word)
				goto docall;
		}
	}
	if (P32_PDIR_E2_IS4MIB(lastword.p_word)) {
		(*func)(arg, P32_PDIR_VECADDR(laststart, 0),
		        (size_t)(1024 - laststart) * 4096 * 1024,
		        p32_convert_en_to_e1(lastword.p_word & ~(u32)0x3ff000));
	}
}

struct p32_enumdat {
	void  *ed_prevstart;
	size_t ed_prevsize;
	u32    ed_prevword;
	u32    ed_mask;
	size_t ed_identcnt;
	bool   ed_skipident;
};

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
p32_printident(struct p32_enumdat *__restrict data) {
	dbg_printf(DBGSTR(AC_WHITE("%p") "-" AC_WHITE("%p") ": " AC_WHITE("%" PRIuSIZ) " identity mappings\n"),
	           (byte_t *)P32_MMAN_KERNEL_PDIR_IDENTITY_BASE,
	           (byte_t *)P32_MMAN_KERNEL_PDIR_IDENTITY_BASE + P32_MMAN_KERNEL_PDIR_IDENTITY_SIZE - 1,
	           data->ed_identcnt);
	data->ed_identcnt = 0;
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
p32_doenum(struct p32_enumdat *__restrict data,
           void *start, size_t num_bytes, u32 word, u32 mask) {
	assert((word & P32_PAGE_FPRESENT) || (word & P32_PAGE_FISAHINT));
	if (data->ed_identcnt) {
		p32_printident(data);
		return;
	}
	dbg_printf(DBGSTR(AC_WHITE("%p") "-" AC_WHITE("%p")),
	           start, (byte_t *)start + num_bytes - 1);
	if (word & P32_PAGE_FPRESENT) {
		size_t indent;
		dbg_printf(DBGSTR(": " AC_WHITE("%p") "+" AC_FG_WHITE),
		           word & P32_PAGE_FADDR_4KIB);
		if ((num_bytes >= ((u32)1024 * 1024 * 1024)) &&
		    (num_bytes % ((u32)1024 * 1024 * 1024)) == 0) {
			indent = dbg_printf(DBGSTR("%" PRIuSIZ AC_DEFATTR "GiB"),
			                    (size_t)(num_bytes / ((u32)1024 * 1024 * 1024)));
		} else if ((num_bytes >= ((u32)1024 * 1024)) &&
		           (num_bytes % ((u32)1024 * 1024)) == 0) {
			indent = dbg_printf(DBGSTR("%" PRIuSIZ AC_DEFATTR "MiB"),
			                    (size_t)(num_bytes / ((u32)1024 * 1024)));
		} else if ((num_bytes >= ((u32)1024)) &&
		           (num_bytes % ((u32)1024)) == 0) {
			indent = dbg_printf(DBGSTR("%" PRIuSIZ AC_DEFATTR "KiB"),
			                    (size_t)(num_bytes / ((u32)1024)));
		} else {
			indent = dbg_printf(DBGSTR("%" PRIuSIZ AC_DEFATTR "B"),
			                    num_bytes);
		}
#define COMMON_INDENT (9 + 3)
		if (indent < COMMON_INDENT)
			dbg_printf(DBGSTR("%*s"), COMMON_INDENT - indent, "");
#undef COMMON_INDENT
		dbg_print(DBGSTR(" ["));
		{
			PRIVATE ATTR_DBGRODATA struct {
				u32  mask;
				char ch;
			} const masks[] = {
				{ P32_PAGE_FWRITE, 'w' },
				{ P32_PAGE_FUSER, 'u' },
				{ P32_PAGE_FGLOBAL, 'g' },
				{ P32_PAGE_FACCESSED, 'a' },
				{ P32_PAGE_FDIRTY, 'd' },
				{ P32_PAGE_FPREPARED, 'p' },
			};
			dbg_color_t oldcolor;
			unsigned int i;
			oldcolor = dbg_getcolor();
			for (i = 0; i < lengthof(masks); ++i) {
				if (mask & masks[i].mask) {
					dbg_setcolor(oldcolor);
					if (word & masks[i].mask)
						dbg_setfgcolor(ANSITTY_CL_WHITE);
					dbg_putc(word & masks[i].mask ? masks[i].ch : '-');
				}
			}
			dbg_setcolor(oldcolor);
		}
#undef PUTMASK
		if (mask & (P32_PAGE_FPAT | P32_PAGE_FPWT | P32_PAGE_FPCD)) {
			u8 state = 0;
			if (word & P32_PAGE_FPWT)
				state |= 1;
			if (word & P32_PAGE_FPCD)
				state |= 2;
			if (word & P32_PAGE_FPAT)
				state |= 4;
			dbg_printf(DBGSTR("][" AC_FG_WHITE "%x"), (unsigned int)state);
		}
		dbg_print(DBGSTR(AC_DEFATTR "]\n"));
	} else {
		dbg_printf(DBGSTR(": hint@" AC_WHITE("%p") "\n"),
		           (void *)(word & P32_PAGE_FHINT));
	}
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
p32_enumfun(void *arg, void *start, size_t num_bytes, u32 word) {
	struct p32_enumdat *data;
	data = (struct p32_enumdat *)arg;
	word &= data->ed_mask; /* Mask relevant bits. */
	if (!((word & P32_PAGE_FPRESENT) || (word & P32_PAGE_FISAHINT)))
		return;
	if ((byte_t *)data->ed_prevstart + data->ed_prevsize == start) {
		u32 expected_word;
		if (!data->ed_prevsize) {
			expected_word = 0;
		} else if (word & P32_PAGE_FPRESENT) {
			expected_word = data->ed_prevword + data->ed_prevsize;
		} else {
			assert(word & P32_PAGE_FISAHINT);
			expected_word = data->ed_prevword;
		}
		if (expected_word == word) {
			data->ed_prevsize += num_bytes;
			return;
		}
	}
	if (data->ed_prevsize) {
		if ((byte_t *)data->ed_prevstart >= (byte_t *)P32_MMAN_KERNEL_PDIR_IDENTITY_BASE) {
			++data->ed_identcnt;
			goto done_print; /* Skip entries within the identity mapping. */
		}
		p32_doenum(data, data->ed_prevstart, data->ed_prevsize, data->ed_prevword, data->ed_mask);
	}
done_print:
	data->ed_prevstart   = start;
	data->ed_prevsize    = num_bytes;
	data->ed_prevword    = word;
}

PRIVATE ATTR_DBGTEXT void KCALL
p32_do_lspd(unsigned int vec2_max) {
	struct p32_enumdat data;
	data.ed_prevstart = 0;
	data.ed_prevsize  = 0;
	data.ed_prevword  = 0;
	data.ed_skipident = true;
	data.ed_identcnt  = 0;
	data.ed_mask = P32_PAGE_FVECTOR | P32_PAGE_FPRESENT | P32_PAGE_FWRITE | P32_PAGE_FUSER |
	               P32_PAGE_FPWT | P32_PAGE_FPCD | P32_PAGE_FPAT | P32_PAGE_FPREPARED |
	               P32_PAGE_FGLOBAL | P32_PAGE_FACCESSED | P32_PAGE_FDIRTY;
	p32_enum_e2(&p32_enumfun, &data, vec2_max);
	if (data.ed_prevsize)
		p32_doenum(&data, data.ed_prevstart, data.ed_prevsize, data.ed_prevword, data.ed_mask);
}

INTERN ATTR_DBGTEXT void FCALL p32_dbg_lspd(pagedir_phys_t pdir) {
	if (pdir == pagedir_kernel_phys) {
		p32_do_lspd(1024);
		return;
	}
	PAGEDIR_P_BEGINUSE(pdir) {
		p32_do_lspd(768);
	}
	PAGEDIR_P_ENDUSE(pdir);
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


DECL_END

#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_P32_C_INL */
