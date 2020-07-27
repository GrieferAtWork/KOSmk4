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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_CONFIG_H
#define GUARD_LIBC_HYBRID_ARCH_I386_CONFIG_H 1

#include <hybrid/host.h>

/* Libc functions implemented by arch-specific, optimized functions.
 * Defining these macros causes libc's auto/user-system to not provide
 * the associated functions. */

/* memcpy() */
#define LIBC_ARCH_HAVE_MEMCPY   1
#define LIBC_ARCH_HAVE_MEMCPYW  1
#define LIBC_ARCH_HAVE_MEMCPYL  1
#define LIBC_ARCH_HAVE_MEMPCPY  1
#define LIBC_ARCH_HAVE_MEMPCPYW 1
#define LIBC_ARCH_HAVE_MEMPCPYL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMCPYQ  1
#define LIBC_ARCH_HAVE_MEMPCPYQ 1
#endif /* __x86_64__ */

/* memmove() */
#define LIBC_ARCH_HAVE_MEMMOVE       1
#define LIBC_ARCH_HAVE_MEMMOVEUP     1
#define LIBC_ARCH_HAVE_MEMMOVEDOWN   1
#define LIBC_ARCH_HAVE_MEMMOVEW      1
#define LIBC_ARCH_HAVE_MEMMOVEUPW    1
#define LIBC_ARCH_HAVE_MEMMOVEDOWNW  1
#define LIBC_ARCH_HAVE_MEMMOVEL      1
#define LIBC_ARCH_HAVE_MEMMOVEUPL    1
#define LIBC_ARCH_HAVE_MEMMOVEDOWNL  1
#define LIBC_ARCH_HAVE_MEMPMOVE      1
#define LIBC_ARCH_HAVE_MEMPMOVEUP    1
#define LIBC_ARCH_HAVE_MEMPMOVEDOWN  1
#define LIBC_ARCH_HAVE_MEMPMOVEW     1
#define LIBC_ARCH_HAVE_MEMPMOVEUPW   1
#define LIBC_ARCH_HAVE_MEMPMOVEDOWNW 1
#define LIBC_ARCH_HAVE_MEMPMOVEL     1
#define LIBC_ARCH_HAVE_MEMPMOVEUPL   1
#define LIBC_ARCH_HAVE_MEMPMOVEDOWNL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMMOVEQ      1
#define LIBC_ARCH_HAVE_MEMMOVEUPQ    1
#define LIBC_ARCH_HAVE_MEMMOVEDOWNQ  1
#define LIBC_ARCH_HAVE_MEMPMOVEQ     1
#define LIBC_ARCH_HAVE_MEMPMOVEUPQ   1
#define LIBC_ARCH_HAVE_MEMPMOVEDOWNQ 1
#endif /* __x86_64__ */

/* memset() */
#define LIBC_ARCH_HAVE_MEMSET   1
#define LIBC_ARCH_HAVE_MEMSETW  1
#define LIBC_ARCH_HAVE_MEMSETL  1
#define LIBC_ARCH_HAVE_MEMPSET  1
#define LIBC_ARCH_HAVE_MEMPSETW 1
#define LIBC_ARCH_HAVE_MEMPSETL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMSETQ  1
#define LIBC_ARCH_HAVE_MEMPSETQ 1
#endif /* __x86_64__ */

/* bzero() */
#define LIBC_ARCH_HAVE_BZERO  1
#define LIBC_ARCH_HAVE_BZEROW 1
#define LIBC_ARCH_HAVE_BZEROL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_BZEROQ 1
#endif /* __x86_64__ */

/* memcmp() */
#define LIBC_ARCH_HAVE_MEMCMP  1
#define LIBC_ARCH_HAVE_MEMCMPW 1
#define LIBC_ARCH_HAVE_MEMCMPL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMCMPQ 1
#endif /* __x86_64__ */

/* strlen() */
#define LIBC_ARCH_HAVE_STRLEN  1
#define LIBC_ARCH_HAVE_STREND  1
#define LIBC_ARCH_HAVE_STRNLEN 1
#define LIBC_ARCH_HAVE_STRNEND 1

/* c16slen() */
#define LIBC_ARCH_HAVE_C16SLEN  1
#define LIBC_ARCH_HAVE_C16SEND  1
#define LIBC_ARCH_HAVE_C16SNLEN 1
#define LIBC_ARCH_HAVE_C16SNEND 1

/* c32slen() */
#define LIBC_ARCH_HAVE_C32SLEN  1
#define LIBC_ARCH_HAVE_C32SEND  1
#define LIBC_ARCH_HAVE_C32SNLEN 1
#define LIBC_ARCH_HAVE_C32SNEND 1

/* abort() */
#define LIBC_ARCH_HAVE_ABORT 1


#ifndef __KERNEL__
/* void ASMCALL libc_sig_restore(void); */
#define LIBC_ARCH_HAVE_SIG_RESTORE 1

/* Arch-specific RTM optimizations do exist on x86
 * (in the form of a dedicated instruction set) */
#define LIBC_ARCH_HAVE_RTM_BEGIN 1
#define LIBC_ARCH_HAVE_RTM_END   1
#define LIBC_ARCH_HAVE_RTM_ABORT 1
#define LIBC_ARCH_HAVE_RTM_TEST  1

#define LIBC_ARCH_HAVE_GETCONTEXT  1
#define LIBC_ARCH_HAVE_SETCONTEXT  1
#define LIBC_ARCH_HAVE_SWAPCONTEXT 1
#define LIBC_ARCH_HAVE_MAKECONTEXT 1
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_CONFIG_H */
