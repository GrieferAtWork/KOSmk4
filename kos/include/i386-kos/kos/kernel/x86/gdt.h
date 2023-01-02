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
#ifndef _I386_KOS_KOS_KERNEL_X86_GDT_H
#define _I386_KOS_KOS_KERNEL_X86_GDT_H 1

#include <__stdinc.h>

#include <bits/types.h>

/*
 * NOTE: Segment  indices must be selected to fulfill the
 *       following architecturally mandated requirements:
 * >> SEGMENT_KERNEL_CODE == IA32_SYSENTER_CS       (sysenter)
 * >> SEGMENT_KERNEL_DATA == IA32_SYSENTER_CS + 8   (sysenter)
 * >> SEGMENT_USER_CODE32 == IA32_SYSENTER_CS + 16  (sysexit)
 * >> SEGMENT_USER_DATA32 == IA32_SYSENTER_CS + 24  (sysexit)
 * >> SEGMENT_KERNEL_CODE == IA32_STAR[47:32]       (syscall)
 * >> SEGMENT_KERNEL_DATA == IA32_STAR[47:32] + 8   (syscall)
 * >> SEGMENT_USER_CODE32 == IA32_STAR[63:48]       (sysret)
 * >> SEGMENT_USER_DATA32 == IA32_STAR[63:48] + 8   (sysret)
 * >> SEGMENT_USER_CODE64 == IA32_STAR[63:48] + 16  (sysret)
 *
 * Or simplified:
 * >> SEGMENT_KERNEL_CODE == BASE       (sysenter)
 * >> SEGMENT_KERNEL_DATA == BASE + 8   (sysenter, syscall)
 * >> SEGMENT_USER_CODE32 == BASE + 16  (sysexit)
 * >> SEGMENT_USER_DATA32 == BASE + 24  (sysexit)
 * >> SEGMENT_USER_CODE64 == BASE + 32  (sysret)
 * With:
 * >> IA32_SYSENTER_CS = SEGMENT_KERNEL_CODE
 * >> IA32_STAR[47:32] = SEGMENT_KERNEL_CODE
 * >> IA32_STAR[63:48] = SEGMENT_USER_CODE32 | 3 (aka. `SEGMENT_USER_CODE32_RPL')
 *
 * Also: Since these segment indices are visible  to user-space, make sure that  any
 *       segment that may be useful to user-space (such as all of the SEGMENT_USER_*
 *       segments)  have the same value between 32-bit and 64-bit mode, irregardless
 *       of user-space being hosted by a 32-bit or 64-bit kernel.
 *       User-space should be allowed to hard-code expected segment values when it
 *       deems that doing so may be beneficial.
 */


/************************************************************************/
/* GDT SEGMENT INDICES                                                  */
/************************************************************************/
#define SEGMENT_NULL            0x0000 /* NULL-segment. */
#define SEGMENT_CPU_TSS         0x0008 /* TSS segment of the current CPU (%tr; aka. `ltr') */
#ifdef __x86_64__
#define SEGMENT_CPU_TSS2        0x0010 /* On x86_64, a TSS requires two consecutive entries. */
#else /* __x86_64__ */
#define SEGMENT_CPU_TSS_DF      0x0010 /* TSS segment of the current CPU when handling #DF faults. */
#endif /* !__x86_64__ */
#define SEGMENT_CPU_LDT         0x0018 /* Local descriptor table segment */
#ifdef __x86_64__
#define SEGMENT_CPU_LDT2        0x0020 /* On x86_64, an LDT requires two consecutive entries. */
#else /* __x86_64__ */
#define SEGMENT_KERNEL_FSBASE   0x0020 /* Ring #0 fs-base (%fs; Pointers to the `struct task' of the current thread)
                                        * NOTE: This segment's base address is updated during every task-switch,
                                        *       and represents  the linear  base address  of the  current  task. */
#endif /* !__x86_64__ */
#define SEGMENT_USER_FSBASE     0x0028 /* Ring #3 fs-segment (%fs by convention (user may re-assign the base address)) */
#define SEGMENT_USER_FSBASE_RPL 0x002b /* SEGMENT_USER_FSBASE | 3 */
#define SEGMENT_USER_GSBASE     0x0030 /* Ring #3 gs-segment (%gs by convention (user may re-assign the base address)) */
#define SEGMENT_USER_GSBASE_RPL 0x0033 /* SEGMENT_USER_GSBASE | 3 */
#define SEGMENT_KERNEL_CODE     0x0038 /* Ring #0 code segment (%cs) */
#define SEGMENT_KERNEL_DATA     0x0040 /* Ring #0 data segment (%ss)
                                        * NOTE: For %ds  and %es,  `SEGMENT_USER_DATA' is  re-used, so-as  to  reduce
                                        *       the number of  required segment  changes during  interrupts/syscalls.
                                        *       However,  this also means that user-space isn't allowed to change the
                                        *       base addresses of these segments, but only allowed to change those of
                                        *       `SEGMENT_USER_FSBASE' and `SEGMENT_USER_GSBASE', which can be done by
                                        *       use of the `wrfsbase' and `wrgsbase' instruction (which are  emulated
                                        *       within a 32-bit kernel) */
#define SEGMENT_USER_CODE32     0x0048 /* Ring #3 32-bit code segment (%cs) */
#define SEGMENT_USER_CODE32_RPL 0x004b /* SEGMENT_USER_CODE32 | 3 */
#define SEGMENT_USER_DATA32     0x0050 /* Ring #3 32-bit data segment (%ss, %ds, %es) */
#define SEGMENT_USER_DATA32_RPL 0x0053 /* SEGMENT_USER_DATA32 | 3 */
#ifdef __x86_64__
#define SEGMENT_USER_CODE64     0x0058 /* Ring #3 64-bit code segment (%cs) */
#define SEGMENT_USER_CODE64_RPL 0x005b /* SEGMENT_USER_CODE64 | 3 */
#define SEGMENT_USER_DATA64     0x0060 /* Ring #3 64-bit data segment (%ss, %ds, %es) */
#define SEGMENT_USER_DATA64_RPL 0x0063 /* SEGMENT_USER_DATA64 | 3 */
#define SEGMENT_KERNEL_CODE32   0x0068 /* Ring #0 32-bit code segment (%cs) */
#define SEGMENT_KERNEL_DATA32   0x0070 /* Ring #0 32-bit data segment (%ss) */
#define SEGMENT_COUNT           15
#else /* __x86_64__ */
#define SEGMENT_COUNT           11
#endif /* !__x86_64__ */
/************************************************************************/




/* The effective user-space code segment (for use outside of compatibility mode) */
#ifdef __x86_64__
#define SEGMENT_USER_CODE     SEGMENT_USER_CODE64     /* Ring #3 code segment (%cs) */
#define SEGMENT_USER_CODE_RPL SEGMENT_USER_CODE64_RPL /* SEGMENT_USER_CODE | 3 */
#define SEGMENT_USER_DATA     SEGMENT_USER_DATA64     /* Ring #3 data segment (%ss, %ds, %es) */
#define SEGMENT_USER_DATA_RPL SEGMENT_USER_DATA64_RPL /* SEGMENT_USER_DATA | 3 */
#else /* __x86_64__ */
#define SEGMENT_USER_CODE     SEGMENT_USER_CODE32     /* Ring #3 code segment (%cs) */
#define SEGMENT_USER_CODE_RPL SEGMENT_USER_CODE32_RPL /* SEGMENT_USER_CODE | 3 */
#define SEGMENT_USER_DATA     SEGMENT_USER_DATA32     /* Ring #3 data segment (%ss, %ds, %es) */
#define SEGMENT_USER_DATA_RPL SEGMENT_USER_DATA32_RPL /* SEGMENT_USER_DATA | 3 */
#endif /* !__x86_64__ */


/* The (expected) code/data segments for the current program */
#ifdef __KERNEL__
#define SEGMENT_CURRENT_CODE     SEGMENT_KERNEL_CODE
#define SEGMENT_CURRENT_DATA     SEGMENT_KERNEL_DATA
#define SEGMENT_CURRENT_CODE_RPL SEGMENT_KERNEL_CODE
#define SEGMENT_CURRENT_DATA_RPL SEGMENT_KERNEL_DATA
#else /* __KERNEL__ */
#define SEGMENT_CURRENT_CODE     SEGMENT_USER_CODE
#define SEGMENT_CURRENT_DATA     SEGMENT_USER_DATA
#define SEGMENT_CURRENT_CODE_RPL SEGMENT_USER_CODE_RPL
#define SEGMENT_CURRENT_DATA_RPL SEGMENT_USER_DATA_RPL
#endif /* !__KERNEL__ */


/************************************************************************/
/* LDT SEGMENT INDICES                                                  */
/************************************************************************/
#define LDT_SEGMENT_SYSCALL     0x0000 /* System call callgate (for use with `lcall $7, $...') */
#define LDT_SEGMENT_SYSCALL_RPL 0x0007 /* LDT_SEGMENT_SYSCALL | 7 */
#ifdef __x86_64__
#define LDT_SEGMENT_SYSCALL2    0x0008 /* On x86_64, a callgate requires two consecutive entries. */
#define LDT_SEGMENT_COUNT       2
#else /* __x86_64__ */
#define LDT_SEGMENT_COUNT       1
#endif /* !__x86_64__ */
/************************************************************************/


#ifdef __x86_64__
/* Because of stuff  like `mov $0, %ax; mov %ax, %fs;',  `0' must  also
 * be allowed as user-space segment index (except for %ss or %cs, which
 * aren't allowed to be loaded with a zero-selector) */
#define SEGMENT_IS_VALID_USERCODE(x)   ((x) == SEGMENT_USER_CODE64_RPL || (x) == SEGMENT_USER_CODE32_RPL)
#define SEGMENT_IS_VALID_USERCODE32(x) ((x) == SEGMENT_USER_CODE32_RPL)
#define SEGMENT_IS_VALID_USERCODE64(x) ((x) == SEGMENT_USER_CODE64_RPL)
#define SEGMENT_IS_VALID_USERDATA(x)   ((x) == SEGMENT_USER_DATA64_RPL || (x) == SEGMENT_USER_DATA32_RPL || (x) == SEGMENT_USER_FSBASE_RPL || (x) == SEGMENT_USER_GSBASE_RPL)
#define SEGMENT_IS_VALID_USERDATA32(x) ((x) == SEGMENT_USER_DATA32_RPL || (x) == SEGMENT_USER_FSBASE_RPL || (x) == SEGMENT_USER_GSBASE_RPL)
#define SEGMENT_IS_VALID_USERDATA64(x) ((x) == SEGMENT_USER_DATA64_RPL)
#define SEGMENT_IS_VALID_KERNCODE(x)   ((x) == SEGMENT_KERNEL_CODE)
#define SEGMENT_IS_VALID_KERNDATA(x)   ((x) == 0 || (x) == SEGMENT_KERNEL_DATA)
#define SEGMENT_KERNEL_DATA0           0
#else /* __x86_64__ */
#define SEGMENT_IS_VALID_USERCODE(x) ((x) == SEGMENT_USER_CODE32_RPL)
#define SEGMENT_IS_VALID_USERDATA(x) ((x) == SEGMENT_USER_DATA32_RPL || (x) == SEGMENT_USER_FSBASE_RPL || (x) == SEGMENT_USER_GSBASE_RPL)
#define SEGMENT_IS_VALID_KERNCODE(x) ((x) == SEGMENT_KERNEL_CODE)
#define SEGMENT_IS_VALID_KERNDATA(x) ((x) == SEGMENT_KERNEL_DATA)
#define SEGMENT_KERNEL_DATA0         SEGMENT_KERNEL_DATA
#endif /* !__x86_64__ */

/* NOTES:
 * In kernel-space (i386):
 *   - `%ds' is always `SEGMENT_USER_DATA_RPL'
 *   - `%es' is always `SEGMENT_USER_DATA_RPL'
 *   - `%ss' is always `SEGMENT_KERNEL_DATA'
 *   - `%cs' is always `SEGMENT_KERNEL_CODE'
 *   - `%fs' is always `SEGMENT_KERNEL_FSBASE'
 *   - `%gs' is undefined (left unchanged), which means it's usually `SEGMENT_USER_GSBASE_RPL'
 *
 * In kernel-space (x86_64):
 *   - `%ds' is undefined (left unchanged), which means it's usually `SEGMENT_USER_DATA64_RPL' or `SEGMENT_USER_DATA32_RPL'
 *   - `%es' is undefined (left unchanged), which means it's usually `SEGMENT_USER_DATA64_RPL' or `SEGMENT_USER_DATA32_RPL'
 *   - `%ss' is always either `SEGMENT_KERNEL_DATA' or `0'
 *   - `%cs' is always `SEGMENT_KERNEL_CODE'
 *   - `%fs' is undefined (left unchanged), which means it's usually `SEGMENT_USER_DATA64_RPL' or `SEGMENT_USER_FSBASE_RPL'
 *   - `%gs' is undefined (left unchanged), which means it's usually `SEGMENT_USER_DATA64_RPL' or `SEGMENT_USER_GSBASE_RPL'
 *
 * In user-space (i386 or IA32e-Compat):
 *   - `%ds' is usually `SEGMENT_USER_DATA32_RPL'
 *   - `%es' is usually `SEGMENT_USER_DATA32_RPL'
 *   - `%ss' is usually `SEGMENT_USER_DATA32_RPL'
 *   - `%cs' is always `SEGMENT_USER_CODE32_RPL'
 *   - `%fs' is usually `SEGMENT_USER_FSBASE_RPL'
 *   - `%gs' is usually `SEGMENT_USER_GSBASE_RPL'
 *
 * In user-space (x86_64):
 *   - `%ds' is usually `SEGMENT_USER_DATA64_RPL'
 *   - `%es' is usually `SEGMENT_USER_DATA64_RPL'
 *   - `%ss' is usually `SEGMENT_USER_DATA64_RPL'
 *   - `%cs' is always `SEGMENT_USER_CODE64_RPL'
 *   - `%fs' is usually `SEGMENT_USER_DATA64_RPL'
 *   - `%gs' is usually `SEGMENT_USER_DATA64_RPL'
 *
 * always:  Guarantied to be the case (may assume this case)
 * usually: Is the case by default; can be changed by factors (don't assume, but may optimize for this case)
 *
 * NOTE: The fact that %gs  goes unused in 32-bit  kernel-space is also the  reason
 *       why some CPU  state structures exist  that simply omit  it, as it  doesn't
 *       need to be saved/written/restored for the purposes of syscalls or hardware
 *       interrupts. The only place where it does actually need to be saved is when
 *       it comes to scheduling, as different user-space tasks are allowed to  have
 *       different values for their %gs segment selector.
 */



/* Helper macros for checking if a given segment is 32-bit, or 64-bit code. */
#define __KOS64_IS_CS32BIT(cs) ((cs) == SEGMENT_USER_CODE32_RPL)
#define __KOS64_IS_CS64BIT(cs) ((cs) != SEGMENT_USER_CODE32_RPL)


#endif /* !_I386_KOS_KOS_KERNEL_X86_GDT_H */
