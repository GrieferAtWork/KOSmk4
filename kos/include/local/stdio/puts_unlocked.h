/* HASH CRC-32:0x766faed7 */
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
#ifndef __local_puts_unlocked_defined
#if !defined(__NO_STDSTREAMS) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || defined(__CRT_HAVE_fputs_unlocked) || defined(__CRT_HAVE_fputs))
#define __local_puts_unlocked_defined 1
#include <kos/anno.h>
#include <local/stdstreams.h>
/* Dependency: "fputs_unlocked" from "stdio" */
#ifndef ____localdep_fputs_unlocked_defined
#define ____localdep_fputs_unlocked_defined 1
#if __has_builtin(__builtin_fputs_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputs_unlocked)
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL __localdep_fputs_unlocked)(char const *__restrict __string, __FILE *__restrict __stream) __THROWS(...) { return __builtin_fputs_unlocked(__string, __stream); }
#elif defined(__CRT_HAVE_fputs_unlocked)
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,__localdep_fputs_unlocked,(char const *__restrict __string, __FILE *__restrict __stream),fputs_unlocked,(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputs)
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,__localdep_fputs_unlocked,(char const *__restrict __string, __FILE *__restrict __stream),fputs,(__string,__stream)) __THROWS(...)
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf)))
#include <local/stdio/fputs_unlocked.h>
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
#define __localdep_fputs_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputs_unlocked))
#else /* CUSTOM: fputs_unlocked */
#undef ____localdep_fputs_unlocked_defined
#endif /* fputs_unlocked... */
#endif /* !____localdep_fputs_unlocked_defined */

/* Dependency: "fputc_unlocked" from "stdio" */
#ifndef ____localdep_fputc_unlocked_defined
#define ____localdep_fputc_unlocked_defined 1
#if __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__FORCELOCAL __ATTR_NONNULL((2)) int (__LIBCCALL __localdep_fputc_unlocked)(int __ch, __FILE *__restrict __stream) __THROWS(...) { return __builtin_fputc_unlocked(__ch, __stream); }
#elif defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_putc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream)) __THROWS(...)
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s)
#include <local/stdio/fputc_unlocked.h>
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
#define __localdep_fputc_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc_unlocked))
#else /* CUSTOM: fputc_unlocked */
#undef ____localdep_fputc_unlocked_defined
#endif /* fputc_unlocked... */
#endif /* !____localdep_fputc_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(puts_unlocked) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(puts_unlocked))(char const *__restrict __string) __THROWS(...) {
#line 1985 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SSIZE_T __result, __temp;
	__result = __localdep_fputs_unlocked(__string, __LOCAL_stdout);
	if (__result >= 0) {
		__temp = __localdep_fputc_unlocked('\n', __LOCAL_stdout);
		if (__temp <= 0)
			__result = __temp;
		else
			__result += __temp;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !defined(__NO_STDSTREAMS) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || defined(__CRT_HAVE_fputs_unlocked) || defined(__CRT_HAVE_fputs)) */
#endif /* !__local_puts_unlocked_defined */
