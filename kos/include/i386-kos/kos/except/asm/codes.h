/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_EXCEPT_ASM_CODE_H
#define _I386_KOS_KOS_EXCEPT_ASM_CODE_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

/* System exception classes.
 * NOTE: Many of these are never actually thrown, and those that are  also
 *       exist  as `E_*' classes below. Also note that some exceptions may
 *       be merged with others,  while allowing for differentiation  using
 *       `except_info()' (most notably: `X86_E_SYSTEM_GP' as the result of
 *       non-canonical memory access is  thrown an `E_SEGFAULT', which  is
 *       the same as `X86_E_SYSTEM_PF'). */
#define X86_E_SYSTEM_DE   0xff00 /* Divide-by-zero. */
#define X86_E_SYSTEM_DB   0xff01 /* Debug. */
#define X86_E_SYSTEM_NMI  0xff02 /* Non-maskable Interrupt. */
#define X86_E_SYSTEM_BP   0xff03 /* Breakpoint. */
#define X86_E_SYSTEM_OF   0xff04 /* Overflow. */
#define X86_E_SYSTEM_BR   0xff05 /* Bound Range Exceeded. */
#define X86_E_SYSTEM_UD   0xff06 /* Invalid Opcode. */
#define X86_E_SYSTEM_NM   0xff07 /* Device Not Available. */
#define X86_E_SYSTEM_DF   0xff08 /* Double Fault. */
/*      X86_E_SYSTEM_     0xff09  */
#define X86_E_SYSTEM_TS   0xff0a /* Invalid TSS. */
#define X86_E_SYSTEM_NP   0xff0b /* Segment Not Present. */
#define X86_E_SYSTEM_SS   0xff0c /* Stack-Segment Fault. */
#define X86_E_SYSTEM_GP   0xff0d /* General Protection Fault. */
#define X86_E_SYSTEM_PF   0xff0e /* Page Fault. */
/*      X86_E_SYSTEM_     0xff0f  */
#define X86_E_SYSTEM_MF   0xff10 /* x87 Floating-Point Exception. */
#define X86_E_SYSTEM_AC   0xff11 /* Alignment Check. */
#define X86_E_SYSTEM_MC   0xff12 /* Machine Check. */
#define X86_E_SYSTEM_XM   0xff13 /* SIMD Floating-Point Exception. */
#define X86_E_SYSTEM_VE   0xff14 /* Virtualization Exception. */
/*      X86_E_SYSTEM_     0xff15  */
/*                        ....    */
/*      X86_E_SYSTEM_     0xff1d  */
#define X86_E_SYSTEM_SX   0xff1e /* Security Exception. */
/*      X86_E_SYSTEM_     0xff1f  */
#define X86_E_SYSTEM_XF   X86_E_SYSTEM_XM /* Alias */


/* Exception code overrides */
#define E_SEGFAULT            (X86_E_SYSTEM_PF)
#define E_BREAKPOINT          (X86_E_SYSTEM_BP)
#define E_DIVIDE_BY_ZERO      (X86_E_SYSTEM_DE)
#define E_OVERFLOW            (X86_E_SYSTEM_OF)
#define E_ILLEGAL_INSTRUCTION (X86_E_SYSTEM_UD)
#define E_STACK_OVERFLOW      (X86_E_SYSTEM_DF)
#define E_INDEX_ERROR         (X86_E_SYSTEM_BR)


/* Helper macros to encode/decode the `opcode' field of `E_ILLEGAL_INSTRUCTION'
 * NOTE: If the instruction doesn't depend on `modrm_reg', set it directly. */
#define E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, modrm_reg) \
	(__CCAST(__UINT32_TYPE__)(opcode) |                     \
	 __CCAST(__UINT32_TYPE__)(modrm_reg) << 29 |            \
	 __UINT32_C(0x10000000))
#define E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETOPC(v) \
	(__CCAST(__UINT32_TYPE__)(v) & __UINT32_C(0x0fffffff))
#define E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETREG(v) \
	(__CCAST(__UINT8_TYPE__)(__CCAST(__UINT32_TYPE__)(v) >> 29))
#define E_ILLEGAL_INSTRUCTION_X86_OPCODE_HASREG(v) \
	(__CCAST(__UINT32_TYPE__)(v) & __UINT32_C(0x10000000))



#endif /* !_I386_KOS_KOS_EXCEPT_ASM_CODE_H */
