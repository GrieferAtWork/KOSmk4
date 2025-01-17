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
#ifndef _I386_KOS_ASM_INSTR_MOVZXQ_H
#define _I386_KOS_ASM_INSTR_MOVZXQ_H 1

#include <__stdinc.h>

#include <hybrid/__asm.h>
#include <hybrid/host.h>

/* On x86_64, mov between 32-bit registers automatically fills in the upper 32  bits
 * of the destination register with all zeroes. - Sometimes, readability of assembly
 * can be improved  by explicitly annotating  this implicit zero-extension,  however
 * no instructions `movzbq' / `movzwq' / `movzlq' exist, but can easily be  emulated
 * by using assembly macros.
 * It is the purpose of this file to define these macros. */

#ifndef __COMPILER_NO_GCC_ASM_MACROS
#ifdef __x86_64__
__ASM_BEGIN
__ASM_L(.macro __call_with_32bit_register func:req, src:req, dst:req)
__ASM_L(.ifc __ASM_ARG(\dst),%rax; __ASM_ARG(\func) __ASM_ARG(\src), %eax; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%rcx; __ASM_ARG(\func) __ASM_ARG(\src), %ecx; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%rdx; __ASM_ARG(\func) __ASM_ARG(\src), %edx; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%rbx; __ASM_ARG(\func) __ASM_ARG(\src), %ebx; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%rsp; __ASM_ARG(\func) __ASM_ARG(\src), %esp; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%rbp; __ASM_ARG(\func) __ASM_ARG(\src), %ebp; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%rsi; __ASM_ARG(\func) __ASM_ARG(\src), %esi; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%rdi; __ASM_ARG(\func) __ASM_ARG(\src), %edi; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%r8; __ASM_ARG(\func) __ASM_ARG(\src), %r8d; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%r9; __ASM_ARG(\func) __ASM_ARG(\src), %r9d; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%r10; __ASM_ARG(\func) __ASM_ARG(\src), %r10d; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%r11; __ASM_ARG(\func) __ASM_ARG(\src), %r11d; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%r12; __ASM_ARG(\func) __ASM_ARG(\src), %r12d; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%r13; __ASM_ARG(\func) __ASM_ARG(\src), %r13d; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%r14; __ASM_ARG(\func) __ASM_ARG(\src), %r14d; .else)
__ASM_L(.ifc __ASM_ARG(\dst),%r15; __ASM_ARG(\func) __ASM_ARG(\src), %r15d; .else)
__ASM_L(.error "Expected a 64-bit register as first operand in `\func \src \dst`";)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endm)

/* Zero-extend an 8-bit register to 64 bits */
__ASM_L(.macro movzbq src:req, dst:req)
__ASM_L(	__call_with_32bit_register movzbl, __ASM_ARG(\src), __ASM_ARG(\dst))
__ASM_L(.endm)

/* Zero-extend a 16-bit register to 64 bits */
__ASM_L(.macro movzwq src:req, dst:req)
__ASM_L(	__call_with_32bit_register movzwl, __ASM_ARG(\src), __ASM_ARG(\dst))
__ASM_L(.endm)

/* Zero-extend a 32-bit register to 64 bits */
__ASM_L(.macro movzlq src:req, dst:req)
__ASM_L(	__call_with_32bit_register movl, __ASM_ARG(\src), __ASM_ARG(\dst))
__ASM_L(.endm)
__ASM_END
#if defined(__ASSEMBLER__) && defined(_I386_KOS_ASM_INSTR_COMPAT_H)
#define movzbP movzbq
#define movzwP movzwq
#define movzlP movzlq
#endif /* __ASSEMBLER__ && _I386_KOS_ASM_INSTR_COMPAT_H */
#endif /* __x86_64__ */
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */

#endif /* !_I386_KOS_ASM_INSTR_MOVZXQ_H */
