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
#ifdef __INTELLISENSE__
#define __ASSEMBLER__ 1
#include <hybrid/host.h>
#ifdef __x86_64__
#include "string64-template.S"
#else /* __x86_64__ */
#include "string32-template.S"
#endif /* !__x86_64__ */
#endif /* __INTELLISENSE__ */

#include <asm/instr/compat.h>

#ifndef BEGIN_MEMFUNC
#define BEGIN_MEMFUNC(name)           \
	.section .text.crt.string.memory; \
	INTERN_FUNCTION(F(libc_##name));  \
		.cfi_startproc
#define END_MEMFUNC(name) \
		.cfi_endproc;     \
	END(F(libc_##name));  \
	DEFINE_PUBLIC_ALIAS(F(name), F(libc_##name))
#endif /* !BEGIN_MEMFUNC */

#ifndef RET
#define RET(n) ret
#endif /* !RET */

/* Subtract N from a pointer-sized operand */
#undef subNP
#if N == 1
#define subNP  decP
#else /* N == 1 */
#define subNP  subP $(N),
#endif /* N != 1 */




/* Enter/leave a function taking N arguments that should
 * be loaded into the named registers
 * NOTE: Pxx is a pointer-sized register (e.g. i386: %eax, x86_64: %rax)
 * NOTE: Nxx is a N-sized register (s.a. #define N)
 */
#ifndef ENTER_Pdi_Psi_Pcx
#ifdef __x86_64__
#define ENTER_Pdi_Psi_Pcx movq %rdx, %rcx
#define LEAVE_Pdi_Psi_Pcx /* nothing */
#define ENTER_Pdi_Pcx     movq %rsi, %rcx
#define LEAVE_Pdi_Pcx     /* nothing */
#else /* __x86_64__ */
#define ENTER_Pdi_Psi_Pcx  \
	pushl_cfi_r %edi;      \
	pushl_cfi_r %esi;      \
	movl   12(%esp), %edi; \
	movl   16(%esp), %esi; \
	movl   20(%esp), %ecx
#define LEAVE_Pdi_Psi_Pcx \
	popl_cfi_r %esi;      \
	popl_cfi_r %edi
#define ENTER_Pdi_Pcx     \
	pushl_cfi_r %edi;     \
	movl   8(%esp), %edi; \
	movl   12(%esp), %ecx
#define LEAVE_Pdi_Pcx \
	popl_cfi_r %edi
#endif /* !__x86_64__ */
#endif /* !ENTER_Pdi_Psi_Pcx */

#undef ENTER_Pdi_Nax
#undef LEAVE_Pdi_Nax
#undef ENTER_Psi_Nax
#undef LEAVE_Psi_Nax
#undef ENTER_Pdi_Nax_Pcx
#undef LEAVE_Pdi_Nax_Pcx
#undef ENTER_Psi_Nax_Pcx
#undef LEAVE_Psi_Nax_Pcx
#ifdef __x86_64__
#if N == 1
#define ENTER_Pdi_Nax movb %sil, %al
#elif N == 2
#define ENTER_Pdi_Nax movw %si, %ax
#elif N == 4
#define ENTER_Pdi_Nax movl %esi, %eax
#else
#define ENTER_Pdi_Nax movq %rsi, %rax
#endif
#define ENTER_Pdi_Nax_Pcx movq %rdx, %rcx; ENTER_Pdi_Nax
#define LEAVE_Pdi_Nax     /* nothing */
#define LEAVE_Pdi_Nax_Pcx /* nothing */
#define ENTER_Psi_Nax     ENTER_Pdi_Nax;     movq %rdi, %rsi
#define ENTER_Psi_Nax_Pcx ENTER_Pdi_Nax_Pcx; movq %rdi, %rsi
#define LEAVE_Psi_Nax     /* nothing */
#define LEAVE_Psi_Nax_Pcx /* nothing */
#else /* __x86_64__ */
#undef _ENTER_Pxi_Nax
#if N == 1
#define _ENTER_Pxi_Nax(x) \
	pushl_cfi_r x;        \
	movl   8(%esp), x;    \
	movb   12(%esp), %al
#elif N == 2
#define _ENTER_Pxi_Nax(x) \
	pushl_cfi_r x;        \
	movl   8(%esp), x;    \
	movw   12(%esp), %ax
#else /* N == ... */
#define _ENTER_Pxi_Nax(x) \
	pushl_cfi_r x;        \
	movl   8(%esp), x;    \
	movl   12(%esp), %eax
#endif /* N != ... */
#undef _ENTER_Pxi_Nax_Pcx
#define _ENTER_Pxi_Nax_Pcx(x) \
	_ENTER_Pxi_Nax(x);        \
	movl   16(%esp), %ecx
#define ENTER_Pdi_Nax     _ENTER_Pxi_Nax(%edi)
#define ENTER_Psi_Nax     _ENTER_Pxi_Nax(%esi)
#define LEAVE_Pdi_Nax     popl_cfi_r %edi
#define LEAVE_Psi_Nax     popl_cfi_r %esi
#define ENTER_Pdi_Nax_Pcx _ENTER_Pxi_Nax_Pcx(%edi)
#define ENTER_Psi_Nax_Pcx _ENTER_Pxi_Nax_Pcx(%esi)
#define LEAVE_Pdi_Nax_Pcx popl_cfi_r %edi
#define LEAVE_Psi_Nax_Pcx popl_cfi_r %esi
#endif /* !__x86_64__ */

/* The location of the original num_Twords argument after the
 * caller  made  use of  `ENTER_Pdi_Nax_Pcx'  and `BEGIN_CLD' */
#ifdef __x86_64__
#define RM_numTwords_after_ENTER_Pdi_Nax_Pcx__BEGIN_CLD %rdx
#else /* __x86_64__ */
#define RM_numTwords_after_ENTER_Pdi_Nax_Pcx__BEGIN_CLD 16(%esp)
#endif /* !__x86_64__ */




#ifndef REQUIRE_ZF0_if_Pcxz
/* Require that `(%Pcx = 0) ==> (PFLAGS.ZF = 0)', in  that
 * a zero-value in %Pcx requires that the ZF flag _NOT_ be
 * set.
 * This  is  a  pre-requirement for  `repne'-style  loops where
 * an empty haystack (%Pcx =  0) should lead to the  assumption
 * that a needle wasn't found (ZF=0), and since `repne' doesn't
 * modify %Pflags when %Pcx = 0, the user must ensure that  the
 * case  of an  empty haystack  is handled  _before_ making use
 * of said instruction.
 * This macro expands  to an instruction  that will ensure  that
 * the above implication holds true immediately after returning.
 *
 * Current implementation:
 *   >> cmpb   $(1), %cl
 * This will set PFLAGS.ZF = ((%Pcx & 0xff) == 1), and by filling
 * in the case for `%Pcx = 0', we get:
 *    PFLAGS.ZF = ((0 & 0xff) == 1)
 *    PFLAGS.ZF = (0 == 1)
 *    PFLAGS.ZF = 0
 * Thus fulfilling the requirement stated above. */
#define REQUIRE_ZF0_if_Pcxz cmpb $(1), %cl
#endif /* !REQUIRE_ZF0_if_Pcxz */



/********************************************************************************/
/* int LIBCCALL memcmp(void const *lhs, void const *rhs, size_t num_Tword);     */
/********************************************************************************/
BEGIN_MEMFUNC(memcmp)
	ENTER_Pdi_Psi_Pcx
	BEGIN_CLD
	/* Compare DS:PSI (rhs) with ES:PDI (lhs) */
	xorP   %Pax, %Pax  /* result = 0; // HINT: This also forces  %eflags into a  je=1 state  to
	                    *             //       handle %Pcx==0 (where cmps won't update %eflags) */
	repe   I(cmps)     /* Do the actual compare */
	/* jb -> return 1;  */
	/* ja -> return -1; */
	/* je -> return 0;  */
	setb   %al         /* result = (result & 0xffffffffffffff00) | ((rhs < lhs) ? 1 : 0); */
	movP   $(-1), %Pcx
	cmovaP %Pcx, %Pax  /* if (rhs > lhs) result = -1; */
	END_CLD
	LEAVE_Pdi_Psi_Pcx
	RET(12)
END_MEMFUNC(memcmp)




/********************************************************************************/
/* Tsigned LIBCCALL bcmp(void const *lhs, void const *rhs, size_t num_Tword);   */
/********************************************************************************/
BEGIN_MEMFUNC(bcmp)
	ENTER_Pdi_Psi_Pcx
	BEGIN_CLD
	/* Compare DS:PSI (rhs) with ES:PDI (lhs) */
	xorP   %Pax, %Pax  /* result = 0; // HINT: This also forces  %eflags into a  je=1 state  to
	                    *             //       handle %Pcx==0 (where cmps won't update %eflags) */
	repe   I(cmps)     /* Do the actual compare */
	/* jne -> return 1; */
	/* je  -> return 0; */
	setne  %al         /* result = (result & 0xffffffffffffff00) | ((rhs != lhs) ? 1 : 0); */
	END_CLD
	LEAVE_Pdi_Psi_Pcx
	RET(12)
END_MEMFUNC(bcmp)




/********************************************************************************/
/* void *LIBCCALL rawmemchr(void const *haystack, T needle);                    */
/********************************************************************************/
BEGIN_MEMFUNC(rawmemchr)
	ENTER_Pdi_Nax
	BEGIN_CLD             /* Search forward */
	movP   $(-1), %Pcx    /* Infinite haystack size */
	repne  I(scas)        /* Find the first match */
	/* At this point, %Pdi points N bytes past the matching word */
	leaP   -N(%Pdi), %Pax /* Return the pointer _to_ the matching element */
	END_CLD
	LEAVE_Pdi_Nax
	RET(8)
END_MEMFUNC(rawmemchr)
#if N == 1 && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(__rawmemchr, libc_rawmemchr)
#endif /* N == 1 && !__KERNEL__ */




/********************************************************************************/
/* void *LIBCCALL rawmemrchr(void const *haystack, T needle);                   */
/********************************************************************************/
BEGIN_MEMFUNC(rawmemrchr)
	ENTER_Pdi_Nax
	BEGIN_STD             /* Search in reverse */
	movP   $(-1), %Pcx    /* Infinite haystack size */
	subNP  %Pdi           /* Fix-up the start-of-search loaction */
	repne  I(scas)        /* Find the first match */
	/* At this point, %Pdi points N bytes before the matching word */
	leaP   N(%Pdi), %Pax /* Return the pointer _to_ the matching element */
	END_STD
	LEAVE_Pdi_Nax
	RET(8)
END_MEMFUNC(rawmemrchr)




/********************************************************************************/
/* void *LIBCCALL memchr(void const *haystack, T needle, size_t num_Tword);     */
/********************************************************************************/
BEGIN_MEMFUNC(memchr)
	ENTER_Pdi_Nax_Pcx
	BEGIN_CLD             /* Search forward */
	xorP   %Pdx, %Pdx     /* Return value if not found */
	REQUIRE_ZF0_if_Pcxz   /* Handle empty haystacks */
	repne  I(scas)        /* Find the first match */
	leaP   -N(%Pdi), %Pax /* result = %Pdi - N; */
	cmovnzP %Pdx, %Pax    /* if (!found) result = NULL; */
	END_CLD
	LEAVE_Pdi_Nax_Pcx
	RET(12)
END_MEMFUNC(memchr)
#ifndef __KERNEL__
#if N == 2 && defined(__LIBCCALL_IS_LIBDCALL)
DEFINE_PUBLIC_ALIAS(DOS$wmemchr, libc_memchrw)
#elif N == 4
DEFINE_PUBLIC_ALIAS(wmemchr, libc_memchrl)
#endif /* N == ... */
#endif /* !__KERNEL__ */




/********************************************************************************/
/* void *LIBCCALL memrchr(void const *haystack, T needle, size_t num_Tword);    */
/********************************************************************************/
BEGIN_MEMFUNC(memrchr)
	ENTER_Pdi_Nax_Pcx
	BEGIN_STD             /* Search reverse */
	leaP   -N(%Pdi,%Pcx,N), %Pdi /* Jump ahead to the last element to compare */
	xorP   %Pdx, %Pdx     /* Return value if not found */
	REQUIRE_ZF0_if_Pcxz   /* Handle empty haystacks */
	repne  I(scas)        /* Find the first match */
	leaP   N(%Pdi), %Pax  /* result = %Pdi + N; */
	cmovnzP %Pdx, %Pax    /* if (!found) result = NULL; */
	END_STD
	LEAVE_Pdi_Nax_Pcx
	RET(12)
END_MEMFUNC(memrchr)




/********************************************************************************/
/* void *LIBCCALL memend(void const *haystack, T needle, size_t num_Tword);     */
/********************************************************************************/
BEGIN_MEMFUNC(memend)
	ENTER_Pdi_Nax_Pcx
	BEGIN_CLD             /* Search forward */
	REQUIRE_ZF0_if_Pcxz   /* Handle empty haystacks */
	repne  I(scas)        /* Find the first match */
	/* if (found) {       // found (ZF=1)
	 *     return %Pdi - N;
	 * } else {           // not-found (ZF=0)
	 *     return %Pdi;
	 * } */
	leaP   -N(%Pdi), %Pax /* result = %Pdi - N; */
	cmovnzP %Pdi, %Pax    /* if (!found) result = %Pdi; */
	END_CLD
	LEAVE_Pdi_Nax_Pcx
	RET(12)
END_MEMFUNC(memend)




/********************************************************************************/
/* void *LIBCCALL memrend(void const *haystack, T needle, size_t num_Tword);    */
/********************************************************************************/
BEGIN_MEMFUNC(memrend)
	ENTER_Pdi_Nax_Pcx
	BEGIN_STD             /* Search reverse */
	leaP   -N(%Pdi,%Pcx,N), %Pdi /* Jump ahead to the last element to compare */
	REQUIRE_ZF0_if_Pcxz   /* Handle empty haystacks */
	repne  I(scas)        /* Find the first match */
	leaP   N(%Pdi), %Pax  /* result = %Pdi + N; */
	cmovnzP %Pdi, %Pax    /* if (!found) result = %Pdi; */
	END_STD
	LEAVE_Pdi_Nax_Pcx
	RET(12)
END_MEMFUNC(memrend)




/********************************************************************************/
/* size_t LIBCCALL memlen(void const *haystack, T needle, size_t num_Tword);    */
/********************************************************************************/
BEGIN_MEMFUNC(memlen)
	ENTER_Pdi_Nax_Pcx
	BEGIN_CLD             /* Search forward */
	REQUIRE_ZF0_if_Pcxz   /* Handle empty haystacks */
	repne  I(scas)        /* Find the first match */
	/* %Pcx is the # of words not searched if a match was found.
	 * For our purposes, the value of %Pcx is undefined if no  match
	 * was found (though in reality it's `0', though we'd need it to
	 * be `-1' if we wanted  to make use of indirect  optimizations)
	 * >> return WAS_FOUND ? num_Tword - (%Pcx + 1) : num_Tword;
	 * With `WAS_FOUND = (ZF=1)'
	 *
	 * To start out with, load the value of `num_Tword' into %Pax */
	movP   RM_numTwords_after_ENTER_Pdi_Nax_Pcx__BEGIN_CLD, %Pax
	/* Now refactor the return expression above:
	 * >> return WAS_FOUND ? num_Tword - (%Pcx + 1) : num_Tword;
	 * >> return WAS_FOUND ? (num_Tword - %Pcx) - 1 : num_Tword;
	 * >> return WAS_FOUND ? (num_Tword - %Pcx) - 1 : (num_Tword + 1) - 1;
	 * >> return WAS_FOUND ? (num_Tword - %Pcx) - 1 : (num_Tword - -1) - 1;
	 * With this in mind, we now do:
	 * >> if (!WAS_FOUND)
	 * >>     %Pcx = -1;
	 * So that our return expression becomes:
	 * >> return (num_Tword - %Pcx) - 1; */
	movP   $(-1), %Pdx
	cmovnzP %Pdx, %Pcx    /* if (!WAS_FOUND) %Pcx = -1; */
	subP   %Pcx, %Pax     /* Subtract the value of %Pcx from our result */
	decP   %Pax           /* fix the off-by-one error */
	END_CLD
	LEAVE_Pdi_Nax_Pcx
	RET(12)
END_MEMFUNC(memlen)




/********************************************************************************/
/* size_t LIBCCALL memrlen(void const *haystack, T needle, size_t num_Tword);   */
/********************************************************************************/
BEGIN_MEMFUNC(memrlen)
	ENTER_Pdi_Nax_Pcx
	BEGIN_STD             /* Search reverse */
	leaP   -N(%Pdi,%Pcx,N), %Pdi /* Jump ahead to the last element to compare */
	REQUIRE_ZF0_if_Pcxz   /* Handle empty haystacks */
	repne  I(scas)        /* Find the first match */
	/* %Pcx is the # of words not searched if a match was found.
	 * For our purposes, the value of %Pcx is undefined if no  match
	 * was found (though in reality it's `0', though we'd need it to
	 * be `-1' if we wanted  to make use of indirect  optimizations)
	 * >> return WAS_FOUND ? %Pcx : (size_t)-1;
	 * With `WAS_FOUND = (ZF=1)' */
	movP   $(-1), %Pax
	cmovzP %Pcx, %Pax     /* if (WAS_FOUND) %Pax = %Pcx; */
	END_STD
	LEAVE_Pdi_Nax_Pcx
	RET(12)
END_MEMFUNC(memrlen)


/* TODO: rawmemlen[b|w|l|q]()   (scas) */
/* TODO: rawmemrlen[b|w|l|q]()  (scas) */

#ifndef __KERNEL__
/********************************************************************************/
/* void *LIBCCALL rawmemxchr(void const *haystack, T needle);                   */
/********************************************************************************/
BEGIN_MEMFUNC(rawmemxchr)
	ENTER_Pdi_Nax
	BEGIN_CLD             /* Search forward */
	movP   $(-1), %Pcx    /* Infinite haystack size */
	repe   I(scas)        /* Find the first miss-match */
	/* At this point, %Pdi points N bytes past the non-matching word */
	leaP   -N(%Pdi), %Pax /* Return the pointer _to_ the non-matching element */
	END_CLD
	LEAVE_Pdi_Nax
	RET(8)
END_MEMFUNC(rawmemxchr)




/********************************************************************************/
/* void *LIBCCALL rawmemrxchr(void const *haystack, T needle);                  */
/********************************************************************************/
BEGIN_MEMFUNC(rawmemrxchr)
	ENTER_Pdi_Nax
	BEGIN_STD             /* Search in reverse */
	movP   $(-1), %Pcx    /* Infinite haystack size */
	subNP  %Pdi           /* Fix-up the start-of-search loaction */
	repe   I(scas)        /* Find the first miss-match */
	/* At this point, %Pdi points N bytes before the non-matching word */
	leaP   N(%Pdi), %Pax /* Return the pointer _to_ the non-matching element */
	END_STD
	LEAVE_Pdi_Nax
	RET(8)
END_MEMFUNC(rawmemrxchr)




/********************************************************************************/
/* void *LIBCCALL memxchr(void const *haystack, T needle, size_t num_Tword);    */
/********************************************************************************/
BEGIN_MEMFUNC(memxchr)
	ENTER_Pdi_Nax_Pcx
	BEGIN_CLD             /* Search forward */
	xorP   %Pdx, %Pdx     /* Return value if not found (also forces ZF=1) */
	repe   I(scas)        /* Find the first miss-match */
	leaP   -N(%Pdi), %Pax /* result = %Pdi - N; */
	cmovzP %Pdx, %Pax     /* if (!found) result = NULL; */
	END_CLD
	LEAVE_Pdi_Nax_Pcx
	RET(12)
END_MEMFUNC(memxchr)




/********************************************************************************/
/* void *LIBCCALL memrxchr(void const *haystack, T needle, size_t num_Tword);   */
/********************************************************************************/
BEGIN_MEMFUNC(memrxchr)
	ENTER_Pdi_Nax_Pcx
	BEGIN_STD             /* Search reverse */
	leaP   -N(%Pdi,%Pcx,N), %Pdi /* Jump ahead to the last element to compare */
	xorP   %Pdx, %Pdx     /* Return value if not found (also forces ZF=1) */
	repe   I(scas)        /* Find the first miss-match */
	leaP   N(%Pdi), %Pax  /* result = %Pdi + N; */
	cmovzP %Pdx, %Pax     /* if (!found) result = NULL; */
	END_STD
	LEAVE_Pdi_Nax_Pcx
	RET(12)
END_MEMFUNC(memrxchr)


/* TODO: memxend[b|w|l|q]()     (scas) */
/* TODO: memrxend[b|w|l|q]()    (scas) */
/* TODO: memxlen[b|w|l|q]()     (scas) */
/* TODO: memrxlen[b|w|l|q]()    (scas) */
/* TODO: rawmemxlen[b|w|l|q]()  (scas) */
/* TODO: rawmemrxlen[b|w|l|q]() (scas) */
#endif /* !__KERNEL__ */
