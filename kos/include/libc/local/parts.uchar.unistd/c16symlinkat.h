/* HASH CRC-32:0x92096783 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16symlinkat_defined
#define __local_c16symlinkat_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_wfsymlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wfsymlinkat) || (defined(__CRT_HAVE_fsymlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fsymlinkat) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_symlinkat) || defined(__CRT_HAVE_fsymlinkat)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16fsymlinkat_defined
#define __local___localdep_c16fsymlinkat_defined
#if defined(__CRT_HAVE_wfsymlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_c16fsymlinkat,(__CHAR16_TYPE__ const *__link_text, __fd_t __tofd, __CHAR16_TYPE__ const *__target_path, __atflag_t __flags),wfsymlinkat,(__link_text,__tofd,__target_path,__flags))
#elif defined(__CRT_HAVE_DOS$wfsymlinkat)
__CREDIRECT_DOS(__ATTR_IN(1) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_c16fsymlinkat,(__CHAR16_TYPE__ const *__link_text, __fd_t __tofd, __CHAR16_TYPE__ const *__target_path, __atflag_t __flags),wfsymlinkat,(__link_text,__tofd,__target_path,__flags))
#elif defined(__CRT_HAVE_fsymlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.unistd/wfsymlinkat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16fsymlinkat __NAMESPACE_LOCAL_TYPEHAX(int(__LIBDCALL*)(__CHAR16_TYPE__ const *,__fd_t,__CHAR16_TYPE__ const *,__atflag_t),int(__LIBDCALL&)(__CHAR16_TYPE__ const *,__fd_t,__CHAR16_TYPE__ const *,__atflag_t),wfsymlinkat)
#elif defined(__CRT_HAVE_fsymlinkat) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.unistd/c16fsymlinkat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16fsymlinkat __LIBC_LOCAL_NAME(c16fsymlinkat)
#else /* ... */
#undef __local___localdep_c16fsymlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_c16fsymlinkat_defined */
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
#ifndef __local___localdep_symlinkat_defined
#define __local___localdep_symlinkat_defined
#ifdef __CRT_HAVE_symlinkat
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_symlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path),symlinkat,(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_fsymlinkat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/symlinkat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_symlinkat __LIBC_LOCAL_NAME(symlinkat)
#else /* ... */
#undef __local___localdep_symlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_symlinkat_defined */
__LOCAL_LIBC(c16symlinkat) __ATTR_IN(1) __ATTR_IN(3) int
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16symlinkat))(__CHAR16_TYPE__ const *__link_text, __fd_t __tofd, __CHAR16_TYPE__ const *__target_path) {
#if (defined(__CRT_HAVE_wfsymlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wfsymlinkat) || (defined(__CRT_HAVE_fsymlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fsymlinkat) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
	return (__NAMESPACE_LOCAL_SYM __localdep_c16fsymlinkat)(__link_text, __tofd, __target_path, 0);
#else /* (__CRT_HAVE_wfsymlinkat && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wfsymlinkat || (__CRT_HAVE_fsymlinkat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_fsymlinkat && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
	int __result = -1;
	char *__utf8_link_text, *__utf8_target_path;
	__utf8_link_text = (__NAMESPACE_LOCAL_SYM __localdep_convert_c16tombs)(__link_text);
	if __unlikely(!__utf8_link_text)
		goto __done;
	__utf8_target_path = (__NAMESPACE_LOCAL_SYM __localdep_convert_c16tombs)(__target_path);
	if __unlikely(!__utf8_target_path)
		goto __done_from;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_symlinkat)(__utf8_link_text, __tofd, __utf8_target_path);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_target_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done_from:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_link_text);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done:
	return __result;
#endif /* (!__CRT_HAVE_wfsymlinkat || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wfsymlinkat && (!__CRT_HAVE_fsymlinkat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_fsymlinkat || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16symlinkat_defined
#define __local___localdep_c16symlinkat_defined
#define __localdep_c16symlinkat __LIBC_LOCAL_NAME(c16symlinkat)
#endif /* !__local___localdep_c16symlinkat_defined */
#else /* (__CRT_HAVE_wfsymlinkat && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wfsymlinkat || (__CRT_HAVE_fsymlinkat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_fsymlinkat && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_symlinkat || __CRT_HAVE_fsymlinkat) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_c16symlinkat_defined
#endif /* (!__CRT_HAVE_wfsymlinkat || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wfsymlinkat && (!__CRT_HAVE_fsymlinkat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_fsymlinkat || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) && ((!__CRT_HAVE_symlinkat && !__CRT_HAVE_fsymlinkat) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_c16symlinkat_defined */
