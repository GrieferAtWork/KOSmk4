/* HASH CRC-32:0x9305aba3 */
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
#ifndef __local_putchar_unlocked_defined
#if !defined(__NO_STDSTREAMS) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))))
#define __local_putchar_unlocked_defined 1
#include <__crt.h>
#include <kos/anno.h>
#include <local/stdstreams.h>
/* Dependency: "fputc_unlocked" from "stdio" */
#ifndef ____localdep_fputc_unlocked_defined
#define ____localdep_fputc_unlocked_defined 1
#if __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CEIREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc_unlocked,{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s)
#include <local/stdio/fputc_unlocked.h>
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
#define __localdep_fputc_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc_unlocked))
#else /* CUSTOM: fputc_unlocked */
#undef ____localdep_fputc_unlocked_defined
#endif /* fputc_unlocked... */
#endif /* !____localdep_fputc_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__LOCAL_LIBC(putchar_unlocked) int
(__LIBCCALL __LIBC_LOCAL_NAME(putchar_unlocked))(int __ch) __THROWS(...) {
#line 1355 "kos/src/libc/magic/stdio.c"
	return __localdep_fputc_unlocked(__ch, __LOCAL_stdout);
}
__NAMESPACE_LOCAL_END
#endif /* !__NO_STDSTREAMS && ((__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_HAVE_putc && (!__CRT_DOS || !__CRT_HAVE__flsbuf)) || (__CRT_HAVE_fputc && (!__CRT_DOS || !__CRT_HAVE__flsbuf)) || (__CRT_HAVE__IO_putc && (!__CRT_DOS || !__CRT_HAVE__flsbuf))) */
#endif /* !__local_putchar_unlocked_defined */
