/* HASH CRC-32:0xe68631da */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wmknodat_defined
#define __local_wmknodat_defined
#include <__crt.h>
#if defined(__CRT_HAVE_wfmknodat) || (defined(__CRT_HAVE_fmknodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_convert_wcstombs_defined
#define __local___localdep_convert_wcstombs_defined
#ifdef __CRT_HAVE_convert_wcstombs
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1),char *,__NOTHROW_NCX,__localdep_convert_wcstombs,(__WCHAR_TYPE__ const *__str),convert_wcstombs,(__str))
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
#ifndef __local___localdep_mknodat_defined
#define __local___localdep_mknodat_defined
#ifdef __CRT_HAVE_mknodat
__CREDIRECT(__ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,__localdep_mknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev),mknodat,(__dirfd,__nodename,__mode,__dev))
#elif defined(__CRT_HAVE_fmknodat)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/mknodat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mknodat __LIBC_LOCAL_NAME(mknodat)
#else /* ... */
#undef __local___localdep_mknodat_defined
#endif /* !... */
#endif /* !__local___localdep_mknodat_defined */
#ifndef __local___localdep_wfmknodat_defined
#define __local___localdep_wfmknodat_defined
#ifdef __CRT_HAVE_wfmknodat
__CREDIRECT(__ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,__localdep_wfmknodat,(__fd_t __dirfd, __WCHAR_TYPE__ const *__nodename, __mode_t __mode, __dev_t __dev, __atflag_t __flags),wfmknodat,(__dirfd,__nodename,__mode,__dev,__flags))
#elif defined(__CRT_HAVE_fmknodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.sys.stat/wfmknodat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wfmknodat __LIBC_LOCAL_NAME(wfmknodat)
#else /* ... */
#undef __local___localdep_wfmknodat_defined
#endif /* !... */
#endif /* !__local___localdep_wfmknodat_defined */
__LOCAL_LIBC(wmknodat) __ATTR_ACCESS_RO(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wmknodat))(__fd_t __dirfd, __WCHAR_TYPE__ const *__nodename, __mode_t __mode, __dev_t __dev) {
#if defined(__CRT_HAVE_wfmknodat) || (defined(__CRT_HAVE_fmknodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
	return (__NAMESPACE_LOCAL_SYM __localdep_wfmknodat)(__dirfd, __nodename, __mode, __dev, 0);
#else /* __CRT_HAVE_wfmknodat || (__CRT_HAVE_fmknodat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
	int __result;
	char *__utf8_nodename;
	__utf8_nodename = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__nodename);
	if __unlikely(!__utf8_nodename)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_mknodat)(__dirfd, __utf8_nodename, __mode, __dev);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_nodename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
#endif /* !__CRT_HAVE_wfmknodat && (!__CRT_HAVE_fmknodat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wmknodat_defined
#define __local___localdep_wmknodat_defined
#define __localdep_wmknodat __LIBC_LOCAL_NAME(wmknodat)
#endif /* !__local___localdep_wmknodat_defined */
#else /* __CRT_HAVE_wfmknodat || (__CRT_HAVE_fmknodat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_mknodat || __CRT_HAVE_fmknodat) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_wmknodat_defined
#endif /* !__CRT_HAVE_wfmknodat && (!__CRT_HAVE_fmknodat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) && ((!__CRT_HAVE_mknodat && !__CRT_HAVE_fmknodat) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_wmknodat_defined */
