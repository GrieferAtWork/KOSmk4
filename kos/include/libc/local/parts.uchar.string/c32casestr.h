/* HASH CRC-32:0xb7756f6a */
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
#ifndef __local_c32casestr_defined
#define __local_c32casestr_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32casecmp_defined
#define __local___localdep_c32casecmp_defined
#if defined(__CRT_HAVE_wcscasecmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_NCX,__localdep_c32casecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscasecmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_NCX,__localdep_c32casecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_NCX,__localdep_c32casecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$_wcsicmp)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_NCX,__localdep_c32casecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),_wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcscasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32casecmp __NAMESPACE_LOCAL_TYPEHAX(int(__LIBKCALL*)(__CHAR32_TYPE__ const *,__CHAR32_TYPE__ const *),int(__LIBKCALL&)(__CHAR32_TYPE__ const *,__CHAR32_TYPE__ const *),wcscasecmp)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32casecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32casecmp __LIBC_LOCAL_NAME(c32casecmp)
#endif /* !... */
#endif /* !__local___localdep_c32casecmp_defined */
__LOCAL_LIBC(c32casestr) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32casestr))(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__needle) {
	for (; *__haystack; ++__haystack) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_c32casecmp)(__haystack, __needle) == 0)
			return (__CHAR32_TYPE__ *)__haystack;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32casestr_defined
#define __local___localdep_c32casestr_defined
#define __localdep_c32casestr __LIBC_LOCAL_NAME(c32casestr)
#endif /* !__local___localdep_c32casestr_defined */
#endif /* !__local_c32casestr_defined */
