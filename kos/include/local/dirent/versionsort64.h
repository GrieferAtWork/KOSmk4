/* HASH CRC-32:0xa75e7dae */
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
#ifndef __local_versionsort64_defined
#define __local_versionsort64_defined 1
#include <__crt.h>
#include <bits/dirent.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strverscmp from string */
#ifndef __local___localdep_strverscmp_defined
#define __local___localdep_strverscmp_defined 1
#ifdef __CRT_HAVE_strverscmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strverscmp,(char const *__s1, char const *__s2),strverscmp,(__s1,__s2))
#elif defined(__CRT_HAVE___strverscmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strverscmp,(char const *__s1, char const *__s2),__strverscmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/strverscmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strverscmp __LIBC_LOCAL_NAME(strverscmp)
#endif /* !... */
#endif /* !__local___localdep_strverscmp_defined */
/* 64-bit variant of `versionsort()' */
__LOCAL_LIBC(versionsort64) __ATTR_PURE __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(versionsort64))(struct dirent64 const **__e1, struct dirent64 const **__e2) {
	return __localdep_strverscmp((*__e1)->d_name, (*__e2)->d_name);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_versionsort64_defined
#define __local___localdep_versionsort64_defined 1
#define __localdep_versionsort64 __LIBC_LOCAL_NAME(versionsort64)
#endif /* !__local___localdep_versionsort64_defined */
#endif /* !__local_versionsort64_defined */
