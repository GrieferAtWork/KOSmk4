/* HASH CRC-32:0x1b243a4 */
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
#ifndef __local_wlchown_defined
#define __local_wlchown_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && (defined(__CRT_HAVE_wfchownat) || (defined(__CRT_HAVE_fchownat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_lchown) || (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && defined(__CRT_HAVE_fchownat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
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
#ifndef __local___localdep_lchown_defined
#define __local___localdep_lchown_defined
#ifdef __CRT_HAVE_lchown
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_lchown,(char const *__file, __uid_t __owner, __gid_t __group),lchown,(__file,__owner,__group))
#elif defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && defined(__CRT_HAVE_fchownat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/lchown.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lchown __LIBC_LOCAL_NAME(lchown)
#else /* ... */
#undef __local___localdep_lchown_defined
#endif /* !... */
#endif /* !__local___localdep_lchown_defined */
#ifndef __local___localdep_wfchownat_defined
#define __local___localdep_wfchownat_defined
#ifdef __CRT_HAVE_wfchownat
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_RPC,__localdep_wfchownat,(__fd_t __dfd, __WCHAR_TYPE__ const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_fchownat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.unistd/wfchownat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wfchownat __LIBC_LOCAL_NAME(wfchownat)
#else /* ... */
#undef __local___localdep_wfchownat_defined
#endif /* !... */
#endif /* !__local___localdep_wfchownat_defined */
__LOCAL_LIBC(wlchown) __ATTR_IN(1) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wlchown))(__WCHAR_TYPE__ const *__file, __uid_t __owner, __gid_t __group) {
#if defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && (defined(__CRT_HAVE_wfchownat) || (defined(__CRT_HAVE_fchownat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
	return (__NAMESPACE_LOCAL_SYM __localdep_wfchownat)(__AT_FDCWD, __file, __owner, __group, __AT_SYMLINK_NOFOLLOW);
#else /* __AT_FDCWD && __AT_SYMLINK_NOFOLLOW && (__CRT_HAVE_wfchownat || (__CRT_HAVE_fchownat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
	int __result;
	char *__utf8_file;
	__utf8_file = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__file);
	if __unlikely(!__utf8_file)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_lchown)(__utf8_file, __owner, __group);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_file);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
#endif /* !__AT_FDCWD || !__AT_SYMLINK_NOFOLLOW || (!__CRT_HAVE_wfchownat && (!__CRT_HAVE_fchownat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wlchown_defined
#define __local___localdep_wlchown_defined
#define __localdep_wlchown __LIBC_LOCAL_NAME(wlchown)
#endif /* !__local___localdep_wlchown_defined */
#else /* (__AT_FDCWD && __AT_SYMLINK_NOFOLLOW && (__CRT_HAVE_wfchownat || (__CRT_HAVE_fchownat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_lchown || (__AT_FDCWD && __AT_SYMLINK_NOFOLLOW && __CRT_HAVE_fchownat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_wlchown_defined
#endif /* (!__AT_FDCWD || !__AT_SYMLINK_NOFOLLOW || (!__CRT_HAVE_wfchownat && (!__CRT_HAVE_fchownat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))) && ((!__CRT_HAVE_lchown && (!__AT_FDCWD || !__AT_SYMLINK_NOFOLLOW || !__CRT_HAVE_fchownat)) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_wlchown_defined */
