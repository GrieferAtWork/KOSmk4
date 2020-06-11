/* HASH CRC-32:0xd6f2f13c */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16toll_defined
#define __local_c16toll_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16sto32 from parts.uchar.stdlib */
#ifndef __local___localdep_c16sto32_defined
#define __local___localdep_c16sto32_defined 1
#if defined(__CRT_HAVE_wcsto32) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16sto32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto32)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c16sto32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && (__SIZEOF_LONG__ == 4) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16sto32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol) && (__SIZEOF_LONG__ == 4)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c16sto32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && (__SIZEOF_LONG_LONG__ == 4) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16sto32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c16sto32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && (__SIZEOF_LONG_LONG__ == 4) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16sto32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c16sto32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && (__SIZEOF_INTMAX_T__ == 4) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16sto32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c16sto32,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoimax,(__nptr,__endptr,__base))
#elif (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsto32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16sto32 (*(__INT32_TYPE__(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict, __CHAR16_TYPE__ **, int))&__LIBC_LOCAL_NAME(wcsto32))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.stdlib/c16sto32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16sto32 __LIBC_LOCAL_NAME(c16sto32)
#endif /* !... */
#endif /* !__local___localdep_c16sto32_defined */
/* Dependency: c16sto64 from parts.uchar.stdlib */
#ifndef __local___localdep_c16sto64_defined
#define __local___localdep_c16sto64_defined 1
#if defined(__CRT_HAVE_wcsto64) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16sto64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoi64)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c16sto64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && (__SIZEOF_LONG__ == 8) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16sto64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol) && (__SIZEOF_LONG__ == 8)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c16sto64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && (__SIZEOF_LONG_LONG__ == 8) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16sto64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c16sto64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && (__SIZEOF_LONG_LONG__ == 8) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16sto64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c16sto64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && (__SIZEOF_INTMAX_T__ == 8) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_c16sto64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c16sto64,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoimax,(__nptr,__endptr,__base))
#elif (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsto64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16sto64 (*(__INT64_TYPE__(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict, __CHAR16_TYPE__ **, int))&__LIBC_LOCAL_NAME(wcsto64))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.stdlib/c16sto64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16sto64 __LIBC_LOCAL_NAME(c16sto64)
#endif /* !... */
#endif /* !__local___localdep_c16sto64_defined */
__LOCAL_LIBC(c16toll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16toll))(__CHAR16_TYPE__ const *__nptr) {
#if __SIZEOF_LONG_LONG__
	return (__LONGLONG)__localdep_c16sto32(__nptr, __NULLPTR, 10);
#else /* __SIZEOF_LONG_LONG__ */
	return (__LONGLONG)__localdep_c16sto64(__nptr, __NULLPTR, 10);
#endif /* !__SIZEOF_LONG_LONG__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16toll_defined
#define __local___localdep_c16toll_defined 1
#define __localdep_c16toll __LIBC_LOCAL_NAME(c16toll)
#endif /* !__local___localdep_c16toll_defined */
#endif /* !__local_c16toll_defined */
