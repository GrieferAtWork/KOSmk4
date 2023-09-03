/* HASH CRC-32:0xf18b69ab */
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
#ifndef __local_c32utimensat64_defined
#define __local_c32utimensat64_defined
#include <__crt.h>
#include <bits/types.h>
#if ((defined(__CRT_HAVE_utimensat64) || defined(__CRT_HAVE___utimensat64) || defined(__CRT_HAVE_utimensat)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || (defined(__CRT_HAVE_wutimensat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wutimensat)
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_crt_c32utimensat32_defined
#define __local___localdep_crt_c32utimensat32_defined
#if defined(__CRT_HAVE_wutimensat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_IN(2) __ATTR_IN_OPT(3),int,__NOTHROW_RPC,__localdep_crt_c32utimensat32,(__fd_t __dirfd, __CHAR32_TYPE__ const *__filename, struct __timespec32 const __times[2 /*or:3*/], __atflag_t __flags),wutimensat,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_KOS$wutimensat)
__CREDIRECT_KOS(__ATTR_IN(2) __ATTR_IN_OPT(3),int,__NOTHROW_RPC,__localdep_crt_c32utimensat32,(__fd_t __dirfd, __CHAR32_TYPE__ const *__filename, struct __timespec32 const __times[2 /*or:3*/], __atflag_t __flags),wutimensat,(__dirfd,__filename,__times,__flags))
#else /* ... */
#undef __local___localdep_crt_c32utimensat32_defined
#endif /* !... */
#endif /* !__local___localdep_crt_c32utimensat32_defined */
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
#ifndef __local___localdep_utimensat64_defined
#define __local___localdep_utimensat64_defined
#if defined(__CRT_HAVE_utimensat) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_IN_OPT(3),int,__NOTHROW_RPC,__localdep_utimensat64,(__fd_t __dirfd, char const *__filename, struct __timespec64 const __times[2 /*or:3*/], __atflag_t __flags),utimensat,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_utimensat64)
__CREDIRECT(__ATTR_IN(2) __ATTR_IN_OPT(3),int,__NOTHROW_RPC,__localdep_utimensat64,(__fd_t __dirfd, char const *__filename, struct __timespec64 const __times[2 /*or:3*/], __atflag_t __flags),utimensat64,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE___utimensat64)
__CREDIRECT(__ATTR_IN(2) __ATTR_IN_OPT(3),int,__NOTHROW_RPC,__localdep_utimensat64,(__fd_t __dirfd, char const *__filename, struct __timespec64 const __times[2 /*or:3*/], __atflag_t __flags),__utimensat64,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_utimensat)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/utimensat64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_utimensat64 __LIBC_LOCAL_NAME(utimensat64)
#else /* ... */
#undef __local___localdep_utimensat64_defined
#endif /* !... */
#endif /* !__local___localdep_utimensat64_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32utimensat64) __ATTR_IN(2) __ATTR_IN_OPT(3) int
__NOTHROW_RPC(__LIBKCALL __LIBC_LOCAL_NAME(c32utimensat64))(__fd_t __dirfd, __CHAR32_TYPE__ const *__filename, struct __timespec64 const __times[2 /*or:3*/], __atflag_t __flags) {
#if (defined(__CRT_HAVE_utimensat64) || defined(__CRT_HAVE___utimensat64) || defined(__CRT_HAVE_utimensat)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
	int __result;
	char *__utf8_filename;
	__utf8_filename = (__NAMESPACE_LOCAL_SYM __localdep_convert_c32tombs)(__filename);
	if __unlikely(!__utf8_filename)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_utimensat64)(__dirfd, __utf8_filename, __times, __flags);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
#else /* (__CRT_HAVE_utimensat64 || __CRT_HAVE___utimensat64 || __CRT_HAVE_utimensat) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#ifdef __AT_CHANGE_BTIME
	struct __timespec32 __tms[3];
	if (!__times)
		return (__NAMESPACE_LOCAL_SYM __localdep_crt_c32utimensat32)(__dirfd, __filename, __NULLPTR, __flags);
	__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	if (__flags & __AT_CHANGE_BTIME) {
		__tms[2].tv_sec  = (__time32_t)__times[2].tv_sec;
		__tms[2].tv_nsec = __times[2].tv_nsec;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_c32utimensat32)(__dirfd, __filename, __tms, __flags);
#else /* __AT_CHANGE_BTIME */
	struct __timespec32 __tms[2];
	if (!__times)
		return (__NAMESPACE_LOCAL_SYM __localdep_crt_c32utimensat32)(__dirfd, __filename, __NULLPTR, __flags);
	__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_c32utimensat32)(__dirfd, __filename, __tms, __flags);
#endif /* !__AT_CHANGE_BTIME */
#endif /* (!__CRT_HAVE_utimensat64 && !__CRT_HAVE___utimensat64 && !__CRT_HAVE_utimensat) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32utimensat64_defined
#define __local___localdep_c32utimensat64_defined
#define __localdep_c32utimensat64 __LIBC_LOCAL_NAME(c32utimensat64)
#endif /* !__local___localdep_c32utimensat64_defined */
#else /* ((__CRT_HAVE_utimensat64 || __CRT_HAVE___utimensat64 || __CRT_HAVE_utimensat) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || (__CRT_HAVE_wutimensat && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wutimensat */
#undef __local_c32utimensat64_defined
#endif /* ((!__CRT_HAVE_utimensat64 && !__CRT_HAVE___utimensat64 && !__CRT_HAVE_utimensat) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) && (!__CRT_HAVE_wutimensat || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wutimensat */
#endif /* !__local_c32utimensat64_defined */
