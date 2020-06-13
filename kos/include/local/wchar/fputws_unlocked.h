/* HASH CRC-32:0x74171e4b */
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
#ifndef __local_fputws_unlocked_defined
#define __local_fputws_unlocked_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_file_wprinter_unlocked) || (defined(__CRT_HAVE_DOS$file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_file_wprinter) || (defined(__CRT_HAVE_DOS$file_wprinter) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$file_wprinter) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_fputwc_unlocked) || (defined(__CRT_HAVE_DOS$fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wcslen from wchar */
#ifndef __local___localdep_wcslen_defined
#define __local___localdep_wcslen_defined 1
#ifdef __CRT_HAVE_wcslen
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_DOS$wcslen) && __SIZEOF_WCHAR_T__ == 4
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_DOS$wcslen) && __SIZEOF_WCHAR_T__ == 2
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __string),wcslen,(__string))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_wcslen __LIBC_LOCAL_NAME(wcslen)
#endif /* !... */
#endif /* !__local___localdep_wcslen_defined */
/* Dependency: file_wprinter_unlocked from wchar */
#ifndef __local___localdep_file_wprinter_unlocked_defined
#define __local___localdep_file_wprinter_unlocked_defined 1
#ifdef __CRT_HAVE_file_wprinter_unlocked
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_wprinter_unlocked,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_wprinter_unlocked,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_wprinter_unlocked,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter)
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_wprinter_unlocked,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter) && __SIZEOF_WCHAR_T__ == 4
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_wprinter_unlocked,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter) && __SIZEOF_WCHAR_T__ == 2
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_wprinter_unlocked,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc_unlocked) || (defined(__CRT_HAVE_DOS$fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/file_wprinter_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
#define __localdep_file_wprinter_unlocked __LIBC_LOCAL_NAME(file_wprinter_unlocked)
#else /* ... */
#undef __local___localdep_file_wprinter_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_file_wprinter_unlocked_defined */
__LOCAL_LIBC(fputws_unlocked) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(fputws_unlocked))(__WCHAR_TYPE__ const *__restrict __string, __FILE *__restrict __stream) __THROWS(...) {
	__STDC_INT_AS_SIZE_T __result;
	__result = __localdep_file_wprinter_unlocked(__stream, __string, __localdep_wcslen(__string));
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fputws_unlocked_defined
#define __local___localdep_fputws_unlocked_defined 1
#define __localdep_fputws_unlocked __LIBC_LOCAL_NAME(fputws_unlocked)
#endif /* !__local___localdep_fputws_unlocked_defined */
#else /* __CRT_HAVE_file_wprinter_unlocked || (__CRT_HAVE_DOS$file_wprinter_unlocked && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$file_wprinter_unlocked && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_file_wprinter || (__CRT_HAVE_DOS$file_wprinter && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$file_wprinter && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_fputwc_unlocked || (__CRT_HAVE_DOS$fputwc_unlocked && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$_fputwc_nolock && __SIZEOF_WCHAR_T__ == 2) */
#undef __local_fputws_unlocked_defined
#endif /* !__CRT_HAVE_file_wprinter_unlocked && (!__CRT_HAVE_DOS$file_wprinter_unlocked || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$file_wprinter_unlocked || !__SIZEOF_WCHAR_T__ == 2) && !__CRT_HAVE_file_wprinter && (!__CRT_HAVE_DOS$file_wprinter || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$file_wprinter || !__SIZEOF_WCHAR_T__ == 2) && !__CRT_HAVE_fputwc_unlocked && (!__CRT_HAVE_DOS$fputwc_unlocked || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$_fputwc_nolock || !__SIZEOF_WCHAR_T__ == 2) */
#endif /* !__local_fputws_unlocked_defined */
