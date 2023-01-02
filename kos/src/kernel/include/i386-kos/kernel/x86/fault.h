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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_FAULT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_FAULT_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

/* Makeup of `ecode' passed to `x86_handle_pagefault()' */
#define X86_PAGEFAULT_ECODE_PRESENT     0x0001 /* FLAG: The accessed page is present (Check for LOA) */
#define X86_PAGEFAULT_ECODE_WRITING     0x0002 /* FLAG: The fault happened as a result of a memory write (Check for COW) */
#define X86_PAGEFAULT_ECODE_USERSPACE   0x0004 /* FLAG: The fault occurred while in user-space */
#define X86_PAGEFAULT_ECODE_RESBIT      0x0008 /* FLAG: A reserved page bit is set */
#define X86_PAGEFAULT_ECODE_INSTRFETCH  0x0010 /* FLAG: The fault happened while fetching instructions.
                                                * NOTE: This flag  isn't guarantied  to be  set, though  an
                                                *       instruction-fetch fault can also easily be detected
                                                *       by comparing `%eip' with `%cr2' */

#ifdef __CC__
#ifdef BUILDING_KERNEL_CORE
DECL_BEGIN

/* Helpers and prototypes for c-level hardware fault handlers. */
struct icpustate;
struct df_cpustate;

/* Fallback interrupt handler. */
INTDEF ABNORMAL_RETURN WUNUSED NONNULL((1)) struct icpustate *FCALL
x86_handle_unhandled_idt(struct icpustate *__restrict state,
                         uintptr_t ecode, uintptr_t intno);

/* Exception handlers */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_divide_by_zero(struct icpustate *__restrict state);                         /* #DE  Divide-by-zero */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_debugtrap(struct icpustate *__restrict state);                              /* #DB  Debug */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_non_maskable_interrupt(struct icpustate *__restrict state);                 /* #NMI Non-maskable Interrupt */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_breakpoint(struct icpustate *__restrict state);                             /* #BP  Breakpoint */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_overflow(struct icpustate *__restrict state);                               /* #OF  Overflow */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_bound_range(struct icpustate *__restrict state);                            /* #BR  Bound Range Exceeded */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_illegal_instruction(struct icpustate *__restrict state);                    /* #UD  Invalid Opcode */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_device_not_available(struct icpustate *__restrict state);                   /* #NM  Device Not Available */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct df_cpustate *FCALL x86_handle_double_fault(struct df_cpustate *__restrict state);                       /* #DF  Double Fault */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_coprocessor_fault(struct icpustate *__restrict state);                      /* #CSO Coprocessor Segment Overrun (unused on 486+) */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_invalid_tss(struct icpustate *__restrict state, uintptr_t ecode);           /* #TS  Invalid TSS */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_segment_not_present(struct icpustate *__restrict state, uintptr_t ecode);   /* #NP  Segment Not Present */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_stackfault(struct icpustate *__restrict state, uintptr_t ecode);            /* #SS  Stack-Segment Fault */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_gpf(struct icpustate *__restrict state, uintptr_t ecode);                   /* #GP  General Protection Fault */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_pagefault(struct icpustate *__restrict state, uintptr_t ecode, void *addr); /* #PF  Page Fault */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_0fh(struct icpustate *__restrict state);                                    /* Reserved (exception)... */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_fpu_x87(struct icpustate *__restrict state);                                /* #MF  x87 Floating-Point Exception */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_bad_alignment(struct icpustate *__restrict state, uintptr_t ecode);         /* #AC  Alignment Check */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_machine_check(struct icpustate *__restrict state);                          /* #MC  Machine Check */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_fpu_simd(struct icpustate *__restrict state);                               /* #XM  SIMD Floating-Point Exception */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_virtualization_error(struct icpustate *__restrict state);                   /* #VE  Virtualization Exception */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_15h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_16h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_17h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_18h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_19h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_1ah(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_1bh(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_1ch(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_1dh(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_security_exception(struct icpustate *__restrict state, uintptr_t ecode); /* #SX  Security Exception. */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_1fh(struct icpustate *__restrict state);

/* NT Service interrupt handlers. */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_20h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_21h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_22h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_23h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_24h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_25h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_26h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_27h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_28h(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_ms_fastfail(struct icpustate *__restrict state); /* __fastfail() */
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_2ah(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_2bh(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_2ch(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_2dh(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_2eh(struct icpustate *__restrict state);
INTDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL x86_handle_2fh(struct icpustate *__restrict state);

DECL_END
#endif /* BUILDING_KERNEL_CORE */
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_FAULT_H */
