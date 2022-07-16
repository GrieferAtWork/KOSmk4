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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_C_INL
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_C_INL 1
#define __OMIT_PAGING_CONSTANT_P_WRAPPERS
#define __WANT_MMAN_EXCLUDE_PAGEDIR
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/_archinit.h>
#include <kernel/paging.h>
#include <sched/cpu.h>
#include <sched/userkern.h>
#include <sched/x86/tss.h>

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
	callback(pagedir_prepareone);             \
	callback(pagedir_prepare);                \
	callback(pagedir_unprepareone);           \
	callback(pagedir_unprepare);              \
	callback(pagedir_maphintone);             \
	callback(pagedir_maphint);                \
	callback(pagedir_gethint);                \
	callback(pagedir_mapone);                 \
	callback(pagedir_map);                    \
	callback(pagedir_push_mapone);            \
	callback(pagedir_pop_mapone);             \
	callback(pagedir_unmapone);               \
	callback(pagedir_unmap);                  \
	callback(pagedir_denywriteone);           \
	callback(pagedir_denywrite);              \
	callback(pagedir_unmap_userspace);        \
	callback(pagedir_unmap_userspace_nosync); \
	callback(pagedir_translate);              \
	callback(pagedir_ismapped);               \
	callback(pagedir_iswritable);             \
	callback(pagedir_isuseraccessible);       \
	callback(pagedir_isuserwritable);         \
	callback(pagedir_haschanged);             \
	callback(pagedir_unsetchanged);           \
	__PAGEDIR_MAYBE_DBG_LSPD(callback)


DECL_BEGIN

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#define __PAGEDIR_MAYBE_DBG_LSPD(callback) callback(dbg_lspd);
INTDEF ATTR_DBGTEXT void FCALL dbg_lspd(pagedir_phys_t pdir);
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
#define __PAGEDIR_MAYBE_DBG_LSPD(callback) /* nothing */
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */


/* Define the kernel mman */
INTERN ATTR_SECTION(".data.permman.head")
struct mman mman_kernel_head = { _MMAN_KERNEL_INIT };

/* Allocate BSS memory for the initial shared+identity mapping
 * that  will later be shared with, and re-appear in all other
 * page directories (except for the identity page)
 * NOTE: This buffer is quite large (1Mb), but we'd need
 *       to allocate it sooner or later, no matter what. */
INTERN ATTR_SECTION(".bss.x86.pagedir_kernel_share")
kernel_share_t __x86_pagedir_kernel_share = {};

DECL_END


#ifdef CONFIG_NO_KERNEL_X86_PAGING_PAE
/* P32 only */

#ifndef __INTELLISENSE__
#include "paging32-p32.c.inl"
#endif /* !__INTELLISENSE__ */

#define DEFINE_PUBLIC_ALIAS_PAGING_P32(name) \
	DEFINE_PUBLIC_ALIAS(name, p32_##name);
FOREACH_PAGING_FUNCTION(DEFINE_PUBLIC_ALIAS_PAGING_P32)
#undef DEFINE_PUBLIC_ALIAS_PAGING_P32

#elif defined(CONFIG_NO_KERNEL_X86_PAGING_P32)
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
LOCAL NOBLOCK ATTR_FREETEXT void
NOTHROW(FCALL pagedir_install_jmp)(void *redirection_addr,
                                   void const *redirection_target) {
	byte_t *dst = (byte_t *)redirection_addr;
	*(u8 *)(dst + 0)  = 0xe9;
	*(s32 *)(dst + 1) = ((s32)(uintptr_t)redirection_target -
	                     (s32)(uintptr_t)(dst + 5));
}
#endif /* HYBRID_PAGING_MODE */


/*[[[config CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32 = false]]]*/
#ifdef CONFIG_NO_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32
#undef CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32
#elif !defined(CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32)
#define CONFIG_NO_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32
#elif (-CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32 - 1) == -1
#undef CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32
#define CONFIG_NO_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32
#endif /* ... */
/*[[[end]]]*/
/*[[[config CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE = true]]]*/
#ifdef CONFIG_NO_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE
#undef CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE
#elif !defined(CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE)
#define CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE
#elif (-CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE - 1) == -1
#undef CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE
#define CONFIG_NO_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE
#endif /* ... */
/*[[[end]]]*/

#if defined(CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE) && defined(CONFIG_NO_KERNEL_X86_PAGING_PAE)
#undef CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE
#endif /* CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE && CONFIG_NO_KERNEL_X86_PAGING_PAE */
#if defined(CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32) && defined(CONFIG_NO_KERNEL_X86_PAGING_P32)
#undef CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32
#endif /* CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32 && CONFIG_NO_KERNEL_X86_PAGING_P32 */
#if defined(CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32) && defined(CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE)
#error "You can't optimize for both P32 and PAE paging (pick one!)"
#endif /* CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32 && CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE */

#ifdef CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE
#define DEFINE_PUBLIC_ALIAS_PAGING_PAE(name) \
	DEFINE_PUBLIC_ALIAS(name, pae_##name);
FOREACH_PAGING_FUNCTION(DEFINE_PUBLIC_ALIAS_PAGING_PAE)
#undef DEFINE_PUBLIC_ALIAS_PAGING_PAE
#elif defined(CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32)
#define DEFINE_PUBLIC_ALIAS_PAGING_P32(name) \
	DEFINE_PUBLIC_ALIAS(name, p32_##name);
FOREACH_PAGING_FUNCTION(DEFINE_PUBLIC_ALIAS_PAGING_P32)
#undef DEFINE_PUBLIC_ALIAS_PAGING_P32
#endif /* ... */


#ifndef CONFIG_NO_KERNEL_X86_PAGING_P32
INTDEF u32 p32_pageperm_matrix_[0x40] ASMNAME("p32_pageprot_table");

INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_paging_p32)(void) {
	if __untraced(HAVE_4MIB_PAGES) {
		__wrcr4(__rdcr4() | CR4_PSE);
		/* TODO: Merge  whole  4MiB pages  within  the kernel  core,  thus saving  on the
		 *       amount of needed TLB entries to translate kernel-space memory addresses. */
	}
	/* TODO: Add support for  `PSE-36' to  map 4MiB  pages to  40-bit physical  addresses.
	 *       Implementing this shouldn't be too  difficult, but would require a  dedicated
	 *       function for mapping a 4MiB-aligned 40-bit physical address to a 4MiB-aligned
	 *       virtual address. */
	if (!HAVE_PAGE_ATTRIBUTE_TABLE) {
		/* Disable PAT bits. */
		unsigned int i;
		for (i = 0; i < COMPILER_LENOF(p32_pageperm_matrix_); ++i)
			p32_pageperm_matrix_[i] &= ~(P32_PAGE_FPWT | P32_PAGE_FPCD | P32_PAGE_FPAT_4KIB);
	}
}
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */

#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE
INTDEF u64 pae_pageprot_table_[0x40] ASMNAME("pae_pageprot_table");

INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_paging_pae)(void) {
	if __untraced(HAVE_2MIB_PAGES) {
		/* TODO: Merge  whole  2MiB pages  within  the kernel  core,  thus saving  on the
		 *       amount of needed TLB entries to translate kernel-space memory addresses. */
	}
	if __untraced(!HAVE_EXECUTE_DISABLE) {
		unsigned int i;
		/* Disable support for execute-disable. */
		for (i = 0; i < COMPILER_LENOF(pae_pageprot_table_); ++i)
			pae_pageprot_table_[i] &= ~PAE_PAGE_FNOEXEC;
	} else {
		u64 msr;
		/* Set the NXE msr bit to enable support for execute-disable */
		msr  = __rdmsr(IA32_EFER);
		msr |= IA32_EFER_NXE;
		__wrmsr(IA32_EFER, msr);
	}
	if (!HAVE_PAGE_ATTRIBUTE_TABLE) {
		/* Disable PAT bits. */
		unsigned int i;
		for (i = 0; i < COMPILER_LENOF(pae_pageprot_table_); ++i)
			pae_pageprot_table_[i] &= ~(PAE_PAGE_FPWT | PAE_PAGE_FPCD | PAE_PAGE_FPAT_4KIB);
	}
}
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */


INTDEF byte_t const x86_pagedir_syncall_cr3[];
INTDEF byte_t x86_pagedir_syncall_cr3_size[];
INTDEF byte_t const x86_pagedir_syncall_cr4[];
INTDEF byte_t x86_pagedir_syncall_cr4_size[];


#ifndef CONFIG_NO_KERNEL_X86_PAGING_P32
INTERN ATTR_FREETEXT ATTR_CONST WUNUSED NONNULL((1)) union p32_pdir_e1 *
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
	/* Initialize the `bootcpu.thiscpu_x86_iobnode_pagedir_identity' pointer. */
	FORCPU(&bootcpu, thiscpu_x86_iobnode_pagedir_identity) = x86_get_cpu_iob_pointer_p32(&bootcpu);
#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE
	/* Re-write the assembly of `__x86_lazy_disable_ioperm_bitmap_pae',  as
	 * found in `arch/i386/sched/sched32.S' to only clear 8 bytes of memory
	 * in order to unmap the IOB vector, rather than clearing 16 bytes  (as
	 * is required by PAE paging, which is the default configuration) */
	{
		INTDEF byte_t __x86_lazy_disable_ioperm_bitmap_pae[];
		INTDEF byte_t __x86_lazy_disable_ioperm_bitmap_return[];
		s32 rel_offset;
		rel_offset = (s32)((__x86_lazy_disable_ioperm_bitmap_pae + 5) -
		                   __x86_lazy_disable_ioperm_bitmap_return);
		*(u8 *)(__x86_lazy_disable_ioperm_bitmap_pae + 0)  = 0xe9;
		*(s32 *)(__x86_lazy_disable_ioperm_bitmap_pae + 1) = rel_offset;
	}
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */
}
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */

#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE
INTERN ATTR_FREETEXT ATTR_CONST WUNUSED NONNULL((1)) union pae_pdir_e1 *
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
	/* Initialize the `bootcpu.thiscpu_x86_iobnode_pagedir_identity' pointer. */
	FORCPU(&bootcpu, thiscpu_x86_iobnode_pagedir_identity) = x86_get_cpu_iob_pointer_pae(&bootcpu);
}
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */

/* Enable use of p32 paging */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_paging)(void) {
#ifndef CONFIG_NO_KERNEL_X86_PAGING_P32
#ifdef HYBRID_PAGING_MODE
	if __untraced(X86_PAGEDIR_USES_P32())
#endif /* HYBRID_PAGING_MODE */
	{
#ifdef HYBRID_PAGING_MODE
#ifdef CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE
		/* Must redirect `pagedir_*' functions to use the `p32_pagedir_*' variants. */
#define REDIRECT_PAGING_FUNCTION_P32(name) \
		pagedir_install_jmp((void *)&name, (void const *)&p32_##name);
		FOREACH_PAGING_FUNCTION(REDIRECT_PAGING_FUNCTION_P32)
#undef REDIRECT_PAGING_FUNCTION_P32
#endif /* CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_PAE */
#endif /* HYBRID_PAGING_MODE */
		kernel_initialize_paging_p32();
		ioperm_preemption_set_p32_unmap();
	}
#ifdef HYBRID_PAGING_MODE
	else
#endif /* HYBRID_PAGING_MODE */
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */
#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE
	{
#ifdef CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32
		/* Must redirect `pagedir_*' functions to use the `pae_pagedir_*' variants. */
#define REDIRECT_PAGING_FUNCTION_PAE(name) \
		pagedir_install_jmp((void *)&name, (void const *)&pae_##name);
		FOREACH_PAGING_FUNCTION(REDIRECT_PAGING_FUNCTION_PAE)
#undef REDIRECT_PAGING_FUNCTION_PAE
#endif /* CONFIG_HAVE_KERNEL_X86_BOOTUP_OPTIMIZE_FOR_P32 */
		kernel_initialize_paging_pae();
		ioperm_preemption_set_pae_unmap();
	}
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */

	/* Check if we must re-write our implementation of `pagedir_syncall()'.
	 * Currently, it looks like this:
	 * >> movl   $2, %eax
	 * >> invpcid (%eax), %eax // The first operand is ignored.
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
		 *    `MOV to CR4. The behavior of the instruction depends on the bits being modified:'
		 *       `The instruction invalidates all TLB entries (including global entries) and all entries
		 *       in  all paging-structure caches (for all PCIDs) if ... it changes the value of CR4.PGE' */
		/* In other words: Toggling the PGE bit twice will get rid of all global TLBs */
		memcpy((void *)&pagedir_syncall, x86_pagedir_syncall_cr4, (size_t)x86_pagedir_syncall_cr4_size);
	}

	if (!HAVE_INSTR_INVLPG) {
		if (HAVE_PAGE_GLOBAL_BIT) {
			/* Must re-write `pagedir_syncone' and `arch_pagedir_sync' to use cr4 for flushing */
			memcpy((void *)&pagedir_syncone, x86_pagedir_syncall_cr4, (size_t)x86_pagedir_syncall_cr4_size);
			memcpy((void *)&arch_pagedir_sync, x86_pagedir_syncall_cr4, (size_t)x86_pagedir_syncall_cr4_size);
		} else {
			/* Must re-write `pagedir_syncone' and `arch_pagedir_sync'
			 * to use the cr3-trick for TLB invalidation */
			memcpy((void *)&pagedir_syncone, x86_pagedir_syncall_cr3, (size_t)x86_pagedir_syncall_cr3_size);
			memcpy((void *)&arch_pagedir_sync, x86_pagedir_syncall_cr3, (size_t)x86_pagedir_syncall_cr3_size);
		}
	}

	/* TODO: Make  use of `CPUID.80000008H:EAX[7:0]'  to figure out the
	 *       physical address width supported by the hosting processor. */
}



#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
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
	pdir = dbg_getpagedir();
	if (argc == 2) {
		if (strcmp(argv[1], lspd_str_kernel) == 0) {
			pdir = pagedir_kernel_phys;
		} else if (strcmp(argv[1], lspd_str_user) != 0) {
			return DBG_STATUS_INVALID_ARGUMENTS;
		}
	} else {
		if (argc != 1)
			return DBG_STATUS_INVALID_ARGUMENTS;
	}
	dbg_lspd(pdir);
	return 0;
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


DECL_END


#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_C_INL */
