/* HASH CRC-32:0xfb46d8c5 */
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
#ifndef __local_wcscoll_defined
#define __local_wcscoll_defined 1
/* Dependency: "wcscmp" from "wchar" */
#ifndef ____localdep_wcscmp_defined
#define ____localdep_wcscmp_defined 1
#ifdef __std___localdep_wcscmp_defined
__NAMESPACE_STD_USING(__localdep_wcscmp)
#elif defined(__CRT_HAVE_wcscmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#else /* LIBC: wcscmp */
#include <local/wchar/wcscmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __localdep_wcscmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))
#endif /* wcscmp... */
#endif /* !____localdep_wcscmp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcscoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcscoll))(__WCHAR_TYPE__ const *__s1,
                                                     __WCHAR_TYPE__ const *__s2) {
#line 371 "kos/src/libc/magic/string.c"
	return __localdep_wcscmp(__s1, __s2);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcscoll_defined */
