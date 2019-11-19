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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_C_INL
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_C_INL 1
#define _KOS_SOURCE 1
#define __VM_INTERNAL_EXCLUDE_PAGEDIR 1
#define __OMIT_PAGING_CONSTANT_P_WRAPPERS 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/tss.h>
#include <kernel/vm.h>
#include <sched/cpu.h>

#include <asm/cpu-cpuid.h>
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/intrin.h>

#include <assert.h>
#include <string.h>


/**/
#include "paging32-share.h"
#include "paging32-com.h"


#define FOREACH_PAGING_FUNCTION(callback)     \
	callback(pagedir_init);                   \
	callback(pagedir_fini);                   \
	callback(pagedir_prepare_mapone);         \
	callback(pagedir_prepare_map);            \
	callback(pagedir_prepare_map_keep);       \
	callback(pagedir_unprepare_mapone);       \
	callback(pagedir_unprepare_map);          \
	callback(pagedir_maphintone);             \
	callback(pagedir_maphint);                \
	callback(pagedir_gethint);                \
	callback(pagedir_mapone);                 \
	callback(pagedir_map);                    \
	callback(pagedir_push_mapone);            \
	callback(pagedir_pop_mapone);             \
	callback(pagedir_unmapone);               \
	callback(pagedir_unmap);                  \
	callback(pagedir_unwriteone);             \
	callback(pagedir_unwrite);                \
	callback(pagedir_unmap_userspace);        \
	callback(pagedir_unmap_userspace_nosync); \
	callback(pagedir_translate);              \
	callback(pagedir_ismapped);               \
	callback(pagedir_iswritable);             \
	callback(pagedir_isuseraccessible);       \
	callback(pagedir_isuserwritable);         \
	callback(pagedir_haschanged);             \
	callback(pagedir_unsetchanged);



DECL_BEGIN

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
		/* .vn_node   = */ { (struct vm_node *)0xcccccccc,
		                     (struct vm_node *)0xcccccccc,
		                     (vm_vpage_t)0xcccccccc,
		                     (vm_vpage_t)0xcccccccc },
		/* .vn_byaddr = */ { (struct vm_node *)0xcccccccc, (struct vm_node **)0xcccccccc },
		/* .vn_prot   = */ 0xcccc,
		/* .vn_flags  = */ 0xcccc,
		/* .vn_vm     = */ (struct vm *)0xcccccccc,
		/* .vn_part   = */ (struct vm_datapart *)0xcccccccc,
		/* .vn_block  = */ (struct vm_datablock *)0xcccccccc,
		/* .vn_link   = */ { (struct vm_node *)0xcccccccc, (struct vm_node **)0xcccccccc },
		/* .vn_guard  = */ 0xcccccccc
	}
};

/* Allocate BSS memory for the initial shared+identity mapping
 * that will later be shared with, and re-appear in all other
 * page directories (except for the identity page)
 * NOTE: This buffer is quite large (1Mb), but we'd need
 *       to allocate it sooner or later, no matter what. */
INTERN ATTR_SECTION(".bss.x86.pagedir_kernel_share")
kernel_share_t __x86_pagedir_kernel_share = {};

DECL_END


#ifdef CONFIG_NO_PAGING_PAE
/* P32 only */

#ifndef __INTELLISENSE__
#include "paging32-p32.c.inl"
#endif /* !__INTELLISENSE__ */

#define DEFINE_PUBLIC_ALIAS_PAGING_P32(name) \
	DEFINE_PUBLIC_ALIAS(name, p32_##name);
FOREACH_PAGING_FUNCTION(DEFINE_PUBLIC_ALIAS_PAGING_P32)
#undef DEFINE_PUBLIC_ALIAS_PAGING_P32

#elif defined(CONFIG_NO_PAGING_P32)
/* PAE only */

#ifndef __INTELLISENSE__
#include "paging32-pae.c.inl"
#endif /* !__INTELLISENSE__ */

#define DEFINE_PUBLIC_ALIAS_PAGING_PAE(name) \
	DEFINE_PUBLIC_ALIAS(name, pae_##name);
FOREACH_PAGING_FUNCTION(DEFINE_PUBLIC_ALIAS_PAGING_PAE)
#undef DEFINE_PUBLIC_ALIAS_PAGING_PAE

#else /* Single-Mode */

#define HYBRID_PAGING_MODE 1

#ifndef __INTELLISENSE__
#include "paging32-p32.c.inl"
#include "paging32-pae.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* Hybrid-Mode */


DECL_BEGIN


#ifdef HYBRID_PAGING_MODE
LOCAL ATTR_FREETEXT NOBLOCK void
NOTHROW(FCALL pagedir_install_jmp)(void *redirection_addr,
                                   void const *redirection_target) {
	byte_t *dst = (byte_t *)redirection_addr;
	*(u8 *)(dst + 0) = 0xe9;
	*(s32 *)(dst + 1) = ((s32)(uintptr_t)redirection_target -
	                     (s32)(uintptr_t)(dst + 5));
}
#endif /* HYBRID_PAGING_MODE */



#if !defined(CONFIG_BOOTUP_OPTIMIZE_FOR_P32) && \
    !defined(CONFIG_BOOTUP_OPTIMIZE_FOR_PAE)
#if defined(CONFIG_NO_PAGING_P32)
#define CONFIG_BOOTUP_OPTIMIZE_FOR_PAE 1
#elif defined(CONFIG_NO_PAGING_PAE)
#define CONFIG_BOOTUP_OPTIMIZE_FOR_P32 1
#else
#define CONFIG_BOOTUP_OPTIMIZE_FOR_PAE 1
#endif
#endif

#ifdef CONFIG_BOOTUP_OPTIMIZE_FOR_PAE
#define DEFINE_PUBLIC_ALIAS_PAGING_PAE(name) \
	DEFINE_PUBLIC_ALIAS(name, pae_##name);
FOREACH_PAGING_FUNCTION(DEFINE_PUBLIC_ALIAS_PAGING_PAE)
#undef DEFINE_PUBLIC_ALIAS_PAGING_PAE
#elif defined(CONFIG_BOOTUP_OPTIMIZE_FOR_P32)
#define DEFINE_PUBLIC_ALIAS_PAGING_P32(name) \
	DEFINE_PUBLIC_ALIAS(name, p32_##name);
FOREACH_PAGING_FUNCTION(DEFINE_PUBLIC_ALIAS_PAGING_P32)
#undef DEFINE_PUBLIC_ALIAS_PAGING_P32
#endif


#ifndef CONFIG_NO_PAGING_P32
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_paging_p32)(void) {
	if __untraced(HAVE_4MIB_PAGES) {
		__wrcr4(__rdcr4() | CR4_PSE);
		/* TODO: Merge whole 4MiB pages within the kernel core, thus saving on the
		 *       about on needed TLB entires of translate kernel-space memory addresses. */
	}
	/* TODO: Add support for `PSE-36' to map 4MiB pages to 40-bit physical addresses.
	 *       Implementing this shouldn't be too difficult, but would require a dedicated
	 *       function for mapping a 4MiB-aligned 40-bit physical address to a 4MiB-aligned
	 *       virtual address. */
}
#endif /* !CONFIG_NO_PAGING_P32 */

#ifndef CONFIG_NO_PAGING_PAE
INTDEF u64 pae_pageperm_matrix[16];

INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_paging_pae)(void) {
	if __untraced(HAVE_2MIB_PAGES) {
		/* TODO: Merge whole 2MiB pages within the kernel core, thus saving on the
		 *       about on needed TLB entires of translate kernel-space memory addresses. */
	}
	if __untraced(!HAVE_EXECUTE_DISABLE) {
		unsigned int i;
		/* Disable support for execute-disable. */
		for (i = 0; i < COMPILER_LENOF(pae_pageperm_matrix); ++i)
			pae_pageperm_matrix[i] &= ~PAE_PAGE_FNOEXEC;
	} else {
		u64 msr;
		/* Set the NXE msr bit to enable support for execute-disable */
		msr  = __rdmsr(IA32_EFER);
		msr |= IA32_EFER_NXE;
		__wrmsr(IA32_EFER, msr);
	}
}
#endif /* !CONFIG_NO_PAGING_PAE */


PRIVATE ATTR_FREERODATA byte_t const
x86_pagedir_syncall_cr3_text[] = {
	0x0f, 0x20, 0xd8, /* movl %cr3, %eax             */
	0x0f, 0x22, 0xd8, /* movl %eax, %cr3             */
	                  /* --- TLB reload happens here */
	0xc3              /* ret                         */
};

PRIVATE ATTR_FREERODATA byte_t const
x86_pagedir_syncall_cr4_text[] = {
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


STATIC_ASSERT_MSG(sizeof(x86_pagedir_syncall_cr3_text) == 7,
                  "Update this, as well as the `RELOAD_WITH_CR3_TEXTSIZE' in `paging32.S'");
STATIC_ASSERT_MSG(sizeof(x86_pagedir_syncall_cr4_text) == 16,
                  "Update this, as well as the `RELOAD_WITH_CR4_TEXTSIZE' in `paging32.S'");


#ifndef CONFIG_NO_PAGING_P32
INTERN ATTR_FREETEXT ATTR_CONST union p32_pdir_e1 *
NOTHROW(FCALL x86_get_cpu_iob_pointer_p32)(struct cpu *__restrict self) {
	union p32_pdir_e1 *e1_pointer;
	uintptr_t iobp;
	iobp       = (uintptr_t)&FORCPU(self, thiscpu_x86_iob[0]);
	e1_pointer = &P32_PDIR_E1_IDENTITY[P32_PDIR_VEC2INDEX(iobp)]
	                                  [P32_PDIR_VEC1INDEX(iobp)];
	return e1_pointer;
}
LOCAL ATTR_FREETEXT void
NOTHROW(KCALL ioperm_preemption_set_p32_unmap)(void) {
	/* Initialize the `_bootcpu.thiscpu_x86_iobnode_pagedir_identity' pointer. */
	FORCPU(&_bootcpu, thiscpu_x86_iobnode_pagedir_identity) = x86_get_cpu_iob_pointer_p32(&_bootcpu);
#ifndef CONFIG_NO_PAGING_PAE
	/* Re-write the assembly of `__x86_lazy_disable_ioperm_bitmap_pae', as
	 * found in `arch/i386/sched/sched32.S' to only clear 8 bytes of memory
	 * in order to unmap the IOB vector, rather than clearing 16 bytes (as
	 * is required by PAE paging, which is the default configuration) */
	{
		INTDEF byte_t __x86_lazy_disable_ioperm_bitmap_pae[];
		INTDEF byte_t __x86_lazy_disable_ioperm_bitmap_return[];
		s32 rel_offset;
		rel_offset = (s32)((__x86_lazy_disable_ioperm_bitmap_pae + 5) -
		                   __x86_lazy_disable_ioperm_bitmap_return);
		*(u8 *)(__x86_lazy_disable_ioperm_bitmap_pae + 0) = 0xe9;
		*(s32 *)(__x86_lazy_disable_ioperm_bitmap_pae + 1) = rel_offset;
	}
#endif /* !CONFIG_NO_PAGING_PAE */
}
#endif /* !CONFIG_NO_PAGING_P32 */

#ifndef CONFIG_NO_PAGING_PAE
INTERN ATTR_FREETEXT ATTR_CONST union pae_pdir_e1 *
NOTHROW(FCALL x86_get_cpu_iob_pointer_pae)(struct cpu *__restrict self) {
	union pae_pdir_e1 *e1_pointer;
	uintptr_t iobp;
	iobp       = (uintptr_t)&FORCPU(self, thiscpu_x86_iob[0]);
	e1_pointer = &PAE_PDIR_E1_IDENTITY[PAE_PDIR_VEC3INDEX(iobp)]
	                                  [PAE_PDIR_VEC2INDEX(iobp)]
	                                  [PAE_PDIR_VEC1INDEX(iobp)];
	return e1_pointer;
}
LOCAL ATTR_FREETEXT void
NOTHROW(KCALL ioperm_preemption_set_pae_unmap)(void) {
	/* Initialize the `_bootcpu.thiscpu_x86_iobnode_pagedir_identity' pointer. */
	FORCPU(&_bootcpu, thiscpu_x86_iobnode_pagedir_identity) = x86_get_cpu_iob_pointer_pae(&_bootcpu);
}
#endif /* !CONFIG_NO_PAGING_PAE */

/* Enable use of p32 paging */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_paging)(void) {
#ifndef CONFIG_NO_PAGING_P32
#ifdef HYBRID_PAGING_MODE
	if __untraced(X86_PAGEDIR_USES_P32())
#endif /* HYBRID_PAGING_MODE */
	{
#ifdef HYBRID_PAGING_MODE
#ifdef CONFIG_BOOTUP_OPTIMIZE_FOR_PAE
		/* Must redirect `pagedir_*' functions to use the `p32_pagedir_*' variants. */
#define REDIRECT_PAGING_FUNCTION_P32(name) \
		pagedir_install_jmp((void *)&name, (void const *)&p32_##name);
		FOREACH_PAGING_FUNCTION(REDIRECT_PAGING_FUNCTION_P32)
#undef REDIRECT_PAGING_FUNCTION_P32
#endif /* CONFIG_BOOTUP_OPTIMIZE_FOR_PAE */
#endif /* HYBRID_PAGING_MODE */
		kernel_initialize_paging_p32();
		ioperm_preemption_set_p32_unmap();
	}
#ifdef HYBRID_PAGING_MODE
	else
#endif /* HYBRID_PAGING_MODE */
#endif /* !CONFIG_NO_PAGING_P32 */
#ifndef CONFIG_NO_PAGING_PAE
	{
#ifdef CONFIG_BOOTUP_OPTIMIZE_FOR_P32
		/* Must redirect `pagedir_*' functions to use the `pae_pagedir_*' variants. */
#define REDIRECT_PAGING_FUNCTION_PAE(name) \
		pagedir_install_jmp((void *)&name, (void const *)&pae_##name);
		FOREACH_PAGING_FUNCTION(REDIRECT_PAGING_FUNCTION_PAE)
#undef REDIRECT_PAGING_FUNCTION_PAE
#endif /* CONFIG_BOOTUP_OPTIMIZE_FOR_P32 */
		kernel_initialize_paging_pae();
		ioperm_preemption_set_pae_unmap();
	}
#endif /* !CONFIG_NO_PAGING_PAE */

	/* Check if we must re-write our implementation of `pagedir_syncall()'.
	 * Currently, it looks like this:
	 * >> movl   $2, %eax
	 * >> invpcid (%eax), %eax // The first operand is ignored.
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

	if (!HAVE_INSTR_INVLPG) {
		if (HAVE_PAGE_GLOBAL_BIT) {
			/* Must re-write `x86_pagedir_syncone' and `x86_pagedir_sync' to use cr4 for flushing */
			memcpy((void *)&x86_pagedir_syncone, x86_pagedir_syncall_cr4_text, sizeof(x86_pagedir_syncall_cr4_text));
			memcpy((void *)&x86_pagedir_sync, x86_pagedir_syncall_cr4_text, sizeof(x86_pagedir_syncall_cr4_text));
		} else {
			/* Must re-write `x86_pagedir_syncone' and `x86_pagedir_sync'
			 * to use the cr3-trick for TLB invalidation */
			memcpy((void *)&x86_pagedir_syncone, x86_pagedir_syncall_cr3_text, sizeof(x86_pagedir_syncall_cr3_text));
			memcpy((void *)&x86_pagedir_sync, x86_pagedir_syncall_cr3_text, sizeof(x86_pagedir_syncall_cr3_text));
		}
	}


	/* TODO: Make use of `HAVE_PAGE_ATTRIBUTE_TABLE' to control
	 *       availability of `P32_PAGE_FPAT_4KIB' / `P32_PAGE_FPAT_4MIB' */

	/* TODO: Make use of `CPUID.80000008H:EAX[7:0]' to figure out the physical address
	 *       width supported by the hosting processor. */

}


DECL_END


#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_C_INL */
