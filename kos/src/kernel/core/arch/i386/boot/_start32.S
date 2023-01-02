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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_BOOT__START32_S
#define GUARD_KERNEL_CORE_ARCH_I386_BOOT__START32_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/arch/paging32.h>
#include <kernel/paging.h>
#include <kernel/x86/cpuid.h>

#include <hybrid/align.h>

#include <asm/cpu-cpuid.h>
#include <asm/cpu-flags.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/bits/cpu-state32.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/x86/segment.h>
#include <kos/kernel/x86/tss.h>

#ifndef CONFIG_NO_KERNEL_X86_PAGING_P32
#include <kernel/arch/paging32-p32.h>
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */

#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE
#include <kernel/arch/paging32-pae.h>
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */

/**/
#include "start.h"
#include "_objects.S"
/**/

#define P2V(x) ((x) + KERNEL_CORE_BASE)
#define V2P(x) ((x) - KERNEL_CORE_BASE)

/* The starting  VEC2-index  (in  `x86_pdir::p_e2')  and  amount
 * of continuous indices thereafter of the kernel-share segment.
 * That is the segment where the kernel itself resides at, which
 * is then mapped again in all other page directories. */
#define VEC2_SHARE_BEGIN     X86_PDIR_VEC2INDEX(KERNEL_CORE_BASE)
#define VEC2_SHARE_SIZE     (VEC2_IDENTITY_BEGIN - VEC2_SHARE_BEGIN)

/* Similar to the SHARE indices, but for the identity mapping instead. */
#define VEC2_IDENTITY_BEGIN  X86_PDIR_VEC2INDEX(X86_PDIR_E1_IDENTITY_BASE)
#define VEC2_IDENTITY_SIZE  (1024 - VEC2_IDENTITY_BEGIN)

EXTERN(boot_cpustate)
EXTERN(__kernel_boottask_stack)
EXTERN(bootcpu_x86_cpufeatures)
EXTERN(bootcpu_x86_cpuid)

#ifndef CONFIG_NO_KERNEL_X86_BOOT0
#include "_boot0.S"
#endif /* !CONFIG_NO_KERNEL_X86_BOOT0 */

.section .text.free
INTERN_FUNCTION(_start)
	/* Boot loader entry point. */

	movl   %edi, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_EDI)
	movl   %esi, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_ESI)
	movl   %ebp, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_EBP)
	movl   %esp, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_ESP)
	movl   %ebx, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_EBX)
	movl   %edx, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_EDX)
	movl   %ecx, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_ECX)
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GPREGS + OFFSET_GPREGS32_EAX)
	sgdtl  V2P(boot_cpustate + OFFSET_FCPUSTATE32_GDT)
	sidtl  V2P(boot_cpustate + OFFSET_FCPUSTATE32_IDT)
	movl   $(V2P(_start)), V2P(boot_cpustate + OFFSET_FCPUSTATE32_EIP)
	movw   %gs, V2P(boot_cpustate + OFFSET_FCPUSTATE32_GS)
	movw   %fs, V2P(boot_cpustate + OFFSET_FCPUSTATE32_FS)
	movw   %es, V2P(boot_cpustate + OFFSET_FCPUSTATE32_ES)
	movw   %ds, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DS)
	movw   %cs, V2P(boot_cpustate + OFFSET_FCPUSTATE32_CS)
	movw   %ss, V2P(boot_cpustate + OFFSET_FCPUSTATE32_SS)
	strw   V2P(boot_cpustate + OFFSET_FCPUSTATE32_TR)
	sldtw  V2P(boot_cpustate + OFFSET_FCPUSTATE32_LDT)
	movl   %cr0, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_COREGS + OFFSET_COREGS32_CR0)
	movl   %cr2, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_COREGS + OFFSET_COREGS32_CR2)
	movl   %cr3, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_COREGS + OFFSET_COREGS32_CR3)
	movl   %cr4, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_COREGS + OFFSET_COREGS32_CR4)
	movl   %dr0, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DRREGS + OFFSET_DRREGS32_DR0)
	movl   %dr1, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DRREGS + OFFSET_DRREGS32_DR1)
	movl   %dr2, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DRREGS + OFFSET_DRREGS32_DR2)
	movl   %dr3, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DRREGS + OFFSET_DRREGS32_DR3)
	movl   %dr6, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DRREGS + OFFSET_DRREGS32_DR6)
	movl   %dr7, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE32_DRREGS + OFFSET_DRREGS32_DR7)
	movl   $(V2P(__kernel_boottask_stack + KERNEL_STACKSIZE)), %esp

#if 1 /* Fixup required when loaded via bochs's `load32bitOSImage' function */
	/* Prematurely load our GDT, so we can manually set valid segments for %ds, %es and %ss,
	 * as  we only  want to  rely on  the boot loader  to have  set up  a valid  %ds and %cs */
	.pushsection .rodata.free
1:	.word  (SEGMENT_COUNT * 8 - 1)
	.long  V2P(__templatecpu_x86_gdt)
	.popsection
	lgdtl  %ds:V2P(1b)
	movw   $(SEGMENT_KERNEL_DATA), %ax
	movw   %ax, %ss
	movw   %ax, %ds
	movw   %ax, %es
#endif

	pushfl
	movl   0(%esp), %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE_EFLAGS)
	/* Make sure that %eflags is in a valid state */
	andl   $(~(EFLAGS_IF | /* Disable interrupts */                                      \
	           EFLAGS_TF |                                                               \
	           EFLAGS_DF | /* Clear the direction bit (required for REP instructions) */ \
	           EFLAGS_IOPLMASK |                                                         \
	           EFLAGS_NT |                                                               \
	           EFLAGS_RF |                                                               \
	           EFLAGS_AC                                                                 \
	           )), %eax
	movl   %eax, 0(%esp)
	popfl


#ifndef CONFIG_NO_SMP
	/* memcpy(&bootcpu, __kernel_percpu_start, (size_t)__kernel_percpu_size); */
	EXTERN(bootcpu)
	EXTERN(__kernel_percpu_start)
	EXTERN(__kernel_percpu_size)
	movl   $(V2P(bootcpu)), %edi
	movl   $(V2P(__kernel_percpu_start)), %esi
	movl   $(__kernel_percpu_size), %ecx
	rep    movsb

	/* memcpy(&bootcpu_x86_tss, __kernel_percpu_tss, SIZEOF_TSS); */
	EXTERN(bootcpu_x86_tss)
	EXTERN(__kernel_percpu_tss)
	movl   $(V2P(bootcpu_x86_tss)), %edi
	movl   $(V2P(__kernel_percpu_tss)), %esi
#if IS_ALIGNED(SIZEOF_TSS, 4)
	movl   $(SIZEOF_TSS / 4), %ecx
	rep    movsl
#elif IS_ALIGNED(SIZEOF_TSS, 2)
	movl   $(SIZEOF_TSS / 2), %ecx
	rep    movsw
#else
	movl   $(SIZEOF_TSS), %ecx
	rep    movsb
#endif
#endif /* !CONFIG_NO_SMP */

	/* memcpy(&bootidle, __kernel_pertask_start, (size_t)__kernel_pertask_size); */
	EXTERN(bootidle)
	EXTERN(__kernel_pertask_start)
	EXTERN(__kernel_pertask_size)
	movl   $(V2P(bootidle)), %edi
	movl   $(V2P(__kernel_pertask_start)), %esi
	movl   $(__kernel_pertask_size), %ecx
	rep    movsb

	/* memcpy(&boottask, __kernel_pertask_start, (size_t)__kernel_pertask_size); */
	EXTERN(boottask)
	movl   $(V2P(boottask)), %edi
	movl   $(V2P(__kernel_pertask_start)), %esi
	movl   $(__kernel_pertask_size), %ecx
	rep    movsb

	/* memcpy(&asyncwork, __kernel_pertask_start, (size_t)__kernel_pertask_size); */
	EXTERN(asyncwork)
	movl   $(V2P(asyncwork)), %edi
	movl   $(V2P(__kernel_pertask_start)), %esi
	movl   $(__kernel_pertask_size), %ecx
	rep    movsb

	/* memcpy((byte_t *)&mman_kernel + PAGEDIR_SIZE, __kernel_permman_start, (size_t)__kernel_permman_size); */
	EXTERN(mman_kernel)
	EXTERN(__kernel_permman_start)
	EXTERN(__kernel_permman_size)
	movl   $(V2P(mman_kernel) + PAGEDIR_SIZE), %edi
	movl   $(V2P(__kernel_permman_start)), %esi
	movl   $(__kernel_permman_size), %ecx
	rep    movsb

	/* Set the DIDINIT flag for the boot cpu's feature table. */
	EXTERN(bootcpu_x86_cpufeatures)
	orl    $(CPU_FEATURE_FDIDINIT), V2P(bootcpu_x86_cpufeatures)

	/* Check if CPUID is supported. */
	pushfl
	pushfl
	xorl   $(EFLAGS_ID), 0(%esp)
	popfl
	pushfl
	popl   %eax
	xorl   0(%esp), %eax
	popfl
	andl   $(EFLAGS_ID), %eax
	jz    .Lno_cpuid


	orl    $(CPU_FEATURE_FCPUID), V2P(bootcpu_x86_cpufeatures)

	movl   $(1), %eax
	cpuid
	movl   %eax, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1A
	movl   %ebx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1B
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1D
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1C

	/* if (Family == 6 && Model < 3 && Stepping < 3)
	 *     OFFSET_CPUID_1D &= ~CPUID_1D_SEP; */
	ttest  mask=CPUID_1D_SEP, loc=%edx
	jz     1f
	movl   %eax, %ecx
	andl   $(CPUID_1A_FAMILY_M), %ecx
	cmpl   $(6 << CPUID_1A_FAMILY_S), %ecx
	jne    1f  /* if (Family != 6) goto 1f; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_MODEL_M), %ecx
#if CPUID_1A_MODEL_S != 0
	shrl   $(CPUID_1A_MODEL_S), %ecx
#endif /* CPUID_1A_MODEL_S != 0 */
	cmpl   $(3), %ecx
	jae    1f  /* if (Model >= 3) goto 1f; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_STEPPING_M), %ecx
#if CPUID_1A_STEPPING_S != 0
	shrl   $(CPUID_1A_STEPPING_S), %ecx
#endif /* CPUID_1A_STEPPING_S != 0 */
	cmpl   $(3), %ecx
	/* if (Stepping >= 3) goto 1f; */
	jae    1f
	andl   $(~CPUID_1D_SEP), V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1D
1:

	/* Query additional CPUID features. */
	xorl   %eax, %eax
	cpuid
	movl   %eax, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_0A
	movl   %ebx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_0B
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_0D
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_0C
	cmpl   $(7), %eax
	jnae   1f
	movl   $(7), %eax
	xorl   %ecx, %ecx /* Sub-leaf:0 */
	cpuid
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_7D
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_7C
	movl   %ebx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_7B
1:	movl   $(0x80000000), %eax
	cpuid
	movl   %eax, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000000A
	cmpl   $(0x80000001), %eax
	jnae   2f
	movl   $(0x80000001), %eax
	cpuid
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000001C
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000001D

	/* Check if we can extract the brand string from cpuid */
	movl   V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000000A, %eax
	cmpl   $(0x80000007), %eax
	jnae   4f
	movl   $(0x80000007), %eax
	cpuid
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000007D
	jmp    5f
4:	cmpl   $(0x80000004), %eax
	jnae   3f
5:

	movl   $(0x80000004), %eax
	cpuid
	movl   %eax, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000004A
	movl   %ebx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000004B
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000004C
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000004D

	movl   $(0x80000003), %eax
	cpuid
	movl   %eax, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000003A
	movl   %ebx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000003B
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000003C
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000003D

	movl   $(0x80000002), %eax
	cpuid
	movl   %eax, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000002A
	movl   %ebx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000002B
	movl   %ecx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000002C
	movl   %edx, V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_80000002D
3:  /* ci_80000000a < 0x80000004 */
2:  /* ci_80000000a < 0x80000001 */
.Lno_cpuid:

	/* Check for page-global support
	 * If not supported, clear out the used GLOBAL bit */
	EXTERN(used_pxx_page_fglobal)
	ttest  mask=CPUID_1D_PGE, loc=(V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1D)
	jnz    1f
	movl   $(0), V2P(used_pxx_page_fglobal)
#if !defined(CONFIG_NO_KERNEL_X86_PAGING_PAE) && (PAE_PAGE_FGLOBAL > 0xffffffff)
	movl   $(0), V2P(used_pxx_page_fglobal) + 4
#endif
	jmp    2f
1:	/* Enable page-global support */
	movl   %cr4, %eax
	orl    $(CR4_PGE), %eax
	movl   %eax, %cr4
2:

#if !defined(CONFIG_NO_KERNEL_X86_PAGING_P32) && \
    !defined(CONFIG_NO_KERNEL_X86_PAGING_PAE)
#define HYBRID_PAGING_MODE 1
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */


	EXTERN(__x86_pagedir_kernel_share)
#ifdef HYBRID_PAGING_MODE
	/* Check which paging mode we should enable. */
	ttest  mask=CPUID_1D_PAE, loc=(V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1D)
#if 0
	jmp    .Linit_paging_p32
#else
	jz     .Linit_paging_p32
#endif
	/* Fallthrough to `.Linit_paging_pae' */
#endif /* HYBRID_PAGING_MODE */





	/* Initialize the kernel's paging structures for PAE-mode. */
#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE
.Linit_paging_pae:
#ifdef HYBRID_PAGING_MODE
	/* Check  if the host  supports the cmpxchg8b instruction  (our PAE paging implementation
	 * requires this instruction to function properly, and there is no way around this, since
	 * the control words used by PAE are 64-bit wide)
	 * However, judging by the fact  that any CPU that supports  PAE must necessarily have  some
	 * sort of wiring in place to be able  to atomically fetch 64-bit values from RAM, it  would
	 * seem  likely that it would also expose this  functionality in the firs tof providing this
	 * very instruction, but still though: it can't hurt to be save and disable PAE if CX8 isn't
	 * available. */
	ttest  mask=CPUID_1D_CX8, loc=(V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1D)
	jz     .Linit_paging_p32
	/* TODO: Check if using PAE would even give us any form of advantage:
	 *  - CPUID.80000008H:EAX[7:0]:
	 *    Can physical addresses even exceed the 32-bit limit of non-pae paging?
	 *  - Does the CPU have support for the NX bit? If not, we don't
	 *    even gain that ability from using PAE.
	 */
#else /* !HYBRID_PAGING_MODE */
	/* TODO: Assert that the hosting  CPU supports PAE and  CX8.
	 *       If it doesn't, print an an error message on-screen. */
#endif /* HYBRID_PAGING_MODE */

	/*
	 * >> VECTOR_FLAGS = PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	 * >> PAGE_FLAGS   = PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT |
	 * >>                PAE_PAGE_FDIRTY | PAE_PAGE_FGLOBAL | PAE_PAGE_FPREPARED;
	 * >> pagedir_kernel.pd_pae.p_e3[0].p_word = PHYS_ADDR(&ks_share_e2[3][0]) | PAE_PAGE_FPRESENT; // Low-memory identity map (removed later)
	 * >> pagedir_kernel.pd_pae.p_e3[1].p_word = PHYS_ADDR(&ks_share_e2[1][0]) | PAE_PAGE_FPRESENT;
	 * >> pagedir_kernel.pd_pae.p_e3[2].p_word = PHYS_ADDR(&ks_share_e2[2][0]) | PAE_PAGE_FPRESENT;
	 * >> pagedir_kernel.pd_pae.p_e3[3].p_word = PHYS_ADDR(&ks_share_e2[3][0]) | PAE_PAGE_FPRESENT;
	 * >> // Note that this init is already done by .bss (it is only
	 * >> // explicitly stated here since this zero-init is required)
	 * >> bzero(ks_share_e2, 3 * 512 * 8);
	 * >> for (i = 0; i < 508; ++i) {
	 * >>     ks_share_e2[3][i] = PHYS_ADDR(&ks_share_e1[i][0]) | VECTOR_FLAGS;
	 * >> }
	 * >> ks_share_e2[3][508] = PHYS_ADDR(&ks_share_e2[0][0]) | VECTOR_FLAGS; // Self-map
	 * >> ks_share_e2[3][509] = PHYS_ADDR(&ks_share_e2[1][0]) | VECTOR_FLAGS; // Self-map
	 * >> ks_share_e2[3][510] = PHYS_ADDR(&ks_share_e2[2][0]) | VECTOR_FLAGS; // Self-map
	 * >> ks_share_e2[3][511] = PHYS_ADDR(&ks_share_e2[3][0]) | VECTOR_FLAGS; // Self-map
	 * >> for (i = 0; i < 508 * 512; ++i) {
	 * >>     ((union pae_pdir_e1 *)&ks_share_e1[0][0])[i].p_word = (i * 4096) | PAGE_FLAGS;
	 * >> }
	 */
#define VECTOR_FLAGS    (PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT)
#define PAGE_FLAGS      (PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT | \
	                     PAE_PAGE_FDIRTY | /*PAE_PAGE_FGLOBAL |*/ PAE_PAGE_FPREPARED)
#define PAE_KS_SHARE_E2_BASE           V2P(__x86_pagedir_kernel_share)
#define PAE_KS_SHARE_E1_BASE          (V2P(__x86_pagedir_kernel_share) + 0x4000)                /* 0x4000 == 4 * 512 * 8 */
#define PAE_KS_SHARE_E2(vec3, vec2)   (PAE_KS_SHARE_E2_BASE + ((vec3) * 0x1000) + ((vec2) * 8)) /* 0x1000 == 8 * 512 */
#define PAE_KS_SHARE_E1(vec2, vec1)   (PAE_KS_SHARE_E1_BASE + ((vec2) * 0x1000) + ((vec1) * 8)) /* 0x1000 == 8 * 512 */
#define PAE_PAGEDIR_KERNEL_P_E3(vec3) (pagedir_kernel_phys + (vec3) * 8)
	movl   $(PAE_KS_SHARE_E2(3, 0) + PAE_PAGE_FPRESENT), PAE_PAGEDIR_KERNEL_P_E3(0)
	movl   $(PAE_KS_SHARE_E2(1, 0) + PAE_PAGE_FPRESENT), PAE_PAGEDIR_KERNEL_P_E3(1)
	movl   $(PAE_KS_SHARE_E2(2, 0) + PAE_PAGE_FPRESENT), PAE_PAGEDIR_KERNEL_P_E3(2)
	movl   $(PAE_KS_SHARE_E2(3, 0) + PAE_PAGE_FPRESENT), PAE_PAGEDIR_KERNEL_P_E3(3)
	/* >> for (i = 0; i < 508; ++i) {
	 * >>     ks_share_e2[3][i] = PHYS_ADDR(&ks_share_e1[i][0]) | VECTOR_FLAGS;
	 * >> } */
	movl   $(508), %ecx
	movl   $(PAE_KS_SHARE_E1(0, 0) + VECTOR_FLAGS), %eax
	movl   $(PAE_KS_SHARE_E2(3, 0)), %edi
1:	stosl
	addl   $(4),      %edi /* Keep the upper 32 bits as 0 (the 0 stemming from .bss init) */
	addl   $(0x1000), %eax /* 0x1000 == PAE_KS_SHARE_E1(1, 0) - PAE_KS_SHARE_E1(0, 0) */
	loop   1b
	/* >> ks_share_e2[3][508] = PHYS_ADDR(&ks_share_e2[0][0]) | VECTOR_FLAGS; // Self-map
	 * >> ks_share_e2[3][509] = PHYS_ADDR(&ks_share_e2[1][0]) | VECTOR_FLAGS; // Self-map
	 * >> ks_share_e2[3][510] = PHYS_ADDR(&ks_share_e2[2][0]) | VECTOR_FLAGS; // Self-map
	 * >> ks_share_e2[3][511] = PHYS_ADDR(&ks_share_e2[3][0]) | VECTOR_FLAGS; // Self-map */
	movl   $(PAE_KS_SHARE_E2(0, 0) + VECTOR_FLAGS), PAE_KS_SHARE_E2(3, 508)
	movl   $(PAE_KS_SHARE_E2(1, 0) + VECTOR_FLAGS), PAE_KS_SHARE_E2(3, 509)
	movl   $(PAE_KS_SHARE_E2(2, 0) + VECTOR_FLAGS), PAE_KS_SHARE_E2(3, 510)
	movl   $(PAE_KS_SHARE_E2(3, 0) + VECTOR_FLAGS), PAE_KS_SHARE_E2(3, 511)
	/* >> for (i = 0; i < 508 * 512; ++i) {
	 * >>     ((union pae_pdir_e1 *)&ks_share_e1[0][0])[i].p_word = (i * 4096) | PAGE_FLAGS;
	 * >> } */
	movl   $(508 * 512), %ecx
	movl   $(PAE_KS_SHARE_E1(0, 0)), %edi
	movl   $(0 + PAGE_FLAGS), %eax
	orl    V2P(used_pxx_page_fglobal), %eax /* Include the `PAE_PAGE_FGLOBAL' flag (if supported) */
1:	stosl
	addl   $(4),      %edi /* Keep the upper 32 bits as 0 (the 0 stemming from .bss init) */
	addl   $(4096),   %eax
	loop   1b

	/* Enable PAE support in CR4 */
	movl   %cr4, %eax
	orl    $(CR4_PAE), %eax
	/* With PAE we're also able to support the NX bit, so try to enable
	 * its effects  while in  kernel-space (if  supported by  the  CPU) */
	ttest  mask=CPUID_7B_SMEP, loc=(V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_7B)
	jz     1f
	orl    $(CR4_SMEP), %eax
1:	movl   %eax, %cr4
#ifdef HYBRID_PAGING_MODE
	jmp    .Ldone_init_paging
#endif /* HYBRID_PAGING_MODE */
#undef PAGE_FLAGS
#undef VECTOR_FLAGS
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */






	/* Initialize the kernel's paging structures for P32-mode. */
#ifndef CONFIG_NO_KERNEL_X86_PAGING_P32
.Linit_paging_p32:
#ifdef HYBRID_PAGING_MODE
	/* Manually clear the PAE-support  flag (it shouldn't actually  be set, but someone  may
	 * wish to hack the kernel to quickly disable PAE by changing the conditional jump above
	 * into an unconditional one, in  which case we'd get  here with PAE-enabled still  set)
	 * Make their live a bit easier by allowing for such a simple hack and act like the  cpu
	 * told us that PAE wasn't supported.
	 * Also: The check for `CPUID_1D_CX8' assumes that we clear the PAE bit for it. */
	andl   $(~CPUID_1D_PAE), V2P(bootcpu_x86_cpuid) + OFFSET_CPUID_1D
#endif /* HYBRID_PAGING_MODE */
	/*
	 * >> VECTOR_FLAGS = P32_PAGE_FACCESSED | P32_PAGE_FWRITE | P32_PAGE_FPRESENT;
	 * >> PAGE_FLAGS   = P32_PAGE_FACCESSED | P32_PAGE_FWRITE | P32_PAGE_FPRESENT |
	 * >>                P32_PAGE_FDIRTY | P32_PAGE_FGLOBAL | P32_PAGE_FPREPARED;
	 * >> for (i = 768; i < 1023; ++i) {
	 * >>     pagedir_kernel.pd_p32.p_e2[i].p_word = PHYS_ADDR(&ks_share[i - 768][0]) | VECTOR_FLAGS;
	 * >> }
	 * >> pagedir_kernel.pd_p32.p_e2[1023].p_word = PHYS_ADDR(&pagedir_kernel) | VECTOR_FLAGS; // Self-map
	 * >> for (i = 0; i < 255 * 1024; ++i) {
	 * >>     ((union p32_pdir_e1 *)&ks_share[0][0])[i].p_word = (i * 4096) | PAGE_FLAGS;
	 * >> }
	 * >> i = __x86_p32_identity_mapped_text_4mib_index;
	 * >> pagedir_kernel.pd_p32.p_e2[i].p_word = PHYS_ADDR(&ks_share[i][0]) | VECTOR_FLAGS;
	 */
#define VECTOR_FLAGS (P32_PAGE_FACCESSED | P32_PAGE_FWRITE | P32_PAGE_FPRESENT)
#define PAGE_FLAGS   (P32_PAGE_FACCESSED | P32_PAGE_FWRITE | P32_PAGE_FPRESENT | \
	                  P32_PAGE_FDIRTY | /*P32_PAGE_FGLOBAL |*/ P32_PAGE_FPREPARED)
#define P32_KS_SHARE_BASE              V2P(__x86_pagedir_kernel_share)
#define P32_KS_SHARE(vec2, vec1)      (P32_KS_SHARE_BASE + ((vec2) * 0x1000) + ((vec1) * 4)) /* 0x1000 == 4 * 1024 */
#define P32_PAGEDIR_KERNEL_P_E2(vec2) (pagedir_kernel_phys + (vec2) * 4)
	/* >> for (i = 768; i < 1023; ++i) {
	 * >>     pagedir_kernel.pd_p32.p_e2[i].p_word = PHYS_ADDR(&ks_share[i - 768][0]) | VECTOR_FLAGS;
	 * >> } */
	movl   $(1023 - 768), %ecx
	movl   $(P32_KS_SHARE(0, 0) + VECTOR_FLAGS), %eax
	movl   $(P32_PAGEDIR_KERNEL_P_E2(768)), %edi
1:	stosl
	addl   $(0x1000), %eax /* 0x1000 == P32_KS_SHARE(1, 0) - P32_KS_SHARE(0, 0) */
	loop   1b
	/* >> pagedir_kernel.pd_p32.p_e2[1023].p_word = PHYS_ADDR(&pagedir_kernel) | VECTOR_FLAGS; // Self-map */
	movl   $(pagedir_kernel_phys + VECTOR_FLAGS), P32_PAGEDIR_KERNEL_P_E2(1023)
	/* >> for (i = 0; i < 255 * 1024; ++i) {
	 * >>     ((union p32_pdir_e1 *)&ks_share[0][0])[i].p_word = (i * 4096) | PAGE_FLAGS;
	 * >> } */
	movl   $(255 * 1024), %ecx
	movl   $(P32_KS_SHARE(0, 0)), %edi
	movl   $(0 + PAGE_FLAGS), %eax
	orl    V2P(used_pxx_page_fglobal), %eax /* Include the `PAE_PAGE_FGLOBAL' flag (if supported) */
1:	stosl
	addl   $(4096), %eax
	loop   1b
	/* >> i = __x86_p32_identity_mapped_text_4mib_index;
	 * >> pagedir_kernel.pd_p32.p_e2[i].p_word = PHYS_ADDR(&ks_share[i][0]) | VECTOR_FLAGS; */
	EXTERN(__x86_p32_identity_mapped_text_4mib_e2_word)  /* == &P32_PAGEDIR_KERNEL_P_E2(__x86_p32_identity_mapped_text_4mib_index) */
	EXTERN(__x86_p32_identity_mapped_text_4mib_ks_share) /* == P32_KS_SHARE(__x86_p32_identity_mapped_text_4mib_index, 0) */
	movl   $(__x86_p32_identity_mapped_text_4mib_ks_share + VECTOR_FLAGS), V2P(__x86_p32_identity_mapped_text_4mib_e2_word)
#undef PAGE_FLAGS
#undef VECTOR_FLAGS
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */






.Ldone_init_paging:
	/* And with that, the kernel page directory is fully initialized.
	 * Now to activate paging. */
	movl   $(pagedir_kernel_phys), %esi
	movl   %esi, %cr3
	movl   %cr0, %eax
	orl    $(CR0_PG | CR0_WP), %eax

	/* Jump into virtual memory.
	 * NOTE: We  manually  encode  these  instructions,  since  we  are  _very_  dependent  on
	 *       their layout.  -  Since  this is  the  point  where we  enable  paging,  followed
	 *       by  jumping  into  virtual  memory,   instruction  pointers  within  this   block
	 *       have to remain  identity-mapped in physical  memory during paging  initialization
	 *       above. - To  accomodate for  this, take note  that the  mov to cr0  and jmp  take
	 *       up a total of 8 bytes (which is very helpful since we need to use some power-of-2
	 *       number that is at least as large, meaning  we can just use that same 8 for  this)
	 *       We then align  this piece  of code  such that it  stored on  an 8-byte  boundary,
	 *       thus also ensuring  that there  isn't a  page-split anywhere  inside, meaning  we
	 *       can get the management above  to only have to ensure  a single page of  identity-
	 *       mapped memory needing to exist.
	 * With all of this mind, we are guarantied that the page which these 8 bytes of  text
	 * reside inside of is identity-mapped when we enable paging, which is all we need for
	 * this setup to work flawlessly!
	 * To accomplish this identity mapping, PAE/P32 do the following
	 * PAE: (Always identity-maps the first 1GiB since this is the simplest)
	 * >> pagedir_kernel.pd_pae.p_e3[0].p_word = PHYS_ADDR(&ks_share_e2[3][0]) | PAE_PAGE_FPRESENT;
	 * P32: (Only identity-maps the 4MiB page that `__x86_paging_init_identity_mapped_text' is apart of)
	 * >> index = __x86_p32_identity_mapped_text_4mib_index;
	 * >> pagedir_kernel.pd_p32.p_e2[index].p_word = PHYS_ADDR(&ks_share[index][0]) | VECTOR_FLAGS;
	 */

	.align 8, 0x90  /* Align by padding with nop (nop == 0x90) */
INTERN_BEGIN(__x86_paging_init_identity_mapped_text)
	.byte  0x0f, 0x22, 0xc0 /* movl   %eax, %cr0 */
	.byte  0xe9             /* jmp    1f + KERNEL_CORE_BASE; 1: */
	.long  KERNEL_CORE_BASE
END(__x86_paging_init_identity_mapped_text)


#ifdef HYBRID_PAGING_MODE
	/* Check which paging mode we should enable. */
	ttest  mask=CPUID_1D_PAE, loc=(bootcpu_x86_cpuid + OFFSET_CPUID_1D)
	jz     .Lcleanup_paging_p32
	/* Fallthrough to `.Lcleanup_paging_pae' */
#endif /* HYBRID_PAGING_MODE */

#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE
.Lcleanup_paging_pae:
	movl   $(PAE_KS_SHARE_E2(0, 0) + PAE_PAGE_FPRESENT), PAE_PAGEDIR_KERNEL_P_E3(0)
#ifdef HYBRID_PAGING_MODE
	jmp    .Ldone_cleanup_paging
#endif /* HYBRID_PAGING_MODE */
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */

#ifndef CONFIG_NO_KERNEL_X86_PAGING_P32
.Lcleanup_paging_p32:
	movl   $(0), __x86_p32_identity_mapped_text_4mib_e2_word
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */
.Ldone_cleanup_paging:

	/* Reload the page directory to flush any stale caches for removed physical memory. */
	movl   %esi, %cr3

	/* Setup a stack. */
	movl   $(__kernel_boottask_stack + KERNEL_STACKSIZE), %esp

	/* Load the initial (boot) GDT. (now that it's been copied) */
	.pushsection .rodata.free
		.align 2
1:		.word  (SEGMENT_COUNT * 8) - 1
		EXTERN(bootcpu_x86_gdt)
		.long  bootcpu_x86_gdt
	.popsection
	lgdtl  1b

	/* With the new GDT now loaded, load the new segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	movw   $(SEGMENT_USER_GSBASE_RPL), %ax
	movw   %ax, %gs
	movw   $(SEGMENT_KERNEL_DATA), %ax
	movw   %ax, %ss
	ljmp   $(SEGMENT_KERNEL_CODE), $(1f)
1:	movw   $(SEGMENT_CPU_TSS), %ax
	ltrw   %ax

	movw   $(SEGMENT_CPU_LDT), %ax
	lldtw  %ax

	/* Initialize the interrupt handling subsystem. */
	EXTERN(x86_idt_ptr)
	lidtl  x86_idt_ptr

	/* Setup the state of /bin/init at our stack base, thus following the
	 * general expectation that the user-space return state can be  found
	 * at exactly that location. */
#define SIZEOF_ICPUSTATE_USER (OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_USER)
	subl   $(SIZEOF_ICPUSTATE_USER), %esp
	movl   %esp, %edi
	xorl   %eax, %eax
	movl   $(SIZEOF_ICPUSTATE_USER / 4), %ecx
	rep    stosl /* Clear out all registers (these will be set by `__i386_kernel_main') */

	/* Fill in user-space segments registers (these will be used for /bin/init) */
	movb   $(SEGMENT_USER_DATA_RPL),   %al
	movb   %al,                        OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_SS(%esp)
	movb   $(EFLAGS_IF >> 8),          OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_EFLAGS + 1(%esp)
	movb   $(SEGMENT_USER_CODE_RPL),   OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS(%esp)
	movb   %al,                        OFFSET_ICPUSTATE_DS(%esp)
	movb   %al,                        OFFSET_ICPUSTATE_ES(%esp)
	movb   $(SEGMENT_USER_FSBASE_RPL), OFFSET_ICPUSTATE_FS(%esp)

	/* Initialize the kernel. */
	pushl  %esp /* struct icpustate *state */
	call   __i386_kernel_main
	movl   %eax, %esp
	/* TODO: call x86_kernel_unload_free_and_jump_to_userspace */

	/* Load the initial user-space CPU state. */
	popal
	popl   %fs
	popl   %es
	popl   %ds
	iret
END(_start)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_BOOT__START32_S */
