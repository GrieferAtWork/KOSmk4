/* HASH CRC-32:0x8d400601 */
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
#ifndef __local_c16remove_defined
#define __local_c16remove_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#include <asm/os/errno.h>
#if (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wremoveat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wremoveat) || ((defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR))))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || ((defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR))))) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_remove) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR)))))) || (defined(__EISDIR) && defined(__ENOTDIR) && (defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))) && (defined(__CRT_HAVE_rmdir) || defined(__CRT_HAVE__rmdir) || defined(__CRT_HAVE___rmdir) || defined(__CRT_HAVE___libc_rmdir) || (defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat))))) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16removeat_defined
#define __local___localdep_c16removeat_defined
#if defined(__CRT_HAVE_wremoveat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_RPC,__localdep_c16removeat,(__fd_t __dirfd, __CHAR16_TYPE__ const *__filename),wremoveat,(__dirfd,__filename))
#elif defined(__CRT_HAVE_DOS$wremoveat)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_IN(2),int,__NOTHROW_RPC,__localdep_c16removeat,(__fd_t __dirfd, __CHAR16_TYPE__ const *__filename),wremoveat,(__dirfd,__filename))
#elif (defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR))))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.stdio/wremoveat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16removeat __NAMESPACE_LOCAL_TYPEHAX(int(__LIBDCALL*)(__fd_t,__CHAR16_TYPE__ const *),int(__LIBDCALL&)(__fd_t,__CHAR16_TYPE__ const *),wremoveat)
#elif (defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR))))) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdio/c16removeat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16removeat __LIBC_LOCAL_NAME(c16removeat)
#else /* ... */
#undef __local___localdep_c16removeat_defined
#endif /* !... */
#endif /* !__local___localdep_c16removeat_defined */
#ifndef __local___localdep_convert_c16tombs_defined
#define __local___localdep_convert_c16tombs_defined
#if defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char *,__NOTHROW_NCX,__localdep_convert_c16tombs,(__CHAR16_TYPE__ const *__str),convert_wcstombs,(__str))
#elif defined(__CRT_HAVE_DOS$convert_wcstombs)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char *,__NOTHROW_NCX,__localdep_convert_c16tombs,(__CHAR16_TYPE__ const *__str),convert_wcstombs,(__str))
#elif (defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_wcstombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c16tombs __NAMESPACE_LOCAL_TYPEHAX(char *(__LIBDCALL*)(__CHAR16_TYPE__ const *),char *(__LIBDCALL&)(__CHAR16_TYPE__ const *),convert_wcstombs)
#elif (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_c16tombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c16tombs __LIBC_LOCAL_NAME(convert_c16tombs)
#else /* ... */
#undef __local___localdep_convert_c16tombs_defined
#endif /* !... */
#endif /* !__local___localdep_convert_c16tombs_defined */
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
#ifndef __local___localdep_remove_defined
#define __local___localdep_remove_defined
#ifdef __CRT_HAVE_remove
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_remove,(char const *__filename),remove,(__filename))
#elif (defined(__AT_FDCWD) && (defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR)))))) || (defined(__EISDIR) && defined(__ENOTDIR) && (defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))) && (defined(__CRT_HAVE_rmdir) || defined(__CRT_HAVE__rmdir) || defined(__CRT_HAVE___rmdir) || defined(__CRT_HAVE___libc_rmdir) || (defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat))))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/remove.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_remove __LIBC_LOCAL_NAME(remove)
#else /* ... */
#undef __local___localdep_remove_defined
#endif /* !... */
#endif /* !__local___localdep_remove_defined */
__LOCAL_LIBC(c16remove) __ATTR_IN(1) int
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16remove))(__CHAR16_TYPE__ const *__filename) {
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wremoveat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wremoveat) || ((defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR))))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || ((defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR))))) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
	return (__NAMESPACE_LOCAL_SYM __localdep_c16removeat)(__AT_FDCWD, __filename);
#else /* __AT_FDCWD && ((__CRT_HAVE_wremoveat && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wremoveat || ((__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR)))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || ((__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR)))) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
	char *__utf8_filename;
	int __result;
	__utf8_filename = (__NAMESPACE_LOCAL_SYM __localdep_convert_c16tombs)(__filename);
	if __unlikely(!__utf8_filename)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_remove)(__utf8_filename);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
#endif /* !__AT_FDCWD || ((!__CRT_HAVE_wremoveat || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wremoveat && ((!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR)))) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && ((!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR)))) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16remove_defined
#define __local___localdep_c16remove_defined
#define __localdep_c16remove __LIBC_LOCAL_NAME(c16remove)
#endif /* !__local___localdep_c16remove_defined */
#else /* (__AT_FDCWD && ((__CRT_HAVE_wremoveat && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wremoveat || ((__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR)))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || ((__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR)))) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_remove || (__AT_FDCWD && (__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR))))) || (__EISDIR && __ENOTDIR && (__CRT_HAVE_unlink || __CRT_HAVE__unlink || __CRT_HAVE___unlink || __CRT_HAVE___libc_unlink || (__AT_FDCWD && __CRT_HAVE_unlinkat)) && (__CRT_HAVE_rmdir || __CRT_HAVE__rmdir || __CRT_HAVE___rmdir || __CRT_HAVE___libc_rmdir || (__AT_FDCWD && __AT_REMOVEDIR && __CRT_HAVE_unlinkat)))) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_c16remove_defined
#endif /* (!__AT_FDCWD || ((!__CRT_HAVE_wremoveat || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wremoveat && ((!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR)))) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && ((!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR)))) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))) && ((!__CRT_HAVE_remove && (!__AT_FDCWD || (!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR))))) && (!__EISDIR || !__ENOTDIR || (!__CRT_HAVE_unlink && !__CRT_HAVE__unlink && !__CRT_HAVE___unlink && !__CRT_HAVE___libc_unlink && (!__AT_FDCWD || !__CRT_HAVE_unlinkat)) || (!__CRT_HAVE_rmdir && !__CRT_HAVE__rmdir && !__CRT_HAVE___rmdir && !__CRT_HAVE___libc_rmdir && (!__AT_FDCWD || !__AT_REMOVEDIR || !__CRT_HAVE_unlinkat)))) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_c16remove_defined */
