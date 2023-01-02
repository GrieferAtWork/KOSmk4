/* HASH CRC-32:0x5b5db22d */
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
#ifndef __local_wmkdirat_defined
#define __local_wmkdirat_defined
#include <__crt.h>
#if defined(__CRT_HAVE_wfmkdirat) || (defined(__CRT_HAVE_fmkdirat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_convert_wcstombs_defined
#define __local___localdep_convert_wcstombs_defined
#ifdef __CRT_HAVE_convert_wcstombs
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char *,__NOTHROW_NCX,__localdep_convert_wcstombs,(__WCHAR_TYPE__ const *__str),convert_wcstombs,(__str))
#elif defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_wcstombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_wcstombs __LIBC_LOCAL_NAME(convert_wcstombs)
#else /* ... */
#undef __local___localdep_convert_wcstombs_defined
#endif /* !... */
#endif /* !__local___localdep_convert_wcstombs_defined */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_mkdirat_defined
#define __local___localdep_mkdirat_defined
#ifdef __CRT_HAVE_mkdirat
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_RPC,__localdep_mkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode),mkdirat,(__dirfd,__pathname,__mode))
#elif defined(__CRT_HAVE_fmkdirat)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/mkdirat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mkdirat __LIBC_LOCAL_NAME(mkdirat)
#else /* ... */
#undef __local___localdep_mkdirat_defined
#endif /* !... */
#endif /* !__local___localdep_mkdirat_defined */
#ifndef __local___localdep_wfmkdirat_defined
#define __local___localdep_wfmkdirat_defined
#ifdef __CRT_HAVE_wfmkdirat
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_RPC,__localdep_wfmkdirat,(__fd_t __dirfd, __WCHAR_TYPE__ const *__pathname, __mode_t __mode, __atflag_t __flags),wfmkdirat,(__dirfd,__pathname,__mode,__flags))
#elif defined(__CRT_HAVE_fmkdirat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.sys.stat/wfmkdirat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wfmkdirat __LIBC_LOCAL_NAME(wfmkdirat)
#else /* ... */
#undef __local___localdep_wfmkdirat_defined
#endif /* !... */
#endif /* !__local___localdep_wfmkdirat_defined */
__LOCAL_LIBC(wmkdirat) __ATTR_IN(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wmkdirat))(__fd_t __dirfd, __WCHAR_TYPE__ const *__pathname, __mode_t __mode) {
#if defined(__CRT_HAVE_wfmkdirat) || (defined(__CRT_HAVE_fmkdirat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
	return (__NAMESPACE_LOCAL_SYM __localdep_wfmkdirat)(__dirfd, __pathname, __mode, 0);
#else /* __CRT_HAVE_wfmkdirat || (__CRT_HAVE_fmkdirat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
	int __result;
	char *__utf8_pathname;
	__utf8_pathname = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__pathname);
	if __unlikely(!__utf8_pathname)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_mkdirat)(__dirfd, __utf8_pathname, __mode);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_pathname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
#endif /* !__CRT_HAVE_wfmkdirat && (!__CRT_HAVE_fmkdirat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wmkdirat_defined
#define __local___localdep_wmkdirat_defined
#define __localdep_wmkdirat __LIBC_LOCAL_NAME(wmkdirat)
#endif /* !__local___localdep_wmkdirat_defined */
#else /* __CRT_HAVE_wfmkdirat || (__CRT_HAVE_fmkdirat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_mkdirat || __CRT_HAVE_fmkdirat) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_wmkdirat_defined
#endif /* !__CRT_HAVE_wfmkdirat && (!__CRT_HAVE_fmkdirat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) && ((!__CRT_HAVE_mkdirat && !__CRT_HAVE_fmkdirat) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_wmkdirat_defined */
