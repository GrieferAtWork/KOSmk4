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
#ifndef _I386_KOS_KOS_KERNEL_GDT_H
#define _I386_KOS_KOS_KERNEL_GDT_H 1

#include <__stdinc.h>
#include <bits/types.h>
#include <features.h>

__SYSDECL_BEGIN

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

/* Segment descriptor allocations made by the KOS kernel. */
#define SEGMENT_NULL            0x0000 /* NULL-segment. */
#define SEGMENT_KERNEL_CODE     0x0008 /* Ring #0 code segment (%cs) */
#define SEGMENT_KERNEL_DATA     0x0010 /* Ring #0 data segment (%ss)
                                        * NOTE: For %ds and %es, `SEGMENT_USER_DATA' is re-used, so-as to reduce
                                        *       the number of required segment changes during interrupts/syscalls.
                                        *       However, this also means that user-space isn't allowed to change the
                                        *       base addresses of these segments, but only allowed to change those of
                                        *       `SEGMENT_USER_FSBASE' and `SEGMENT_USER_GSBASE', which can be done by
                                        *       use of the `wrfsbase' and `wrgsbase' instruction (which are emulated
                                        *       within a 32-bit kernel) */
#define SEGMENT_USER_CODE       0x0018 /* Ring #3 code segment (%cs) */
#define SEGMENT_USER_CODE_RPL   0x001b /* SEGMENT_USER_CODE | 3 */
#define SEGMENT_USER_DATA       0x0020 /* Ring #3 data segment (%ds, %es) */
#define SEGMENT_USER_DATA_RPL   0x0023 /* SEGMENT_USER_DATA | 3 */
#ifdef __x86_64__
#define SEGMENT_USER_CODE32     0x0028 /* Ring #3 32-bit code segment (%cs) */
#define SEGMENT_USER_CODE32_RPL 0x002b /* SEGMENT_USER_CODE32 | 3 */
#define SEGMENT_USER_DATA32     0x0030 /* Ring #3 32-bit data segment (%ds, %es) */
#define SEGMENT_USER_DATA32_RPL 0x0033 /* SEGMENT_USER_DATA32 | 3 */
#define SEGMENT_CPU_LDT         0x0040 /* Local descriptor table segment */
#define SEGMENT_CPU_TSS         0x0050 /* TSS segment of the current CPU (%tr; aka. `ltr') */
#define SEGMENT_COUNT           12
/* TODO: Binary compatibility so that user-space can set `SEGMENT_USER_FSBASE_RPL'
 *       and `SEGMENT_USER_GSBASE_RPL' while running in compatibility mode (in this
 *       case, these 2 should simply refer to two more simple, flat DPL=3 data segment) */
#else /* __x86_64__ */
#define SEGMENT_CPU_TSS         0x0028 /* TSS segment of the current CPU (%tr; aka. `ltr') */
#define SEGMENT_CPU_TSS_DF      0x0030 /* TSS segment of the current CPU when handling #DF faults. */
#define SEGMENT_CPU_LDT         0x0038 /* Local descriptor table segment */
#define SEGMENT_KERNEL_FSBASE   0x0040 /* Ring #0 fs-base (%fs; Pointers to the `struct task' of the current thread)
                                        * NOTE: This segment's base address is updated during every task-switch,
                                        *       and represents the linear base address of the current task. */
#define SEGMENT_USER_FSBASE     0x0048 /* Ring #3 fs-segment (%fs by convention (user may re-assign the base to another segment))
                                        * NOTE: This segment's base address is updated during every task-switch,
                                        *       and stored on a per-task basis. */
#define SEGMENT_USER_FSBASE_RPL 0x004b /* SEGMENT_USER_FSBASE | 3 */
#define SEGMENT_USER_GSBASE     0x0050 /* Ring #3 gs-segment (%gs by convention (user may re-assign the base to another segment))
                                        * NOTE: This segment's base address is updated during every task-switch,
                                        *       and stored on a per-task basis. */
#define SEGMENT_USER_GSBASE_RPL 0x0053 /* SEGMENT_USER_GSBASE | 3 */
#define SEGMENT_COUNT           11
#endif /* !__x86_64__ */


#define LDT_SEGMENT_SYSCALL     0x0000 /* System call callgate (for use with `lcall $7, $...') */
#define LDT_SEGMENT_SYSCALL_RPL 0x0007 /* LDT_SEGMENT_SYSCALL | 7 */
#ifdef __x86_64__
#define LDT_SEGMENT_COUNT       2 /* `LDT_SEGMENT_SYSCALL' takes up 2 entries. */
#else /* __x86_64__ */
#define LDT_SEGMENT_COUNT       1
#endif /* !__x86_64__ */


#ifdef __x86_64__
#define SEGMENT_IS_VALID_USERCODE(x) ((x) == SEGMENT_USER_CODE_RPL || (x) == SEGMENT_USER_CODE32_RPL)
#define SEGMENT_IS_VALID_USERDATA(x) ((x) == SEGMENT_USER_DATA_RPL || (x) == SEGMENT_USER_DATA32_RPL)
#else /* __x86_64__ */
#define SEGMENT_IS_VALID_USERCODE(x) ((x) == SEGMENT_USER_CODE_RPL)
#define SEGMENT_IS_VALID_USERDATA(x) ((x) == SEGMENT_USER_DATA_RPL || \
                                      (x) == SEGMENT_USER_FSBASE_RPL || \
                                      (x) == SEGMENT_USER_GSBASE_RPL)
#endif /* !__x86_64__ */

/* NOTES:
 * In kernel-space:
 *   - `%ds' is always `SEGMENT_USER_DATA_RPL'
 *   - `%es' is always `SEGMENT_USER_DATA_RPL'
 *   - `%ss' is always `SEGMENT_KERNEL_DATA'
 *   - `%cs' is always `SEGMENT_KERNEL_CODE'
 *   - `%fs' is always `SEGMENT_KERNEL_FSBASE'
 *   - `%gs' is undefined (left unchanged), which means it's usually `SEGMENT_USER_GSBASE_RPL'
 *
 * In user-space:
 *   - `%ds' is usually `SEGMENT_USER_DATA_RPL'
 *   - `%es' is usually `SEGMENT_USER_DATA_RPL'
 *   - `%ss' is usually `SEGMENT_USER_DATA_RPL'
 *   - `%cs' is always `SEGMENT_USER_CODE_RPL'
 *   - `%fs' is usually `SEGMENT_USER_FSBASE_RPL'
 *   - `%gs' is usually `SEGMENT_USER_GSBASE_RPL'
 *
 * The fact that %gs goes unused in kernel-space is also the reason why
 * some CPU state structures exist that simply omit it, as it doesn't
 * need to be saved/written/restored for the purposes of syscalls or hardware
 * interrupts. The only place where it does actually need to be saved is when
 * it comes to scheduling, as different user-space tasks are allowed to have
 * different values for their %gs segment selector.
 */



#ifdef SEGMENT_USER_CODE32_RPL
#define __KOS64_IS_CS32(cs) ((cs) == SEGMENT_USER_CODE32_RPL)
#define __KOS64_IS_CS64(cs) ((cs) != SEGMENT_USER_CODE32_RPL)
#else /* SEGMENT_USER_CODE32_RPL */
#define __KOS64_IS_CS32(cs) ((cs) == 0x002b)
#define __KOS64_IS_CS64(cs) ((cs) != 0x002b)
#endif /* !SEGMENT_USER_CODE32_RPL */


__SYSDECL_END

#endif /* !_I386_KOS_KOS_KERNEL_GDT_H */
