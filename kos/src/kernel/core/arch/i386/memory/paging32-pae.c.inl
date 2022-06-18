/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_PAE_C_INL
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_PAE_C_INL 1
#define __OMIT_PAGING_CONSTANT_P_WRAPPERS
#define __WANT_MMAN_EXCLUDE_PAGEDIR
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/arch/paging32-pae.h>
#include <kernel/except.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/phys.h>
#include <kernel/mman/sync.h>
#include <kernel/paging.h>
#include <kernel/x86/cpuid.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sched/preemption.h>

#include <asm/cpu-cpuid.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifndef CONFIG_NO_PAGING_PAE

#include "paging.h"
#include "paging32-com.h"


DECL_BEGIN

/* Return the physical page ID of a given physical address. */
#define ppageof(paddr) (physpage_t)((paddr) / PAGESIZE)

#if defined(__cplusplus) && 0
extern "C++" {
template<class T, size_t len> using my_array_t = T[len];
}
typedef int TYPE_X[2];
typedef int TYPE_Y[2][3]; /* This is array<array<int, 3>, 2> */
typedef TYPE_X TYPE_Z[3]; /* This is array<array<int, 2>, 3> */
static_assert(__builtin_types_compatible_p(TYPE_X, my_array_t<int, 2>));
static_assert(__builtin_types_compatible_p(TYPE_Y, my_array_t<my_array_t<int, 3>, 2>));
static_assert(__builtin_types_compatible_p(TYPE_Z, my_array_t<my_array_t<int, 2>, 3>));
#endif /* __cplusplus */

/* I always find recursive array declarations in C to be extremely confusing,
 * so  to make sure I didn't screw up the array-length ordering of the E{1-3}
 * descriptor types, assert that they offsets behave correctly in relation to
 * their indices. */
struct pae_pdir_e1_identity_t_struct { pae_pdir_e1_identity_t x; };
struct pae_pdir_e2_identity_t_struct { pae_pdir_e2_identity_t x; };
struct pae_pdir_e3_identity_t_struct { pae_pdir_e3_identity_t x; };
static_assert(offsetof(struct pae_pdir_e1_identity_t_struct, x[1][0][0]) == 512 * 512 * 8);
static_assert(offsetof(struct pae_pdir_e2_identity_t_struct, x[1][0])    == 512 * 8);
static_assert(offsetof(struct pae_pdir_e3_identity_t_struct, x[1])       == 8);


#ifndef __x86_64__
/* We can't use the the normal ATOMIC_READ(), since the code that GCC (rightfully) generates
 * for atomically reading a 64-bit  value makes use of the  FPU, which is something that  we
 * can't have, as the paging system can't possibly make use of the FPU, as this would create
 * a dependency on the heap sub-system (which could cause E_BADALLOC), as well as a loop:
 *
 *    PAGING ─> FPU ─> MALLOC ─> HEAP ─> MMAP
 *       ^                                │
 *       │                                │
 *       └────────────────────────────────┘
 *
 * So  because of all of this, we are  left having to implement an atomic read by
 * reading 64-bit words in 2 steps (hi/lo part), which may yield corrupted values
 * if another thread/cpu did a reverse write at the same time.
 * For this reason, we need to use the cmpxchg8b instruction which we're already
 * depending on regardless in order to perform the read.
 */
#if 1 /* Since we need to use a cmpxchg8b anyways, it's better to \
       * simply use it to figure out the correct value from the get-go */
#define ATOMIC_READ64(word)                              \
	XBLOCK({                                             \
		u64 _res;                                        \
		_res = ATOMIC_CMPXCH_VAL(*(u64 *)&(word), 0, 0); \
		XRETURN _res;                                    \
	})
#else
#define ATOMIC_READ64(word)                              \
	XBLOCK({                                             \
		u64 _res;                                        \
		do {                                             \
			COMPILER_READ_BARRIER();                     \
			_res = (word);                               \
			COMPILER_READ_BARRIER();                     \
		} while (!ATOMIC_CMPXCH_WEAK(word, _res, _res)); \
		XRETURN _res;                                    \
	})
#endif
#define ATOMIC_READ64_ALLOW_CORRUPT(word) \
	XBLOCK({                              \
		u64 _res;                         \
		COMPILER_READ_BARRIER();          \
		_res = (word);                    \
		COMPILER_READ_BARRIER();          \
		XRETURN _res;                     \
	})
#endif /* !__x86_64__ */


#ifndef ATOMIC_READ64
#define ATOMIC_READ64(word) ATOMIC_READ(word)
#endif /* !ATOMIC_READ64 */

#ifndef ATOMIC_READ64_ALLOW_CORRUPT
#define ATOMIC_READ64_ALLOW_CORRUPT(word) ATOMIC_READ64(word)
#endif /* !ATOMIC_READ64_ALLOW_CORRUPT */


static_assert(sizeof(struct pae_pdir) == PAE_PDIR_SIZE);
static_assert(sizeof(struct pae_pdir) == 32);
static_assert(sizeof(union pae_pdir_e3) == 8);
static_assert(sizeof(union pae_pdir_e2) == 8);
static_assert(sizeof(union pae_pdir_e1) == 8);
static_assert(PAE_PDIR_E1_IDENTITY_BASE == PAE_MMAN_KERNEL_PDIR_IDENTITY_BASE);



/* Initialize the given page directory.
 * The caller is required to allocate the page directory
 * controller itself, which  must be  aligned and  sized
 * according to `PAGEDIR_ALIGN' and `PAGEDIR_SIZE'. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL pae_pagedir_tryinit)(VIRT struct pae_pdir *__restrict self) {
	u64 e3[4];
	/* Assert constants that are used below. */
	static_assert(PAE_PDIR_VEC3INDEX(PAE_MMAN_KERNEL_PDIR_IDENTITY_BASE) == 3);
	static_assert(PAE_PDIR_VEC2INDEX(PAE_MMAN_KERNEL_PDIR_IDENTITY_BASE) == 508);
	static_assert(PAE_PDIR_VEC1INDEX(PAE_MMAN_KERNEL_PDIR_IDENTITY_BASE) == 0);
	assert(IS_ALIGNED((uintptr_t)self, PAGESIZE));

	e3[0] = (u64)page_mallocone_for_paging();
	if unlikely((physpage_t)e3[0] == PHYSPAGE_INVALID)
		goto err_0;
	e3[1] = (u64)page_mallocone_for_paging();
	if unlikely((physpage_t)e3[1] == PHYSPAGE_INVALID)
		goto err_1;
	e3[2] = (u64)page_mallocone_for_paging();
	if unlikely((physpage_t)e3[2] == PHYSPAGE_INVALID)
		goto err_2;
	e3[3] = (u64)page_mallocone_for_paging();
	if unlikely((physpage_t)e3[3] == PHYSPAGE_INVALID)
		goto err_3;

	/* Now to initialize our pre-allocated level#3 vectors.
	 * For this purpose, we must zero-initialize e3[0...2] and e3[3] like this:
	 * >> e3[3].p_e2[0...507] = KERNEL_SHARE; // Kernel share:     0xc0000000 ... 0xff7fffff
	 * >> e3[3].p_e2[508]     = e3[0];        // Identity mapping: 0xff800000 ... 0xff9fffff
	 * >> e3[3].p_e2[509]     = e3[1];        // Identity mapping: 0xffa00000 ... 0xff8fffff
	 * >> e3[3].p_e2[510]     = e3[2];        // Identity mapping: 0xffc00000 ... 0xffdfffff
	 * >> e3[3].p_e2[511]     = e3[3];        // Identity mapping: 0xffe00000 ... 0xffffffff
	 */
	e3[0] = (u64)physpage2addr((physpage_t)e3[0]);
	e3[1] = (u64)physpage2addr((physpage_t)e3[1]);
	e3[2] = (u64)physpage2addr((physpage_t)e3[2]);
	e3[3] = (u64)physpage2addr((physpage_t)e3[3]);
	if (!page_iszero((physpage_t)e3[0]))
		memsetphyspage((physaddr_t)e3[0], 0);
	if (!page_iszero((physpage_t)e3[1]))
		memsetphyspage((physaddr_t)e3[1], 0);
	if (!page_iszero((physpage_t)e3[2]))
		memsetphyspage((physaddr_t)e3[2], 0);

	/* Kernel share (copy from our own page directory) */
	copytophys_onepage((physaddr_t)e3[3], PAE_PDIR_E2_IDENTITY[3], 508 * 8);
	self->p_e3[0].p_word = e3[0] | PAE_PAGE_FPRESENT;
	self->p_e3[1].p_word = e3[1] | PAE_PAGE_FPRESENT;
	self->p_e3[2].p_word = e3[2] | PAE_PAGE_FPRESENT;
	self->p_e3[3].p_word = e3[3] | PAE_PAGE_FPRESENT;
	e3[0] |= PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	e3[1] |= PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	e3[2] |= PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	e3[3] |= PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;

	/* Identity mapping */
	copytophys_onepage((physaddr_t)(e3[3] & PAE_PAGE_FVECTOR) +
	                   508 * 8,
	                   e3,
	                   4 * 8);
	return true;
err_3:
	page_ccfree_for_paging((physpage_t)e3[2], 1);
err_2:
	page_ccfree_for_paging((physpage_t)e3[1], 1);
err_1:
	page_ccfree_for_paging((physpage_t)e3[0], 1);
err_0:
	return false;
}


/* Initialize the given page directory.
 * The caller is required to allocate the page directory
 * controller itself, which  must be  aligned and  sized
 * according to `PAGEDIR_ALIGN' and `PAGEDIR_SIZE'. */
INTERN NONNULL((1)) void FCALL
pae_pagedir_init(VIRT struct pae_pdir *__restrict self)
		THROWS(E_BADALLOC) {
	if unlikely(!pae_pagedir_tryinit(self))
		THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 4 * PAGESIZE);
}




/* Finalize a given page directory. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pae_pagedir_fini)(VIRT struct pae_pdir *__restrict self,
                                PHYS struct pae_pdir *phys_self) {
	unsigned int vec3;
	preemption_flag_t was;
	PHYS pagedir_t *old_pagedir;
	assert(IS_ALIGNED((uintptr_t)self, PAGESIZE));
	assert(IS_ALIGNED((uintptr_t)phys_self, PAGESIZE));
	preemption_pushoff(&was);
	old_pagedir = pagedir_get();

	/* Temporarily  switch  to  the  page-directory  to-be  freed,  so  we
	 * can make use of its identity-mapping in order to free its contents.
	 * The  other possibility  would be  to use  the slow `copyfromphys()'
	 * function to dereference its memory contents. */
	pagedir_set((pagedir_phys_t)phys_self);

	/* NOTE: Only iterate 0, 1 and 2 here (entry #3 contains) */
	for (vec3 = 0; vec3 < 3; ++vec3) {
		union pae_pdir_e3 e3;
		unsigned int vec2;
		e3 = PAE_PDIR_E3_IDENTITY[vec3];
		assert(e3.p_vec2.v_present);
		for (vec2 = 0; vec2 < 512; ++vec2) {
			union pae_pdir_e2 e2;
			e2 = PAE_PDIR_E2_IDENTITY[vec3][vec2];
			/* Free allocated E1-vectors from E2-entries. */
			if unlikely(PAE_PDIR_E2_ISVEC1(e2.p_word))
				page_freeone_for_paging(ppageof(e2.p_word & PAE_PAGE_FVECTOR));
		}
	}
	pagedir_set(old_pagedir);
	preemption_pop(&was);

	/* Free the always-allocated E2-vectors */
	for (vec3 = 0; vec3 < 4; ++vec3) {
		assert(self->p_e3[vec3].p_vec2.v_present);
		page_freeone_for_paging(ppageof(self->p_e3[vec3].p_word & PAE_PAGE_FVECTOR));
	}
}




LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pae_pagedir_set_prepared)(union pae_pdir_e1 *__restrict e1_p) {
	u64 word;
	for (;;) {
		/* Corrupt is OK, since ISHINT() only depends on the low 32 bits. */
		word = ATOMIC_READ64_ALLOW_CORRUPT(e1_p->p_word);
		if unlikely(PAE_PDIR_E1_ISHINT(word))
			break; /* Special case: Hint */
		if likely(ATOMIC_CMPXCH_WEAK(e1_p->p_word, word, word | PAE_PAGE_FPREPARED))
			break;
	}
}


/* Try  to  widen a  2MiB  mapping to  a  512*4KiB vector  of  linear memory
 * Alternatively, if  the specified  E1-vector is  absent, pre-allocate  it.
 * Additionally, set the `PAE_PAGE_FPREPARED' bit for all E1 vector elements
 * within   the    range    of    `vec1_prepare_start...+=vec1_prepare_size'
 * Note that `vec1_prepare_size' must be non-zero!
 * @return: true:  Success
 * @return: false: Failed to allocate physical memory */
PRIVATE NOBLOCK WUNUSED bool
NOTHROW(FCALL pae_pagedir_prepare_impl_widen)(unsigned int vec3,
                                              unsigned int vec2,
                                              unsigned int vec1_prepare_start,
                                              unsigned int vec1_prepare_size) {
	union pae_pdir_e2 e2, *e2_p;
	union pae_pdir_e1 e1, *e1_p;
	physpage_t new_e1_vector;
	u64 new_e2_word;
	unsigned int vec1;
	uintptr_t backup;
	assert(vec3 < 4);
	assert(vec2 < 512);
	assert(vec1_prepare_start < 512);
	assert(vec1_prepare_size != 0);
	assert(vec1_prepare_start + vec1_prepare_size > vec1_prepare_start);
	assert(vec1_prepare_start + vec1_prepare_size <= 512);
	assert(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT);
	assertf(vec3 < PAE_PDIR_VEC3INDEX(KERNELSPACE_BASE),
	        "The caller must ensure that no kernel-space addresses get here");
	e2_p = &PAE_PDIR_E2_IDENTITY[vec3][vec2];
again:
	e2.p_word = ATOMIC_READ64(e2_p->p_word);
	if (!e2.p_vec1.v_present) {
		/* Not present */
		new_e1_vector = page_mallocone_for_paging();
		if unlikely(new_e1_vector == PHYSPAGE_INVALID)
			return false;

		/* Initialize the inner vector.
		 * We can safely make use of our trampoline, since kernel-space is always prepared. */
		e1_p = (union pae_pdir_e1 *)THIS_TRAMPOLINE;
		backup = pae_pagedir_push_mapone(e1_p, (physaddr_t)((u64)new_e1_vector * 4096),
		                                 PAGEDIR_PROT_WRITE);
		pagedir_syncone(e1_p);
		COMPILER_WRITE_BARRIER();

		/* If the 2MiB entry was marked as prepared, always mark every entry
		 * within the E1-vector as prepared. */
		if (vec1_prepare_size == 512 || (e2.p_word & PAE_PAGE_FPREPARED)) {
			assert(vec1_prepare_size == 512 ? vec1_prepare_start == 0 : true);
			memsetq(e1_p, PAE_PAGE_FPREPARED, 512);
		} else {
			memsetq(&e1_p[0], PAE_PAGE_ABSENT, vec1_prepare_start);
			memsetq(&e1_p[vec1_prepare_start], PAE_PAGE_FPREPARED, vec1_prepare_size);
			memsetq(&e1_p[vec1_prepare_start + vec1_prepare_size], PAE_PAGE_ABSENT,
			        512 - (vec1_prepare_start + vec1_prepare_size));
		}
		COMPILER_WRITE_BARRIER();
		pae_pagedir_pop_mapone(e1_p, backup);

		/* Map the new vector. */
		new_e2_word = ((u64)new_e1_vector * 4096) |
		              PAE_PAGE_FPRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FACCESSED;
#if 0 /* This is always the case: Kernel-space always has all vectors allocated. */
		if (vec3 < PAE_PDIR_VEC3INDEX(KERNELSPACE_BASE))
#endif
		{
			/* Allow user-space access of stuff that will eventually mapped by this page. */
			new_e2_word |= PAE_PAGE_FUSER;
		}
atomic_set_new_e2_word_or_free_new_e1_vector:
		if unlikely(!ATOMIC_CMPXCH(e2_p->p_word, e2.p_word, new_e2_word)) {
			page_freeone_for_paging(new_e1_vector);
			goto again;
		}
	} else if (e2.p_2mib.d_2mib_1) {
		/* Convert a 2MiB mapping to 512*4KiB pages
		 * Because the mapping may be getting used _right_ _now_, we have
		 * to be careful about how  we go about initializing the  vector.
		 * Because  the process has to be atomic, we use our thread-local
		 * temporary mapping trampoline to  temporarily map the new  page
		 * for  initialization  (Because   the  trampoline  always   uses
		 * `PAE_PAGE_FNOFLATTEN'  when  mapping, it  is  always prepared) */
		new_e1_vector = page_mallocone_for_paging();
		if unlikely(new_e1_vector == PHYSPAGE_INVALID)
			return false;
		e1.p_word = e2.p_word & ~(PAE_PAGE_F2MIB | PAE_PAGE_FPAT_2MIB);
		if (e2.p_word & PAE_PAGE_FPAT_2MIB)
			e1.p_word |= PAE_PAGE_FPAT_4KIB;
		e1_p   = (union pae_pdir_e1 *)THIS_TRAMPOLINE;
		backup = pae_pagedir_push_mapone(e1_p, (physaddr_t)((u64)new_e1_vector * 4096),
		                                 PAGEDIR_PROT_WRITE);
		pagedir_syncone(e1_p);
		COMPILER_WRITE_BARRIER();
		if (vec1_prepare_size == 512) {
			assert(vec1_prepare_start == 0);
			e1.p_word |= PAE_PAGE_FPREPARED;
			for (vec1 = 0; vec1 < 512; ++vec1) {
				e1_p[vec1] = e1;
				e1.p_word += 4096;
			}
		} else {
			for (vec1 = 0; vec1 < 512; ++vec1) {
				e1_p[vec1] = e1;
				e1.p_word += 4096;
			}
			/* Mark specific pages as prepared */
			for (vec1 = vec1_prepare_start;
			     vec1 < vec1_prepare_start + vec1_prepare_size; ++vec1)
				e1_p[vec1].p_word |= PAE_PAGE_FPREPARED;
		}
		COMPILER_WRITE_BARRIER();
		pae_pagedir_pop_mapone(e1_p, backup);
		new_e2_word  = (u64)new_e1_vector * 4096;
		new_e2_word |= PAE_PAGE_FPRESENT | PAE_PAGE_FWRITE;
		new_e2_word |= e2.p_word & (PAE_PAGE_FUSER | PAE_PAGE_FPWT |
		                            PAE_PAGE_FPCD | PAE_PAGE_FACCESSED |
		                            PAE_PAGE_FGLOBAL);

		/* Make sure that the vector was allocated and is active */
		goto atomic_set_new_e2_word_or_free_new_e1_vector;
	} else {
		/* Already a fully allocated vector (nothing to do here) */
		preemption_flag_t was;
		assert(PAE_PDIR_E2_ISVEC1(e2.p_word));
		e1_p = &PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1_prepare_start];

		/* The first page needs to be marked under special conditions. */
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was);

		/* With a prepare-first token held, check if our e2 control work is still correct.
		 * If some other thread flattened the vector  in the mean time, that control  word
		 * will have changed. */
		COMPILER_BARRIER();
		if unlikely(e2.p_word != ATOMIC_READ64(e2_p->p_word)) {
			X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
			goto again;
		}
		pae_pagedir_set_prepared(e1_p);
		COMPILER_BARRIER();
		X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);

		/* Mark all of the other pages. */
		for (vec1 = 1;
		     vec1 < vec1_prepare_size; ++vec1)
			pae_pagedir_set_prepared(&e1_p[vec1]);
		COMPILER_WRITE_BARRIER();
	}
	return true;
}



/* Called after  an E1-vector  was flattened  into an  E2-entry
 * that now resides at `PAE_PDIR_E2_IDENTITY[vec4][vec3][vec2]' */
PRIVATE NOBLOCK void
NOTHROW(FCALL pae_pagedir_sync_flattened_e1_vector)(unsigned int vec3,
                                                    unsigned int vec2) {
	/* Even  though the in-memory mapping of `PAE_PDIR_VECADDR(vec4, vec3, vec2, 0..511)'
	 * didn't change, due to being flattened, the contents of our page directory identity
	 * mapping _have_ changed:
	 *     UNMAP(PAE_PDIR_E1_IDENTITY[vec3][vec2][0..511])  (This is exactly 1 page)
	 */
	void *sync_pageaddr;
	sync_pageaddr = PAE_PDIR_E1_IDENTITY[vec3][vec2];
	if (vec3 >= PAE_PDIR_VEC3INDEX(KERNELSPACE_BASE)) {
		/* Sync as part of the kernel MMan */
		mman_supersyncone(sync_pageaddr);
	} else {
		/* Sync as part of the current page directory. */
		pagedir_syncone_smp(sync_pageaddr);
	}
}



PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(KCALL pae_pagedir_can_flatten_e1_vector)(union pae_pdir_e1 const e1_p[512],
                                                 u64 *__restrict new_e2_word,
                                                 unsigned int still_prepared_vec2) {
	unsigned int vec1;
	union pae_pdir_e1 e1;
	e1.p_word = ATOMIC_READ64(e1_p[0].p_word);
	if (still_prepared_vec2 == 0) {
		assert(e1.p_word & PAE_PAGE_FPREPARED || PAE_PDIR_E1_ISHINT(e1.p_word));
		if (!PAE_PDIR_E1_ISHINT(e1.p_word))
			e1.p_word &= ~PAE_PAGE_FPREPARED;
	}
	if (e1.p_word & PAE_PAGE_FPRESENT) {
		union pae_pdir_e1 iter, flag;
		if __untraced(!HAVE_2MIB_PAGES)
			return false; /* Would need 2MiB pages to flatten present vector. */
		if likely(!PAE_IS_2MIB_ALIGNED(e1.p_word & PAE_PAGE_FADDR_4KIB))
			return false; /* Physical starting address isn't 2MiB aligned. */
		if (e1.p_word & PAE_PAGE_FPREPARED)
			return false; /* Cannot flatten prepared pages. */
		if (PAE_PDIR_E1_ISHINT(e1.p_word))
			return false; /* Cannot flatten hints. */

		/* Check if we can form a linear page of memory. */
		flag.p_word = 0;
		iter.p_word = e1.p_word & ~(PAE_PAGE_FACCESSED | PAE_PAGE_FDIRTY);
		for (vec1 = 1; vec1 < 512; ++vec1) {
			e1.p_word = ATOMIC_READ64(e1_p[vec1].p_word);
			if (vec1 == still_prepared_vec2 && !PAE_PDIR_E1_ISHINT(e1.p_word))
				e1.p_word &= ~PAE_PAGE_FPREPARED;
			flag.p_word |= e1.p_word & (PAE_PAGE_FACCESSED | PAE_PAGE_FDIRTY);
			if (iter.p_word != (e1.p_word & ~(PAE_PAGE_FACCESSED | PAE_PAGE_FDIRTY)))
				return false; /* Non-linear memory, or different page attributes/meta-data */
			assert(!(e1.p_word & PAE_PAGE_FPREPARED) || PAE_PDIR_E1_ISHINT(e1.p_word));
			iter.p_word += 4096;
		}
		e1.p_word |= flag.p_word;
		if (e1.p_word & PAE_PAGE_FPAT_4KIB) {
#if PAE_PAGE_FPAT_4KIB != PAE_PAGE_F2MIB
			e1.p_word &= ~PAE_PAGE_FPAT_4KIB;
#endif /* PAE_PAGE_FPAT_4KIB != PAE_PAGE_F2MIB */
			e1.p_word |= PAE_PAGE_FPAT_2MIB;
		}
		e1.p_word |= PAE_PAGE_F2MIB;
		*new_e2_word = e1.p_word;
		return true;
	}
	if (e1.p_word != PAE_PAGE_ABSENT)
		return false; /* Non-present, but with meta-data (hint/prepared) -> Cannot flatten. */

	/* Check if all entries are marked as ABSENT */
	for (vec1 = 1; vec1 < 512; ++vec1) {
		e1.p_word = ATOMIC_READ64(e1_p[vec1].p_word);
		if (vec1 == still_prepared_vec2 && !PAE_PDIR_E1_ISHINT(e1.p_word))
			e1.p_word &= ~PAE_PAGE_FPREPARED;
		if (e1.p_word != PAE_PAGE_ABSENT)
			return false; /* Present, or with meta-data (hint/prepared) -> Cannot flatten. */
	}
	*new_e2_word = PAE_PAGE_ABSENT;
	return true;
}



#ifdef NDEBUG
#define pae_pagedir_unset_prepared(e1_p, vec3, vec2, vec1, vec1_unprepare_start, vec1_unprepare_size) \
	pae_pagedir_unset_prepared(e1_p)
#endif /* NDEBUG */

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pae_pagedir_unset_prepared)(union pae_pdir_e1 *__restrict e1_p
#ifndef NDEBUG
                                          ,
                                          unsigned int vec3,
                                          unsigned int vec2,
                                          unsigned int vec1,
                                          unsigned int vec1_unprepare_start,
                                          unsigned int vec1_unprepare_size
#endif /* !NDEBUG */
                                          ) {
	u64 word;
	for (;;) {
		/* Corrupt is OK, since ISHINT() only depends on the low 32 bits. */
		word = ATOMIC_READ64_ALLOW_CORRUPT(e1_p->p_word);
		if unlikely(PAE_PDIR_E1_ISHINT(word))
			break; /* Special case: Hint */
#ifndef NDEBUG
		assertf(word & PAE_PAGE_FPREPARED,
		        "Attempted to unprepare page %p...%p as part of "
		        "%p...%p, but that page wasn't marked as prepared",
		        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1),
		        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1 + 1) - 1,
		        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1_unprepare_start),
		        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1_unprepare_start + vec1_unprepare_size) - 1);
#endif /* !NDEBUG */
		if likely(ATOMIC_CMPXCH_WEAK(e1_p->p_word, word, word & ~PAE_PAGE_FPREPARED))
			break;
	}
}


/* Try to flatten 512*4KiB of linear memory to a 2MiB mapping */
PRIVATE NOBLOCK void
NOTHROW(FCALL pae_pagedir_unprepare_impl_flatten)(unsigned int vec3,
                                                  unsigned int vec2,
                                                  unsigned int vec1_unprepare_start,
                                                  unsigned int vec1_unprepare_size) {
	union pae_pdir_e1 *e1_p;
	union pae_pdir_e2 e2, *e2_p;
	unsigned int vec1;
	uintptr_t old_version;
	u64 new_e2_word;
	bool can_flatten;
	assert(vec3 < 4);
	assert(vec2 < 512);
	assert(vec1_unprepare_start < 512);
	assert(vec1_unprepare_size != 0);
	assert(vec1_unprepare_start + vec1_unprepare_size > vec1_unprepare_start);
	assert(vec1_unprepare_start + vec1_unprepare_size <= 512);
	assertf(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT,
			"E2-Vector %u:0-511 (%p-%p) containing pages %p-%p is not present", vec3,
	        (byte_t *)PAE_PDIR_VECADDR(vec3, 0, 0),
	        (byte_t *)PAE_PDIR_VECADDR(vec3, 1, 0) - 1,
	        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1_unprepare_start),
	        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1_unprepare_start + vec1_unprepare_size) - 1);
	assertf(vec3 < PAE_PDIR_VEC3INDEX(KERNELSPACE_BASE),
	        "The caller must ensure that no kernel-space addresses get here");
	e2_p = &PAE_PDIR_E2_IDENTITY[vec3][vec2];
	e2.p_word = ATOMIC_READ64(e2_p->p_word);
	assertf(e2.p_word & PAE_PAGE_FPRESENT,
	        "E1-Vector %u:%u:%u-%u (%p-%p) containing pages %p-%p is not present",
	        vec3, vec2, vec1_unprepare_start, vec1_unprepare_start + vec1_unprepare_size - 1,
	        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, 0),
	        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2 + 1, 0) - 1,
	        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1_unprepare_start),
	        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1_unprepare_start + vec1_unprepare_size) - 1);
	assertf(!(e2.p_word & PAE_PAGE_F2MIB),
	        "A 2MiB page couldn't have been prepared (only 4KiB pages can be)");

	/* Check if the 4KiB vector can be merged.
	 * NOTE: We are guarantied  that accessing the  E1-vector is OK,  because
	 *       the caller guaranties that at least  some part of the vector  is
	 *       still marked as prepared, meaning  that no other thread is  able
	 *       to fully free() the vector until we've cleared all of our marked
	 *       bits. */
	e1_p = PAE_PDIR_E1_IDENTITY[vec3][vec2];
	for (vec1 = vec1_unprepare_start + 1;
	     vec1 < vec1_unprepare_start + vec1_unprepare_size; ++vec1) {
		pae_pagedir_unset_prepared(&e1_p[vec1], vec3, vec2, vec1,
		                           vec1_unprepare_start, vec1_unprepare_size);
	}

	/* Read  the  current prepare-version  _before_  we check  if  flattening is
	 * possible. - That way, other threads are allowed to increment the version,
	 * forcing us to check again further below. */
	old_version = ATOMIC_READ(x86_pagedir_prepare_version);
	can_flatten = pae_pagedir_can_flatten_e1_vector(e1_p, &new_e2_word, vec1_unprepare_start);
	pae_pagedir_unset_prepared(&e1_p[vec1_unprepare_start], vec3, vec2, vec1_unprepare_start,
	                           vec1_unprepare_start, vec1_unprepare_size);
	if unlikely(can_flatten) {
		preemption_flag_t was;
		bool must_restart;
again_try_exchange_e2_word:
		must_restart = false;
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_WRITE(was);
		if unlikely(old_version != ATOMIC_READ(x86_pagedir_prepare_version))
			must_restart = true;
		else if unlikely(!ATOMIC_CMPXCH(e2_p->p_word, e2.p_word, new_e2_word)) {
			must_restart = true;
		}
		X86_PAGEDIR_PREPARE_LOCK_RELEASE_WRITE(was);
		if unlikely(must_restart) {
			/* Check again if the vector can be flattened.
			 * Note  that  we need  a read-lock  to  to the  prepare-lock in
			 * order to prevent the vector from being freed while we do this */
			X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ_NOVER(was);

			/* Re-load the E2 control word in case it has changed. */
			e2.p_word = ATOMIC_READ64(e2_p->p_word);
			if (!(e2.p_word & PAE_PAGE_FPRESENT) || (e2.p_word & PAE_PAGE_F2MIB)) {
				can_flatten = false; /* Not present, or already a 2MiB mapping */
			} else {
				/* Re-load the active version number before
				 * we check if flatten is (still) possible. */
				old_version = ATOMIC_READ(x86_pagedir_prepare_version);
				can_flatten = pae_pagedir_can_flatten_e1_vector(e1_p, &new_e2_word, 512);
			}
			X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
			if unlikely(!can_flatten)
				return;
			goto again_try_exchange_e2_word;
		}

		/* Sync if necessary. */
		pae_pagedir_sync_flattened_e1_vector(vec3, vec2);

		/* Successfully merged the vector.
		 * At this point, all that's left is to free the vector.
		 * NOTE: No need to Shoot-down anything for this, since the new,
		 *       flattened control word has identical meaning to the old
		 *       E1-vector. */
		page_freeone_for_paging(ppageof(e2.p_word & PAE_PAGE_FVECTOR));
	}
}




#if defined(NDEBUG) || 0
#define assert_prepared(addr, num_bytes)          (void)0
#define assert_prepared_if(cond, addr, num_bytes) (void)0
#else /* NDEBUG */
PRIVATE NOBLOCK WUNUSED bool
NOTHROW(FCALL pae_pagedir_isprepared)(VIRT void *addr) {
	uintptr_t word;
	unsigned int vec3, vec2, vec1;
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	word = PAE_PDIR_E3_IDENTITY[vec3].p_word;
	if unlikely(!(word & PAE_PAGE_FPRESENT))
		return false; /* Not mapped */
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	word = PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word;
	if unlikely(!(word & PAE_PAGE_FPRESENT))
		return false; /* Not mapped */
	if unlikely(word & PAE_PAGE_F2MIB)
		return false; /* 2MiB page */
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	word = ATOMIC_READ64_ALLOW_CORRUPT(PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word);
	return word & PAE_PAGE_FPREPARED || PAE_PDIR_E1_ISHINT(word);
}
#define assert_prepared_if(cond, addr, num_bytes) \
	((cond) ? assert_prepared(addr, num_bytes) : (void)0)
LOCAL NOBLOCK void
NOTHROW(KCALL assert_prepared)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes) {
	size_t i;
	for (i = 0; i < num_bytes; i += PAGESIZE) {
		void *ptr = (byte_t *)addr + i;
		assertf(pae_pagedir_isprepared(ptr),
		        "Page at %p of range %p...%p isn't prepared",
		        ptr, addr, (byte_t *)addr + num_bytes - 1);
	}
}
#endif /* !NDEBUG */









/* Prepare the page directory for a future map() operation.
 * The full cycle of a single mapping then looks like this:
 * >> pae_pagedir_prepare(...);
 * >> pae_pagedir_map(...);
 * >> pae_pagedir_unmap(...);
 * >> pae_pagedir_unprepare(...);
 * @return: true:  Successfully allocated structures required for creating mappings.
 * @return: false: Insufficient physical memory to change mappings. */
INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL pae_pagedir_prepareone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	bool result;
	unsigned int vec3, vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	if unlikely((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE)
		return true;
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	result = pae_pagedir_prepare_impl_widen(vec3, vec2, vec1, 1);
	PG_TRACE_PREPARE_IF(result, addr, PAGESIZE);
	assert_prepared_if(result, addr, PAGESIZE);
	return result;
}

INTERN NOBLOCK void
NOTHROW(FCALL pae_pagedir_unprepareone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec3, vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	if unlikely((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE)
		return;
	PG_TRACE_UNPREPARE(addr, PAGESIZE);
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	pae_pagedir_unprepare_impl_flatten(vec3, vec2, vec1, 1);
}


LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL pae_pagedir_prepare_impl_widen_v1)(unsigned int vec3,
                                                 unsigned int vec2,
                                                 unsigned int vec1_min,
                                                 unsigned int vec1_max) {
	assert(vec1_min <= vec1_max);
	return pae_pagedir_prepare_impl_widen(vec3, vec2, vec1_min,
	                                      (vec1_max - vec1_min) + 1);
}

LOCAL NOBLOCK void
NOTHROW(FCALL pae_pagedir_unprepare_impl_flatten_v1)(unsigned int vec3,
                                                     unsigned int vec2,
                                                     unsigned int vec1_min,
                                                     unsigned int vec1_max) {
	assert(vec1_min <= vec1_max);
	pae_pagedir_unprepare_impl_flatten(vec3, vec2, vec1_min,
	                                   (vec1_max - vec1_min) + 1);
}

LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL pae_pagedir_prepare_impl_widen_v2)(unsigned int vec3,
                                                 unsigned int vec2_min,
                                                 unsigned int vec2_max,
                                                 unsigned int vec1_min,
                                                 unsigned int vec1_max) {
	unsigned int vec2;
	assert(vec2_min <= vec2_max);
	if (vec2_min == vec2_max)
		return pae_pagedir_prepare_impl_widen_v1(vec3, vec2_min, vec1_min, vec1_max);
	if (!pae_pagedir_prepare_impl_widen_v1(vec3, vec2_min, vec1_min, 511))
		goto err;
	if (!pae_pagedir_prepare_impl_widen_v1(vec3, vec2_max, 0, vec1_max))
		goto err1;
	for (vec2 = vec2_min + 1; vec2 < vec2_max; ++vec2) {
		if (!pae_pagedir_prepare_impl_widen_v1(vec3, vec2, 0, 511))
			goto err2;
	}
	return true;
err2:
	while (vec2 > vec2_min + 1) {
		--vec2;
		pae_pagedir_unprepare_impl_flatten_v1(vec3, vec2, 0, 511);
	}
	pae_pagedir_unprepare_impl_flatten_v1(vec3, vec2_max, 0, vec1_max);
err1:
	pae_pagedir_unprepare_impl_flatten_v1(vec3, vec2_min, vec1_min, 511);
err:
	return false;
}

LOCAL NOBLOCK void
NOTHROW(FCALL pae_pagedir_unprepare_impl_flatten_v2)(unsigned int vec3,
                                                     unsigned int vec2_min,
                                                     unsigned int vec2_max,
                                                     unsigned int vec1_min,
                                                     unsigned int vec1_max) {
	unsigned int vec2;
	assert(vec2_min <= vec2_max);
	if (vec2_min == vec2_max) {
		pae_pagedir_unprepare_impl_flatten_v1(vec3, vec2_min, vec1_min, vec1_max);
		return;
	}
	pae_pagedir_unprepare_impl_flatten_v1(vec3, vec2_min, vec1_min, 511);
	pae_pagedir_unprepare_impl_flatten_v1(vec3, vec2_max, 0, vec1_max);
	for (vec2 = vec2_min + 1; vec2 < vec2_max; ++vec2)
		pae_pagedir_unprepare_impl_flatten_v1(vec3, vec2, 0, 511);
}


LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL pae_pagedir_prepare_impl_widen_v3)(unsigned int vec3_min,
                                                 unsigned int vec3_max,
                                                 unsigned int vec2_min,
                                                 unsigned int vec2_max,
                                                 unsigned int vec1_min,
                                                 unsigned int vec1_max) {
	assert(vec3_min <= vec3_max);
	assert(vec3_max <= 2);
	if (vec3_min == vec3_max)
		return pae_pagedir_prepare_impl_widen_v2(vec3_min, vec2_min, vec2_max, vec1_min, vec1_max);
	if (!pae_pagedir_prepare_impl_widen_v2(vec3_min, vec2_min, 511, vec1_min, 511))
		goto err;
	if (!pae_pagedir_prepare_impl_widen_v2(vec3_max, 0, vec2_max, 0, vec1_max))
		goto err1;
	if (vec3_min + 1 < vec3_max) {
		assert(vec3_min == 0);
		assert(vec3_max == 2);
		if (!pae_pagedir_prepare_impl_widen_v2(1, 0, 511, 0, 511))
			goto err2;
	}
	return true;
err2:
	pae_pagedir_unprepare_impl_flatten_v2(vec3_max, 0, vec2_max, 0, vec1_max);
err1:
	pae_pagedir_unprepare_impl_flatten_v2(vec3_min, vec2_min, 511, vec1_min, 511);
err:
	return false;
}

LOCAL NOBLOCK void
NOTHROW(FCALL pae_pagedir_unprepare_impl_flatten_v3)(unsigned int vec3_min,
                                                     unsigned int vec3_max,
                                                     unsigned int vec2_min,
                                                     unsigned int vec2_max,
                                                     unsigned int vec1_min,
                                                     unsigned int vec1_max) {
	assert(vec3_min <= vec3_max);
	assert(vec3_max <= 2);
	if (vec3_min == vec3_max) {
		pae_pagedir_unprepare_impl_flatten_v2(vec3_min, vec2_min, vec2_max, vec1_min, vec1_max);
		return;
	}
	pae_pagedir_unprepare_impl_flatten_v2(vec3_min, vec2_min, 511, vec1_min, 511);
	pae_pagedir_unprepare_impl_flatten_v2(vec3_max, 0, vec2_max, 0, vec1_max);
	if (vec3_min + 1 < vec3_max) {
		assert(vec3_min == 0);
		assert(vec3_max == 2);
		pae_pagedir_unprepare_impl_flatten_v2(1, 0, 511, 0, 511);
	}
}


INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL pae_pagedir_prepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes) {
	bool result;
	unsigned int vec3_min, vec3_max;
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_max;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	if unlikely((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE)
		return true;
	if unlikely((byte_t *)addr + num_bytes > (byte_t *)KERNELSPACE_BASE)
		num_bytes = (size_t)((byte_t *)KERNELSPACE_BASE - (byte_t *)addr);
	if (!num_bytes)
		return true;
	if (num_bytes == 4096)
		return pae_pagedir_prepareone(addr);
	vec3_min = PAE_PDIR_VEC3INDEX(addr);
	vec3_max = PAE_PDIR_VEC3INDEX((byte_t *)addr + num_bytes - 1);
	vec2_min = PAE_PDIR_VEC2INDEX(addr);
	vec2_max = PAE_PDIR_VEC2INDEX((byte_t *)addr + num_bytes - 1);
	vec1_min = PAE_PDIR_VEC1INDEX(addr);
	vec1_max = PAE_PDIR_VEC1INDEX((byte_t *)addr + num_bytes - 1);
	result = pae_pagedir_prepare_impl_widen_v3(vec3_min, vec3_max,
	                                           vec2_min, vec2_max,
	                                           vec1_min, vec1_max);
	PG_TRACE_PREPARE_IF(result, addr, num_bytes);
	assert_prepared_if(result, addr, num_bytes);
	return result;
}

INTERN NOBLOCK void
NOTHROW(FCALL pae_pagedir_unprepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes) {
	unsigned int vec3_min, vec3_max;
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_max;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	if unlikely(addr >= (byte_t *)KERNELSPACE_BASE)
		return;
	if unlikely((byte_t *)addr + num_bytes > (byte_t *)KERNELSPACE_BASE)
		num_bytes = (size_t)((byte_t *)KERNELSPACE_BASE - (byte_t *)addr);
	if (!num_bytes)
		return;
	if (num_bytes == 4096) {
		pae_pagedir_unprepareone(addr);
		return;
	}
	PG_TRACE_UNPREPARE(addr, num_bytes);
	vec3_min = PAE_PDIR_VEC3INDEX(addr);
	vec3_max = PAE_PDIR_VEC3INDEX((byte_t *)addr + num_bytes - 1);
	vec2_min = PAE_PDIR_VEC2INDEX(addr);
	vec2_max = PAE_PDIR_VEC2INDEX((byte_t *)addr + num_bytes - 1);
	vec1_min = PAE_PDIR_VEC1INDEX(addr);
	vec1_max = PAE_PDIR_VEC1INDEX((byte_t *)addr + num_bytes - 1);
	pae_pagedir_unprepare_impl_flatten_v3(vec3_min, vec3_max,
	                                      vec2_min, vec2_max,
	                                      vec1_min, vec1_max);
}


#ifdef NDEBUG
#define pae_pagedir_assert_e1_word_prepared(vec3, vec2, vec1, e1_word) (void)0
#else /* NDEBUG */
LOCAL NOBLOCK void
NOTHROW(FCALL pae_pagedir_assert_e1_word_prepared)(unsigned int vec3,
                                                   unsigned int vec2,
                                                   unsigned int vec1,
                                                   u64 e1_word) {
	union pae_pdir_e2 e2;
	assert(vec3 < 4);
	assert(vec2 < 512);
	assert(vec1 < 512);
	assertf((e1_word & PAE_PAGE_FPREPARED) || PAE_PDIR_E1_ISHINT(e1_word),
	        "Cannot set invalid E1 word %" PRIp64 " for prepared entry",
	        (u64)e1_word);
	assert(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT);
	e2 = PAE_PDIR_E2_IDENTITY[vec3][vec2];
	assertf(e2.p_word & PAE_PAGE_FPRESENT,
	        "Page vector #%u:%u for page %p...%p isn't allocated\n"
	        "e2.p_word = %" PRIp64,
	        (unsigned int)vec3, (unsigned int)vec2,
	        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1),
	        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1) + PAGESIZE - 1,
	        e2.p_word);
	assertf(!(e2.p_word & PAE_PAGE_F2MIB),
	        "Page %p...%p exists as a present 2MiB page #%u:%u\n"
	        "e2.p_word = %" PRIp64,
	        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1),
	        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1) + PAGESIZE - 1,
	        (unsigned int)vec3, (unsigned int)vec2, e2.p_word);
	if (vec3 < PAE_PDIR_VEC3INDEX(KERNELSPACE_BASE)) {
		union pae_pdir_e1 e1;
		e1 = PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1];
		assertf(e1.p_word & PAE_PAGE_FPREPARED || PAE_PDIR_E1_ISHINT(e1.p_word),
		        "Page %p...%p [vec3=%u,vec2=%u,vec1=%u] hasn't been prepared\n"
		        "e1.p_word = %" PRIp64,
		        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1),
		        (byte_t *)PAE_PDIR_VECADDR(vec3, vec2, vec1) + PAGESIZE - 1,
		        vec3, vec2, vec1, e1.p_word);
	}
}
#endif /* !NDEBUG */


LOCAL NOBLOCK void
NOTHROW(FCALL pae_pagedir_set_e1_word)(unsigned int vec3,
                                       unsigned int vec2,
                                       unsigned int vec1,
                                       u64 e1_word) {
	pae_pagedir_assert_e1_word_prepared(vec3, vec2, vec1, e1_word);
	COMPILER_WRITE_BARRIER();
	PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word = e1_word;
	COMPILER_WRITE_BARRIER();
}

LOCAL NOBLOCK void
NOTHROW(FCALL pae_pagedir_and_e1_word)(unsigned int vec3,
                                       unsigned int vec2,
                                       unsigned int vec1,
                                       u64 e1_kept_bits_mask) {
	pae_pagedir_assert_e1_word_prepared(vec3, vec2, vec1, e1_kept_bits_mask);
	ATOMIC_AND(PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word, e1_kept_bits_mask);
}

LOCAL NOBLOCK u64
NOTHROW(FCALL pae_pagedir_xch_e1_word)(unsigned int vec3,
                                       unsigned int vec2,
                                       unsigned int vec1,
                                       u64 e1_word) {
	pae_pagedir_assert_e1_word_prepared(vec3, vec2, vec1, e1_word);
	return ATOMIC_XCH(PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word, e1_word);
}

#ifdef NDEBUG
#define pae_pagedir_xch_e1_word_nochk pae_pagedir_xch_e1_word
#else /* NDEBUG */
LOCAL NOBLOCK u64
NOTHROW(FCALL pae_pagedir_xch_e1_word_nochk)(unsigned int vec3,
                                             unsigned int vec2,
                                             unsigned int vec1,
                                             u64 e1_word) {
	return ATOMIC_XCH(PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word, e1_word);
}
#endif /* !NDEBUG */



INTERN ATTR_PAGING_READMOSTLY u64 pae_pageprot_table[0x40] = {
#define COMMON_PRESENT (PAE_PAGE_FPREPARED | PAE_PAGE_FACCESSED | PAE_PAGE_FDIRTY | PAE_PAGE_FPRESENT)
	[(0)]                                                                                                                               = PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_EXEC)]                                                                                                               = COMMON_PRESENT,
	[(PAGEDIR_PROT_WRITE)]                                                                                                              = COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                                          = COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_READ)]                                                                                                               = COMMON_PRESENT | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                                                                           = COMMON_PRESENT,
	[(PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                                                                          = COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                      = COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PWT)]                                                                                                            = PAE_PAGE_FPWT | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_EXEC)]                                                                                        = PAE_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE)]                                                                                       = PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                   = PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ)]                                                                                        = PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                                                    = PAE_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                                                   = PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                               = PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD)]                                                                                                            = PAE_PAGE_FPCD | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_EXEC)]                                                                                        = PAE_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_WRITE)]                                                                                       = PAE_PAGE_FPCD | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                   = PAE_PAGE_FPCD | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ)]                                                                                        = PAE_PAGE_FPCD | COMMON_PRESENT | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                                                    = PAE_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                                                   = PAE_PAGE_FPCD | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                               = PAE_PAGE_FPCD | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT)]                                                                                     = PAE_PAGE_FPCD | PAE_PAGE_FPWT | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_EXEC)]                                                                 = PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE)]                                                                = PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                            = PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ)]                                                                 = PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                             = PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                            = PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                        = PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT)]                                                                                                            = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_EXEC)]                                                                                        = PAE_PAGE_FPAT_4KIB | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_WRITE)]                                                                                       = PAE_PAGE_FPAT_4KIB | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                   = PAE_PAGE_FPAT_4KIB | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_READ)]                                                                                        = PAE_PAGE_FPAT_4KIB | COMMON_PRESENT | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                                                    = PAE_PAGE_FPAT_4KIB | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                                                   = PAE_PAGE_FPAT_4KIB | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                               = PAE_PAGE_FPAT_4KIB | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT)]                                                                                     = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPWT | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_EXEC)]                                                                 = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE)]                                                                = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                            = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ)]                                                                 = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                             = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                            = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                        = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD)]                                                                                     = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_EXEC)]                                                                 = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_WRITE)]                                                                = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                            = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ)]                                                                 = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | COMMON_PRESENT | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                             = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                            = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                        = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT)]                                                              = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | PAE_PAGE_FPWT | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_EXEC)]                                          = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE)]                                         = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                     = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ)]                                          = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                      = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                     = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)] = PAE_PAGE_FPAT_4KIB | PAE_PAGE_FPCD | PAE_PAGE_FPWT | COMMON_PRESENT | PAE_PAGE_FWRITE,
#undef COMMON_PRESENT
};


LOCAL NOBLOCK WUNUSED u64
NOTHROW(FCALL pae_pagedir_encode_4kib)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED PHYS physaddr_t phys,
                                       pagedir_prot_t prot) {
	u64 result;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	assertf(IS_ALIGNED(phys, 4096), "phys = %" PRIpN(__SIZEOF_PHYSADDR_T__), phys);
	assertf(!(prot & ~PAGEDIR_PROT_MASK),
	        "Invalid page protection: %#.4" PRIx16, prot);
	assertf(phys <= (physaddr_t)UINT64_C(0x000ffffffffff000),
	        "Address cannot be mapped under pae: %" PRIpN(__SIZEOF_PHYSADDR_T__),
	        phys);
	result  = (u64)phys;
#if PAGEDIR_PROT_MASK == 0x3f
	result |= pae_pageprot_table[prot];
#else /* PAGEDIR_PROT_MASK == 0x3f */
	result |= pae_pageprot_table[prot & 0x3f];
#endif /* PAGEDIR_PROT_MASK != 0x3f */

	/* All kernel pages have the GLOBAL bit set, and all user pages the USER bit. */
	if ((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE)
		result |= USED_PAE_PAGE_FGLOBAL;
	else {
		result |= PAE_PAGE_FUSER;
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
NOTHROW(FCALL pae_pagedir_maphintone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      VIRT /*ALIGNED(PAE_PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	unsigned int vec3, vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	assertf(IS_ALIGNED((uintptr_t)hint, PAE_PAGEDIR_MAPHINT_ALIGNMENT), "hint = %p", hint);
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	pae_pagedir_set_e1_word(vec3, vec2, vec1,
	                        (u64)(uintptr_t)hint |
	                        PAE_PAGE_FISAHINT);
}

INTERN NOBLOCK void
NOTHROW(FCALL pae_pagedir_maphint)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes,
                                   VIRT /*ALIGNED(PAE_PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	size_t i;
	u64 e1_word;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	assertf(IS_ALIGNED((uintptr_t)hint, PAE_PAGEDIR_MAPHINT_ALIGNMENT), "hint = %p", hint);
	e1_word = (u64)(uintptr_t)hint | PAE_PAGE_FISAHINT;
	for (i = 0; i < num_bytes; i += 4096) {
		unsigned int vec3, vec2, vec1;
		byte_t *effective_addr = (byte_t *)addr + i;
		vec3 = PAE_PDIR_VEC3INDEX(effective_addr);
		vec2 = PAE_PDIR_VEC2INDEX(effective_addr);
		vec1 = PAE_PDIR_VEC1INDEX(effective_addr);
		pae_pagedir_set_e1_word(vec3, vec2, vec1, e1_word);
	}
}

/* Return the hint of the given page, or NULL if no hint has been mapped. */
INTERN NOBLOCK WUNUSED void *
NOTHROW(FCALL pae_pagedir_gethint)(VIRT void *addr) {
	uintptr_t word;
	unsigned int vec3, vec2, vec1;
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	assert(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT);
	word = PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word;
	if unlikely(!(word & PAE_PAGE_FPRESENT))
		return NULL; /* Not mapped */
	if unlikely(word & PAE_PAGE_F2MIB)
		return NULL; /* 2MiB page */
	vec1 = PAE_PDIR_VEC1INDEX(addr);

	/* NOTE: Only read as much as fits into a pointer, thus subverting
	 *       the problem of possibly reading a corrupted value on i386 */
	word = ATOMIC_READ64(PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word);
	if unlikely(!PAE_PDIR_E1_ISHINT(word))
		return NULL;
	return (void *)(uintptr_t)(word & (uintptr_t)PAE_PAGE_FHINT);
}




/* Create/delete a page-directory mapping.
 * @param: prot: A set of `PAGEDIR_PROT_*' detailing how memory should be mapped. */
INTERN NOBLOCK void
NOTHROW(FCALL pae_pagedir_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED PHYS physaddr_t phys,
                                  pagedir_prot_t prot) {
	u64 e1_word;
	unsigned int vec3, vec2, vec1;
	PG_TRACE_MAP(addr, PAGESIZE, phys, prot);
	e1_word = pae_pagedir_encode_4kib(addr, phys, prot);
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	pae_pagedir_set_e1_word(vec3, vec2, vec1, e1_word);
}

INTERN NOBLOCK void
NOTHROW(FCALL pae_pagedir_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes,
                               PAGEDIR_PAGEALIGNED PHYS physaddr_t phys,
                               pagedir_prot_t prot) {
	size_t i;
	u64 e1_word;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	PG_TRACE_MAP(addr, num_bytes, phys, prot);
	e1_word = pae_pagedir_encode_4kib(addr, phys, prot);
	for (i = 0; i < num_bytes; i += 4096) {
		unsigned int vec3, vec2, vec1;
		byte_t *effective_addr = (byte_t *)addr + i;
		vec3 = PAE_PDIR_VEC3INDEX(effective_addr);
		vec2 = PAE_PDIR_VEC2INDEX(effective_addr);
		vec1 = PAE_PDIR_VEC1INDEX(effective_addr);
		pae_pagedir_set_e1_word(vec3, vec2, vec1, e1_word);
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
INTERN NOBLOCK WUNUSED pae_pagedir_pushval_t
NOTHROW(FCALL pae_pagedir_push_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED PHYS physaddr_t phys,
                                       pagedir_prot_t prot) {
	u64 e1_word, result;
	unsigned int vec3, vec2, vec1;
	PG_TRACE_MAP(addr, PAGESIZE, phys, prot);
	e1_word = pae_pagedir_encode_4kib(addr, phys, prot);
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	result = pae_pagedir_xch_e1_word(vec3, vec2, vec1, e1_word);
	return result;
}

INTERN NOBLOCK void
NOTHROW(FCALL pae_pagedir_pop_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      pae_pagedir_pushval_t backup) {
	u64 old_word;
	unsigned int vec3, vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	old_word = pae_pagedir_xch_e1_word_nochk(vec3, vec2, vec1, backup);
	if (old_word & PAE_PAGE_FPRESENT)
		pagedir_syncone(addr); /* The old mapping was also present (explicitly refresh the page). */
}

/* Unmap pages from the given address range. (requires that the given area be prepared) */
INTERN NOBLOCK void
NOTHROW(FCALL pae_pagedir_unmapone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec3, vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	PG_TRACE_UNMAP(addr, PAGESIZE);
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	pae_pagedir_set_e1_word(vec3, vec2, vec1,
	                        PAE_PAGE_ABSENT |
	                        PAE_PAGE_FPREPARED);
}

INTERN NOBLOCK void
NOTHROW(FCALL pae_pagedir_unmap)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes) {
	size_t i;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	PG_TRACE_UNMAP(addr, num_bytes);
	for (i = 0; i < num_bytes; i += 4096) {
		unsigned int vec3, vec2, vec1;
		byte_t *effective_addr = (byte_t *)addr + i;
		vec3 = PAE_PDIR_VEC3INDEX(effective_addr);
		vec2 = PAE_PDIR_VEC2INDEX(effective_addr);
		vec1 = PAE_PDIR_VEC1INDEX(effective_addr);
		pae_pagedir_set_e1_word(vec3, vec2, vec1,
		                        PAE_PAGE_ABSENT |
		                        PAE_PAGE_FPREPARED);
	}
}

/* Remove write-permissions from the given address range. (requires that the given area be prepared) */
INTERN NOBLOCK void
NOTHROW(FCALL pae_pagedir_denywriteone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec3, vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	pae_pagedir_and_e1_word(vec3, vec2, vec1, ~PAE_PAGE_FWRITE);
}

INTERN NOBLOCK void
NOTHROW(FCALL pae_pagedir_denywrite)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes) {
	size_t i;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	for (i = 0; i < num_bytes; i += 4096) {
		unsigned int vec3, vec2, vec1;
		byte_t *effective_addr = (byte_t *)addr + i;
		vec3 = PAE_PDIR_VEC3INDEX(effective_addr);
		vec2 = PAE_PDIR_VEC2INDEX(effective_addr);
		vec1 = PAE_PDIR_VEC1INDEX(effective_addr);
		pae_pagedir_and_e1_word(vec3, vec2, vec1, ~PAE_PAGE_FWRITE);
	}
}

/* Unmap the entirety of user-space.
 * NOTE: Unlike all other unmap() functions, this one guaranties that it
 *       can perform the task without  needing to allocate more  memory! */
INTERN NOBLOCK void
NOTHROW(FCALL pae_pagedir_unmap_userspace)(void) {
	unsigned int vec3, vec2, free_count = 0;
	u64 free_pages[64];
	/* Map all pages before the share-segment as absent. */
	for (vec3 = 0; vec3 < 3; ++vec3) {
		assert(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT);
		for (vec2 = 0; vec2 < 512; ++vec2) {
			union pae_pdir_e2 e2;
			u64 pageptr;
again_read_word:
			/* Allow corruption, since we do our own CMPXCH() below. */
			e2.p_word = ATOMIC_READ64_ALLOW_CORRUPT(PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word);
			if likely(!(e2.p_word & PAE_PAGE_FPRESENT))
				continue; /* Not allocated */

			/* Delete this vector. */
			if unlikely(!ATOMIC_CMPXCH_WEAK(PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word, e2.p_word, PAE_PAGE_ABSENT))
				goto again_read_word;
			if unlikely(e2.p_word & PAE_PAGE_F2MIB)
				continue; /* 2MiB page. */
			pageptr = e2.p_word >> PAE_PAGE_SHIFT;
			if unlikely(free_count >= COMPILER_LENOF(free_pages)) {
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
				free_pages[free_count++] = (u64)pageptr;
			}
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
NOTHROW(FCALL pae_pagedir_unmap_userspace_nosync)(void) {
	unsigned int vec3, vec2;
	/* Map all pages before the share-segment as absent. */
	for (vec3 = 0; vec3 < 3; ++vec3) {
		assert(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT);
		for (vec2 = 0; vec2 < 512; ++vec2) {
			union pae_pdir_e2 e2;
			u64 pageptr;
again_read_word:

			/* Allow corruption, since we do our own CMPXCH() below. */
			e2.p_word = ATOMIC_READ64_ALLOW_CORRUPT(PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word);
			if likely(!(e2.p_word & PAE_PAGE_FPRESENT))
				continue; /* Not allocated */

			/* Delete this vector. */
			if unlikely(!ATOMIC_CMPXCH_WEAK(PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word, e2.p_word, PAE_PAGE_ABSENT))
				goto again_read_word;
			if unlikely(e2.p_word & PAE_PAGE_F2MIB)
				continue; /* 2MiB page. */
			pageptr = e2.p_word >> PAE_PAGE_SHIFT;
			page_freeone_for_paging((physpage_t)pageptr);
		}
	}
}

/* Translate a virtual address into its physical counterpart. */
INTERN NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(1) PHYS physaddr_t
NOTHROW(FCALL pae_pagedir_translate)(VIRT void const *addr) {
	u64 word;
	unsigned int vec3, vec2, vec1;
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	assert(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT);
	word = PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word;
	assertf(word & PAE_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	if unlikely(word & PAE_PAGE_F2MIB)
		return (physaddr_t)((word & PAE_PAGE_FADDR_2MIB) | PAE_PDIR_PAGEINDEX_2MIB(addr));
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	word = PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word;
	assertf(word & PAE_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	return (physaddr_t)((word & PAE_PAGE_FADDR_4KIB) | PAE_PDIR_PAGEINDEX_4KIB(addr));
}

/* Check if the given page is mapped. */
INTERN NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(1) bool
NOTHROW(FCALL pae_pagedir_ismapped)(VIRT void const *addr) {
	u64 word;
	unsigned int vec3, vec2, vec1;
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	assert(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT);
	word = PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word;
	if (!(word & PAE_PAGE_FPRESENT))
		return false;
	if unlikely(word & PAE_PAGE_F2MIB)
		return true;
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	word = PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word;
	return (word & PAE_PAGE_FPRESENT) != 0;
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL pae_pagedir_iswritable)(VIRT void *addr) {
	u64 word;
	unsigned int vec3, vec2, vec1;
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	assert(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT);
	word = PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word;
	if (!(word & PAE_PAGE_FPRESENT))
		return false;
	if unlikely(word & PAE_PAGE_F2MIB)
		return (word & PAE_PAGE_FWRITE) != 0;
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	word = PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word;
	return (word & (PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT)) ==
	       /*   */ (PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT);
}

INTERN NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(1) bool
NOTHROW(FCALL pae_pagedir_isuseraccessible)(VIRT void const *addr) {
	u64 word;
	unsigned int vec3, vec2, vec1;
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	assert(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT);
	word = PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word;
	if (!(word & PAE_PAGE_FPRESENT))
		return false;
	if unlikely(word & PAE_PAGE_F2MIB)
		return (word & PAE_PAGE_FUSER) != 0;
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	word = PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word;
	return (word & (PAE_PAGE_FUSER | PAE_PAGE_FPRESENT)) ==
	       /*   */ (PAE_PAGE_FUSER | PAE_PAGE_FPRESENT);
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL pae_pagedir_isuserwritable)(VIRT void *addr) {
	u64 word;
	unsigned int vec3, vec2, vec1;
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	assert(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT);
	word = PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word;
	if (!(word & PAE_PAGE_FPRESENT))
		return false;
	if unlikely(word & PAE_PAGE_F2MIB)
		return (word & (PAE_PAGE_FUSER | PAE_PAGE_FWRITE)) ==
		       /*   */ (PAE_PAGE_FUSER | PAE_PAGE_FWRITE);
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	word = PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word;
	return (word & (PAE_PAGE_FUSER | PAE_PAGE_FPRESENT | PAE_PAGE_FWRITE)) ==
	       /*   */ (PAE_PAGE_FUSER | PAE_PAGE_FPRESENT | PAE_PAGE_FWRITE);
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL pae_pagedir_haschanged)(VIRT void *addr) {
	u64 word;
	unsigned int vec3, vec2, vec1;
	/* TODO: Figure out a better design for this function
	 *       The current system is written under the assumption that 2MiB pages don't exist... */
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	assert(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT);
	word = PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word;
	if (!(word & PAE_PAGE_FPRESENT))
		return false;
	if unlikely(word & PAE_PAGE_F2MIB)
		return true; /* 2MiB pages aren't supported for this purpose */
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	word = PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word;
	return (word & (PAE_PAGE_FDIRTY | PAE_PAGE_FPRESENT)) ==
	       /*   */ (PAE_PAGE_FDIRTY | PAE_PAGE_FPRESENT);
}

INTERN NOBLOCK void
NOTHROW(FCALL pae_pagedir_unsetchanged)(VIRT void *addr) {
	u64 word;
	unsigned int vec3, vec2, vec1;
	/* TODO: Figure out a better design for this function
	 *       The current system is written under the assumption that 2MiB pages don't exist... */
	vec3 = PAE_PDIR_VEC3INDEX(addr);
	vec2 = PAE_PDIR_VEC2INDEX(addr);
	assert(PAE_PDIR_E3_IDENTITY[vec3].p_word & PAE_PAGE_FPRESENT);
	word = PAE_PDIR_E2_IDENTITY[vec3][vec2].p_word;
	if (!(word & PAE_PAGE_FPRESENT))
		return;
	if unlikely(word & PAE_PAGE_F2MIB)
		return; /* 2MiB pages aren't supported for this purpose */
	vec1 = PAE_PDIR_VEC1INDEX(addr);
	do {
		/* Allow corruption, since we do our own CMPXCH() below. */
		word = ATOMIC_READ64_ALLOW_CORRUPT(PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word);
		if unlikely((word & (PAE_PAGE_FPRESENT | PAE_PAGE_FDIRTY)) ==
		            /*   */ (PAE_PAGE_FPRESENT | PAE_PAGE_FDIRTY))
			return;
	} while (!ATOMIC_CMPXCH_WEAK(PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1].p_word,
	                             word, word & ~PAE_PAGE_FDIRTY));
}


#ifdef CONFIG_HAVE_DEBUGGER

/* NOTE: This function must do its own tracing of continuous page ranges.
 *       The caller is may not necessary ensure that the function is only
 *       called once for a single, continuous range.
 * @param: word: The page directory starting control word.
 *               When `PAE_PAGE_FPRESENT' is set, refers to a mapped page range
 *               When `PAE_PAGE_FISAHINT' is set, refers to a mapped page range */
typedef void (KCALL *pae_enumfun_t)(void *arg, void *start, size_t num_bytes, u64 word);

#define PAE_PAGE_CASCADING \
	(PAE_PAGE_FPRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FUSER | PAE_PAGE_FNOEXEC)

#define PAE_PAGE_FPAT PAE_PAGE_FPAT_4KIB
/* Convert an En | n >= 2 word into an E1 word */
PRIVATE ATTR_DBGTEXT ATTR_CONST WUNUSED u64
NOTHROW(KCALL pae_convert_en_to_e1)(u64 word) {
	assert(word & PAE_PAGE_FPRESENT);
	assert(word & PAE_PAGE_F2MIB);
	word &= ~PAE_PAGE_F2MIB;
#if PAE_PAGE_FPAT_4KIB != PAE_PAGE_FPAT_2MIB
	if (word & PAE_PAGE_FPAT_2MIB) {
		word &= ~PAE_PAGE_FPAT_2MIB;
		word |= PAE_PAGE_FPAT_4KIB;
	}
#endif /* PAE_PAGE_FPAT_4KIB != PAE_PAGE_FPAT_2MIB */
	return word;
}

#define PAE_PDIR_E1_ISUSED(e1_word) (((e1_word) & (PAE_PAGE_FPRESENT | PAE_PAGE_FISAHINT | PAE_PAGE_FPREPARED)) != 0)
PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
pae_enum_e1(pae_enumfun_t func, void *arg,
            unsigned int vec3,
            unsigned int vec2, u64 mask) {
	unsigned int vec1, laststart = 0;
	union pae_pdir_e1 *e1 = PAE_PDIR_E1_IDENTITY[vec3][vec2];
	union pae_pdir_e1 lastword = e1[0];
	lastword.p_word ^= PAE_PAGE_FNOEXEC;
	lastword.p_word &= mask;
	for (vec1 = 1; vec1 < 512; ++vec1) {
		union pae_pdir_e1 word;
		word = e1[vec1];
		word.p_word ^= PAE_PAGE_FNOEXEC;
		word.p_word &= mask;
		if (PAE_PDIR_E1_IS1KIB(word.p_4kib.d_present)) {
			union pae_pdir_e1 expected_word;
			expected_word = lastword;
			expected_word.p_word += (u64)(vec1 - laststart) * 4096;
			if (word.p_word != expected_word.p_word) {
docall:
				if (PAE_PDIR_E1_ISUSED(lastword.p_word)) {
					(*func)(arg, PAE_PDIR_VECADDR(vec3, vec2, laststart),
					        (size_t)(vec1 - laststart) * 4096,
					        lastword.p_word ^ PAE_PAGE_FNOEXEC);
				}
				laststart = vec1;
				lastword  = word;
			}
#if 0
		} else if (PAE_PDIR_E1_ISHINT(word.p_word)) {
			if (word.p_word != lastword.p_word)
				goto docall;
#endif
		} else {
			if (word.p_word != lastword.p_word)
				goto docall;
		}
	}
	if (PAE_PDIR_E1_ISUSED(lastword.p_word)) {
		(*func)(arg, PAE_PDIR_VECADDR(vec3, vec2, laststart),
		        (size_t)(512 - laststart) * 4096,
		        lastword.p_word ^ PAE_PAGE_FNOEXEC);
	}
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
pae_enum_e2(pae_enumfun_t func, void *arg,
            unsigned int vec3, u64 mask) {
	unsigned int vec2 = 1, laststart = 0;
	union pae_pdir_e2 *e2 = PAE_PDIR_E2_IDENTITY[vec3];
	union pae_pdir_e2 word, lastword = e2[0];
	lastword.p_word ^= PAE_PAGE_FNOEXEC;
	lastword.p_word &= mask;
	if (PAE_PDIR_E2_ISVEC1(lastword.p_word)) {
		word = lastword;
		vec2 = 0;
		goto do_enum_e1;
	}
	for (; vec2 < 512; ++vec2) {
		word = e2[vec2];
		word.p_word ^= PAE_PAGE_FNOEXEC;
		word.p_word &= mask;
		if (PAE_PDIR_E2_ISVEC1(word.p_word)) {
			if (PAE_PDIR_E2_IS2MIB(lastword.p_word)) {
				(*func)(arg, PAE_PDIR_VECADDR(vec3, laststart, 0),
				        (size_t)(vec2 - laststart) * 4096 * 512,
				        pae_convert_en_to_e1(lastword.p_word & ~(u64)0x1ff000) ^
				        PAE_PAGE_FNOEXEC);
			}
do_enum_e1:
			pae_enum_e1(func, arg, vec3, vec2,
			            word.p_word | ~(u64)PAE_PAGE_CASCADING);
			laststart = vec2;
			lastword  = word;
		} else if (PAE_PDIR_E2_IS2MIB(word.p_word)) {
			union pae_pdir_e2 expected_word;
			expected_word = lastword;
			expected_word.p_word += (u64)(vec2 - laststart) * 4096 * 512;
			if (word.p_word != expected_word.p_word) {
docall:
				if (PAE_PDIR_E2_IS2MIB(lastword.p_word)) {
					(*func)(arg, PAE_PDIR_VECADDR(vec3, laststart, 0),
					        (size_t)(vec2 - laststart) * 4096 * 512,
					        pae_convert_en_to_e1(lastword.p_word & ~(u64)0x1ff000) ^
					        PAE_PAGE_FNOEXEC);
				}
				laststart = vec2;
				lastword  = word;
			}
		} else {
			if (word.p_word != lastword.p_word)
				goto docall;
		}
	}
	if (PAE_PDIR_E2_IS2MIB(lastword.p_word)) {
		(*func)(arg, PAE_PDIR_VECADDR(vec3, laststart, 0),
		        (size_t)(512 - laststart) * 4096 * 512,
		        pae_convert_en_to_e1(lastword.p_word & ~(u64)0x1ff000) ^
		        PAE_PAGE_FNOEXEC);
	}
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
pae_enum_e3(pae_enumfun_t func, void *arg, unsigned int vec3_end) {
	unsigned int vec3;
	union pae_pdir_e3 *e3 = PAE_PDIR_E3_IDENTITY;
	for (vec3 = 0; vec3 < vec3_end; ++vec3) {
		union pae_pdir_e3 word;
		word = e3[vec3];
		word.p_word ^= PAE_PAGE_FNOEXEC;
		pae_enum_e2(func, arg, vec3,
		            word.p_word | ~(u64)PAE_PAGE_CASCADING);
	}
}

struct pae_enumdat {
	void  *ed_prevstart;
	size_t ed_prevsize;
	u64    ed_prevword;
	u64    ed_mask;
	size_t ed_identcnt;
	bool   ed_skipident;
};

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
pae_printident(struct pae_enumdat *__restrict data) {
	dbg_printf(DBGSTR(AC_WHITE("%p") "-" AC_WHITE("%p") ": " AC_WHITE("%" PRIuSIZ) " identity mappings\n"),
	           (byte_t *)PAE_MMAN_KERNEL_PDIR_IDENTITY_BASE,
	           (byte_t *)PAE_MMAN_KERNEL_PDIR_IDENTITY_BASE + PAE_MMAN_KERNEL_PDIR_IDENTITY_SIZE - 1,
	           data->ed_identcnt);
	data->ed_identcnt = 0;
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
pae_doenum(struct pae_enumdat *__restrict data,
           void *start, size_t num_bytes, u64 word, u64 mask) {
	assert((word & PAE_PAGE_FPRESENT) || (word & PAE_PAGE_FISAHINT));
	if (data->ed_identcnt) {
		pae_printident(data);
		return;
	}
	dbg_printf(DBGSTR(AC_WHITE("%p") "-" AC_WHITE("%p")),
	           start, (byte_t *)start + num_bytes - 1);
	if (word & PAE_PAGE_FPRESENT) {
		size_t indent;
		dbg_printf(DBGSTR(": " AC_WHITE("%p") "+" AC_FG_WHITE),
		           word & PAE_PAGE_FADDR_4KIB);
#if __SIZEOF_SIZE_T__ >= 8
		if ((num_bytes >= ((u64)1024 * 1024 * 1024 * 1024)) &&
		    (num_bytes % ((u64)1024 * 1024 * 1024 * 1024)) == 0) {
			indent = dbg_printf(DBGSTR("%" PRIuSIZ AC_DEFATTR "TiB"),
			                    (size_t)(num_bytes / ((u64)1024 * 1024 * 1024 * 1024)));
		} else
#endif /* __SIZEOF_SIZE_T__ >= 8 */
		if ((num_bytes >= ((u64)1024 * 1024 * 1024)) &&
		    (num_bytes % ((u64)1024 * 1024 * 1024)) == 0) {
			indent = dbg_printf(DBGSTR("%" PRIuSIZ AC_DEFATTR "GiB"),
			                    (size_t)(num_bytes / ((u64)1024 * 1024 * 1024)));
		} else if ((num_bytes >= ((u64)1024 * 1024)) &&
		           (num_bytes % ((u64)1024 * 1024)) == 0) {
			indent = dbg_printf(DBGSTR("%" PRIuSIZ AC_DEFATTR "MiB"),
			                    (size_t)(num_bytes / ((u64)1024 * 1024)));
		} else if ((num_bytes >= ((u64)1024)) &&
		           (num_bytes % ((u64)1024)) == 0) {
			indent = dbg_printf(DBGSTR("%" PRIuSIZ AC_DEFATTR "KiB"),
			                    (size_t)(num_bytes / ((u64)1024)));
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
				u64  mask;
				char ch;
			} const masks[] = {
				{ PAE_PAGE_FNOEXEC, 'x' },
				{ PAE_PAGE_FWRITE, 'w' },
				{ PAE_PAGE_FUSER, 'u' },
				{ PAE_PAGE_FGLOBAL, 'g' },
				{ PAE_PAGE_FACCESSED, 'a' },
				{ PAE_PAGE_FDIRTY, 'd' },
				{ PAE_PAGE_FPREPARED, 'p' },
			};
			dbg_color_t oldcolor;
			unsigned int i;
			oldcolor = dbg_getcolor();
			word ^= PAE_PAGE_FNOEXEC;
			for (i = 0; i < COMPILER_LENOF(masks); ++i) {
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
		if (mask & (PAE_PAGE_FPAT | PAE_PAGE_FPWT | PAE_PAGE_FPCD)) {
			u8 state = 0;
			if (word & PAE_PAGE_FPWT)
				state |= 1;
			if (word & PAE_PAGE_FPCD)
				state |= 2;
			if (word & PAE_PAGE_FPAT)
				state |= 4;
			dbg_printf(DBGSTR("][" AC_FG_WHITE "%x"), (unsigned int)state);
		}
		dbg_print(DBGSTR(AC_DEFATTR "]\n"));
	} else {
		dbg_printf(DBGSTR(": hint@" AC_WHITE("%p") "\n"),
		           (void *)(word & PAE_PAGE_FHINT));
	}
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
pae_enumfun(void *arg, void *start, size_t num_bytes, u64 word) {
	struct pae_enumdat *data;
	data = (struct pae_enumdat *)arg;
	word &= data->ed_mask; /* Mask relevant bits. */
	if (!((word & PAE_PAGE_FPRESENT) || (word & PAE_PAGE_FISAHINT)))
		return;
	if ((byte_t *)data->ed_prevstart + data->ed_prevsize == start) {
		u64 expected_word;
		if (!data->ed_prevsize)
			expected_word = 0;
		else if (word & PAE_PAGE_FPRESENT)
			expected_word = data->ed_prevword + data->ed_prevsize;
		else {
			assert(word & PAE_PAGE_FISAHINT);
			expected_word = data->ed_prevword;
		}
		if (expected_word == word) {
			data->ed_prevsize += num_bytes;
			return;
		}
	}
	if (data->ed_prevsize) {
		if ((byte_t *)data->ed_prevstart >= (byte_t *)PAE_MMAN_KERNEL_PDIR_IDENTITY_BASE) {
			++data->ed_identcnt;
			goto done_print; /* Skip entries within the identity mapping. */
		}
		pae_doenum(data, data->ed_prevstart, data->ed_prevsize, data->ed_prevword, data->ed_mask);
	}
done_print:
	data->ed_prevstart   = start;
	data->ed_prevsize    = num_bytes;
	data->ed_prevword    = word;
}

PRIVATE ATTR_DBGTEXT void KCALL
pae_do_ldsd(unsigned int vec3_max) {
	struct pae_enumdat data;
	data.ed_prevstart = 0;
	data.ed_prevsize  = 0;
	data.ed_prevword  = 0;
	data.ed_skipident = true;
	data.ed_identcnt  = 0;
	data.ed_mask = PAE_PAGE_FVECTOR | PAE_PAGE_FPRESENT | PAE_PAGE_FWRITE | PAE_PAGE_FUSER |
	               PAE_PAGE_FPWT | PAE_PAGE_FPCD | PAE_PAGE_FPAT | PAE_PAGE_FNOEXEC |
	               PAE_PAGE_FPREPARED | PAE_PAGE_FGLOBAL | PAE_PAGE_FACCESSED | PAE_PAGE_FDIRTY;
	pae_enum_e3(&pae_enumfun, &data, vec3_max);
	if (data.ed_prevsize)
		pae_doenum(&data, data.ed_prevstart, data.ed_prevsize, data.ed_prevword, data.ed_mask);
}

INTERN ATTR_DBGTEXT void FCALL
pae_dbg_lspd(pagedir_phys_t pdir) {
	if (pdir == pagedir_kernel_phys) {
		pae_do_ldsd(4);
		return;
	}
	PAGEDIR_P_BEGINUSE(pdir) {
		pae_do_ldsd(3);
	}
	PAGEDIR_P_ENDUSE(pdir);
}
#endif /* CONFIG_HAVE_DEBUGGER */


DECL_END

#endif /* !CONFIG_NO_PAGING_PAE */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_PAE_C_INL */
