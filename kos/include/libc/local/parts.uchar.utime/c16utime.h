/* HASH CRC-32:0x63016156 */
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
#ifndef __local_c16utime_defined
#define __local_c16utime_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#if (defined(__CRT_HAVE_wutime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wutime) || (defined(__CRT_HAVE__wutime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wutime) || (defined(__CRT_HAVE__wutime32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wutime32) || (defined(__CRT_HAVE_wutime64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wutime64) || (defined(__CRT_HAVE__wutime64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wutime64) || ((defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32) || defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <hybrid/typecore.h>
#include <bits/os/utimbuf.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16utime64_defined
#define __local___localdep_c16utime64_defined
#if defined(__CRT_HAVE_wutime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c16utime64,(__CHAR16_TYPE__ const *__file, struct __utimbuf64 const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c16utime64,(__CHAR16_TYPE__ const *__file, struct __utimbuf64 const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_wutime64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c16utime64,(__CHAR16_TYPE__ const *__file, struct __utimbuf64 const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime64)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c16utime64,(__CHAR16_TYPE__ const *__file, struct __utimbuf64 const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c16utime64,(__CHAR16_TYPE__ const *__file, struct __utimbuf64 const *__file_times),_wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime64)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c16utime64,(__CHAR16_TYPE__ const *__file, struct __utimbuf64 const *__file_times),_wutime64,(__file,__file_times))
#elif ((defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64) || defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime) || defined(__CRT_HAVE__wutime32)) && __SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.utime/wutime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16utime64 __NAMESPACE_LOCAL_TYPEHAX(int(__LIBDCALL*)(__CHAR16_TYPE__ const *,struct __utimbuf64 const *),int(__LIBDCALL&)(__CHAR16_TYPE__ const *,struct __utimbuf64 const *),wutime64)
#elif ((defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64) || defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || (defined(__CRT_HAVE_wutime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wutime) || (defined(__CRT_HAVE__wutime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wutime) || (defined(__CRT_HAVE__wutime32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wutime32)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.utime/c16utime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16utime64 __LIBC_LOCAL_NAME(c16utime64)
#else /* ... */
#undef __local___localdep_c16utime64_defined
#endif /* !... */
#endif /* !__local___localdep_c16utime64_defined */
#ifndef __local___localdep_convert_c16tombs_defined
#define __local___localdep_convert_c16tombs_defined
#if defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_convert_c16tombs,(__CHAR16_TYPE__ const *__str),convert_wcstombs,(__str))
#elif defined(__CRT_HAVE_DOS$convert_wcstombs)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_convert_c16tombs,(__CHAR16_TYPE__ const *__str),convert_wcstombs,(__str))
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
#ifndef __local___localdep_crt_c16utime32_defined
#define __local___localdep_crt_c16utime32_defined
#if defined(__CRT_HAVE_wutime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__file, struct __utimbuf32 const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__file, struct __utimbuf32 const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__file, struct __utimbuf32 const *__file_times),_wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__file, struct __utimbuf32 const *__file_times),_wutime,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__file, struct __utimbuf32 const *__file_times),_wutime32,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime32)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__file, struct __utimbuf32 const *__file_times),_wutime32,(__file,__file_times))
#else /* ... */
#undef __local___localdep_crt_c16utime32_defined
#endif /* !... */
#endif /* !__local___localdep_crt_c16utime32_defined */
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
#ifndef __local___localdep_utime_defined
#define __local___localdep_utime_defined
#if defined(__CRT_HAVE_utime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_utime,(char const *__filename, struct utimbuf const *__file_times),utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___utime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_utime,(char const *__filename, struct utimbuf const *__file_times),__utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___libc_utime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_utime,(char const *__filename, struct utimbuf const *__file_times),__libc_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_utime,(char const *__filename, struct utimbuf const *__file_times),_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_utime,(char const *__filename, struct utimbuf const *__file_times),_utime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_utime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_utime,(char const *__filename, struct utimbuf const *__file_times),utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_utime,(char const *__filename, struct utimbuf const *__file_times),_utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32) || defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64)
__NAMESPACE_LOCAL_END
#include <libc/local/utime/utime.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_utime __LIBC_LOCAL_NAME(utime)
#else /* ... */
#undef __local___localdep_utime_defined
#endif /* !... */
#endif /* !__local___localdep_utime_defined */
__LOCAL_LIBC(c16utime) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16utime))(__CHAR16_TYPE__ const *__file, struct utimbuf const *__file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime
#if (defined(__CRT_HAVE_wutime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wutime) || (defined(__CRT_HAVE__wutime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wutime) || (defined(__CRT_HAVE__wutime32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wutime32)
	struct __utimbuf32 __buf32;
	if (!__file_times)
		return (__NAMESPACE_LOCAL_SYM __localdep_crt_c16utime32)(__file, __NULLPTR);
	__buf32.actime  = (__time32_t)__file_times->actime;
	__buf32.modtime = (__time32_t)__file_times->modtime;
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_c16utime32)(__file, &__buf32);
#elif (defined(__CRT_HAVE_wutime64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wutime64) || (defined(__CRT_HAVE__wutime64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wutime64)
	struct __utimbuf64 __buf64;
	if (!__file_times)
		return (__NAMESPACE_LOCAL_SYM __localdep_c16utime64)(__file, __NULLPTR);
	__buf64.actime  = (__time64_t)__file_times->actime;
	__buf64.modtime = (__time64_t)__file_times->modtime;
	return (__NAMESPACE_LOCAL_SYM __localdep_c16utime64)(__file, &__buf64);
#else /* ... */
	int __result;
	char *__utf8_file;
	__utf8_file = (__NAMESPACE_LOCAL_SYM __localdep_convert_c16tombs)(__file);
	if __unlikely(!__utf8_file)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_utime)(__utf8_file, __file_times);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_file);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
#endif /* !... */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16utime_defined
#define __local___localdep_c16utime_defined
#define __localdep_c16utime __LIBC_LOCAL_NAME(c16utime)
#endif /* !__local___localdep_c16utime_defined */
#else /* (__CRT_HAVE_wutime && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wutime || (__CRT_HAVE__wutime && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_wutime || (__CRT_HAVE__wutime32 && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_wutime32 || (__CRT_HAVE_wutime64 && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wutime64 || (__CRT_HAVE__wutime64 && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_wutime64 || ((__CRT_HAVE_utime || __CRT_HAVE___utime || __CRT_HAVE___libc_utime || __CRT_HAVE__utime || __CRT_HAVE__utime32 || __CRT_HAVE_utime64 || __CRT_HAVE__utime64) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_c16utime_defined
#endif /* (!__CRT_HAVE_wutime || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wutime && (!__CRT_HAVE__wutime || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_wutime && (!__CRT_HAVE__wutime32 || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_wutime32 && (!__CRT_HAVE_wutime64 || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wutime64 && (!__CRT_HAVE__wutime64 || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_wutime64 && ((!__CRT_HAVE_utime && !__CRT_HAVE___utime && !__CRT_HAVE___libc_utime && !__CRT_HAVE__utime && !__CRT_HAVE__utime32 && !__CRT_HAVE_utime64 && !__CRT_HAVE__utime64) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_c16utime_defined */
