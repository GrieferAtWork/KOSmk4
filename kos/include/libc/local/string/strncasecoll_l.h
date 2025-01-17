/* HASH CRC-32:0x17224ab7 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strncasecoll_l_defined
#define __local_strncasecoll_l_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strncasecoll_defined
#define __local___localdep_strncasecoll_defined
#ifdef __CRT_HAVE_strncasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strncasecoll.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strncasecoll __LIBC_LOCAL_NAME(strncasecoll)
#endif /* !... */
#endif /* !__local___localdep_strncasecoll_defined */
__LOCAL_LIBC(strncasecoll_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strncasecoll_l))(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) {
	/* XXX: Implement properly? */
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_strncasecoll)(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strncasecoll_l_defined
#define __local___localdep_strncasecoll_l_defined
#define __localdep_strncasecoll_l __LIBC_LOCAL_NAME(strncasecoll_l)
#endif /* !__local___localdep_strncasecoll_l_defined */
#endif /* !__local_strncasecoll_l_defined */
