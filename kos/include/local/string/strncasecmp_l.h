/* HASH CRC-32:0x2a2fc313 */
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
#ifndef __local_strncasecmp_l_defined
#define __local_strncasecmp_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strncasecmp from string */
#ifndef __local___localdep_strncasecmp_defined
#define __local___localdep_strncasecmp_defined 1
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/strncasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strncasecmp __LIBC_LOCAL_NAME(strncasecmp)
#endif /* !... */
#endif /* !__local___localdep_strncasecmp_defined */
__LOCAL_LIBC(strncasecmp_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strncasecmp_l))(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) {
	(void)__locale;
	return __localdep_strncasecmp(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strncasecmp_l_defined
#define __local___localdep_strncasecmp_l_defined 1
#define __localdep_strncasecmp_l __LIBC_LOCAL_NAME(strncasecmp_l)
#endif /* !__local___localdep_strncasecmp_l_defined */
#endif /* !__local_strncasecmp_l_defined */
