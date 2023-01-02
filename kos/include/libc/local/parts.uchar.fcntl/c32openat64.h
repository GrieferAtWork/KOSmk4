/* HASH CRC-32:0x4ab2d9b6 */
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
#ifndef __local_c32openat64_defined
#define __local_c32openat64_defined
#include <__crt.h>
#include <asm/os/oflags.h>
#if (defined(__CRT_HAVE_wopenat) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)) || defined(__CRT_HAVE_KOS$wopenat) || ((defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32openat_defined
#define __local___localdep_c32openat_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_wopenat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__COMPILER_CVREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,__VLIBKCALL,__localdep_c32openat,(__fd_t __dirfd, __CHAR32_TYPE__ const *__filename, __oflag_t __oflags),wopenat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_KOS$wopenat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT_KOS(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,__localdep_c32openat,(__fd_t __dirfd, __CHAR32_TYPE__ const *__filename, __oflag_t __oflags),wopenat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_wopenat64) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__COMPILER_CVREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,__VLIBKCALL,__localdep_c32openat,(__fd_t __dirfd, __CHAR32_TYPE__ const *__filename, __oflag_t __oflags),wopenat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_KOS$wopenat64)
__CVREDIRECT_KOS(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,__localdep_c32openat,(__fd_t __dirfd, __CHAR32_TYPE__ const *__filename, __oflag_t __oflags),wopenat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_wopenat64) || defined(__CRT_HAVE_wopenat) || ((defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.fcntl/wopenat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32openat __NAMESPACE_LOCAL_TYPEHAX(__fd_t(__VLIBKCALL*)(__fd_t,__CHAR32_TYPE__ const *,__oflag_t,...),__fd_t(__VLIBKCALL&)(__fd_t,__CHAR32_TYPE__ const *,__oflag_t,...),wopenat)
#elif defined(__CRT_HAVE_KOS$wopenat) || ((defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.fcntl/c32openat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32openat __LIBC_LOCAL_NAME(c32openat)
#else /* ... */
#undef __local___localdep_c32openat_defined
#endif /* !... */
#endif /* !__local___localdep_c32openat_defined */
#ifndef __local___localdep_c32openat32_defined
#define __local___localdep_c32openat32_defined
#if defined(__CRT_HAVE_wopenat) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__COMPILER_CVREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,__VLIBKCALL,__localdep_c32openat32,(__fd_t __dirfd, __CHAR32_TYPE__ const *__filename, __oflag_t __oflags),wopenat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_KOS$wopenat)
__CVREDIRECT_KOS(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,__localdep_c32openat32,(__fd_t __dirfd, __CHAR32_TYPE__ const *__filename, __oflag_t __oflags),wopenat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#else /* ... */
#undef __local___localdep_c32openat32_defined
#endif /* !... */
#endif /* !__local___localdep_c32openat32_defined */
#ifndef __local___localdep_convert_c32tombs_defined
#define __local___localdep_convert_c32tombs_defined
#if defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char *,__NOTHROW_NCX,__localdep_convert_c32tombs,(__CHAR32_TYPE__ const *__str),convert_wcstombs,(__str))
#elif defined(__CRT_HAVE_KOS$convert_wcstombs)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),char *,__NOTHROW_NCX,__localdep_convert_c32tombs,(__CHAR32_TYPE__ const *__str),convert_wcstombs,(__str))
#elif (defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_wcstombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c32tombs __NAMESPACE_LOCAL_TYPEHAX(char *(__LIBKCALL*)(__CHAR32_TYPE__ const *),char *(__LIBKCALL&)(__CHAR32_TYPE__ const *),convert_wcstombs)
#elif (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_c32tombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c32tombs __LIBC_LOCAL_NAME(convert_c32tombs)
#else /* ... */
#undef __local___localdep_convert_c32tombs_defined
#endif /* !... */
#endif /* !__local___localdep_convert_c32tombs_defined */
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
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
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
__LOCAL_LIBC(c32openat64) __ATTR_WUNUSED __ATTR_IN(2) __fd_t
__NOTHROW_RPC(__VLIBKCALL __LIBC_LOCAL_NAME(c32openat64))(__fd_t __dirfd, __CHAR32_TYPE__ const *__filename, __oflag_t __oflags, ...) {
	__fd_t __result;
	__builtin_va_list __args;
	__mode_t __mode;
	__builtin_va_start(__args, __oflags);
	__mode = __builtin_va_arg(__args, __mode_t);
	__builtin_va_end(__args);


#if (defined(__CRT_HAVE_wopenat) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)) || defined(__CRT_HAVE_KOS$wopenat)
#ifdef __O_LARGEFILE
	__result = (__NAMESPACE_LOCAL_SYM __localdep_c32openat32)(__dirfd, __filename, __oflags | __O_LARGEFILE, __mode);
#else /* __O_LARGEFILE */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_c32openat32)(__dirfd, __filename, __oflags, __mode);
#endif /* !__O_LARGEFILE */
#else /* (__CRT_HAVE_wopenat && __SIZEOF_WCHAR_T__ == 4 && __VLIBCCALL_IS_VLIBKCALL) || __CRT_HAVE_KOS$wopenat */
	{
		char *__utf8_filename;
		__utf8_filename = (__NAMESPACE_LOCAL_SYM __localdep_convert_c32tombs)(__filename);
		if __unlikely(!__utf8_filename)
			return -1;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_openat)(__dirfd, __utf8_filename, __oflags, __mode);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	}
#endif /* (!__CRT_HAVE_wopenat || __SIZEOF_WCHAR_T__ != 4 || !__VLIBCCALL_IS_VLIBKCALL) && !__CRT_HAVE_KOS$wopenat */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32openat64_defined
#define __local___localdep_c32openat64_defined
#define __localdep_c32openat64 __LIBC_LOCAL_NAME(c32openat64)
#endif /* !__local___localdep_c32openat64_defined */
#else /* (__CRT_HAVE_wopenat && __SIZEOF_WCHAR_T__ == 4 && __VLIBCCALL_IS_VLIBKCALL) || __CRT_HAVE_KOS$wopenat || ((__CRT_HAVE_openat64 || __CRT_HAVE_openat) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_c32openat64_defined
#endif /* (!__CRT_HAVE_wopenat || __SIZEOF_WCHAR_T__ != 4 || !__VLIBCCALL_IS_VLIBKCALL) && !__CRT_HAVE_KOS$wopenat && ((!__CRT_HAVE_openat64 && !__CRT_HAVE_openat) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_c32openat64_defined */
