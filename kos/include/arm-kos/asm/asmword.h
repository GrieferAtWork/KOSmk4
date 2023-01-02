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
#ifndef _ARM_KOS_ASM_ASMWORD_H
#define _ARM_KOS_ASM_ASMWORD_H 1

#include <__stdinc.h>

#include <hybrid/__asm.h>
#include <hybrid/host.h>

/* Helper assembler macros for encoding fixed-width data words in
 * text,  as  well as  module-relative  (non-relocated) pointers. */

#ifndef __COMPILER_NO_GCC_ASM_MACROS
__ASM_BEGIN

/* Emit an 8-bit word */
__ASM_L(.macro .word8 value:req)
__ASM_L(	.byte __ASM_ARG(\value))
__ASM_L(.endm)

/* Emit a 16-bit word */
__ASM_L(.macro .word16 value:req)
__ASM_L(	.2byte __ASM_ARG(\value))
__ASM_L(.endm)

/* Emit a 32-bit word */
__ASM_L(.macro .word32 value:req)
__ASM_L(	.4byte __ASM_ARG(\value))
__ASM_L(.endm)

/* Emit a 64-bit word */
__ASM_L(.macro .word64 value:req)
__ASM_L(	.8byte __ASM_ARG(\value))
__ASM_L(.endm)

/* Emit a pointer-sized word */
__ASM_L(.macro .wordptr value:req)
#ifdef __aarch64__
__ASM_L(	.8byte __ASM_ARG(\value))
#else /* __aarch64__ */
__ASM_L(	.4byte __ASM_ARG(\value))
#endif /* !__aarch64__ */
__ASM_L(.endm)

/* Doesn't work because LD sucks: "dangerous relocation: unsupported relocation" */
#undef __ARCH_HAVE_wordrel
#if 0
/* Emit a pointer-sized relocation to `value', offset by `offset',
 * that   will  become  a   module-relative  pointer  at  runtime. */
__ASM_L(.macro .wordrel value:req, offset=0)
#ifdef __aarch64__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("R_AARCH64_RELATIVE")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef R_AARCH64_RELATIVE
__ASM_L(	.reloc .,R_AARCH64_RELATIVE, __ASM_ARG(\value))
__ASM_L(	.quad __ASM_ARG(\offset))
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("R_AARCH64_RELATIVE")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#else /* __aarch64__ */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("R_ARM_RELATIVE")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef R_ARM_RELATIVE
__ASM_L(	.reloc .,R_ARM_RELATIVE, __ASM_ARG(\value))
__ASM_L(	.long __ASM_ARG(\offset))
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("R_ARM_RELATIVE")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !__aarch64__ */
__ASM_L(.endm)
#endif


/* Emit a pointer-sized relocation to `value', offset by `offset',
 * that   will   become  a   self-relative  pointer   at  runtime:
 *
 * >> exterin int bar(void);
 * >>
 * >> __asm__(".pushsection .rodata\n\t"
 * >>         "foo: .wordoff bar\n\t"
 * >>         ".popsection");
 * >> extern uintptr_t foo;
 * >>
 * >> void test(void) {
 * >>     void *a = (void *)&bar;
 * >>     void *b = (byte_t *)&foo + foo;
 * >>     assert(a == b);
 * >> }
 */
#define __ARCH_HAVE_wordoff
__ASM_L(.macro .wordoff value:req, offset=0)
#ifdef __aarch64__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("R_AARCH64_REL64")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef R_AARCH64_REL64
__ASM_L(	.reloc .,R_AARCH64_REL64, __ASM_ARG(\value))
__ASM_L(	.8byte __ASM_ARG(\offset))
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("R_AARCH64_REL64")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#else /* __aarch64__ */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("R_ARM_REL32")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef R_ARM_REL32
__ASM_L(	.reloc .,R_ARM_REL32, __ASM_ARG(\value))
__ASM_L(	.4byte __ASM_ARG(\offset))
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("R_ARM_REL32")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !__aarch64__ */
__ASM_L(.endm)

__ASM_END
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */

#endif /* !_ARM_KOS_ASM_ASMWORD_H */
