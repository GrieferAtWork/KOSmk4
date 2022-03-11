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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_MSABI64_S
#define GUARD_LIBC_LIBC_ARCH_I386_MSABI64_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <__crt.h>
#include <hybrid/compiler.h>

#include <hybrid/typecore.h>

#include <asm/cfi.h>
#include <asm/instr/movzxq.h>
#include <bits/types.h>
#include <sys/syscall.h>

#include <wctype.h> /* __SIZEOF_WCTRANS_T__ */

/**/
#include "msabi64.h"


/* Define type class IDs:
 *   - R: General purpose register argument
 *   - F: Floating point register argument
 */
#define TP     R
#define THH    R
#define TH     R
#define TD     R
#define TL     R
#define TLL    R
#define TF     F
#define TFD    F
#define TFL    F
#define TI     R
#define TI8    R
#define TI16   R
#define TI32   R
#define TI64   R
#define TIn(s) R
#define TS(n)  R /* ??? */
#define TCF    FF /* ??? */
#define TCFD   FF /* ??? */
#define TCFL   FF /* ??? */


#define MSABI64_CONVERTER_FOR_1(a)                                   libd_msabi64_##a
#define MSABI64_CONVERTER_FOR_2(a, b)                                libd_msabi64_##a##b
#define MSABI64_CONVERTER_FOR_3(a, b, c)                             libd_msabi64_##a##b##c
#define MSABI64_CONVERTER_FOR_4(a, b, c, d)                          libd_msabi64_##a##b##c##d
#define MSABI64_CONVERTER_FOR_5(a, b, c, d, e)                       libd_msabi64_##a##b##c##d##e
#define MSABI64_CONVERTER_FOR_6(a, b, c, d, e, f)                    libd_msabi64_##a##b##c##d##e##f
#define MSABI64_CONVERTER_FOR_7(a, b, c, d, e, f, g)                 libd_msabi64_##a##b##c##d##e##f##g
#define MSABI64_CONVERTER_FOR_8(a, b, c, d, e, f, g, h)              libd_msabi64_##a##b##c##d##e##f##g##h
#define MSABI64_CONVERTER_FOR_9(a, b, c, d, e, f, g, h, i)           libd_msabi64_##a##b##c##d##e##f##g##h##i
#define MSABI64_CONVERTER_FOR_10(a, b, c, d, e, f, g, h, i, j)       libd_msabi64_##a##b##c##d##e##f##g##h##i##j
#define MSABI64_CONVERTER_FOR_11(a, b, c, d, e, f, g, h, i, j, k)    libd_msabi64_##a##b##c##d##e##f##g##h##i##j##k
#define MSABI64_CONVERTER_FOR_12(a, b, c, d, e, f, g, h, i, j, k, l) libd_msabi64_##a##b##c##d##e##f##g##h##i##j##k##l

#define MSABI64_CONVERTER_FOR3(func, argv) func argv
#define MSABI64_CONVERTER_FOR2(argc, argv) MSABI64_CONVERTER_FOR3(MSABI64_CONVERTER_FOR_##argc, argv)
#define MSABI64_CONVERTER_FOR(argc, ...)   MSABI64_CONVERTER_FOR2(argc, (__VA_ARGS__))


/* Floating point argument passing is identical between msabi and sysvabi,
 * with the exception that msabi requires a bunch of fpu registers to stay
 * preserved upon return. */
#define libd_msabi64_F      libd_msabi64_R
#define libd_msabi64_FF     libd_msabi64_R
#define libd_msabi64_FFF    libd_msabi64_R
#define libd_msabi64_FFFF   libd_msabi64_R
#define libd_msabi64_FFR    libd_msabi64_R
#define libd_msabi64_FR     libd_msabi64_R
#define libd_msabi64_FRR    libd_msabi64_RR
#define libd_msabi64_FRRR   libd_msabi64_RRR
#define libd_msabi64_RRRF   libd_msabi64_RRR
#define libd_msabi64_FRRRRR libd_msabi64_RRRRR
#define libd_msabi64_RF     libd_msabi64_R
#define libd_msabi64_RRFR   libd_msabi64_RRR
#define libd_msabi64_RRFRRR libd_msabi64_RRRRR

/* The 1-4 general-purpose wrappers can all use the same implementation */
#define libd_msabi64_R   libd_msabi64_RRRR
#define libd_msabi64_RR  libd_msabi64_RRRR
#define libd_msabi64_RRR libd_msabi64_RRRR


/* Calculate the address of the libc_* variant from data set-up by the libd_* wrapper.
 * Upon return,  the  absolute  address of  the  libc_*  function is  stored  in  %rax
 * s.a.  The `#define DFUN()' macro below, which fills in the data used by this macro! */
#define MSABI_LOAD_RETURN_ADDRESS()             \
	movslq %eax, %rax; /* Sign-extend offset */ \
	popq   %r11;       /* offset-addent */      \
	addq   %r11, %rax  /* calculate absolute address */


.section ".text.crt.dos.compat.dos.msabi64"
#define DFUN(sectionName, libd_name, libc_name, returnType, argc, ...)              \
	INTERN_FUNCTION(libd_name);                                                     \
		INTERN(libc_name);                                                          \
		/* movl $((libc_name - .) - 10), %eax */                                    \
		/* HINT: 10 == END(libd_name) - . */                                        \
		.byte  0xb8;                                                                \
		.reloc ., R_X86_64_PC32, libc_name - 9; /* 10-1=9, where 1=sizeof(.byte) */ \
		.int   0;                                                                   \
		INTERN(MSABI64_CONVERTER_FOR(argc, __VA_ARGS__));                           \
		call   MSABI64_CONVERTER_FOR(argc, __VA_ARGS__);                            \
	END(libd_name);

/* Since wrappers don't really need any CFI instrumentation,
 * we simply wrap all of them in one gigantic CFI procedure. */
.cfi_startproc
#ifndef __INTELLISENSE__
#include "../../dosabi-functions.h"
#endif /* !__INTELLISENSE__ */
.cfi_endproc

.section ".text.crt.compat.dos.msabi64.msabi64_RRRR"
INTERN_FUNCTION(libd_msabi64_RRRR)
	.cfi_startproc
	MSABI_LOAD_RETURN_ADDRESS()
	MSABI_SAVEZONE_PUSH()
	/* The simple cases: All arguments reside in registers. */

	/* Transform the argument list:
	 *   %rcx  -->  %rdi
	 *   %rdx  -->  %rsi
	 *   %r8   -->  %rdx
	 *   %r9   -->  %rcx */
	movq   %rcx, %rdi
	movq   %rdx, %rsi
	movq   %r8,  %rdx
	movq   %r9,  %rcx

	callq  *%rax /* Call the libc_* variant */

	MSABI_SAVEZONE_POP()
	ret
	.cfi_endproc
END(libd_msabi64_RRRR)


.section ".text.crt.compat.dos.msabi64.msabi64_RRRRR"
INTERN_FUNCTION(libd_msabi64_RRRRR)
	.cfi_startproc
	MSABI_LOAD_RETURN_ADDRESS()
	MSABI_SAVEZONE_PUSH()

	/* Transform the argument list:
	 *   %rcx                                                   --> %rdi
	 *   %rdx                                                   --> %rsi
	 *   %r8                                                    --> %rdx
	 *   %r9                                                    --> %rcx
	 *   MSABI_SAVEZONE_SIZE + MSABI_SHADOWSPACE_SIZE + 8(%rsp) --> %r8 */
	movq   %rcx,     %rdi
	movq   %rdx,     %rsi
	movq   %r8,      %rdx
	movq   %r9,      %rcx
	movq   (MSABI_SAVEZONE_SIZE + MSABI_SHADOWSPACE_SIZE + 8)(%rsp), %r8

	callq  *%rax /* Call the libc_* variant */

	MSABI_SAVEZONE_POP()
	ret
	.cfi_endproc
END(libd_msabi64_RRRRR)


.section ".text.crt.compat.dos.msabi64.msabi64_RRRRRRn"
.cfi_startproc
/* If necessary, add wrappers for more arguments here! */
INTERN_FUNCTION(libd_msabi64_RRRRRRRRRRRR)
	movzlq $(6), %r10
	INTERN(libd_msabi64_RRRRRRn)
	jmp    libd_msabi64_RRRRRRn
END(libd_msabi64_RRRRRRRRRRRR)

INTERN_FUNCTION(libd_msabi64_RRRRRRRRRR)
	movzlq $(4), %r10
	INTERN(libd_msabi64_RRRRRRn)
	jmp    libd_msabi64_RRRRRRn
END(libd_msabi64_RRRRRRRRRR)

INTERN_FUNCTION(libd_msabi64_RRRRRRRRR)
	movzlq $(3), %r10
	INTERN(libd_msabi64_RRRRRRn)
	jmp    libd_msabi64_RRRRRRn
END(libd_msabi64_RRRRRRRRR)

INTERN_FUNCTION(libd_msabi64_RRRRRRRR)
	movzlq $(2), %r10
	INTERN(libd_msabi64_RRRRRRn)
	jmp    libd_msabi64_RRRRRRn
END(libd_msabi64_RRRRRRRR)

INTERN_FUNCTION(libd_msabi64_RRRRRRR)
	movzlq $(1), %r10
	INTERN(libd_msabi64_RRRRRRn)
	jmp    libd_msabi64_RRRRRRn
END(libd_msabi64_RRRRRRR)

INTERN_FUNCTION(libd_msabi64_RRRRRR)
	movzlq $(0), %r10
/*	INTERN(libd_msabi64_RRRRRRn) */
/*	jmp    libd_msabi64_RRRRRRn */
	/* FALLTHRU */
END(libd_msabi64_RRRRRR)

INTERN_FUNCTION(libd_msabi64_RRRRRRn)
	/* Special argument:
	 * >> size_t num_sysv_stack_arguments = %r10;
	 */
	MSABI_LOAD_RETURN_ADDRESS()
	MSABI_SAVEZONE_PUSH()
	pushq_cfi_r %rbp
	movq   %rsp, %rbp
	.cfi_register %rsp, %rbp
	.cfi_def_cfa_register %rbp

	/* Transform the argument list:
	 *   %rcx                                                      --> %rdi
	 *   %rdx                                                      --> %rsi
	 *   %r8                                                       --> %rdx
	 *   %r9                                                       --> %rcx
	 *   (MSABI_SAVEZONE_SIZE + MSABI_SHADOWSPACE_SIZE + 16)(%rbp) --> %r8
	 *   (MSABI_SAVEZONE_SIZE + MSABI_SHADOWSPACE_SIZE + 24)(%rbp) --> %r9
	 * for (i: [:%r10].reversed()) {
	 *   pushq (MSABI_SAVEZONE_SIZE + MSABI_SHADOWSPACE_SIZE + 32 + i * 8)(%rbp)
	 * }
	 */
	movq   %rcx, %rdi /* arg1 */

	/* Ensure that the stack stays aligned to 16-bit within libc_*
	 * >> if ((%r10 % 2) == 0) {
	 * >>     pushq <ignored>
	 * >> } */
	testb  $(1), %r10b
	jz     2f
	pushq  %rax /* Doesn't matter what we push here. - Only used for alignment! */
2:

	movq   %r10, %rcx /* arg7-argN */
	testq  %rcx, %rcx
	jz     2f
1:	pushq  (MSABI_SAVEZONE_SIZE + MSABI_SHADOWSPACE_SIZE + 32 - 8)(%rbp, %rcx, 8)
	loop   1b
2:

	movq   %rdx, %rsi                                                     /* arg2 */
	movq   %r8,  %rdx                                                     /* arg3 */
	movq   %r9,  %rcx                                                     /* arg4 */
	movq   (MSABI_SAVEZONE_SIZE + MSABI_SHADOWSPACE_SIZE + 16)(%rbp), %r8 /* arg5 */
	movq   (MSABI_SAVEZONE_SIZE + MSABI_SHADOWSPACE_SIZE + 24)(%rbp), %r9 /* arg6 */

	callq  *%rax /* Call the libc_* variant */

	movq   %rbp, %rsp
	.cfi_same_value %rsp
	.cfi_def_cfa_register %rsp
	popq_cfi_r  %rbp
	MSABI_SAVEZONE_POP()
	ret
END(libd_msabi64_RRRRRRn)
.cfi_endproc




#ifndef __INTELLISENSE__
#include "../../dosabi-exports.h"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_MSABI64_S */
