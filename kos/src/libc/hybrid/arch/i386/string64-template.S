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
#define N             1
#define RETURN_PCPY   0
#define __ASSEMBLER__ 1
#endif /* __INTELLISENSE__ */
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <cfi.h>
#include <asm/instr/movzxq.h>

#include <inttypes.h>

#ifndef __DEEMON__
#ifndef N
#error "Must #define N before #including this file"
#endif /* !N */
#ifndef RETURN_PCPY
#error "Must #define RETURN_PCPY before #including this file"
#endif /* !RETURN_PCPY */
#endif /* !__DEEMON__ */

/* Being/end a code-block during which EFLAGS.DF=0 is required */
#ifdef __KERNEL__
#define BEGIN_CLD cld
#define END_CLD   /* nothing */
#else /* __KERNEL__ */
#define BEGIN_CLD /* nothing */
#define END_CLD   /* nothing */
#endif /* !__KERNEL__ */


/* Being/end a code-block during which EFLAGS.DF=1 is required */
#if !defined(__KERNEL__) || 1

/*[[[cfi{register='%rflags', mode='macro:CFI_RESTORE_EFLAGS_CLEARDF'}
	push %rflags
	and  ~$EFLAGS_DF
]]]*/
#define CFI_RESTORE_EFLAGS_CLEARDF \
	__ASM_L(	.cfi_escape 22,49,7,146,49,0,11,255,251,26)
/*[[[end]]]*/
/* Setup a custom CFI restore function to clear EFLAGS.DF during unwinding */
#define BEGIN_STD std; CFI_RESTORE_EFLAGS_CLEARDF
#else /* !__KERNEL__ */
#define BEGIN_STD std
#endif /* __KERNEL__ */
#ifdef __KERNEL__
#define END_STD   /* nothing */
#else /* __KERNEL__ */
#define END_STD   cld; .cfi_restore %eflags
#endif /* !__KERNEL__ */


#if N == 1
#define F(x)   x
#define I(x)   x##b
#elif N == 2
#define F(x)   x##w
#define I(x)   x##w
#elif N == 4
#define F(x)   x##l
#define I(x)   x##l
#elif N == 8
#define F(x)   x##q
#define I(x)   x##q
#endif



#undef TEST_DX_MASK
#undef TEST_SI_MASK
#if 1
#define TEST_DX_MASK(mask) testb $(mask), %dl
#define TEST_SI_MASK(mask) testb $(mask), %sil
#else
#define TEST_DX_MASK(mask) testq $(mask), %rdx
#define TEST_SI_MASK(mask) testq $(mask), %rsi
#endif

#if RETURN_PCPY
#define IFELSE_PCPY(if_pcpy, nif_pcpy)  if_pcpy
#define IF_PCPY(...)                    __VA_ARGS__
#define NIF_PCPY(...)                   /* nothing */
#else /* RETURN_PCPY */
#define IFELSE_PCPY(if_pcpy, nif_pcpy)  nif_pcpy
#define IF_PCPY(...)                    /* nothing */
#define NIF_PCPY(...)                   __VA_ARGS__
#endif /* !RETURN_PCPY */


#if RETURN_PCPY
#define USED_LIBC_MEMMOVEDOWN_START F(libc_x86_mempmovedown_start)
#define USED_LIBC_MEMMOVEUP_START   F(libc_x86_mempmoveup_start)
#else /* RETURN_PCPY */
#define USED_LIBC_MEMMOVEDOWN_START F(libc_x86_memmovedown_start)
#define USED_LIBC_MEMMOVEUP_START   F(libc_x86_memmoveup_start)
#endif /* !RETURN_PCPY */




/******************************************************************************************/
/* void *SYSVABI memcpy(void *restrict dst, void const *restrict src, size_t num_bytes);  */
/* void *SYSVABI mempcpy(void *restrict dst, void const *restrict src, size_t num_bytes); */
/******************************************************************************************/
.section .text.crt.string.memory
INTERN_FUNCTION(IFELSE_PCPY(F(libc_mempcpy),
                            F(libc_memcpy)))
	.cfi_startproc
	BEGIN_CLD
	NIF_PCPY(movq %rdi, %rax)
	movq   %rdx, %rcx
#if N == 1
	shrq   $(3), %rcx
	rep    movsq
	jnc    1f /* if (!(n_bytes & 4)) goto 1f; */
	movsl
1:	TEST_DX_MASK(2)
	jz     1f /* if (!(n_bytes & 2)) goto 1f; */
	movsw
1:	TEST_DX_MASK(1)
	jz     1f /* if (!(n_bytes & 1)) goto 1f; */
	movsb
1:
#elif N == 2
	shrq   $(2), %rcx
	rep    movsq
	jnc    1f /* if (!(n_words & 2)) goto 1f; */
	movsl
1:	TEST_DX_MASK(1)
	jz     1f /* if (!(n_words & 1)) goto 1f; */
	movsw
1:
#elif N == 4
	shrq   $(1), %rcx
	rep    movsq
	jnc    1f /* if (!(n_dwords & 1)) goto 1f; */
	movsl
1:
#else /* N == ... */
	rep    movsq
#endif /* N != ... */
	IF_PCPY(movq %rdi, %rax)
	END_CLD
	ret
	.cfi_endproc
END(IFELSE_PCPY(F(libc_mempcpy),
                F(libc_memcpy)))
DEFINE_PUBLIC_ALIAS(IFELSE_PCPY(F(mempcpy),
                                F(memcpy)),
                    IFELSE_PCPY(F(libc_mempcpy),
                                F(libc_memcpy)))




/**************************************************************************/
/* void *LIBCCALL memmove(void *dst, void const *src, size_t num_bytes);  */
/* void *LIBCCALL mempmove(void *dst, void const *src, size_t num_bytes); */
/**************************************************************************/
.section .text.crt.string.memory
INTERN_FUNCTION(IFELSE_PCPY(F(libc_mempmove),
                            F(libc_memmove)))
	.cfi_startproc
	movq   %rdx, %rcx /* num_WORDS */
	cmpq   %rsi, %rdi
#ifdef __OPTIMIZE_SIZE__
	jb     USED_LIBC_MEMMOVEDOWN_START /* if (dst < src) memmovedown() */
	jmp    USED_LIBC_MEMMOVEUP_START   /* if (dst >= src) memmoveup() */
#else /* __OPTIMIZE_SIZE__ */
	jb     USED_LIBC_MEMMOVEDOWN_START /* if (dst < src) memmovedown() */
	ja     USED_LIBC_MEMMOVEUP_START   /* if (dst > src) memmoveup() */
	ret    /* dst == src */
#endif /* !__OPTIMIZE_SIZE__ */
	.cfi_endproc
END(IFELSE_PCPY(F(libc_mempmove),
                F(libc_memmove)))
DEFINE_PUBLIC_ALIAS(IFELSE_PCPY(F(mempmove),
                                F(memmove)),
                    IFELSE_PCPY(F(libc_mempmove),
                                F(libc_memmove)))





#ifndef NDEBUG
#ifndef MEMMOVEDOWN_INVALID_ORDER_STRINGS_DEFINED
#define MEMMOVEDOWN_INVALID_ORDER_STRINGS_DEFINED 1
.pushsection .rodata.crt.string.memory
	.Linvalid_order_str_format: .asciz "This isn't a memmovedown() operation, but is memmoveup(): dst(%p) > src(%p) (count:%" PRIuSIZ ")"
	.Linvalid_order_str_file:   .asciz __FILE__
	.Linvalid_order_str_expr:   .asciz "dst <= src"
.popsection
#endif /* !MEMMOVEDOWN_INVALID_ORDER_STRINGS_DEFINED */

#if RETURN_PCPY
#ifndef MEMMOVEDOWN_INVALID_ORDER_FUNC_DEFINED
#define MEMMOVEDOWN_INVALID_ORDER_FUNC_DEFINED 1
.pushsection .rodata.crt.string.memory
	.Linvalid_order_str_pfunc: .asciz "mempmovedown"
.popsection
#endif /* !MEMMOVEDOWN_INVALID_ORDER_FUNC_DEFINED */
#else /* RETURN_PCPY */
#ifndef MEMMOVEDOWN_INVALID_ORDER_PFUNC_DEFINED
#define MEMMOVEDOWN_INVALID_ORDER_PFUNC_DEFINED 1
.pushsection .rodata.crt.string.memory
	.Linvalid_order_str_func: .asciz "memmovedown"
.popsection
#endif /* !MEMMOVEDOWN_INVALID_ORDER_PFUNC_DEFINED */
#endif /* !RETURN_PCPY */
#endif /* !NDEBUG */


/******************************************************************************/
/* void *LIBCCALL memmovedown(void *dst, void const *src, size_t num_bytes);  */
/* void *LIBCCALL mempmovedown(void *dst, void const *src, size_t num_bytes); */
/******************************************************************************/
.section .text.crt.string.memory
INTERN_FUNCTION(IFELSE_PCPY(F(libc_mempmovedown),
                            F(libc_memmovedown)))
	.cfi_startproc
	BEGIN_CLD
	movq   %rdx, %rcx /* num_WORDS */

	/* assert(dst <= src || !n_bytes); */
#ifndef NDEBUG
	.cfi_remember_state
	cmpq   %rsi, %rdi
	jbe    1f         /* if (dst <= src) goto 1f; */
	testq  %rcx, %rcx
	jz     1f         /* if (!n_bytes) goto 1f; */
	/* Invalid use of `memmovedown' */
#ifdef __CRT_HAVE___acheckf
	pushq_cfi %rdi
#endif /* __CRT_HAVE___acheckf */
	pushq_cfi %rcx                          /* format:`...count:%Iu' */
	pushq_cfi %rsi                          /* format:`...src(%p)...' */
	movq   %rdi, %r9                        /* format:`...dst(%p)...' */
	leaq   .Linvalid_order_str_format(%rip), %r8 /* format */
	leaq   IFELSE_PCPY(.Linvalid_order_str_pfunc,
	                   .Linvalid_order_str_func)(%rip), %rcx /* func */
	movq   $(__LINE__), %rdx                    /* line */
	leaq   .Linvalid_order_str_file(%rip), %rsi /* file */
	leaq   .Linvalid_order_str_expr(%rip), %rdi /* expr */
#undef PUSH_RELSTR
#ifdef __CRT_HAVE___acheckf
	INTERN(libc___acheckf)
	call   libc___acheckf
	popq_cfi %rsi
	popq_cfi %rcx
	popq_cfi %rdi
	INTERN(IFELSE_PCPY(F(libc_mempmoveup), F(libc_memmoveup)))
	jmp    IFELSE_PCPY(F(libc_mempmoveup), F(libc_memmoveup))
#else /* __CRT_HAVE___acheckf */
	INTERN(libc___afailf)
	call   libc___afailf
#endif /* !__CRT_HAVE___acheckf */
1:	.cfi_restore_state
#endif /* !NDEBUG */

PRIVATE_LABEL(IFELSE_PCPY(F(libc_x86_mempmovedown_start),
                          F(libc_x86_memmovedown_start))):
	BEGIN_CLD
	NIF_PCPY(movq %rdi, %rax)
	rep    I(movs)   /* Actually copy memory */
	IF_PCPY(movq %rdi, %rax)
	END_CLD
	ret
	.cfi_endproc
END(IFELSE_PCPY(F(libc_mempmovedown),
                F(libc_memmovedown)))
DEFINE_PUBLIC_ALIAS(IFELSE_PCPY(F(mempmovedown),
                                F(memmovedown)),
                    IFELSE_PCPY(F(libc_mempmovedown),
                                F(libc_memmovedown)))






#ifndef NDEBUG
#ifndef MEMMOVEUP_INVALID_ORDER_STRINGS_DEFINED
#define MEMMOVEUP_INVALID_ORDER_STRINGS_DEFINED 1
	.pushsection .rodata.crt.string.memory
.Linvalid_orderup_str_format: .asciz "This isn't a memmoveup() operation, but is memmovedown(): dst(%p) < src(%p) (count:%" PRIuSIZ ")"
.Linvalid_orderup_str_expr:   .asciz "dst >= src"
	.popsection
#endif /* !MEMMOVEUP_INVALID_ORDER_STRINGS_DEFINED */

#if RETURN_PCPY
#ifndef MEMMOVEUP_INVALID_ORDER_FUNC_DEFINED
#define MEMMOVEUP_INVALID_ORDER_FUNC_DEFINED 1
	.pushsection .rodata.crt.string.memory
.Linvalid_orderup_str_pfunc:  .asciz "mempmoveup"
	.popsection
#endif /* !MEMMOVEUP_INVALID_ORDER_FUNC_DEFINED */
#else /* RETURN_PCPY */
#ifndef MEMMOVEUP_INVALID_ORDER_PFUNC_DEFINED
#define MEMMOVEUP_INVALID_ORDER_PFUNC_DEFINED 1
	.pushsection .rodata.crt.string.memory
.Linvalid_orderup_str_func:   .asciz "memmoveup"
	.popsection
#endif /* !MEMMOVEUP_INVALID_ORDER_PFUNC_DEFINED */
#endif /* !RETURN_PCPY */
#endif /* !NDEBUG */


/****************************************************************************/
/* void *LIBCCALL memmoveup(void *dst, void const *src, size_t num_bytes);  */
/* void *LIBCCALL mempmoveup(void *dst, void const *src, size_t num_bytes); */
/****************************************************************************/
.section .text.crt.string.memory
INTERN_FUNCTION(IFELSE_PCPY(F(libc_mempmoveup),
                            F(libc_memmoveup)))
	.cfi_startproc
	movq   %rdx, %rcx /* n_bytes */

	/* assert(dst >= src || !n_bytes); */
#ifndef NDEBUG
	.cfi_remember_state
	cmpq   %rsi, %rdi
	jae    1f         /* if (dst >= src) goto 1f; */
	testq  %rcx, %rcx
	jz     1f         /* if (!n_bytes) goto 1f; */
	/* Invalid use of `memmoveup' */
#ifdef __CRT_HAVE___acheckf
	pushq_cfi %rdi
#endif /* __CRT_HAVE___acheckf */
	pushq_cfi %rcx                          /* format:`...count:%Iu' */
	pushq_cfi %rsi                          /* format:`...src(%p)...' */
	movq   %rdi, %r9                        /* format:`...dst(%p)...' */
	leaq   .Linvalid_orderup_str_format(%rip), %r8 /* format */
	leaq   IFELSE_PCPY(.Linvalid_orderup_str_pfunc,
	                   .Linvalid_orderup_str_func)(%rip), %rcx /* func */
	movq   $(__LINE__), %rdx                    /* line */
	leaq   .Linvalid_order_str_file(%rip), %rsi /* file */
	leaq   .Linvalid_orderup_str_expr(%rip), %rdi /* expr */
#undef PUSH_RELSTR
#ifdef __CRT_HAVE___acheckf
	INTERN(libc___acheckf)
	call   libc___acheckf
	popq_cfi %rsi
	popq_cfi %rcx
	popq_cfi %rdi
	INTERN(IFELSE_PCPY(F(libc_mempmovedown), F(libc_memmovedown)))
	jmp    IFELSE_PCPY(F(libc_mempmovedown), F(libc_memmovedown))
#else /* __CRT_HAVE___acheckf */
	INTERN(libc___afailf)
	call   libc___afailf
#endif /* !__CRT_HAVE___acheckf */
1:	.cfi_restore_state
#endif /* !NDEBUG */

PRIVATE_LABEL(IFELSE_PCPY(F(libc_x86_mempmoveup_start),
                          F(libc_x86_memmoveup_start))):
	/* Make  sure that the  direction bit is set,
	 * thus causing `movs' to do a top->down copy */
	BEGIN_STD
	NIF_PCPY(movq %rdi, %rax)
	/* Jump ahead to the last address */
	leaq   -N(%rdi, %rcx, N), %rdi
	leaq   -N(%rsi, %rcx, N), %rsi
	IF_PCPY(leaq N(%rdi), %rax)
	rep    I(movs) /* Actually perform the memory copy */
	END_STD        /* Restore the direction flag */
	ret
	.cfi_endproc
END(IFELSE_PCPY(F(libc_mempmoveup),
                F(libc_memmoveup)))
DEFINE_PUBLIC_ALIAS(IFELSE_PCPY(F(mempmoveup),
                                F(memmoveup)),
                    IFELSE_PCPY(F(libc_mempmoveup),
                                F(libc_memmoveup)))
#undef USED_LIBC_MEMMOVEDOWN_START
#undef USED_LIBC_MEMMOVEUP_START





/*************************************************************************/
/* void *SYSVABI memset(void *restrict dst, T Tword, size_t num_Tword);  */
/* void *SYSVABI mempset(void *restrict dst, T Tword, size_t num_Tword); */
/*************************************************************************/
.section .text.crt.string.memory
INTERN_FUNCTION(IFELSE_PCPY(F(libc_mempset),
                            F(libc_memset)))
	.cfi_startproc
	BEGIN_CLD
#if N == 8
	movq   %rsi, %rax
	movq   %rdx, %rcx
	NIF_PCPY(movq %rdi, %rdx)
	rep    stosq
	movq   IFELSE_PCPY(%rdi, %rdx), %rax
#elif N == 4
	movzlq %esi, %rax /* RAX = ESI & 0xffffffff */
	shlq   $(32),  %rsi
	orq    %rsi, %rax /* RAX = ESI | ESI << 32 */
	movq   %rdx, %rcx
	NIF_PCPY(movq %rdi, %rdx)
	shrq   $(1), %rcx
	rep    stosq
	jnc    1f /* if (!(n_dwords & 1)) goto 1f; */
	stosl
1:	movq   IFELSE_PCPY(%rdi, %rdx), %rax
#elif N == 2
	movw   %si, %ax
	shll   $(16), %eax
	movw   %si, %ax   /* EAX = WORD << 16 | WORD */
	movzlq %eax, %rsi
	shlq   $(32), %rax
	orq    %rsi, %rax /* EAX = WORD << 48 | WORD << 32 | WORD << 16 | WORD */
	NIF_PCPY(movq %rdi, %r8)
	movq   %rdx, %rcx
	shrq   $(2), %rcx
	rep    stosq
	jnc    1f /* if (!(n_words & 2)) goto 1f; */
	stosl
1:	TEST_DX_MASK(1)
	jz     1f /* if (!(n_words & 1)) goto 1f; */
	stosw
1:	movq   IFELSE_PCPY(%rdi, %r8), %rax
#else /* N == ... */
	movb   %sil, %al
	movb   %al, %ah
	movw   %ax, %si
	shll   $(16), %eax
	movw   %si, %ax
	movzlq %eax, %rsi
	shlq   $(32), %rax
	orq    %rsi, %rax
	NIF_PCPY(movq %rdi, %r8)
	movq   %rdx, %rcx
	shrq   $(3), %rcx
	rep    stosq
	jnc    1f /* if (!(n_bytes & 4)) goto 1f; */
	stosl
1:	TEST_DX_MASK(2)
	jz     1f /* if (!(n_bytes & 2)) goto 1f; */
	stosw
1:	TEST_DX_MASK(1)
	jz     1f /* if (!(n_bytes & 1)) goto 1f; */
	stosb
1:	movq   IFELSE_PCPY(%rdi, %r8), %rax
#endif /* N != ... */
	END_CLD
	ret
	.cfi_endproc
END(IFELSE_PCPY(F(libc_mempset),
                F(libc_memset)))
DEFINE_PUBLIC_ALIAS(IFELSE_PCPY(F(mempset),
                                F(memset)),
                    IFELSE_PCPY(F(libc_mempset),
                                F(libc_memset)))





#if !RETURN_PCPY
/******************************************************************************************/
/* void SYSVABI bzero(void *restrict dst, size_t num_words);                              */
/******************************************************************************************/
.section .text.crt.string.memory
INTERN_FUNCTION(F(libc_bzero))
	.cfi_startproc
	BEGIN_CLD
	movq   %rsi, %rcx /* num_words */
	xorq   %rax, %rax /* Filler word */
#if N == 1
	shrq   $(3), %rcx
	rep    stosq
	jnc    1f /* if (!(n_bytes & 4)) goto 1f; */
	stosl
1:	TEST_SI_MASK(2)
	jz     1f /* if (!(n_bytes & 2)) goto 1f; */
	stosw
1:	TEST_SI_MASK(1)
	jz     1f /* if (!(n_bytes & 1)) goto 1f; */
	stosb
1:
#elif N == 2
	shrq   $(2), %rcx
	rep    stosq
	jnc    1f /* if (!(n_words & 2)) goto 1f; */
	stosl
1:	TEST_SI_MASK(1)
	jz     1f /* if (!(n_words & 1)) goto 1f; */
	stosw
1:
#elif N == 4
	shrq   $(1), %rcx
	rep    stosq
	jnc    1f /* if (!(n_dwords & 1)) goto 1f; */
	stosl
1:
#else /* N == ... */
	rep    stosq
#endif /* N != ... */
	END_CLD
	ret
	.cfi_endproc
END(F(libc_bzero))
DEFINE_PUBLIC_ALIAS(F(bzero), F(libc_bzero))


#ifndef __INTELLISENSE__
#include "string-template.S"
#endif /* !__INTELLISENSE__ */



#if N == 1
#define STRING_SECTION         .text.crt.string.memory
#define F_STRING(name)         libc_str##name
#define F_STRING_EXPORT(name)       str##name
#elif !defined(__KERNEL__)
/* Don't define these within the kernel */
#if N == 2
#define STRING_SECTION         .text.crt.dos.wchar.unicode.static.memory
#define F_STRING(name)         libd_wcs##name
#define F_STRING_EXPORT(name)   DOS$wcs##name
#elif N == 4
#define STRING_SECTION         .text.crt.wchar.unicode.static.memory
#define F_STRING(name)         libc_wcs##name
#define F_STRING_EXPORT(name)       wcs##name
#endif /* N... */
#endif /* N... */


#ifdef F_STRING

/*******************************************/
/* char *LIBCCALL strend(char const *str); */
/*******************************************/
.section STRING_SECTION
INTERN_FUNCTION(F_STRING(end))
	.cfi_startproc
	BEGIN_CLD
#if N == 2
	/* MSABI: char const *string = %rcx; */
	pushq_cfi_r %rdi
	movq   %rcx, %rdi
#endif /* N == 2 */
	movq   $-1, %rcx
	xorl   %eax, %eax
	repne  I(scas)
	leaq   -N(%rdi), %rax
#if N == 2
	popq_cfi_r %rdi
#endif /* N == 2 */
	END_CLD
	ret
	.cfi_endproc
END(F_STRING(end))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(end), F_STRING(end))

/********************************************/
/* size_t LIBCCALL strlen(char const *str); */
/********************************************/
.section STRING_SECTION
INTERN_FUNCTION(F_STRING(len))
	.cfi_startproc
	BEGIN_CLD
#if N == 2
	/* MSABI: char const *string = %rcx; */
	pushq_cfi_r %rdi
	movq   %rcx, %rdi
#endif /* N == 2 */
	movq   $-1, %rcx
	xorl   %eax, %eax
	repne  I(scas)
	subq   %rcx, %rax /* result = 0 - RCX; */
	subq   $(2), %rax /* result = (0 - RCX) - 2; */
#if N == 2
	popq_cfi_r %rdi
#endif /* N == 2 */
	END_CLD
	ret
	.cfi_endproc
END(F_STRING(len))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(len), F_STRING(len))

/************************************************************/
/* size_t LIBCCALL strnlen(char const *str, size_t maxlen); */
/************************************************************/
.section STRING_SECTION
INTERN_FUNCTION(F_STRING(nlen))
	.cfi_startproc
	BEGIN_CLD
#if N == 2
	/* MSABI: char const *string = %rcx;
	 *        size_t      maxlen = %rdx; */
	pushq_cfi_r %rdi
	movq   %rcx, %rdi
	xorq   %rax, %rax
	testq  %rdx, %rdx
	jz     2f
	movq   %rdx, %rcx
	repne  I(scas)
	jne    1f
	incq   %rcx
1:	subq   %rcx, %rdx
	movq   %rdx, %rax /* result = max_chars - RCX; */
#else /* N == 2 */
	xorq   %rax, %rax
	testq  %rsi, %rsi
	jz     2f
	movq   %rsi, %rcx
	repne  I(scas)
	jne    1f
	incq   %rcx
1:	subq   %rcx, %rsi
	movq   %rsi, %rax /* result = max_chars - RCX; */
#endif /* N != 2 */
2:	END_CLD
	ret
	.cfi_endproc
END(F_STRING(nlen))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(nlen), F_STRING(nlen))
#ifndef __KERNEL__
#if N == 1
DEFINE_PUBLIC_ALIAS(__strncnt, F_STRING(nlen))     /* DOS-specific name */
#elif N == 2
DEFINE_PUBLIC_ALIAS(DOS$__wcsncnt, F_STRING(nlen)) /* DOS-specific name */
#endif /* N == ... */
#endif /* !__KERNEL__ */


/***********************************************************/
/* char *LIBCCALL strnend(char const *str, size_t maxlen); */
/***********************************************************/
.section STRING_SECTION
INTERN_FUNCTION(F_STRING(nend))
	.cfi_startproc
	BEGIN_CLD
#if N == 2
	/* MSABI: char const *string = %rcx;
	 *        size_t      maxlen = %rdx; */
	pushq_cfi_r %rdi
	xorq   %rax, %rax
	testq  %rdx, %rdx
	movq   %rcx, %rdi
	jz     1f
	movq   %rdx, %rcx
	repne  I(scas)
	jne    1f
	subq   $(2), %rdi
1:	movq   %rdi, %rax
	popq_cfi_r %rdi
	END_CLD
	ret
#else /* N == 2 */
	xorq   %rax, %rax
	testq  %rsi, %rsi
	jz     1f
	movq   %rsi, %rcx
	repne  I(scas)
	jne    1f
#if N == 1
	decq   %rdi
#else /* N == 1 */
	subq   $(N), %rdi
#endif /* N != 1 */
1:	movq   %rdi, %rax
	END_CLD
	ret
#endif /* N != 2 */
	.cfi_endproc
END(F_STRING(nend))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(nend), F_STRING(nend))

#endif /* F_STRING */


#undef F_STRING
#undef F_STRING_EXPORT
#undef STRING_SECTION

#endif /* !RETURN_PCPY */

#ifndef __INTELLISENSE__
#undef IF_PCPY
#undef NIF_PCPY
#undef IFELSE_PCPY
#undef RETURN_PCPY
#undef N
#undef I
#undef F
#undef BEGIN_CLD
#undef END_CLD
#undef BEGIN_STD
#undef END_STD
#endif /* !__INTELLISENSE__ */
