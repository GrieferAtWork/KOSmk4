/* HASH CRC-32:0x3080782d */
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
#ifndef __local_wpopen_defined
#define __local_wpopen_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_popen) || defined(__CRT_HAVE__popen) || defined(__CRT_HAVE__IO_popen)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_convert_wcstombs_defined
#define __local___localdep_convert_wcstombs_defined
#ifdef __CRT_HAVE_convert_wcstombs
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
#ifndef __local___localdep_popen_defined
#define __local___localdep_popen_defined
#ifdef __CRT_HAVE_popen
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_IN_OPT(1),__FILE *,__NOTHROW_RPC,__localdep_popen,(char const *__command, char const *__modes),popen,(__command,__modes))
#elif defined(__CRT_HAVE__popen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_IN_OPT(1),__FILE *,__NOTHROW_RPC,__localdep_popen,(char const *__command, char const *__modes),_popen,(__command,__modes))
#elif defined(__CRT_HAVE__IO_popen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_IN_OPT(1),__FILE *,__NOTHROW_RPC,__localdep_popen,(char const *__command, char const *__modes),_IO_popen,(__command,__modes))
#else /* ... */
#undef __local___localdep_popen_defined
#endif /* !... */
#endif /* !__local___localdep_popen_defined */
__LOCAL_LIBC(wpopen) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __FILE *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wpopen))(__WCHAR_TYPE__ const *__command, __WCHAR_TYPE__ const *__mode) {
	__FILE *__result = __NULLPTR;
	/*utf-8*/ char *__utf8_command;
	/*utf-8*/ char *__utf8_mode;
	__utf8_command = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__command);
	if __unlikely(!__utf8_command)
		goto __done;
	__utf8_mode = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__mode);
	if __unlikely(!__utf8_mode)
		goto __done_utf8_command;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_popen)(__utf8_command, __utf8_mode);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_mode);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done_utf8_command:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_command);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done:
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wpopen_defined
#define __local___localdep_wpopen_defined
#define __localdep_wpopen __LIBC_LOCAL_NAME(wpopen)
#endif /* !__local___localdep_wpopen_defined */
#else /* (__CRT_HAVE_popen || __CRT_HAVE__popen || __CRT_HAVE__IO_popen) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_wpopen_defined
#endif /* (!__CRT_HAVE_popen && !__CRT_HAVE__popen && !__CRT_HAVE__IO_popen) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_wpopen_defined */
