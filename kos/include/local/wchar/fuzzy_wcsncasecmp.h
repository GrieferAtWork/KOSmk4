/* HASH CRC-32:0xe419c107 */
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
#ifndef __local_fuzzy_wcsncasecmp_defined
#if !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp)
#define __local_fuzzy_wcsncasecmp_defined 1
#include <parts/malloca.h>
/* Dependency: "fuzzy_wmemcasecmp" from "wchar" */
#ifndef ____localdep_fuzzy_wmemcasecmp_defined
#define ____localdep_fuzzy_wmemcasecmp_defined 1
#ifdef __CRT_HAVE_fuzzy_wmemcasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_wmemcasecmp,(__WCHAR_TYPE__ const *__s1, __SIZE_TYPE__ __s1_bytes, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
#include <local/wchar/fuzzy_wmemcasecmp.h>
#define __localdep_fuzzy_wmemcasecmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))
#else /* CUSTOM: fuzzy_wmemcasecmp */
#undef ____localdep_fuzzy_wmemcasecmp_defined
#endif /* fuzzy_wmemcasecmp... */
#endif /* !____localdep_fuzzy_wmemcasecmp_defined */

/* Dependency: "wcsnlen" from "wchar" */
#ifndef ____localdep_wcsnlen_defined
#define ____localdep_wcsnlen_defined 1
#ifdef __CRT_HAVE_wcsnlen
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#else /* LIBC: wcsnlen */
#include <local/wchar/wcsnlen.h>
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_wcsnlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))
#endif /* wcsnlen... */
#endif /* !____localdep_wcsnlen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fuzzy_wcsncasecmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))(__WCHAR_TYPE__ const *__s1,
                                                               __SIZE_TYPE__ __s1_maxlen,
                                                               __WCHAR_TYPE__ const *__s2,
                                                               __SIZE_TYPE__ __s2_maxlen) {
#line 1498 "kos/src/libc/magic/wchar.c"
	return __localdep_fuzzy_wmemcasecmp(__s1, __localdep_wcsnlen(__s1, __s1_maxlen), __s2, __localdep_wcsnlen(__s2, __s2_maxlen));
}
__NAMESPACE_LOCAL_END
#endif /* !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp) */
#endif /* !__local_fuzzy_wcsncasecmp_defined */
