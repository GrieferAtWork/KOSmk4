/* HASH CRC-32:0x8121d54b */
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
#ifndef __local_wsymlink_defined
#define __local_wsymlink_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wsymlinkat) || defined(__CRT_HAVE_wfsymlinkat) || (defined(__CRT_HAVE_fsymlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_symlinkat) || defined(__CRT_HAVE_fsymlinkat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_symlink) || defined(__CRT_HAVE___symlink) || defined(__CRT_HAVE___libc_symlink) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_symlinkat) || defined(__CRT_HAVE_fsymlinkat)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
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
#ifndef __local___localdep_symlink_defined
#define __local___localdep_symlink_defined
#ifdef __CRT_HAVE_symlink
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,__localdep_symlink,(char const *__link_text, char const *__target_path),symlink,(__link_text,__target_path))
#elif defined(__CRT_HAVE___symlink)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,__localdep_symlink,(char const *__link_text, char const *__target_path),__symlink,(__link_text,__target_path))
#elif defined(__CRT_HAVE___libc_symlink)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,__localdep_symlink,(char const *__link_text, char const *__target_path),__libc_symlink,(__link_text,__target_path))
#elif defined(__AT_FDCWD) && (defined(__CRT_HAVE_symlinkat) || defined(__CRT_HAVE_fsymlinkat))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/symlink.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_symlink __LIBC_LOCAL_NAME(symlink)
#else /* ... */
#undef __local___localdep_symlink_defined
#endif /* !... */
#endif /* !__local___localdep_symlink_defined */
#ifndef __local___localdep_wfsymlinkat_defined
#define __local___localdep_wfsymlinkat_defined
#ifdef __CRT_HAVE_wfsymlinkat
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(3),int,__NOTHROW_RPC,__localdep_wfsymlinkat,(__WCHAR_TYPE__ const *__link_text, __fd_t __tofd, __WCHAR_TYPE__ const *__target_path, __atflag_t __flags),wfsymlinkat,(__link_text,__tofd,__target_path,__flags))
#elif defined(__CRT_HAVE_fsymlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.unistd/wfsymlinkat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wfsymlinkat __LIBC_LOCAL_NAME(wfsymlinkat)
#else /* ... */
#undef __local___localdep_wfsymlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_wfsymlinkat_defined */
#ifndef __local___localdep_wsymlinkat_defined
#define __local___localdep_wsymlinkat_defined
#ifdef __CRT_HAVE_wsymlinkat
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(3),int,__NOTHROW_RPC,__localdep_wsymlinkat,(__WCHAR_TYPE__ const *__link_text, __fd_t __tofd, __WCHAR_TYPE__ const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_wfsymlinkat) || (defined(__CRT_HAVE_fsymlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_symlinkat) || defined(__CRT_HAVE_fsymlinkat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.unistd/wsymlinkat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wsymlinkat __LIBC_LOCAL_NAME(wsymlinkat)
#else /* ... */
#undef __local___localdep_wsymlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_wsymlinkat_defined */
__LOCAL_LIBC(wsymlink) __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wsymlink))(__WCHAR_TYPE__ const *__link_text, __WCHAR_TYPE__ const *__target_path) {
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_wfsymlinkat) || (defined(__CRT_HAVE_fsymlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
	return (__NAMESPACE_LOCAL_SYM __localdep_wfsymlinkat)(__link_text, __AT_FDCWD, __target_path, 0);
#elif defined(__AT_FDCWD) && (defined(__CRT_HAVE_wsymlinkat) || defined(__CRT_HAVE_wfsymlinkat) || (defined(__CRT_HAVE_fsymlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_symlinkat) || defined(__CRT_HAVE_fsymlinkat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
	return (__NAMESPACE_LOCAL_SYM __localdep_wsymlinkat)(__link_text, __AT_FDCWD, __target_path);
#else /* ... */
	int __result = -1;
	char *__utf8_link_text, *__utf8_target_path;
	__utf8_link_text = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__link_text);
	if __unlikely(!__utf8_link_text)
		goto __done;
	__utf8_target_path = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__target_path);
	if __unlikely(!__utf8_target_path)
		goto __done_from;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_symlink)(__utf8_link_text, __utf8_target_path);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_target_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done_from:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_link_text);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done:
	return __result;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wsymlink_defined
#define __local___localdep_wsymlink_defined
#define __localdep_wsymlink __LIBC_LOCAL_NAME(wsymlink)
#endif /* !__local___localdep_wsymlink_defined */
#else /* (__AT_FDCWD && (__CRT_HAVE_wsymlinkat || __CRT_HAVE_wfsymlinkat || (__CRT_HAVE_fsymlinkat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_symlinkat || __CRT_HAVE_fsymlinkat) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_symlink || __CRT_HAVE___symlink || __CRT_HAVE___libc_symlink || (__AT_FDCWD && (__CRT_HAVE_symlinkat || __CRT_HAVE_fsymlinkat))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_wsymlink_defined
#endif /* (!__AT_FDCWD || (!__CRT_HAVE_wsymlinkat && !__CRT_HAVE_wfsymlinkat && (!__CRT_HAVE_fsymlinkat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) && ((!__CRT_HAVE_symlinkat && !__CRT_HAVE_fsymlinkat) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))) && ((!__CRT_HAVE_symlink && !__CRT_HAVE___symlink && !__CRT_HAVE___libc_symlink && (!__AT_FDCWD || (!__CRT_HAVE_symlinkat && !__CRT_HAVE_fsymlinkat))) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_wsymlink_defined */
