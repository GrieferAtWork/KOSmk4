/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_GDT_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_GDT_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>
#include <kernel/debugger.h>
#include <kernel/gdt.h>

#ifndef CONFIG_NO_DEBUGGER
DECL_BEGIN

INTDEF byte_t __x86_gdt_tss_lo[];
INTDEF byte_t __x86_gdt_tss_hi[];
INTDEF byte_t __x86_gdt_ldt_lo[];
INTDEF byte_t __x86_gdt_ldt_hi[];
#ifndef __x86_64__
INTDEF byte_t __x86_gdt_tss_df_lo[];
INTDEF byte_t __x86_gdt_tss_df_hi[];
INTDEF byte_t __x86_gdt_kernel_tls_lo[];
INTDEF byte_t __x86_gdt_kernel_tls_hi[];
#endif /* !__x86_64__ */

#ifdef __x86_64__
#define GDT_L 1
#else
#define GDT_L 0
#endif

PUBLIC struct segment x86_debug_gdt[SEGMENT_COUNT] = {
	[SEGMENT_INDEX(SEGMENT_NULL)]          = SEGMENT_DESCRIPTOR_INIT(0, 0, 0, 0, 0, 0, 0, 0, 0, 0),                                           /* NULL segment */
	[SEGMENT_INDEX(SEGMENT_KERNEL_CODE)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 0, 1, 0, GDT_L, 1, 1), /* Kernel code segment */
	[SEGMENT_INDEX(SEGMENT_KERNEL_DATA)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, GDT_L, 1, 1), /* Kernel data segment */
	[SEGMENT_INDEX(SEGMENT_USER_CODE)]     = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 3, 1, 0, GDT_L, 1, 1), /* User code */
	[SEGMENT_INDEX(SEGMENT_USER_DATA)]     = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 3, 1, 0, GDT_L, 1, 1), /* User data */
#ifdef __x86_64__
	[SEGMENT_INDEX(SEGMENT_USER_CODE32)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 0, 1, 0, 0, 1, 1),     /* User code (32-bit mode) */
	[SEGMENT_INDEX(SEGMENT_USER_DATA32)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, 0, 1, 1),     /* User data (32-bit mode) */
	[SEGMENT_INDEX(0x38)]                  = SEGMENT_DESCRIPTOR_INIT(0, 0, 0, 0, 0, 0, 0, 0, 0, 0),                                           /* Unused... */
	[SEGMENT_INDEX(SEGMENT_CPU_LDT) + 0]   = { { .s_u = (uintptr_t)__x86_gdt_ldt_lo } },                                                      /* CPU LDT */
	[SEGMENT_INDEX(SEGMENT_CPU_LDT) + 1]   = { { .s_u = (uintptr_t)__x86_gdt_ldt_hi } },                                                      /* CPU LDT */
	[SEGMENT_INDEX(SEGMENT_CPU_TSS) + 0]   = { { .s_u = (uintptr_t)__x86_gdt_tss_lo } },                                                      /* CPU TSS */
	[SEGMENT_INDEX(SEGMENT_CPU_TSS) + 1]   = { { .s_u = (uintptr_t)__x86_gdt_tss_hi } },                                                      /* CPU TSS */
#else /* __x86_64__ */
	[SEGMENT_INDEX(SEGMENT_CPU_TSS)]       = { { { (uintptr_t)__x86_gdt_tss_lo, (uintptr_t)__x86_gdt_tss_hi } } },                            /* CPU TSS */
	[SEGMENT_INDEX(SEGMENT_CPU_TSS_DF)]    = { { { (uintptr_t)__x86_gdt_tss_df_lo, (uintptr_t)__x86_gdt_tss_df_hi } } },                      /* CPU TSS (for #DF) */
	[SEGMENT_INDEX(SEGMENT_CPU_LDT)]       = { { { (uintptr_t)__x86_gdt_ldt_lo, (uintptr_t)__x86_gdt_ldt_hi } } },                            /* CPU LDT */
	[SEGMENT_INDEX(SEGMENT_KERNEL_FSBASE)] = { { { (uintptr_t)__x86_gdt_kernel_tls_lo, (uintptr_t)__x86_gdt_kernel_tls_hi } } },              /* task-self */
	[SEGMENT_INDEX(SEGMENT_USER_FSBASE)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 3, 1, 0, GDT_L, 1, 1), /* User %fs base */
	[SEGMENT_INDEX(SEGMENT_USER_GSBASE)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 3, 1, 0, GDT_L, 1, 1), /* User %gs base */
#endif /* !__x86_64__ */
};

DECL_END
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_GDT_C */
