/* HASH CRC-32:0xcf1e0457 */
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
#ifndef __local_fuzzy_wcsncmp_defined
#if (!defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcmp))
#define __local_fuzzy_wcsncmp_defined 1
#include <parts/malloca.h>
/* Dependency: "fuzzy_wmemcmp" from "wchar" */
#ifndef ____localdep_fuzzy_wmemcmp_defined
#define ____localdep_fuzzy_wmemcmp_defined 1
#if defined(__CRT_HAVE_fuzzy_wmemcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_wmemcmp,(__WCHAR_TYPE__ const *__s1, __SIZE_TYPE__ __s1_chars, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_wmemcmp,(__s1,__s1_chars,__s2,__s2_chars))
#elif !defined(__NO_MALLOCA)
#include <local/wchar/fuzzy_wmemcmp.h>
#define __localdep_fuzzy_wmemcmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcmp))
#else /* CUSTOM: fuzzy_wmemcmp */
#undef ____localdep_fuzzy_wmemcmp_defined
#endif /* fuzzy_wmemcmp... */
#endif /* !____localdep_fuzzy_wmemcmp_defined */

/* Dependency: "wcsnlen" from "wchar" */
#ifndef ____localdep_wcsnlen_defined
#define ____localdep_wcsnlen_defined 1
#if defined(__CRT_HAVE_wcsnlen)
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#else /* LIBC: wcsnlen */
#include <local/wchar/wcsnlen.h>
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_wcsnlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))
#endif /* wcsnlen... */
#endif /* !____localdep_wcsnlen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fuzzy_wcsncmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_wcsncmp))(__WCHAR_TYPE__ const *__s1,
                                                           __SIZE_TYPE__ __s1_maxlen,
                                                           __WCHAR_TYPE__ const *__s2,
                                                           __SIZE_TYPE__ __s2_maxlen) {
#line 1381 "kos/src/libc/magic/wchar.c"
	return __localdep_fuzzy_wmemcmp(__s1, __localdep_wcsnlen(__s1, __s1_maxlen), __s2, __localdep_wcsnlen(__s2, __s2_maxlen));
}
__NAMESPACE_LOCAL_END
#endif /* (!defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcmp)) */
#endif /* !__local_fuzzy_wcsncmp_defined */
