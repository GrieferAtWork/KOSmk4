/* HASH CRC-32:0x889abe88 */
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
#ifndef __local_fputs_defined
#if (defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)|| defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))))
#define __local_fputs_defined 1
#include <kos/anno.h>
/* Dependency: "fwrite" from "stdio" */
#ifndef ____localdep_fwrite_defined
#define ____localdep_fwrite_defined 1
#if __has_builtin(__builtin_fwrite) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fwrite)
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__FORCELOCAL __ATTR_NONNULL((1, 4)) __SIZE_TYPE__ (__LIBCCALL __localdep_fwrite)(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) __THROWS(...) { return __builtin_fwrite(__buf, __elemsize, __elemcount, __stream); }
#elif defined(__CRT_HAVE_fwrite_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_fwrite,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite_unlocked,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fwrite_nolock) && (defined(__USE_STDIO_UNLOCKED))
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_fwrite,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fwrite_nolock,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fwrite)
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_fwrite,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fwrite_s)
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_fwrite,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite_s,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <local/stdio/fwrite.h>
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
#define __localdep_fwrite (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwrite))
#else /* CUSTOM: fwrite */
#undef ____localdep_fwrite_defined
#endif /* fwrite... */
#endif /* !____localdep_fwrite_defined */

/* Dependency: "strlen" from "string" */
#ifndef ____localdep_strlen_defined
#define ____localdep_strlen_defined 1
#if defined(__CRT_HAVE_strlen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#endif /* !____localdep_strlen_defined */

__NAMESPACE_LOCAL_BEGIN
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
__LOCAL_LIBC(fputs) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(fputs))(char const *__restrict __str,
                                      __FILE *__restrict __stream) __THROWS(...) {
#line 524 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__result = __localdep_fwrite(__str,
	                sizeof(char),
	                __localdep_strlen(__str),
	                __stream);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)|| defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked)))) */
#endif /* !__local_fputs_defined */
