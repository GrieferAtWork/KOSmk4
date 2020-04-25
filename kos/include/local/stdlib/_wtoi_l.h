/* HASH CRC-32:0x9e9bed0c */
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
#ifndef __local__wtoi_l_defined
#define __local__wtoi_l_defined 1
/* Dependency: "wcstol_l" from "wchar" */
#ifndef ____localdep_wcstol_l_defined
#define ____localdep_wcstol_l_defined 1
#ifdef __CRT_HAVE_wcstol_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_wcstol_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__restrict __endptr, int __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_wcstol_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__restrict __endptr, int __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_wcstol_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__restrict __endptr, int __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: wcstol_l */
#include <local/wchar/wcstol_l.h>
#define __localdep_wcstol_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_l))
#endif /* wcstol_l... */
#endif /* !____localdep_wcstol_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wtoi_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wtoi_l))(__WCHAR_TYPE__ const *__nptr,
                                                     __locale_t __locale) {
#line 2111 "kos/src/libc/magic/stdlib.c"
	return (int)__localdep_wcstol_l(__nptr, __NULLPTR, 10, __locale);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__wtoi_l_defined */
