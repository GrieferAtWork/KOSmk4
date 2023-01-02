/* HASH CRC-32:0xccab2734 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strncasecoll_defined
#define __local_strncasecoll_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strncasecmp_defined
#define __local___localdep_strncasecmp_defined
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strncasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strncasecmp __LIBC_LOCAL_NAME(strncasecmp)
#endif /* !... */
#endif /* !__local___localdep_strncasecmp_defined */
__LOCAL_LIBC(strncasecoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strncasecoll))(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) {
	/* XXX: Implement properly? */
	return (__NAMESPACE_LOCAL_SYM __localdep_strncasecmp)(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strncasecoll_defined
#define __local___localdep_strncasecoll_defined
#define __localdep_strncasecoll __LIBC_LOCAL_NAME(strncasecoll)
#endif /* !__local___localdep_strncasecoll_defined */
#endif /* !__local_strncasecoll_defined */
