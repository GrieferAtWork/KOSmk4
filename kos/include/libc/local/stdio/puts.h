/* HASH CRC-32:0x5993182 */
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
#ifndef __local_puts_defined
#define __local_puts_defined 1
#include <__crt.h>
#include <features.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fputc from stdio */
#ifndef __local___localdep_fputc_defined
#define __local___localdep_fputc_defined 1
#if __has_builtin(__builtin_fputc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc)
/* >> fputc(3)
 * Write a single character `ch' to `stream' */
__CEIREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc,{ return __builtin_fputc(__ch, __stream); })
#elif defined(__CRT_HAVE_fputc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc)
/* >> fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE_putc)
/* >> fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc)
/* >> fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
/* >> fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
/* >> fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fputc.h>
__NAMESPACE_LOCAL_BEGIN
/* >> fputc(3)
 * Write a single character `ch' to `stream' */
#define __localdep_fputc __LIBC_LOCAL_NAME(fputc)
#else /* ... */
#undef __local___localdep_fputc_defined
#endif /* !... */
#endif /* !__local___localdep_fputc_defined */
/* Dependency: fputs from stdio */
#ifndef __local___localdep_fputs_defined
#define __local___localdep_fputs_defined 1
#if __has_builtin(__builtin_fputs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputs)
/* >> fputs(3)
 * Print a given string `str' to `stream'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
__CEIREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_fputs,(char const *__restrict __str, __FILE *__restrict __stream),fputs,{ return __builtin_fputs(__str, __stream); })
#elif defined(__CRT_HAVE_fputs_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fputs(3)
 * Print a given string `str' to `stream'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_fputs,(char const *__restrict __str, __FILE *__restrict __stream),fputs_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE_fputs)
/* >> fputs(3)
 * Print a given string `str' to `stream'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_fputs,(char const *__restrict __str, __FILE *__restrict __stream),fputs,(__str,__stream))
#elif defined(__CRT_HAVE__IO_fputs)
/* >> fputs(3)
 * Print a given string `str' to `stream'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_fputs,(char const *__restrict __str, __FILE *__restrict __stream),_IO_fputs,(__str,__stream))
#elif defined(__CRT_HAVE_fputs_unlocked)
/* >> fputs(3)
 * Print a given string `str' to `stream'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_fputs,(char const *__restrict __str, __FILE *__restrict __stream),fputs_unlocked,(__str,__stream))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fputs.h>
__NAMESPACE_LOCAL_BEGIN
/* >> fputs(3)
 * Print a given string `str' to `stream'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
#define __localdep_fputs __LIBC_LOCAL_NAME(fputs)
#endif /* !... */
#endif /* !__local___localdep_fputs_defined */
__NAMESPACE_LOCAL_END
#include <libc/local/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
/* >> puts(3)
 * Print a given string `str', followed by a line-feed to `stdout' */
__LOCAL_LIBC(puts) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(puts))(char const *__restrict __string) __THROWS(...) {
	__STDC_INT_AS_SSIZE_T __result, __temp;
	__result = __localdep_fputs(__string, __LOCAL_stdout);
	if (__result >= 0) {
		__temp = __localdep_fputc('\n', __LOCAL_stdout);
		if (__temp <= 0)
			__result = __temp;
		else
			__result += __temp;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_puts_defined
#define __local___localdep_puts_defined 1
#define __localdep_puts __LIBC_LOCAL_NAME(puts)
#endif /* !__local___localdep_puts_defined */
#else /* !__NO_STDSTREAMS && (__CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __local_puts_defined
#endif /* __NO_STDSTREAMS || (!__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__local_puts_defined */
