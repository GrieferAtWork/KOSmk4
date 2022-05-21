/* HASH CRC-32:0x965a4cdd */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wcscasestr_defined
#define __local_wcscasestr_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcscasecmp_defined
#define __local___localdep_wcscasecmp_defined
#ifdef __CRT_HAVE_wcscasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_NCX,__localdep_wcscasecmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),_wcsicmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcscasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcscasecmp __LIBC_LOCAL_NAME(wcscasecmp)
#endif /* !... */
#endif /* !__local___localdep_wcscasecmp_defined */
__LOCAL_LIBC(wcscasestr) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcscasestr))(__WCHAR_TYPE__ const *__haystack, __WCHAR_TYPE__ const *__needle) {
	for (; *__haystack; ++__haystack) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_wcscasecmp)(__haystack, __needle) == 0)
			return (__WCHAR_TYPE__ *)__haystack;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcscasestr_defined
#define __local___localdep_wcscasestr_defined
#define __localdep_wcscasestr __LIBC_LOCAL_NAME(wcscasestr)
#endif /* !__local___localdep_wcscasestr_defined */
#endif /* !__local_wcscasestr_defined */
