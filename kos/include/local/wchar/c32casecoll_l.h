/* HASH CRC-32:0x22112640 */
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
#ifndef __local_c32casecoll_l_defined
#define __local_c32casecoll_l_defined 1
/* Dependency: "wcscasecmp_l" from "wchar" */
#ifndef ____localdep_c32casecmp_l_defined
#define ____localdep_c32casecmp_l_defined 1
#if defined(__CRT_HAVE_wcscasecmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32casecmp_l,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32casecmp_l,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32casecmp_l,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscasecmp_l.h>
#define __localdep_c32casecmp_l(s1, s2, locale) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))((__WCHAR_TYPE__ const *)(s1), (__WCHAR_TYPE__ const *)(s2), locale)
#else /* LIBC: c32casecmp_l */
#include <local/wchar/c32casecmp_l.h>
#define __localdep_c32casecmp_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32casecmp_l))
#endif /* c32casecmp_l... */
#endif /* !____localdep_c32casecmp_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32casecoll_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32casecoll_l))(__CHAR32_TYPE__ const *__s1,
                                                           __CHAR32_TYPE__ const *__s2,
                                                           __locale_t __locale) {
#line 4262 "kos/src/libc/magic/string.c"
	return __localdep_c32casecmp_l(__s1, __s2, __locale);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32casecoll_l_defined */
