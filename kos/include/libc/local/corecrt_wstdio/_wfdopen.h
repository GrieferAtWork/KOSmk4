/* HASH CRC-32:0x60fa881a */
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
#ifndef __local__wfdopen_defined
#define __local__wfdopen_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_fdopen) || defined(__CRT_HAVE__fdopen) || defined(__CRT_HAVE__IO_fdopen)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
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
#ifndef __local___localdep_fdopen_defined
#define __local___localdep_fdopen_defined
#ifdef __CRT_HAVE_fdopen
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__FILE *,__NOTHROW_NCX,__localdep_fdopen,(__fd_t __fd, char const *__restrict __modes),fdopen,(__fd,__modes))
#elif defined(__CRT_HAVE__fdopen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__FILE *,__NOTHROW_NCX,__localdep_fdopen,(__fd_t __fd, char const *__restrict __modes),_fdopen,(__fd,__modes))
#elif defined(__CRT_HAVE__IO_fdopen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__FILE *,__NOTHROW_NCX,__localdep_fdopen,(__fd_t __fd, char const *__restrict __modes),_IO_fdopen,(__fd,__modes))
#else /* ... */
#undef __local___localdep_fdopen_defined
#endif /* !... */
#endif /* !__local___localdep_fdopen_defined */
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
__LOCAL_LIBC(_wfdopen) __ATTR_WUNUSED __ATTR_IN(2) __FILE *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wfdopen))(__fd_t __fd, __WCHAR_TYPE__ const *__mode) {
	__FILE *__result = __NULLPTR;
	char *__utf8_mode;
	__utf8_mode = (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombs)(__mode);
	if __unlikely(!__utf8_mode)
		goto __done;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_fdopen)(__fd, __utf8_mode);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_mode);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done:
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wfdopen_defined
#define __local___localdep__wfdopen_defined
#define __localdep__wfdopen __LIBC_LOCAL_NAME(_wfdopen)
#endif /* !__local___localdep__wfdopen_defined */
#else /* (__CRT_HAVE_fdopen || __CRT_HAVE__fdopen || __CRT_HAVE__IO_fdopen) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local__wfdopen_defined
#endif /* (!__CRT_HAVE_fdopen && !__CRT_HAVE__fdopen && !__CRT_HAVE__IO_fdopen) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local__wfdopen_defined */
