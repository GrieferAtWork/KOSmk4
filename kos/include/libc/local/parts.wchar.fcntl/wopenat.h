/* HASH CRC-32:0xb6c5c343 */
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
#ifndef __local_wopenat_defined
#define __local_wopenat_defined
#include <__crt.h>
#include <asm/os/oflags.h>
#include <features.h>
#if defined(__CRT_HAVE_wopenat64) || defined(__CRT_HAVE_wopenat) || ((defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
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
#ifndef __local___localdep_openat_defined
#define __local___localdep_openat_defined
#if defined(__CRT_HAVE_openat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,__localdep_openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,__localdep_openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat)
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/openat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_openat __LIBC_LOCAL_NAME(openat)
#else /* ... */
#undef __local___localdep_openat_defined
#endif /* !... */
#endif /* !__local___localdep_openat_defined */
#ifndef __local___localdep_wopenat64_defined
#define __local___localdep_wopenat64_defined
#if defined(__CRT_HAVE_wopenat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,__localdep_wopenat64,(__fd_t __dirfd, __WCHAR_TYPE__ const *__filename, __oflag_t __oflags),wopenat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_wopenat64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,__localdep_wopenat64,(__fd_t __dirfd, __WCHAR_TYPE__ const *__filename, __oflag_t __oflags),wopenat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_wopenat) || ((defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.fcntl/wopenat64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wopenat64 __LIBC_LOCAL_NAME(wopenat64)
#else /* ... */
#undef __local___localdep_wopenat64_defined
#endif /* !... */
#endif /* !__local___localdep_wopenat64_defined */
__LOCAL_LIBC(wopenat) __ATTR_WUNUSED __ATTR_IN(2) __fd_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wopenat))(__fd_t __dirfd, __WCHAR_TYPE__ const *__filename, __oflag_t __oflags, ...) {
	__fd_t __result;
	__builtin_va_list __args;
	__mode_t __mode;
	__builtin_va_start(__args, __oflags);
	__mode = __builtin_va_arg(__args, __mode_t);
	__builtin_va_end(__args);

	__result = (__NAMESPACE_LOCAL_SYM __localdep_wopenat64)(__dirfd, __filename, __oflags, __mode);












	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wopenat_defined
#define __local___localdep_wopenat_defined
#define __localdep_wopenat __LIBC_LOCAL_NAME(wopenat)
#endif /* !__local___localdep_wopenat_defined */
#else /* __CRT_HAVE_wopenat64 || __CRT_HAVE_wopenat || ((__CRT_HAVE_openat64 || __CRT_HAVE_openat) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_wopenat_defined
#endif /* !__CRT_HAVE_wopenat64 && !__CRT_HAVE_wopenat && ((!__CRT_HAVE_openat64 && !__CRT_HAVE_openat) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_wopenat_defined */
