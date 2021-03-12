/* HASH CRC-32:0xf0fc9c18 */
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
#ifndef __local_strncoll_defined
#define __local_strncoll_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strncmp from string */
#ifndef __local___localdep_strncmp_defined
#define __local___localdep_strncmp_defined 1
#if __has_builtin(__builtin_strncmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncmp)
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmp,{ return __builtin_strncmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncmp)
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmp,(__s1,__s2,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strncmp.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
#define __localdep_strncmp __LIBC_LOCAL_NAME(strncmp)
#endif /* !... */
#endif /* !__local___localdep_strncmp_defined */
__LOCAL_LIBC(strncoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strncoll))(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) {
	return __localdep_strncmp(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strncoll_defined
#define __local___localdep_strncoll_defined 1
#define __localdep_strncoll __LIBC_LOCAL_NAME(strncoll)
#endif /* !__local___localdep_strncoll_defined */
#endif /* !__local_strncoll_defined */
