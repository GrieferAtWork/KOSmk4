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
#ifndef _I386_KOS_ASM_INTRIN_CPUID_H
#define _I386_KOS_ASM_INTRIN_CPUID_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#include <asm/cpu-cpuid.h>
#include <asm/intrin.h>

/* Figure out  if feature  test  macros should  not  assume
 * kernel  emulation  for  certain  instructions.  This  is
 * required  while  in  kernel-space  itself  (in  order to
 * prevent  the   possibility  of   recursion  of   certain
 * instructions being accidentally emulated with  themself,
 * or when we're not actually compiling with KOS as target) */
#ifndef __WANT_CPU_HAVE_NOT_EMULATED
#if !defined(__KOS__) || defined(__KERNEL__)
#define __WANT_CPU_HAVE_NOT_EMULATED 1
#endif
#endif /* !__WANT_CPU_HAVE_NOT_EMULATED */


/* CPU feature helpers. */
#ifdef __CC__
__SYSDECL_BEGIN

/* NOTE: The `cpuid'  instruction is  emulated by  the
 *       KOS kernel and  can be used  unconditionally.
 *       Also note that a couple of other instructions
 *       are emulated.
 * To simplify CPU detection,  as well as the  fact
 * that I very much doubt the fact that you'll find
 * a CPU without `cpuid', as well as the fact  that
 * the KOS kernel emulates this instruction, checks
 * for  cpuid actually existing are omitted to keep
 * things a little bit simpler. */
#if defined(__SSE__) || defined(__SSE_MATH__)
#define __CPU_HAVE_SSE()       1
#else /* __SSE__ || __SSE_MATH__ */
#define __CPU_HAVE_SSE()       (__cpuid_edx(0x1) & CPUID_1D_SSE)
#endif /* !__SSE__ && !__SSE_MATH__ */
#if defined(__SSE2__) || defined(__SSE2_MATH__)
#define __CPU_HAVE_SSE2()      1
#else /* __SSE2__ || __SSE2_MATH__ */
#define __CPU_HAVE_SSE2()      (__cpuid_edx(0x1) & CPUID_1D_SSE2)
#endif /* !__SSE2__ && !__SSE2_MATH__ */
#define __CPU_HAVE_SSSE3()     (__cpuid_ecx(0x1) & CPUID_1C_SSSE3)
#define __CPU_HAVE_SSE4_1()    (__cpuid_ecx(0x1) & CPUID_1C_SSE4_1)
#define __CPU_HAVE_SSE4_2()    (__cpuid_ecx(0x1) & CPUID_1C_SSE4_2)
#ifndef __WANT_CPU_HAVE_NOT_EMULATED
#define __CPU_HAVE_CX8()       1 /* Emulated under KOS */
#define __CPU_HAVE_OSXSAVE()   1 /* Emulated under KOS */
#define __CPU_HAVE_POPCOUNT()  1 /* Emulated under KOS */
#define __CPU_HAVE_LZCNT()     1 /* Emulated under KOS */
#define __CPU_HAVE_MOVBE()     1 /* Emulated under KOS */
#else /* !__WANT_CPU_HAVE_NOT_EMULATED */
#define __CPU_HAVE_CX8()       (__cpuid_ecx(0x1) & CPUID_1D_CX8)
#define __CPU_HAVE_OSXSAVE()   (__cpuid_ecx(0x1) & CPUID_1C_OSXSAVE)
#define __CPU_HAVE_POPCOUNT()  (__cpuid_ecx(0x1) & CPUID_1C_POPCNT)
#define __CPU_HAVE_LZCNT()     (__cpuid_ecx(0x80000001) & CPUID_80000001C_ABM)
#define __CPU_HAVE_MOVBE()     (__cpuid_ecx(0x1) & CPUID_1C_MOVBE)
#endif /* __WANT_CPU_HAVE_NOT_EMULATED */
#if !defined(__WANT_CPU_HAVE_NOT_EMULATED) && defined(__x86_64__)
#define __CPU_HAVE_CX16()      1 /* Emulated under KOS */
#else /* !__WANT_CPU_HAVE_NOT_EMULATED && __x86_64__ */
#define __CPU_HAVE_CX16()      (__cpuid_ecx(0x1) & CPUID_1C_CX16)
#endif /* __WANT_CPU_HAVE_NOT_EMULATED || !__x86_64__ */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_ASM_INTRIN_CPUID_H */
