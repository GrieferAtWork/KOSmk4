/* HASH CRC-32:0x9fe21247 */
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
#ifndef __local_wrename_defined
#define __local_wrename_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wrenameat) || defined(__CRT_HAVE_wrenameat2) || (defined(__CRT_HAVE_renameat2) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
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
#ifndef __local___localdep_rename_defined
#define __local___localdep_rename_defined
#ifdef __CRT_HAVE_rename
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,__localdep_rename,(char const *__oldname, char const *__newname_or_path),rename,(__oldname,__newname_or_path))
#elif defined(__CRT_HAVE___rename)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,__localdep_rename,(char const *__oldname, char const *__newname_or_path),__rename,(__oldname,__newname_or_path))
#elif defined(__CRT_HAVE___libc_rename)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,__localdep_rename,(char const *__oldname, char const *__newname_or_path),__libc_rename,(__oldname,__newname_or_path))
#elif defined(__AT_FDCWD) && (defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/rename.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rename __LIBC_LOCAL_NAME(rename)
#else /* ... */
#undef __local___localdep_rename_defined
#endif /* !... */
#endif /* !__local___localdep_rename_defined */
#ifndef __local___localdep_wrenameat_defined
#define __local___localdep_wrenameat_defined
#ifdef __CRT_HAVE_wrenameat
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO(4),int,__NOTHROW_RPC,__localdep_wrenameat,(__fd_t __oldfd, __WCHAR_TYPE__ const *__oldname, __fd_t __newfd, __WCHAR_TYPE__ const *__newname_or_path),wrenameat,(__oldfd,__oldname,__newfd,__newname_or_path))
#elif defined(__CRT_HAVE_wrenameat2) || (defined(__CRT_HAVE_renameat2) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.stdio/wrenameat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wrenameat __LIBC_LOCAL_NAME(wrenameat)
#else /* ... */
#undef __local___localdep_wrenameat_defined
#endif /* !... */
#endif /* !__local___localdep_wrenameat_defined */
__LOCAL_LIBC(wrename) __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wrename))(__WCHAR_TYPE__ const *__oldname, __WCHAR_TYPE__ const *__newname_or_path) {
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_wrenameat) || defined(__CRT_HAVE_wrenameat2) || (defined(__CRT_HAVE_renameat2) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
	return (__NAMESPACE_LOCAL_SYM __localdep_wrenameat)(__AT_FDCWD, __oldname, __AT_FDCWD, __newname_or_path);
#else /* __AT_FDCWD && (__CRT_HAVE_wrenameat || __CRT_HAVE_wrenameat2 || (__CRT_HAVE_renameat2 && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_renameat || __CRT_HAVE_renameat2) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
	char *__utf8_oldname;
	char *__utf8_newname_or_path;
	int __result;
	__utf8_oldname = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__oldname);
	if __unlikely(!__utf8_oldname)
		return -1;
	__utf8_newname_or_path = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__newname_or_path);
	if __unlikely(!__utf8_newname_or_path) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		return -1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_rename)(__utf8_oldname, __utf8_newname_or_path);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_newname_or_path);
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_oldname);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
#endif /* !__AT_FDCWD || (!__CRT_HAVE_wrenameat && !__CRT_HAVE_wrenameat2 && (!__CRT_HAVE_renameat2 || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) && ((!__CRT_HAVE_renameat && !__CRT_HAVE_renameat2) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wrename_defined
#define __local___localdep_wrename_defined
#define __localdep_wrename __LIBC_LOCAL_NAME(wrename)
#endif /* !__local___localdep_wrename_defined */
#else /* (__AT_FDCWD && (__CRT_HAVE_wrenameat || __CRT_HAVE_wrenameat2 || (__CRT_HAVE_renameat2 && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_renameat || __CRT_HAVE_renameat2) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_wrename_defined
#endif /* (!__AT_FDCWD || (!__CRT_HAVE_wrenameat && !__CRT_HAVE_wrenameat2 && (!__CRT_HAVE_renameat2 || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))) && ((!__CRT_HAVE_renameat && !__CRT_HAVE_renameat2) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_wrename_defined */
