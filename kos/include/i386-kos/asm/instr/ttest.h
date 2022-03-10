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
#ifndef _I386_KOS_ASM_INSTR_TTEST_H
#define _I386_KOS_ASM_INSTR_TTEST_H 1

#include <__stdinc.h>

#include <hybrid/__asm.h>
#include <hybrid/host.h>

/* Helper macros to automatically select the optimal encoding for
 * the `test' instruction being  used with an immediate  operand.
 *
 * Using this, something like
 *    `testl $0x10000, foo'
 *
 * can be optimized into
 *    `testb $0x1, foo+2'
 *
 * when instead written as:
 *    `ttest  mask=0x10000, loc=foo'
 *
 * You can also use registers for the `loc' operand. */



/*
 * Q: Why do you check for 32-bit masks using this:
 *    >> (__ASM_ARG(\mask) <= 0xffffffff) || (__ASM_ARG(\mask) >= (-0x7fffffff - 1) && __ASM_ARG(\mask) <= 0x7fffffff)
 *    Instead of just doing this:
 *    >> (__ASM_ARG(\mask) <= 0xffffffff))
 *    When I use the later, it's working fine for me, so what's with the bloat?
 *
 * A: Weird answer:
 *      You've just revealed to me that you're using a 64-bit computer to build KOS.
 *    Short answer:
 *      GAS sucks!
 *    Long answer:
 *      GAS still sucks. And here's why:
 *      When building the KOS toolchain on a 32-bit machine, the assembler that gets
 *      built (which is the one that has to parse the conditional expression) is set
 *      up such that  it uses  host-machine-sized data words  to store  intermediate
 *      values for use in constant expressions (emphasis on the "host" part). Before
 *      I set out to build KOS on the  old i386 linux server I've got sitting in  my
 *      basement, I always thought gas  used 64-bit integers in all  configurations.
 *      Well: I was proven wrong, so to give you an example:
 *         >> .if (0x8000000 < 0)
 *         >> .error "The machine you're using to assemble this file is 32-bit"
 *         >> .else
 *         >> .error "The machine you're using to assemble this file is 64-bit"
 *         >> .endif
 *      Reason: `0x8000000' becomes INT32_MIN when casted to signed 32-bit,  which
 *      is exactly what GAS does (without warning) if the machine it is running on
 *      is a 32-bit machine.
 *      So  if you take another look at the expression above, you will see that the
 *      `(__ASM_ARG(\mask) >= (-0x7fffffff - 1) && __ASM_ARG(\mask) <= 0x7fffffff)'
 *      part  always becomes true  if all operands are  truncated to signed 32-bit.
 *      But if the  operands are allowed  to be signed  64-bit (as is  the case  if
 *      your build machine is 64-bit), then the expression correctly works to  test
 *      for signed 32-bit integer (or unsigned 31-bit, hence why we still need  the
 *      other `<= UINT32_MAX'-style check to accept all types of 32-bit  integers).
 */


#ifndef __COMPILER_NO_GCC_ASM_MACROS
__ASM_BEGIN

/* ttest with register operand in `regname+regkind',
 * which is one of a,c,d,b:
 *    regkind=0: b,d,c,a
 *    regkind=1: di,si,bp,sp
 *    regkind=2: r8,r9,r10,r11,r12,r13,r14,r15  (__x86_64__ only)
 */
__ASM_L(.macro __ttest_r mask:req, regname:req, regkind:req)
#ifdef __x86_64__
__ASM_L(.if (__ASM_ARG(\regkind) == 2))
__ASM_L(	.if (__ASM_ARG(\mask) <= 0xff))
__ASM_L(		testb $(__ASM_ARG(\mask)), %__ASM_ARG(\regname)__ASM_ARG(\())b)
__ASM_L(	.elseif (__ASM_ARG(\mask) <= 0xffff))
__ASM_L(		testw $(__ASM_ARG(\mask)), %__ASM_ARG(\regname)__ASM_ARG(\())w)
__ASM_L(	.elseif (__ASM_ARG(\mask) <= 0xffffffff) || (__ASM_ARG(\mask) >= (-0x7fffffff - 1) && __ASM_ARG(\mask) <= 0x7fffffff))
__ASM_L(		testl $(__ASM_ARG(\mask)), %__ASM_ARG(\regname)__ASM_ARG(\())d)
__ASM_L(	.else)
__ASM_L(		.error "ttest: unsupported mask: \mask";)
__ASM_L(	.endif)
__ASM_L(.elseif (__ASM_ARG(\regkind)))
#else /* __x86_64__ */
__ASM_L(.if (__ASM_ARG(\regkind)))
#endif /* !__x86_64__ */
#ifdef __x86_64__
__ASM_L(	.if (__ASM_ARG(\mask) <= 0xff))
__ASM_L(		testb $(__ASM_ARG(\mask)), %__ASM_ARG(\regname)__ASM_ARG(\())l)
__ASM_L(	.elseif (__ASM_ARG(\mask) <= 0xffff))
#else /* __x86_64__ */
__ASM_L(	.if (__ASM_ARG(\mask) <= 0xffff))
#endif /* !__x86_64__ */
__ASM_L(		testw $(__ASM_ARG(\mask)), %__ASM_ARG(\regname))
__ASM_L(	.elseif (__ASM_ARG(\mask) <= 0xffffffff) || (__ASM_ARG(\mask) >= (-0x7fffffff - 1) && __ASM_ARG(\mask) <= 0x7fffffff))
#if defined(__ASSEMBLER__) || defined(__TPP_VERSION__)
__ASM_L(		testl $(\mask), %e\regname)
#else /* __ASSEMBLER__ || __TPP_VERSION__ */
__ASM_L(		testl $(\\mask), %e\\regname)
#endif /* !__ASSEMBLER__ && !__TPP_VERSION__ */
__ASM_L(	.else)
__ASM_L(		.error "ttest: unsupported mask: \mask";)
__ASM_L(	.endif)
__ASM_L(.else)
__ASM_L(	.if (__ASM_ARG(\mask) <= 0xff))
__ASM_L(		testb $(__ASM_ARG(\mask)), %__ASM_ARG(\regname)__ASM_ARG(\())l)
__ASM_L(	.elseif (__ASM_ARG(\mask) <= 0xffff))
__ASM_L(		.if (__ASM_ARG(\mask) >= 0xff00))
__ASM_L(			testb $((__ASM_ARG(\mask)) >> 8), %__ASM_ARG(\regname)__ASM_ARG(\())h)
__ASM_L(		.else)
__ASM_L(			testw $(__ASM_ARG(\mask)), %__ASM_ARG(\regname)__ASM_ARG(\())x)
__ASM_L(		.endif)
__ASM_L(	.elseif (__ASM_ARG(\mask) <= 0xffffffff) || (__ASM_ARG(\mask) >= (-0x7fffffff - 1) && __ASM_ARG(\mask) <= 0x7fffffff))
#if defined(__ASSEMBLER__) || defined(__TPP_VERSION__)
__ASM_L(		testl $(\mask), %e\regname\()x)
#else /* __ASSEMBLER__ || __TPP_VERSION__ */
__ASM_L(		testl $(\\mask), %e\\regname\\()x)
#endif /* !__ASSEMBLER__ && !__TPP_VERSION__ */
__ASM_L(	.else)
__ASM_L(		.error "ttest: unsupported mask: \mask";)
__ASM_L(	.endif)
__ASM_L(.endif)
__ASM_L(.endm)

/* Same as `test[b|w|l|q] $mask, loc', but when `loc' is a memory location,
 * automatically  try  to  truncate  `mask',  and  adjust  `loc'  to reduce
 * the final sizeof the instruction.
 * As such, something like:  ttest 0x200, foo(%eax)
 * ... eventually becomes:   testb $0x2, 1+foo(%eax)
 * NOTE: `mask' must always be a 32-bit, unsigned, immediate
 *       constant  integer.  No   extern  symbols   allowed!
 * HINT: ttest stands for TruncatedTEST */
__ASM_L(.macro ttest mask:req, loc:req, seg='')
__ASM_L(.ifc __ASM_ARG(\loc),%al; __ttest_r __ASM_ARG(\mask), a, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%ax; __ttest_r __ASM_ARG(\mask), a, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%eax; __ttest_r __ASM_ARG(\mask), a, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%cl; __ttest_r __ASM_ARG(\mask), c, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%cx; __ttest_r __ASM_ARG(\mask), c, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%ecx; __ttest_r __ASM_ARG(\mask), c, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%dl; __ttest_r __ASM_ARG(\mask), d, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%dx; __ttest_r __ASM_ARG(\mask), d, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%edx; __ttest_r __ASM_ARG(\mask), d, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%bl; __ttest_r __ASM_ARG(\mask), b, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%bx; __ttest_r __ASM_ARG(\mask), b, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%ebx; __ttest_r __ASM_ARG(\mask), b, 0; .else)
#ifdef __x86_64__
__ASM_L(.ifc __ASM_ARG(\loc),%rax; __ttest_r __ASM_ARG(\mask), a, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%rcx; __ttest_r __ASM_ARG(\mask), c, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%rdx; __ttest_r __ASM_ARG(\mask), d, 0; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%rbx; __ttest_r __ASM_ARG(\mask), b, 0; .else)
#endif /* __x86_64__ */
__ASM_L(.ifc __ASM_ARG(\loc),%di; __ttest_r __ASM_ARG(\mask), di, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%edi; __ttest_r __ASM_ARG(\mask), di, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%si; __ttest_r __ASM_ARG(\mask), si, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%esi; __ttest_r __ASM_ARG(\mask), si, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%bp; __ttest_r __ASM_ARG(\mask), bp, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%ebp; __ttest_r __ASM_ARG(\mask), bp, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%sp; __ttest_r __ASM_ARG(\mask), sp, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%esp; __ttest_r __ASM_ARG(\mask), sp, 1; .else)
#ifdef __x86_64__
__ASM_L(.ifc __ASM_ARG(\loc),%dil; __ttest_r __ASM_ARG(\mask), di, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%rdi; __ttest_r __ASM_ARG(\mask), di, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%sil; __ttest_r __ASM_ARG(\mask), si, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%rsi; __ttest_r __ASM_ARG(\mask), si, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%bpl; __ttest_r __ASM_ARG(\mask), bp, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%rbp; __ttest_r __ASM_ARG(\mask), bp, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%spl; __ttest_r __ASM_ARG(\mask), sp, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%rsp; __ttest_r __ASM_ARG(\mask), sp, 1; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r8b; __ttest_r __ASM_ARG(\mask), r8, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r8w; __ttest_r __ASM_ARG(\mask), r8, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r8d; __ttest_r __ASM_ARG(\mask), r8, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r8; __ttest_r __ASM_ARG(\mask), r8, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r9b; __ttest_r __ASM_ARG(\mask), r9, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r9w; __ttest_r __ASM_ARG(\mask), r9, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r9d; __ttest_r __ASM_ARG(\mask), r9, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r9; __ttest_r __ASM_ARG(\mask), r9, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r10b; __ttest_r __ASM_ARG(\mask), r10, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r10w; __ttest_r __ASM_ARG(\mask), r10, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r10d; __ttest_r __ASM_ARG(\mask), r10, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r10; __ttest_r __ASM_ARG(\mask), r10, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r11b; __ttest_r __ASM_ARG(\mask), r11, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r11w; __ttest_r __ASM_ARG(\mask), r11, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r11d; __ttest_r __ASM_ARG(\mask), r11, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r11; __ttest_r __ASM_ARG(\mask), r11, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r12b; __ttest_r __ASM_ARG(\mask), r12, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r12w; __ttest_r __ASM_ARG(\mask), r12, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r12d; __ttest_r __ASM_ARG(\mask), r12, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r12; __ttest_r __ASM_ARG(\mask), r12, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r13b; __ttest_r __ASM_ARG(\mask), r13, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r13w; __ttest_r __ASM_ARG(\mask), r13, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r13d; __ttest_r __ASM_ARG(\mask), r13, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r13; __ttest_r __ASM_ARG(\mask), r13, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r14b; __ttest_r __ASM_ARG(\mask), r14, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r14w; __ttest_r __ASM_ARG(\mask), r14, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r14d; __ttest_r __ASM_ARG(\mask), r14, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r14; __ttest_r __ASM_ARG(\mask), r14, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r15b; __ttest_r __ASM_ARG(\mask), r15, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r15w; __ttest_r __ASM_ARG(\mask), r15, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r15d; __ttest_r __ASM_ARG(\mask), r15, 2; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%r15; __ttest_r __ASM_ARG(\mask), r15, 2; .else)
#endif /* __x86_64__ */
__ASM_L(.ifc __ASM_ARG(\loc),%ah; testb $(__ASM_ARG(\mask)), %ah; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%ch; testb $(__ASM_ARG(\mask)), %ch; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%dh; testb $(__ASM_ARG(\mask)), %dh; .else)
__ASM_L(.ifc __ASM_ARG(\loc),%bh; testb $(__ASM_ARG(\mask)), %bh; .else)
/* With that, all of the different registers have been handled.
 * Now  to  deal  with  testing  of  actual  memory  locations. */
__ASM_L(.if (__ASM_ARG(\mask) <= 0xff))
__ASM_L(	.ifc __ASM_ARG(\seg),'')
__ASM_L(		testb $(__ASM_ARG(\mask)), __ASM_ARG(\loc))
__ASM_L(	.else)
__ASM_L(		testb $(__ASM_ARG(\mask)), __ASM_ARG(\seg):__ASM_ARG(\loc))
__ASM_L(	.endif)
__ASM_L(.elseif (__ASM_ARG(\mask) <= 0xffff))
__ASM_L(	.if (__ASM_ARG(\mask) & 0xff) == 0)
__ASM_L(		.ifc __ASM_ARG(\seg),'')
__ASM_L(			testb $((__ASM_ARG(\mask)) >> 8), 1+__ASM_ARG(\loc))
__ASM_L(		.else)
__ASM_L(			testb $((__ASM_ARG(\mask)) >> 8), __ASM_ARG(\seg):1+__ASM_ARG(\loc))
__ASM_L(		.endif)
__ASM_L(	.else)
__ASM_L(		.ifc __ASM_ARG(\seg),'')
__ASM_L(			testw $(__ASM_ARG(\mask)), __ASM_ARG(\loc))
__ASM_L(		.else)
__ASM_L(			testw $(__ASM_ARG(\mask)), __ASM_ARG(\seg):__ASM_ARG(\loc))
__ASM_L(		.endif)
__ASM_L(	.endif)
__ASM_L(.elseif (__ASM_ARG(\mask) <= 0xffffffff) || (__ASM_ARG(\mask) >= (-0x7fffffff - 1) && __ASM_ARG(\mask) <= 0x7fffffff))
__ASM_L(	.if (__ASM_ARG(\mask) & 0xffffff) == 0)
__ASM_L(		.ifc __ASM_ARG(\seg),'')
__ASM_L(			testb $((__ASM_ARG(\mask)) >> 24), 3+__ASM_ARG(\loc))
__ASM_L(		.else)
__ASM_L(			testb $((__ASM_ARG(\mask)) >> 24), __ASM_ARG(\seg):3+__ASM_ARG(\loc))
__ASM_L(		.endif)
__ASM_L(	.elseif (__ASM_ARG(\mask) & 0xffff) == 0)
__ASM_L(		.ifc __ASM_ARG(\seg),'')
__ASM_L(			testw $((__ASM_ARG(\mask)) >> 16), 2+__ASM_ARG(\loc))
__ASM_L(		.else)
__ASM_L(			testw $((__ASM_ARG(\mask)) >> 16), __ASM_ARG(\seg):2+__ASM_ARG(\loc))
__ASM_L(		.endif)
__ASM_L(	.else)
__ASM_L(		.ifc __ASM_ARG(\seg),'')
__ASM_L(			testl $(__ASM_ARG(\mask)), __ASM_ARG(\loc))
__ASM_L(		.else)
__ASM_L(			testl $(__ASM_ARG(\mask)), __ASM_ARG(\seg):__ASM_ARG(\loc))
__ASM_L(		.endif)
__ASM_L(	.endif)
__ASM_L(.elseif (__ASM_ARG(\mask) <= 0xffffffffffffffff))
__ASM_L(	.if (__ASM_ARG(\mask) & 0xffffffffffffff) == 0)
__ASM_L(		.ifc __ASM_ARG(\seg),'')
__ASM_L(			testb $((__ASM_ARG(\mask)) >> 56), 7+__ASM_ARG(\loc))
__ASM_L(		.else)
__ASM_L(			testb $((__ASM_ARG(\mask)) >> 56), __ASM_ARG(\seg):7+__ASM_ARG(\loc))
__ASM_L(		.endif)
__ASM_L(	.elseif (__ASM_ARG(\mask) & 0xffffffffffff) == 0)
__ASM_L(		.ifc __ASM_ARG(\seg),'')
__ASM_L(			testw $((__ASM_ARG(\mask)) >> 48), 6+__ASM_ARG(\loc))
__ASM_L(		.else)
__ASM_L(			testw $((__ASM_ARG(\mask)) >> 48), __ASM_ARG(\seg):6+__ASM_ARG(\loc))
__ASM_L(		.endif)
__ASM_L(	.elseif (__ASM_ARG(\mask) & 0xffffffff) == 0)
__ASM_L(		.ifc __ASM_ARG(\seg),'')
__ASM_L(			testl $((__ASM_ARG(\mask)) >> 32), 4+__ASM_ARG(\loc))
__ASM_L(		.else)
__ASM_L(			testl $((__ASM_ARG(\mask)) >> 32), __ASM_ARG(\seg):4+__ASM_ARG(\loc))
__ASM_L(		.endif)
__ASM_L(	.else)
__ASM_L(		.error "ttest: unsupported mask: \mask";)
__ASM_L(	.endif)
__ASM_L(.else)
__ASM_L(	.error "ttest: unsupported mask: \mask";)
__ASM_L(.endif)

__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif)
#ifdef __x86_64__
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
#endif /* __x86_64__ */
__ASM_L(.endm)

__ASM_END
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */

#endif /* !_I386_KOS_ASM_INSTR_TTEST_H */
