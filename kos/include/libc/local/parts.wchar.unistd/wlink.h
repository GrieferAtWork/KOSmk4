/* HASH CRC-32:0x4e3019e8 */
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
#ifndef __local_wlink_defined
#define __local_wlink_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wlinkat) || ((defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_linkat)))) || ((defined(__CRT_HAVE_link) || defined(__CRT_HAVE___link) || defined(__CRT_HAVE___libc_link) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_linkat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_convert_wcstombs_defined
#define __local___localdep_convert_wcstombs_defined
#ifdef __CRT_HAVE_convert_wcstombs
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
#ifndef __local___localdep_link_defined
#define __local___localdep_link_defined
#ifdef __CRT_HAVE_link
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,__localdep_link,(char const *__from, char const *__to),link,(__from,__to))
#elif defined(__CRT_HAVE___link)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,__localdep_link,(char const *__from, char const *__to),__link,(__from,__to))
#elif defined(__CRT_HAVE___libc_link)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,__localdep_link,(char const *__from, char const *__to),__libc_link,(__from,__to))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_linkat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/link.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_link __LIBC_LOCAL_NAME(link)
#else /* ... */
#undef __local___localdep_link_defined
#endif /* !... */
#endif /* !__local___localdep_link_defined */
#ifndef __local___localdep_wlinkat_defined
#define __local___localdep_wlinkat_defined
#ifdef __CRT_HAVE_wlinkat
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO(4),int,__NOTHROW_RPC,__localdep_wlinkat,(__fd_t __fromfd, __WCHAR_TYPE__ const *__from, __fd_t __tofd, __WCHAR_TYPE__ const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#elif (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_linkat)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.unistd/wlinkat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wlinkat __LIBC_LOCAL_NAME(wlinkat)
#else /* ... */
#undef __local___localdep_wlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_wlinkat_defined */
__LOCAL_LIBC(wlink) __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wlink))(__WCHAR_TYPE__ const *__from, __WCHAR_TYPE__ const *__to) {
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_wlinkat) || ((defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_linkat)))
	return (__NAMESPACE_LOCAL_SYM __localdep_wlinkat)(__AT_FDCWD, __from, __AT_FDCWD, __to, 0);
#else /* __AT_FDCWD && (__CRT_HAVE_wlinkat || ((__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __CRT_HAVE_linkat)) */
	int __result = -1;
	char *__utf8_from, *__utf8_to;
	__utf8_from = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__from);
	if __unlikely(!__utf8_from)
		goto __done;
	__utf8_to = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__to);
	if __unlikely(!__utf8_to)
		goto __done_from;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_link)(__utf8_from, __utf8_to);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_to);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done_from:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_from);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done:
	return __result;
#endif /* !__AT_FDCWD || (!__CRT_HAVE_wlinkat && ((!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || !__CRT_HAVE_linkat)) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wlink_defined
#define __local___localdep_wlink_defined
#define __localdep_wlink __LIBC_LOCAL_NAME(wlink)
#endif /* !__local___localdep_wlink_defined */
#else /* (__AT_FDCWD && (__CRT_HAVE_wlinkat || ((__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __CRT_HAVE_linkat))) || ((__CRT_HAVE_link || __CRT_HAVE___link || __CRT_HAVE___libc_link || (__AT_FDCWD && __CRT_HAVE_linkat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_wlink_defined
#endif /* (!__AT_FDCWD || (!__CRT_HAVE_wlinkat && ((!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || !__CRT_HAVE_linkat))) && ((!__CRT_HAVE_link && !__CRT_HAVE___link && !__CRT_HAVE___libc_link && (!__AT_FDCWD || !__CRT_HAVE_linkat)) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_wlink_defined */
