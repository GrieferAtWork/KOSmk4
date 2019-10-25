/* HASH CRC-32:0x5ad8ce45 */
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
#ifndef __local_fuzzy_strncasecmp_l_defined
#if !defined(__NO_MALLOCA)
#define __local_fuzzy_strncasecmp_l_defined 1
#include <parts/malloca.h>
/* Dependency: "fuzzy_memcasecmp_l" from "string" */
#ifndef ____localdep_fuzzy_memcasecmp_l_defined
#define ____localdep_fuzzy_memcasecmp_l_defined 1
#if defined(__CRT_HAVE_fuzzy_memcasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcasecmp_l,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_memcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_memcasecmp_l.h>
#define __localdep_fuzzy_memcasecmp_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcasecmp_l))
#else /* CUSTOM: fuzzy_memcasecmp_l */
#undef ____localdep_fuzzy_memcasecmp_l_defined
#endif /* fuzzy_memcasecmp_l... */
#endif /* !____localdep_fuzzy_memcasecmp_l_defined */

/* Dependency: "strnlen" from "string" */
#ifndef ____localdep_strnlen_defined
#define ____localdep_strnlen_defined 1
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL __localdep_strnlen)(char const *__restrict __string, __SIZE_TYPE__ __maxlen) { return __builtin_strnlen(__string, __maxlen); }
#elif defined(__CRT_HAVE_strnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),strnlen,(__string,__maxlen))
#else /* LIBC: strnlen */
#include <local/string/strnlen.h>
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_strnlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlen))
#endif /* strnlen... */
#endif /* !____localdep_strnlen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fuzzy_strncasecmp_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_strncasecmp_l))(char const *__s1,
                                                                 __SIZE_TYPE__ __s1_maxlen,
                                                                 char const *__s2,
                                                                 __SIZE_TYPE__ __s2_maxlen,
                                                                 __locale_t __locale) {
#line 3802 "kos/src/libc/magic/string.c"
	return __localdep_fuzzy_memcasecmp_l(__s1, __localdep_strnlen(__s1, __s1_maxlen), __s2, __localdep_strnlen(__s2, __s2_maxlen), __locale);
}
__NAMESPACE_LOCAL_END
#endif /* !defined(__NO_MALLOCA) */
#endif /* !__local_fuzzy_strncasecmp_l_defined */
