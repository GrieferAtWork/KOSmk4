/* Copyright (c) 2019 Griefer@Work                                            *
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
#include <hybrid/compiler.h>
#include <asm/cfi.h>

#ifndef N
#error "Must #define N before #including this file"
#endif
#ifndef RETURN_PCPY
#error "Must #define RETURN_PCPY before #including this file"
#endif

#ifdef __KERNEL__
#define ENTER_CLD  cld
#define RET(n)     ret $n
#else
#define ENTER_CLD  /* nothing */
#define RET(n)     ret
#endif


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


.section .text.crt.string.memory
#if RETURN_PCPY
INTERN_FUNCTION(F(libc_mempcpy))
#else
INTERN_FUNCTION(F(libc_memcpy))
#endif
	.cfi_startproc
	ENTER_CLD
	pushl_cfi_r %edi
	pushl_cfi_r %esi
	movl   12(%esp), %edi /* dst */
	movl   16(%esp), %esi /* src */
	movl   20(%esp), %ecx /* n_bytes */
#if !RETURN_PCPY
	movl   %edi, %eax
#endif
#if N == 1
	movl   %ecx, %edx
	shrl   $2, %ecx
	rep    movsl
	jnc    1f /* if (!(n_bytes & 2)) goto 1f; */
	movsw
1:	TEST_DX_MASK(1)
	jz     1f /* if (!(n_bytes & 1)) goto 1f; */
	movsb
1:
#elif N == 2
	shrl   $1, %ecx
	rep    movsl
	jnc    1f /* if (!(n_words & 1)) goto 1f; */
	movsw
1:
#else
	rep    movsl
#endif
#if RETURN_PCPY
	movl   %edi, %eax
#endif
	popl_cfi_r  %esi
	popl_cfi_r  %edi
	RET(12)
	.cfi_endproc
#if RETURN_PCPY
END(F(libc_mempcpy))
DEFINE_PUBLIC_ALIAS(F(mempcpy),F(libc_mempcpy))
#else
END(F(libc_memcpy))
DEFINE_PUBLIC_ALIAS(F(memcpy),F(libc_memcpy))
#endif





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
	shll   $16, %eax
	movw   %cx, %ax
	movl   20(%esp), %ecx /* n_bytes */
#if !RETURN_PCPY
	pushl_cfi %edi
#endif
	movl   %ecx, %edx
	shrl   $2, %ecx
	rep    stosl
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
	shll   $16, %eax
	movw   %cx, %ax
	movl   20(%esp), %ecx /* n_words */
#if !RETURN_PCPY
	movl   %edi, %edx
#endif
	shrl   $1, %ecx
	rep    stosl
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
	rep    stosl
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
	subl   $2, %eax   /* result = (0 - ECX) - 2; */
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

