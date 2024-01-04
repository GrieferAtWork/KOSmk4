/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#define N           1
#define RETURN_PCPY 0
#define __ASSEMBLER__ 1
#endif /* __INTELLISENSE__ */
#define _KOS_SOURCE 1

#include <__crt.h>
#include <hybrid/compiler.h>

#include <cfi.h>

#include <inttypes.h>


#ifndef __DEEMON__
#ifndef N
#error "Must #define N before #including this file"
#endif /* !N */
#ifndef RETURN_PCPY
#error "Must #define RETURN_PCPY before #including this file"
#endif /* !RETURN_PCPY */
#endif /* !__DEEMON__ */

#ifdef __KERNEL__
#define RET(n)     ret $n
#else /* __KERNEL__ */
#define RET(n)     ret
#endif /* !__KERNEL__ */

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

/*[[[cfi{register='%eflags', mode='macro:CFI_RESTORE_EFLAGS_CLEARDF'}
	push   %eflags
	and    ~$EFLAGS_DF
]]]*/
#define CFI_RESTORE_EFLAGS_CLEARDF \
	__ASM_L(	.cfi_escape 22,9,6,121,0,11,255,251,26)
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
#endif /* N == ... */



#undef TEST_DX_MASK
#if 1
#define TEST_DX_MASK(mask) testb $mask, %dl
#else
#define TEST_DX_MASK(mask) testl $mask, %edx
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




/*******************************************************************************************/
/* void *LIBCCALL memcpy(void *restrict dst, void const *restrict src, size_t num_bytes);  */
/* void *LIBCCALL mempcpy(void *restrict dst, void const *restrict src, size_t num_bytes); */
/*******************************************************************************************/
.section .text.crt.string.memory
INTERN_FUNCTION(IFELSE_PCPY(F(libc_mempcpy),
                            F(libc_memcpy)))
	.cfi_startproc
	pushl_cfi_r %edi
	pushl_cfi_r %esi
	BEGIN_CLD
	movl   12(%esp), %edi /* dst */
	movl   16(%esp), %esi /* src */
	movl   20(%esp), %ecx /* n_bytes */
	NIF_PCPY(movl %edi, %eax)
#if N == 1
	movl   %ecx, %edx
	shrl   $(2), %ecx
	rep    movsl
	jnc    1f /* if (!(n_bytes & 2)) goto 1f; */
	movsw
1:	TEST_DX_MASK(1)
	jz     1f /* if (!(n_bytes & 1)) goto 1f; */
	movsb
1:
#elif N == 2
	shrl   $(1), %ecx
	rep    movsl
	jnc    1f /* if (!(n_words & 1)) goto 1f; */
	movsw
1:
#else /* N == ... */
	rep    movsl
#endif /* N != ... */
	IF_PCPY(movl %edi, %eax)
	END_CLD
	popl_cfi_r %esi
	popl_cfi_r %edi
	RET(12)
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
	pushl_cfi_r %edi
	pushl_cfi_r %esi
	movl   12(%esp), %edi /* dst */
	movl   16(%esp), %esi /* src */
	movl   20(%esp), %ecx /* n_bytes */
	cmpl   %esi, %edi
#ifdef __OPTIMIZE_SIZE__
	jb     USED_LIBC_MEMMOVEDOWN_START /* if (dst < src) memmovedown() */
	jmp    USED_LIBC_MEMMOVEUP_START   /* if (dst >= src) memmoveup() */
#else /* __OPTIMIZE_SIZE__ */
	jb     USED_LIBC_MEMMOVEDOWN_START /* if (dst < src) memmovedown() */
	ja     USED_LIBC_MEMMOVEUP_START   /* if (dst > src) memmoveup() */
	/* dst == src */
	popl_cfi_r %esi
	popl_cfi_r %edi
	RET(12)
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
	/* assert(dst <= src || !n_bytes); */
	pushl_cfi_r %edi
	pushl_cfi_r %esi
	BEGIN_CLD
	movl   12(%esp), %edi /* dst */
	movl   16(%esp), %esi /* src */
	movl   20(%esp), %ecx /* n_bytes */

	/* assert(dst <= src || !n_bytes); */
#ifndef NDEBUG
	.cfi_remember_state
	cmpl   %esi, %edi
	jbe    1f         /* if (dst <= src) goto 1f; */
	testl  %ecx, %ecx
	jz     1f         /* if (!n_bytes) goto 1f; */
	/* Invalid use of `memmovedown' */
	pushl_cfi %ecx                          /* format:`...count:%Iu' */
	pushl_cfi %esi                          /* format:`...src(%p)...' */
	pushl_cfi %edi                          /* format:`...dst(%p)...' */
#if defined(__PIC__) || defined(__PIE__) || defined(__pic__) || defined(__pie__)
	call   9f
	.cfi_adjust_cfa_offset 4
9:	popl_cfi %edi
	addl   $(_GLOBAL_OFFSET_TABLE_ + (. - 9b)), %edi
#define PUSH_RELSTR(x) leal x@GOTOFF(%edi), %eax; pushl_cfi %eax
#else /* __PIC__ || __PIE__ || __pic__ || __pie__ */
#define PUSH_RELSTR(x) pushl_cfi $(x)
#endif /* !__PIC__ && !__PIE__ && !__pic__ && !__pie__ */
	PUSH_RELSTR(.Linvalid_order_str_format) /* format */
	PUSH_RELSTR(IFELSE_PCPY(.Linvalid_order_str_pfunc,
	                        .Linvalid_order_str_func)) /* func */
	pushl_cfi $(__LINE__)                   /* line */
	PUSH_RELSTR(.Linvalid_order_str_file)   /* file */
	PUSH_RELSTR(.Linvalid_order_str_expr)   /* expr */
#undef PUSH_RELSTR
#ifdef __CRT_HAVE___acheckf
	INTERN(libc___acheckf)
	call   libc___acheckf
	addl   $(32), %esp
	.cfi_adjust_cfa_offset -32
	popl_cfi_r %esi
	popl_cfi_r %edi
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
	NIF_PCPY(movl %edi, %eax)
	rep    I(movs)   /* Actually copy memory */
	IF_PCPY(movl %edi, %eax)
	END_CLD
	popl_cfi_r %esi
	popl_cfi_r %edi
	RET(12)
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
	pushl_cfi_r %edi
	pushl_cfi_r %esi
	movl   12(%esp), %edi /* dst */
	movl   16(%esp), %esi /* src */
	movl   20(%esp), %ecx /* n_bytes */

	/* assert(dst >= src || !n_bytes); */
#ifndef NDEBUG
	.cfi_remember_state
	cmpl   %esi, %edi
	jae    1f         /* if (dst >= src) goto 1f; */
	testl  %ecx, %ecx
	jz     1f         /* if (!n_bytes) goto 1f; */
	/* Invalid use of `memmoveup' */
	pushl_cfi %ecx                            /* format:`...count:%Iu' */
	pushl_cfi %esi                            /* format:`...src(%p)...' */
	pushl_cfi %edi                            /* format:`...dst(%p)...' */
#if defined(__PIC__) || defined(__PIE__) || defined(__pic__) || defined(__pie__)
	call   9f
	.cfi_adjust_cfa_offset 4
9:	popl_cfi %edi
	addl   $(_GLOBAL_OFFSET_TABLE_ + (. - 9b)), %edi
#define PUSH_RELSTR(x) leal x@GOTOFF(%edi), %eax; pushl_cfi %eax
#else /* __PIC__ || __PIE__ || __pic__ || __pie__ */
#define PUSH_RELSTR(x) pushl_cfi $(x)
#endif /* !__PIC__ && !__PIE__ && !__pic__ && !__pie__ */
	PUSH_RELSTR(.Linvalid_orderup_str_format) /* format */
	PUSH_RELSTR(IFELSE_PCPY(.Linvalid_orderup_str_pfunc,
	                        .Linvalid_orderup_str_func))  /* func */
	pushl_cfi $(__LINE__)                     /* line */
	PUSH_RELSTR(.Linvalid_order_str_file)     /* file */
	PUSH_RELSTR(.Linvalid_orderup_str_expr)   /* expr */
#undef PUSH_RELSTR
#ifdef __CRT_HAVE___acheckf
	INTERN(libc___acheckf)
	call   libc___acheckf
	addl   $(32), %esp
	.cfi_adjust_cfa_offset -32
	popl_cfi_r %esi
	popl_cfi_r %edi
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
	NIF_PCPY(movl %edi, %eax)
	/* Jump ahead to the last address */
	leal   -N(%edi, %ecx, N), %edi
	leal   -N(%esi, %ecx, N), %esi
	IF_PCPY(leal N(%edi), %eax)
	rep    I(movs) /* Actually perform the memory copy */
	END_STD        /* Restore the direction flag */
	popl_cfi_r %esi
	popl_cfi_r %edi
	RET(12)
	.cfi_endproc
END(IFELSE_PCPY(F(libc_mempmoveup),
                F(libc_memmoveup)))
DEFINE_PUBLIC_ALIAS(IFELSE_PCPY(F(mempmoveup),
                                F(memmoveup)),
                    IFELSE_PCPY(F(libc_mempmoveup),
                                F(libc_memmoveup)))
#undef USED_LIBC_MEMMOVEDOWN_START
#undef USED_LIBC_MEMMOVEUP_START





/**************************************************************************/
/* void *LIBCCALL memset(void *restrict dst, T Tword, size_t num_Tword);  */
/* void *LIBCCALL mempset(void *restrict dst, T Tword, size_t num_Tword); */
/**************************************************************************/
.section .text.crt.string.memory
INTERN_FUNCTION(IFELSE_PCPY(F(libc_mempset),
                            F(libc_memset)))
	.cfi_startproc
	pushl_cfi_r %edi
	BEGIN_CLD
	movl   8(%esp), %edi /* dst */
#if N == 1
	movzbl 12(%esp), %eax /* byte */
	movb   %al, %ah
	movw   %ax, %cx
	shll   $(16), %eax
	movw   %cx, %ax
	movl   16(%esp), %ecx /* n_bytes */
	NIF_PCPY(pushl_cfi %edi)
	movl   %ecx, %edx
	shrl   $(2), %ecx
	rep    stosl
	jnc    1f /* if (!(n_bytes & 2)) goto 1f; */
	stosw
1:	TEST_DX_MASK(1)
	jz     1f /* if (!(n_bytes & 1)) goto 1f; */
	stosb
1:	NIF_PCPY(popl_cfi %eax)
	IF_PCPY(movl %edi, %eax)
#elif N == 2
	movzwl 12(%esp), %eax /* word */
	movw   %ax, %cx
	shll   $(16), %eax
	movw   %cx, %ax
	movl   16(%esp), %ecx /* n_words */
	NIF_PCPY(movl %edi, %edx)
	shrl   $(1), %ecx
	rep    stosl
	jnc    1f /* if (!(n_words & 1)) goto 1f; */
	stosw
1:	movl   IFELSE_PCPY(%edi, %edx), %eax
#else /* N == 4 */
	movl   12(%esp), %eax /* dword */
	movl   16(%esp), %ecx /* n_dwords */
	NIF_PCPY(movl   %edi, %edx)
	rep    stosl
	movl   IFELSE_PCPY(%edi, %edx), %eax
#endif /* N == ... */
	END_CLD
	popl_cfi_r %edi
	RET(12)
	.cfi_endproc
END(IFELSE_PCPY(F(libc_mempset),
                F(libc_memset)))
DEFINE_PUBLIC_ALIAS(IFELSE_PCPY(F(mempset),
                                F(memset)),
                    IFELSE_PCPY(F(libc_mempset),
                                F(libc_memset)))




#if !RETURN_PCPY

/**************************************************************************/
/* void LIBCCALL bzero(void *restrict dst, size_t num_Tword);             */
/**************************************************************************/
.section .text.crt.string.memory
INTERN_FUNCTION(F(libc_bzero))
	.cfi_startproc
	pushl_cfi_r %edi
	movl   8(%esp),  %edi /* dst */
	movl   12(%esp), %ecx /* n_bytes */
	xorl   %eax, %eax     /* Filler word */
	BEGIN_CLD
#if N == 1
	movl   %ecx, %edx
	shrl   $(2), %ecx
	rep    stosl
	jnc    1f /* if (!(n_bytes & 2)) goto 1f; */
	stosw
1:	TEST_DX_MASK(1)
	jz     1f /* if (!(n_bytes & 1)) goto 1f; */
	stosb
1:
#elif N == 2
	shrl   $(1), %ecx
	rep    stosl
	jnc    1f /* if (!(n_words & 1)) goto 1f; */
	stosw
1:
#else /* N == ... */
	rep    stosl
#endif /* N != ... */
	END_CLD
	popl_cfi_r %edi
	RET(8)
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
	pushl_cfi_r %edi
	BEGIN_CLD
	movl   8(%esp), %edi
	movl   $-1, %ecx
	xorl   %eax, %eax
	repne  I(scas)
	leal   -N(%edi), %eax
	END_CLD
	popl_cfi_r %edi
	RET(4)
	.cfi_endproc
END(F_STRING(end))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(end), F_STRING(end))

/********************************************/
/* size_t LIBCCALL strlen(char const *str); */
/********************************************/
.section STRING_SECTION
INTERN_FUNCTION(F_STRING(len))
	.cfi_startproc
	pushl_cfi_r %edi
	BEGIN_CLD
	movl   8(%esp), %edi
	movl   $-1, %ecx
	xorl   %eax, %eax
	repne  I(scas)
	subl   %ecx, %eax /* result = 0 - ECX; */
	subl   $(2), %eax /* result = (0 - ECX) - 2; */
	END_CLD
	popl_cfi_r %edi
	RET(4)
	.cfi_endproc
END(F_STRING(len))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(len), F_STRING(len))

/************************************************************/
/* size_t LIBCCALL strnlen(char const *str, size_t maxlen); */
/************************************************************/
.section STRING_SECTION
INTERN_FUNCTION(F_STRING(nlen))
	.cfi_startproc
	xorl   %eax, %eax
	movl   8(%esp), %edx
	testl  %edx, %edx
	jz     2f
	pushl_cfi_r %edi
	BEGIN_CLD
	movl   8(%esp), %edi
	movl   %edx, %ecx
	repne  I(scas)
	jne    1f
	incl   %ecx
1:	subl   %ecx, %edx
	movl   %edx, %eax /* result = max_chars - ECX; */
	END_CLD
	popl_cfi_r %edi
2:	RET(8)
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
	pushl_cfi_r %edi
	BEGIN_CLD
	xorl   %eax, %eax
	movl   8(%esp), %edi
	movl   12(%esp), %ecx
	testl  %ecx, %ecx
	jz     1f
	repne  I(scas)
	jne    1f
#if N == 1
	decl   %edi
#else /* N == 1 */
	subl   $(N), %edi
#endif /* N != 1 */
1:	movl   %edi, %eax
	END_CLD
	popl_cfi_r %edi
	RET(8)
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
#undef RET
#endif /* !__INTELLISENSE__ */
