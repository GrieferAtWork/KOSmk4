/* HASH CRC-32:0xffa9a4e3 */
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
#ifndef __local_wcscasestr_defined
#define __local_wcscasestr_defined 1
/* Dependency: "wcscasecmp" from "wchar" */
#ifndef ____localdep_wcscasecmp_defined
#define ____localdep_wcscasecmp_defined 1
#ifdef __CRT_HAVE_wcscasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),wcsicmp,(__s1,__s2))
#else /* LIBC: wcscasecmp */
#include <local/wchar/wcscasecmp.h>
#define __localdep_wcscasecmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))
#endif /* wcscasecmp... */
#endif /* !____localdep_wcscasecmp_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `wcsstr', but ignore casing */
__LOCAL_LIBC(wcscasestr) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcscasestr))(__WCHAR_TYPE__ const *__haystack,
                                                        __WCHAR_TYPE__ const *__needle) {
#line 629 "kos/src/libc/magic/string.c"
	for (; *__haystack; ++__haystack) {
		if (__localdep_wcscasecmp(__haystack, __needle) == 0)
			return (__WCHAR_TYPE__ *)__haystack;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcscasestr_defined */
