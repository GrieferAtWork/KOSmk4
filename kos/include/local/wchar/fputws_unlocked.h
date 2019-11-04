/* HASH CRC-32:0xc7a79abf */
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
#ifndef __local_fputws_unlocked_defined
#if defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter)
#define __local_fputws_unlocked_defined 1
#include <kos/anno.h>
/* Dependency: "file_wprinter_unlocked" from "wchar" */
#ifndef ____localdep_file_wprinter_unlocked_defined
#define ____localdep_file_wprinter_unlocked_defined 1
#ifdef __CRT_HAVE_file_wprinter_unlocked
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,,__localdep_file_wprinter_unlocked,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen)) __THROWS(...)
#elif defined(__CRT_HAVE_file_wprinter)
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,,__localdep_file_wprinter_unlocked,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)
#include <local/wchar/file_wprinter_unlocked.h>
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
#define __localdep_file_wprinter_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter_unlocked))
#else /* CUSTOM: file_wprinter_unlocked */
#undef ____localdep_file_wprinter_unlocked_defined
#endif /* file_wprinter_unlocked... */
#endif /* !____localdep_file_wprinter_unlocked_defined */

/* Dependency: "wcslen" from "wchar" */
#ifndef ____localdep_wcslen_defined
#define ____localdep_wcslen_defined 1
#ifdef __std___localdep_wcslen_defined
__NAMESPACE_STD_USING(__localdep_wcslen)
#elif defined(__CRT_HAVE_wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __string),wcslen,(__string))
#else /* LIBC: wcslen */
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_wcslen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))
#endif /* wcslen... */
#endif /* !____localdep_wcslen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fputws_unlocked) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(fputws_unlocked))(__WCHAR_TYPE__ const *__restrict __string,
                                                __FILE *__restrict __stream) __THROWS(...) {
#line 998 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T __result;
	__result = __localdep_file_wprinter_unlocked(__stream, __string, __localdep_wcslen(__string));
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) */
#endif /* !__local_fputws_unlocked_defined */
