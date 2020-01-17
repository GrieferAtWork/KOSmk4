/* HASH CRC-32:0xa8d1f108 */
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
#ifndef __local_c32stoll_l_defined
#define __local_c32stoll_l_defined 1
/* Dependency: "wcstoll" from "wchar" */
#ifndef ____localdep_c32stoll_defined
#define ____localdep_c32stoll_defined 1
#if defined(__CRT_HAVE_wcstoll) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_c32stoll,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_c32stoll,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_c32stoll,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8 && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_c32stoll,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8 && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_c32stoll,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4 && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_c32stoll,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__ && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_c32stoll,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, int __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcstoll.h>
#define __localdep_c32stoll(nptr, endptr, base) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))((__WCHAR_TYPE__ const *)(nptr), (__WCHAR_TYPE__ **)(endptr), base)
#else /* LIBC: c32stoll */
#include <local/wchar/c32stoll.h>
#define __localdep_c32stoll (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoll))
#endif /* c32stoll... */
#endif /* !____localdep_c32stoll_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32stoll_l) __ATTR_NONNULL((1)) __LONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32stoll_l))(__CHAR32_TYPE__ const *__restrict __nptr,
                                                        __CHAR32_TYPE__ **__endptr,
                                                        int __base,
                                                        __locale_t __locale) {
#line 1646 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep_c32stoll(__nptr, __endptr, __base);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32stoll_l_defined */
