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

#include <kernel/compiler.h>

#include <kernel/cpuid.h>
#include <kernel/paging.h>

#include <asm/cpu-cpuid.h>
#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/segment.h>
#include <kos/kernel/gdt.h>

#define P2V(x) ((x) + KERNEL_BASE)
#define V2P(x) ((x) - KERNEL_BASE)

/* The starting VEC2-index (in `x86_pdir::p_e2') and amount
 * of continuous indices thereafter of the kernel-share segment.
 * That is the segment where the kernel itself resides at, which
 * is then mapped again in all other page directories. */
#define VEC2_SHARE_BEGIN     X86_PDIR_VEC2INDEX(KERNEL_BASE)
#define VEC2_SHARE_SIZE     (VEC2_IDENTITY_BEGIN-VEC2_SHARE_BEGIN)

/* Similar to the SHARE indices, but for the identity mapping instead. */
#define VEC2_IDENTITY_BEGIN  X86_PDIR_VEC2INDEX(X86_PDIR_E1_IDENTITY_BASE)
#define VEC2_IDENTITY_SIZE  (1024-VEC2_IDENTITY_BEGIN)


#define EXPORT_AS_OBJECT(name) \
	.type name, @object; \
	.global name;
EXPORT_AS_OBJECT(vm_kernel)
EXPORT_AS_OBJECT(_this_idle)
EXPORT_AS_OBJECT(_bootcpu)
EXPORT_AS_OBJECT(_bootidle)
EXPORT_AS_OBJECT(_boottask)
EXPORT_AS_OBJECT(pagedir_kernel)
EXPORT_AS_OBJECT(pagedir_kernel_phys)
EXPORT_AS_OBJECT(jiffies)
EXPORT_AS_OBJECT(x86_idt_start)
EXPORT_AS_OBJECT(x86_idt_start_traced)
EXPORT_AS_OBJECT(x86_idt_start_debug)
#undef EXPORT_AS_OBJECT


EXTERN(boot_cpustate)
EXTERN(__kernel_boottask_stack)
EXTERN(__x86_bootcpu_features)
EXTERN(__x86_bootcpu_idfeatures)

.code32
.section .text.free
INTERN_FUNCTION(_start)
	/* Boot loader entry point. */
	movl   %edi, V2P(boot_cpustate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDI)
	movl   %esi, V2P(boot_cpustate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSI)
	movl   %ebp, V2P(boot_cpustate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBP)
	movl   %esp, V2P(boot_cpustate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSP)
	movl   %ebx, V2P(boot_cpustate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBX)
	movl   %edx, V2P(boot_cpustate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDX)
	movl   %ecx, V2P(boot_cpustate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RCX)
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RAX)
	sgdtl  V2P(boot_cpustate + OFFSET_FCPUSTATE_GDT + 2)
	sidtl  V2P(boot_cpustate + OFFSET_FCPUSTATE_IDT + 2)
	movl   $_start, V2P(boot_cpustate + OFFSET_FCPUSTATE_RIP)
	movw   %gs, V2P(boot_cpustate + OFFSET_FCPUSTATE_GS)
	movw   %fs, V2P(boot_cpustate + OFFSET_FCPUSTATE_FS)
	movw   %es, V2P(boot_cpustate + OFFSET_FCPUSTATE_ES)
	movw   %ds, V2P(boot_cpustate + OFFSET_FCPUSTATE_DS)
	movw   %cs, V2P(boot_cpustate + OFFSET_FCPUSTATE_CS)
	movw   %ss, V2P(boot_cpustate + OFFSET_FCPUSTATE_SS)
	strw   V2P(boot_cpustate + OFFSET_FCPUSTATE_TR)
	sldtw  V2P(boot_cpustate + OFFSET_FCPUSTATE_LDT)
	movl   %cr0, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR0)
	movl   %cr2, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR2)
	movl   %cr3, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR3)
	movl   %cr4, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR4)
	movl   %dr0, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR0)
	movl   %dr1, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR1)
	movl   %dr2, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR2)
	movl   %dr3, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR3)
	movl   %dr6, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR6)
	movl   %dr7, %eax
	movl   %eax, V2P(boot_cpustate + OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR7)

	/* Prematurely load our GDT, so we can manually set valid segments for %ds, %es and %ss,
	 * as we only want to rely on the boot loader to have set up a valid %ds and %cs */

	/* TODO: Load a custom, simplistig GDT */

	pushfl
	popl   V2P(boot_cpustate + OFFSET_FCPUSTATE_RFLAGS)

	cli  /* Disable interrupts */
	cld  /* Clear the direction bit (required for REP instructions) */

	/* memcpy(&_bootcpu, __kernel_percpu_start, (size_t)__kernel_percpu_size); */
#ifndef CONFIG_NO_SMP
	movl   $(V2P(_bootcpu)), %edi
	movl   $(V2P(__kernel_percpu_start)), %esi
	movl   $(__kernel_percpu_size), %ecx
	rep;   movsb
#endif /* !CONFIG_NO_SMP */
	/* memcpy(&_bootidle, __kernel_pertask_start, (size_t)__kernel_pertask_size); */
	movl   $(V2P(_bootidle)), %edi
	movl   $(V2P(__kernel_pertask_start)), %esi
	movl   $(__kernel_pertask_size), %ecx
	rep;   movsb
	/* memcpy(&_boottask, __kernel_pertask_start, (size_t)__kernel_pertask_size); */
	PUBLIC(_boottask)
	movl   $(V2P(_boottask)), %edi
	movl   $(V2P(__kernel_pertask_start)), %esi
	movl   $(__kernel_pertask_size), %ecx
	rep;   movsb
	/* memcpy((byte_t *)&vm_kernel + PAGEDIR_SIZE, __kernel_pervm_start, (size_t)__kernel_pervm_size); */
	PUBLIC(vm_kernel)
	movl   $(V2P(vm_kernel) + PAGEDIR_SIZE), %edi
	movl   $(V2P(__kernel_pervm_start)), %esi
	movl   $(__kernel_pervm_size), %ecx
	rep;   movsb


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


	orl    $(CPU_FEATURE_FCPUID), V2P(__x86_bootcpu_features)

	movl   $1, %eax
	cpuid
	movl   %eax, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_1A
	movl   %ebx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_1B
	movl   %edx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_1D
	movl   %ecx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_1C

	/* if (Family == 6 && Model < 3 && Stepping < 3)
	 *     OFFSET_CPUID_1D &= ~CPUID_1D_SEP; */
	testl  $(CPUID_1D_SEP), %edx
	jz     1f
	movl   %eax, %ecx
	andl   $(CPUID_1A_FAMILY_M), %ecx
	cmpl   $(6 << CPUID_1A_FAMILY_S), %ecx
	jne    1f  /* if (Family != 6) goto 1f; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_MODEL_M), %ecx
#if CPUID_1A_MODEL_S
	shrl   $(CPUID_1A_MODEL_S), %ecx
#endif /* CPUID_1A_MODEL_S */
	cmpl   $3, %ecx
	jae    1f  /* if (Model >= 3) goto 1f; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_STEPPING_M), %ecx
#if CPUID_1A_STEPPING_S
	shrl   $(CPUID_1A_STEPPING_S), %ecx
#endif /* CPUID_1A_STEPPING_S */
	cmpl   $3, %ecx
	/* if (Stepping >= 3) goto 1f; */
	jae    1f
	andl   $~CPUID_1D_SEP, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_1D
1:


	testl  $(CPUID_1D_PGE), %edx /* Check if the PAGE_FGLOBAL bit is supported. */
	jnz    1f
	movl   $0,   V2P(x86_page_global)
1:

	/* Query additional CPUID features. */
	movl   $0, %eax
	cpuid
	movl   %eax, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_0A
	movl   %ebx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_0B
	movl   %edx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_0D
	movl   %ecx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_0C
	cmpl   $(7), %eax
	jnae   1f
	movl   $(7), %eax
	movl   $(0), %ecx /* Sub-leaf:0 */
	cpuid
	movl   %edx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_7D
	movl   %ecx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_7C
	movl   %ebx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_7B
1:	movl   $(0x80000000), %eax
	cpuid
	movl   %eax, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000000A
	cmpl   $(0x80000001), %eax
	jnae   2f
	movl   $(0x80000001), %eax
	cpuid
	movl   %ecx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000001C
	movl   %edx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000001D
	movl   V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000000A, %eax
	cmpl   $(0x80000004), %eax
	jnae   3f
	movl   $(0x80000004), %eax
	cpuid
	movl   %eax, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000004A
	movl   %ebx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000004B
	movl   %ecx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000004C
	movl   %edx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000004D
	movl   $(0x80000003), %eax
	cpuid
	movl   %eax, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000003A
	movl   %ebx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000003B
	movl   %ecx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000003C
	movl   %edx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000003D
	movl   $(0x80000002), %eax
	cpuid
	movl   %eax, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000002A
	movl   %ebx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000002B
	movl   %ecx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000002C
	movl   %edx, V2P(__x86_bootcpu_idfeatures) + OFFSET_CPUID_80000002D
3:  /* ci_80000000a < 0x80000004 */
2:  /* ci_80000000a < 0x80000001 */
.Lno_cpuid:


	/* TODO */


END(_start)
