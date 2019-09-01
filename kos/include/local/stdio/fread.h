/* HASH 0x6ebfc35b */
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
#ifndef __local_fread_defined
#if (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))))
#define __local_fread_defined 1
#include <kos/anno.h>
/* Dependency: "fgetc" from "stdio" */
#ifndef ____localdep_fgetc_defined
#define ____localdep_fgetc_defined 1
#if defined(__CRT_HAVE_fgetc_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc,(__FILE *__restrict __stream),fgetc_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_getc_unlocked) && (defined(__USE_STDIO_UNLOCKED))
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
#elif ((defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))))
#include <local/stdio/fgetc.h>
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
#define __localdep_fgetc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc))
#else /* CUSTOM: fgetc */
#undef ____localdep_fgetc_defined
#endif /* fgetc... */
#endif /* !____localdep_fgetc_defined */

__NAMESPACE_LOCAL_BEGIN
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__LOCAL_LIBC(fread) __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(fread))(void *__restrict __buf,
                                      __SIZE_TYPE__ __elemsize,
                                      __SIZE_TYPE__ __elemcount,
                                      __FILE *__restrict __stream) __THROWS(...) {
#line 519 "kos/src/libc/magic/stdio.c"
	__SIZE_TYPE__ __i, __result = 0;
	for (; __elemcount; --__elemcount, ++__result) {
		for (__i = 0; __i < __elemsize; ++__i) {
			int __byte;
			__byte = __localdep_fgetc(__stream);
			if (__byte == __EOF)
				goto __done;
			*(unsigned char *)__buf = (unsigned char)(unsigned int)__byte;
			__buf = (unsigned char *)__buf + 1;
		}
	}
__done:
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))) */
#endif /* !__local_fread_defined */
