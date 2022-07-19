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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING64_C_INL
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING64_C_INL 1
#define __OMIT_PAGING_CONSTANT_P_WRAPPERS
#define __WANT_MMAN_EXCLUDE_PAGEDIR
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/arch/paging64.h>
#include <kernel/except.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/_archinit.h>
#include <kernel/mman/phys.h>
#include <kernel/mman/sync.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/x86/cpuid.h>
#include <sched/cpu.h>
#include <sched/userkern.h>
#include <sched/x86/tss.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sched/preemption.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <asm/cpu-cpuid.h>
#include <asm/cpu-flags.h>
#include <asm/farptr.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "paging.h"

DECL_BEGIN

/* Return the physical page ID of a given physical address. */
#define ppageof(paddr) (physpage_t)((paddr) / PAGESIZE)

/* Feature tests helpers */
#define HAVE_PAGE_GLOBAL_BIT       X86_HAVE_PAGE_GLOBAL_BIT
#define HAVE_PAGE_ATTRIBUTE_TABLE  X86_HAVE_PAGE_ATTRIBUTE_TABLE
#define HAVE_INSTR_INVLPG          X86_HAVE_INSTR_INVLPG
#define HAVE_INSTR_INVPCID         X86_HAVE_INSTR_INVPCID
#define HAVE_1GIB_PAGES            X86_HAVE_1GIB_PAGES
#define HAVE_2MIB_PAGES            X86_HAVE_2MIB_PAGES
#define HAVE_EXECUTE_DISABLE       X86_HAVE_EXECUTE_DISABLE

/* This flag is set to 0 during the boot assembly bootstrap
 * if it is found that the global page bit isn't supported. */
INTERN u64 used_pxx_page_fglobal = P64_PAGE_FGLOBAL;
#define USED_P64_PAGE_FGLOBAL used_pxx_page_fglobal


/* I always find recursive array declarations in C to be extremely confusing,
 * so  to make sure I didn't screw up the array-length ordering of the E{1-4}
 * descriptor types, assert that they offsets behave correctly in relation to
 * their indices. */
struct p64_pdir_e1_identity_t_struct { p64_pdir_e1_identity_t x; };
struct p64_pdir_e2_identity_t_struct { p64_pdir_e2_identity_t x; };
struct p64_pdir_e3_identity_t_struct { p64_pdir_e3_identity_t x; };
struct p64_pdir_e4_identity_t_struct { p64_pdir_e4_identity_t x; };
static_assert(offsetof(struct p64_pdir_e1_identity_t_struct, x[1][0][0][0]) == 512 * 512 * 512 * 8);
static_assert(offsetof(struct p64_pdir_e2_identity_t_struct, x[1][0][0])    == 512 * 512 * 8);
static_assert(offsetof(struct p64_pdir_e3_identity_t_struct, x[1][0])       == 512 * 8);
static_assert(offsetof(struct p64_pdir_e4_identity_t_struct, x[1])          == 8);


static_assert(sizeof(struct p64_pdir) == P64_PDIR_SIZE);
static_assert(sizeof(struct p64_pdir) == 4096);
static_assert(sizeof(union p64_pdir_e4) == 8);
static_assert(sizeof(union p64_pdir_e3) == 8);
static_assert(sizeof(union p64_pdir_e2) == 8);
static_assert(sizeof(union p64_pdir_e1) == 8);

static_assert(P64_PDIR_E1_IDENTITY_BASE == P64_MMAN_KERNEL_PDIR_IDENTITY_BASE);
static_assert(P64_PDIR_E2_IDENTITY_BASE == P64_PDIR_E1_IDENTITY_BASE + (P64_PDIR_VEC4INDEX(P64_PDIR_E1_IDENTITY_BASE) * P64_PDIR_E3_SIZE));
static_assert(P64_PDIR_E3_IDENTITY_BASE == P64_PDIR_E2_IDENTITY_BASE + (P64_PDIR_VEC3INDEX(P64_PDIR_E2_IDENTITY_BASE) * P64_PDIR_E2_SIZE));
static_assert(P64_PDIR_E4_IDENTITY_BASE == P64_PDIR_E3_IDENTITY_BASE + (P64_PDIR_VEC2INDEX(P64_PDIR_E3_IDENTITY_BASE) * P64_PDIR_E1_SIZE));



PRIVATE ATTR_SECTION(".free.unmap_but_keep_allocated") ATTR_ALIGNED(4096)
union p64_pdir_e1 boot_trampoline_e1v[512];

INTDEF byte_t __kernel_free_end[] ASMNAME("__kernel_end");

/* Prepare 2 consecutive (and 2-page aligned) pages of  virtual
 * memory for the purpose of doing the initial prepare required
 * for `THIS_TRAMPOLINE_PAGE' of `boottask' and also `bootidle' */
INTERN NOBLOCK ATTR_FREETEXT WUNUSED void *
NOTHROW(FCALL kernel_initialize_boot_trampolines)(void) {
	u64 e1_word, e2_word;
	byte_t *trampoline_addr;
	unsigned int vec1, vec2, vec3, vec4, i;

	/* We allocate the boot trampoline immediately after the
	 * end of the kernel's .free section in virtual  memory. */
	trampoline_addr = __kernel_free_end;
	assert(IS_ALIGNED((uintptr_t)trampoline_addr, 4096));
again_calculate_vecN:
	vec1 = P64_PDIR_VEC1INDEX(trampoline_addr);
	vec2 = P64_PDIR_VEC2INDEX(trampoline_addr);
	vec3 = P64_PDIR_VEC3INDEX(trampoline_addr);
	vec4 = P64_PDIR_VEC4INDEX(trampoline_addr);
	if unlikely_untraced(vec1 == 511) {
		/* Make sure that the two pages used are located in the same E1-vector. */
		trampoline_addr += PAGESIZE;
		goto again_calculate_vecN;
	}
	assert(IS_ALIGNED((u64)boot_trampoline_e1v, 4096));
	assert(P64_PDIR_E4_IDENTITY[vec4].p_vec3.v_present);
	assert(P64_PDIR_E3_IDENTITY[vec4][vec3].p_vec2.v_present);
	assert(!P64_PDIR_E3_IDENTITY[vec4][vec3].p_1gib.d_1gib_1);
	assert(P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_2mib.d_present);
	assert(P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_2mib.d_2mib_1);

	/* Figure out the physical address surrounding the trampoline's E1-vector. */
	e1_word = (u64)trampoline_addr - KERNEL_CORE_BASE;
	assertf(pagedir_translate(trampoline_addr) == (physaddr_t)e1_word,
	        "%p != %p",
	        (uintptr_t)pagedir_translate(trampoline_addr),
	        (uintptr_t)e1_word);

	/* Since we need to set-up the whole E1-vector, adjust so we start at its base */
	e1_word -= vec1 * 4096;
	e1_word |= (P64_PAGE_FPRESENT | P64_PAGE_FWRITE |
	            P64_PAGE_FACCESSED | P64_PAGE_FDIRTY |
	            USED_P64_PAGE_FGLOBAL);
	for (i = 0; i < 512; ++i) {
		boot_trampoline_e1v[i].p_word = e1_word;
		e1_word += 4096;
	}

	/* Mark the 3 pages used for the trampolines as prepared. */
	boot_trampoline_e1v[vec1 + 0].p_word |= P64_PAGE_FPREPARED;
	boot_trampoline_e1v[vec1 + 1].p_word |= P64_PAGE_FPREPARED;
	boot_trampoline_e1v[vec1 + 2].p_word |= P64_PAGE_FPREPARED;

	/* Setup the replacement E2-word */
	e2_word = (u64)boot_trampoline_e1v - KERNEL_CORE_BASE; /* virt2phys() */
	e2_word |= (P64_PAGE_FPRESENT | P64_PAGE_FWRITE | P64_PAGE_FACCESSED);
	COMPILER_WRITE_BARRIER();

	/* Set the E1-vector as being used. */
	ATOMIC_WRITE(P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word, e2_word);

	/* Return the virtual memory locations used for the
	 * trampolines needed by `boottask', `bootidle' and `asyncwork' */
	return trampoline_addr;
}






/* Define the kernel mman */
INTERN ATTR_SECTION(".data.permman.head")
struct mman mman_kernel_head = { _MMAN_KERNEL_INIT };


typedef struct {
	/* Allocate enough  structures to  allow _start64.S  to create  an
	 * identity mapping of the first 2GiB of physical memory at -2GiB,
	 * using only 2MiB mappings.
	 * With this in mind, we need:
	 *  - 255 * E3-VECTOR  (`union p64_pdir_e3[255][512]') that will be used for the kernel-share
	 *  - 1 * E3-VECTOR    (`union p64_pdir_e3[512]') that goes into `pagedir_kernel.p_e4[511]'
	 *  - 2 * E2-VECTOR    (`union p64_pdir_e2[2][512]') that go into `p64_pdir_e3[510]' and `p64_pdir_e3[511]'
	 * _start64.S will then fill the two E2-vectors with 2MiB identity mappings,
	 * before having the E3 vector point towards them, before finally placing the
	 * E3 vector within the kernel page directory. */
	union p64_pdir_e3 ks_share_e3[256][512];
	union p64_pdir_e2 ks_share_e2[2][512];
} kernel_share_t;

/* Allocate BSS memory for the initial shared+identity mapping
 * that  will later be shared with, and re-appear in all other
 * page directories (except for the identity page) */
INTERN ATTR_SECTION(".bss.x86.pagedir_kernel_share")
kernel_share_t __x86_pagedir_kernel_share = {};



/* Initialize the given page directory.
 * The caller is required to allocate the page directory
 * controller itself, which  must be  aligned and  sized
 * according to `PAGEDIR_ALIGN' and `PAGEDIR_SIZE'. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p64_pagedir_init)(VIRT struct p64_pdir *__restrict self,
                                PHYS u64 phys_self) {
	/* Make  sure that  the page directory  identity mapping is  located at the
	 * proper position. Note that this position is `KERNELSPACE_BASE + 512GiB',
	 * where  KERNELSPACE_BASE  is  at `0xffff800000000000',  meaning  that the
	 * identity mapping is at: `0xffff808000000000 ... 0xffff80ffffffffff'
	 *
	 * With this in mind, x86_64  is different from i386, in  that the page directory  identity
	 * mapping isn't stored at the end of the kernel address space, but rather (near) the start
	 * of  it (we intentionally don't use `KERNELSPACE_BASE' itself as base address in order to
	 * keep the first page  of kernel-space unmapped (meaning  that given the 512GiB  alignment
	 * requirements of the identity mapping, we end up with `KERNELSPACE_BASE + 512GiB')) */
	static_assert(P64_PDIR_VEC4INDEX(P64_MMAN_KERNEL_PDIR_IDENTITY_BASE) == 257);
	static_assert(P64_PDIR_VEC3INDEX(P64_MMAN_KERNEL_PDIR_IDENTITY_BASE) == 0);
	static_assert(P64_PDIR_VEC2INDEX(P64_MMAN_KERNEL_PDIR_IDENTITY_BASE) == 0);
	static_assert(P64_PDIR_VEC1INDEX(P64_MMAN_KERNEL_PDIR_IDENTITY_BASE) == 0);

	/* Assert that the page directory is properly aligned. */
	assert(IS_ALIGNED((uintptr_t)self, PAGESIZE));
	assert(IS_ALIGNED((uintptr_t)phys_self, PAGESIZE));
	memsetq(self->p_e4 + 0, P64_PAGE_ABSENT, 256);              /* user-space */
	memcpyq(self->p_e4 + 256, P64_PDIR_E4_IDENTITY + 256, 256); /* kernel-space */

	/* Set the control word for the page directory identity mapping. */
	self->p_e4[257].p_word = (u64)phys_self | P64_PAGE_FACCESSED | P64_PAGE_FWRITE | P64_PAGE_FPRESENT;
}



/* Finalize a given page directory. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p64_pagedir_fini)(VIRT struct p64_pdir *__restrict self,
                                PHYS struct p64_pdir *phys_self) {
#define NOT_SWITCHED ((PHYS pagedir_t *)-1)
	unsigned int vec4;
	preemption_flag_t was;
	PHYS pagedir_t *old_pagedir = NOT_SWITCHED;
	assert(IS_ALIGNED((uintptr_t)self, PAGESIZE));
	assert(IS_ALIGNED((uintptr_t)phys_self, PAGESIZE));
	assertf((self->p_e4[257].p_word & ~(P64_PAGE_FACCESSED | P64_PAGE_FDIRTY)) ==
	        ((u64)phys_self | P64_PAGE_FWRITE | P64_PAGE_FPRESENT),
	        "Page directory does not contain a valid identity mapping\n"
	        "self->p_e4[257].p_word = %p\n"
	        "phys_self              = %p\n",
	        self->p_e4[257].p_word, phys_self);
	for (vec4 = 0; vec4 < 256; ++vec4) {
		union p64_pdir_e4 e4;
		e4 = self->p_e4[vec4];

		/* Search through user-space for any allocated E3 vectors. */
		if (P64_PDIR_E4_ISVEC3(e4.p_word)) {
			unsigned int vec3;

			/* Switch to the target page directory so we can  make
			 * use of its identity mapping in order to destroy it. */
			if (old_pagedir == NOT_SWITCHED) {
				preemption_pushoff(&was);
				old_pagedir = pagedir_get();
				pagedir_set((PHYS pagedir_t *)phys_self);
			}
			for (vec3 = 0; vec3 < 512; ++vec3) {
				union p64_pdir_e3 e3;
				e3 = P64_PDIR_E3_IDENTITY[vec4][vec3];

				/* Check if this is an allocated E2 vector. */
				if (P64_PDIR_E3_ISVEC2(e3.p_word)) {
					unsigned int vec2;
					for (vec2 = 0; vec2 < 512; ++vec2) {
						union p64_pdir_e2 e2;
						e2 = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2];

						/* Check if this is an allocated E1 vector. */
						if (P64_PDIR_E2_ISVEC1(e2.p_word)) {
							page_freeone_for_paging(ppageof(e2.p_word & P64_PAGE_FVECTOR));
						}
					}
					page_freeone_for_paging(ppageof(e3.p_word & P64_PAGE_FVECTOR));
				}
			}
			page_freeone_for_paging(ppageof(e4.p_word & P64_PAGE_FVECTOR));
		}
	}
	if (old_pagedir != NOT_SWITCHED) {
		pagedir_set(old_pagedir);
		preemption_pop(&was);
	}
#undef NOT_SWITCHED
}


LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p64_pagedir_set_prepared)(union p64_pdir_e1 *__restrict e1_p) {
	u64 word;
	for (;;) {
		word = ATOMIC_READ(e1_p->p_word);
		if unlikely(P64_PDIR_E1_ISHINT(word))
			break; /* Special case: Hint */
		if likely(ATOMIC_CMPXCH_WEAK(e1_p->p_word, word, word | P64_PAGE_FPREPARED))
			break;
	}
}



/* Lock counter to indicate that some thread somewhere is accessing
 * one of the following (already allocated) vectors for the purpose
 * of eventually setting PREPARED bit of some E1 vector entry:
 *  - P64_PDIR_E4_IDENTITY[vec4].p_e3   (only when `vec4 < 256')
 *  - P64_PDIR_E3_IDENTITY[vec4][vec3].p_e2
 *  - P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_e1
 * In turn, this lock must be held whenever some thread is intending
 * on  flattening (or deleting) any one of these vectors (outside of
 * `pagedir_fini()') */
PRIVATE struct atomic_rwlock x86_pagedir_prepare_lock = ATOMIC_RWLOCK_INIT;

/* Version counter for `x86_pagedir_prepare_lock' (incremented each read/write) */
PRIVATE ATTR_WRITEMOSTLY WEAK uintptr_t x86_pagedir_prepare_version = 0;

#define X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was)                    \
	do {                                                              \
		preemption_pushoff(&was);                                     \
		if likely(atomic_rwlock_tryread(&x86_pagedir_prepare_lock)) { \
			ATOMIC_INC(x86_pagedir_prepare_version);                  \
			break;                                                    \
		}                                                             \
		preemption_pop(&was);                                         \
		preemption_tryyield();                                        \
	}	__WHILE1
#define X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ_NOVER(was)            \
	do {                                                            \
		preemption_pushoff(&was);                                   \
		if likely(atomic_rwlock_tryread(&x86_pagedir_prepare_lock)) \
			break;                                                  \
		preemption_pop(&was);                                       \
		preemption_tryyield();                                      \
	}	__WHILE1
#define X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_WRITE(was)                  \
	do {                                                             \
		preemption_pushoff(&was);                                    \
		if likely(atomic_rwlock_trywrite(&x86_pagedir_prepare_lock)) \
			break;                                                   \
		preemption_pop(&was);                                        \
		preemption_tryyield();                                       \
	}	__WHILE1
#define X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was)        \
	do {                                                  \
		atomic_rwlock_endread(&x86_pagedir_prepare_lock); \
		preemption_pop(&was);                              \
	}	__WHILE0
#define X86_PAGEDIR_PREPARE_LOCK_RELEASE_WRITE(was)        \
	do {                                                   \
		atomic_rwlock_endwrite(&x86_pagedir_prepare_lock); \
		preemption_pop(&was);                               \
	}	__WHILE0


PRIVATE NOBLOCK WUNUSED NONNULL((1)) physpage_t
NOTHROW(FCALL p64_create_e1_vector_from_e2_word)(struct mptram *__restrict ptram,
                                                 u64 e2_word,
                                                 unsigned int vec1_prepare_start,
                                                 unsigned int vec1_prepare_size) {
	union p64_pdir_e1 e1, *e1_p;
	physpage_t result;
	result = page_mallocone_for_paging();
	if unlikely(result == PHYSPAGE_INVALID)
		goto done;

	/* Fill in the E1 vector. */
	e1_p = (union p64_pdir_e1 *)mptram_mappage(ptram, result);
	if (e2_word & P64_PAGE_FPRESENT) {
		/* Convert a 2MiB mapping into 512 * 4KiB mappings */
		assert(e2_word & P64_PAGE_F2MIB);
#if P64_PAGE_FPAT_2MIB != P64_PAGE_FPAT_4KIB
		e1.p_word = e2_word & ~(P64_PAGE_F2MIB | P64_PAGE_FPAT_2MIB);
		if (e2_word & P64_PAGE_FPAT_2MIB)
			e1.p_word |= P64_PAGE_FPAT_4KIB;
#else /* P64_PAGE_FPAT_2MIB != P64_PAGE_FPAT_4KIB */
		e1.p_word = e2_word & ~(P64_PAGE_F2MIB);
#endif /* P64_PAGE_FPAT_2MIB == P64_PAGE_FPAT_4KIB */
		if (vec1_prepare_size == 512) {
			unsigned int vec1;
			assert(vec1_prepare_start == 0);
			/* Mark all specific pages as prepared */
			e1.p_word |= P64_PAGE_FPREPARED;
			for (vec1 = 0; vec1 < 512; ++vec1) {
				e1_p[vec1] = e1;
				e1.p_word += 4096;
			}
		} else {
			unsigned int vec1;
			for (vec1 = 0; vec1 < 512; ++vec1) {
				e1_p[vec1] = e1;
				e1.p_word += 4096;
			}
			/* Mark only specific pages as prepared */
			for (vec1 = vec1_prepare_start;
				 vec1 < vec1_prepare_start + vec1_prepare_size; ++vec1)
				e1_p[vec1].p_word |= P64_PAGE_FPREPARED;
		}
	} else if (vec1_prepare_size == 512) {
		/* Mark all pages as prepared */
		assert(vec1_prepare_start == 0);
		memsetq(e1_p, P64_PAGE_FPREPARED, 512);
	} else {
		/* Mark only specific pages as prepared */
		e1_p = (union p64_pdir_e1 *)mempsetq(e1_p, P64_PAGE_ABSENT, vec1_prepare_start);
		e1_p = (union p64_pdir_e1 *)mempsetq(e1_p, P64_PAGE_FPREPARED, vec1_prepare_size);
		e1_p = (union p64_pdir_e1 *)mempsetq(e1_p, P64_PAGE_ABSENT,
		                                     512 - (vec1_prepare_start + vec1_prepare_size));
	}
done:
	return result;
}

/* Create an E2-vector from a given E3-word  */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) physpage_t
NOTHROW(FCALL p64_create_e2_vector_from_e3_word_and_e1_vector)(struct mptram *__restrict ptram,
                                                               u64 e3_word,
                                                               unsigned int vec2,
                                                               physpage_t e1_vector,
                                                               bool is_userspace) {
	physpage_t result;
	union p64_pdir_e2 e2, *e2_p;

	/* Fill in the E2 vector. */
	result = page_mallocone_for_paging();
	if unlikely(result == PHYSPAGE_INVALID)
		goto done;
	e2_p = (union p64_pdir_e2 *)mptram_mappage(ptram, result);
	if (e3_word & P64_PAGE_FPRESENT) {
		unsigned int vec2_i;
		assert(e3_word & P64_PAGE_F1GIB);
		e2.p_word = e3_word;
#if P64_PAGE_F1GIB != P64_PAGE_F2MIB
		e2.p_word &= ~P64_PAGE_F1GIB;
		e2.p_word |= P64_PAGE_F2MIB;
#endif /* P64_PAGE_F1GIB != P64_PAGE_F2MIB */
		assert(e2.p_word & P64_PAGE_F2MIB);
#if P64_PAGE_FPAT_1GIB != P64_PAGE_FPAT_2MIB
		e2.p_word |= P64_PAGE_FPAT_2MIB;
		if (e3_word & P64_PAGE_FPAT_1GIB)
			e2.p_word |= P64_PAGE_FPAT_2MIB;
#endif /* P64_PAGE_FPAT_1GIB != P64_PAGE_FPAT_2MIB */
		for (vec2_i = 0; vec2_i < 512; ++vec2_i) {
			e2_p[vec2_i] = e2;
			e2.p_word += 4096;
		}
	} else {
#if P64_PAGE_ABSENT == 0
		if (!page_iszero(result))
#endif /* P64_PAGE_ABSENT == 0 */
		{
			memsetq(e2_p, P64_PAGE_ABSENT, 512);
		}
		e2.p_word = 0;
	}

	/* Set the E1-vector pointer in `E2[vec2]'. */
	e2.p_word &= (P64_PAGE_FUSER | P64_PAGE_FPWT |
	              P64_PAGE_FPCD | P64_PAGE_FACCESSED |
	              P64_PAGE_FGLOBAL);
	e2.p_word |= (u64)e1_vector * 4096;
	e2.p_word |= P64_PAGE_FPRESENT | P64_PAGE_FWRITE;
	if (is_userspace)
		e2.p_word |= P64_PAGE_FUSER;
	e2_p[vec2] = e2;
done:
	return result;
}


/* Convert an E3-word into an E2-word (replacing 1GIB with 2MIB) */
LOCAL NOBLOCK ATTR_CONST WUNUSED u64
NOTHROW(FCALL p64_e3word_to_e2word)(u64 e3_word) {
	u64 e2_word = e3_word;
#if P64_PAGE_FPAT_1GIB != P64_PAGE_FPAT_2MIB
	if (e3_word & P64_PAGE_F1GIB) {
		e2_word &= ~P64_PAGE_FPAT_1GIB;
		if (e3_word & P64_PAGE_FPAT_1GIB)
			e2_word |= P64_PAGE_FPAT_2MIB;
	}
#endif /* P64_PAGE_FPAT_1GIB != P64_PAGE_FPAT_2MIB */
#if P64_PAGE_F1GIB != P64_PAGE_F2MIB
	if (e3_word & P64_PAGE_F1GIB) {
		e2_word &= ~P64_PAGE_F1GIB;
		e2_word |= P64_PAGE_F2MIB;
	}
#endif /* P64_PAGE_F1GIB != P64_PAGE_F2MIB */
	return e2_word;
}


/* Try  to  widen a  2MiB  mapping to  a  512*4KiB vector  of  linear memory
 * Alternatively, if  the specified  E1-vector is  absent, pre-allocate  it.
 * Additionally, set the `P64_PAGE_FPREPARED' bit for all E1 vector elements
 * within   the    range    of    `vec1_prepare_start...+=vec1_prepare_size'
 * Note that `vec1_prepare_size' must be non-zero!
 * @return: true:  Success
 * @return: false: Failed to allocate physical memory */
PRIVATE NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_impl_widen)(unsigned int vec4,
                                              unsigned int vec3,
                                              unsigned int vec2,
                                              unsigned int vec1_prepare_start,
                                              unsigned int vec1_prepare_size) {
	/* NOTE: This function is  able to  access `THIS_TRAMPOLINE_PAGE',  since
	 *       that memory location is always already prepared from the get-go.
	 * -> The  dependency loop formed  by this is resolved
	 *    thanks to `kernel_initialize_boot_trampolines()' */
#define VEC4_IS_USERSPACE (vec4 < 256)
	union p64_pdir_e4 e4;
	union p64_pdir_e3 e3;
	union p64_pdir_e2 e2;
	preemption_flag_t was;
	assert(vec4 < 512);
	assert(vec3 < 512);
	assert(vec2 < 512);
	assert(vec1_prepare_start < 512);
	assert(vec1_prepare_size != 0);
	assert(vec1_prepare_start + vec1_prepare_size > vec1_prepare_start);
	assert(vec1_prepare_start + vec1_prepare_size <= 512);
again:
	e4.p_word = ATOMIC_READ(P64_PDIR_E4_IDENTITY[vec4].p_word);
	if (!P64_PDIR_E4_ISVEC3(e4.p_word)) {
		physpage_t e3_vector; /* 511 * P64_PAGE_ABSENT + 1 * VEC2 */
		physpage_t e2_vector; /* 511 * P64_PAGE_ABSENT + 1 * VEC1 */
		physpage_t e1_vector; /* 512 * P64_PAGE_ABSENT */
		u64 new_e4_word;
		union p64_pdir_e3 *e3_p;
		union p64_pdir_e2 *e2_p;
		union p64_pdir_e1 *e1_p;
		struct mptram ptram;
		assertf(VEC4_IS_USERSPACE,
		        "All E4 entries for kernel-space must contain pre-allocated E3-vectors\n"
		        "vec4      = %u\n"
		        "e4.p_word = %p",
		        vec4, e4.p_word);
		/* At this point, we must:
		 * >> VEC3 = ALLOC();
		 * >> VEC2 = ALLOC();
		 * >> VEC1 = ALLOC();
		 * >> VEC3[vec3] = VEC2;
		 * >> VEC2[vec2] = VEC1;
		 * >> VEC1[vec1_prepare_start...+=vec1_prepare_size] = P64_PAGE_FPREPARED;
		 * >> P64_PDIR_E4_IDENTITY[vec4] = VEC3; */

		/* Allocate vectors. */
		e3_vector = page_mallocone_for_paging();
		if unlikely(!e3_vector)
			goto err;
		e2_vector = page_mallocone_for_paging();
		if unlikely(!e2_vector) {
err_e3_vector:
			page_freeone_for_paging(e3_vector);
			goto err;
		}
		e1_vector = page_mallocone_for_paging();
		if unlikely(!e1_vector) {
			page_freeone_for_paging(e2_vector);
			goto err_e3_vector;
		}
		mptram_init(&ptram);

		/* Initialize the E1-vector. */
		e1_p = (union p64_pdir_e1 *)mptram_mappage(&ptram, e1_vector);
		if (vec1_prepare_size == 512) {
			assert(vec1_prepare_start == 0);
			memsetq(e1_p, P64_PAGE_FPREPARED, 512);
		} else {
			e1_p = (union p64_pdir_e1 *)mempsetq(e1_p, P64_PAGE_ABSENT, vec1_prepare_start);
			e1_p = (union p64_pdir_e1 *)mempsetq(e1_p, P64_PAGE_FPREPARED, vec1_prepare_size);
			e1_p = (union p64_pdir_e1 *)mempsetq(e1_p, P64_PAGE_ABSENT,
			                                     512 - (vec1_prepare_start + vec1_prepare_size));
		}

		/* Initialize the E2-vector. */
		e2_p = (union p64_pdir_e2 *)mptram_mappage(&ptram, e2_vector);
#if P64_PAGE_ABSENT == 0
		if (!page_iszero(e2_vector))
#endif /* P64_PAGE_ABSENT == 0 */
		{
			memsetq(e2_p, P64_PAGE_ABSENT, 512);
		}
		e2_p[vec2].p_word = (u64)physpage2addr(e1_vector) | P64_PAGE_FPRESENT |
		                    P64_PAGE_FWRITE | P64_PAGE_FUSER;

		/* Initialize the E3-vector. */
		e3_p = (union p64_pdir_e3 *)mptram_mappage(&ptram, e3_vector);
#if P64_PAGE_ABSENT == 0
		if (!page_iszero(e3_vector))
#endif /* P64_PAGE_ABSENT == 0 */
		{
			memsetq(e3_p, P64_PAGE_ABSENT, 512);
		}
		e3_p[vec3].p_word = (u64)physpage2addr(e2_vector) | P64_PAGE_FPRESENT |
		                    P64_PAGE_FWRITE | P64_PAGE_FUSER;
		COMPILER_BARRIER();
		mptram_fini(&ptram);

		/* Try to install the new E3-vector as an E4-word. */
		new_e4_word = (u64)physpage2addr(e3_vector) | P64_PAGE_FPRESENT |
		              P64_PAGE_FWRITE | P64_PAGE_FUSER;
		if unlikely(!ATOMIC_CMPXCH(P64_PDIR_E4_IDENTITY[vec4].p_word,
		                           e4.p_word, new_e4_word)) {
/*word_changed_after_e3_vector:*/
			page_freeone_for_paging(e3_vector);
			page_freeone_for_paging(e2_vector);
			page_freeone_for_paging(e1_vector);
			goto again;
		}
		goto success;
	}

	/* Only  need  to  acquire  the  PREPARE-lock  for accessing
	 * our  associated  `P64_PDIR_E3_IDENTITY[vec4][vec3]'  when
	 * the E3-vector is located in user-space. For kernel-space,
	 * we can  always assume  that  E3-vectors are  always  pre-
	 * allocated,  since  this pre-allocation  is  also required
	 * for the kernel share segment! */
	if (VEC4_IS_USERSPACE) {
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was);
		/* Make sure that the E4 word hasn't changed. */
		if unlikely(e4.p_word != ATOMIC_READ(P64_PDIR_E4_IDENTITY[vec4].p_word)) {
			X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
			goto again;
		}
	}

	e3.p_word = ATOMIC_READ(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word);
	if (!e3.p_vec2.v_present || e3.p_1gib.d_1gib_1) {
		/* Convert the 1GiB mapping into
		 *  - 511 * 2MiB mappings + 512 * 4KiB mappings (the later being `vec2') */
		struct mptram ptram;
		physpage_t e1_vector; /* 512 * 4KiB */
		physpage_t e2_vector; /* 511 * 2MiB + 1 * VEC1 */
		union p64_pdir_e2 e2_word;
		u64 new_word, new_e3_word;
		if (VEC4_IS_USERSPACE)
			X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);

		/* Create an E1 vector and mark all of the requested items as being prepared. */
		e2_word.p_word = p64_e3word_to_e2word(e3.p_word);

		/* Adjust the E2-word such that it properly represent a 2MiB page
		 * offset from a 1GiB page (using a shift of `vec2 * 2MiB' bytes) */
		if (e3.p_vec2.v_present) {
			assert(e3.p_1gib.d_1gib_1);
			assert(e2_word.p_2mib.d_2mib_1);
			e2_word.p_word += vec2 * P64_PDIR_E2_SIZE;
		} else {
			assert(!e2_word.p_vec1.v_present);
		}
		mptram_init(&ptram);
		e1_vector = p64_create_e1_vector_from_e2_word(&ptram,
		                                              e2_word.p_word,
		                                              vec1_prepare_start,
		                                              vec1_prepare_size);
		if (e1_vector == PHYSPAGE_INVALID) {
			mptram_fini(&ptram);
			goto err;
		}

		/* Construct an E2 vector pointing to the E1 vector created earlier. */
		e2_vector = p64_create_e2_vector_from_e3_word_and_e1_vector(&ptram, e3.p_word,
		                                                            vec2, e1_vector,
		                                                            VEC4_IS_USERSPACE);
		COMPILER_BARRIER();
		mptram_fini(&ptram);
		if (e2_vector == PHYSPAGE_INVALID) {
			page_freeone_for_paging(e1_vector);
			goto err;
		}
		new_e3_word = (u64)e2_vector * 4096;
		new_e3_word |= P64_PAGE_FPRESENT | P64_PAGE_FWRITE;
		if (e3.p_vec2.v_present) {
			new_e3_word |= e3.p_word & (P64_PAGE_FUSER | P64_PAGE_FPWT |
			                            P64_PAGE_FPCD | P64_PAGE_FACCESSED |
			                            P64_PAGE_FGLOBAL);
		}
		if (VEC4_IS_USERSPACE)
			new_e3_word |= P64_PAGE_FUSER;
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was);
		new_word = ATOMIC_READ(P64_PDIR_E4_IDENTITY[vec4].p_word);
		if unlikely(e4.p_word != new_word) {
word_changed_after_e2_vector:
			if (VEC4_IS_USERSPACE)
				X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
			page_freeone_for_paging(e2_vector);
			page_freeone_for_paging(e1_vector);
			goto again;
		}

		/* Try to install the new E2-vector. */
		if unlikely(!ATOMIC_CMPXCH(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word,
		                           e3.p_word, new_e3_word))
			goto word_changed_after_e2_vector;
		X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
		goto success;
	}

	/* When  it comes to accessing the E2 and  E1 vectors, we always need to be
	 * holding  the PREPARE lock, regardless of being in kernel- or user-space,
	 * as the E2 and E1 vectors are dynamically allocated (and most importantly
	 * also dynamically freed) in both kernel- and user-space. */
	if (!VEC4_IS_USERSPACE)
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was);
	e2.p_word = ATOMIC_READ(P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word);
	if (!e2.p_vec1.v_present || e2.p_2mib.d_2mib_1) {
		/* Convert the 2MiB mapping into
		 *  - 512 * 4KiB mappings */
		struct mptram ptram;
		physpage_t e1_vector;
		u64 new_word, new_e2_word;
		X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
		mptram_init(&ptram);
		e1_vector = p64_create_e1_vector_from_e2_word(&ptram, e2.p_word,
		                                              vec1_prepare_start,
		                                              vec1_prepare_size);
		COMPILER_BARRIER();
		mptram_fini(&ptram);
		if unlikely(e1_vector == PHYSPAGE_INVALID)
			goto err;

		/* Re-acquire the prepare lock and make sure that the  vectors
		 * leading up to the one we've just allocated haven't changed. */
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was);
		new_word = ATOMIC_READ(P64_PDIR_E4_IDENTITY[vec4].p_word);
		if unlikely(e4.p_word != new_word) {
word_changed_after_e1_vector:
			X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
			page_freeone_for_paging(e1_vector);
			goto again;
		}
		new_word = ATOMIC_READ(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word);
		if unlikely(e3.p_word != new_word)
			goto word_changed_after_e1_vector;
		new_e2_word = (u64)physpage2addr(e1_vector);
		new_e2_word |= P64_PAGE_FPRESENT | P64_PAGE_FWRITE | P64_PAGE_FACCESSED;
		new_e2_word |= e2.p_word & (P64_PAGE_FUSER | P64_PAGE_FPWT |
		                            P64_PAGE_FPCD | P64_PAGE_FGLOBAL);
		if (VEC4_IS_USERSPACE)
			new_e2_word |= P64_PAGE_FUSER;

		/* Try to install the new E1-vector. */
		if unlikely(!ATOMIC_CMPXCH(P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word,
		                           e2.p_word, new_e2_word))
			goto word_changed_after_e1_vector;
		X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
		goto success;
	}

	/* The E1-vector already exists.
	 * In this case, we simply have to set the PREPARED bit for every indicated entry!
	 * Note  that for this purpose, we only need  to keep hold of the PREPARE-LOCK for
	 * the  first entry, since  any entry after that  will still be  apart of the same
	 * E1-vector, while the presence of the  PREPARED bit already guaranties that  the
	 * vector will not be flattened while we're still holding the lock! */
	{
		union p64_pdir_e1 *e1_p;
		unsigned int vec1;
		e1_p = &P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1_prepare_start];
		p64_pagedir_set_prepared(e1_p);
		X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
		/* Now mark all of the remaining pages as prepared. */
		for (vec1 = 1; vec1 < vec1_prepare_size; ++vec1)
			p64_pagedir_set_prepared(&e1_p[vec1]);
		COMPILER_WRITE_BARRIER();
	}

	/* And we're done! */
success:
	return true;
err:
	return false;
#undef VEC4_IS_USERSPACE
}





PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(KCALL p64_pagedir_can_flatten_e1_vector)(union p64_pdir_e1 const e1_p[512],
                                                 u64 *__restrict new_e2_word,
                                                 unsigned int still_prepared_vec2) {
	unsigned int vec1;
	union p64_pdir_e1 e1;
	e1.p_word = ATOMIC_READ(e1_p[0].p_word);
	if (still_prepared_vec2 == 0) {
		assert(e1.p_word & P64_PAGE_FPREPARED || P64_PDIR_E1_ISHINT(e1.p_word));
		if (!P64_PDIR_E1_ISHINT(e1.p_word))
			e1.p_word &= ~P64_PAGE_FPREPARED;
	}
	if (e1.p_word & P64_PAGE_FPRESENT) {
		union p64_pdir_e1 iter, flag;
		if __untraced(!HAVE_2MIB_PAGES)
			return false; /* Would need 2MiB pages to flatten present vector. */
		if likely(!P64_IS_2MIB_ALIGNED(e1.p_word & P64_PAGE_FADDR_4KIB))
			return false; /* Physical starting address isn't 2MiB aligned. */
		if (e1.p_word & P64_PAGE_FPREPARED)
			return false; /* Cannot flatten prepared pages. */
		if (P64_PDIR_E1_ISHINT(e1.p_word))
			return false; /* Cannot flatten hints. */

		/* Check if we can form a linear page of memory. */
		flag.p_word = 0;
		iter.p_word = e1.p_word & ~(P64_PAGE_FACCESSED | P64_PAGE_FDIRTY);
		for (vec1 = 1; vec1 < 512; ++vec1) {
			e1.p_word = ATOMIC_READ(e1_p[vec1].p_word);
			if (vec1 == still_prepared_vec2 && !P64_PDIR_E1_ISHINT(e1.p_word))
				e1.p_word &= ~P64_PAGE_FPREPARED;
			flag.p_word |= e1.p_word & (P64_PAGE_FACCESSED | P64_PAGE_FDIRTY);
			if (iter.p_word != (e1.p_word & ~(P64_PAGE_FACCESSED | P64_PAGE_FDIRTY)))
				return false; /* Non-linear memory, or different page attributes/meta-data */
			assert(!(e1.p_word & P64_PAGE_FPREPARED) || P64_PDIR_E1_ISHINT(e1.p_word));
			iter.p_word += 4096;
		}
		e1.p_word |= flag.p_word;
#if P64_PAGE_FPAT_4KIB != P64_PAGE_FPAT_2MIB
		if (e1.p_word & P64_PAGE_FPAT_4KIB) {
#if P64_PAGE_FPAT_4KIB != P64_PAGE_F2MIB
			e1.p_word &= ~P64_PAGE_FPAT_4KIB;
#endif /* P64_PAGE_FPAT_4KIB != P64_PAGE_F2MIB */
			e1.p_word |= P64_PAGE_FPAT_2MIB;
		}
#endif /* P64_PAGE_FPAT_4KIB != P64_PAGE_FPAT_2MIB */
		e1.p_word |= P64_PAGE_F2MIB;
		*new_e2_word = e1.p_word;
		return true;
	}
	if (e1.p_word != P64_PAGE_ABSENT)
		return false; /* Non-present, but with meta-data (hint/prepared) -> Cannot flatten. */

	/* Check if all entries are marked as ABSENT */
	for (vec1 = 1; vec1 < 512; ++vec1) {
		e1.p_word = ATOMIC_READ(e1_p[vec1].p_word);
		if (vec1 == still_prepared_vec2 && !P64_PDIR_E1_ISHINT(e1.p_word))
			e1.p_word &= ~P64_PAGE_FPREPARED;
		if (e1.p_word != P64_PAGE_ABSENT)
			return false; /* Present, or with meta-data (hint/prepared) -> Cannot flatten. */
	}
	*new_e2_word = P64_PAGE_ABSENT;
	return true;
}

PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(KCALL p64_pagedir_can_flatten_e2_vector)(union p64_pdir_e2 const e2_p[512],
                                                 u64 *__restrict new_e3_word) {
	unsigned int vec2;
	union p64_pdir_e2 e2;
	e2.p_word = ATOMIC_READ(e2_p[0].p_word);
	if (e2.p_word & P64_PAGE_FPRESENT) {
		union p64_pdir_e2 iter, flag;
		if __untraced(!HAVE_1GIB_PAGES)
			return false; /* Would need 1GiB pages to flatten present vector of 2MiB pages. */
		if __untraced(!(e2.p_word & P64_PAGE_F2MIB))
			return false; /* Can only flatten 2MiB pages. */
		if likely(!P64_IS_1GIB_ALIGNED(e2.p_word & P64_PAGE_FADDR_2MIB))
			return false; /* Physical starting address isn't 1GiB aligned. */

		/* Check if we can form a linear page of memory. */
		flag.p_word = 0;
		iter.p_word = e2.p_word & ~(P64_PAGE_FACCESSED | P64_PAGE_FDIRTY);
		for (vec2 = 1; vec2 < 512; ++vec2) {
			e2.p_word = ATOMIC_READ(e2_p[vec2].p_word);
			flag.p_word |= e2.p_word & (P64_PAGE_FACCESSED | P64_PAGE_FDIRTY);
			if (iter.p_word != (e2.p_word & ~(P64_PAGE_FACCESSED | P64_PAGE_FDIRTY)))
				return false; /* Non-linear memory, or different page attributes/meta-data */
			assert(P64_PDIR_E2_IS2MIB(e2.p_word));
			iter.p_word += 512 * 4096;
		}
		e2.p_word |= flag.p_word;
#if P64_PAGE_FPAT_2MIB != P64_PAGE_FPAT_1GIB
		if (e2.p_word & P64_PAGE_FPAT_2MIB) {
#if P64_PAGE_FPAT_2MIB != P64_PAGE_F1GIB
			e2.p_word &= ~P64_PAGE_FPAT_2MIB;
#endif /* P64_PAGE_FPAT_4KIB != P64_PAGE_F1GIB */
			e2.p_word |= P64_PAGE_FPAT_1GIB;
		}
#endif /* P64_PAGE_FPAT_2MIB != P64_PAGE_FPAT_1GIB */
		e2.p_word |= P64_PAGE_F1GIB;
		*new_e3_word = e2.p_word;
		return true;
	}

	/* Check if all entries are marked as NON-PRESENT
	 * NOTE: This  differs  from E1-vectors  in that  we simply
	 *       consider anything without the  `P64_PAGE_FPRESENT'
	 *       flag to be what E1 calls ABSENT, since unlike  E1,
	 *       we don't need to account for custom meta-data such
	 *       as paging hints or the PREPARED flag. */
	for (vec2 = 1; vec2 < 512; ++vec2) {
		e2.p_word = ATOMIC_READ(e2_p[vec2].p_word);
		if (e2.p_word & P64_PAGE_FPRESENT)
			return false; /* Present -> Cannot flatten. */
	}

	/* E2 can be flattened into a non-present E1 vector. */
	*new_e3_word = P64_PAGE_ABSENT;
	return true;
}

PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(KCALL p64_pagedir_can_flatten_e3_vector)(union p64_pdir_e3 const e3_p[512],
                                                 u64 *__restrict new_e4_word) {
	unsigned int vec3;
	union p64_pdir_e3 e3;
	e3.p_word = ATOMIC_READ(e3_p[0].p_word);
	if (e3.p_word & P64_PAGE_FPRESENT) {
		/* There are no 512GiB pages, so we can't flatten this one... */
		return false;
	}

	/* Check if all entries are marked as NON-PRESENT
	 * NOTE: This  differs  from E1-vectors  in that  we simply
	 *       consider anything without the  `P64_PAGE_FPRESENT'
	 *       flag to be what E1 calls ABSENT, since unlike  E1,
	 *       we don't need to account for custom meta-data such
	 *       as paging hints or the PREPARED flag. */
	for (vec3 = 1; vec3 < 512; ++vec3) {
		e3.p_word = ATOMIC_READ(e3_p[vec3].p_word);
		if (e3.p_word & P64_PAGE_FPRESENT)
			return false; /* Present -> Cannot flatten. */
	}

	/* E2 can be flattened into a non-present E1 vector. */
	*new_e4_word = P64_PAGE_ABSENT;
	return true;
}

#ifdef NDEBUG
#define p64_pagedir_unset_prepared(e1_p, vec4, vec3, vec2, vec1, vec1_unprepare_start, vec1_unprepare_size) \
	p64_pagedir_unset_prepared(e1_p)
#endif /* NDEBUG */

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p64_pagedir_unset_prepared)(union p64_pdir_e1 *__restrict e1_p
#ifndef NDEBUG
                                          ,
                                          unsigned int vec4,
                                          unsigned int vec3,
                                          unsigned int vec2,
                                          unsigned int vec1,
                                          unsigned int vec1_unprepare_start,
                                          unsigned int vec1_unprepare_size
#endif /* !NDEBUG */
                                          ) {
	u64 word;
	for (;;) {
		word = ATOMIC_READ(e1_p->p_word);
		if unlikely(P64_PDIR_E1_ISHINT(word))
			break; /* Special case: Hint */
#ifndef NDEBUG
		assertf(word & P64_PAGE_FPREPARED,
		        "Attempted to unprepare page %p...%p as part of "
		        "%p...%p, but that page wasn't marked as prepared",
		        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1),
		        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1 + 1) - 1,
		        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1_unprepare_start),
		        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1_unprepare_start + vec1_unprepare_size) - 1);
#endif /* !NDEBUG */
		if likely(ATOMIC_CMPXCH_WEAK(e1_p->p_word, word, word & ~P64_PAGE_FPREPARED))
			break;
	}
}


/* Called after  an E1-vector  was flattened  into an  E2-entry
 * that now resides at `P64_PDIR_E2_IDENTITY[vec4][vec3][vec2]' */
PRIVATE NOBLOCK void
NOTHROW(FCALL p64_pagedir_sync_flattened_e1_vector)(unsigned int vec4,
                                                    unsigned int vec3,
                                                    unsigned int vec2) {
	/* Even  though the in-memory mapping of `P64_PDIR_VECADDR(vec4, vec3, vec2, 0..511)'
	 * didn't change, due to being flattened, the contents of our page directory identity
	 * mapping _have_ changed:
	 *     UNMAP(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][0..511])  (This is exactly 1 page)
	 */
	void *sync_pageaddr;
	sync_pageaddr = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2];
	if (vec4 >= P64_PDIR_VEC4INDEX(KERNELSPACE_BASE)) {
		/* Sync as part of the kernel MMan */
		mman_supersyncone(sync_pageaddr);
	} else {
		/* Sync as part of the current page directory. */
		pagedir_syncone_smp(sync_pageaddr);
	}
}

/* Called after an E2-vector was flattened into an E3-entry
 * that now  resides at  `P64_PDIR_E3_IDENTITY[vec4][vec3]' */
PRIVATE NOBLOCK void
NOTHROW(FCALL p64_pagedir_sync_flattened_e2_vector)(unsigned int vec4,
                                                    unsigned int vec3) {
#if 1 /* It's faster to just sync everything... */
	(void)vec3;
	if (vec4 >= P64_PDIR_VEC4INDEX(KERNELSPACE_BASE)) {
		mman_supersyncall();
	} else {
		pagedir_syncall_smp();
	}
#else
	/* Even though the in-memory mapping of `P64_PDIR_VECADDR(vec4, vec3, 0..511, 0..511)'
	 * didn't change, due to being flattened, the contents of our page directory  identity
	 * mapping _have_ changed:
	 *     UNMAP(P64_PDIR_E2_IDENTITY[vec4][vec3][0..511])  (This is exactly 1 page)
	 */
	void *sync_pageaddr;
	sync_pageaddr = P64_PDIR_E2_IDENTITY[vec4][vec3];
	if (vec4 >= P64_PDIR_VEC4INDEX(KERNELSPACE_BASE)) {
		/* Sync as part of the kernel MMan */
		mman_supersyncone(sync_pageaddr);
		/* Must also sync:
		 * P64_PDIR_E1_IDENTITY[vec4][vec3][0..511][0..511] */
		mman_supersync(P64_PDIR_E1_IDENTITY[vec4][vec3],
		               512 * 512 * 8);
	} else {
		/* Sync as part of the current page directory. */
		pagedir_syncone_smp(sync_pageaddr);
		/* Must also sync:
		 * P64_PDIR_E1_IDENTITY[vec4][vec3][0..511][0..511] */
		pagedir_sync_smp(P64_PDIR_E1_IDENTITY[vec4][vec3],
		                      512 * 512 * 8);
	}
#endif
}

/* Called after an E3-vector was flattened into an E4-entry
 * that   now   resides   at   `P64_PDIR_E4_IDENTITY[vec4]' */
PRIVATE NOBLOCK void
NOTHROW(FCALL p64_pagedir_sync_flattened_e3_vector)(unsigned int vec4) {
#if 1 /* It's faster to just sync everything... */
	if (vec4 >= P64_PDIR_VEC4INDEX(KERNELSPACE_BASE)) {
		mman_supersyncall();
	} else {
		pagedir_syncall_smp();
	}
#else
	/* Even though the in-memory mapping of `P64_PDIR_VECADDR(vec4, 0..511, 0..511, 0..511)'
	 * didn't change, due to  being flattened, the contents  of our page directory  identity
	 * mapping _have_ changed:
	 *     UNMAP(P64_PDIR_E3_IDENTITY[vec4][0..511])  (This is exactly 1 page)
	 */
	void *sync_pageaddr;
	sync_pageaddr = P64_PDIR_E3_IDENTITY[vec4];
	if (vec4 >= P64_PDIR_VEC4INDEX(KERNELSPACE_BASE)) {
		/* Sync as part of the kernel MMan */
		mman_supersyncone(sync_pageaddr);
		/* Must also sync:
		 * P64_PDIR_E2_IDENTITY[vec4][0..511][0..511] */
		mman_supersync(P64_PDIR_E2_IDENTITY[vec4],
		               512 * 512 * 8);
		/* Must also sync:
		 * P64_PDIR_E1_IDENTITY[vec4][0..511][0..511][0..511] */
		mman_supersync(P64_PDIR_E1_IDENTITY[vec4],
		               512 * 512 * 512 * 8);
	} else {
		/* Sync as part of the current page directory. */
		pagedir_syncone_smp(sync_pageaddr);
		/* Must also sync:
		 * P64_PDIR_E2_IDENTITY[vec4][0..511][0..511] */
		pagedir_sync_smp(P64_PDIR_E2_IDENTITY[vec4],
		                      512 * 512 * 8);
		/* Must also sync:
		 * P64_PDIR_E1_IDENTITY[vec4][0..511][0..511][0..511] */
		pagedir_sync_smp(P64_PDIR_E1_IDENTITY[vec4],
		                      512 * 512 * 512 * 8);
	}
#endif
}


/* Try to flatten 512*4KiB of linear memory to a 2MiB mapping,
 * as well as  512*2MiB of  linear memory to  a 1GiB  mapping. */
PRIVATE NOBLOCK void
NOTHROW(FCALL p64_pagedir_unprepare_impl_flatten)(unsigned int vec4,
                                                  unsigned int vec3,
                                                  unsigned int vec2,
                                                  unsigned int vec1_unprepare_start,
                                                  unsigned int vec1_unprepare_size) {
	/* Delete the `P64_PAGE_FPREPARED' bit for:
	 *     P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1_unprepare_start...+=vec1_unprepare_size-1]
	 * Then, try to flatten:
	 *   - P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][0-511]
	 *     P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word = P64_PAGE_F2MIB (or P64_PAGE_ABSENT)
	 *
	 *   - P64_PDIR_E2_IDENTITY[vec4][vec3][0-511]
	 *     P64_PDIR_E3_IDENTITY[vec4][vec3].p_word = P64_PAGE_F1GIB (or P64_PAGE_ABSENT)
	 *
	 *   - P64_PDIR_E3_IDENTITY[vec4][0-511]
	 *     P64_PDIR_E4_IDENTITY[vec4].p_word = P64_PAGE_ABSENT
	 * Note that for the flattening part, we need to be holding `x86_pagedir_prepare_lock',
	 * as well as account for `x86_pagedir_prepare_version' */
	union p64_pdir_e1 *e1_p;
	union p64_pdir_e2 e2, *e2_p;
	unsigned int vec1;
	uintptr_t old_version;
	u64 new_e2_word;
	bool can_flatten;
	assert(vec4 < 512);
	assert(vec3 < 512);
	assert(vec2 < 512);
	assert(vec1_unprepare_start < 512);
	assert(vec1_unprepare_size != 0);
	assert(vec1_unprepare_start + vec1_unprepare_size > vec1_unprepare_start);
	assert(vec1_unprepare_start + vec1_unprepare_size <= 512);
	assertf(P64_PDIR_E4_IDENTITY[vec4].p_word & P64_PAGE_FPRESENT,
	        "E3-Vector %u:0-511 (%p-%p) containing pages %p-%p is not present", vec4,
	        (byte_t *)P64_PDIR_VECADDR(vec4, 0, 0, 0),
	        (byte_t *)P64_PDIR_VECADDR(vec4, 1, 0, 0) - 1,
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1_unprepare_start),
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1_unprepare_start + vec1_unprepare_size) - 1);
	assertf(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word & P64_PAGE_FPRESENT,
	        "E2-Vector %u:%u:0-511 (%p-%p) containing pages %p-%p is not present", vec4, vec3,
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, 0, 0),
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, 1, 0) - 1,
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1_unprepare_start),
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1_unprepare_start + vec1_unprepare_size) - 1);
	e2_p = &P64_PDIR_E2_IDENTITY[vec4][vec3][vec2];
	e2.p_word = ATOMIC_READ(e2_p->p_word);
	assertf(e2.p_word & P64_PAGE_FPRESENT,
	        "E1-Vector %u:%u:%u:%u-%u (%p-%p) containing pages %p-%p is not present",
	        vec4, vec3, vec2, vec1_unprepare_start, vec1_unprepare_start + vec1_unprepare_size - 1,
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, 0),
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2 + 1, 0) - 1,
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1_unprepare_start),
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1_unprepare_start + vec1_unprepare_size) - 1);
	assertf(!(e2.p_word & P64_PAGE_F2MIB),
	        "A 2MiB page couldn't have been prepared (only 4KiB pages can be)");

	/* Check if the 4KiB vector can be merged.
	 * NOTE: We are guarantied  that accessing the  E1-vector is OK,  because
	 *       the caller guaranties that at least  some part of the vector  is
	 *       still marked as prepared, meaning  that no other thread is  able
	 *       to fully free() the vector until we've cleared all of our marked
	 *       bits. */
	e1_p = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2];
	for (vec1 = vec1_unprepare_start + 1;
	     vec1 < vec1_unprepare_start + vec1_unprepare_size; ++vec1) {
		p64_pagedir_unset_prepared(&e1_p[vec1], vec4, vec3, vec2, vec1,
		                           vec1_unprepare_start, vec1_unprepare_size);
	}

	/* Read  the  current prepare-version  _before_  we check  if  flattening is
	 * possible. - That way, other threads are allowed to increment the version,
	 * forcing us to check again further below. */
	old_version = ATOMIC_READ(x86_pagedir_prepare_version);
	can_flatten = p64_pagedir_can_flatten_e1_vector(e1_p, &new_e2_word, vec1_unprepare_start);
	p64_pagedir_unset_prepared(&e1_p[vec1_unprepare_start],
	                           vec4, vec3, vec2,
	                           vec1_unprepare_start,
	                           vec1_unprepare_start,
	                           vec1_unprepare_size);
	if unlikely(can_flatten) {
		preemption_flag_t was;
		bool must_restart;
		u64 new_e3_word;
		union p64_pdir_e3 *e3_p, e3;
again_try_exchange_e2_word:
		must_restart = false;
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_WRITE(was);
		if unlikely(old_version != ATOMIC_READ(x86_pagedir_prepare_version)) {
			must_restart = true;
		} else if unlikely(!ATOMIC_CMPXCH(e2_p->p_word, e2.p_word, new_e2_word)) {
			must_restart = true;
		}
		X86_PAGEDIR_PREPARE_LOCK_RELEASE_WRITE(was);
		if unlikely(must_restart) {
			/* Check again if the vector can be flattened.
			 * Note  that  we need  a read-lock  to  to the  prepare-lock in
			 * order to prevent the vector from being freed while we do this */
			X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ_NOVER(was);
			if (!P64_PDIR_E4_ISVEC3(ATOMIC_READ(P64_PDIR_E4_IDENTITY[vec4].p_word)) ||
			    !P64_PDIR_E3_ISVEC2(ATOMIC_READ(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word))) {
				can_flatten = false; /* One of the surrounding vectors was deleted */
			} else {
				/* Re-load the E2 control word in case it has changed. */
				e2.p_word = ATOMIC_READ(e2_p->p_word);
				if (!(e2.p_word & P64_PAGE_FPRESENT) || (e2.p_word & P64_PAGE_F2MIB)) {
					/* !P64_PDIR_E2_ISVEC1() */
					can_flatten = false; /* Not present, or already a 2MiB mapping */
				} else {
					/* Re-load the active version number before
					 * we check if flatten is (still) possible. */
					old_version = ATOMIC_READ(x86_pagedir_prepare_version);
					can_flatten = p64_pagedir_can_flatten_e1_vector(e1_p, &new_e2_word, 512);
				}
			}
			X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
			if unlikely(!can_flatten)
				return;
			goto again_try_exchange_e2_word;
		}

		/* Sync if necessary. */
		p64_pagedir_sync_flattened_e1_vector(vec4, vec3, vec2);

		/* Successfully merged the vector.
		 * At this point, all that's left is to free the vector.
		 * NOTE: No need to Shoot-down anything for this, since the new,
		 *       flattened control word has identical meaning to the old
		 *       E1-vector. */
		page_freeone_for_paging(ppageof(e2.p_word & P64_PAGE_FVECTOR));

		/* At this  point, we've  flattened the  E1-vector into  an  E2-word.
		 * With  this in mind,  also try to  flatten the associated E2-vector
		 * into an E3-word (aka. a 1GiB page / 1GiB of fully unmapped memory) */
		e2_p = P64_PDIR_E2_IDENTITY[vec4][vec3];
		e3_p = &P64_PDIR_E3_IDENTITY[vec4][vec3];
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_WRITE(was);
		if (!P64_PDIR_E4_ISVEC3(ATOMIC_READ(P64_PDIR_E4_IDENTITY[vec4].p_word)) ||
		    !P64_PDIR_E3_ISVEC2(ATOMIC_READ(e3_p->p_word))) {
			can_flatten = false; /* One of the surrounding vectors was deleted */
		} else {
			can_flatten = p64_pagedir_can_flatten_e2_vector(e2_p, &new_e3_word);
		}
		if (!can_flatten) {
			X86_PAGEDIR_PREPARE_LOCK_RELEASE_WRITE(was);
			return;
		}

		/* Replace the E3-word for the E2-vector with the new (flattened) control word. */
		e3.p_word = ATOMIC_XCH(e3_p->p_word, new_e3_word);
		X86_PAGEDIR_PREPARE_LOCK_RELEASE_WRITE(was);

		/* Sync if necessary. */
		p64_pagedir_sync_flattened_e2_vector(vec4, vec3);

		/* Free the old E2-vector
		 * NOTE: No need to Shoot-down anything for this, since the new,
		 *       flattened control word has identical meaning to the old
		 *       E2-vector. */
		page_freeone_for_paging(ppageof(e3.p_word & P64_PAGE_FVECTOR));
		if (vec4 < 256) {
			/* There's   still  one   thing  left   which  we're   able  to  flatten:
			 * The 512GiB E3-vector  pointed to  by `P64_PDIR_E4_IDENTITY[vec4]'  may
			 * not be mergeable into a 512GiB page (since those don't exist), however
			 * what  does exist are  fully empty pages, meaning  that if there aren't
			 * any  remaining mappings within  this range, then we  can merge it into
			 * a non-allocated page!
			 * Note  that this can  only be done  for user-space, since kernel-space
			 * must always have all of its E3-vectors preallocated (and its E4-words
			 * point to those  E3-vectors) in order  to facilitate the  kernel-share
			 * memory space found within the upper half of virtual memory. */
			u64 new_e4_word;
			union p64_pdir_e4 *e4_p, e4;
			e3_p = P64_PDIR_E3_IDENTITY[vec4];
			e4_p = &P64_PDIR_E4_IDENTITY[vec4];
			X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_WRITE(was);
			if (!P64_PDIR_E4_ISVEC3(ATOMIC_READ(e4_p->p_word))) {
				can_flatten = false; /* The E3-vector was already deleted */
			} else {
				can_flatten = p64_pagedir_can_flatten_e3_vector(e3_p, &new_e4_word);
			}
			if (!can_flatten) {
				X86_PAGEDIR_PREPARE_LOCK_RELEASE_WRITE(was);
				return;
			}
			e4.p_word = ATOMIC_XCH(e4_p->p_word, new_e4_word);
			X86_PAGEDIR_PREPARE_LOCK_RELEASE_WRITE(was);

			/* Sync if necessary. */
			p64_pagedir_sync_flattened_e3_vector(vec4);

			/* Free the old E3-vector
			 * NOTE: No need to Shoot-down anything for this, since the new,
			 *       flattened control word has identical meaning to the old
			 *       E3-vector. */
			page_freeone_for_paging(ppageof(e4.p_word & P64_PAGE_FVECTOR));
		}
	}
}

#ifdef NDEBUG
#define assert_prepared(addr, num_bytes) (void)0
#define assert_prepared_if(cond, addr, num_bytes) (void)0
#else /* NDEBUG */
PRIVATE NOBLOCK void
NOTHROW(FCALL p64_pagedir_assert_prepared)(VIRT void *addr,
                                           PAGEDIR_PAGEALIGNED VIRT void *range_addr,
                                           PAGEDIR_PAGEALIGNED size_t range_num_bytes) {
	uintptr_t word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX(addr);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	assertf(word & P64_PAGE_FPRESENT,
	        "Page at %p of range %p...%p isn't prepared\n"
	        "%p=P64_PDIR_E4_IDENTITY[%u] = %#" PRIxPTR " (!P64_PAGE_FPRESENT)\n",
	        addr, range_addr, (byte_t *)range_addr + range_num_bytes - 1,
	        &P64_PDIR_E4_IDENTITY[vec4].p_word, vec4, word);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	assertf(word & P64_PAGE_FPRESENT,
	        "Page at %p of range %p...%p isn't prepared\n"
	        "%p=P64_PDIR_E3_IDENTITY[%u][%u] = %#" PRIxPTR " (!P64_PAGE_FPRESENT)\n",
	        addr, range_addr, (byte_t *)range_addr + range_num_bytes - 1,
	        &P64_PDIR_E3_IDENTITY[vec4][vec3].p_word, vec4, vec3, word);
	assertf(!(word & P64_PAGE_F1GIB),
	        "Page at %p of range %p...%p isn't prepared\n"
	        "%p=P64_PDIR_E3_IDENTITY[%u][%u] = %#" PRIxPTR " (P64_PAGE_F1GIB)\n",
	        addr, range_addr, (byte_t *)range_addr + range_num_bytes - 1,
	        &P64_PDIR_E3_IDENTITY[vec4][vec3].p_word, vec4, vec3, word);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	assertf(word & P64_PAGE_FPRESENT,
	        "Page at %p of range %p...%p isn't prepared\n"
	        "%p=P64_PDIR_E2_IDENTITY[%u][%u][%u] = %#" PRIxPTR " (!P64_PAGE_FPRESENT)\n",
	        addr, range_addr, (byte_t *)range_addr + range_num_bytes - 1,
	        &P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word, vec4, vec3, vec2, word);
	assertf(!(word & P64_PAGE_F2MIB),
	        "Page at %p of range %p...%p isn't prepared\n"
	        "%p=P64_PDIR_E2_IDENTITY[%u][%u][%u] = %#" PRIxPTR " (P64_PAGE_F2MIB)\n",
	        addr, range_addr, (byte_t *)range_addr + range_num_bytes - 1,
	        &P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word, vec4, vec3, vec2, word);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	word = ATOMIC_READ(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word);
	assertf((word & P64_PAGE_FPREPARED) || P64_PDIR_E1_ISHINT(word),
	        "Page at %p of range %p...%p isn't prepared\n"
	        "%p=P64_PDIR_E1_IDENTITY[%u][%u][%u][%u] = %#" PRIxPTR "\n",
	        addr, range_addr, (byte_t *)range_addr + range_num_bytes - 1,
	        &P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word, vec4, vec3, vec2, vec1, word);
}
#define assert_prepared_if(cond, addr, num_bytes) \
	((cond) ? assert_prepared(addr, num_bytes) : (void)0)
LOCAL NOBLOCK void
NOTHROW(KCALL assert_prepared)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes) {
	size_t i;
	for (i = 0; i < num_bytes; i += PAGESIZE) {
		void *ptr = (byte_t *)addr + i;
		p64_pagedir_assert_prepared(ptr, addr, num_bytes);
	}
}
#endif /* !NDEBUG */


LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_impl_widen_v1)(unsigned int vec4,
                                                 unsigned int vec3,
                                                 unsigned int vec2,
                                                 unsigned int vec1_min,
                                                 unsigned int vec1_max) {
	bool result;
	assert(vec1_min <= vec1_max);
	result = p64_pagedir_prepare_impl_widen(vec4, vec3, vec2,
	                                        vec1_min,
	                                        (vec1_max - vec1_min) + 1);
	assert_prepared_if(result,
	                   P64_PDIR_VECADDR(vec4, vec3, vec2, vec1_min),
	                   (size_t)((vec1_max - vec1_min) + 1) * PAGESIZE);
	return result;
}

LOCAL NOBLOCK void
NOTHROW(FCALL p64_pagedir_unprepare_impl_flatten_v1)(unsigned int vec4,
                                                     unsigned int vec3,
                                                     unsigned int vec2,
                                                     unsigned int vec1_min,
                                                     unsigned int vec1_max) {
	assert(vec1_min <= vec1_max);
	p64_pagedir_unprepare_impl_flatten(vec4, vec3, vec2,
	                                   vec1_min,
	                                   (vec1_max - vec1_min) + 1);
}

LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_impl_widen_v2)(unsigned int vec4,
                                                 unsigned int vec3,
                                                 unsigned int vec2_min,
                                                 unsigned int vec2_max,
                                                 unsigned int vec1_min,
                                                 unsigned int vec1_max) {
	unsigned int vec2;
	assert(vec2_min <= vec2_max);
	if (vec2_min == vec2_max)
		return p64_pagedir_prepare_impl_widen_v1(vec4, vec3, vec2_min, vec1_min, vec1_max);
	if (!p64_pagedir_prepare_impl_widen_v1(vec4, vec3, vec2_min, vec1_min, 511))
		goto err;
	if (!p64_pagedir_prepare_impl_widen_v1(vec4, vec3, vec2_max, 0, vec1_max))
		goto err1;
	for (vec2 = vec2_min + 1; vec2 < vec2_max; ++vec2) {
		if (!p64_pagedir_prepare_impl_widen_v1(vec4, vec3, vec2, 0, 511))
			goto err2;
	}
	return true;
err2:
	while (vec2 > vec2_min + 1) {
		--vec2;
		p64_pagedir_unprepare_impl_flatten_v1(vec4, vec3, vec2, 0, 511);
	}
	p64_pagedir_unprepare_impl_flatten_v1(vec4, vec3, vec2_max, 0, vec1_max);
err1:
	p64_pagedir_unprepare_impl_flatten_v1(vec4, vec3, vec2_min, vec1_min, 511);
err:
	return false;
}

LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_impl_widen_v2_keep)(unsigned int vec4,
                                                      unsigned int vec3,
                                                      unsigned int vec2_min,
                                                      unsigned int vec2_max,
                                                      unsigned int vec1_min,
                                                      unsigned int vec1_max) {
	unsigned int vec2;
	assert(vec2_min <= vec2_max);
	if (vec2_min == vec2_max)
		return p64_pagedir_prepare_impl_widen_v1(vec4, vec3, vec2_min, vec1_min, vec1_max);
	if (!p64_pagedir_prepare_impl_widen_v1(vec4, vec3, vec2_min, vec1_min, 511))
		goto err;
	if (!p64_pagedir_prepare_impl_widen_v1(vec4, vec3, vec2_max, 0, vec1_max))
		goto err;
	for (vec2 = vec2_min + 1; vec2 < vec2_max; ++vec2) {
		if (!p64_pagedir_prepare_impl_widen_v1(vec4, vec3, vec2, 0, 511))
			goto err;
	}
	return true;
err:
	return false;
}

LOCAL NOBLOCK void
NOTHROW(FCALL p64_pagedir_unprepare_impl_flatten_v2)(unsigned int vec4,
                                                     unsigned int vec3,
                                                     unsigned int vec2_min,
                                                     unsigned int vec2_max,
                                                     unsigned int vec1_min,
                                                     unsigned int vec1_max) {
	unsigned int vec2;
	assert(vec2_min <= vec2_max);
	if (vec2_min == vec2_max) {
		p64_pagedir_unprepare_impl_flatten_v1(vec4,
		                                      vec3,
		                                      vec2_min,
		                                      vec1_min, vec1_max);
		return;
	}
	p64_pagedir_unprepare_impl_flatten_v1(vec4, vec3, vec2_min, vec1_min, 511);
	p64_pagedir_unprepare_impl_flatten_v1(vec4, vec3, vec2_max, 0, vec1_max);
	for (vec2 = vec2_min + 1; vec2 < vec2_max; ++vec2)
		p64_pagedir_unprepare_impl_flatten_v1(vec4, vec3, vec2, 0, 511);
}

LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_impl_widen_v3)(unsigned int vec4,
                                                 unsigned int vec3_min,
                                                 unsigned int vec3_max,
                                                 unsigned int vec2_min,
                                                 unsigned int vec2_max,
                                                 unsigned int vec1_min,
                                                 unsigned int vec1_max) {
	unsigned int vec3;
	assert(vec3_min <= vec3_max);
	if (vec3_min == vec3_max)
		return p64_pagedir_prepare_impl_widen_v2(vec4, vec3_min, vec2_min, vec2_max, vec1_min, vec1_max);
	if (!p64_pagedir_prepare_impl_widen_v2(vec4, vec3_min, vec2_min, 511, vec1_min, 511))
		goto err;
	if (!p64_pagedir_prepare_impl_widen_v2(vec4, vec3_max, 0, vec2_max, 0, vec1_max))
		goto err1;
	for (vec3 = vec3_min + 1; vec3 < vec3_max; ++vec3) {
		if (!p64_pagedir_prepare_impl_widen_v2(vec4, vec3, 0, 511, 0, 511))
			goto err2;
	}
	return true;
err2:
	while (vec3 > vec3_min + 1) {
		--vec3;
		p64_pagedir_unprepare_impl_flatten_v2(vec4, vec3, 0, 511, 0, 511);
	}
	p64_pagedir_unprepare_impl_flatten_v2(vec4, vec3_max, 0, vec2_max, 0, vec1_max);
err1:
	p64_pagedir_unprepare_impl_flatten_v2(vec4, vec3_min, vec2_min, 511, vec1_min, 511);
err:
	return false;
}

LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_impl_widen_v3_keep)(unsigned int vec4,
                                                      unsigned int vec3_min,
                                                      unsigned int vec3_max,
                                                      unsigned int vec2_min,
                                                      unsigned int vec2_max,
                                                      unsigned int vec1_min,
                                                      unsigned int vec1_max) {
	unsigned int vec3;
	assert(vec3_min <= vec3_max);
	if (vec3_min == vec3_max)
		return p64_pagedir_prepare_impl_widen_v2_keep(vec4, vec3_min, vec2_min, vec2_max, vec1_min, vec1_max);
	if (!p64_pagedir_prepare_impl_widen_v2_keep(vec4, vec3_min, vec2_min, 511, vec1_min, 511))
		goto err;
	if (!p64_pagedir_prepare_impl_widen_v2_keep(vec4, vec3_max, 0, vec2_max, 0, vec1_max))
		goto err;
	for (vec3 = vec3_min + 1; vec3 < vec3_max; ++vec3) {
		if (!p64_pagedir_prepare_impl_widen_v2_keep(vec4, vec3, 0, 511, 0, 511))
			goto err;
	}
	return true;
err:
	return false;
}

LOCAL NOBLOCK void
NOTHROW(FCALL p64_pagedir_unprepare_impl_flatten_v3)(unsigned int vec4,
                                                     unsigned int vec3_min,
                                                     unsigned int vec3_max,
                                                     unsigned int vec2_min,
                                                     unsigned int vec2_max,
                                                     unsigned int vec1_min,
                                                     unsigned int vec1_max) {
	unsigned int vec3;
	assert(vec3_min <= vec3_max);
	if (vec3_min == vec3_max) {
		p64_pagedir_unprepare_impl_flatten_v2(vec4,
		                                      vec3_min,
		                                      vec2_min, vec2_max,
		                                      vec1_min, vec1_max);
		return;
	}
	p64_pagedir_unprepare_impl_flatten_v2(vec4, vec3_min, vec2_min, 511, vec1_min, 511);
	p64_pagedir_unprepare_impl_flatten_v2(vec4, vec3_max, 0, vec2_max, 0, vec1_max);
	for (vec3 = vec3_min + 1; vec3 < vec3_max; ++vec3)
		p64_pagedir_unprepare_impl_flatten_v2(vec4, vec3, 0, 511, 0, 511);
}

LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_impl_widen_v4)(unsigned int vec4_min,
                                                 unsigned int vec4_max,
                                                 unsigned int vec3_min,
                                                 unsigned int vec3_max,
                                                 unsigned int vec2_min,
                                                 unsigned int vec2_max,
                                                 unsigned int vec1_min,
                                                 unsigned int vec1_max) {
	unsigned int vec4;
	assert(vec4_min <= vec4_max);
	if (vec4_min == vec4_max)
		return p64_pagedir_prepare_impl_widen_v3(vec4_min, vec3_min, vec3_max, vec2_min, vec2_max, vec1_min, vec1_max);
	if (!p64_pagedir_prepare_impl_widen_v3(vec4_min, vec3_min, 511, vec2_min, 511, vec1_min, 511))
		goto err;
	if (!p64_pagedir_prepare_impl_widen_v3(vec4_max, 0, vec3_max, 0, vec2_max, 0, vec1_max))
		goto err1;
	for (vec4 = vec4_min + 1; vec4 < vec4_max; ++vec4) {
		if (!p64_pagedir_prepare_impl_widen_v3(vec4, 0, 511, 0, 511, 0, 511))
			goto err2;
	}
	return true;
err2:
	while (vec4 > vec4_min + 1) {
		--vec4;
		p64_pagedir_unprepare_impl_flatten_v3(vec4, 0, 511, 0, 511, 0, 511);
	}
	p64_pagedir_unprepare_impl_flatten_v3(vec4_max, 0, vec3_max, 0, vec2_max, 0, vec1_max);
err1:
	p64_pagedir_unprepare_impl_flatten_v3(vec4_min, vec3_min, 511, vec2_min, 511, vec1_min, 511);
err:
	return false;
}

LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_impl_widen_v4_keep)(unsigned int vec4_min,
                                                      unsigned int vec4_max,
                                                      unsigned int vec3_min,
                                                      unsigned int vec3_max,
                                                      unsigned int vec2_min,
                                                      unsigned int vec2_max,
                                                      unsigned int vec1_min,
                                                      unsigned int vec1_max) {
	unsigned int vec4;
	assert(vec4_min <= vec4_max);
	if (vec4_min == vec4_max)
		return p64_pagedir_prepare_impl_widen_v3_keep(vec4_min, vec3_min, vec3_max, vec2_min, vec2_max, vec1_min, vec1_max);
	if (!p64_pagedir_prepare_impl_widen_v3_keep(vec4_min, vec3_min, 511, vec2_min, 511, vec1_min, 511))
		goto err;
	if (!p64_pagedir_prepare_impl_widen_v3_keep(vec4_max, 0, vec3_max, 0, vec2_max, 0, vec1_max))
		goto err;
	for (vec4 = vec4_min + 1; vec4 < vec4_max; ++vec4) {
		if (!p64_pagedir_prepare_impl_widen_v3_keep(vec4, 0, 511, 0, 511, 0, 511))
			goto err;
	}
	return true;
err:
	return false;
}

LOCAL NOBLOCK void
NOTHROW(FCALL p64_pagedir_unprepare_impl_flatten_v4)(unsigned int vec4_min,
                                                     unsigned int vec4_max,
                                                     unsigned int vec3_min,
                                                     unsigned int vec3_max,
                                                     unsigned int vec2_min,
                                                     unsigned int vec2_max,
                                                     unsigned int vec1_min,
                                                     unsigned int vec1_max) {
	unsigned int vec4;
	assert(vec4_min <= vec4_max);
	if (vec4_min == vec4_max) {
		p64_pagedir_unprepare_impl_flatten_v3(vec4_min,
		                                      vec3_min, vec3_max,
		                                      vec2_min, vec2_max,
		                                      vec1_min, vec1_max);
		return;
	}
	p64_pagedir_unprepare_impl_flatten_v3(vec4_min, vec3_min, 511, vec2_min, 511, vec1_min, 511);
	p64_pagedir_unprepare_impl_flatten_v3(vec4_max, 0, vec3_max, 0, vec2_max, 0, vec1_max);
	for (vec4 = vec4_min + 1; vec4 < vec4_max; ++vec4)
		p64_pagedir_unprepare_impl_flatten_v3(vec4, 0, 511, 0, 511, 0, 511);
}

/* Prepare the page directory for a future map() operation.
 * The full cycle of a single mapping then looks like this:
 * >> p64_pagedir_prepare(...);
 * >> p64_pagedir_map(...);
 * >> p64_pagedir_unmap(...);
 * >> p64_pagedir_unprepare(...);
 * @return: true:  Successfully allocated structures required for creating mappings.
 * @return: false: Insufficient physical memory to change mappings. */
INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepareone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	bool result;
	unsigned int vec4, vec3, vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	result = p64_pagedir_prepare_impl_widen(vec4, vec3, vec2, vec1, 1);
	PG_TRACE_PREPARE_IF(result, addr, PAGESIZE);
	assert_prepared_if(result, addr, PAGESIZE);
	return result;
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unprepareone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec4, vec3, vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	PG_TRACE_UNPREPARE(addr, PAGESIZE);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	p64_pagedir_unprepare_impl_flatten(vec4, vec3, vec2, vec1, 1);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes) {
	bool result;
	unsigned int vec4_min, vec4_max;
	unsigned int vec3_min, vec3_max;
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_max;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	if (!num_bytes)
		return true;
	if (num_bytes == 4096)
		return p64_pagedir_prepareone(addr);
	vec4_min = P64_PDIR_VEC4INDEX(addr);
	vec4_max = P64_PDIR_VEC4INDEX((byte_t *)addr + num_bytes - 1);
	vec3_min = P64_PDIR_VEC3INDEX(addr);
	vec3_max = P64_PDIR_VEC3INDEX((byte_t *)addr + num_bytes - 1);
	vec2_min = P64_PDIR_VEC2INDEX(addr);
	vec2_max = P64_PDIR_VEC2INDEX((byte_t *)addr + num_bytes - 1);
	vec1_min = P64_PDIR_VEC1INDEX(addr);
	vec1_max = P64_PDIR_VEC1INDEX((byte_t *)addr + num_bytes - 1);
	result = p64_pagedir_prepare_impl_widen_v4(vec4_min, vec4_max,
	                                           vec3_min, vec3_max,
	                                           vec2_min, vec2_max,
	                                           vec1_min, vec1_max);
	PG_TRACE_PREPARE_IF(result, addr, num_bytes);
	assert_prepared_if(result, addr, num_bytes);
	return result;
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unprepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes) {
	unsigned int vec4_min, vec4_max;
	unsigned int vec3_min, vec3_max;
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_max;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	if (!num_bytes)
		return;
	if (num_bytes == 4096) {
		p64_pagedir_unprepareone(addr);
		return;
	}
	PG_TRACE_UNPREPARE(addr, num_bytes);
	vec4_min = P64_PDIR_VEC4INDEX(addr);
	vec4_max = P64_PDIR_VEC4INDEX((byte_t *)addr + num_bytes - 1);
	vec3_min = P64_PDIR_VEC3INDEX(addr);
	vec3_max = P64_PDIR_VEC3INDEX((byte_t *)addr + num_bytes - 1);
	vec2_min = P64_PDIR_VEC2INDEX(addr);
	vec2_max = P64_PDIR_VEC2INDEX((byte_t *)addr + num_bytes - 1);
	vec1_min = P64_PDIR_VEC1INDEX(addr);
	vec1_max = P64_PDIR_VEC1INDEX((byte_t *)addr + num_bytes - 1);
	p64_pagedir_unprepare_impl_flatten_v4(vec4_min, vec4_max,
	                                      vec3_min, vec3_max,
	                                      vec2_min, vec2_max,
	                                      vec1_min, vec1_max);
}



#ifdef NDEBUG
#define p64_pagedir_assert_e1_word_prepared(vec4, vec3, vec2, vec1, e1_word) (void)0
#else /* NDEBUG */
LOCAL NOBLOCK void
NOTHROW(FCALL p64_pagedir_assert_e1_word_prepared)(unsigned int vec4,
                                                   unsigned int vec3,
                                                   unsigned int vec2,
                                                   unsigned int vec1,
                                                   u64 e1_word) {
	union p64_pdir_e4 e4;
	union p64_pdir_e3 e3;
	union p64_pdir_e2 e2;
	union p64_pdir_e1 e1;
	assert(vec4 < 512);
	assert(vec3 < 512);
	assert(vec2 < 512);
	assert(vec1 < 512);
	assertf((e1_word & P64_PAGE_FPREPARED) || P64_PDIR_E1_ISHINT(e1_word),
	        "Cannot set invalid E1 word %p for prepared entry",
	        (u64)e1_word);
	e4 = P64_PDIR_E4_IDENTITY[vec4];
	assertf(e4.p_word & P64_PAGE_FPRESENT,
	        "Page vector #%u for page %p...%p isn't allocated",
	        (unsigned int)vec4,
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1),
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1) + PAGESIZE - 1);
	e3 = P64_PDIR_E3_IDENTITY[vec4][vec3];
	assertf(e3.p_word & P64_PAGE_FPRESENT,
	        "Page vector #%u:%u for page %p...%p isn't allocated",
	        (unsigned int)vec4, (unsigned int)vec3,
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1),
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1) + PAGESIZE - 1);
	assertf(!(e3.p_word & P64_PAGE_F1GIB),
	        "Page %p...%p exists as a present 1GiB page #%u:%u",
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1),
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1) + PAGESIZE - 1,
	        (unsigned int)vec4, (unsigned int)vec3);
	e2 = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2];
	assertf(e2.p_word & P64_PAGE_FPRESENT,
	        "Page vector #%u:%u:%u for page %p...%p isn't allocated",
	        (unsigned int)vec4, (unsigned int)vec3, (unsigned int)vec2,
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1),
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1) + PAGESIZE - 1);
	assertf(!(e2.p_word & P64_PAGE_F2MIB),
	        "Page %p...%p exists as a present 2MiB page #%u:%u:%u",
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1),
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1) + PAGESIZE - 1,
	        (unsigned int)vec4, (unsigned int)vec3, (unsigned int)vec2);
	e1 = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1];
	assertf(e1.p_word & P64_PAGE_FPREPARED || P64_PDIR_E1_ISHINT(e1.p_word),
	        "Page %p...%p [vec4=%u,vec3=%u,vec2=%u,vec1=%u] hasn't been prepared",
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1),
	        (byte_t *)P64_PDIR_VECADDR(vec4, vec3, vec2, vec1) + PAGESIZE - 1,
	        vec4, vec3, vec2, vec1);
}
#endif /* !NDEBUG */


LOCAL NOBLOCK void
NOTHROW(FCALL p64_pagedir_set_e1_word)(unsigned int vec4,
                                       unsigned int vec3,
                                       unsigned int vec2,
                                       unsigned int vec1,
                                       u64 e1_word) {
	p64_pagedir_assert_e1_word_prepared(vec4, vec3, vec2, vec1, e1_word);
	COMPILER_WRITE_BARRIER();
	P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word = e1_word;
	COMPILER_WRITE_BARRIER();
}

LOCAL NOBLOCK void
NOTHROW(FCALL p64_pagedir_and_e1_word)(unsigned int vec4,
                                       unsigned int vec3,
                                       unsigned int vec2,
                                       unsigned int vec1,
                                       u64 e1_kept_bits_mask) {
	p64_pagedir_assert_e1_word_prepared(vec4, vec3, vec2, vec1, e1_kept_bits_mask);
	ATOMIC_AND(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word, e1_kept_bits_mask);
}

LOCAL NOBLOCK u64
NOTHROW(FCALL p64_pagedir_xch_e1_word)(unsigned int vec4,
                                       unsigned int vec3,
                                       unsigned int vec2,
                                       unsigned int vec1,
                                       u64 e1_word) {
	p64_pagedir_assert_e1_word_prepared(vec4, vec3, vec2, vec1, e1_word);
	return ATOMIC_XCH(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word, e1_word);
}


#ifdef NDEBUG
#define p64_pagedir_xch_e1_word_nochk p64_pagedir_xch_e1_word
#else /* NDEBUG */
LOCAL NOBLOCK u64
NOTHROW(FCALL p64_pagedir_xch_e1_word_nochk)(unsigned int vec4,
                                             unsigned int vec3,
                                             unsigned int vec2,
                                             unsigned int vec1,
                                             u64 e1_word) {
	return ATOMIC_XCH(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word, e1_word);
}
#endif /* !NDEBUG */


INTERN u64 p64_pageprot_table[0x40] = {
#define COMMON_PRESENT (P64_PAGE_FPREPARED | P64_PAGE_FACCESSED | P64_PAGE_FDIRTY | P64_PAGE_FPRESENT)
	[(0)]                                                                                                                               = P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_EXEC)]                                                                                                               = COMMON_PRESENT,
	[(PAGEDIR_PROT_WRITE)]                                                                                                              = COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                                          = COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_READ)]                                                                                                               = COMMON_PRESENT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                                                                           = COMMON_PRESENT,
	[(PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                                                                          = COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                      = COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PWT)]                                                                                                            = P64_PAGE_FPWT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_EXEC)]                                                                                        = P64_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE)]                                                                                       = P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                   = P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ)]                                                                                        = P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                                                    = P64_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                                                   = P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                               = P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD)]                                                                                                            = P64_PAGE_FPCD | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_EXEC)]                                                                                        = P64_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_WRITE)]                                                                                       = P64_PAGE_FPCD | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                   = P64_PAGE_FPCD | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ)]                                                                                        = P64_PAGE_FPCD | COMMON_PRESENT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                                                    = P64_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                                                   = P64_PAGE_FPCD | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                               = P64_PAGE_FPCD | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT)]                                                                                     = P64_PAGE_FPCD | P64_PAGE_FPWT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_EXEC)]                                                                 = P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE)]                                                                = P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                            = P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ)]                                                                 = P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                             = P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                            = P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                        = P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT)]                                                                                                            = P64_PAGE_FPAT_4KIB | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_EXEC)]                                                                                        = P64_PAGE_FPAT_4KIB | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_WRITE)]                                                                                       = P64_PAGE_FPAT_4KIB | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                                                   = P64_PAGE_FPAT_4KIB | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_READ)]                                                                                        = P64_PAGE_FPAT_4KIB | COMMON_PRESENT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                                                    = P64_PAGE_FPAT_4KIB | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                                                   = P64_PAGE_FPAT_4KIB | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                               = P64_PAGE_FPAT_4KIB | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT)]                                                                                     = P64_PAGE_FPAT_4KIB | P64_PAGE_FPWT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_EXEC)]                                                                 = P64_PAGE_FPAT_4KIB | P64_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE)]                                                                = P64_PAGE_FPAT_4KIB | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                            = P64_PAGE_FPAT_4KIB | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ)]                                                                 = P64_PAGE_FPAT_4KIB | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                             = P64_PAGE_FPAT_4KIB | P64_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                            = P64_PAGE_FPAT_4KIB | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                        = P64_PAGE_FPAT_4KIB | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD)]                                                                                     = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_EXEC)]                                                                 = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_WRITE)]                                                                = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                                            = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ)]                                                                 = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | COMMON_PRESENT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                                             = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                                            = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                        = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT)]                                                              = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | P64_PAGE_FPWT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_EXEC)]                                          = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE)]                                         = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)]                     = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ)]                                          = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_EXEC)]                      = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)]                     = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_PROT_X86_PAT | PAGEDIR_PROT_X86_PCD | PAGEDIR_PROT_X86_PWT | PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC)] = P64_PAGE_FPAT_4KIB | P64_PAGE_FPCD | P64_PAGE_FPWT | COMMON_PRESENT | P64_PAGE_FWRITE,
#undef COMMON_PRESENT
};

LOCAL NOBLOCK WUNUSED u64
NOTHROW(FCALL p64_pagedir_encode_4kib)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED PHYS physaddr_t phys,
                                       pagedir_prot_t prot) {
	u64 result;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	assertf(IS_ALIGNED(phys, 4096), "phys = %" PRIpN(__SIZEOF_PHYSADDR_T__), phys);
	assertf(!(prot & ~PAGEDIR_PROT_MASK),
	        "Invalid page protection: %#.4" PRIx16, prot);
	assertf(phys <= (physaddr_t)UINT64_C(0x000ffffffffff000),
	        "Address cannot be mapped under p64: %" PRIpN(__SIZEOF_PHYSADDR_T__),
	        phys);
	result  = (u64)phys;
#if PAGEDIR_PROT_MASK == 0x3f
	result |= p64_pageprot_table[prot];
#else /* PAGEDIR_PROT_MASK == 0x3f */
	result |= p64_pageprot_table[prot & 0x3f];
#endif /* PAGEDIR_PROT_MASK != 0x3f */

	/* All kernel pages have the GLOBAL bit set, and all user pages the USER bit. */
	if ((byte_t *)addr >= (byte_t *)KERNELSPACE_BASE) {
		result |= USED_P64_PAGE_FGLOBAL;
	} else {
		result |= P64_PAGE_FUSER;
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
NOTHROW(FCALL p64_pagedir_maphintone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	unsigned int vec4, vec3, vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	assertf(IS_ALIGNED((uintptr_t)hint, PAGEDIR_MAPHINT_ALIGNMENT), "hint = %p", hint);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1,
	                        (u64)(uintptr_t)hint |
	                        P64_PAGE_FISAHINT);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_maphint)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes,
                                   VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	size_t i;
	u64 e1_word;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	assertf(IS_ALIGNED((uintptr_t)hint, PAGEDIR_MAPHINT_ALIGNMENT), "hint = %p", hint);
	e1_word = (u64)(uintptr_t)hint | P64_PAGE_FISAHINT;
	for (i = 0; i < num_bytes; i += 4096) {
		unsigned int vec4, vec3, vec2, vec1;
		byte_t *effective_addr = (byte_t *)addr + i;
		vec4 = P64_PDIR_VEC4INDEX(effective_addr);
		vec3 = P64_PDIR_VEC3INDEX(effective_addr);
		vec2 = P64_PDIR_VEC2INDEX(effective_addr);
		vec1 = P64_PDIR_VEC1INDEX(effective_addr);
		p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1, e1_word);
	}
}

/* Return the hint of the given page, or NULL if no hint has been mapped. */
INTERN NOBLOCK WUNUSED void *
NOTHROW(FCALL p64_pagedir_gethint)(VIRT void *addr) {
	uintptr_t word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX(addr);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if unlikely(!(word & P64_PAGE_FPRESENT))
		return NULL; /* Not mapped */
	vec3 = P64_PDIR_VEC3INDEX(addr);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if unlikely(!(word & P64_PAGE_FPRESENT))
		return NULL; /* Not mapped */
	if unlikely(word & P64_PAGE_F1GIB)
		return NULL; /* 1GiB page */
	vec2 = P64_PDIR_VEC2INDEX(addr);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if unlikely(!(word & P64_PAGE_FPRESENT))
		return NULL; /* Not mapped */
	if unlikely(word & P64_PAGE_F2MIB)
		return NULL; /* 2MiB page */
	vec1 = P64_PDIR_VEC1INDEX(addr);
	word = ATOMIC_READ(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word);
	if unlikely(!P64_PDIR_E1_ISHINT(word))
		return NULL;
	return (void *)(uintptr_t)(word & (uintptr_t)P64_PAGE_FHINT);
}




/* Create/delete a page-directory mapping.
 * @param: prot: A set of `PAGEDIR_PROT_*' detailing how memory should be mapped. */
INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED PHYS physaddr_t phys,
                                  pagedir_prot_t prot) {
	u64 e1_word;
	unsigned int vec4, vec3, vec2, vec1;
	PG_TRACE_MAP(addr, PAGESIZE, phys, prot);
	e1_word = p64_pagedir_encode_4kib(addr, phys, prot);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1, e1_word);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes,
                               PAGEDIR_PAGEALIGNED PHYS physaddr_t phys,
                               pagedir_prot_t prot) {
	size_t i;
	u64 e1_word;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	PG_TRACE_MAP(addr, num_bytes, phys, prot);
	e1_word = p64_pagedir_encode_4kib(addr, phys, prot);
	for (i = 0; i < num_bytes; i += 4096) {
		unsigned int vec4, vec3, vec2, vec1;
		byte_t *effective_addr = (byte_t *)addr + i;
		vec4 = P64_PDIR_VEC4INDEX(effective_addr);
		vec3 = P64_PDIR_VEC3INDEX(effective_addr);
		vec2 = P64_PDIR_VEC2INDEX(effective_addr);
		vec1 = P64_PDIR_VEC1INDEX(effective_addr);
		p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1, e1_word);
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
INTERN NOBLOCK WUNUSED pagedir_pushval_t
NOTHROW(FCALL p64_pagedir_push_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED PHYS physaddr_t phys,
                                       pagedir_prot_t prot) {
	u64 e1_word, result;
	unsigned int vec4, vec3, vec2, vec1;
	PG_TRACE_MAP(addr, PAGESIZE, phys, prot);
	e1_word = p64_pagedir_encode_4kib(addr, phys, prot);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	result = p64_pagedir_xch_e1_word(vec4, vec3, vec2, vec1, e1_word);
	return result;
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_pop_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      pagedir_pushval_t backup) {
	u64 old_word;
	unsigned int vec4, vec3, vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	old_word = p64_pagedir_xch_e1_word_nochk(vec4, vec3, vec2, vec1, backup);
	if (old_word & P64_PAGE_FPRESENT)
		pagedir_syncone(addr); /* The old mapping was also present (explicitly refresh the page). */
}

/* Unmap pages from the given address range. (requires that the given area be prepared) */
INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unmapone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec4, vec3, vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	PG_TRACE_UNMAP(addr, PAGESIZE);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1,
	                        P64_PAGE_ABSENT | P64_PAGE_FPREPARED);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unmap)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes) {
	size_t i;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	PG_TRACE_UNMAP(addr, num_bytes);
	for (i = 0; i < num_bytes; i += 4096) {
		unsigned int vec4, vec3, vec2, vec1;
		byte_t *effective_addr = (byte_t *)addr + i;
		vec4 = P64_PDIR_VEC4INDEX(effective_addr);
		vec3 = P64_PDIR_VEC3INDEX(effective_addr);
		vec2 = P64_PDIR_VEC2INDEX(effective_addr);
		vec1 = P64_PDIR_VEC1INDEX(effective_addr);
		p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1,
		                        P64_PAGE_ABSENT | P64_PAGE_FPREPARED);
	}
}

/* Remove write-permissions from the given address range. (requires that the given area be prepared) */
INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_denywriteone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec4, vec3, vec2, vec1;
	PG_ASSERT_ALIGNED_ADDRESS(addr);
	vec4 = P64_PDIR_VEC3INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	p64_pagedir_and_e1_word(vec4, vec3, vec2, vec1, ~P64_PAGE_FWRITE);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_denywrite)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes) {
	size_t i;
	PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes);
	for (i = 0; i < num_bytes; i += 4096) {
		unsigned int vec4, vec3, vec2, vec1;
		byte_t *effective_addr = (byte_t *)addr + i;
		vec4 = P64_PDIR_VEC4INDEX(effective_addr);
		vec3 = P64_PDIR_VEC3INDEX(effective_addr);
		vec2 = P64_PDIR_VEC2INDEX(effective_addr);
		vec1 = P64_PDIR_VEC1INDEX(effective_addr);
		p64_pagedir_and_e1_word(vec4, vec3, vec2, vec1, ~P64_PAGE_FWRITE);
	}
}


/* Unmap the entirety of user-space.
 * NOTE: Unlike all other unmap() functions, this one guaranties that it
 *       can perform the task without  needing to allocate more  memory! */
INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unmap_userspace)(void) {
	unsigned int free_count = 0;
	unsigned int vec4;
	u64 free_pages[64];
#define FREEPAGE(pageptr)                                                        \
	do {                                                                         \
		if unlikely(free_count >= COMPILER_LENOF(free_pages)) {                  \
			/* Must  sync  memory  before  we  can  actually  delete  pages.     \
			 * Otherwise, other CPUs may still  be using the mappings  after     \
			 * they've already been re-designated as general-purpose RAM, at     \
			 * which point they'd start reading garbage, or corrupt pointers. */ \
			pagedir_syncall_smp();                                               \
			page_freeone_for_paging(pageptr);                                    \
			do {                                                                 \
				--free_count;                                                    \
				page_freeone_for_paging((physpage_t)free_pages[free_count]);     \
			} while (free_count);                                                \
		} else {                                                                 \
			free_pages[free_count++] = (u64)(pageptr);                           \
		}                                                                        \
	}	__WHILE0

	/* Map all pages before the share-segment as absent. */
	for (vec4 = 0; vec4 < 256; ++vec4) {
		union p64_pdir_e4 e4;
		unsigned int vec3;
		e4 = P64_PDIR_E4_IDENTITY[vec4];
		if (!P64_PDIR_E4_ISVEC3(e4.p_word))
			continue;
		for (vec3 = 0; vec3 < 512; ++vec3) {
			union p64_pdir_e3 e3;
			unsigned int vec2;
			e3 = P64_PDIR_E3_IDENTITY[vec4][vec3];
			if (!P64_PDIR_E3_ISVEC2(e3.p_word))
				continue;
			for (vec2 = 0; vec2 < 512; ++vec2) {
				union p64_pdir_e2 e2;
				e2 = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2];
				if (!P64_PDIR_E2_ISVEC1(e2.p_word))
					continue;
				ATOMIC_WRITE(P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word, P64_PAGE_ABSENT);
				FREEPAGE((physpage_t)((e2.p_word & P64_PAGE_FVECTOR) / 4096));
			}
			ATOMIC_WRITE(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word, P64_PAGE_ABSENT);
			FREEPAGE((physpage_t)((e3.p_word & P64_PAGE_FVECTOR) / 4096));
		}
		ATOMIC_WRITE(P64_PDIR_E4_IDENTITY[vec4].p_word, P64_PAGE_ABSENT);
		FREEPAGE((physpage_t)((e4.p_word & P64_PAGE_FVECTOR) / 4096));
	}

	/* Free any remaining pages. */
	if (free_count) {
		pagedir_syncall_smp();
		do {
			--free_count;
			page_freeone_for_paging((physpage_t)free_pages[free_count]);
		} while (free_count);
	}
#undef FREEPAGE
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unmap_userspace_nosync)(void) {
	unsigned int vec4;

	/* Map all pages before the share-segment as absent. */
	for (vec4 = 0; vec4 < 256; ++vec4) {
		union p64_pdir_e4 e4;
		unsigned int vec3;
		e4 = P64_PDIR_E4_IDENTITY[vec4];
		if (!P64_PDIR_E4_ISVEC3(e4.p_word))
			continue;
		for (vec3 = 0; vec3 < 512; ++vec3) {
			union p64_pdir_e3 e3;
			unsigned int vec2;
			e3 = P64_PDIR_E3_IDENTITY[vec4][vec3];
			if (!P64_PDIR_E3_ISVEC2(e3.p_word))
				continue;
			for (vec2 = 0; vec2 < 512; ++vec2) {
				union p64_pdir_e2 e2;
				e2 = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2];
				if (!P64_PDIR_E2_ISVEC1(e2.p_word))
					continue;
				ATOMIC_WRITE(P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word, P64_PAGE_ABSENT);
				page_freeone_for_paging((physpage_t)((e2.p_word & P64_PAGE_FVECTOR) / 4096));
			}
			ATOMIC_WRITE(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word, P64_PAGE_ABSENT);
			page_freeone_for_paging((physpage_t)((e3.p_word & P64_PAGE_FVECTOR) / 4096));
		}
		ATOMIC_WRITE(P64_PDIR_E4_IDENTITY[vec4].p_word, P64_PAGE_ABSENT);
		page_freeone_for_paging((physpage_t)((e4.p_word & P64_PAGE_FVECTOR) / 4096));
	}
}


/* Translate a virtual address into its physical counterpart. */
INTERN NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(1) PHYS physaddr_t
NOTHROW(FCALL p64_pagedir_translate)(VIRT void const *addr) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	assertf(word & P64_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	assertf(word & P64_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	if unlikely(word & P64_PAGE_F1GIB)
		return (physaddr_t)((word & P64_PAGE_FADDR_1GIB) | P64_PDIR_PAGEINDEX_1GIB(addr));
	vec2 = P64_PDIR_VEC2INDEX(addr);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	assertf(word & P64_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	if unlikely(word & P64_PAGE_F2MIB)
		return (physaddr_t)((word & P64_PAGE_FADDR_2MIB) | P64_PDIR_PAGEINDEX_2MIB(addr));
	vec1 = P64_PDIR_VEC1INDEX(addr);
	word = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word;
	assertf(word & P64_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	return (physaddr_t)((word & P64_PAGE_FADDR_4KIB) | P64_PDIR_PAGEINDEX_4KIB(addr));
}

/* Check if the given page is mapped. */
INTERN NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(1) bool
NOTHROW(FCALL p64_pagedir_ismapped)(VIRT void const *addr) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX(addr);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	vec3 = P64_PDIR_VEC3INDEX(addr);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F1GIB)
		return true;
	vec2 = P64_PDIR_VEC2INDEX(addr);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F2MIB)
		return true;
	vec1 = P64_PDIR_VEC1INDEX(addr);
	word = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word;
	return (word & P64_PAGE_FPRESENT) != 0;
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL p64_pagedir_iswritable)(VIRT void *addr) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX(addr);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	vec3 = P64_PDIR_VEC3INDEX(addr);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F1GIB)
		return (word & P64_PAGE_FWRITE) != 0;
	vec2 = P64_PDIR_VEC2INDEX(addr);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F2MIB)
		return (word & P64_PAGE_FWRITE) != 0;
	vec1 = P64_PDIR_VEC1INDEX(addr);
	word = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word;
	return (word & (P64_PAGE_FPRESENT | P64_PAGE_FWRITE)) ==
	       /*   */ (P64_PAGE_FPRESENT | P64_PAGE_FWRITE);
}

INTERN NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(1) bool
NOTHROW(FCALL p64_pagedir_isuseraccessible)(VIRT void const *addr) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX(addr);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	vec3 = P64_PDIR_VEC3INDEX(addr);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F1GIB)
		return (word & P64_PAGE_FUSER) != 0;
	vec2 = P64_PDIR_VEC2INDEX(addr);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F2MIB)
		return (word & P64_PAGE_FUSER) != 0;
	vec1 = P64_PDIR_VEC1INDEX(addr);
	word = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word;
	return (word & (P64_PAGE_FPRESENT | P64_PAGE_FUSER)) ==
	       /*   */ (P64_PAGE_FPRESENT | P64_PAGE_FUSER);
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL p64_pagedir_isuserwritable)(VIRT void *addr) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX(addr);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	vec3 = P64_PDIR_VEC3INDEX(addr);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F1GIB)
		return (word & (P64_PAGE_FUSER | P64_PAGE_FWRITE)) ==
		       /*   */ (P64_PAGE_FUSER | P64_PAGE_FWRITE);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F2MIB)
		return (word & (P64_PAGE_FUSER | P64_PAGE_FWRITE)) ==
		       /*   */ (P64_PAGE_FUSER | P64_PAGE_FWRITE);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	word = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word;
	return (word & (P64_PAGE_FPRESENT | P64_PAGE_FUSER | P64_PAGE_FWRITE)) ==
	       /*   */ (P64_PAGE_FPRESENT | P64_PAGE_FUSER | P64_PAGE_FWRITE);
}

INTERN NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL p64_pagedir_haschanged)(VIRT void *addr) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	/* TODO: Figure out a better design for this function
	 *       The current system is written under the assumption that 4MiB pages don't exist... */
	vec4 = P64_PDIR_VEC4INDEX(addr);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	vec3 = P64_PDIR_VEC3INDEX(addr);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if (word & P64_PAGE_F1GIB)
		return true; /* 1GiB pages aren't supported for this purpose */
	vec2 = P64_PDIR_VEC2INDEX(addr);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F2MIB)
		return true; /* 4MiB pages aren't supported for this purpose */
	vec1 = P64_PDIR_VEC1INDEX(addr);
	word = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word;
	return (word & (P64_PAGE_FDIRTY | P64_PAGE_FPRESENT)) ==
	       /*   */ (P64_PAGE_FDIRTY | P64_PAGE_FPRESENT);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unsetchanged)(VIRT void *addr) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	/* TODO: Figure out a better design for this function
	 *       The current system is written under the assumption that 4MiB pages don't exist... */
	vec4 = P64_PDIR_VEC4INDEX(addr);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return;
	vec3 = P64_PDIR_VEC3INDEX(addr);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return;
	if (word & P64_PAGE_F1GIB)
		return; /* 1GiB pages aren't supported for this purpose */
	vec2 = P64_PDIR_VEC2INDEX(addr);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return;
	if unlikely(word & P64_PAGE_F2MIB)
		return; /* 4MiB pages aren't supported for this purpose */
	vec1 = P64_PDIR_VEC1INDEX(addr);
	do {
		/* Allow corruption, since we do our own CMPXCH() below. */
		word = ATOMIC_READ(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word);
		if unlikely((word & (P64_PAGE_FPRESENT | P64_PAGE_FDIRTY)) ==
		            /*   */ (P64_PAGE_FPRESENT | P64_PAGE_FDIRTY))
			break;
	} while (!ATOMIC_CMPXCH_WEAK(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word,
	                             word, word & ~P64_PAGE_FDIRTY));
}


DEFINE_PUBLIC_ALIAS(pagedir_init, p64_pagedir_init);
DEFINE_PUBLIC_ALIAS(pagedir_fini, p64_pagedir_fini);
DEFINE_PUBLIC_ALIAS(pagedir_unmap_userspace, p64_pagedir_unmap_userspace);
DEFINE_PUBLIC_ALIAS(pagedir_unmap_userspace_nosync, p64_pagedir_unmap_userspace_nosync);
DEFINE_PUBLIC_ALIAS(pagedir_translate, p64_pagedir_translate);
DEFINE_PUBLIC_ALIAS(pagedir_prepareone, p64_pagedir_prepareone);
DEFINE_PUBLIC_ALIAS(pagedir_unprepareone, p64_pagedir_unprepareone);
DEFINE_PUBLIC_ALIAS(pagedir_prepare, p64_pagedir_prepare);
DEFINE_PUBLIC_ALIAS(pagedir_unprepare, p64_pagedir_unprepare);
DEFINE_PUBLIC_ALIAS(pagedir_maphintone, p64_pagedir_maphintone);
DEFINE_PUBLIC_ALIAS(pagedir_maphint, p64_pagedir_maphint);
DEFINE_PUBLIC_ALIAS(pagedir_gethint, p64_pagedir_gethint);
DEFINE_PUBLIC_ALIAS(pagedir_mapone, p64_pagedir_mapone);
DEFINE_PUBLIC_ALIAS(pagedir_map, p64_pagedir_map);
DEFINE_PUBLIC_ALIAS(pagedir_push_mapone, p64_pagedir_push_mapone);
DEFINE_PUBLIC_ALIAS(pagedir_pop_mapone, p64_pagedir_pop_mapone);
DEFINE_PUBLIC_ALIAS(pagedir_unmapone, p64_pagedir_unmapone);
DEFINE_PUBLIC_ALIAS(pagedir_unmap, p64_pagedir_unmap);
DEFINE_PUBLIC_ALIAS(pagedir_denywriteone, p64_pagedir_denywriteone);
DEFINE_PUBLIC_ALIAS(pagedir_denywrite, p64_pagedir_denywrite);
DEFINE_PUBLIC_ALIAS(pagedir_ismapped, p64_pagedir_ismapped);
DEFINE_PUBLIC_ALIAS(pagedir_iswritable, p64_pagedir_iswritable);
DEFINE_PUBLIC_ALIAS(pagedir_isuseraccessible, p64_pagedir_isuseraccessible);
DEFINE_PUBLIC_ALIAS(pagedir_isuserwritable, p64_pagedir_isuserwritable);
DEFINE_PUBLIC_ALIAS(pagedir_haschanged, p64_pagedir_haschanged);
DEFINE_PUBLIC_ALIAS(pagedir_unsetchanged, p64_pagedir_unsetchanged);


INTERN ATTR_FREETEXT ATTR_CONST WUNUSED NONNULL((1)) union p64_pdir_e1 *
NOTHROW(FCALL x86_get_cpu_iob_pointer_p64)(struct cpu const *__restrict self) {
	union p64_pdir_e1 *e1_pointer;
	uintptr_t iobp;
	iobp       = (uintptr_t)&FORCPU(self, thiscpu_x86_iob[0]);
	e1_pointer = &P64_PDIR_E1_IDENTITY[P64_PDIR_VEC4INDEX(iobp)]
	                                  [P64_PDIR_VEC3INDEX(iobp)]
	                                  [P64_PDIR_VEC2INDEX(iobp)]
	                                  [P64_PDIR_VEC1INDEX(iobp)];
	return e1_pointer;
}

INTDEF byte_t const x86_pagedir_syncall_cr3[];
INTDEF byte_t x86_pagedir_syncall_cr3_size[];
INTDEF byte_t const x86_pagedir_syncall_cr4[];
INTDEF byte_t x86_pagedir_syncall_cr4_size[];

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_paging)(void) {
	/* Configure paging */
	if (!HAVE_PAGE_GLOBAL_BIT)
		used_pxx_page_fglobal = 0;
	if (!HAVE_EXECUTE_DISABLE) {
		unsigned int i;
		for (i = 0; i < COMPILER_LENOF(p64_pageprot_table); ++i)
			p64_pageprot_table[i] &= ~P64_PAGE_FNOEXEC;
	}
	if (!HAVE_PAGE_ATTRIBUTE_TABLE) {
		/* Disable PAT bits. */
		unsigned int i;
		for (i = 0; i < COMPILER_LENOF(p64_pageprot_table); ++i)
			p64_pageprot_table[i] &= ~(P64_PAGE_FPWT | P64_PAGE_FPCD | P64_PAGE_FPAT_4KIB);
	}

	/* Check if we must re-write our implementation of `pagedir_syncall()'.
	 * Currently, it looks like this:
	 * >> movq   $2, %rax
	 * >> invpcid (%rax), %rax // The first operand is ignored.
	 * >> ret */
	if (!HAVE_PAGE_GLOBAL_BIT) {
		/* If global TLBs don't exist, we can simply use the mov-to-cr3 trick to flush TLBs */
		/* Also: Since global TLBs don't exist, we can re-write `x86_pagedir_syncall_maybe_global'
		 *       to  always  unconditionally  reload  cr3  with  the  same  code  we  already  use
		 *       for `pagedir_syncall' */
		memcpy((void *)&pagedir_syncall, x86_pagedir_syncall_cr3, (size_t)x86_pagedir_syncall_cr3_size);
		memcpy((void *)&x86_pagedir_syncall_maybe_global, x86_pagedir_syncall_cr3, (size_t)x86_pagedir_syncall_cr3_size);
	} else if (!HAVE_INSTR_INVPCID) {
		/* From `4.10.4.1     Operations that Invalidate TLBs and Paging-Structure Caches'
		 *  `MOV to CR4. The behavior of the instruction depends on the bits being modified:'
		 *   `The instruction invalidates all TLB entries (including global entries) and all entries
		 *    in all paging-structure caches (for all PCIDs) if ... it changes the value of CR4.PGE ...' */
		/* In other words: Toggling the PGE bit twice will get rid of all global TLBs */
		memcpy((void *)&pagedir_syncall, x86_pagedir_syncall_cr4, (size_t)x86_pagedir_syncall_cr4_size);
	}

	/* Initialize the `bootcpu.thiscpu_x86_iobnode_pagedir_identity' pointer. */
	FORCPU(&bootcpu, thiscpu_x86_iobnode_pagedir_identity) = x86_get_cpu_iob_pointer_p64(&bootcpu);
}



#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

/* NOTE: This function must do its own tracing of continuous page ranges.
 *       The caller is may not necessary ensure that the function is only
 *       called once for a single, continuous range.
 * @param: word: The page directory starting control word.
 *               When `P64_PAGE_FPRESENT' is set, refers to a mapped page range
 *               When `P64_PAGE_FISAHINT' is set, refers to a mapped page range */
typedef void (KCALL *p64_enumfun_t)(void *arg, void *start, size_t num_bytes, u64 word);

#define P64_PAGE_CASCADING \
	(P64_PAGE_FPRESENT | P64_PAGE_FWRITE | P64_PAGE_FUSER | P64_PAGE_FNOEXEC)

#define P64_PAGE_FPAT P64_PAGE_FPAT_4KIB
/* Convert an En | n >= 2 word into an E1 word */
PRIVATE ATTR_DBGTEXT ATTR_CONST WUNUSED u64
NOTHROW(KCALL p64_convert_en_to_e1)(u64 word) {
	assert(word & P64_PAGE_FPRESENT);
	assert(word & P64_PAGE_F2MIB);
	word &= ~P64_PAGE_F2MIB;
#if P64_PAGE_FPAT_4KIB != P64_PAGE_FPAT_2MIB
	if (word & P64_PAGE_FPAT_2MIB) {
		word &= ~P64_PAGE_FPAT_2MIB;
		word |= P64_PAGE_FPAT_4KIB;
	}
#endif /* P64_PAGE_FPAT_4KIB != P64_PAGE_FPAT_2MIB */
	return word;
}

#define P64_PDIR_E1_ISUSED(e1_word) (((e1_word) & (P64_PAGE_FPRESENT | P64_PAGE_FISAHINT | P64_PAGE_FPREPARED)) != 0)
PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
p64_enum_e1(p64_enumfun_t func, void *arg,
            unsigned int vec4,
            unsigned int vec3,
            unsigned int vec2, u64 mask) {
	unsigned int vec1, laststart = 0;
	union p64_pdir_e1 *e1 = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2];
	union p64_pdir_e1 lastword = e1[0];
	lastword.p_word ^= P64_PAGE_FNOEXEC;
	lastword.p_word &= mask;
	for (vec1 = 1; vec1 < 512; ++vec1) {
		union p64_pdir_e1 word;
		word = e1[vec1];
		word.p_word ^= P64_PAGE_FNOEXEC;
		word.p_word &= mask;
		if (P64_PDIR_E1_IS1KIB(word.p_4kib.d_present)) {
			union p64_pdir_e1 expected_word;
			expected_word = lastword;
			expected_word.p_word += (u64)(vec1 - laststart) * 4096;
			if (word.p_word != expected_word.p_word) {
docall:
				if (P64_PDIR_E1_ISUSED(lastword.p_word)) {
					(*func)(arg, P64_PDIR_VECADDR(vec4, vec3, vec2, laststart),
					        (size_t)(vec1 - laststart) * 4096,
					        lastword.p_word ^ P64_PAGE_FNOEXEC);
				}
				laststart = vec1;
				lastword  = word;
			}
#if 0
		} else if (P64_PDIR_E1_ISHINT(word.p_word)) {
			if (word.p_word != lastword.p_word)
				goto docall;
#endif
		} else {
			if (word.p_word != lastword.p_word)
				goto docall;
		}
	}
	if (P64_PDIR_E1_ISUSED(lastword.p_word)) {
		(*func)(arg, P64_PDIR_VECADDR(vec4, vec3, vec2, laststart),
		        (size_t)(512 - laststart) * 4096,
		        lastword.p_word ^ P64_PAGE_FNOEXEC);
	}
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
p64_enum_e2(p64_enumfun_t func, void *arg,
            unsigned int vec4,
            unsigned int vec3, u64 mask) {
	unsigned int vec2 = 1, laststart = 0;
	union p64_pdir_e2 *e2 = P64_PDIR_E2_IDENTITY[vec4][vec3];
	union p64_pdir_e2 word, lastword = e2[0];
	lastword.p_word ^= P64_PAGE_FNOEXEC;
	lastword.p_word &= (mask ^ P64_PAGE_FNOEXEC);
	if (P64_PDIR_E2_ISVEC1(lastword.p_word)) {
		word = lastword;
		vec2 = 0;
		goto do_enum_e1;
	}
	for (; vec2 < 512; ++vec2) {
		word = e2[vec2];
		word.p_word ^= P64_PAGE_FNOEXEC;
		word.p_word &= mask;
		if (P64_PDIR_E2_ISVEC1(word.p_word)) {
			if (P64_PDIR_E2_IS2MIB(lastword.p_word)) {
				(*func)(arg, P64_PDIR_VECADDR(vec4, vec3, laststart, 0),
				        (size_t)(vec2 - laststart) * 4096 * 512,
				        p64_convert_en_to_e1(lastword.p_word & ~(u64)0x1ff000) ^
				        P64_PAGE_FNOEXEC);
			}
do_enum_e1:
			p64_enum_e1(func, arg, vec4, vec3, vec2,
			            word.p_word | ~(u64)P64_PAGE_CASCADING);
			laststart = vec2;
			lastword  = word;
		} else if (P64_PDIR_E2_IS2MIB(word.p_word)) {
			union p64_pdir_e2 expected_word;
			expected_word = lastword;
			expected_word.p_word += (u64)(vec2 - laststart) * 4096 * 512;
			if (word.p_word != expected_word.p_word) {
docall:
				if (P64_PDIR_E2_IS2MIB(lastword.p_word)) {
					(*func)(arg, P64_PDIR_VECADDR(vec4, vec3, laststart, 0),
					        (size_t)(vec2 - laststart) * 4096 * 512,
					        p64_convert_en_to_e1(lastword.p_word & ~(u64)0x1ff000) ^
					        P64_PAGE_FNOEXEC);
				}
				laststart = vec2;
				lastword  = word;
			}
		} else {
			if (word.p_word != lastword.p_word)
				goto docall;
		}
	}
	if (P64_PDIR_E2_IS2MIB(lastword.p_word)) {
		(*func)(arg, P64_PDIR_VECADDR(vec4, vec3, laststart, 0),
		        (size_t)(512 - laststart) * 4096 * 512,
		        p64_convert_en_to_e1(lastword.p_word & ~(u64)0x1ff000) ^
		        P64_PAGE_FNOEXEC);
	}
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
p64_enum_e3(p64_enumfun_t func, void *arg,
            unsigned int vec4, u64 mask) {
	unsigned int vec3 = 1, laststart = 0;
	union p64_pdir_e3 *e3 = P64_PDIR_E3_IDENTITY[vec4];
	union p64_pdir_e3 word, lastword = e3[0];
	lastword.p_word ^= P64_PAGE_FNOEXEC;
	lastword.p_word &= mask;
	if (P64_PDIR_E3_ISVEC2(lastword.p_word)) {
		word = lastword;
		vec3 = 0;
		goto do_enum_e2;
	}
	for (; vec3 < 512; ++vec3) {
		word = e3[vec3];
		word.p_word ^= P64_PAGE_FNOEXEC;
		word.p_word &= mask;
		if (P64_PDIR_E3_ISVEC2(word.p_word)) {
			if (P64_PDIR_E3_IS1GIB(lastword.p_word)) {
				(*func)(arg, P64_PDIR_VECADDR(vec4, laststart, 0, 0),
				        (size_t)(vec3 - laststart) * 4096 * 512 * 512,
				        p64_convert_en_to_e1(lastword.p_word & ~(u64)0x3ffff000) ^
				        P64_PAGE_FNOEXEC);
			}
do_enum_e2:
			p64_enum_e2(func, arg, vec4, vec3,
			            word.p_word | ~(u64)P64_PAGE_CASCADING);
			laststart = vec3;
			lastword  = word;
		} else if (P64_PDIR_E2_IS2MIB(word.p_word)) {
			union p64_pdir_e3 expected_word;
			expected_word = lastword;
			expected_word.p_word += (u64)(vec3 - laststart) * 4096 * 512 * 512;
			if (word.p_word != expected_word.p_word) {
docall:
				if (P64_PDIR_E3_IS1GIB(lastword.p_word)) {
					(*func)(arg, P64_PDIR_VECADDR(vec4, laststart, 0, 0),
					        (size_t)(vec3 - laststart) * 4096 * 512 * 512,
					        p64_convert_en_to_e1(lastword.p_word & ~(u64)0x3ffff000) ^
					        P64_PAGE_FNOEXEC);
				}
				laststart = vec3;
				lastword  = word;
			}
		} else {
			if (word.p_word != lastword.p_word)
				goto docall;
		}
	}
	if (P64_PDIR_E3_IS1GIB(lastword.p_word)) {
		(*func)(arg, P64_PDIR_VECADDR(vec4, laststart, 0, 0),
		        (size_t)(512 - laststart) * 4096 * 512 * 512,
		        p64_convert_en_to_e1(lastword.p_word & ~(u64)0x3ffff000) ^
		        P64_PAGE_FNOEXEC);
	}
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
p64_enum_e4(p64_enumfun_t func, void *arg, unsigned int vec4_max) {
	unsigned int vec4;
	union p64_pdir_e4 *e4 = P64_PDIR_E4_IDENTITY;
	for (vec4 = 0; vec4 < vec4_max; ++vec4) {
		union p64_pdir_e4 word;
		word = e4[vec4];
		if (P64_PDIR_E4_ISVEC3(word.p_word)) {
			word.p_word ^= P64_PAGE_FNOEXEC;
			p64_enum_e3(func, arg, vec4,
			            word.p_word | ~(u64)P64_PAGE_CASCADING);
		}
	}
}

struct p64_enumdat {
	void  *ed_prevstart;
	size_t ed_prevsize;
	u64    ed_prevword;
	u64    ed_mask;
	size_t ed_identcnt;
	bool   ed_skipident;
};

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
p64_printident(struct p64_enumdat *__restrict data) {
	dbg_printf(DBGSTR(AC_WHITE("%p") "-" AC_WHITE("%p") ": " AC_WHITE("%" PRIuSIZ) " identity mappings\n"),
	           (byte_t *)P64_MMAN_KERNEL_PDIR_IDENTITY_BASE,
	           (byte_t *)P64_MMAN_KERNEL_PDIR_IDENTITY_BASE + P64_MMAN_KERNEL_PDIR_IDENTITY_SIZE - 1,
	           data->ed_identcnt);
	data->ed_identcnt = 0;
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
p64_doenum(struct p64_enumdat *__restrict data,
           void *start, size_t num_bytes, u64 word, u64 mask) {
	assert((word & P64_PAGE_FPRESENT) || (word & P64_PAGE_FISAHINT));
	if (data->ed_identcnt) {
		p64_printident(data);
		return;
	}
	dbg_printf(DBGSTR(AC_WHITE("%p") "-" AC_WHITE("%p")),
	           start, (byte_t *)start + num_bytes - 1);
	if (word & P64_PAGE_FPRESENT) {
		size_t indent;
		dbg_printf(DBGSTR(": " AC_WHITE("%p") "+" AC_FG_WHITE),
		           word & P64_PAGE_FADDR_4KIB);
		if ((num_bytes >= ((u64)1024 * 1024 * 1024 * 1024)) &&
		    (num_bytes % ((u64)1024 * 1024 * 1024 * 1024)) == 0) {
			indent = dbg_printf(DBGSTR("%" PRIuSIZ AC_DEFATTR "TiB"),
			                    (size_t)(num_bytes / ((u64)1024 * 1024 * 1024 * 1024)));
		} else if ((num_bytes >= ((u64)1024 * 1024 * 1024)) &&
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
				{ P64_PAGE_FNOEXEC, 'x' },
				{ P64_PAGE_FWRITE, 'w' },
				{ P64_PAGE_FUSER, 'u' },
				{ P64_PAGE_FGLOBAL, 'g' },
				{ P64_PAGE_FACCESSED, 'a' },
				{ P64_PAGE_FDIRTY, 'd' },
				{ P64_PAGE_FPREPARED, 'p' },
			};
			dbg_color_t oldcolor;
			unsigned int i;
			oldcolor = dbg_getcolor();
			word ^= P64_PAGE_FNOEXEC;
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
		if (mask & (P64_PAGE_FPAT | P64_PAGE_FPWT | P64_PAGE_FPCD)) {
			u8 state = 0;
			if (word & P64_PAGE_FPWT)
				state |= 1;
			if (word & P64_PAGE_FPCD)
				state |= 2;
			if (word & P64_PAGE_FPAT)
				state |= 4;
			dbg_printf(DBGSTR("][" AC_FG_WHITE "%x"), (unsigned int)state);
		}
		dbg_print(DBGSTR(AC_DEFATTR "]\n"));
	} else {
		dbg_printf(DBGSTR(": hint@" AC_WHITE("%p") "\n"),
		           (void *)(word & P64_PAGE_FHINT));
	}
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL
p64_enumfun(void *arg, void *start, size_t num_bytes, u64 word) {
	struct p64_enumdat *data;
	data = (struct p64_enumdat *)arg;
	word &= data->ed_mask; /* Mask relevant bits. */
	if (!((word & P64_PAGE_FPRESENT) || (word & P64_PAGE_FISAHINT)))
		return;
	if ((byte_t *)data->ed_prevstart + data->ed_prevsize == start) {
		u64 expected_word;
		if (!data->ed_prevsize) {
			expected_word = 0;
		} else if (word & P64_PAGE_FPRESENT) {
			expected_word = data->ed_prevword + data->ed_prevsize;
		} else {
			assert(word & P64_PAGE_FISAHINT);
			expected_word = data->ed_prevword;
		}
		if (expected_word == word) {
			data->ed_prevsize += num_bytes;
			return;
		}
	}
	if (data->ed_prevsize) {
		if ((byte_t *)data->ed_prevstart >= (byte_t *)P64_MMAN_KERNEL_PDIR_IDENTITY_BASE &&
		    (byte_t *)data->ed_prevstart + data->ed_prevsize <= (byte_t *)(P64_MMAN_KERNEL_PDIR_IDENTITY_BASE +
		                                                                   P64_MMAN_KERNEL_PDIR_IDENTITY_SIZE)) {
			++data->ed_identcnt;
			goto done_print; /* Skip entries within the identity mapping. */
		}
		p64_doenum(data, data->ed_prevstart, data->ed_prevsize, data->ed_prevword, data->ed_mask);
	}
done_print:
	data->ed_prevstart   = start;
	data->ed_prevsize    = num_bytes;
	data->ed_prevword    = word;
}

PRIVATE ATTR_DBGTEXT void KCALL
p64_do_lspd(unsigned int vec4_max) {
	struct p64_enumdat data;
	data.ed_prevstart = 0;
	data.ed_prevsize  = 0;
	data.ed_prevword  = 0;
	data.ed_skipident = true;
	data.ed_identcnt  = 0;
	data.ed_mask = P64_PAGE_FVECTOR | P64_PAGE_FPRESENT | P64_PAGE_FWRITE | P64_PAGE_FUSER |
	               P64_PAGE_FPWT | P64_PAGE_FPCD | P64_PAGE_FPAT | P64_PAGE_FNOEXEC |
	               P64_PAGE_FPREPARED | P64_PAGE_FGLOBAL | P64_PAGE_FACCESSED | P64_PAGE_FDIRTY;
	p64_enum_e4(&p64_enumfun, &data, vec4_max);
	if (data.ed_prevsize)
		p64_doenum(&data, data.ed_prevstart, data.ed_prevsize, data.ed_prevword, data.ed_mask);
}

PRIVATE ATTR_DBGRODATA char const lspd_str_kernel[] = "kernel";
PRIVATE ATTR_DBGRODATA char const lspd_str_user[]   = "user";

DBG_AUTOCOMPLETE(lspd,
                 /*size_t*/ argc, /*char **/ argv /*[]*/,
                 /*dbg_autocomplete_cb_t*/ cb, /*void **/arg) {
	(void)argv;
	if (argc == 1) {
		(*cb)(arg, lspd_str_kernel, COMPILER_STRLEN(lspd_str_kernel));
		(*cb)(arg, lspd_str_user, COMPILER_STRLEN(lspd_str_user));
	}
}

DBG_COMMAND_AUTO(lspd, DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE,
                 "lspd [MODE:kernel|user=user]\n"
                 "\tDo a raw walk over the loaded page directory and enumerate mappings.\n"
                 "\t" AC_WHITE("mode") " can be specified as either " AC_WHITE("kernel")
                 " or " AC_WHITE("user") " to select if " AC_WHITE("mman_kernel") "\n"
                 "\tor " AC_WHITE("THIS_MMAN") " should be dumped\n",
                 argc, argv) {
	pagedir_phys_t pdir;
	if (argc == 2) {
		if (strcmp(argv[1], lspd_str_kernel) == 0)
			goto do_ls_kernel;
		if (strcmp(argv[1], lspd_str_user) != 0)
			return DBG_STATUS_INVALID_ARGUMENTS;
	} else {
		if (argc != 1)
			return DBG_STATUS_INVALID_ARGUMENTS;
	}
	pdir = dbg_getpagedir();
	if (pdir == pagedir_kernel_phys) {
do_ls_kernel:
		p64_do_lspd(512);
		return 0;
	}
	PAGEDIR_P_BEGINUSE(pdir) {
		p64_do_lspd(256);
	}
	PAGEDIR_P_ENDUSE(pdir);
	return 0;
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING64_C_INL */
