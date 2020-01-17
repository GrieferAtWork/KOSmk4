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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#include <hybrid/compiler.h>
#include <asm/cfi.h>

#ifndef __DEEMON__
#ifndef N
#error "Must #define N before #including this file"
#endif /* !N */
#ifndef RETURN_PCPY
#error "Must #define RETURN_PCPY before #including this file"
#endif /* !RETURN_PCPY */
#endif /* !__DEEMON__ */

#ifdef __KERNEL__
#define ENTER_CLD  cld
#define RET(n)     ret $n
#else /* __KERNEL__ */
#define ENTER_CLD  /* nothing */
#define RET(n)     ret
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
#endif



#undef TEST_DX_MASK
#if 1
#define TEST_DX_MASK(mask) testb $mask, %dl
#else
#define TEST_DX_MASK(mask) testl $mask, %edx
#endif


#if RETURN_PCPY
#define USED_LIBC_MEMMOVEDOWN_START F(libc_x86_mempmovedown_start)
#define USED_LIBC_MEMMOVEUP_START   F(libc_x86_mempmoveup_start)
#else /* RETURN_PCPY */
#define USED_LIBC_MEMMOVEDOWN_START F(libc_x86_memmovedown_start)
#define USED_LIBC_MEMMOVEUP_START   F(libc_x86_memmoveup_start)
#endif /* !RETURN_PCPY */


.section .text.crt.string.memory
#if RETURN_PCPY
INTERN_FUNCTION(F(libc_mempcpy))
#else /* RETURN_PCPY */
INTERN_FUNCTION(F(libc_memcpy))
#endif /* !RETURN_PCPY */
	.cfi_startproc
	ENTER_CLD
	pushl_cfi_r %edi
	pushl_cfi_r %esi
	movl   12(%esp), %edi /* dst */
	movl   16(%esp), %esi /* src */
	movl   20(%esp), %ecx /* n_bytes */
#if !RETURN_PCPY
	movl   %edi, %eax
#endif /* !RETURN_PCPY */
#if N == 1
	movl   %ecx, %edx
	shrl   $(2), %ecx
	rep;   movsl
	jnc    1f /* if (!(n_bytes & 2)) goto 1f; */
	movsw
1:	TEST_DX_MASK(1)
	jz     1f /* if (!(n_bytes & 1)) goto 1f; */
	movsb
1:
#elif N == 2
	shrl   $(1), %ecx
	rep;   movsl
	jnc    1f /* if (!(n_words & 1)) goto 1f; */
	movsw
1:
#else
	rep;   movsl
#endif
#if RETURN_PCPY
	movl   %edi, %eax
#endif /* RETURN_PCPY */
	popl_cfi_r  %esi
	popl_cfi_r  %edi
	RET(12)
	.cfi_endproc
#if RETURN_PCPY
END(F(libc_mempcpy))
DEFINE_PUBLIC_ALIAS(F(mempcpy),F(libc_mempcpy))
#else /* RETURN_PCPY */
END(F(libc_memcpy))
DEFINE_PUBLIC_ALIAS(F(memcpy),F(libc_memcpy))
#endif /* !RETURN_PCPY */




.section .text.crt.string.memory
#if RETURN_PCPY
INTERN_FUNCTION(F(libc_mempmove))
#else /* RETURN_PCPY */
INTERN_FUNCTION(F(libc_memmove))
#endif /* !RETURN_PCPY */
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
	popl_cfi_r  %esi
	popl_cfi_r  %edi
	RET(12)
#endif /* !__OPTIMIZE_SIZE__ */
	.cfi_endproc
#if RETURN_PCPY
END(F(libc_mempmove))
DEFINE_PUBLIC_ALIAS(F(mempmove),F(libc_mempmove))
#else /* RETURN_PCPY */
END(F(libc_memmove))
DEFINE_PUBLIC_ALIAS(F(memmove),F(libc_memmove))
#endif /* !RETURN_PCPY */



.section .text.crt.string.memory
	.cfi_startproc
#if RETURN_PCPY
INTERN_FUNCTION(F(libc_mempmovedown))
#else /* RETURN_PCPY */
INTERN_FUNCTION(F(libc_memmovedown))
#endif /* !RETURN_PCPY */
	/* assert(dst <= src || !n_bytes); */
	ENTER_CLD
	pushl_cfi_r %edi
	pushl_cfi_r %esi
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
#ifndef MEMMOVEDOWN_INVALID_ORDER_STRINGS_DEFINED
#define MEMMOVEDOWN_INVALID_ORDER_STRINGS_DEFINED 1
	.pushsection .rodata.crt.string.memory
.Linvalid_order_str_format: .asciz "This isn't a memmovedown() operation, but is memmoveup(): dst(%p) > src(%p) (count:%Iu)"
.Linvalid_order_str_file:   .asciz __FILE__
.Linvalid_order_str_expr:   .asciz "dst <= src"
	.popsection
#endif /* !MEMMOVEDOWN_INVALID_ORDER_STRINGS_DEFINED */
#if RETURN_PCPY
#ifndef MEMMOVEDOWN_INVALID_ORDER_FUNC_DEFINED
#define MEMMOVEDOWN_INVALID_ORDER_FUNC_DEFINED 1
	.pushsection .rodata.crt.string.memory
.Linvalid_order_str_pfunc:  .asciz "mempmovedown"
	.popsection
#endif /* !MEMMOVEDOWN_INVALID_ORDER_FUNC_DEFINED */
#else /* RETURN_PCPY */
#ifndef MEMMOVEDOWN_INVALID_ORDER_PFUNC_DEFINED
#define MEMMOVEDOWN_INVALID_ORDER_PFUNC_DEFINED 1
	.pushsection .rodata.crt.string.memory
.Linvalid_order_str_func:   .asciz "memmovedown"
	.popsection
#endif /* !MEMMOVEDOWN_INVALID_ORDER_PFUNC_DEFINED */
#endif /* !RETURN_PCPY */
	pushl_cfi %ecx                                  /* format:`...count:%Iu' */
	pushl_cfi %esi                                  /* format:`...src(%p)...' */
	pushl_cfi %edi                                  /* format:`...dst(%p)...' */
#if defined(__PIC__) || defined(__PIE__) || defined(__pic__) || defined(__pie__)
	call   9f
	.cfi_adjust_cfa_offset 4
9:	popl_cfi  %edi
	addl   $(_GLOBAL_OFFSET_TABLE_ - (. - 9b)), %edi
#define PUSH_RELSTR(x) leal x@GOTOFF(%edi), %eax; pushl_cfi %eax
#else /* __PIC__ || __PIE__ || __pic__ || __pie__ */
#define PUSH_RELSTR(x) pushl_cfi $(x)
#endif /* !__PIC__ && !__PIE__ && !__pic__ && !__pie__ */
	PUSH_RELSTR(.Linvalid_order_str_format) /* format */
#if RETURN_PCPY
	PUSH_RELSTR(.Linvalid_order_str_pfunc)  /* func */
#else /* RETURN_PCPY */
	PUSH_RELSTR(.Linvalid_order_str_func)   /* func */
#endif /* !RETURN_PCPY */
	pushl_cfi $(__LINE__)                   /* line */
	PUSH_RELSTR(.Linvalid_order_str_file)   /* file */
	PUSH_RELSTR(.Linvalid_order_str_expr)   /* expr */
#undef PUSH_RELSTR
	INTERN(libc___afailf)
	call   libc___afailf
	addl   $(32), %esp
	.cfi_adjust_cfa_offset -32
	popl_cfi_r %esi
	popl_cfi_r %edi
#if RETURN_PCPY
	INTERN(F(libc_mempmoveup))
	jmp    F(libc_mempmoveup)
#else /* RETURN_PCPY */
	INTERN(F(libc_memmoveup))
	jmp    F(libc_memmoveup)
#endif /* !RETURN_PCPY */
1:	.cfi_restore_state
#endif /* !NDEBUG */

#if RETURN_PCPY
PRIVATE_LABEL(F(libc_x86_mempmovedown_start)):
#else /* RETURN_PCPY */
PRIVATE_LABEL(F(libc_x86_memmovedown_start)):
#endif /* !RETURN_PCPY */

#if !RETURN_PCPY
	movl   %edi, %eax
#endif /* !RETURN_PCPY */

	/* Actually copy memory */
	rep;   I(movs)

#if RETURN_PCPY
	movl   %edi, %eax
#endif /* RETURN_PCPY */
	popl_cfi_r  %esi
	popl_cfi_r  %edi
	RET(12)
	.cfi_endproc
#if RETURN_PCPY
END(F(libc_mempmovedown))
DEFINE_PUBLIC_ALIAS(F(mempmovedown),F(libc_mempmovedown))
#else /* RETURN_PCPY */
END(F(libc_memmovedown))
DEFINE_PUBLIC_ALIAS(F(memmovedown),F(libc_memmovedown))
#endif /* !RETURN_PCPY */

.section .text.crt.string.memory
#if RETURN_PCPY
INTERN_FUNCTION(F(libc_mempmoveup))
#else /* RETURN_PCPY */
INTERN_FUNCTION(F(libc_memmoveup))
#endif /* !RETURN_PCPY */
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
	/* Invalid use of `memmovedown' */
#ifndef MEMMOVEUP_INVALID_ORDER_STRINGS_DEFINED
#define MEMMOVEUP_INVALID_ORDER_STRINGS_DEFINED 1
	.pushsection .rodata.crt.string.memory
.Linvalid_orderup_str_format: .asciz "This isn't a memmoveup() operation, but is memmovedown(): dst(%p) < src(%p) (count:%Iu)"
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
	pushl_cfi %ecx                                  /* format:`...count:%Iu' */
	pushl_cfi %esi                                  /* format:`...src(%p)...' */
	pushl_cfi %edi                                  /* format:`...dst(%p)...' */
#if defined(__PIC__) || defined(__PIE__) || defined(__pic__) || defined(__pie__)
	call   9f
	.cfi_adjust_cfa_offset 4
9:	popl_cfi  %edi
	addl   $(_GLOBAL_OFFSET_TABLE_ - (. - 9b)), %edi
#define PUSH_RELSTR(x) leal x@GOTOFF(%edi), %eax; pushl_cfi %eax
#else /* __PIC__ || __PIE__ || __pic__ || __pie__ */
#define PUSH_RELSTR(x) pushl_cfi $(x)
#endif /* !__PIC__ && !__PIE__ && !__pic__ && !__pie__ */
	PUSH_RELSTR(.Linvalid_orderup_str_format) /* format */
#if RETURN_PCPY
	PUSH_RELSTR(.Linvalid_orderup_str_pfunc)  /* func */
#else /* RETURN_PCPY */
	PUSH_RELSTR(.Linvalid_orderup_str_func)   /* func */
#endif /* !RETURN_PCPY */
	pushl_cfi $(__LINE__)                     /* line */
	PUSH_RELSTR(.Linvalid_order_str_file)     /* file */
	PUSH_RELSTR(.Linvalid_orderup_str_expr)   /* expr */
#undef PUSH_RELSTR
	INTERN(libc___afailf)
	call   libc___afailf
	addl   $(32), %esp
	.cfi_adjust_cfa_offset -32
	popl_cfi_r %esi
	popl_cfi_r %edi
#if RETURN_PCPY
	INTERN(F(libc_mempmoveup))
	jmp    F(libc_mempmoveup)
#else /* RETURN_PCPY */
	INTERN(F(libc_memmoveup))
	jmp    F(libc_memmoveup)
#endif /* !RETURN_PCPY */
1:	.cfi_restore_state
#endif /* !NDEBUG */


#if RETURN_PCPY
PRIVATE_LABEL(F(libc_x86_mempmoveup_start)):
#else /* RETURN_PCPY */
PRIVATE_LABEL(F(libc_x86_memmoveup_start)):
#endif /* !RETURN_PCPY */

	/* Make sure that the direction bit is set,
	 * thus causing `movs' to do a top->down copy */
	std
#if !defined(__KERNEL__) || 1
	/* Setup a custom CFI restore function to clear EFLAGS.DF during unwinding */
/*[[[deemon
import * from deemon;
import compileExpression from ......misc.libgen.cfi.compiler;
compileExpression('i386', '%eflags', r'
	push %eflags     # %eflags
	push $EFLAGS_DF  # %eflags, EFLAGS_DF
	not              # %eflags, ~EFLAGS_DF
	and              # (%eflags & ~EFLAGS_DF)
', deref_after: false);
]]]*/
__ASM_L(	.cfi_escape 0x16,0x09,0x06,0x59,0x0a,0x00,0x04,0x20)
__ASM_L(	.cfi_escape 0x1a)
//[[[end]]]
#endif /* !__KERNEL__ */
#if !RETURN_PCPY
	movl   %edi, %eax
#endif /* !RETURN_PCPY */

	/* Jump ahead to the last address */
	leal   -N(%edi, %ecx, N), %edi
	leal   -N(%esi, %ecx, N), %esi
#if RETURN_PCPY
	leal   N(%edi), %eax
#endif /* RETURN_PCPY */

	/* Actually perform the memory copy */
	rep;   I(movs)

	/* Restore the direction flag */
#ifndef __KERNEL__
	cld
	.cfi_restore %eflags
#endif /* !__KERNEL__ */
	popl_cfi_r  %esi
	popl_cfi_r  %edi
	RET(12)
	.cfi_endproc
#if RETURN_PCPY
END(F(libc_mempmoveup))
DEFINE_PUBLIC_ALIAS(F(mempmoveup),F(libc_mempmoveup))
#else /* RETURN_PCPY */
END(F(libc_memmoveup))
DEFINE_PUBLIC_ALIAS(F(memmoveup),F(libc_memmoveup))
#endif /* !RETURN_PCPY */


#undef USED_LIBC_MEMMOVEDOWN_START
#undef USED_LIBC_MEMMOVEUP_START





.section .text.crt.string.memory
#if RETURN_PCPY
INTERN_FUNCTION(F(libc_mempset))
#else
INTERN_FUNCTION(F(libc_memset))
#endif
	.cfi_startproc
	ENTER_CLD
	pushl_cfi_r %edi
	pushl_cfi_r %esi
	movl   12(%esp), %edi /* dst */
#if N == 1
	movzbl 16(%esp), %eax /* byte */
	movb   %al, %ah
	movw   %ax, %cx
	shll   $(16), %eax
	movw   %cx, %ax
	movl   20(%esp), %ecx /* n_bytes */
#if !RETURN_PCPY
	pushl_cfi %edi
#endif
	movl   %ecx, %edx
	shrl   $(2), %ecx
	rep;   stosl
	jnc    1f /* if (!(n_bytes & 2)) goto 1f; */
	stosw
1:	TEST_DX_MASK(1)
	jz     1f /* if (!(n_bytes & 1)) goto 1f; */
	stosb
1:
#if !RETURN_PCPY
	popl_cfi %eax
#else
	movl   %edi, %eax
#endif
#elif N == 2
	movzwl 16(%esp), %eax /* word */
	movw   %ax, %cx
	shll   $(16), %eax
	movw   %cx, %ax
	movl   20(%esp), %ecx /* n_words */
#if !RETURN_PCPY
	movl   %edi, %edx
#endif
	shrl   $(1), %ecx
	rep;   stosl
	jnc    1f /* if (!(n_words & 1)) goto 1f; */
	stosw
1:
#if !RETURN_PCPY
	movl   %edx, %eax
#else
	movl   %edi, %eax
#endif
#else /* N == 4 */
	movl   16(%esp), %eax /* dword */
	movl   20(%esp), %ecx /* n_dwords */
#if !RETURN_PCPY
	movl   %edi, %edx
#endif
	rep;   stosl
#if !RETURN_PCPY
	movl   %edx, %eax
#else
	movl   %edi, %eax
#endif
#endif
	popl_cfi_r  %esi
	popl_cfi_r  %edi
	RET(12)
	.cfi_endproc
#if RETURN_PCPY
END(F(libc_mempset))
DEFINE_PUBLIC_ALIAS(F(mempset),F(libc_mempset))
#else
END(F(libc_memset))
DEFINE_PUBLIC_ALIAS(F(memset),F(libc_memset))
#endif



/* TODO: memmove[b|w|l]()     (movs) */
/* TODO: memmoveup[b|w|l]()   (movs) */
/* TODO: memmovedown[b|w|l]() (movs) */


#if !RETURN_PCPY

/* TODO: memcmp[b|w|l]()      (cmps) */
/* TODO: memchr[b|w|l]()      (scas) */
/* TODO: memrchr[b|w|l]()     (scas) */
/* TODO: memxchr[b|w|l]()     (scas) */
/* TODO: memrxchr[b|w|l]()    (scas) */
/* TODO: memend[b|w|l]()      (scas) */
/* TODO: memrend[b|w|l]()     (scas) */
/* TODO: memxend[b|w|l]()     (scas) */
/* TODO: memrxend[b|w|l]()    (scas) */
/* TODO: memlen[b|w|l]()      (scas) */
/* TODO: memrlen[b|w|l]()     (scas) */
/* TODO: memxlen[b|w|l]()     (scas) */
/* TODO: memrxlen[b|w|l]()    (scas) */
/* TODO: rawmemchr[b|w|l]()   (scas) */
/* TODO: rawmemrchr[b|w|l]()  (scas) */
/* TODO: rawmemxchr[b|w|l]()  (scas) */
/* TODO: rawmemrxchr[b|w|l]() (scas) */
/* TODO: rawmemlen[b|w|l]()   (scas) */
/* TODO: rawmemrlen[b|w|l]()  (scas) */
/* TODO: rawmemxlen[b|w|l]()  (scas) */
/* TODO: rawmemrxlen[b|w|l]() (scas) */



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
#endif
#endif


#ifdef F_STRING

.section STRING_SECTION
INTERN_FUNCTION(F_STRING(end))
	.cfi_startproc
	ENTER_CLD
	pushl_cfi_r %edi
	movl   8(%esp), %edi
	movl   $-1, %ecx
	xorl   %eax, %eax
	repne; I(scas)
	leal   -N(%edi), %eax
	popl_cfi_r %edi
	RET(4)
	.cfi_endproc
END(F_STRING(end))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(end),F_STRING(end))

.section STRING_SECTION
INTERN_FUNCTION(F_STRING(len))
	.cfi_startproc
	ENTER_CLD
	pushl_cfi_r %edi
	movl   8(%esp), %edi
	movl   $-1, %ecx
	xorl   %eax, %eax
	repne; I(scas)
	subl   %ecx, %eax /* result = 0 - ECX; */
	subl   $(2), %eax   /* result = (0 - ECX) - 2; */
	popl_cfi_r %edi
	RET(4)
	.cfi_endproc
END(F_STRING(len))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(len),F_STRING(len))

.section STRING_SECTION
INTERN_FUNCTION(F_STRING(nlen))
	.cfi_startproc
	ENTER_CLD
	xorl   %eax, %eax
	movl   8(%esp), %edx
	testl  %edx, %edx
	jz     2f
	pushl_cfi_r %edi
	movl   8(%esp), %edi
	movl   %edx, %ecx
	repne; I(scas)
	jne    1f
	incl   %ecx
1:	subl   %ecx, %edx
	movl   %edx, %eax /* result = max_chars - ECX; */
	popl_cfi_r %edi
2:	RET(8)
	.cfi_endproc
END(F_STRING(nlen))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(nlen),F_STRING(nlen))

.section STRING_SECTION
INTERN_FUNCTION(F_STRING(nend))
	.cfi_startproc
	ENTER_CLD
	pushl_cfi_r %edi
	xorl   %eax, %eax
	movl   8(%esp), %edi
	movl   12(%esp), %ecx
	testl  %ecx, %ecx
	jz     1f
	repne; I(scas)
	jne    1f
#if N == 1
	decl   %edi
#else
	subl   $N, %edi
#endif
1:	movl   %edi, %eax
	popl_cfi_r %edi
	RET(8)
	.cfi_endproc
END(F_STRING(nend))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(nend),F_STRING(nend))

#endif /* F_STRING */


#undef F_STRING
#undef F_STRING_EXPORT
#undef STRING_SECTION

#endif /* !RETURN_PCPY */



#undef RETURN_PCPY
#undef N
#undef I
#undef F
#undef ENTER_CLD
#undef RET

