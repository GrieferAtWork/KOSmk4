/* HASH CRC-32:0xeff2f45d */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef __local_c16stol_l_defined
#define __local_c16stol_l_defined 1
/* Dependency: "wcstol" from "wchar" */
#ifndef ____localdep_c16stol_defined
#define ____localdep_c16stol_defined 1
#if defined(__CRT_HAVE_wcstol) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && (__SIZEOF_WCHAR_T__ == 2))
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && (__SIZEOF_WCHAR_T__ == 2))
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && (__SIZEOF_LONG__ == 4 && (__SIZEOF_WCHAR_T__ == 2))
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && (__SIZEOF_LONG__ == 8 && (__SIZEOF_WCHAR_T__ == 2))
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && (__SIZEOF_LONG__ == 8 && (__SIZEOF_WCHAR_T__ == 2))
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && (__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__ && (__SIZEOF_WCHAR_T__ == 2))
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto32) && (__SIZEOF_LONG__ == 4)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoi64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && (__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_c16stol,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, int __base),wcstol,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcstol.h>
#define __localdep_c16stol(nptr, endptr, base) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol))((__WCHAR_TYPE__ const *)(nptr), (__WCHAR_TYPE__ **)(endptr), base)
#else /* LIBC: c16stol */
#include <local/wchar/c16stol.h>
#define __localdep_c16stol (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stol))
#endif /* c16stol... */
#endif /* !____localdep_c16stol_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16stol_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c16stol_l))(__CHAR16_TYPE__ const *__restrict __nptr,
                                                       __CHAR16_TYPE__ **__restrict __endptr,
                                                       int __base,
                                                       __locale_t __locale) {
#line 1378 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep_c16stol(__nptr, __endptr, __base);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16stol_l_defined */
