/* HASH CRC-32:0x3f88dfa4 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fuzzy_strncasecmp_l_defined
#define __local_fuzzy_strncasecmp_l_defined 1
#include <__crt.h>
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcasecmp_l) || !defined(__NO_MALLOCA)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fuzzy_memcasecmp_l from string */
#ifndef __local___localdep_fuzzy_memcasecmp_l_defined
#define __local___localdep_fuzzy_memcasecmp_l_defined 1
#ifdef __CRT_HAVE_fuzzy_memcasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcasecmp_l,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),fuzzy_memcasecmp_l,(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_END
#include <libc/local/string/fuzzy_memcasecmp_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_memcasecmp_l __LIBC_LOCAL_NAME(fuzzy_memcasecmp_l)
#else /* ... */
#undef __local___localdep_fuzzy_memcasecmp_l_defined
#endif /* !... */
#endif /* !__local___localdep_fuzzy_memcasecmp_l_defined */
/* Dependency: strnlen from string */
#ifndef __local___localdep_strnlen_defined
#define __local___localdep_strnlen_defined 1
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),strnlen,{ return __builtin_strnlen(__string, __maxlen); })
#elif defined(__CRT_HAVE_strnlen)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),strnlen,(__string,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_strnlen __LIBC_LOCAL_NAME(strnlen)
#endif /* !... */
#endif /* !__local___localdep_strnlen_defined */
__LOCAL_LIBC(fuzzy_strncasecmp_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_strncasecmp_l))(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) {
	return __localdep_fuzzy_memcasecmp_l(__s1, __localdep_strnlen(__s1, __s1_maxlen), __s2, __localdep_strnlen(__s2, __s2_maxlen), __locale);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_strncasecmp_l_defined
#define __local___localdep_fuzzy_strncasecmp_l_defined 1
#define __localdep_fuzzy_strncasecmp_l __LIBC_LOCAL_NAME(fuzzy_strncasecmp_l)
#endif /* !__local___localdep_fuzzy_strncasecmp_l_defined */
#else /* __CRT_HAVE_fuzzy_memcasecmp_l || !__NO_MALLOCA */
#undef __local_fuzzy_strncasecmp_l_defined
#endif /* !__CRT_HAVE_fuzzy_memcasecmp_l && __NO_MALLOCA */
#endif /* !__local_fuzzy_strncasecmp_l_defined */
