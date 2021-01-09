/* HASH CRC-32:0x1d8491fd */
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
#ifndef __local_strcasestr_defined
#define __local_strcasestr_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strcasecmp from string */
#ifndef __local___localdep_strcasecmp_defined
#define __local___localdep_strcasecmp_defined 1
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),strcasecmp,{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcasecmp __LIBC_LOCAL_NAME(strcasecmp)
#endif /* !... */
#endif /* !__local___localdep_strcasecmp_defined */
/* Same as `strstr', but ignore casing */
__LOCAL_LIBC(strcasestr) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strcasestr))(char const *__haystack, char const *__needle) {
	for (; *__haystack; ++__haystack) {
		if (__localdep_strcasecmp(__haystack, __needle) == 0)
			return (char *)__haystack;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strcasestr_defined
#define __local___localdep_strcasestr_defined 1
#define __localdep_strcasestr __LIBC_LOCAL_NAME(strcasestr)
#endif /* !__local___localdep_strcasestr_defined */
#endif /* !__local_strcasestr_defined */
