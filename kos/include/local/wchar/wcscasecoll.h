/* HASH CRC-32:0x990c2114 */
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
#ifndef __local_wcscasecoll_defined
#define __local_wcscasecoll_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wcscasecmp from wchar */
#ifndef __local___localdep_wcscasecmp_defined
#define __local___localdep_wcscasecmp_defined 1
#ifdef __CRT_HAVE_wcscasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicmp) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicmp) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcsicmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wchar/wcscasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcscasecmp __LIBC_LOCAL_NAME(wcscasecmp)
#endif /* !... */
#endif /* !__local___localdep_wcscasecmp_defined */
__LOCAL_LIBC(wcscasecoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcscasecoll))(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2) {
	return __localdep_wcscasecmp(__s1, __s2);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcscasecoll_defined
#define __local___localdep_wcscasecoll_defined 1
#define __localdep_wcscasecoll __LIBC_LOCAL_NAME(wcscasecoll)
#endif /* !__local___localdep_wcscasecoll_defined */
#endif /* !__local_wcscasecoll_defined */
