/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_GDT_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_GDT_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <kernel/x86/gdt.h>

#include <kos/kernel/cpu-state.h>

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
#define GDT_L  1
#define GDT_DB 0
#define N64(...) /* nothing */
#else /* __x86_64__ */
#define GDT_L  0
#define GDT_DB 1
#define N64(...) __VA_ARGS__
#endif /* !__x86_64__ */

#ifdef __x86_64__
#define DEFINE_LOHI_SEGMENT(id, lo, hi)                     \
	[SEGMENT_INDEX(id) + 0] = { { .s_u = (uintptr_t)lo } }, \
	[SEGMENT_INDEX(id) + 1] = { { .s_u = (uintptr_t)hi } }
#else /* __x86_64__ */
#define DEFINE_LOHI_SEGMENT(id, lo, hi) \
	[SEGMENT_INDEX(id)] = { { { (uintptr_t)lo, (uintptr_t)hi } } }
#endif /* !__x86_64__ */

#define DTX SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD /* Code descriptor */
#define DTD SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR /* Data descriptor */

PUBLIC ATTR_DBGDATA struct segment x86_dbggdt[SEGMENT_COUNT] = {
	[SEGMENT_INDEX(SEGMENT_NULL)]          = SEGMENT_DESCRIPTOR_INIT(0, 0, 0, 0, 0, 0, 0, 0, 0, 0),                  /* NULL segment */
	DEFINE_LOHI_SEGMENT(SEGMENT_CPU_TSS, __x86_gdt_tss_lo, __x86_gdt_tss_hi),                                        /* CPU TSS */
	N64(DEFINE_LOHI_SEGMENT(SEGMENT_CPU_TSS_DF, __x86_gdt_tss_df_lo, __x86_gdt_tss_df_hi),)                          /* CPU TSS (for #DF) */
	DEFINE_LOHI_SEGMENT(SEGMENT_CPU_LDT, __x86_gdt_ldt_lo, __x86_gdt_ldt_hi),                                        /* CPU LDT */
	N64(DEFINE_LOHI_SEGMENT(SEGMENT_KERNEL_FSBASE, __x86_gdt_kernel_tls_lo, __x86_gdt_kernel_tls_hi),)               /* THIS_TASK */
	[SEGMENT_INDEX(SEGMENT_USER_FSBASE)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTD, 1, 3, 1, 0, 0, 1, 1),          /* User %fs base (32-bit) */
	[SEGMENT_INDEX(SEGMENT_USER_GSBASE)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTD, 1, 3, 1, 0, 0, 1, 1),          /* User %gs base (32-bit) */
	[SEGMENT_INDEX(SEGMENT_KERNEL_CODE)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTX, 1, 0, 1, 0, GDT_L, GDT_DB, 1), /* Kernel code segment */
	[SEGMENT_INDEX(SEGMENT_KERNEL_DATA)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTD, 1, 0, 1, 0, GDT_L, GDT_DB, 1), /* Kernel data segment */
	[SEGMENT_INDEX(SEGMENT_USER_CODE32)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTX, 1, 3, 1, 0, 0, 1, 1),          /* User code (32-bit) */
	[SEGMENT_INDEX(SEGMENT_USER_DATA32)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTD, 1, 3, 1, 0, 0, 1, 1),          /* User data (32-bit) */
#ifdef __x86_64__
	[SEGMENT_INDEX(SEGMENT_USER_CODE64)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTX, 1, 3, 1, 0, 1, 0, 1),          /* User code (64-bit) */
	[SEGMENT_INDEX(SEGMENT_USER_DATA64)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTD, 1, 3, 1, 0, 1, 0, 1),          /* User data (64-bit) */
	[SEGMENT_INDEX(SEGMENT_KERNEL_CODE32)] = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTX, 1, 0, 1, 0, 0, 1, 1),          /* Kernel code (32-bit) */
	[SEGMENT_INDEX(SEGMENT_KERNEL_DATA32)] = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTD, 1, 0, 1, 0, 0, 1, 1),          /* Kernel data (32-bit) */
#endif /* __x86_64__ */
};

PUBLIC_CONST ATTR_DBGRODATA struct desctab const x86_dbggdt_ptr = {
	/* .dt_limit = */ sizeof(x86_dbggdt) - 1,
	/* .dt_base  = */ (uintptr_t)&x86_dbggdt[0]
};

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_GDT_C */
