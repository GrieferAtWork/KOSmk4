/* HASH CRC-32:0xbbca3896 */
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
#ifndef __local_fuzzy_strcasecmp_l_defined
#if !defined(__NO_MALLOCA)
#define __local_fuzzy_strcasecmp_l_defined 1
#include <parts/malloca.h>
/* Dependency: "fuzzy_memcasecmp_l" from "string" */
#ifndef ____localdep_fuzzy_memcasecmp_l_defined
#define ____localdep_fuzzy_memcasecmp_l_defined 1
#if defined(__CRT_HAVE_fuzzy_memcasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcasecmp_l,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_memcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_memcasecmp_l.h>
#define __localdep_fuzzy_memcasecmp_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcasecmp_l))
#else /* CUSTOM: fuzzy_memcasecmp_l */
#undef ____localdep_fuzzy_memcasecmp_l_defined
#endif /* fuzzy_memcasecmp_l... */
#endif /* !____localdep_fuzzy_memcasecmp_l_defined */

/* Dependency: "strlen" from "string" */
#ifndef ____localdep_strlen_defined
#define ____localdep_strlen_defined 1
#if defined(__CRT_HAVE_strlen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#endif /* !____localdep_strlen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fuzzy_strcasecmp_l) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_strcasecmp_l))(char const *__s1,
                                                                char const *__s2,
                                                                __locale_t __locale) {
#line 3912 "kos/src/libc/magic/string.c"
	return __localdep_fuzzy_memcasecmp_l(__s1, __localdep_strlen(__s1), __s2, __localdep_strlen(__s2), __locale);
}
__NAMESPACE_LOCAL_END
#endif /* !defined(__NO_MALLOCA) */
#endif /* !__local_fuzzy_strcasecmp_l_defined */
