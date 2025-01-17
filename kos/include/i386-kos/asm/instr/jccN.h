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
#ifndef _I386_KOS_ASM_INSTR_JCCN_H
#define _I386_KOS_ASM_INSTR_JCCN_H 1

#include <__stdinc.h>

#include <hybrid/__asm.h>
#include <hybrid/host.h>

/* When writing  self-modifying code,  it is  often very  important to  already
 * know the size of the generated code at assembly-time, rather than link-time,
 * as one often has to ensure sufficient padding space for being able to inject
 * instruction overrides.
 * However, on x86, the conditional jump instructions (jcc) pose a problem for this,
 * since they can be assembled in one of a couple of ways (each of which results  in
 * different instruction lengths):
 * >>  jz    1f
 * Can be assembled as:
 * #1: >>  jz8   1f  // 8-bit displacement
 * #2: >>  jz32  1f  // 32-bit displacement
 * #3: >>  jnz8  2f  // Reverse 8-bit displacement, used to wrap a 32-bit displacement
 *     >>  jmp32 1f
 *     >>2:
 * Because of these choices that can often only be made later on during linking, one might
 * get  an assembler error `error : non-constant expression in ".if" statement', since the
 * exact size of a instruction is yet to be known.
 *
 * To fix this problem, the programmer can make use of the macros in this file to explicitly
 * select between 8-bit or 32-bit displacements, such that the instruction length is already
 * known early on during assembly
 */

#ifndef __COMPILER_NO_GCC_ASM_MACROS
__ASM_BEGIN
__ASM_L(.macro jmp8   sym:req; .byte 0xeb; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jo8    sym:req; .byte 0x70; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jno8   sym:req; .byte 0x71; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jb8    sym:req; .byte 0x72; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jc8    sym:req; .byte 0x72; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jnae8  sym:req; .byte 0x72; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jae8   sym:req; .byte 0x73; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jnb8   sym:req; .byte 0x73; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jnc8   sym:req; .byte 0x73; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro je8    sym:req; .byte 0x74; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jz8    sym:req; .byte 0x74; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jne8   sym:req; .byte 0x75; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jnz8   sym:req; .byte 0x75; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jbe8   sym:req; .byte 0x76; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jna8   sym:req; .byte 0x76; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro ja8    sym:req; .byte 0x77; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jnbe8  sym:req; .byte 0x77; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro js8    sym:req; .byte 0x78; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jns8   sym:req; .byte 0x79; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jp8    sym:req; .byte 0x7a; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jpe8   sym:req; .byte 0x7a; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jnp8   sym:req; .byte 0x7b; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jpo8   sym:req; .byte 0x7b; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jl8    sym:req; .byte 0x7c; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jnge8  sym:req; .byte 0x7c; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jge8   sym:req; .byte 0x7d; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jnl8   sym:req; .byte 0x7d; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jle8   sym:req; .byte 0x7e; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jng8   sym:req; .byte 0x7e; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jg8    sym:req; .byte 0x7f; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jnle8  sym:req; .byte 0x7f; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jcxz8  sym:req; .byte 0x66, 0xe3; .byte __ASM_ARG(\sym) - (.+1); .endm)
__ASM_L(.macro jecxz8 sym:req; .byte 0xe3; .byte __ASM_ARG(\sym) - (.+1); .endm)
#ifdef __x86_64__
__ASM_L(.macro jrcxz8 sym:req; .byte 0x48, 0xe3; .byte __ASM_ARG(\sym) - (.+1); .endm)
#endif /* __x86_64__ */
__ASM_L(.macro jmp32   sym:req; .byte 0xe9; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jo32    sym:req; .byte 0x0f, 0x80; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jno32   sym:req; .byte 0x0f, 0x81; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jb32    sym:req; .byte 0x0f, 0x82; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jc32    sym:req; .byte 0x0f, 0x82; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jnae32  sym:req; .byte 0x0f, 0x82; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jae32   sym:req; .byte 0x0f, 0x83; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jnb32   sym:req; .byte 0x0f, 0x83; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jnc32   sym:req; .byte 0x0f, 0x83; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro je32    sym:req; .byte 0x0f, 0x84; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jz32    sym:req; .byte 0x0f, 0x84; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jne32   sym:req; .byte 0x0f, 0x85; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jnz32   sym:req; .byte 0x0f, 0x85; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jbe32   sym:req; .byte 0x0f, 0x86; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jna32   sym:req; .byte 0x0f, 0x86; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro ja32    sym:req; .byte 0x0f, 0x87; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jnbe32  sym:req; .byte 0x0f, 0x87; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro js32    sym:req; .byte 0x0f, 0x88; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jns32   sym:req; .byte 0x0f, 0x89; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jp32    sym:req; .byte 0x0f, 0x8a; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jpe32   sym:req; .byte 0x0f, 0x8a; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jnp32   sym:req; .byte 0x0f, 0x8b; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jpo32   sym:req; .byte 0x0f, 0x8b; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jl32    sym:req; .byte 0x0f, 0x8c; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jnge32  sym:req; .byte 0x0f, 0x8c; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jge32   sym:req; .byte 0x0f, 0x8d; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jnl32   sym:req; .byte 0x0f, 0x8d; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jle32   sym:req; .byte 0x0f, 0x8e; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jng32   sym:req; .byte 0x0f, 0x8e; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jg32    sym:req; .byte 0x0f, 0x8f; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_L(.macro jnle32  sym:req; .byte 0x0f, 0x8f; .long __ASM_ARG(\sym) - (.+4); .endm)
__ASM_END
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */

#endif /* !_I386_KOS_ASM_INSTR_JCCN_H */
