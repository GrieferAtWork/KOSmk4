/* HASH CRC-32:0x4079f658 */
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
#ifndef __local_c32coll_defined
#define __local_c32coll_defined 1
/* Dependency: "wcscmp" from "wchar" */
#ifndef ____localdep_c32cmp_defined
#define ____localdep_c32cmp_defined 1
#if defined(__CRT_HAVE_wcscmp) && (__SIZEOF_WCHAR_T__ == 4)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32cmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __localdep_c32cmp(s1, s2) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))((__WCHAR_TYPE__ const *)(s1), (__WCHAR_TYPE__ const *)(s2))
#else /* LIBC: c32cmp */
#include <local/wchar/c32cmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __localdep_c32cmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cmp))
#endif /* c32cmp... */
#endif /* !____localdep_c32cmp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32coll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32coll))(__CHAR32_TYPE__ const *__s1,
                                                     __CHAR32_TYPE__ const *__s2) {
#line 401 "kos/src/libc/magic/string.c"
	return __localdep_c32cmp(__s1, __s2);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32coll_defined */
