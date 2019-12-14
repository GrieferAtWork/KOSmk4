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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING64_C_INL
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING64_C_INL 1
#define _KOS_SOURCE 1
#define __VM_INTERNAL_EXCLUDE_PAGEDIR 1
#define __OMIT_PAGING_CONSTANT_P_WRAPPERS 1

#include <kernel/compiler.h>

#include <kernel/arch/paging64.h>
#include <kernel/cpuid.h>
#include <kernel/except.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <sched/cpu.h>
#include <sched/tss.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <asm/cpu-cpuid.h>
#include <asm/cpu-flags.h>

#include <assert.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

/* Return the physical page ID of a given physical address. */
#define ppageof(paddr) (pageptr_t)((paddr) / PAGESIZE)

/* Feature tests helpers */
#define HAVE_PAGE_GLOBAL_BIT       (x86_bootcpu_cpuid.ci_1d & CPUID_1D_PGE)
#define HAVE_PAGE_ATTRIBUTE_TABLE  (x86_bootcpu_cpuid.ci_1d & CPUID_1D_PAT)
#define HAVE_INSTR_INVLPG          1 /* Always supported on x86_64 */
#define HAVE_INSTR_INVPCID         (x86_bootcpu_cpuid.ci_7b & CPUID_7B_INVPCID)
#define HAVE_1GIB_PAGES            (x86_bootcpu_cpuid.ci_80000001d & CPUID_80000001D_PSE)
#define HAVE_2MIB_PAGES            1 /* Always available! (and also assumed to be by code below!) */
#define HAVE_EXECUTE_DISABLE       (x86_bootcpu_cpuid.ci_80000001d & CPUID_80000001D_NX)

INTERN u64 used_pxx_page_fglobal = P64_PAGE_FGLOBAL;
#define USED_P64_PAGE_FGLOBAL used_pxx_page_fglobal


/* I always find recursive array declarations in C to be extremely confusing,
 * so to make sure I didn't screw up the array-length ordering of the E{1-4}
 * descriptor types, assert that they offsets behave correctly in relation to
 * their indices. */
struct p64_pdir_e1_identity_t_struct { p64_pdir_e1_identity_t x; };
struct p64_pdir_e2_identity_t_struct { p64_pdir_e2_identity_t x; };
struct p64_pdir_e3_identity_t_struct { p64_pdir_e3_identity_t x; };
struct p64_pdir_e4_identity_t_struct { p64_pdir_e4_identity_t x; };
STATIC_ASSERT(offsetof(struct p64_pdir_e1_identity_t_struct, x[1][0][0][0]) == 512 * 512 * 512 * 8);
STATIC_ASSERT(offsetof(struct p64_pdir_e2_identity_t_struct, x[1][0][0])    == 512 * 512 * 8);
STATIC_ASSERT(offsetof(struct p64_pdir_e3_identity_t_struct, x[1][0])       == 512 * 8);
STATIC_ASSERT(offsetof(struct p64_pdir_e4_identity_t_struct, x[1])          == 8);


STATIC_ASSERT(sizeof(struct p64_pdir) == P64_PDIR_SIZE);
STATIC_ASSERT(sizeof(struct p64_pdir) == 4096);
STATIC_ASSERT(sizeof(union p64_pdir_e4) == 8);
STATIC_ASSERT(sizeof(union p64_pdir_e3) == 8);
STATIC_ASSERT(sizeof(union p64_pdir_e2) == 8);
STATIC_ASSERT(sizeof(union p64_pdir_e1) == 8);
STATIC_ASSERT(P64_PDIR_E1_IDENTITY_BASE == P64_VM_KERNEL_PDIR_IDENTITY_BASE);


PRIVATE ATTR_SECTION(".free.unmap_but_keep_allocated") ATTR_ALIGNED(4096)
union p64_pdir_e1 boot_trampoline_e1v[512];

INTDEF byte_t __kernel_free_endpage[];

/* Prepare 2 consecutive (and 2-page aligned) pages of virtual
 * memory for the purpose of doing the initial prepare required
 * for `THIS_TRAMPOLINE_PAGE' of `_boottask' and also `_bootidle' */
INTERN NOBLOCK ATTR_FREETEXT vm_vpage_t
NOTHROW(FCALL kernel_initialize_boot_trampolines)(void) {
	u64 e1_word, e2_word;
	vm_vpage_t trampoline_page;
	unsigned int vec1, vec2, vec3, vec4, i;
	/* We allocate the boot trampoline immediately after the
	 * end of the kernel's .free section in virtual memory. */
	trampoline_page = (vm_vpage_t)(uintptr_t)__kernel_free_endpage;
again_calculate_vecN:
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(trampoline_page);
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(trampoline_page);
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(trampoline_page);
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(trampoline_page);
	if unlikely_untraced(vec1 == 511) {
		/* Make sure that the two pages used are located in the same E1-vector. */
		++trampoline_page;
		goto again_calculate_vecN;
	}
	assert(IS_ALIGNED((u64)boot_trampoline_e1v, 4096));
	assert(P64_PDIR_E4_IDENTITY[vec4].p_vec3.v_present);
	assert(P64_PDIR_E3_IDENTITY[vec4][vec3].p_vec2.v_present);
	assert(!P64_PDIR_E3_IDENTITY[vec4][vec3].p_1gib.d_1gib_1);
	assert(P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_2mib.d_present);
	assert(P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_2mib.d_2mib_1);
	/* Figure out the physical address surrounding the trampoline's E1-vector. */
	e1_word = (u64)((trampoline_page - KERNEL_CORE_PAGE) * 4096);
	assertf(pagedir_translate((void *)VM_PAGE2ADDR(trampoline_page)) == (vm_phys_t)e1_word,
	        "%p != %p",
	        (uintptr_t)pagedir_translate((void *)VM_PAGE2ADDR(trampoline_page)),
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
	/* Mark the 2 pages used for the trampolines as prepared. */
	boot_trampoline_e1v[vec1 + 0].p_word |= P64_PAGE_FPREPARED;
	boot_trampoline_e1v[vec1 + 1].p_word |= P64_PAGE_FPREPARED;
	/* Setup the replacement E2-word */
	e2_word = (u64)boot_trampoline_e1v - KERNEL_CORE_BASE; /* virt2phys() */
	e2_word |= (P64_PAGE_FPRESENT | P64_PAGE_FWRITE |
	            P64_PAGE_FACCESSED | P64_PAGE_FDIRTY);
	COMPILER_WRITE_BARRIER();
	/* Set the E1-vector as being used. */
	ATOMIC_WRITE(P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word, e2_word);
	/* Return the virtual memory locations used for the
	 * trampolines needed by `_boottask' and `_bootidle' */
	return trampoline_page;
}






INTDEF byte_t __kernel_pervm_size[];

/* Define the kernel VM */
INTERN ATTR_SECTION(".data.pervm.head")
struct vm vm_kernel_head = {
	{
		.v_pdir_phys_ptr = &pagedir_kernel_phys,
	},
	/* .v_refcnt     = */ 3,
	/* .v_weakrefcnt = */ 1,
	/* .v_tree       = */ NULL,
	/* .v_byaddr     = */ NULL,
	/* .v_heap_size  = */ (size_t)__kernel_pervm_size + PAGEDIR_SIZE,
	/* .v_treelock   = */ ATOMIC_RWLOCK_INIT,
	/* .v_tasks      = */ NULL,
	/* .v_tasklock   = */ ATOMIC_RWLOCK_INIT,
	/* .v_deltasks   = */ NULL,
	/* .v_kernreserve = */ {
		/* .vn_node   = */ { (struct vm_node *)UINT64_C(0xcccccccccccccccc),
		                     (struct vm_node *)UINT64_C(0xcccccccccccccccc),
		                     (vm_vpage_t)UINT64_C(0xcccccccccccccccc),
		                     (vm_vpage_t)UINT64_C(0xcccccccccccccccc) },
		/* .vn_byaddr = */ { (struct vm_node *)UINT64_C(0xcccccccccccccccc),
		                     (struct vm_node **)UINT64_C(0xcccccccccccccccc) },
		/* .vn_prot   = */ UINT32_C(0xcccccccc),
		/* .vn_flags  = */ UINT32_C(0xcccccccc),
		/* .vn_vm     = */ (struct vm *)UINT64_C(0xcccccccccccccccc),
		/* .vn_part   = */ (struct vm_datapart *)UINT64_C(0xcccccccccccccccc),
		/* .vn_block  = */ (struct vm_datablock *)UINT64_C(0xcccccccccccccccc),
		/* .vn_link   = */ { (struct vm_node *)UINT64_C(0xcccccccccccccccc),
		                     (struct vm_node **)UINT64_C(0xcccccccccccccccc) },
		/* .vn_guard  = */ UINT64_C(0xcccccccccccccccc)
	}
};


typedef struct {
	/* Allocate enough structures to allow _start64.S to create an
	 * identity mapping of the first 2GiB of physical memory at -2GiB,
	 * using only 2MiB mappings.
	 * With this in mind, we need:
	 *  - 255 * E3-VECTOR  (`union p64_pdir_e3[255][512]') that will be used for the kernel-share
	 *  - 1 * E3-VECTOR  (`union p64_pdir_e3[512]') that goes into `pagedir_kernel.p_e4[511]'
	 *  - 2 * E2-VECTOR  (`union p64_pdir_e2[2][512]') that go into `p64_pdir_e3[510]' and `p64_pdir_e3[511]'
	 * _start64.S will then fill the two E2-vectors with 2MiB identity mappings,
	 * before having the E3 vector point towards them, before finally placing the
	 * E3 vector within the kernel page directory. */
	union p64_pdir_e3 ks_share_e3[256][512];
	union p64_pdir_e2 ks_share_e2[2][512];
} kernel_share_t;

/* Allocate BSS memory for the initial shared+identity mapping
 * that will later be shared with, and re-appear in all other
 * page directories (except for the identity page) */
INTERN ATTR_SECTION(".bss.x86.pagedir_kernel_share")
kernel_share_t __x86_pagedir_kernel_share = {};



/* Initialize the given page directory.
 * The caller is required to allocate the page directory
 * controller itself, which must be aligned and sized
 * according to `PAGEDIR_ALIGN' and `PAGEDIR_SIZE'. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p64_pagedir_init)(VIRT struct p64_pdir *__restrict self,
                                PHYS vm_phys_t phys_self) {
	/* Make sure that the page directory identity mapping is located at the proper position.
	 * Note that this position is `KERNEL_BASE + 512GiB', where KERNEL_BASE is at `0xffff800000000000',
	 * meaning that the identity mapping is at: `0xffff808000000000 ... 0xffff80ffffffffff'
	 * With this in mind, x86_64 is different from i386, in that the page directory identity
	 * mapping isn't stored at the end of the kernel address space, but rather (near) the start
	 * of it (we intentionally don't use `KERNEL_BASE' itself as base address in order to keep
	 * the first page of kernel-space unmapped (meaning that given the 512GiB alignment
	 * requirements of the identity mapping, we end up with `KERNEL_BASE + 512GiB')) */
	STATIC_ASSERT(P64_PDIR_VEC4INDEX(P64_VM_KERNEL_PDIR_IDENTITY_BASE) == 257);
	STATIC_ASSERT(P64_PDIR_VEC3INDEX(P64_VM_KERNEL_PDIR_IDENTITY_BASE) == 0);
	STATIC_ASSERT(P64_PDIR_VEC2INDEX(P64_VM_KERNEL_PDIR_IDENTITY_BASE) == 0);
	STATIC_ASSERT(P64_PDIR_VEC1INDEX(P64_VM_KERNEL_PDIR_IDENTITY_BASE) == 0);
	/* Assert that the page directory is properly aligned. */
	assert(IS_ALIGNED((uintptr_t)self, PAGESIZE));
	assert(IS_ALIGNED((uintptr_t)phys_self, PAGESIZE));
	memsetq(self->p_e4 + 0, P64_PAGE_ABSENT, 256);              /* user-space */
	memcpyq(self->p_e4 + 256, P64_PDIR_E4_IDENTITY + 256, 256); /* kernel-space */
	/* Set the control word for the page directory identity mapping. */
	self->p_e4[267].p_word = (u64)phys_self | P64_PAGE_FACCESSED | P64_PAGE_FWRITE | P64_PAGE_FPRESENT;
}


/* Because we're omitting the `v_pagedir' field from the start of the VM, we have
 * to adjust for that fact when we're trying to access the `v_pdir_phys_ptr' field! */
#define VM_GET_V_PDIR_PHYS_PTR(x) \
	(*(PHYS pagedir_t **)((byte_t *)(x) + sizeof(pagedir_t) + offsetof(struct vm, v_pdir_phys_ptr)))


/* Finalize a given page directory. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p64_pagedir_fini)(VIRT struct p64_pdir *__restrict self,
                                PHYS vm_phys_t phys_self) {
#define NOT_SWITCHED ((PHYS pagedir_t *)-1)
	unsigned int vec4;
	pflag_t was = 0;
	PHYS pagedir_t *old_pagedir = NOT_SWITCHED;
	assert(IS_ALIGNED((uintptr_t)self, PAGESIZE));
	assert(IS_ALIGNED((uintptr_t)phys_self, PAGESIZE));
	assertf(VM_GET_V_PDIR_PHYS_PTR(THIS_VM) == pagedir_get(),
	        "Wrong page directory set (%p != %p)",
	        old_pagedir, pagedir_get());
	assertf((self->p_e4[267].p_word & ~(P64_PAGE_FACCESSED)) ==
	        ((u64)phys_self | P64_PAGE_FWRITE | P64_PAGE_FPRESENT),
	        "Page directory does not contain a valid identity mapping");
	for (vec4 = 0; vec4 < 256; ++vec4) {
		union p64_pdir_e4 e4;
		e4 = self->p_e4[vec4];
		/* Search through user-space for any allocated E3 vectors. */
		if (P64_PDIR_E4_ISVEC3(e4.p_word)) {
			unsigned int vec3;
			/* Switch to the target page directory so we can make
			 * use of its identity mapping in order to destroy it. */
			if (old_pagedir == NOT_SWITCHED) {
				was         = PREEMPTION_PUSHOFF();
				old_pagedir = VM_GET_V_PDIR_PHYS_PTR(THIS_VM);
				pagedir_set((pagedir_t *)(uintptr_t)phys_self);
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
							page_freeone(ppageof(e2.p_word & P64_PAGE_FVECTOR));
						}
					}
					page_freeone(ppageof(e3.p_word & P64_PAGE_FVECTOR));
				}
			}
			page_freeone(ppageof(e4.p_word & P64_PAGE_FVECTOR));
		}
	}
	if (old_pagedir != NOT_SWITCHED) {
		pagedir_set(old_pagedir);
		PREEMPTION_POP(was);
	}
#undef NOT_SWITCHED
}


LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p64_pagedir_set_prepared)(union p64_pdir_e1 *__restrict e1_p) {
	u64 word;
	for (;;) {
		/* Corrupt is OK, since ISHINT() only depends on the low 32 bits. */
		word = ATOMIC_READ(e1_p->p_word);
		if unlikely(P64_PDIR_E1_ISHINT(word))
			break; /* Special case: Hint */
		if likely(ATOMIC_CMPXCH_WEAK(e1_p->p_word, word, word | P64_PAGE_FPREPARED))
			break;
	}
}

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL p64_pagedir_unset_prepared)(union p64_pdir_e1 *__restrict e1_p) {
	u64 word;
	for (;;) {
		/* Corrupt is OK, since ISHINT() only depends on the low 32 bits. */
		word = ATOMIC_READ(e1_p->p_word);
		if unlikely(P64_PDIR_E1_ISHINT(word))
			break; /* Special case: Hint */
		assert(word & P64_PAGE_FPREPARED);
		if likely(ATOMIC_CMPXCH_WEAK(e1_p->p_word, word, word & ~P64_PAGE_FPREPARED))
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
 * on flattening (or deleting) any one of these vectors (outside of
 * `pagedir_fini()') */
PRIVATE struct atomic_rwlock x86_pagedir_prepare_lock = ATOMIC_RWLOCK_INIT;

/* Version counter for `x86_pagedir_prepare_lock' (incremented each read/write) */
PRIVATE ATTR_WRITEMOSTLY WEAK uintptr_t x86_pagedir_prepare_version = 0;

#define X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was)                    \
	do {                                                              \
		was = PREEMPTION_PUSHOFF();                                   \
		if likely(atomic_rwlock_tryread(&x86_pagedir_prepare_lock)) { \
			ATOMIC_FETCHINC(x86_pagedir_prepare_version);             \
			break;                                                    \
		}                                                             \
		PREEMPTION_POP(was);                                          \
		task_tryyield_or_pause();                                     \
	} __WHILE1
#define X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ_NOVER(was)            \
	do {                                                            \
		was = PREEMPTION_PUSHOFF();                                 \
		if likely(atomic_rwlock_tryread(&x86_pagedir_prepare_lock)) \
			break;                                                  \
		PREEMPTION_POP(was);                                        \
		task_tryyield_or_pause();                                   \
	} __WHILE1
#define X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_WRITE(was)                  \
	do {                                                             \
		was = PREEMPTION_PUSHOFF();                                  \
		if likely(atomic_rwlock_trywrite(&x86_pagedir_prepare_lock)) \
			break;                                                   \
		PREEMPTION_POP(was);                                         \
		task_tryyield_or_pause();                                    \
	} __WHILE1
#define X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was)        \
	do {                                                  \
		atomic_rwlock_endread(&x86_pagedir_prepare_lock); \
		PREEMPTION_POP(was);                              \
	} __WHILE0
#define X86_PAGEDIR_PREPARE_LOCK_RELEASE_WRITE(was)        \
	do {                                                   \
		atomic_rwlock_endwrite(&x86_pagedir_prepare_lock); \
		PREEMPTION_POP(was);                               \
	} __WHILE0


LOCAL NOBLOCK pageptr_t
NOTHROW(FCALL p64_create_e1_vector_from_e2_word)(struct vm_ptram *__restrict ptram,
                                                 u64 e2_word,
                                                 unsigned int vec1_prepare_start,
                                                 unsigned int vec1_prepare_size) {
	union p64_pdir_e1 e1, *e1_p;
	pageptr_t result;
	result = page_mallocone();
	if unlikely(result == PAGEPTR_INVALID)
		goto done;
	/* Fill in the E1 vector. */
	e1_p = (union p64_pdir_e1 *)vm_ptram_mappage(ptram, result);
	if (e2_word & P64_PAGE_FPRESENT) {
		/* Convert a 2MiB mapping into 512 * 4KiB mappings */
		assert(e2_word & P64_PAGE_F2MIB);
		e1.p_word = e2_word & ~(P64_PAGE_F2MIB | P64_PAGE_FPAT_2MIB);
		if (e2_word & P64_PAGE_FPAT_2MIB)
			e1.p_word |= P64_PAGE_FPAT_4KIB;
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
LOCAL NOBLOCK pageptr_t
NOTHROW(FCALL p64_create_e2_vector_from_e3_word_and_e1_vector)(struct vm_ptram *__restrict ptram,
                                                               u64 e3_word,
                                                               unsigned int vec2,
                                                               pageptr_t e1_vector,
                                                               bool is_userspace) {
	pageptr_t result;
	union p64_pdir_e2 e2, *e2_p;
	/* Fill in the E2 vector. */
	result = page_mallocone();
	if unlikely(result == PAGEPTR_INVALID)
		goto done;
	e2_p = (union p64_pdir_e2 *)vm_ptram_mappage(ptram, result);
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
LOCAL NOBLOCK u64
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


/* Try to widen a 2MiB mapping to a 512*4KiB vector of linear memory
 * Alternatively, if the specified E1-vector is absent, pre-allocate it.
 * Additionally, set the `P64_PAGE_FPREPARED' bit for all E1 vector elements
 * within the range of `vec1_prepare_start...+=vec1_prepare_size'
 * Note that `vec1_prepare_size' must be non-zero!
 * @return: true:  Success
 * @return: false: Failed to allocate physical memory */
PRIVATE NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_impl_widen)(unsigned int vec4,
                                              unsigned int vec3,
                                              unsigned int vec2,
                                              unsigned int vec1_prepare_start,
                                              unsigned int vec1_prepare_size) {
	/* NOTE: This function is able to access `THIS_TRAMPOLINE_PAGE', since
	 *       that memory location is always already prepared from the get-go.
	 *       The trampoline page of any given thread gets initially prepared
	 *       by the thread that called `task_alloc()' (where the act of preparing
	 *       the trampoline page of some new thread will require the use of one's
	 *       own trampoline page)
	 * The dependency loop formed by this is resolved thanks to
	 *      `kernel_initialize_boot_trampolines()' */
#define VEC4_IS_USERSPACE (vec4 < 256)
	union p64_pdir_e4 e4;
	union p64_pdir_e3 e3;
	union p64_pdir_e2 e2;
	pflag_t was = 0;
	assert(vec3 < 4);
	assert(vec2 < 512);
	assert(vec1_prepare_start < 512);
	assert(vec1_prepare_size != 0);
	assert(vec1_prepare_start + vec1_prepare_size > vec1_prepare_start);
	assert(vec1_prepare_start + vec1_prepare_size <= 512);
again:
	e4.p_word = ATOMIC_READ(P64_PDIR_E4_IDENTITY[vec4].p_word);
	if (!P64_PDIR_E4_ISVEC3(e4.p_word)) {
		pageptr_t e3_vector; /* 511 * P64_PAGE_ABSENT + 1 * VEC2 */
		pageptr_t e2_vector; /* 511 * P64_PAGE_ABSENT + 1 * VEC1 */
		pageptr_t e1_vector; /* 512 * P64_PAGE_ABSENT */
		u64 new_e4_word;
		union p64_pdir_e3 *e3_p;
		union p64_pdir_e2 *e2_p;
		union p64_pdir_e1 *e1_p;
		struct vm_ptram ptram;
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
		e3_vector = page_mallocone();
		if unlikely(!e3_vector)
			goto err;
		e2_vector = page_mallocone();
		if unlikely(!e2_vector) {
err_e3_vector:
			page_freeone(e3_vector);
			goto err;
		}
		e1_vector = page_mallocone();
		if unlikely(!e1_vector) {
			page_freeone(e2_vector);
			goto err_e3_vector;
		}
		vm_ptram_init(&ptram);
		/* Initialize the E1-vector. */
		e1_p = (union p64_pdir_e1 *)vm_ptram_mappage(&ptram, e1_vector);
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
		e2_p = (union p64_pdir_e2 *)vm_ptram_mappage(&ptram, e2_vector);
#if P64_PAGE_ABSENT == 0
		if (!page_iszero(e2_vector))
#endif /* P64_PAGE_ABSENT == 0 */
		{
			memsetq(e2_p, P64_PAGE_ABSENT, 512);
		}
		e2_p[vec2].p_word = ((u64)e1_vector * 4096) | P64_PAGE_FPRESENT |
		                    P64_PAGE_FWRITE | P64_PAGE_FUSER;
		/* Initialize the E3-vector. */
		e3_p = (union p64_pdir_e3 *)vm_ptram_mappage(&ptram, e3_vector);
#if P64_PAGE_ABSENT == 0
		if (!page_iszero(e3_vector))
#endif /* P64_PAGE_ABSENT == 0 */
		{
			memsetq(e3_p, P64_PAGE_ABSENT, 512);
		}
		e3_p[vec3].p_word = ((u64)e2_vector * 4096) | P64_PAGE_FPRESENT |
		                    P64_PAGE_FWRITE | P64_PAGE_FUSER;
		vm_ptram_fini(&ptram);
		/* Try to install the new E3-vector as an E4-word. */
		new_e4_word = (u64)e3_vector * 4096;
		new_e4_word |= P64_PAGE_FPRESENT | P64_PAGE_FWRITE | P64_PAGE_FUSER;
		if unlikely(!ATOMIC_CMPXCH(P64_PDIR_E4_IDENTITY[vec4].p_word,
		                           e4.p_word, new_e4_word)) {
/*word_changed_after_e3_vector:*/
			page_freeone(e3_vector);
			page_freeone(e2_vector);
			page_freeone(e1_vector);
			goto again;
		}
		goto success;
	}
	/* Only need to acquire the PREPARE-lock for accessing
	 * our associated `P64_PDIR_E3_IDENTITY[vec4][vec3]' when
	 * the E3-vector is located in user-space. For kernel-space,
	 * we can always assume that E3-vectors are always pre-
	 * allocated, since this pre-allocation is also required
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
		struct vm_ptram ptram;
		pageptr_t e1_vector; /* 512 * 4KiB */
		pageptr_t e2_vector; /* 511 * 2MiB + 1 * VEC1 */
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
		vm_ptram_init(&ptram);
		e1_vector = p64_create_e1_vector_from_e2_word(&ptram,
		                                              e2_word.p_word,
		                                              vec1_prepare_start,
		                                              vec1_prepare_size);
		if (e1_vector == PAGEPTR_INVALID) {
			vm_ptram_fini(&ptram);
			goto err;
		}
		/* Construct an E2 vector pointing to the E1 vector created earlier. */
		e2_vector = p64_create_e2_vector_from_e3_word_and_e1_vector(&ptram, e3.p_word,
		                                                            vec2, e1_vector,
		                                                            VEC4_IS_USERSPACE);
		vm_ptram_fini(&ptram);
		if (e2_vector == PAGEPTR_INVALID) {
			page_freeone(e1_vector);
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
			page_freeone(e2_vector);
			page_freeone(e1_vector);
			goto again;
		}
		/* Try to install the new E2-vector. */
		if unlikely(!ATOMIC_CMPXCH(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word,
		                           e3.p_word, new_e3_word))
			goto word_changed_after_e2_vector;
		goto success;
	}

	/* When it comes to accessing the E2 and E1 vectors, we always need to be
	 * holding the PREPARE lock, regardless of being in kernel- or user-space,
	 * as the E2 and E1 vectors are dynamically allocated (and most importantly
	 * also dynamically freed) in both kernel- and user-space. */
	if (!VEC4_IS_USERSPACE)
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was);
	e2.p_word = ATOMIC_READ(P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word);
	if (!e2.p_vec1.v_present || e2.p_2mib.d_2mib_1) {
		/* Convert the 2MiB mapping into
		 *  - 512 * 4KiB mappings */
		struct vm_ptram ptram;
		pageptr_t e1_vector;
		u64 new_word, new_e2_word;
		X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
		vm_ptram_init(&ptram);
		e1_vector = p64_create_e1_vector_from_e2_word(&ptram, e2.p_word,
		                                              vec1_prepare_start,
		                                              vec1_prepare_size);
		vm_ptram_fini(&ptram);
		if unlikely(e1_vector == PAGEPTR_INVALID)
			goto err;
		/* Re-acquire the prepare lock and make sure that the vectors
		 * leading up to the one we've just allocated haven't changed. */
		X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was);
		new_word = ATOMIC_READ(P64_PDIR_E4_IDENTITY[vec4].p_word);
		if unlikely(e4.p_word != new_word) {
word_changed_after_e1_vector:
			X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was);
			page_freeone(e1_vector);
			goto again;
		}
		new_word = ATOMIC_READ(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word);
		if unlikely(e3.p_word != new_word)
			goto word_changed_after_e1_vector;
		new_e2_word = (u64)e1_vector * 4096;
		new_e2_word |= P64_PAGE_FPRESENT | P64_PAGE_FWRITE;
		new_e2_word |= e2.p_word & (P64_PAGE_FUSER | P64_PAGE_FPWT |
		                            P64_PAGE_FPCD | P64_PAGE_FACCESSED |
		                            P64_PAGE_FGLOBAL);
		if (VEC4_IS_USERSPACE)
			new_e2_word |= P64_PAGE_FUSER;
		/* Try to install the new E1-vector. */
		if unlikely(!ATOMIC_CMPXCH(P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word,
		                           e2.p_word, new_e2_word))
			goto word_changed_after_e1_vector;
		goto success;
	}
	/* The E1-vector already exists.
	 * In this case, we simply have to set the PREPARED bit for every indicated entry!
	 * Note that for this purpose, we only need to keep hold of the PREPARE-LOCK for
	 * the first entry, since any entry after that will still be apart of the same
	 * E1-vector, while the presence of the PREPARED bit already guaranties that the
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
	}
	/* And we're done! */
success:
	return true;
err:
	return false;
#undef VEC4_IS_USERSPACE
}

/* Try to flatten 512*4KiB of linear memory to a 2MiB mapping,
 * or well as 512*2MiB of linear memory to a 1GiB mapping. */
PRIVATE NOBLOCK void
NOTHROW(FCALL p64_pagedir_unprepare_impl_flatten)(unsigned int vec4,
                                                  unsigned int vec3,
                                                  unsigned int vec2,
                                                  unsigned int vec1_unprepare_start,
                                                  unsigned int vec1_unprepare_size) {
	(void)vec4;
	(void)vec3;
	(void)vec2;
	(void)vec1_unprepare_start;
	(void)vec1_unprepare_size;
	/* TODO */
}



LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_impl_widen_v1)(unsigned int vec4,
                                                 unsigned int vec3,
                                                 unsigned int vec2,
                                                 unsigned int vec1_min,
                                                 unsigned int vec1_max) {
	assert(vec1_min <= vec1_max);
	return p64_pagedir_prepare_impl_widen(vec4, vec3, vec2,
	                                      vec1_min,
	                                      (vec1_max - vec1_min) + 1);
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
		p64_pagedir_unprepare_impl_flatten_v1(vec4, vec3, vec2_min, vec1_min, vec1_max);
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
		p64_pagedir_unprepare_impl_flatten_v2(vec4, vec3_min, vec2_min, vec2_max, vec1_min, vec1_max);
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
		p64_pagedir_unprepare_impl_flatten_v3(vec4_min, vec3_min, vec3_max, vec2_min, vec2_max, vec1_min, vec1_max);
		return;
	}
	p64_pagedir_unprepare_impl_flatten_v3(vec4_min, vec3_min, 511, vec2_min, 511, vec1_min, 511);
	p64_pagedir_unprepare_impl_flatten_v3(vec4_max, 0, vec3_max, 0, vec2_max, 0, vec1_max);
	for (vec4 = vec4_min + 1; vec4 < vec4_max; ++vec4)
		p64_pagedir_unprepare_impl_flatten_v3(vec4, 0, 511, 0, 511, 0, 511);
}



/* Prepare the page directory for a future map() operation.
 * The full cycle of a single mapping then looks like this:
 * >> p64_pagedir_prepare_map(...);
 * >> p64_pagedir_map(...);
 * >> p64_pagedir_unmap(...);
 * >> p64_pagedir_unprepare_map(...);
 * NOTE: `p64_pagedir_prepare_map_keep()' is the same as `p64_pagedir_prepare_map()', but
 *        will not undo already successfully made preparations after a later one fails.
 *        This will include the undoing of redundant preparations of the given range that
 *        were made in prior calls.
 * @return: true:  Successfully allocated structures required for creating mappings.
 * @return: false: Insufficient physical memory to change mappings. */
#ifdef CONFIG_USE_NEW_PAGING
INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_npagedir_prepare_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec4, vec3, vec2, vec1;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	return p64_pagedir_prepare_impl_widen(vec4, vec3, vec2, vec1, 1);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_npagedir_unprepare_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec4, vec3, vec2, vec1;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	p64_pagedir_unprepare_impl_flatten(vec4, vec3, vec2, vec1, 1);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_npagedir_prepare_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                        PAGEDIR_PAGEALIGNED size_t num_bytes) {
	unsigned int vec4_min, vec4_max;
	unsigned int vec3_min, vec3_max;
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_max;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	assertf(IS_ALIGNED((uintptr_t)num_bytes, 4096), "num_bytes = %#Ix", num_bytes);
	assertf((uintptr_t)addr + num_bytes >= (uintptr_t)addr, "Invalid range %p...%p",
	        addr, (uintptr_t)addr + num_bytes - 1);
	if (!num_bytes)
		return true;
	if (num_bytes == 4096)
		return p64_npagedir_prepare_mapone(addr);
	vec4_min = P64_PDIR_VEC4INDEX(addr);
	vec4_max = P64_PDIR_VEC4INDEX((byte_t *)addr + num_bytes - 1);
	vec3_min = P64_PDIR_VEC3INDEX(addr);
	vec3_max = P64_PDIR_VEC3INDEX((byte_t *)addr + num_bytes - 1);
	vec2_min = P64_PDIR_VEC2INDEX(addr);
	vec2_max = P64_PDIR_VEC2INDEX((byte_t *)addr + num_bytes - 1);
	vec1_min = P64_PDIR_VEC1INDEX(addr);
	vec1_max = P64_PDIR_VEC1INDEX((byte_t *)addr + num_bytes - 1);
	return p64_pagedir_prepare_impl_widen_v4(vec4_min, vec4_max,
	                                         vec3_min, vec3_max,
	                                         vec2_min, vec2_max,
	                                         vec1_min, vec1_max);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_npagedir_prepare_map_keep)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                             PAGEDIR_PAGEALIGNED size_t num_bytes) {
	unsigned int vec4_min, vec4_max;
	unsigned int vec3_min, vec3_max;
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_max;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	assertf(IS_ALIGNED((uintptr_t)num_bytes, 4096), "num_bytes = %#Ix", num_bytes);
	assertf((uintptr_t)addr + num_bytes >= (uintptr_t)addr, "Invalid range %p...%p",
	        addr, (uintptr_t)addr + num_bytes - 1);
	if (!num_bytes)
		return true;
	if (num_bytes == 4096)
		return p64_npagedir_prepare_mapone(addr);
	vec4_min = P64_PDIR_VEC4INDEX(addr);
	vec4_max = P64_PDIR_VEC4INDEX((byte_t *)addr + num_bytes - 1);
	vec3_min = P64_PDIR_VEC3INDEX(addr);
	vec3_max = P64_PDIR_VEC3INDEX((byte_t *)addr + num_bytes - 1);
	vec2_min = P64_PDIR_VEC2INDEX(addr);
	vec2_max = P64_PDIR_VEC2INDEX((byte_t *)addr + num_bytes - 1);
	vec1_min = P64_PDIR_VEC1INDEX(addr);
	vec1_max = P64_PDIR_VEC1INDEX((byte_t *)addr + num_bytes - 1);
	return p64_pagedir_prepare_impl_widen_v4_keep(vec4_min, vec4_max,
	                                              vec3_min, vec3_max,
	                                              vec2_min, vec2_max,
	                                              vec1_min, vec1_max);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_npagedir_unprepare_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                          PAGEDIR_PAGEALIGNED size_t num_bytes) {
	unsigned int vec4_min, vec4_max;
	unsigned int vec3_min, vec3_max;
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_max;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	assertf(IS_ALIGNED((uintptr_t)num_bytes, 4096), "num_bytes = %#Ix", num_bytes);
	assertf((uintptr_t)addr + num_bytes >= (uintptr_t)addr, "Invalid range %p...%p",
	        addr, (uintptr_t)addr + num_bytes - 1);
	if (!num_bytes)
		return;
	if (num_bytes == 4096) {
		p64_npagedir_unprepare_mapone(addr);
		return;
	}
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
#else /* CONFIG_USE_NEW_PAGING */
INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_mapone)(VIRT vm_vpage_t virt_page) {
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(virt_page);
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(virt_page);
	return p64_pagedir_prepare_impl_widen(vec4, vec3, vec2, vec1, 1);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unprepare_mapone)(VIRT vm_vpage_t virt_page) {
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(virt_page);
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(virt_page);
	p64_pagedir_unprepare_impl_flatten(vec4, vec3, vec2, vec1, 1);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_map)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	unsigned int vec4_min, vec4_max;
	unsigned int vec3_min, vec3_max;
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_max;
	assert(virt_page + num_pages >= virt_page);
	switch (num_pages) {
	case 0:
		return true;
	case 1:
		return p64_pagedir_prepare_mapone(virt_page);
	default:
		break;
	}
	vec4_min = P64_PDIR_VEC4INDEX_VPAGE(virt_page);
	vec4_max = P64_PDIR_VEC4INDEX_VPAGE(virt_page + num_pages - 1);
	vec3_min = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec3_max = P64_PDIR_VEC3INDEX_VPAGE(virt_page + num_pages - 1);
	vec2_min = P64_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec2_max = P64_PDIR_VEC2INDEX_VPAGE(virt_page + num_pages - 1);
	vec1_min = P64_PDIR_VEC1INDEX_VPAGE(virt_page);
	vec1_max = P64_PDIR_VEC1INDEX_VPAGE(virt_page + num_pages - 1);
	return p64_pagedir_prepare_impl_widen_v4(vec4_min, vec4_max,
	                                         vec3_min, vec3_max,
	                                         vec2_min, vec2_max,
	                                         vec1_min, vec1_max);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_prepare_map_keep)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	unsigned int vec4_min, vec4_max;
	unsigned int vec3_min, vec3_max;
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_max;
	assert(virt_page + num_pages >= virt_page);
	switch (num_pages) {
	case 0:
		return true;
	case 1:
		return p64_pagedir_prepare_mapone(virt_page);
	default:
		break;
	}
	vec4_min = P64_PDIR_VEC4INDEX_VPAGE(virt_page);
	vec4_max = P64_PDIR_VEC4INDEX_VPAGE(virt_page + num_pages - 1);
	vec3_min = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec3_max = P64_PDIR_VEC3INDEX_VPAGE(virt_page + num_pages - 1);
	vec2_min = P64_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec2_max = P64_PDIR_VEC2INDEX_VPAGE(virt_page + num_pages - 1);
	vec1_min = P64_PDIR_VEC1INDEX_VPAGE(virt_page);
	vec1_max = P64_PDIR_VEC1INDEX_VPAGE(virt_page + num_pages - 1);
	return p64_pagedir_prepare_impl_widen_v4_keep(vec4_min, vec4_max,
	                                              vec3_min, vec3_max,
	                                              vec2_min, vec2_max,
	                                              vec1_min, vec1_max);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unprepare_map)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	unsigned int vec4_min, vec4_max;
	unsigned int vec3_min, vec3_max;
	unsigned int vec2_min, vec2_max;
	unsigned int vec1_min, vec1_max;
	assert(virt_page + num_pages >= virt_page);
	switch (num_pages) {
	case 0:
		return;
	case 1:
		p64_pagedir_unprepare_mapone(virt_page);
		return;
	default:
		break;
	}
	vec4_min = P64_PDIR_VEC4INDEX_VPAGE(virt_page);
	vec4_max = P64_PDIR_VEC4INDEX_VPAGE(virt_page + num_pages - 1);
	vec3_min = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec3_max = P64_PDIR_VEC3INDEX_VPAGE(virt_page + num_pages - 1);
	vec2_min = P64_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec2_max = P64_PDIR_VEC2INDEX_VPAGE(virt_page + num_pages - 1);
	vec1_min = P64_PDIR_VEC1INDEX_VPAGE(virt_page);
	vec1_max = P64_PDIR_VEC1INDEX_VPAGE(virt_page + num_pages - 1);
	p64_pagedir_unprepare_impl_flatten_v4(vec4_min, vec4_max,
	                                      vec3_min, vec3_max,
	                                      vec2_min, vec2_max,
	                                      vec1_min, vec1_max);
}
#endif /* !CONFIG_USE_NEW_PAGING */



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
	        (uintptr_t)(P64_PDIR_VECADDR(vec4, vec3, vec2, vec1)),
	        (uintptr_t)(P64_PDIR_VECADDR(vec4, vec3, vec2, vec1) + PAGESIZE - 1));
	e3 = P64_PDIR_E3_IDENTITY[vec4][vec3];
	assertf(e3.p_word & P64_PAGE_FPRESENT,
	        "Page vector #%u:%u for page %p...%p isn't allocated",
	        (unsigned int)vec4, (unsigned int)vec3,
	        (uintptr_t)(P64_PDIR_VECADDR(vec4, vec3, vec2, vec1)),
	        (uintptr_t)(P64_PDIR_VECADDR(vec4, vec3, vec2, vec1) + PAGESIZE - 1));
	assertf(!(e3.p_word & P64_PAGE_F1GIB),
	        "Page %p...%p exists as a present 1GiB page #%u:%u",
	        (uintptr_t)(P64_PDIR_VECADDR(vec4, vec3, vec2, vec1)),
	        (uintptr_t)(P64_PDIR_VECADDR(vec4, vec3, vec2, vec1) + PAGESIZE - 1),
	        (unsigned int)vec4, (unsigned int)vec3);
	e2 = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2];
	assertf(e2.p_word & P64_PAGE_FPRESENT,
	        "Page vector #%u:%u:%u for page %p...%p isn't allocated",
	        (unsigned int)vec4, (unsigned int)vec3, (unsigned int)vec2,
	        (uintptr_t)(P64_PDIR_VECADDR(vec4, vec3, vec2, vec1)),
	        (uintptr_t)(P64_PDIR_VECADDR(vec4, vec3, vec2, vec1) + PAGESIZE - 1));
	assertf(!(e2.p_word & P64_PAGE_F2MIB),
	        "Page %p...%p exists as a present 2MiB page #%u:%u:%u",
	        (uintptr_t)(P64_PDIR_VECADDR(vec4, vec3, vec2, vec1)),
	        (uintptr_t)(P64_PDIR_VECADDR(vec4, vec3, vec2, vec1) + PAGESIZE - 1),
	        (unsigned int)vec4, (unsigned int)vec3, (unsigned int)vec2);
	e1 = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1];
	assertf(e1.p_word & P64_PAGE_FPREPARED || P64_PDIR_E1_ISHINT(e1.p_word),
	        "Page %p...%p [vec4=%u,vec3=%u,vec2=%u,vec1=%u] hasn't been prepared",
	        (uintptr_t)(P64_PDIR_VECADDR(vec4, vec3, vec2, vec1)),
	        (uintptr_t)(P64_PDIR_VECADDR(vec4, vec3, vec2, vec1) + PAGESIZE - 1),
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
	ATOMIC_FETCHAND(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word, e1_kept_bits_mask);
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

INTERN u64 p64_pageperm_matrix[16] = {
#define COMMON_PRESENT (P64_PAGE_FACCESSED | P64_PAGE_FDIRTY | P64_PAGE_FPRESENT)
	[(0)]                                                                              = P64_PAGE_FPREPARED | P64_PAGE_FNOEXEC,
	[(PAGEDIR_MAP_FEXEC)]                                                              = P64_PAGE_FPREPARED | COMMON_PRESENT,
	[(PAGEDIR_MAP_FWRITE)]                                                             = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FEXEC)]                                         = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_MAP_FREAD)]                                                              = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FNOEXEC,
	[(PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FEXEC)]                                          = P64_PAGE_FPREPARED | COMMON_PRESENT,
	[(PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE)]                                         = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FNOEXEC,
	[(PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FEXEC)]                     = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FWRITE,
	[(PAGEDIR_MAP_FUSER)]                                                              = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FUSER | P64_PAGE_FNOEXEC,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FEXEC)]                                          = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FUSER,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FWRITE)]                                         = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FUSER | P64_PAGE_FNOEXEC,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FEXEC)]                     = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FUSER,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FREAD)]                                          = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FUSER | P64_PAGE_FNOEXEC,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FEXEC)]                      = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FUSER,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE)]                     = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FUSER | P64_PAGE_FNOEXEC,
	[(PAGEDIR_MAP_FUSER | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FEXEC)] = P64_PAGE_FPREPARED | COMMON_PRESENT | P64_PAGE_FWRITE | P64_PAGE_FUSER,
#undef COMMON_PRESENT
};

#ifdef CONFIG_USE_NEW_PAGING
LOCAL NOBLOCK u64
NOTHROW(FCALL p64_pagedir_encode_4kib)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                                       u16 perm) {
	u64 result;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	assertf(IS_ALIGNED(phys, 4096), "phys = " FORMAT_VM_PHYS_T, phys);
	assertf(!(perm & ~PAGEDIR_MAP_FMASK),
	        "Invalid page permissions: %#.4I16x", perm);
	assertf(phys <= (vm_phys_t)UINT64_C(0x000ffffffffff000),
	        "Address cannot be mapped under p64: " FORMAT_VM_PHYS_T,
	        phys);
	result  = (u64)phys;
#if PAGEDIR_MAP_FMASK == 0xf
	result |= p64_pageperm_matrix[perm];
#else /* PAGEDIR_MAP_FMASK == 0xf */
	result |= p64_pageperm_matrix[perm & 0xf];
#endif /* PAGEDIR_MAP_FMASK != 0xf */
	if ((byte_t *)addr >= (byte_t *)KERNEL_BASE)
		result |= USED_P64_PAGE_FGLOBAL;
	return result;
}
#else /* CONFIG_USE_NEW_PAGING */
LOCAL NOBLOCK u64
NOTHROW(FCALL p64_pagedir_encode_4kib)(PHYS vm_vpage_t dest_page,
                                       PHYS pageptr_t phys_page, u16 perm) {
	u64 result;
	assertf(!(perm & ~PAGEDIR_MAP_FMASK),
	        "Invalid page permissions: %#.4I16x", perm);
	assertf(phys_page <= (pageptr_t)VM_ADDR2PAGE(UINT64_C(0x000ffffffffff000)),
	        "Page cannot be mapped: " FORMAT_VM_PHYS_T,
	        page2addr(phys_page));
	result  = (u64)page2addr(phys_page);
#if PAGEDIR_MAP_FMASK == 0xf
	result |= p64_pageperm_matrix[perm];
#else /* PAGEDIR_MAP_FMASK == 0xf */
	result |= p64_pageperm_matrix[perm & 0xf];
#endif /* PAGEDIR_MAP_FMASK != 0xf */
	if (dest_page >= (vm_vpage_t)KERNEL_BASE_PAGE)
		result |= USED_P64_PAGE_FGLOBAL;
	return result;
}
#endif /* !CONFIG_USE_NEW_PAGING */




/* Set a mapping hint for pages apart of the given virtual memory range.
 * Mapping hints are overwritten once a page has been mapped, and when
 * not specified, will default to `NULL'.
 * Their main purpose is to be accessible through atomic means, allowing
 * them to be used by the PAGE_FAULT handler, while still ensuring that
 * access remains non-blocking. */
#ifdef CONFIG_USE_NEW_PAGING
INTERN NOBLOCK void
NOTHROW(FCALL p64_npagedir_maphintone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	unsigned int vec4, vec3, vec2, vec1;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
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
NOTHROW(FCALL p64_npagedir_maphint)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                    PAGEDIR_PAGEALIGNED size_t num_bytes,
                                    VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	size_t i;
	u64 e1_word;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	assertf(IS_ALIGNED((uintptr_t)num_bytes, 4096), "num_bytes = %#Ix", num_bytes);
	assertf((uintptr_t)addr + num_bytes >= (uintptr_t)addr, "Invalid range %p...%p",
	        addr, (uintptr_t)addr + num_bytes - 1);
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
#else /* CONFIG_USE_NEW_PAGING */
INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_maphintone)(VIRT vm_vpage_t virt_page,
                                      VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	unsigned int vec4, vec3, vec2, vec1;
	assertf(virt_page <= __ARCH_PAGEID_MAX, "Invalid page %p", (u64)virt_page);
	assertf(IS_ALIGNED((uintptr_t)hint, PAGEDIR_MAPHINT_ALIGNMENT), "hint = %p", hint);
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(virt_page);
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(virt_page);
	p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1, (u64)(uintptr_t)hint | P64_PAGE_FISAHINT);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_maphint)(VIRT vm_vpage_t virt_page, size_t num_pages,
                                   VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	size_t i;
	u64 e1_word;
	assertf(virt_page <= __ARCH_PAGEID_MAX, "Invalid page range %p...%p", (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages >= virt_page, "Invalid page %p...%p", (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages <= __ARCH_PAGEID_MAX, "Invalid page %p...%p", (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(IS_ALIGNED((uintptr_t)hint, PAGEDIR_MAPHINT_ALIGNMENT), "hint = %p", hint);
	e1_word = (u64)(uintptr_t)hint | P64_PAGE_FISAHINT;
	for (i = 0; i < num_pages; ++i) {
		unsigned int vec4, vec3, vec2, vec1;
		vm_vpage_t effective_virt_page = virt_page + i;
		vec4 = P64_PDIR_VEC4INDEX_VPAGE(effective_virt_page);
		vec3 = P64_PDIR_VEC3INDEX_VPAGE(effective_virt_page);
		vec2 = P64_PDIR_VEC2INDEX_VPAGE(effective_virt_page);
		vec1 = P64_PDIR_VEC1INDEX_VPAGE(effective_virt_page);
		p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1, e1_word);
	}
}
#endif /* !CONFIG_USE_NEW_PAGING */

/* Return the given of the given page, or NULL if no hint has been mapped. */
#ifdef CONFIG_USE_NEW_PAGING
INTERN NOBLOCK WUNUSED void *
NOTHROW(FCALL p64_npagedir_gethint)(VIRT void *addr) {
	uintptr_t word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	assert(P64_PDIR_E4_IDENTITY[vec4].p_word & P64_PAGE_FPRESENT);
	assert(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word & P64_PAGE_FPRESENT);
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
#else /* CONFIG_USE_NEW_PAGING */
INTERN NOBLOCK WUNUSED void *
NOTHROW(FCALL p64_pagedir_gethint)(VIRT vm_vpage_t virt_page) {
	uintptr_t word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(virt_page);
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(virt_page);
	assert(P64_PDIR_E4_IDENTITY[vec4].p_word & P64_PAGE_FPRESENT);
	assert(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word & P64_PAGE_FPRESENT);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if unlikely(!(word & P64_PAGE_FPRESENT))
		return NULL; /* Not mapped */
	if unlikely(word & P64_PAGE_F2MIB)
		return NULL; /* 2MiB page */
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(virt_page);
	word = ATOMIC_READ(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word);
	if unlikely(!P64_PDIR_E1_ISHINT(word))
		return NULL;
	return (void *)(uintptr_t)(word & (uintptr_t)P64_PAGE_FHINT);
}
#endif /* !CONFIG_USE_NEW_PAGING */




/* Create/delete a page-directory mapping.
 * @param: perm: A set of `PAGEDIR_MAP_F*' detailing how memory should be mapped. */
#ifdef CONFIG_USE_NEW_PAGING
INTERN NOBLOCK void
NOTHROW(FCALL p64_npagedir_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                                   u16 perm) {
	u64 e1_word;
	unsigned int vec4, vec3, vec2, vec1;
	e1_word = p64_pagedir_encode_4kib(addr, phys, perm);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1, e1_word);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_npagedir_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                PAGEDIR_PAGEALIGNED size_t num_bytes,
                                PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                                u16 perm) {
	size_t i;
	u64 e1_word;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	assertf(IS_ALIGNED((uintptr_t)num_bytes, 4096), "num_bytes = %#Ix", num_bytes);
	assertf((uintptr_t)addr + num_bytes >= (uintptr_t)addr, "Invalid range %p...%p",
	        addr, (uintptr_t)addr + num_bytes - 1);
	e1_word = p64_pagedir_encode_4kib(addr, phys, perm);
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
#else /* CONFIG_USE_NEW_PAGING */
INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_mapone)(VIRT vm_vpage_t virt_page,
                                  PHYS pageptr_t phys_page, u16 perm) {
	u64 e1_word;
	unsigned int vec4, vec3, vec2, vec1;
	e1_word = p64_pagedir_encode_4kib(virt_page, phys_page, perm);
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(virt_page);
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(virt_page);
	p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1, e1_word);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_map)(VIRT vm_vpage_t virt_page, size_t num_pages,
                               PHYS pageptr_t phys_page, u16 perm) {
	size_t i;
	u64 e1_word;
	assertf(virt_page <= __ARCH_PAGEID_MAX, "Invalid page range %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages >= virt_page, "Invalid page %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages <= __ARCH_PAGEID_MAX, "Invalid page %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	e1_word = p64_pagedir_encode_4kib(virt_page, phys_page, perm);
	for (i = 0; i < num_pages; ++i) {
		unsigned int vec4, vec3, vec2, vec1;
		vm_vpage_t effective_virt_page = virt_page + i;
		vec4 = P64_PDIR_VEC4INDEX_VPAGE(effective_virt_page);
		vec3 = P64_PDIR_VEC3INDEX_VPAGE(effective_virt_page);
		vec2 = P64_PDIR_VEC2INDEX_VPAGE(effective_virt_page);
		vec1 = P64_PDIR_VEC1INDEX_VPAGE(effective_virt_page);
		p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1, e1_word);
		e1_word += 4096;
	}
}
#endif /* !CONFIG_USE_NEW_PAGING */

/* Special variants of `pagedir_mapone()' that should be used to
 * temporary override the mapping of a single, prepared page.
 * These functions are mainly intended for use with `this_trampoline_page', allowing
 * each thread to push/pop its trampoline page, with doing so actually being an atomic
 * operation in the sense that the data is entirely thread-private, while modifications
 * do not require any kind of lock.
 * NOTE: If the page had been mapped, `pagedir_pop_mapone()' will automatically sync the page. */
#ifdef CONFIG_USE_NEW_PAGING
INTERN NOBLOCK WUNUSED pagedir_pushval_t
NOTHROW(FCALL p64_npagedir_push_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                        PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                                        u16 perm) {
	u64 e1_word, result;
	unsigned int vec4, vec3, vec2, vec1;
	e1_word = p64_pagedir_encode_4kib(addr, phys, perm);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	result = p64_pagedir_xch_e1_word(vec4, vec3, vec2, vec1, e1_word);
	return result;
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_npagedir_pop_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       pagedir_pushval_t backup) {
	u64 old_word;
	unsigned int vec4, vec3, vec2, vec1;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	old_word = p64_pagedir_xch_e1_word(vec4, vec3, vec2, vec1, backup);
	if (old_word & P64_PAGE_FPRESENT)
		npagedir_syncone(addr); /* The old mapping was also present (explicitly refresh the page). */
}
#else /* CONFIG_USE_NEW_PAGING */
INTERN NOBLOCK WUNUSED pagedir_pushval_t
NOTHROW(FCALL p64_pagedir_push_mapone)(VIRT vm_vpage_t virt_page,
                                       PHYS pageptr_t phys_page, u16 perm) {
	u64 e1_word, result;
	unsigned int vec4, vec3, vec2, vec1;
	e1_word = p64_pagedir_encode_4kib(virt_page, phys_page, perm);
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(virt_page);
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(virt_page);
	result = p64_pagedir_xch_e1_word(vec4, vec3, vec2, vec1, e1_word);
	return result;
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_pop_mapone)(VIRT vm_vpage_t virt_page,
                                      pagedir_pushval_t backup) {
	u64 old_word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(virt_page);
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(virt_page);
	old_word = p64_pagedir_xch_e1_word(vec4, vec3, vec2, vec1, backup);
	if (old_word & P64_PAGE_FPRESENT)
		pagedir_syncone(virt_page); /* The old mapping was also present (explicitly refresh the page). */
}
#endif /* !CONFIG_USE_NEW_PAGING */

/* Unmap pages from the given address range. (requires that the given area be prepared) */
#ifdef CONFIG_USE_NEW_PAGING
INTERN NOBLOCK void
NOTHROW(FCALL p64_npagedir_unmapone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec4, vec3, vec2, vec1;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1,
	                        P64_PAGE_ABSENT | P64_PAGE_FPREPARED);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_npagedir_unmap)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED size_t num_bytes) {
	size_t i;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	assertf(IS_ALIGNED((uintptr_t)num_bytes, 4096), "num_bytes = %#Ix", num_bytes);
	assertf((uintptr_t)addr + num_bytes >= (uintptr_t)addr, "Invalid range %p...%p",
	        addr, (uintptr_t)addr + num_bytes - 1);
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
#else /* CONFIG_USE_NEW_PAGING */
INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unmapone)(VIRT vm_vpage_t virt_page) {
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(virt_page);
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(virt_page);
	p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1,
	                        P64_PAGE_ABSENT | P64_PAGE_FPREPARED);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unmap)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	size_t i;
	assertf(virt_page <= __ARCH_PAGEID_MAX, "Invalid page range %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages >= virt_page, "Invalid page %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages <= __ARCH_PAGEID_MAX, "Invalid page %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	for (i = 0; i < num_pages; ++i) {
		unsigned int vec4, vec3, vec2, vec1;
		vm_vpage_t effective_virt_page = virt_page + i;
		vec4 = P64_PDIR_VEC4INDEX_VPAGE(effective_virt_page);
		vec3 = P64_PDIR_VEC3INDEX_VPAGE(effective_virt_page);
		vec2 = P64_PDIR_VEC2INDEX_VPAGE(effective_virt_page);
		vec1 = P64_PDIR_VEC1INDEX_VPAGE(effective_virt_page);
		p64_pagedir_set_e1_word(vec4, vec3, vec2, vec1,
		                        P64_PAGE_ABSENT | P64_PAGE_FPREPARED);
	}
}
#endif /* !CONFIG_USE_NEW_PAGING */

/* Remove write-permissions from the given address range. (requires that the given area be prepared) */
#ifdef CONFIG_USE_NEW_PAGING
INTERN NOBLOCK void
NOTHROW(FCALL p64_npagedir_unwriteone)(PAGEDIR_PAGEALIGNED VIRT void *addr) {
	unsigned int vec4, vec3, vec2, vec1;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	vec4 = P64_PDIR_VEC3INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	vec1 = P64_PDIR_VEC1INDEX(addr);
	p64_pagedir_and_e1_word(vec4, vec3, vec2, vec1, ~P64_PAGE_FWRITE);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_npagedir_unwrite)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                    PAGEDIR_PAGEALIGNED size_t num_bytes) {
	size_t i;
	assertf(IS_ALIGNED((uintptr_t)addr, 4096), "addr = %p", addr);
	assertf(IS_ALIGNED((uintptr_t)num_bytes, 4096), "num_bytes = %#Ix", num_bytes);
	assertf((uintptr_t)addr + num_bytes >= (uintptr_t)addr, "Invalid range %p...%p",
	        addr, (uintptr_t)addr + num_bytes - 1);
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
#else /* CONFIG_USE_NEW_PAGING */
INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unwriteone)(VIRT vm_vpage_t virt_page) {
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(virt_page);
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(virt_page);
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(virt_page);
	p64_pagedir_and_e1_word(vec4, vec3, vec2, vec1, ~P64_PAGE_FWRITE);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unwrite)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	size_t i;
	assertf(virt_page <= __ARCH_PAGEID_MAX, "Invalid page range %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages >= virt_page, "Invalid page %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	assertf(virt_page + num_pages <= __ARCH_PAGEID_MAX, "Invalid page %I64p...%I64p",
	        (u64)virt_page, (u64)virt_page + num_pages - 1);
	for (i = 0; i < num_pages; ++i) {
		unsigned int vec4, vec3, vec2, vec1;
		vm_vpage_t effective_virt_page = virt_page + i;
		vec4 = P64_PDIR_VEC4INDEX_VPAGE(effective_virt_page);
		vec3 = P64_PDIR_VEC3INDEX_VPAGE(effective_virt_page);
		vec2 = P64_PDIR_VEC2INDEX_VPAGE(effective_virt_page);
		vec1 = P64_PDIR_VEC1INDEX_VPAGE(effective_virt_page);
		p64_pagedir_and_e1_word(vec4, vec3, vec2, vec1, ~P64_PAGE_FWRITE);
	}
}
#endif /* !CONFIG_USE_NEW_PAGING */


/* Unmap the entirety of user-space.
 * NOTE: Unlike all other unmap() functions, this one guaranties that it
 *       can perform the task without needing to allocate more memory! */
INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unmap_userspace)(struct vm *__restrict sync_vm) {
	unsigned int free_count = 0;
	unsigned int vec4;
	u64 free_pages[64];
#define FREEPAGE(pageptr)                                                        \
	do {                                                                         \
		if unlikely(free_count >= COMPILER_LENOF(free_pages)) {                  \
			/* Must sync memory before we can actually delete pages.             \
			 * Otherwise, other CPUs may still be using the mappings after       \
			 * they've already been re-designated as general-purpose RAM, at     \
			 * which point they'd start reading garbage, or corrupt pointers. */ \
			vm_syncall_locked(sync_vm);                                          \
			page_freeone(pageptr);                                               \
			do {                                                                 \
				--free_count;                                                    \
				page_freeone((pageptr_t)free_pages[free_count]);                 \
			} while (free_count);                                                \
		}                                                                        \
		else {                                                                   \
			free_pages[free_count++] = (u64)(pageptr);                           \
		}                                                                        \
	} __WHILE0
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
				FREEPAGE((pageptr_t)((e2.p_word & P64_PAGE_FVECTOR) / 4096));
			}
			ATOMIC_WRITE(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word, P64_PAGE_ABSENT);
			FREEPAGE((pageptr_t)((e3.p_word & P64_PAGE_FVECTOR) / 4096));
		}
		ATOMIC_WRITE(P64_PDIR_E4_IDENTITY[vec4].p_word, P64_PAGE_ABSENT);
		FREEPAGE((pageptr_t)((e4.p_word & P64_PAGE_FVECTOR) / 4096));
	}
	/* Free any remaining pages. */
	if (free_count) {
		vm_syncall_locked(sync_vm);
		do {
			--free_count;
			page_freeone((pageptr_t)free_pages[free_count]);
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
				page_freeone((pageptr_t)((e2.p_word & P64_PAGE_FVECTOR) / 4096));
			}
			ATOMIC_WRITE(P64_PDIR_E3_IDENTITY[vec4][vec3].p_word, P64_PAGE_ABSENT);
			page_freeone((pageptr_t)((e3.p_word & P64_PAGE_FVECTOR) / 4096));
		}
		ATOMIC_WRITE(P64_PDIR_E4_IDENTITY[vec4].p_word, P64_PAGE_ABSENT);
		page_freeone((pageptr_t)((e4.p_word & P64_PAGE_FVECTOR) / 4096));
	}
}


/* Translate a virtual address into its physical counterpart. */
INTERN NOBLOCK WUNUSED PHYS vm_phys_t
NOTHROW(FCALL p64_pagedir_translate)(VIRT void *addr) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX(addr);
	vec3 = P64_PDIR_VEC3INDEX(addr);
	vec2 = P64_PDIR_VEC2INDEX(addr);
	assert(P64_PDIR_E4_IDENTITY[vec4].p_word & P64_PAGE_FPRESENT);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	assertf(word & P64_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	if unlikely(word & P64_PAGE_F1GIB)
		return (vm_phys_t)((word & P64_PAGE_FADDR_1GIB) | P64_PDIR_PAGEINDEX_1GIB(addr));
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	assertf(word & P64_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	if unlikely(word & P64_PAGE_F2MIB)
		return (vm_phys_t)((word & P64_PAGE_FADDR_2MIB) | P64_PDIR_PAGEINDEX_2MIB(addr));
	vec1 = P64_PDIR_VEC1INDEX(addr);
	word = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word;
	assertf(word & P64_PAGE_FPRESENT, "Page at %p is not mapped", addr);
	return (vm_phys_t)((word & P64_PAGE_FADDR_4KIB) | P64_PDIR_PAGEINDEX_4KIB(addr));
}

/* Check if the given page is mapped. */
#ifdef CONFIG_USE_NEW_PAGING
INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_npagedir_ismapped)(VIRT void *addr) {
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

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_npagedir_iswritable)(VIRT void *addr) {
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

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_npagedir_isuseraccessible)(VIRT void *addr) {
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

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_npagedir_isuserwritable)(VIRT void *addr) {
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

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_npagedir_haschanged)(VIRT void *addr) {
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
NOTHROW(FCALL p64_npagedir_unsetchanged)(VIRT void *addr) {
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
			return;
	} while (!ATOMIC_CMPXCH_WEAK(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word,
	                             word, word & ~P64_PAGE_FDIRTY));
}
#else /* CONFIG_USE_NEW_PAGING */
INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_ismapped)(VIRT vm_vpage_t vpage) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(vpage);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(vpage);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F1GIB)
		return true;
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(vpage);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F2MIB)
		return true;
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(vpage);
	word = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word;
	return (word & P64_PAGE_FPRESENT) != 0;
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_iswritable)(VIRT vm_vpage_t vpage) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(vpage);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(vpage);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F1GIB)
		return (word & P64_PAGE_FWRITE) != 0;
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(vpage);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F2MIB)
		return (word & P64_PAGE_FWRITE) != 0;
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(vpage);
	word = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word;
	return (word & (P64_PAGE_FPRESENT | P64_PAGE_FWRITE)) ==
	       /*   */ (P64_PAGE_FPRESENT | P64_PAGE_FWRITE);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_isuseraccessible)(VIRT vm_vpage_t vpage) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(vpage);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(vpage);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F1GIB)
		return (word & P64_PAGE_FUSER) != 0;
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(vpage);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F2MIB)
		return (word & P64_PAGE_FUSER) != 0;
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(vpage);
	word = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word;
	return (word & (P64_PAGE_FPRESENT | P64_PAGE_FUSER)) ==
	       /*   */ (P64_PAGE_FPRESENT | P64_PAGE_FUSER);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_isuserwritable)(VIRT vm_vpage_t vpage) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(vpage);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(vpage);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F1GIB)
		return (word & (P64_PAGE_FUSER | P64_PAGE_FWRITE)) ==
		       /*   */ (P64_PAGE_FUSER | P64_PAGE_FWRITE);
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(vpage);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F2MIB)
		return (word & (P64_PAGE_FUSER | P64_PAGE_FWRITE)) ==
		       /*   */ (P64_PAGE_FUSER | P64_PAGE_FWRITE);
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(vpage);
	word = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word;
	return (word & (P64_PAGE_FPRESENT | P64_PAGE_FUSER | P64_PAGE_FWRITE)) ==
	       /*   */ (P64_PAGE_FPRESENT | P64_PAGE_FUSER | P64_PAGE_FWRITE);
}

INTERN NOBLOCK WUNUSED bool
NOTHROW(FCALL p64_pagedir_haschanged)(VIRT vm_vpage_t vpage) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	/* TODO: Figure out a better design for this function
	 *       The current system is written under the assumption that 4MiB pages don't exist... */
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(vpage);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(vpage);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if (word & P64_PAGE_F1GIB)
		return true; /* 1GiB pages aren't supported for this purpose */
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(vpage);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return false;
	if unlikely(word & P64_PAGE_F2MIB)
		return true; /* 4MiB pages aren't supported for this purpose */
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(vpage);
	word = P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word;
	return (word & (P64_PAGE_FDIRTY | P64_PAGE_FPRESENT)) ==
	       /*   */ (P64_PAGE_FDIRTY | P64_PAGE_FPRESENT);
}

INTERN NOBLOCK void
NOTHROW(FCALL p64_pagedir_unsetchanged)(VIRT vm_vpage_t vpage) {
	u64 word;
	unsigned int vec4, vec3, vec2, vec1;
	/* TODO: Figure out a better design for this function
	 *       The current system is written under the assumption that 4MiB pages don't exist... */
	vec4 = P64_PDIR_VEC4INDEX_VPAGE(vpage);
	word = P64_PDIR_E4_IDENTITY[vec4].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return;
	vec3 = P64_PDIR_VEC3INDEX_VPAGE(vpage);
	word = P64_PDIR_E3_IDENTITY[vec4][vec3].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return;
	if (word & P64_PAGE_F1GIB)
		return; /* 1GiB pages aren't supported for this purpose */
	vec2 = P64_PDIR_VEC2INDEX_VPAGE(vpage);
	word = P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_word;
	if (!(word & P64_PAGE_FPRESENT))
		return;
	if unlikely(word & P64_PAGE_F2MIB)
		return; /* 4MiB pages aren't supported for this purpose */
	vec1 = P64_PDIR_VEC1INDEX_VPAGE(vpage);
	do {
		/* Allow corruption, since we do our own CMPXCH() below. */
		word = ATOMIC_READ(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word);
		if unlikely((word & (P64_PAGE_FPRESENT | P64_PAGE_FDIRTY)) ==
		            /*   */ (P64_PAGE_FPRESENT | P64_PAGE_FDIRTY))
			return;
	} while (!ATOMIC_CMPXCH_WEAK(P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word,
	                             word, word & ~P64_PAGE_FDIRTY));
}
#endif /* !CONFIG_USE_NEW_PAGING */


DEFINE_PUBLIC_ALIAS(pagedir_init, p64_pagedir_init);
DEFINE_PUBLIC_ALIAS(pagedir_fini, p64_pagedir_fini);
DEFINE_PUBLIC_ALIAS(pagedir_unmap_userspace, p64_pagedir_unmap_userspace);
DEFINE_PUBLIC_ALIAS(pagedir_unmap_userspace_nosync, p64_pagedir_unmap_userspace_nosync);
DEFINE_PUBLIC_ALIAS(pagedir_translate, p64_pagedir_translate);
#ifdef CONFIG_USE_NEW_PAGING
DEFINE_PUBLIC_ALIAS(npagedir_prepare_mapone, p64_npagedir_prepare_mapone);
DEFINE_PUBLIC_ALIAS(npagedir_unprepare_mapone, p64_npagedir_unprepare_mapone);
DEFINE_PUBLIC_ALIAS(npagedir_prepare_map, p64_npagedir_prepare_map);
DEFINE_PUBLIC_ALIAS(npagedir_prepare_map_keep, p64_npagedir_prepare_map_keep);
DEFINE_PUBLIC_ALIAS(npagedir_unprepare_map, p64_npagedir_unprepare_map);
DEFINE_PUBLIC_ALIAS(npagedir_maphintone, p64_npagedir_maphintone);
DEFINE_PUBLIC_ALIAS(npagedir_maphint, p64_npagedir_maphint);
DEFINE_PUBLIC_ALIAS(npagedir_gethint, p64_npagedir_gethint);
DEFINE_PUBLIC_ALIAS(npagedir_mapone, p64_npagedir_mapone);
DEFINE_PUBLIC_ALIAS(npagedir_map, p64_npagedir_map);
DEFINE_PUBLIC_ALIAS(npagedir_push_mapone, p64_npagedir_push_mapone);
DEFINE_PUBLIC_ALIAS(npagedir_pop_mapone, p64_npagedir_pop_mapone);
DEFINE_PUBLIC_ALIAS(npagedir_unmapone, p64_npagedir_unmapone);
DEFINE_PUBLIC_ALIAS(npagedir_unmap, p64_npagedir_unmap);
DEFINE_PUBLIC_ALIAS(npagedir_unwriteone, p64_npagedir_unwriteone);
DEFINE_PUBLIC_ALIAS(npagedir_unwrite, p64_npagedir_unwrite);
DEFINE_PUBLIC_ALIAS(npagedir_ismapped, p64_npagedir_ismapped);
DEFINE_PUBLIC_ALIAS(npagedir_iswritable, p64_npagedir_iswritable);
DEFINE_PUBLIC_ALIAS(npagedir_isuseraccessible, p64_npagedir_isuseraccessible);
DEFINE_PUBLIC_ALIAS(npagedir_isuserwritable, p64_npagedir_isuserwritable);
DEFINE_PUBLIC_ALIAS(npagedir_haschanged, p64_npagedir_haschanged);
DEFINE_PUBLIC_ALIAS(npagedir_unsetchanged, p64_npagedir_unsetchanged);
#else /* CONFIG_USE_NEW_PAGING */
DEFINE_PUBLIC_ALIAS(pagedir_prepare_mapone, p64_pagedir_prepare_mapone);
DEFINE_PUBLIC_ALIAS(pagedir_unprepare_mapone, p64_pagedir_unprepare_mapone);
DEFINE_PUBLIC_ALIAS(pagedir_prepare_map, p64_pagedir_prepare_map);
DEFINE_PUBLIC_ALIAS(pagedir_prepare_map_keep, p64_pagedir_prepare_map_keep);
DEFINE_PUBLIC_ALIAS(pagedir_unprepare_map, p64_pagedir_unprepare_map);
DEFINE_PUBLIC_ALIAS(pagedir_maphintone, p64_pagedir_maphintone);
DEFINE_PUBLIC_ALIAS(pagedir_maphint, p64_pagedir_maphint);
DEFINE_PUBLIC_ALIAS(pagedir_gethint, p64_pagedir_gethint);
DEFINE_PUBLIC_ALIAS(pagedir_mapone, p64_pagedir_mapone);
DEFINE_PUBLIC_ALIAS(pagedir_map, p64_pagedir_map);
DEFINE_PUBLIC_ALIAS(pagedir_push_mapone, p64_pagedir_push_mapone);
DEFINE_PUBLIC_ALIAS(pagedir_pop_mapone, p64_pagedir_pop_mapone);
DEFINE_PUBLIC_ALIAS(pagedir_unmapone, p64_pagedir_unmapone);
DEFINE_PUBLIC_ALIAS(pagedir_unmap, p64_pagedir_unmap);
DEFINE_PUBLIC_ALIAS(pagedir_unwriteone, p64_pagedir_unwriteone);
DEFINE_PUBLIC_ALIAS(pagedir_unwrite, p64_pagedir_unwrite);
DEFINE_PUBLIC_ALIAS(pagedir_ismapped, p64_pagedir_ismapped);
DEFINE_PUBLIC_ALIAS(pagedir_iswritable, p64_pagedir_iswritable);
DEFINE_PUBLIC_ALIAS(pagedir_isuseraccessible, p64_pagedir_isuseraccessible);
DEFINE_PUBLIC_ALIAS(pagedir_isuserwritable, p64_pagedir_isuserwritable);
DEFINE_PUBLIC_ALIAS(pagedir_haschanged, p64_pagedir_haschanged);
DEFINE_PUBLIC_ALIAS(pagedir_unsetchanged, p64_pagedir_unsetchanged);
#endif /* !CONFIG_USE_NEW_PAGING */


INTERN ATTR_FREETEXT ATTR_CONST union p64_pdir_e1 *
NOTHROW(FCALL x86_get_cpu_iob_pointer_p64)(struct cpu *__restrict self) {
	union p64_pdir_e1 *e1_pointer;
	uintptr_t iobp;
	iobp       = (uintptr_t)&FORCPU(self, thiscpu_x86_iob[0]);
	e1_pointer = &P64_PDIR_E1_IDENTITY[P64_PDIR_VEC4INDEX(iobp)]
	                                  [P64_PDIR_VEC3INDEX(iobp)]
	                                  [P64_PDIR_VEC2INDEX(iobp)]
	                                  [P64_PDIR_VEC1INDEX(iobp)];
	return e1_pointer;
}

PRIVATE ATTR_FREERODATA byte_t const
x86_pagedir_syncall_cr3_text[] = {
	/* TODO: Re-write this assembly for x86_64! */
	0x0f, 0x20, 0xd8, /* movl %cr3, %eax             */
	0x0f, 0x22, 0xd8, /* movl %eax, %cr3             */
	                  /* --- TLB reload happens here */
	0xc3              /* ret                         */
};

PRIVATE ATTR_FREERODATA byte_t const
x86_pagedir_syncall_cr4_text[] = {
	/* TODO: Re-write this assembly for x86_64! */
	0x9c,                            /* pushfl                      */
	0xfa,                            /* cli                         */
	0x0f, 0x20, 0xe0,                /* movl   %cr4, %eax           */
	0x8d, 0x48, ((-CR4_PGE) & 0xff), /* leal   -CR4_PGE(%eax), %ecx */
	0x0f, 0x22, 0xe1,                /* movl   %ecx, %cr4           */
	                                 /* --- TLB reload happens here */
	0x0f, 0x22, 0xe0,                /* movl   %eax, %cr4           */
	0x9d,                            /* popfl                       */
	0xc3,                            /* ret                         */
};

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_paging)(void) {
	/* Configure paging */
	if (!HAVE_PAGE_GLOBAL_BIT)
		used_pxx_page_fglobal = 0;
	if (!HAVE_EXECUTE_DISABLE) {
		unsigned int i;
		for (i = 0; i < COMPILER_LENOF(p64_pageperm_matrix); ++i)
			p64_pageperm_matrix[i] &= ~P64_PAGE_FNOEXEC;
	}

	/* Check if we must re-write our implementation of `pagedir_syncall()'.
	 * Currently, it looks like this:
	 * >> movq   $2, %rax
	 * >> invpcid (%rax), %rax // The first operand is ignored.
	 * >> ret */
	if (!HAVE_PAGE_GLOBAL_BIT) {
		/* If global TLBs don't exist, we can simply use the mov-to-cr3 trick to flush TLBs */
		/* Also: Since global TLBs don't exist, we can re-write `x86_pagedir_syncall_maybe_global'
		 *       to always unconditionally reload cr3 with the same code we already use
		 *       for `pagedir_syncall' */
		memcpy((void *)&pagedir_syncall, x86_pagedir_syncall_cr3_text, sizeof(x86_pagedir_syncall_cr3_text));
		memcpy((void *)&x86_pagedir_syncall_maybe_global, x86_pagedir_syncall_cr3_text, sizeof(x86_pagedir_syncall_cr3_text));
	} else if (!HAVE_INSTR_INVPCID) {
		/* From `4.10.4.1     Operations that Invalidate TLBs and Paging-Structure Caches'
		 *  `MOV to CR4. The behavior of the instruction depends on the bits being modified:'
		 *   `The instruction invalidates all TLB entries (including global entries) and all entries
		 *    in all paging-structure caches (for all PCIDs) if ... it changes the value of CR4.PGE ...' */
		/* In other words: Toggling the PGE bit twice will get rid of all global TLBs */
		memcpy((void *)&pagedir_syncall, x86_pagedir_syncall_cr4_text, sizeof(x86_pagedir_syncall_cr4_text));
	}


	/* Initialize the `_bootcpu.thiscpu_x86_iobnode_pagedir_identity' pointer. */
	FORCPU(&_bootcpu, thiscpu_x86_iobnode_pagedir_identity) = x86_get_cpu_iob_pointer_p64(&_bootcpu);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING64_C_INL */
