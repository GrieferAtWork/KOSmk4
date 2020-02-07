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
#include <asm/instr/movzxq.h>

#ifndef N
#error "Must #define N before #including this file"
#endif /* !N */
#ifndef RETURN_PCPY
#error "Must #define RETURN_PCPY before #including this file"
#endif /* !RETURN_PCPY */

#ifdef __KERNEL__
#define ENTER_CLD  cld
#else /* __KERNEL__ */
#define ENTER_CLD  /* nothing */
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
#if 1
#define TEST_DX_MASK(mask) testb $(mask), %dl
#else
#define TEST_DX_MASK(mask) testq $(mask), %rdx
#endif


.section .text.crt.string.memory
#if RETURN_PCPY
INTERN_FUNCTION(F(libc_mempcpy))
#else /* RETURN_PCPY */
INTERN_FUNCTION(F(libc_memcpy))
#endif /* !RETURN_PCPY */
	.cfi_startproc
	ENTER_CLD
#if !RETURN_PCPY
	movq   %rdi, %rax
#endif /* !RETURN_PCPY */
#if N == 1
	movq   %rdx, %rcx
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
	movq   %rdx, %rcx
	shrq   $(2), %rcx
	rep    movsq
	jnc    1f /* if (!(n_words & 2)) goto 1f; */
	movsl
1:	TEST_DX_MASK(1)
	jz     1f /* if (!(n_words & 1)) goto 1f; */
	movsw
1:
#elif N == 4
	movq   %rdx, %rcx
	shrq   $(1), %rcx
	rep    movsq
	jnc    1f /* if (!(n_dwords & 1)) goto 1f; */
	movsl
1:
#else /* N... */
	movq   %rdx, %rcx
	rep    movsq
#endif /* !N... */
#if RETURN_PCPY
	movq   %rdi, %rax
#endif /* RETURN_PCPY */
	ret
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
INTERN_FUNCTION(F(libc_mempset))
#else /* RETURN_PCPY */
INTERN_FUNCTION(F(libc_memset))
#endif /* !RETURN_PCPY */
	.cfi_startproc
	ENTER_CLD
#if N == 8
	movq   %rsi, %rax
	movq   %rdx, %rcx
#if !RETURN_PCPY
	movq   %rdi, %rdx
#endif /* !RETURN_PCPY */
	rep    stosq
#if RETURN_PCPY
	movq   %rdi, %rax
#else /* RETURN_PCPY */
	movq   %rdx, %rax
#endif /* !RETURN_PCPY */
#elif N == 4
	movzlq %esi, %rax /* RAX = ESI & 0xffffffff */
	shlq   $(32),  %rsi
	orq    %rsi, %rax /* RAX = ESI | ESI << 32 */
	movq   %rdx, %rcx
#if !RETURN_PCPY
	movq   %rdi, %rdx
#endif /* !RETURN_PCPY */
	shrq   $(1), %rcx
	rep    stosq
	jnc    1f /* if (!(n_dwords & 1)) goto 1f; */
	stosl
1:
#if RETURN_PCPY
	movq   %rdi, %rax
#else /* RETURN_PCPY */
	movq   %rdx, %rax
#endif /* !RETURN_PCPY */
#elif N == 2
	movw   %si, %ax
	shll   $(16), %eax
	movw   %si, %ax   /* EAX = WORD << 16 | WORD */
	movzlq %eax, %rsi
	shlq   $(32), %rax
	orq    %rsi, %rax /* EAX = WORD << 48 | WORD << 32 | WORD << 16 | WORD */
#if !RETURN_PCPY
	movq   %rdi, %r8
#endif /* !RETURN_PCPY */
	movq   %rdx, %rcx
	shrq   $(2), %rcx
	rep    stosq
	jnc    1f /* if (!(n_words & 2)) goto 1f; */
	stosl
1:	TEST_DX_MASK(1)
	jz     1f /* if (!(n_words & 1)) goto 1f; */
	stosw
1:
#if RETURN_PCPY
	movq   %rdi, %rax
#else /* RETURN_PCPY */
	movq   %r8, %rax
#endif /* !RETURN_PCPY */
#elif N == 1
	movb   %sil, %al
	movb   %al, %ah
	movw   %ax, %si
	shll   $(16), %eax
	movw   %si, %ax
	movzlq %eax, %rsi
	shlq   $(32), %rax
	orq    %rsi, %rax
#if !RETURN_PCPY
	movq   %rdi, %r8
#endif /* !RETURN_PCPY */
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
1:
#if RETURN_PCPY
	movq   %rdi, %rax
#else /* RETURN_PCPY */
	movq   %r8, %rax
#endif /* !RETURN_PCPY */
#else /* N... */
#error "INVALID N"
#endif /* !N... */
	ret
	.cfi_endproc
#if RETURN_PCPY
END(F(libc_mempset))
DEFINE_PUBLIC_ALIAS(F(mempset),F(libc_mempset))
#else /* RETURN_PCPY */
END(F(libc_memset))
DEFINE_PUBLIC_ALIAS(F(memset),F(libc_memset))
#endif /* !RETURN_PCPY */



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
#if N == 2
	/* char const *string = %rcx; */
	pushq_cfi_r %rdi
	movq   %rcx, %rdi
#endif
	movq   $-1, %rcx
	xorl   %eax, %eax
	repne; I(scas)
	leaq   -N(%rdi), %rax
#if N == 2
	popq_cfi_r %rdi
#endif
	ret
	.cfi_endproc
END(F_STRING(end))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(end),F_STRING(end))

.section STRING_SECTION
INTERN_FUNCTION(F_STRING(len))
	.cfi_startproc
	ENTER_CLD
#if N == 2
	/* char const *string = %rcx; */
	pushq_cfi_r %rdi
	movq   %rcx, %rdi
#endif
	movq   $-1, %rcx
	xorl   %eax, %eax
	repne; I(scas)
	subq   %rcx, %rax /* result = 0 - RCX; */
	subq   $(2), %rax   /* result = (0 - RCX) - 2; */
#if N == 2
	popq_cfi_r %rdi
#endif
	ret
	.cfi_endproc
END(F_STRING(len))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(len),F_STRING(len))

.section STRING_SECTION
INTERN_FUNCTION(F_STRING(nlen))
	.cfi_startproc
	ENTER_CLD
#if N == 2
	/* char const *string = %rcx; */
	/* size_t      maxlen = %rdx; */
	pushq_cfi_r %rdi
	movq   %rcx, %rdi
	xorq   %rax, %rax
	testq  %rdx, %rdx
	jz     2f
	movq   %rdx, %rcx
	repne; I(scas)
	jne    1f
	incq   %rcx
1:	subq   %rcx, %rdx
	movq   %rdx, %rax /* result = max_chars - RCX; */
#else /* N == 2 */
	xorq   %rax, %rax
	testq  %rsi, %rsi
	jz     2f
	movq   %rsi, %rcx
	repne; I(scas)
	jne    1f
	incq   %rcx
1:	subq   %rcx, %rsi
	movq   %rsi, %rax /* result = max_chars - RCX; */
#endif
2:	ret
	.cfi_endproc
END(F_STRING(nlen))
DEFINE_PUBLIC_ALIAS(F_STRING_EXPORT(nlen),F_STRING(nlen))

.section STRING_SECTION
INTERN_FUNCTION(F_STRING(nend))
	.cfi_startproc
	ENTER_CLD
#if N == 2
	/* char const *string = %rcx; */
	/* size_t      maxlen = %rdx; */
	pushq_cfi_r %rdi
	xorq   %rax, %rax
	testq  %rdx, %rdx
	movq   %rcx, %rdi
	jz     1f
	movq   %rdx, %rcx
	repne; I(scas)
	jne    1f
	subq   $(2), %rdi
1:	movq   %rdi, %rax
	popq_cfi_r %rdi
	ret
#else
	xorq   %rax, %rax
	testq  %rsi, %rsi
	jz     1f
	movq   %rsi, %rcx
	repne; I(scas)
	jne    1f
#if N == 1
	decq   %rdi
#else /* N == 1 */
	subq   $(N), %rdi
#endif /* N != 1 */
1:	movq   %rdi, %rax
	ret
#endif
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

