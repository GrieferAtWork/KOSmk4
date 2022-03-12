/* HASH CRC-32:0x18ae6a68 */
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
#ifndef __local_strsuftoll_defined
#define __local_strsuftoll_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#include <features.h>
#if defined(__CRT_HAVE_errx) || defined(__CRT_HAVE_verrx) || ((defined(__CRT_HAVE_vwarnx) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_errx_defined
#define __local___localdep_errx_defined
#ifdef __CRT_HAVE_errx
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 3) void (__VLIBCCALL __localdep_errx)(int __status, char const *__format, ...) __THROWS(...) __CASMNAME("errx");
#elif defined(__CRT_HAVE_verrx) || ((defined(__CRT_HAVE_vwarnx) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)))
__NAMESPACE_LOCAL_END
#include <libc/local/err/errx.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_errx __LIBC_LOCAL_NAME(errx)
#else /* ... */
#undef __local___localdep_errx_defined
#endif /* !... */
#endif /* !__local___localdep_errx_defined */
#ifndef __local___localdep_strsuftollx_defined
#define __local___localdep_strsuftollx_defined
#ifdef __CRT_HAVE_strsuftollx
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__LONGLONG,__NOTHROW_NCX,__localdep_strsuftollx,(char const *__desc, char const *__val, __LONGLONG __lo, __LONGLONG __hi, char *__errbuf, __SIZE_TYPE__ __errbuflen),strsuftollx,(__desc,__val,__lo,__hi,__errbuf,__errbuflen))
#else /* __CRT_HAVE_strsuftollx */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strsuftollx.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strsuftollx __LIBC_LOCAL_NAME(strsuftollx)
#endif /* !__CRT_HAVE_strsuftollx */
#endif /* !__local___localdep_strsuftollx_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/stdlib.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strsuftoll) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __LONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strsuftoll))(char const *__desc, char const *__val, __LONGLONG __lo, __LONGLONG __hi) {
	__LONGLONG __result;
	char __error_message[128];
	__result = (__NAMESPACE_LOCAL_SYM __localdep_strsuftollx)(__desc, __val, __lo, __hi,
	                     __error_message,
	                     sizeof(__error_message));
	if (__result == 0 && *__error_message) {
#ifdef __EXIT_FAILURE
		(__NAMESPACE_LOCAL_SYM __localdep_errx)(__EXIT_FAILURE, "%s", __error_message);
#else /* __EXIT_FAILURE */
		(__NAMESPACE_LOCAL_SYM __localdep_errx)(1, "%s", __error_message);
#endif /* !__EXIT_FAILURE */
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strsuftoll_defined
#define __local___localdep_strsuftoll_defined
#define __localdep_strsuftoll __LIBC_LOCAL_NAME(strsuftoll)
#endif /* !__local___localdep_strsuftoll_defined */
#else /* __CRT_HAVE_errx || __CRT_HAVE_verrx || ((__CRT_HAVE_vwarnx || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit)) */
#undef __local_strsuftoll_defined
#endif /* !__CRT_HAVE_errx && !__CRT_HAVE_verrx && ((!__CRT_HAVE_vwarnx && (!__LOCAL_stderr || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock))) || (!__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit)) */
#endif /* !__local_strsuftoll_defined */
