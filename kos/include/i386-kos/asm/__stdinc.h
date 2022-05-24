/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_ASM___STDINC_H
#define _I386_KOS_ASM___STDINC_H 1

#if (defined(__KOS__) && defined(__KERNEL__) && defined(__i386__) && !defined(__x86_64__) && \
     (defined(CONFIG_NO_VM86) || (defined(CONFIG_VM86) && (-CONFIG_VM86 - 1) == -1)))
/* Disable support for hardware vm86 mode (iow: no special handling for `EFLAGS_VM' in interrupts)
 * -> This does not affect software-emulation of vm86, as can be done with libvm86! */
#define __I386_NO_VM86
#endif /* ... */

#if (!defined(__INTELLISENSE__) && defined(__CC__) && \
     defined(__KOS__) && defined(__KERNEL__) &&       \
     defined(__COMPILER_HAVE_GCC_ASM) && !defined(__HAVE_FPU))
/* Define some macros to force liner errors when GCC tries to use
 * floating-point instructions. This  can unintentionally  happen
 * when 32-bit codes  uses ATOMIC_READ()  or ATOMIC_WRITE()  with
 * 64-bit operands.
 *
 * These are set-up to cause linker errors (which include file+
 * line info) when an FPU  instruction does end up being  used. */
__asm__(
".macro fildq _a:vararg\n"
"\t.hidden __x86_linkerror_fpu_instruction_fildq\n"
"\tcall __x86_linkerror_fpu_instruction_fildq\n"
".endm\n"
".macro fistpq _a:vararg\n"
"\t.hidden __x86_linkerror_fpu_instruction_fistpq\n"
"\tcall __x86_linkerror_fpu_instruction_fistpq\n"
".endm\n");
#endif /* ... */

#endif /* !_I386_KOS_ASM___STDINC_H */
