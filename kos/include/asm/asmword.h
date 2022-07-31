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
#ifndef _ASM_ASMWORD_H
#define _ASM_ASMWORD_H 1

#include <__stdinc.h>

#include <hybrid/__asm.h>
#include <hybrid/typecore.h> /* __SIZEOF_POINTER__ */

/* Helper assembler macros for encoding fixed-width data words in
 * text,  as  well as  module-relative  (non-relocated) pointers. */

#ifndef __COMPILER_NO_GCC_ASM_MACROS
__ASM_BEGIN

/* Emit an 8-bit word */
__ASM_L(.macro .word8 value:req)
__ASM_L(	.1byte __ASM_ARG(\value))
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
#if __SIZEOF_POINTER__ == 8
__ASM_L(	.8byte __ASM_ARG(\value))
#elif __SIZEOF_POINTER__ == 4
__ASM_L(	.4byte __ASM_ARG(\value))
#elif __SIZEOF_POINTER__ == 2
__ASM_L(	.2byte __ASM_ARG(\value))
#elif __SIZEOF_POINTER__ == 1
__ASM_L(	.1byte __ASM_ARG(\value))
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported __SIZEOF_POINTER__"
#endif /* __SIZEOF_POINTER__ != ... */
__ASM_L(.endm)

/* Emit a pointer-sized relocation to `value', offset by `offset',
 * that   will  become  a   module-relative  pointer  at  runtime. */
#undef __ARCH_HAVE_wordrel
__ASM_L(.macro .wordrel value:req, offset=0)
__ASM_L(	.error "Not implemented for this architecture: '.wordrel'")
__ASM_L(.endm)


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
#undef __ARCH_HAVE_wordoff
__ASM_L(.macro .wordoff value:req, offset=0)
__ASM_L(	.error "Not implemented for this architecture: '.wordoff'")
__ASM_L(.endm)

__ASM_END
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */

#endif /* !_ASM_ASMWORD_H */
