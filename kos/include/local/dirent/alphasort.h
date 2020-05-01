/* HASH CRC-32:0x4e046b6 */
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
#ifndef __local_alphasort_defined
#define __local_alphasort_defined 1
#include <__crt.h>
/* Dependency: "strcoll" from "string" */
#ifndef ____localdep_strcoll_defined
#define ____localdep_strcoll_defined 1
#ifdef __CRT_HAVE_strcoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcoll,(char const *__s1, char const *__s2),strcoll,(__s1,__s2))
#else /* LIBC: strcoll */
#include <local/string/strcoll.h>
#define __localdep_strcoll (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcoll))
#endif /* strcoll... */
#endif /* !____localdep_strcoll_defined */

__NAMESPACE_LOCAL_BEGIN
/* Sort the 2 given directory entries `E1' and `E2' the same way `strcmp(3)' would */
__LOCAL_LIBC(alphasort) __ATTR_PURE __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(alphasort))(struct dirent const **__e1,
                                                       struct dirent const **__e2) {
#line 253 "kos/src/libc/magic/dirent.c"
	return __localdep_strcoll((*__e1)->d_name, (*__e2)->d_name);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_alphasort_defined */
