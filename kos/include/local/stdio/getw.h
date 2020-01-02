/* HASH CRC-32:0xe59798d0 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getw_defined
#if ((defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#define __local_getw_defined 1
#include <kos/anno.h>
/* Dependency: "fgetc" from "stdio" */
#ifndef ____localdep_fgetc_defined
#define ____localdep_fgetc_defined 1
#if defined(__CRT_HAVE_fgetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc,(__FILE *__restrict __stream),fgetc_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_getc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc,(__FILE *__restrict __stream),getc_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetc)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc,(__FILE *__restrict __stream),fgetc,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_getc)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc,(__FILE *__restrict __stream),getc,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_getc)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc,(__FILE *__restrict __stream),_IO_getc,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetc_unlocked)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc,(__FILE *__restrict __stream),fgetc_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_getc_unlocked)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc,(__FILE *__restrict __stream),getc_unlocked,(__stream)) __THROWS(...)
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)
#include <local/stdio/fgetc.h>
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
#define __localdep_fgetc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc))
#else /* CUSTOM: fgetc */
#undef ____localdep_fgetc_defined
#endif /* fgetc... */
#endif /* !____localdep_fgetc_defined */

/* Dependency: "ungetc" */
#ifndef ____localdep_ungetc_defined
#define ____localdep_ungetc_defined 1
#if defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock) && defined(__USE_STDIO_UNLOCKED)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_ungetc)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),_IO_ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc_unlocked)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#else /* LIBC: ungetc */
#undef ____localdep_ungetc_defined
#endif /* ungetc... */
#endif /* !____localdep_ungetc_defined */

__NAMESPACE_LOCAL_BEGIN
/* Similar to `getc()', but read 2 bytes */
__LOCAL_LIBC(getw) __ATTR_NONNULL((1)) int
(__LIBCCALL __LIBC_LOCAL_NAME(getw))(__FILE *__restrict __stream) __THROWS(...) {
#line 1399 "kos/src/libc/magic/stdio.c"
	char __bytes[2]; int __ch;
	__ch = __localdep_fgetc(__self);
	if __unlikely(__ch == __EOF)
		return __EOF;
	__bytes[0] = (char)__ch;
	__ch = __localdep_fgetc(__self);
	if __unlikely(__ch == __EOF) {
		__localdep_ungetc(__bytes[0], __stream);
		return __EOF;
	}
	__bytes[1] = (char)__ch;
	__bytes[2] = (char)__ch;
	return (int)*(__UINT16_TYPE__ *)__bytes;
}
__NAMESPACE_LOCAL_END
#endif /* ((__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread || __CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) */
#endif /* !__local_getw_defined */
