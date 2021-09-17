/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_CONFIG_H
#define GUARD_LIBC_HYBRID_ARCH_I386_CONFIG_H 1

#include <hybrid/host.h>

/* Libc functions implemented  by arch-specific, optimized  functions.
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
#ifndef __KERNEL__
#ifndef __x86_64__
#define LIBC_ARCH_HAVE_C16MEMCMP 1 /* Alias for `memcmpw'. Works, because memcmpw returns through %eax,
                                    * rather than %ax,  meaning that even  though the public  prototype
                                    * might indicate a 16-bit return value, that is only partly true as
                                    * the user normally only sees a truncation.
                                    * But because wmemcmp(3)  (and thus c16memcmp(3))  return `int',  this
                                    * alias  would  normally  only work  when  `sizeof(int) <= 2', meaning
                                    * that this isn't something that can normally be done unconditionally. */
#else /* !__x86_64__ */
/* `LIBC_ARCH_HAVE_C16MEMCMP' is not implemented because of msabi64! */
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_C32MEMCMP 1 /* Alias for `memcmpl', because on i386/x86_64 `sizeof(int) <= 4' */
#endif /* !__KERNEL__ */

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

/* Misc string/memory functions */
#define LIBC_ARCH_HAVE_RAWMEMCHR  1
#define LIBC_ARCH_HAVE_RAWMEMCHRW 1
#define LIBC_ARCH_HAVE_RAWMEMCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_RAWMEMCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_RAWMEMRCHR  1
#define LIBC_ARCH_HAVE_RAWMEMRCHRW 1
#define LIBC_ARCH_HAVE_RAWMEMRCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_RAWMEMRCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMCHR  1
#define LIBC_ARCH_HAVE_MEMCHRW 1
#define LIBC_ARCH_HAVE_MEMCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMRCHR  1
#define LIBC_ARCH_HAVE_MEMRCHRW 1
#define LIBC_ARCH_HAVE_MEMRCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMRCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMEND  1
#define LIBC_ARCH_HAVE_MEMENDW 1
#define LIBC_ARCH_HAVE_MEMENDL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMENDQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMREND  1
#define LIBC_ARCH_HAVE_MEMRENDW 1
#define LIBC_ARCH_HAVE_MEMRENDL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMRENDQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMLEN  1
#define LIBC_ARCH_HAVE_MEMLENW 1
#define LIBC_ARCH_HAVE_MEMLENL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMLENQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMRLEN  1
#define LIBC_ARCH_HAVE_MEMRLENW 1
#define LIBC_ARCH_HAVE_MEMRLENL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMRLENQ 1
#endif /* __x86_64__ */
#ifndef __KERNEL__
#define LIBC_ARCH_HAVE_RAWMEMXCHR  1
#define LIBC_ARCH_HAVE_RAWMEMXCHRW 1
#define LIBC_ARCH_HAVE_RAWMEMXCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_RAWMEMXCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_RAWMEMRXCHR  1
#define LIBC_ARCH_HAVE_RAWMEMRXCHRW 1
#define LIBC_ARCH_HAVE_RAWMEMRXCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_RAWMEMRXCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMXCHR  1
#define LIBC_ARCH_HAVE_MEMXCHRW 1
#define LIBC_ARCH_HAVE_MEMXCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMXCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMRXCHR  1
#define LIBC_ARCH_HAVE_MEMRXCHRW 1
#define LIBC_ARCH_HAVE_MEMRXCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMRXCHRQ 1
#endif /* __x86_64__ */
#endif /* !__KERNEL__ */

/* abort() */
#define LIBC_ARCH_HAVE_ABORT 1


#ifndef __KERNEL__
/* void ASMCALL libc_sig_restore(void); */
#define LIBC_ARCH_HAVE_SIG_RESTORE 1

/* void *LIBCCALL libc_handle(void); */
#define LIBC_ARCH_HAVE_LIBC_HANDLE 1

#ifdef __x86_64__
#ifdef __CC__
DECL_BEGIN
#define libc_handle libc_handle
LOCAL WUNUSED ATTR_CONST ATTR_RETNONNULL void *NOTHROW(libc_handle)(void) {
	void *result;
	/* The  `current@tlsgd' symbol points to a `tls_index' structure,
	 * which consists of 16 bytes total, where the first 8 are filled
	 * with a module handle pointer by libdl.
	 * Note that this is a KOS-specific implementation detail. As far
	 * as the standard is concerned, libdl is allowed to make up some
	 * arbitrary module index for those 8 bytes, however KOS's  libdl
	 * simply re-uses  the regular  module handle  for this  purpose,
	 * meaning that we can simply (ab-)use that fact to quickly get a
	 * handle for libc itself. */
	__asm__("movq current@tlsgd(%%rip), %0" : "=r" (result));
	return result;
}
DECL_END
#endif /* __CC__ */
#endif /* __x86_64__ */

/* Arch-specific RTM optimizations do exist on x86
 * (in the form  of a  dedicated instruction  set) */
#define LIBC_ARCH_HAVE_RTM_BEGIN 1
#define LIBC_ARCH_HAVE_RTM_END   1
#define LIBC_ARCH_HAVE_RTM_ABORT 1
#define LIBC_ARCH_HAVE_RTM_TEST  1

#define LIBC_ARCH_HAVE_GETCONTEXT  1
#define LIBC_ARCH_HAVE_SETCONTEXT  1
#define LIBC_ARCH_HAVE_SWAPCONTEXT 1
#define LIBC_ARCH_HAVE_MAKECONTEXT 1

#define LIBC_ARCH_HAVE_CRTDBGBREAK 1
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_CONFIG_H */
