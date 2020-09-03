/* HASH CRC-32:0x5d3672f2 */
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
#ifndef __local_strcasecoll_l_defined
#define __local_strcasecoll_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strcasecmp_l from string */
#ifndef __local___localdep_strcasecmp_l_defined
#define __local___localdep_strcasecmp_l_defined 1
#ifdef __CRT_HAVE_strcasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),strcasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),_stricmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___strcasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),__strcasecmp_l,(__s1,__s2,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcasecmp_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcasecmp_l __LIBC_LOCAL_NAME(strcasecmp_l)
#endif /* !... */
#endif /* !__local___localdep_strcasecmp_l_defined */
__LOCAL_LIBC(strcasecoll_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strcasecoll_l))(char const *__s1, char const *__s2, __locale_t __locale) {
	return __localdep_strcasecmp_l(__s1, __s2, __locale);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strcasecoll_l_defined
#define __local___localdep_strcasecoll_l_defined 1
#define __localdep_strcasecoll_l __LIBC_LOCAL_NAME(strcasecoll_l)
#endif /* !__local___localdep_strcasecoll_l_defined */
#endif /* !__local_strcasecoll_l_defined */
