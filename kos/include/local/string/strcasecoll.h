/* HASH CRC-32:0xd043a12e */
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
#ifndef __local_strcasecoll_defined
#define __local_strcasecoll_defined 1
/* Dependency: "strcasecmp" from "string" */
#ifndef ____localdep_strcasecmp_defined
#define ____localdep_strcasecmp_defined 1
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL __localdep_strcasecmp)(char const *__s1, char const *__s2) { return __builtin_strcasecmp(__s1, __s2); }
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
#else /* LIBC: strcasecmp */
#include <local/string/strcasecmp.h>
#define __localdep_strcasecmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))
#endif /* strcasecmp... */
#endif /* !____localdep_strcasecmp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strcasecoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strcasecoll))(char const *__s1,
                                                         char const *__s2) {
#line 4632 "kos/src/libc/magic/string.c"
	return __localdep_strcasecmp(__s1, __s2);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strcasecoll_defined */
