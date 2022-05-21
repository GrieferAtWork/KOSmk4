/* HASH CRC-32:0x7af2a1b7 */
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
#ifndef _PARTS_UCHAR_INTTYPES_H
#define _PARTS_UCHAR_INTTYPES_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _INTTYPES_H
#include <inttypes.h>
#endif /* !_INTTYPES_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#include <hybrid/typecore.h>

#ifdef __CC__
__SYSDECL_BEGIN

#if defined(__CRT_HAVE_wcstoimax) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoi64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto32) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toimax)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#elif __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toimax)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/inttypes/wcstoimax.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toimax)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoimax))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.inttypes/c16toimax.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16toimax, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toimax)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16toimax))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoimax) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoi64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto32) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toimax)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#elif __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toimax)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/inttypes/wcstoimax.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toimax)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoimax))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.inttypes/c32toimax.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32toimax, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toimax)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32toimax))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoumax) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoui64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou32) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toumax)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#elif __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toumax)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/inttypes/wcstoumax.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toumax)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoumax))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.inttypes/c16toumax.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16toumax, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toumax)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16toumax))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoumax) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoui64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou32) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toumax)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#elif __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toumax)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/inttypes/wcstoumax.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toumax)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoumax))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.inttypes/c32toumax.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32toumax, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toumax)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32toumax))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoimax_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoimax_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcsto64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoi64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto32_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcsto32_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c16toimax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toimax_l)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#elif __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toimax_l)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/inttypes/wcstoimax_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toimax_l)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoimax_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.inttypes/c16toimax_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16toimax_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toimax_l)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16toimax_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoimax_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoimax_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcsto64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoi64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto32_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcsto32_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,c32toimax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toimax_l)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#elif __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toimax_l)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/inttypes/wcstoimax_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toimax_l)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoimax_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.inttypes/c32toimax_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32toimax_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toimax_l)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32toimax_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoumax_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoumax_l)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstou64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoui64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou32_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstou32_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c16toumax_l,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toumax_l)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#elif __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toumax_l)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/inttypes/wcstoumax_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toumax_l)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoumax_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.inttypes/c16toumax_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16toumax_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBDCALL c16toumax_l)(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16toumax_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoumax_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoumax_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstou64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoui64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou32_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstou32_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__UINTMAX_TYPE__,__NOTHROW_NCX,c32toumax_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toumax_l)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#elif __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toumax_l)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/inttypes/wcstoumax_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toumax_l)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoumax_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.inttypes/c32toumax_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32toumax_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBKCALL c32toumax_l)(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32toumax_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_UCHAR_INTTYPES_H */
