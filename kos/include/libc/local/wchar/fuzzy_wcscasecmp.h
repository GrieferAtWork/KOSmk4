/* HASH CRC-32:0xac536c83 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fuzzy_wcscasecmp_defined
#define __local_fuzzy_wcscasecmp_defined
#include <__crt.h>
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fuzzy_wmemcasecmp_defined
#define __local___localdep_fuzzy_wmemcasecmp_defined
#ifdef __CRT_HAVE_fuzzy_wmemcasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_wmemcasecmp,(__WCHAR_TYPE__ const *__s1, __SIZE_TYPE__ __s1_bytes, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/fuzzy_wmemcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_wmemcasecmp __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp)
#else /* ... */
#undef __local___localdep_fuzzy_wmemcasecmp_defined
#endif /* !... */
#endif /* !__local___localdep_fuzzy_wmemcasecmp_defined */
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
__LOCAL_LIBC(fuzzy_wcscasecmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_wcscasecmp))(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fuzzy_wmemcasecmp)(__s1, (__NAMESPACE_LOCAL_SYM __localdep_wcslen)(__s1), __s2, (__NAMESPACE_LOCAL_SYM __localdep_wcslen)(__s2));
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_wcscasecmp_defined
#define __local___localdep_fuzzy_wcscasecmp_defined
#define __localdep_fuzzy_wcscasecmp __LIBC_LOCAL_NAME(fuzzy_wcscasecmp)
#endif /* !__local___localdep_fuzzy_wcscasecmp_defined */
#else /* __CRT_HAVE_fuzzy_wmemcasecmp || !__NO_MALLOCA */
#undef __local_fuzzy_wcscasecmp_defined
#endif /* !__CRT_HAVE_fuzzy_wmemcasecmp && __NO_MALLOCA */
#endif /* !__local_fuzzy_wcscasecmp_defined */
