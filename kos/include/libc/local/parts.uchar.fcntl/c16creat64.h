/* HASH CRC-32:0x7d713694 */
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
#ifndef __local_c16creat64_defined
#define __local_c16creat64_defined
#include <__crt.h>
#include <asm/os/oflags.h>
#if (defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && ((defined(__CRT_HAVE_wopen64) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)) || defined(__CRT_HAVE_DOS$wopen64) || defined(__CRT_HAVE_wopen) || defined(__CRT_HAVE__wopen) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$wopen) || defined(__CRT_HAVE_DOS$_wopen) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || (((defined(__CRT_HAVE_creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE__creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE___creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE___libc_creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_creat64) || (defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)))) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16open64_defined
#define __local___localdep_c16open64_defined
#if defined(__CRT_HAVE_wopen) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__COMPILER_CVREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__VLIBDCALL,__localdep_c16open64,(__CHAR16_TYPE__ const *__filename, __oflag_t __oflags),wopen,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_DOS$wopen) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT_DOS(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_c16open64,(__CHAR16_TYPE__ const *__filename, __oflag_t __oflags),wopen,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__wopen) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__COMPILER_CVREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__VLIBDCALL,__localdep_c16open64,(__CHAR16_TYPE__ const *__filename, __oflag_t __oflags),_wopen,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_DOS$_wopen) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT_DOS(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_c16open64,(__CHAR16_TYPE__ const *__filename, __oflag_t __oflags),_wopen,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_wopen64) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__COMPILER_CVREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__VLIBDCALL,__localdep_c16open64,(__CHAR16_TYPE__ const *__filename, __oflag_t __oflags),wopen64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_DOS$wopen64)
__CVREDIRECT_DOS(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_c16open64,(__CHAR16_TYPE__ const *__filename, __oflag_t __oflags),wopen64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_wopen) || defined(__CRT_HAVE__wopen) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.fcntl/wopen64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16open64 __NAMESPACE_LOCAL_TYPEHAX(__fd_t(__VLIBDCALL*)(__CHAR16_TYPE__ const *,__oflag_t,...),__fd_t(__VLIBDCALL&)(__CHAR16_TYPE__ const *,__oflag_t,...),wopen64)
#elif defined(__CRT_HAVE_DOS$wopen) || defined(__CRT_HAVE_DOS$_wopen) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.fcntl/c16open64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16open64 __LIBC_LOCAL_NAME(c16open64)
#else /* ... */
#undef __local___localdep_c16open64_defined
#endif /* !... */
#endif /* !__local___localdep_c16open64_defined */
#ifndef __local___localdep_convert_c16tombs_defined
#define __local___localdep_convert_c16tombs_defined
#if defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char *,__NOTHROW_NCX,__localdep_convert_c16tombs,(__CHAR16_TYPE__ const *__str),convert_wcstombs,(__str))
#elif defined(__CRT_HAVE_DOS$convert_wcstombs)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_creat64_defined
#define __local___localdep_creat64_defined
#if defined(__CRT_HAVE_creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_creat64,(char const *__filename, __mode_t __mode),creat,(__filename,__mode))
#elif defined(__CRT_HAVE__creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_creat64,(char const *__filename, __mode_t __mode),_creat,(__filename,__mode))
#elif defined(__CRT_HAVE___creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_creat64,(char const *__filename, __mode_t __mode),__creat,(__filename,__mode))
#elif defined(__CRT_HAVE___libc_creat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_creat64,(char const *__filename, __mode_t __mode),__libc_creat,(__filename,__mode))
#elif defined(__CRT_HAVE_creat64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_creat64,(char const *__filename, __mode_t __mode),creat64,(__filename,__mode))
#elif defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open))
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/creat64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_creat64 __LIBC_LOCAL_NAME(creat64)
#else /* ... */
#undef __local___localdep_creat64_defined
#endif /* !... */
#endif /* !__local___localdep_creat64_defined */
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
__LOCAL_LIBC(c16creat64) __ATTR_WUNUSED __ATTR_IN(1) __fd_t
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16creat64))(__CHAR16_TYPE__ const *__filename, __mode_t __mode) {
#if defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && ((defined(__CRT_HAVE_wopen64) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)) || defined(__CRT_HAVE_DOS$wopen64) || defined(__CRT_HAVE_wopen) || defined(__CRT_HAVE__wopen) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$wopen) || defined(__CRT_HAVE_DOS$_wopen) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
	return (__NAMESPACE_LOCAL_SYM __localdep_c16open64)(__filename, __O_CREAT | __O_WRONLY | __O_TRUNC, __mode);
#else /* __O_CREAT && __O_WRONLY && __O_TRUNC && ((__CRT_HAVE_wopen64 && __SIZEOF_WCHAR_T__ == 2 && __VLIBCCALL_IS_VLIBDCALL) || __CRT_HAVE_DOS$wopen64 || __CRT_HAVE_wopen || __CRT_HAVE__wopen || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$wopen || __CRT_HAVE_DOS$_wopen || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
	__fd_t __result;
	char *__utf8_filename;
	__utf8_filename = (__NAMESPACE_LOCAL_SYM __localdep_convert_c16tombs)(__filename);
	if __unlikely(!__utf8_filename)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_creat64)(__utf8_filename, __mode);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
#endif /* !__O_CREAT || !__O_WRONLY || !__O_TRUNC || ((!__CRT_HAVE_wopen64 || __SIZEOF_WCHAR_T__ != 2 || !__VLIBCCALL_IS_VLIBDCALL) && !__CRT_HAVE_DOS$wopen64 && !__CRT_HAVE_wopen && !__CRT_HAVE__wopen && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$wopen && !__CRT_HAVE_DOS$_wopen && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16creat64_defined
#define __local___localdep_c16creat64_defined
#define __localdep_c16creat64 __LIBC_LOCAL_NAME(c16creat64)
#endif /* !__local___localdep_c16creat64_defined */
#else /* (__O_CREAT && __O_WRONLY && __O_TRUNC && ((__CRT_HAVE_wopen64 && __SIZEOF_WCHAR_T__ == 2 && __VLIBCCALL_IS_VLIBDCALL) || __CRT_HAVE_DOS$wopen64 || __CRT_HAVE_wopen || __CRT_HAVE__wopen || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$wopen || __CRT_HAVE_DOS$_wopen || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || (((__CRT_HAVE_creat && (!__O_LARGEFILE || !__O_LARGEFILE)) || (__CRT_HAVE__creat && (!__O_LARGEFILE || !__O_LARGEFILE)) || (__CRT_HAVE___creat && (!__O_LARGEFILE || !__O_LARGEFILE)) || (__CRT_HAVE___libc_creat && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_creat64 || (__O_CREAT && __O_WRONLY && __O_TRUNC && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open))) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_c16creat64_defined
#endif /* (!__O_CREAT || !__O_WRONLY || !__O_TRUNC || ((!__CRT_HAVE_wopen64 || __SIZEOF_WCHAR_T__ != 2 || !__VLIBCCALL_IS_VLIBDCALL) && !__CRT_HAVE_DOS$wopen64 && !__CRT_HAVE_wopen && !__CRT_HAVE__wopen && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$wopen && !__CRT_HAVE_DOS$_wopen && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))) && (((!__CRT_HAVE_creat || (__O_LARGEFILE && __O_LARGEFILE)) && (!__CRT_HAVE__creat || (__O_LARGEFILE && __O_LARGEFILE)) && (!__CRT_HAVE___creat || (__O_LARGEFILE && __O_LARGEFILE)) && (!__CRT_HAVE___libc_creat || (__O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_creat64 && (!__O_CREAT || !__O_WRONLY || !__O_TRUNC || (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open))) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_c16creat64_defined */
