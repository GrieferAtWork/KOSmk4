/* HASH CRC-32:0xf9ff6b60 */
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
#ifndef __local_fputws_defined
#if (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked))
#define __local_fputws_defined 1
#include <kos/anno.h>
/* Dependency: "file_wprinter" from "wchar" */
#ifndef ____localdep_file_wprinter_defined
#define ____localdep_file_wprinter_defined 1
#if defined(__CRT_HAVE_file_wprinter_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,,__localdep_file_wprinter,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen)) __THROWS(...)
#elif defined(__CRT_HAVE_file_wprinter)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,,__localdep_file_wprinter,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen)) __THROWS(...)
#elif defined(__CRT_HAVE_file_wprinter_unlocked)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,,__localdep_file_wprinter,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <local/wchar/file_wprinter.h>
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
#define __localdep_file_wprinter (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter))
#else /* CUSTOM: file_wprinter */
#undef ____localdep_file_wprinter_defined
#endif /* file_wprinter... */
#endif /* !____localdep_file_wprinter_defined */

/* Dependency: "wcslen" from "wchar" */
#ifndef ____localdep_wcslen_defined
#define ____localdep_wcslen_defined 1
#ifdef __std___localdep_wcslen_defined
__NAMESPACE_STD_USING(__localdep_wcslen)
#elif defined(__CRT_HAVE_wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __string),wcslen,(__string))
#else /* LIBC: wcslen */
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_wcslen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))
#endif /* wcslen... */
#endif /* !____localdep_wcslen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fputws) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(fputws))(__WCHAR_TYPE__ const *__restrict __string,
                                       __FILE *__restrict __stream) __THROWS(...) {
#line 452 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T __result;
	__result = __localdep_file_wprinter(__stream, __string, __localdep_wcslen(__string));
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)) */
#endif /* !__local_fputws_defined */
