/* HASH CRC-32:0xe8a4fc94 */
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
#ifndef __local_fuzzy_wcscasecmp_l_defined
#if !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp_l)
#define __local_fuzzy_wcscasecmp_l_defined 1
#include <__crt.h>
#include <parts/malloca.h>
/* Dependency: "fuzzy_wmemcasecmp_l" from "wchar" */
#ifndef ____localdep_fuzzy_wmemcasecmp_l_defined
#define ____localdep_fuzzy_wmemcasecmp_l_defined 1
#ifdef __CRT_HAVE_fuzzy_wmemcasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_wmemcasecmp_l,(__WCHAR_TYPE__ const *__s1, __SIZE_TYPE__ __s1_bytes, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_wmemcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif !defined(__NO_MALLOCA)
#include <local/wchar/fuzzy_wmemcasecmp_l.h>
#define __localdep_fuzzy_wmemcasecmp_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))
#else /* CUSTOM: fuzzy_wmemcasecmp_l */
#undef ____localdep_fuzzy_wmemcasecmp_l_defined
#endif /* fuzzy_wmemcasecmp_l... */
#endif /* !____localdep_fuzzy_wmemcasecmp_l_defined */

/* Dependency: "wcslen" from "wchar" */
#ifndef ____localdep_wcslen_defined
#define ____localdep_wcslen_defined 1
#ifdef __std___localdep_wcslen_defined
__NAMESPACE_STD_USING(__localdep_wcslen)
#elif defined(__CRT_HAVE_wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __string),wcslen,(__string))
#else /* LIBC: wcslen */
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_wcslen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))
#endif /* wcslen... */
#endif /* !____localdep_wcslen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fuzzy_wcscasecmp_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_wcscasecmp_l))(__WCHAR_TYPE__ const *__s1,
                                                                __WCHAR_TYPE__ const *__s2,
                                                                __locale_t __locale) {
#line 1607 "kos/src/libc/magic/wchar.c"
	return __localdep_fuzzy_wmemcasecmp_l(__s1, __localdep_wcslen(__s1), __s2, __localdep_wcslen(__s2), __locale);
}
__NAMESPACE_LOCAL_END
#endif /* !__NO_MALLOCA || __CRT_HAVE_fuzzy_wmemcasecmp_l */
#endif /* !__local_fuzzy_wcscasecmp_l_defined */
