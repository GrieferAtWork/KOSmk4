/* HASH CRC-32:0x2f784c8e */
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
#ifndef __local_wlchmod_defined
#define __local_wlchmod_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && (defined(__CRT_HAVE_wfchmodat) || (defined(__CRT_HAVE_fchmodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_lchmod) || (defined(__CRT_HAVE__chmod) && defined(__CRT_DOS_PRIMARY)) || (defined(__CRT_HAVE_chmod) && defined(__CRT_DOS_PRIMARY)) || (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && defined(__CRT_HAVE_fchmodat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
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
#ifndef __local___localdep_lchmod_defined
#define __local___localdep_lchmod_defined
#ifdef __CRT_HAVE_lchmod
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_lchmod,(char const *__filename, __mode_t __mode),lchmod,(__filename,__mode))
#elif defined(__CRT_HAVE__chmod) && defined(__CRT_DOS_PRIMARY)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_lchmod,(char const *__filename, __mode_t __mode),_chmod,(__filename,__mode))
#elif defined(__CRT_HAVE_chmod) && defined(__CRT_DOS_PRIMARY)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_lchmod,(char const *__filename, __mode_t __mode),chmod,(__filename,__mode))
#elif defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && defined(__CRT_HAVE_fchmodat)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/lchmod.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lchmod __LIBC_LOCAL_NAME(lchmod)
#else /* ... */
#undef __local___localdep_lchmod_defined
#endif /* !... */
#endif /* !__local___localdep_lchmod_defined */
#ifndef __local___localdep_wfchmodat_defined
#define __local___localdep_wfchmodat_defined
#ifdef __CRT_HAVE_wfchmodat
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_RPC,__localdep_wfchmodat,(__fd_t __dirfd, __WCHAR_TYPE__ const *__filename, __mode_t __mode, __atflag_t __flags),wfchmodat,(__dirfd,__filename,__mode,__flags))
#elif defined(__CRT_HAVE_fchmodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.sys.stat/wfchmodat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wfchmodat __LIBC_LOCAL_NAME(wfchmodat)
#else /* ... */
#undef __local___localdep_wfchmodat_defined
#endif /* !... */
#endif /* !__local___localdep_wfchmodat_defined */
__LOCAL_LIBC(wlchmod) __ATTR_IN(1) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wlchmod))(__WCHAR_TYPE__ const *__filename, __mode_t __mode) {
#if defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && (defined(__CRT_HAVE_wfchmodat) || (defined(__CRT_HAVE_fchmodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
	return (__NAMESPACE_LOCAL_SYM __localdep_wfchmodat)(__AT_FDCWD, __filename, __mode, __AT_SYMLINK_NOFOLLOW);
#else /* __AT_FDCWD && __AT_SYMLINK_NOFOLLOW && (__CRT_HAVE_wfchmodat || (__CRT_HAVE_fchmodat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
	int __result;
	char *__utf8_filename;
	__utf8_filename = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__filename);
	if __unlikely(!__utf8_filename)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_lchmod)(__utf8_filename, __mode);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
#endif /* !__AT_FDCWD || !__AT_SYMLINK_NOFOLLOW || (!__CRT_HAVE_wfchmodat && (!__CRT_HAVE_fchmodat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wlchmod_defined
#define __local___localdep_wlchmod_defined
#define __localdep_wlchmod __LIBC_LOCAL_NAME(wlchmod)
#endif /* !__local___localdep_wlchmod_defined */
#else /* (__AT_FDCWD && __AT_SYMLINK_NOFOLLOW && (__CRT_HAVE_wfchmodat || (__CRT_HAVE_fchmodat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_lchmod || (__CRT_HAVE__chmod && __CRT_DOS_PRIMARY) || (__CRT_HAVE_chmod && __CRT_DOS_PRIMARY) || (__AT_FDCWD && __AT_SYMLINK_NOFOLLOW && __CRT_HAVE_fchmodat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_wlchmod_defined
#endif /* (!__AT_FDCWD || !__AT_SYMLINK_NOFOLLOW || (!__CRT_HAVE_wfchmodat && (!__CRT_HAVE_fchmodat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))) && ((!__CRT_HAVE_lchmod && (!__CRT_HAVE__chmod || !__CRT_DOS_PRIMARY) && (!__CRT_HAVE_chmod || !__CRT_DOS_PRIMARY) && (!__AT_FDCWD || !__AT_SYMLINK_NOFOLLOW || !__CRT_HAVE_fchmodat)) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_wlchmod_defined */
