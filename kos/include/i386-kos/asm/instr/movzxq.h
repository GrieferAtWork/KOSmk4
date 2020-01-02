/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef _I386_KOS_ASM_INSTR_MOVZXQ_H
#define _I386_KOS_ASM_INSTR_MOVZXQ_H 1

#include <__stdinc.h>
#include <hybrid/__asm.h>
#include <hybrid/host.h>

/* On x86_64, mov between 32-bit registers automatically fills in the upper 32 bits
 * of the destination register with all zeroes. - Sometimes, readability of assembly
 * can be improved by explicitly annotating this implicit zero-extension, however
 * no instructions `movzbq' / `movzwq' / `movzlq' exist, but can easily be emulated
 * by using assembly macros.
 * It is the purpose of this file to define these macros. */

#ifdef __x86_64__
__ASM_BEGIN
__ASM_L(.macro __call_with_32bit_register func:req, src:req, dst:req)
__ASM_L(.ifc \dst,%rax; \func \src, %eax; .else)
__ASM_L(.ifc \dst,%rcx; \func \src, %ecx; .else)
__ASM_L(.ifc \dst,%rdx; \func \src, %edx; .else)
__ASM_L(.ifc \dst,%rbx; \func \src, %ebx; .else)
__ASM_L(.ifc \dst,%rsp; \func \src, %esp; .else)
__ASM_L(.ifc \dst,%rbp; \func \src, %ebp; .else)
__ASM_L(.ifc \dst,%rsi; \func \src, %esi; .else)
__ASM_L(.ifc \dst,%rdi; \func \src, %edi; .else)
__ASM_L(.ifc \dst,%r8; \func \src, %r8d; .else)
__ASM_L(.ifc \dst,%r9; \func \src, %r9d; .else)
__ASM_L(.ifc \dst,%r10; \func \src, %r10d; .else)
__ASM_L(.ifc \dst,%r11; \func \src, %r11d; .else)
__ASM_L(.ifc \dst,%r12; \func \src, %r12d; .else)
__ASM_L(.ifc \dst,%r13; \func \src, %r13d; .else)
__ASM_L(.ifc \dst,%r14; \func \src, %r14d; .else)
__ASM_L(.ifc \dst,%r15; \func \src, %r15d; .else)
__ASM_L(.error 'Expected a 64-bit register as first operand in `\func \src \dst`')
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endm)

/* Zero-extend an 8-bit register to 64 bits */
__ASM_L(.macro movzbq src:req, dst:req)
__ASM_L(	__call_with_32bit_register movzbl, \src, \dst)
__ASM_L(.endm)

/* Zero-extend a 16-bit register to 64 bits */
__ASM_L(.macro movzwq src:req, dst:req)
__ASM_L(	__call_with_32bit_register movzwl, \src, \dst)
__ASM_L(.endm)

/* Zero-extend a 32-bit register to 64 bits */
__ASM_L(.macro movzlq src:req, dst:req)
__ASM_L(	__call_with_32bit_register movl, \src, \dst)
__ASM_L(.endm)
__ASM_END
#endif /* __x86_64__ */

#endif /* !_I386_KOS_ASM_INSTR_MOVZXQ_H */
