/* HASH CRC-32:0xaf33d1c9 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16stoul_l_defined
#define __local_c16stoul_l_defined 1
/* Dependency: "wcstoul" from "wchar" */
#ifndef ____localdep_c16stoul_defined
#define ____localdep_c16stoul_defined 1
#if defined(__CRT_HAVE_wcstoul) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG__ == 4 && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG__ == 8 && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG__ == 8 && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__ && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou32) && (__SIZEOF_LONG__ == 4)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoui64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && (__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,__localdep_c16stoul,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoul,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcstoul.h>
#define __localdep_c16stoul(nptr, endptr, base) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul))((__WCHAR_TYPE__ const *)(nptr), (__WCHAR_TYPE__ **)(endptr), base)
#else /* LIBC: c16stoul */
#include <local/wchar/c16stoul.h>
#define __localdep_c16stoul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoul))
#endif /* c16stoul... */
#endif /* !____localdep_c16stoul_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16stoul_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) unsigned long
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16stoul_l))(__CHAR16_TYPE__ const *__restrict __nptr,
                                                        __CHAR16_TYPE__ **__restrict __endptr,
                                                        int __base,
                                                        __locale_t __locale) {
#line 1631 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep_c16stoul(__nptr, __endptr, __base);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16stoul_l_defined */
