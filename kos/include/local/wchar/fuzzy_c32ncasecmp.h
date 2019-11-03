/* HASH CRC-32:0xb5fcc179 */
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
#ifndef __local_fuzzy_c32ncasecmp_defined
#if (!defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp))
#define __local_fuzzy_c32ncasecmp_defined 1
#include <parts/malloca.h>
/* Dependency: "fuzzy_wmemcasecmp" from "wchar" */
#ifndef ____localdep_fuzzy_c32memcasecmp_defined
#define ____localdep_fuzzy_c32memcasecmp_defined 1
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_c32memcasecmp,(__CHAR32_TYPE__ const *__s1, __SIZE_TYPE__ __s1_bytes, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fuzzy_wmemcasecmp.h>
#define __localdep_fuzzy_c32memcasecmp(s1, s1_bytes, s2, s2_bytes) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))((__WCHAR_TYPE__ const *)(s1), s1_bytes, (__WCHAR_TYPE__ const *)(s2), s2_bytes)
#else /* LIBC: fuzzy_c32memcasecmp */
#include <local/wchar/fuzzy_c32memcasecmp.h>
#define __localdep_fuzzy_c32memcasecmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_c32memcasecmp))
#endif /* LIBC: fuzzy_c32memcasecmp */
#else /* CUSTOM: fuzzy_wmemcasecmp */
#undef ____localdep_fuzzy_c32memcasecmp_defined
#endif /* fuzzy_c32memcasecmp... */
#endif /* !____localdep_fuzzy_c32memcasecmp_defined */

/* Dependency: "wcsnlen" from "wchar" */
#ifndef ____localdep_c32nlen_defined
#define ____localdep_c32nlen_defined 1
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32nlen,(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnlen.h>
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c32nlen(string, maxlen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)(string), maxlen)
#else /* LIBC: c32nlen */
#include <local/wchar/c32nlen.h>
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c32nlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nlen))
#endif /* c32nlen... */
#endif /* !____localdep_c32nlen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fuzzy_c32ncasecmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_c32ncasecmp))(__CHAR32_TYPE__ const *__s1,
                                                               __SIZE_TYPE__ __s1_maxlen,
                                                               __CHAR32_TYPE__ const *__s2,
                                                               __SIZE_TYPE__ __s2_maxlen) {
#line 1406 "kos/src/libc/magic/wchar.c"
	return __localdep_fuzzy_c32memcasecmp(__s1, __localdep_c32nlen(__s1, __s1_maxlen), __s2, __localdep_c32nlen(__s2, __s2_maxlen));
}
__NAMESPACE_LOCAL_END
#endif /* (!defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp)) */
#endif /* !__local_fuzzy_c32ncasecmp_defined */
