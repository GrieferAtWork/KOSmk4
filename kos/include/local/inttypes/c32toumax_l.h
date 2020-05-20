/* HASH CRC-32:0xf6af1384 */
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
#ifndef __local_c32toumax_l_defined
#define __local_c32toumax_l_defined 1
#include <__crt.h>
/* Dependency: "wcstoumax" from "inttypes" */
#ifndef ____localdep_c32toumax_defined
#define ____localdep_c32toumax_defined 1
#if defined(__CRT_HAVE_wcstoumax) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_c32toumax,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcstou32,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/inttypes/wcstoumax.h>
#define __localdep_c32toumax (*(__UINTMAX_TYPE__(__LIBCCALL*)(__CHAR32_TYPE__ const *__restrict, __CHAR32_TYPE__ **, int))&(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoumax)))
#else /* LIBC: c32toumax */
#include <local/inttypes/c32toumax.h>
#define __localdep_c32toumax (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32toumax))
#endif /* c32toumax... */
#endif /* !____localdep_c32toumax_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32toumax_l) __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32toumax_l))(__CHAR32_TYPE__ const *__restrict __nptr,
                                                         __CHAR32_TYPE__ **__endptr,
                                                         int __base,
                                                         __locale_t __locale) {
#line 625 "kos/src/libc/magic/inttypes.c"
	(void)__locale;
	return __localdep_c32toumax(__nptr, __endptr, __base);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32toumax_l_defined */
