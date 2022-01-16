/* HASH CRC-32:0x40518087 */
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
#ifndef __local_c16toumax_l_defined
#define __local_c16toumax_l_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16toumax_defined
#define __local___localdep_c16toumax_defined
#if defined(__CRT_HAVE_wcstoumax) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoui64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou32) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toumax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstou64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16toumax __NAMESPACE_LOCAL_TYPEHAX(__UINTMAX_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),__UINTMAX_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),wcstou64)
#elif __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstou32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16toumax __NAMESPACE_LOCAL_TYPEHAX(__UINTMAX_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),__UINTMAX_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),wcstou32)
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/inttypes/wcstoumax.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16toumax __NAMESPACE_LOCAL_TYPEHAX(__UINTMAX_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),__UINTMAX_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),wcstoumax)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.inttypes/c16toumax.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16toumax __LIBC_LOCAL_NAME(c16toumax)
#endif /* !... */
#endif /* !__local___localdep_c16toumax_defined */
__LOCAL_LIBC(c16toumax_l) __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16toumax_l))(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_c16toumax)(__nptr, __endptr, __base);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16toumax_l_defined
#define __local___localdep_c16toumax_l_defined
#define __localdep_c16toumax_l __LIBC_LOCAL_NAME(c16toumax_l)
#endif /* !__local___localdep_c16toumax_l_defined */
#endif /* !__local_c16toumax_l_defined */
