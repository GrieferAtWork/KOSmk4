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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_PAGING64_C_INL
#define GUARD_KERNEL_CORE_ARCH_I386_PAGING64_C_INL 1
#define _KOS_SOURCE 1
#define __VM_INTERNAL_EXCLUDE_PAGEDIR 1
#define __OMIT_PAGING_CONSTANT_P_WRAPPERS 1

#include <kernel/compiler.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/vm.h>
#include <kernel/panic.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <asm/intrin.h>

DECL_BEGIN

typedef union x86_pdir_e1 E1;
typedef union x86_pdir_e2 E2;
typedef union x86_pdir_e3 E3;
typedef union x86_pdir_e4 E4;
typedef union {
	E1 e1;
	E2 e2;
	E3 e3;
	E4 e4;
} ENT;


STATIC_ASSERT(sizeof(E1) == 8);
STATIC_ASSERT(sizeof(E2) == 8);
STATIC_ASSERT(sizeof(E3) == 8);
STATIC_ASSERT(sizeof(E4) == 8);
STATIC_ASSERT(sizeof(struct x86_pdir) == X86_PDIR_SIZE);

STATIC_ASSERT(X86_PDIR_E2_IDENTITY_BASE == X86_PDIR_E1_IDENTITY_BASE + (X86_PDIR_VEC4INDEX(X86_PDIR_E1_IDENTITY_BASE) * X86_PDIR_E3_SIZE));
STATIC_ASSERT(X86_PDIR_E3_IDENTITY_BASE == X86_PDIR_E2_IDENTITY_BASE + (X86_PDIR_VEC3INDEX(X86_PDIR_E2_IDENTITY_BASE) * X86_PDIR_E2_SIZE));
STATIC_ASSERT(X86_PDIR_E4_IDENTITY_BASE == X86_PDIR_E3_IDENTITY_BASE + (X86_PDIR_VEC2INDEX(X86_PDIR_E3_IDENTITY_BASE) * X86_PDIR_E1_SIZE));

STATIC_ASSERT(X86_PDIR_VEC3INDEX(X86_VM_KERNEL_PDIR_IDENTITY_BASE) == 0);
STATIC_ASSERT(X86_PDIR_VEC2INDEX(X86_VM_KERNEL_PDIR_IDENTITY_BASE) == 0);
STATIC_ASSERT(X86_PDIR_VEC1INDEX(X86_VM_KERNEL_PDIR_IDENTITY_BASE) == 0);

FORCELOCAL void KCALL inplace_movq(u64 &dst, u64 src) {
	__asm__ __volatile__("movq %1, %0"
	                     : "+m" (dst)
	                     : "Ir" (src)
	                     : "cc", "memory");
}

FORCELOCAL void KCALL inplace_andq(u64 &lhs, u64 rhs) {
	__asm__ __volatile__("andq %1, %0"
	                     : "+m" (lhs)
	                     : "Ir" (rhs)
	                     : "cc", "memory");
}

FORCELOCAL void KCALL inplace_orq(u64 &lhs, u64 rhs) {
	__asm__ __volatile__("orq %1, %0"
	                     : "+m" (lhs)
	                     : "Ir" (rhs)
	                     : "cc", "memory");
}



/* Allocate BSS memory for the shared mapping area of
 * the upper half of every page directory that gets
 * shared by all of them and represents kernel-space.
 * These are the individual E3 vectors for the top-most
 * 256 entries of every `struct x86_pdir::p_e4'
 * Each of these entires represents 1GiB of mappable
 * virtual memory.
 * To account for the kernel itself, we use:
 *   - PAGEDIR[511][510]  -- Identity mapping of the first 1GiB of physical memory
 *                           This is where the kernel core runs from
 *   - PAGEDIR[511][511]  -- Contains all of the dynamically loaded drivers.
 *                           Placed here so that all drivers can still assume to be
 *                           loaded within the -2GiB ... +2GiB memory range allowing
 *                           for 32-bit sign-extended addressing.
 *   - PAGEDIR[0...255]   -- User-space
 *   - PAGEDIR[256]       -- (Usually) unused (although only the first page must remain empty)
 *   - PAGEDIR[257]       -- Reserved for the page directory self-mapping (X86_VM_KERNEL_PDIR_IDENTITY_BASE)
 *   - PAGEDIR[258...510] -- Available for general-purpose kernel-space usage.
 * Mapping to the entires of this vector:
 *   - PAGEDIR[256]   --> __x86_pagedir_kernel_share_e3[0]
 *   - PAGEDIR[257]   --> Special:self-mapping
 *   - PAGEDIR[258+n] --> __x86_pagedir_kernel_share_e3[1+n]
 *   - PAGEDIR[511]   --> __x86_pagedir_kernel_share_e3[254]
 */
INTERN ATTR_ALIGNED(PAGESIZE) ATTR_SECTION(".bss.x86.pagedir_kernel_share")
VIRT union x86_pdir_e3 __x86_pagedir_kernel_share_e3[256 - 1][512];

/* In the event that the host doesn't support 1GiB pages, this vector is
 * used to populate PAGEDIR[511][510] with the 1GiB mapping of 512 2MiB
 * pages that contain the kernel core itself (aka. mapping -2GiB...-1GiB
 * as an identity mapping of physical memory at 0...1GiB)
 * Note that any processor supporting 4-level paging also supports 2MiB
 * pages, so there's no need to allocate .bss for an E1 vector. */
INTERN ATTR_ALIGNED(PAGESIZE) ATTR_SECTION(".bss.x86.pagedir_kernel_share")
VIRT union x86_pdir_e2 __x86_pagedir_kernel_share_e2[1][512];



INTDEF byte_t __kernel_pervm_size[];

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
		/* .vn_prot   = */ 0xcccc,
		/* .vn_flags  = */ 0xcccc,
		/* .vn_vm     = */ (struct vm *)UINT64_C(0xcccccccccccccccc),
		/* .vn_part   = */ (struct vm_datapart *)UINT64_C(0xcccccccccccccccc),
		/* .vn_block  = */ (struct vm_datablock *)UINT64_C(0xcccccccccccccccc),
		/* .vn_link   = */ { (struct vm_node *)UINT64_C(0xcccccccccccccccc),
		                     (struct vm_node **)UINT64_C(0xcccccccccccccccc) },
		/* .vn_guard  = */ UINT64_C(0xcccccccccccccccc)
	}
};


PRIVATE u64 x86_pageperm_matrix[0xf+1] = {
	/* Configure to always set the DIRTY and ACCESSED bits (KOS doesn't
	 * use `DIRTY', and us already setting them will allow the CPU to skip
	 * setting them if the time comes) */
	[0]                                                                        = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FNOEXEC,
	[PAGEDIR_MAP_FEXEC]                                                        = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FPRESENT,
	[PAGEDIR_MAP_FWRITE]                                                       = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FPRESENT|X86_PAGE_FWRITE|X86_PAGE_FNOEXEC,
	[PAGEDIR_MAP_FWRITE|PAGEDIR_MAP_FEXEC]                                     = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FPRESENT|X86_PAGE_FWRITE,
	[PAGEDIR_MAP_FREAD]                                                        = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FPRESENT|X86_PAGE_FNOEXEC,
	[PAGEDIR_MAP_FREAD|PAGEDIR_MAP_FEXEC]                                      = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FPRESENT,
	[PAGEDIR_MAP_FREAD|PAGEDIR_MAP_FWRITE]                                     = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FPRESENT|X86_PAGE_FWRITE|X86_PAGE_FNOEXEC,
	[PAGEDIR_MAP_FREAD|PAGEDIR_MAP_FWRITE|PAGEDIR_MAP_FEXEC]                   = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FPRESENT|X86_PAGE_FWRITE,
	[PAGEDIR_MAP_FUSER]                                                        = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FUSER|X86_PAGE_FNOEXEC,
	[PAGEDIR_MAP_FUSER|PAGEDIR_MAP_FEXEC]                                      = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FUSER|X86_PAGE_FPRESENT,
	[PAGEDIR_MAP_FUSER|PAGEDIR_MAP_FWRITE]                                     = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FUSER|X86_PAGE_FPRESENT|X86_PAGE_FWRITE|X86_PAGE_FNOEXEC,
	[PAGEDIR_MAP_FUSER|PAGEDIR_MAP_FEXEC|PAGEDIR_MAP_FWRITE]                   = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FUSER|X86_PAGE_FPRESENT|X86_PAGE_FWRITE,
	[PAGEDIR_MAP_FUSER|PAGEDIR_MAP_FREAD]                                      = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FUSER|X86_PAGE_FPRESENT|X86_PAGE_FNOEXEC,
	[PAGEDIR_MAP_FUSER|PAGEDIR_MAP_FREAD|PAGEDIR_MAP_FEXEC]                    = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FUSER|X86_PAGE_FPRESENT,
	[PAGEDIR_MAP_FUSER|PAGEDIR_MAP_FREAD|PAGEDIR_MAP_FWRITE]                   = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FUSER|X86_PAGE_FPRESENT|X86_PAGE_FWRITE|X86_PAGE_FNOEXEC,
	[PAGEDIR_MAP_FUSER|PAGEDIR_MAP_FREAD|PAGEDIR_MAP_FWRITE|PAGEDIR_MAP_FEXEC] = X86_PAGE_FDIRTY|X86_PAGE_FACCESSED|X86_PAGE_FUSER|X86_PAGE_FPRESENT|X86_PAGE_FWRITE,
};

#if 1
PRIVATE u64 x86_page_used_fglobal = X86_PAGE_FGLOBAL;
PRIVATE u64 x86_page_used_fnoexec = X86_PAGE_FNOEXEC;
PRIVATE bool x86_page_have_1gib   = true;

#undef X86_PAGE_FGLOBAL
#undef X86_PAGE_FNOEXEC
#define X86_PAGE_FGLOBAL  x86_page_used_fglobal
#define X86_PAGE_FNOEXEC  x86_page_used_fnoexec
#else
#define x86_page_have_1gib true
#endif


PUBLIC NOBLOCK WUNUSED PHYS vm_phys_t
NOTHROW(FCALL pagedir_translate)(VIRT vm_virt_t virt_addr) {
	unsigned int vec1, vec2, vec3, vec4; ENT e;
	vec4 = X86_PDIR_VEC4INDEX(virt_addr);
	assertf(X86_PDIR_E4_IDENTITY[vec4].p_vec3.v_present,
	        "Page at %p is not mapped", virt_addr);
	vec3 = X86_PDIR_VEC3INDEX(virt_addr);
	e.e3 = X86_PDIR_E3_IDENTITY[vec4][vec3];
	assertf(e.e3.p_vec2.v_present, "Page at %p is not mapped", virt_addr);
	if (e.e3.p_1gib.d_1gib_1)
		return e.e3.getpageaddr(virt_addr);
	vec2 = X86_PDIR_VEC2INDEX(virt_addr);
	e.e2 = X86_PDIR_E2_IDENTITY[vec4][vec3][vec2];
	assertf(e.e2.p_vec1.v_present, "Page at %p is not mapped", virt_addr);
	if (e.e2.p_2mib.d_2mib_1)
		return e.e2.getpageaddr(virt_addr);
	vec1 = X86_PDIR_VEC1INDEX(virt_addr);
	e.e1 = X86_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1];
	assertf(e.e1.p_4kib.d_present, "Page at %p is not mapped", virt_addr);
	return e.e1.getpageaddr(virt_addr);
}


LOCAL NOBLOCK WUNUSED bool
NOTHROW(FCALL pagedir_check_bitmask)(VIRT vm_vpage_t vpage, u64 mask, u64 result) {
	unsigned int vec1, vec2, vec3, vec4; ENT e;
	vec4 = X86_PDIR_VEC4INDEX_VPAGE(vpage);
	if ((X86_PDIR_E4_IDENTITY[vec4].p_word & mask) != result)
		return false;
	vec3 = X86_PDIR_VEC3INDEX_VPAGE(vpage);
	e.e3 = X86_PDIR_E3_IDENTITY[vec4][vec3];
	if ((e.e3.p_word & mask) != result)
		return false;
	if (e.e3.p_1gib.d_1gib_1)
		return true;
	vec2 = X86_PDIR_VEC2INDEX_VPAGE(vpage);
	e.e2 = X86_PDIR_E2_IDENTITY[vec4][vec3][vec2];
	if ((e.e2.p_word & mask) != result)
		return false;
	if (e.e2.p_2mib.d_2mib_1)
		return true;
	vec1 = X86_PDIR_VEC1INDEX_VPAGE(vpage);
	e.e1 = X86_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1];
	if ((e.e1.p_word & mask) != result)
		return false;
	return true;
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL pagedir_ismapped)(VIRT vm_vpage_t vpage) {
	return pagedir_check_bitmask(vpage,
	                             X86_PAGE_FPRESENT,
	                             X86_PAGE_FPRESENT);
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL pagedir_iswritable)(VIRT vm_vpage_t vpage) {
	return pagedir_check_bitmask(vpage,
	                             X86_PAGE_FPRESENT | X86_PAGE_FWRITE,
	                             X86_PAGE_FPRESENT | X86_PAGE_FWRITE);
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL pagedir_isuseraccessible)(VIRT vm_vpage_t vpage) {
	return pagedir_check_bitmask(vpage,
	                             X86_PAGE_FPRESENT | X86_PAGE_FUSER,
	                             X86_PAGE_FPRESENT | X86_PAGE_FUSER);
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL pagedir_isuserwritable)(VIRT vm_vpage_t vpage) {
	return pagedir_check_bitmask(vpage,
	                             X86_PAGE_FPRESENT | X86_PAGE_FWRITE | X86_PAGE_FUSER,
	                             X86_PAGE_FPRESENT | X86_PAGE_FWRITE | X86_PAGE_FUSER);
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL pagedir_haschanged)(VIRT vm_vpage_t vpage) {
	unsigned int vec1, vec2, vec3, vec4; ENT e;
	vec4 = X86_PDIR_VEC4INDEX_VPAGE(vpage);
	if (!X86_PDIR_E4_IDENTITY[vec4].p_vec3.v_present)
		return false;
	vec3 = X86_PDIR_VEC3INDEX_VPAGE(vpage);
	e.e3 = X86_PDIR_E3_IDENTITY[vec4][vec3];
	if (!e.e3.p_vec2.v_present)
		return false;
	if (e.e3.p_1gib.d_1gib_1)
		return true; /* 1GiB pages aren't supported for this purpose */
	vec2 = X86_PDIR_VEC2INDEX_VPAGE(vpage);
	e.e2 = X86_PDIR_E2_IDENTITY[vec4][vec3][vec2];
	if (!e.e2.p_vec1.v_present)
		return false;
	if (e.e2.p_2mib.d_2mib_1)
		return true; /* 2MiB pages aren't supported for this purpose */
	vec1 = X86_PDIR_VEC1INDEX_VPAGE(vpage);
	e.e1 = X86_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1];
	if (!e.e1.p_4kib.d_present)
		return false;
	return e.e1.p_4kib.d_dirty;
}

PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_unsetchanged)(VIRT vm_vpage_t vpage) {
	unsigned int vec1, vec2, vec3, vec4; ENT e;
	vec4 = X86_PDIR_VEC4INDEX_VPAGE(vpage);
	if (!X86_PDIR_E4_IDENTITY[vec4].p_vec3.v_present)
		return;
	vec3 = X86_PDIR_VEC3INDEX_VPAGE(vpage);
	e.e3 = X86_PDIR_E3_IDENTITY[vec4][vec3];
	if (!e.e3.p_vec2.v_present)
		return;
	if (e.e3.p_1gib.d_1gib_1)
		return; /* 1GiB pages aren't supported for this purpose */
	vec2 = X86_PDIR_VEC2INDEX_VPAGE(vpage);
	e.e2 = X86_PDIR_E2_IDENTITY[vec4][vec3][vec2];
	if (!e.e2.p_vec1.v_present)
		return;
	if (e.e2.p_2mib.d_2mib_1)
		return; /* 2MiB pages aren't supported for this purpose */
	vec1 = X86_PDIR_VEC1INDEX_VPAGE(vpage);
	e.e1 = X86_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1];
	if (!e.e1.p_4kib.d_present)
		return;
	if (!e.e1.p_4kib.d_dirty)
		return;
	inplace_andq(X86_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1].p_word,
	             ~X86_PAGE_FDIRTY);
}


/* Initialize the given page directory.
 * The caller is required to allocate the page directory
 * controller itself, which must be aligned and sized
 * according to `PAGEDIR_ALIGN' and `PAGEDIR_SIZE'. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pagedir_init)(VIRT pagedir_t *__restrict self,
                            PHYS vm_phys_t phys_self) {
	enum { E4_IDENTITY = X86_PDIR_VEC4INDEX(X86_VM_KERNEL_PDIR_IDENTITY_BASE) };
	STATIC_ASSERT(E4_IDENTITY >= 256);
	assert(IS_ALIGNED((uintptr_t)self, PAGESIZE));
	assert(IS_ALIGNED(phys_self, PAGESIZE));
	memsetq(self->p_e4, X86_PAGE_ABSENT, 256);
	memcpyl(&self->p_e4[256], &pagedir_kernel.p_e4[256], 256);
	self->p_e4[E4_IDENTITY].p_word = ((u64)phys_self |
	                                  (X86_PAGE_FACCESSED | X86_PAGE_FWRITE |
	                                   X86_PAGE_FPRESENT | X86_PAGE_FNOEXEC));
}


/* Because we're omitting the `v_pagedir' field from the start of the VM, we have
 * to adjust for that fact when we're trying to access the `v_pdir_phys_ptr' field! */
#define VM_GET_V_PDIR_PHYS_PTR(x) \
	(*(PHYS pagedir_t **)((byte_t *)(x) + sizeof(pagedir_t) + offsetof(struct vm, v_pdir_phys_ptr)))


/* Finalize a given page directory. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pagedir_fini)(VIRT pagedir_t *__restrict self,
                            PHYS vm_phys_t phys_self) {
	unsigned int vec4;
	pflag_t old_flags = __rdflags();
	bool did_switch = false;
	assertf(VM_GET_V_PDIR_PHYS_PTR(THIS_VM) == pagedir_get(),
	        "Wrong page directory set (%p != %p)",
	        VM_GET_V_PDIR_PHYS_PTR(THIS_VM), pagedir_get());
	for (vec4 = 0; vec4 < 256; ++vec4) {
		unsigned int vec3;
		E4 e4 = self->p_e4[vec4];
		if (!e4.p_vec3.v_present)
			continue; /* Vector was never allocated. */
		if (!did_switch) {
			/* Disable interrupts while we're using an override for our page directory. */
			__cli();
			pagedir_set((PHYS pagedir_t *)phys_self);
			did_switch = true;
		}
		for (vec3 = 0; vec3 < 512; ++vec3) {
			E3 e3 = X86_PDIR_E3_IDENTITY[vec4][vec3];
			if (e3.isunused())
				continue; /* Unused, unallocated */
			if (e3.is1gib())
				continue; /* 1GiB page (not a vector) */
			if (e3.ishint())
				continue; /* Hint page */
			if (e3.p_word & X86_PAGE_FPRESENT) {
				/* Vector is populated. */
				unsigned int vec2;
				for (vec2 = 0; vec2 < 512; ++vec2) {
					E2 e2 = X86_PDIR_E2_IDENTITY[vec4][vec3][vec2];
					if (e2.isunused())
						continue; /* Unused, unallocated */
					if (e2.is2mib())
						continue; /* 2MiB page (not a vector) */
					if (e2.ishint())
						continue; /* Hint page */
#if 0
					if (e2.p_word & X86_PAGE_FPRESENT) {
						/* E1 entires don't need to be iterated.
						 * They don't require any cleanup. */
					}
#endif
					page_freeone(VM_ADDR2PAGE((vm_phys_t)(e2.p_word & X86_PAGE_FVECTOR)));
				}
			}
			page_freeone(VM_ADDR2PAGE((vm_phys_t)(e3.p_word & X86_PAGE_FVECTOR)));
		}
		page_freeone(VM_ADDR2PAGE((vm_phys_t)(e4.p_word & X86_PAGE_FVECTOR)));
	}
	if (did_switch) {
		pagedir_set(VM_GET_V_PDIR_PHYS_PTR(THIS_VM));
		__wrflags(old_flags);
	}
}




/* Prepare the page directory for a future map() operation.
 * The full cycle of a single mapping then looks like this:
 * >> pagedir_prepare_map(...);
 * >> pagedir_map(...);
 * >> pagedir_unmap(...);
 * >> pagedir_unprepare_map(...);
 * NOTE: A prepared mapping is not only valid for the exact range.
 *       Wishing to map something at a sub-range of it is also allowed:
 *       >> pagedir_prepare_map(5,6);   // Prepage 6 pages at page-index 5 for modification
 *       >> pagedir_map(5,3);           // OK
 *       >> pagedir_map(8,3);           // OK
 *       >> pagedir_unprepare_map(5,6); // Indicate that the 6 pages must not longer be modified
 * NOTE: `pagedir_prepare_map_keep()' is the same as `pagedir_prepare_map()', but
 *        will not undo already successfully made preparations after a later one fails.
 *        This will include the undoing of redundant preparations of the given range that
 *        were made in prior calls.
 * WARNING: prepare() + unprepare() _DONT_ work recursively, and are also not thread-safe
 * WARNING: unprepare() should always be called with the same range as prepare()
 * @return: true:  Successfully allocated structures required for creating mappings.
 * @return: false: Insufficient physical memory to change mappings. */
PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL pagedir_prepare_mapone)(VIRT vm_vpage_t virt_page) {
	/* TODO */
	kernel_panic_here();
}
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_unprepare_mapone)(VIRT vm_vpage_t virt_page) {
	/* TODO */
	kernel_panic_here();
}
PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL pagedir_prepare_map)(VIRT vm_vpage_t virt_page,
                                   size_t num_pages) {
	/* TODO: Make sure that start/end are mappable on alignment-based levels */
	/* TODO: Make sure that all 512GiB E4-entries between start...end have E3-vectors allocated */
	kernel_panic_here();
}
PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL pagedir_prepare_map_keep)(VIRT vm_vpage_t virt_page,
                                        size_t num_pages) {
	/* TODO: Make sure that start/end are mappable on alignment-based levels */
	/* TODO: Make sure that all 512GiB E4-entries between start...end have E3-vectors allocated */
	kernel_panic_here();
}
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_unprepare_map)(VIRT vm_vpage_t virt_page,
                                     size_t num_pages) {
	/* TODO: Try to merge 512*4KiB linear pages between FLOOR(start, 2MiB) ... CEIL(end, 2MiB) into 2MiB pages */
	/* TODO: Try to merge 512*2MiB linear pages between FLOOR(start, 1GiB) ... CEIL(end, 1GiB) into 1GiB pages (if supported) */
	kernel_panic_here();
}



/* Set a mapping hint for pages apart of the given virtual memory range.
 * Mapping hints are overwritten once a page has been mapped, and when
 * not specified, will default to `NULL'.
 * Their main purpose is to be accessible through atomic means, allowing
 * them to be used by the PAGE_FAULT handler, while still ensuring that
 * access remains non-blocking.
 * Note that because of platform-specific restrictions, only pointers
 * which are aligned by at least `PAGEDIR_MAPHINT_ALIGNMENT' bytes can
 * be specified as hints.
 *   - Use of this function requires a prior call to `pagedir_prepare_map()',
 *     following the same requirements of `pagedir_map()'. However unlike
 *     with `pagedir_map()', supplying a hint does not unprepare sub-ranges:
 *     >> pagedir_prepare_map(5,6);     // Prepare 6 pages at page-index 5 for modification
 *     >> pagedir_maphint(5,6,my_hint); // OK
 *     >> pagedir_map(5,3);             // OK (`pagedir_maphint()' doesn't unprepare sub-ranges)
 *     >> pagedir_map(8,3);             // OK
 *   - Memory mappings defined in `vm_kernel' to be non-blocking have their
 *     mapping hint set to the address of the associated `struct vm_node' */
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_maphintone)(VIRT vm_vpage_t virt_page,
                                  VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	/* TODO */
	kernel_panic_here();
}
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_maphint)(VIRT vm_vpage_t virt_page, size_t num_pages,
                               VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	/* TODO */
	kernel_panic_here();
}


/* Create/delete a page-directory mapping.
 * @param: perm: A set of `PAGEDIR_MAP_F*' detailing how memory should be mapped.
 * `pagedir_sync()' must be called while specifying a virtual address range containing
 * `virt_page...+=num_pages' in order to ensure that changes will become visible.
 * NOTE: This function can be called regardless of which page directory is active. */
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_mapone)(VIRT vm_vpage_t virt_page,
                              PHYS vm_ppage_t phys_page, u16 perm) {
	/* TODO */
	kernel_panic_here();
}
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_map)(VIRT vm_vpage_t virt_page, size_t num_pages,
                           PHYS vm_ppage_t phys_page, u16 perm) {
	/* TODO */
	kernel_panic_here();
}


/* Special variants of `pagedir_mapone()' that should be used to
 * temporary override the mapping of a single, prepared page.
 * These functions are mainly intended for use with `_this_trampoline_page', allowing
 * each thread to push/pop its trampoline page, with doing so actually being an atomic
 * operation in the sense that the data is entirely thread-private, while modifications
 * do not require any kind of lock.
 * NOTE: If the page had been mapped, `pagedir_pop_mapone()' will automatically sync the page. */
PUBLIC NOBLOCK WUNUSED uintptr_t
NOTHROW(FCALL pagedir_push_mapone)(VIRT vm_vpage_t virt_page,
                                   PHYS vm_ppage_t phys_page, u16 perm) {
	/* TODO */
	kernel_panic_here();
}
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_pop_mapone)(VIRT vm_vpage_t virt_page, uintptr_t backup) {
	/* TODO */
	kernel_panic_here();
}


/* Unmap pages from the given address range. (requires that the given area be prepared) */
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_unmapone)(VIRT vm_vpage_t virt_page) {
	/* TODO */
	kernel_panic_here();
}
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_unmap)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	/* TODO */
	kernel_panic_here();
}


/* Remove write-permissions from the given address range. (requires that the given area be prepared) */
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_unwriteone)(VIRT vm_vpage_t virt_page) {
	/* TODO */
	kernel_panic_here();
}
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_unwrite)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	/* TODO */
	kernel_panic_here();
}



/* Unmap the entirety of user-space.
 * NOTE: Unlike all other unmap() functions, this one guaranties that it
 *       can perform the task without needing to allocate more memory! */
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_unmap_userspace)(struct vm *__restrict sync_vm) {
	/* TODO */
	kernel_panic_here();
}
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_unmap_userspace_nosync)(void) {
	/* TODO */
	kernel_panic_here();
}




DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_PAGING64_C_INL */
