/* HASH CRC-32:0xe635ef02 */
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
#ifndef __local_strcoll_defined
#define __local_strcoll_defined 1
/* Dependency: "strcmp" from "string" */
#ifndef ____localdep_strcmp_defined
#define ____localdep_strcmp_defined 1
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* LIBC: strcmp */
#include <local/string/strcmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __localdep_strcmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcmp))
#endif /* strcmp... */
#endif /* !____localdep_strcmp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strcoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strcoll))(char const *__s1,
                                                     char const *__s2) {
#line 418 "kos/src/libc/magic/string.c"
	return __localdep_strcmp(__s1, __s2);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strcoll_defined */
