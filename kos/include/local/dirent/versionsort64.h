/* HASH CRC-32:0x1e044ed */
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
#ifndef __local_versionsort64_defined
#define __local_versionsort64_defined 1
/* Dependency: "strverscmp" from "string" */
#ifndef ____localdep_strverscmp_defined
#define ____localdep_strverscmp_defined 1
#if defined(__CRT_HAVE_strverscmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strverscmp,(char const *__s1, char const *__s2),strverscmp,(__s1,__s2))
#else /* LIBC: strverscmp */
#include <local/string/strverscmp.h>
#define __localdep_strverscmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strverscmp))
#endif /* strverscmp... */
#endif /* !____localdep_strverscmp_defined */

__NAMESPACE_LOCAL_BEGIN
/* 64-bit variant of `versionsort()' */
__LOCAL_LIBC(versionsort64) __ATTR_PURE __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(versionsort64))(struct dirent64 const **__e1,
                                                           struct dirent64 const **__e2) {
#line 304 "kos/src/libc/magic/dirent.c"
	return __localdep_strverscmp((*__e1)->d_name, (*__e2)->d_name);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_versionsort64_defined */
