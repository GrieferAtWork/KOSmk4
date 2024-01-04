/* HASH CRC-32:0x6ffaab64 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wcscasestr_defined
#define __local_wcscasestr_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcslen_defined
#define __local___localdep_wcslen_defined
#ifdef __CRT_HAVE_wcslen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __str),wcslen,(__str))
#else /* __CRT_HAVE_wcslen */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcslen __LIBC_LOCAL_NAME(wcslen)
#endif /* !__CRT_HAVE_wcslen */
#endif /* !__local___localdep_wcslen_defined */
#ifndef __local___localdep_wmemcasecmp_defined
#define __local___localdep_wmemcasecmp_defined
#ifdef __CRT_HAVE_wmemcasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wmemcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),wmemcasecmp,(__s1,__s2,__num_chars))
#else /* __CRT_HAVE_wmemcasecmp */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wmemcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wmemcasecmp __LIBC_LOCAL_NAME(wmemcasecmp)
#endif /* !__CRT_HAVE_wmemcasecmp */
#endif /* !__local___localdep_wmemcasecmp_defined */
__LOCAL_LIBC(wcscasestr) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcscasestr))(__WCHAR_TYPE__ const *__haystack, __WCHAR_TYPE__ const *__needle) {
	__SIZE_TYPE__ __needle_len = (__NAMESPACE_LOCAL_SYM __localdep_wcslen)(__needle);
	for (; *__haystack; ++__haystack) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_wmemcasecmp)(__haystack, __needle, __needle_len * sizeof(__WCHAR_TYPE__)) == 0)
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
