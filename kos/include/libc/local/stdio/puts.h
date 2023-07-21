/* HASH CRC-32:0xa55eb9ab */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_puts_defined
#define __local_puts_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#include <features.h>
#if defined(__LOCAL_stdout) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fputc_defined
#define __local___localdep_fputc_defined
#if defined(__USE_STDIO_UNLOCKED) && __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
__CEIREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_putc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif __has_builtin(__builtin_fputc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc)
__CEIREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc,{ return __builtin_fputc(__ch, __stream); })
#elif defined(__CRT_HAVE_putc)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fputc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fputc __LIBC_LOCAL_NAME(fputc)
#else /* ... */
#undef __local___localdep_fputc_defined
#endif /* !... */
#endif /* !__local___localdep_fputc_defined */
#ifndef __local___localdep_fputs_defined
#define __local___localdep_fputs_defined
#if defined(__USE_STDIO_UNLOCKED) && __has_builtin(__builtin_fputs_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputs_unlocked)
__CEIREDIRECT(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB,__localdep_fputs,(char const *__restrict __string, __FILE *__restrict __stream),fputs_unlocked,{ return __builtin_fputs_unlocked(__string, __stream); })
#elif defined(__CRT_HAVE_fputs_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB,__localdep_fputs,(char const *__restrict __string, __FILE *__restrict __stream),fputs_unlocked,(__string,__stream))
#elif __has_builtin(__builtin_fputs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputs)
__CEIREDIRECT(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB,__localdep_fputs,(char const *__restrict __string, __FILE *__restrict __stream),fputs,{ return __builtin_fputs(__string, __stream); })
#elif defined(__CRT_HAVE_fputs)
__CREDIRECT(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB,__localdep_fputs,(char const *__restrict __string, __FILE *__restrict __stream),fputs,(__string,__stream))
#elif defined(__CRT_HAVE__IO_fputs)
__CREDIRECT(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB,__localdep_fputs,(char const *__restrict __string, __FILE *__restrict __stream),_IO_fputs,(__string,__stream))
#elif defined(__CRT_HAVE_fputs_unlocked)
__CREDIRECT(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB,__localdep_fputs,(char const *__restrict __string, __FILE *__restrict __stream),fputs_unlocked,(__string,__stream))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fputs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fputs __LIBC_LOCAL_NAME(fputs)
#endif /* !... */
#endif /* !__local___localdep_fputs_defined */
__LOCAL_LIBC(puts) __ATTR_IN(1) __STDC_INT_AS_SSIZE_T
__NOTHROW_CB(__LIBCCALL __LIBC_LOCAL_NAME(puts))(char const *__restrict __string) {
	__STDC_INT_AS_SSIZE_T __result, __temp;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_fputs)(__string, __LOCAL_stdout);
	if (__result >= 0) {
		__temp = (__NAMESPACE_LOCAL_SYM __localdep_fputc)('\n', __LOCAL_stdout);
		if (__temp <= 0) {
			__result = __temp;
		} else {
			__result += __temp;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_puts_defined
#define __local___localdep_puts_defined
#define __localdep_puts __LIBC_LOCAL_NAME(puts)
#endif /* !__local___localdep_puts_defined */
#else /* __LOCAL_stdout && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __local_puts_defined
#endif /* !__LOCAL_stdout || (!__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__local_puts_defined */
