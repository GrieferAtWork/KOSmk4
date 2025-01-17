/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ARM_KOS_ASM_CPU_FLAGS_H
#define _ARM_KOS_ASM_CPU_FLAGS_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

/* Bits for CPSR / APSR */
#define CPSR_M     __UINT32_C(0x0000001f) /* [bit(4-0)]   Mode */
#   define CPSR_M_USR    __UINT32_C(0x10) /* User-space */
#   define CPSR_M_FIQ    __UINT32_C(0x11) /* Mode during FIRQ handling (s.a. `CPSR_F') */
#   define CPSR_M_IRQ    __UINT32_C(0x12) /* Mode during IRQ handling (s.a. `CPSR_I') */
#   define CPSR_M_SVC    __UINT32_C(0x13) /* Kernel-space (after user-space called `svc' aka. `swi') */
#   define CPSR_M_MON    __UINT32_C(0x16) /* ??? */
#   define CPSR_M_ABT    __UINT32_C(0x17) /* Mode when handling a page-fault */
#   define CPSR_M_HYP    __UINT32_C(0x1a) /* ??? */
#   define CPSR_M_UND    __UINT32_C(0x1b) /* Mode during illegal-instruction handling */
#   define CPSR_M_SYS    __UINT32_C(0x1f) /* ??? */
#define CPSR_T     __UINT32_C(0x00000020) /* [bit(5)]     Thumb mode enabled */
#define CPSR_F     __UINT32_C(0x00000040) /* [bit(6)]     FIRQ enabled */
#define CPSR_I     __UINT32_C(0x00000080) /* [bit(7)]     IRQ enabled */
#define CPSR_A     __UINT32_C(0x00000100) /* [bit(8)]     Asynchronous abort enabled */
#define CPSR_E     __UINT32_C(0x00000200) /* [bit(9)]     Endianness: (0: Little-endian; 1: Big-endian) */
#define CPSR_IT_HI __UINT32_C(0x0000fc00) /* [bit(10-15)] Execution state bits for the Thumb IT (If-Then) instruction (2..7) */
#define CPSR_GE    __UINT32_C(0x000f0000) /* [bit(16-19)] Greater than or Equal flags */
/*                            0x00100000   * ... */
/*                            0x00200000   * ... */
/*                            0x00400000   * ... */
/*                            0x00800000   * ... */
#define CPSR_J     __UINT32_C(0x01000000) /* [bit(24)]    Jazelle (???) */
#define CPSR_IT_LO __UINT32_C(0x06000000) /* [bit(25-26)] Execution state bits for the Thumb IT (If-Then) instruction (0..1) */
#define CPSR_Q     __UINT32_C(0x08000000) /* [bit(27)]    Cumulative saturation */
#define CPSR_V     __UINT32_C(0x10000000) /* [bit(28)]    Overflow cc-flag */
#define CPSR_C     __UINT32_C(0x20000000) /* [bit(29)]    Carry cc-flag */
#define CPSR_Z     __UINT32_C(0x40000000) /* [bit(30)]    Zero cc-flag */
#define CPSR_N     __UINT32_C(0x80000000) /* [bit(31)]    Negative cc-flag */

/* Mask of CPSR bits also accessible as APSR */
#define CPSR_APSRMASK __UINT32_C(0xff0ffc00)

#ifdef __KERNEL__
#define CPSR_MYMODE CPSR_M_SVC /* Probably... */
#else /* __KERNEL__ */
#define CPSR_MYMODE CPSR_M_USR
#endif /* !__KERNEL__ */


#endif /* !_ARM_KOS_ASM_CPU_FLAGS_H */
