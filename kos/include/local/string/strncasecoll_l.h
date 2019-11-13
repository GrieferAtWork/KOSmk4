/* HASH CRC-32:0x84692384 */
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
#ifndef __local_strncasecoll_l_defined
#define __local_strncasecoll_l_defined 1
/* Dependency: "strncasecoll" from "string" */
#ifndef ____localdep_strncasecoll_defined
#define ____localdep_strncasecoll_defined 1
#ifdef __CRT_HAVE_strncasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncasecoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#else /* LIBC: strncasecoll */
#include <local/string/strncasecoll.h>
#define __localdep_strncasecoll (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll))
#endif /* strncasecoll... */
#endif /* !____localdep_strncasecoll_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strncasecoll_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strncasecoll_l))(char const *__s1,
                                                            char const *__s2,
                                                            __SIZE_TYPE__ __maxlen,
                                                            __locale_t __locale) {
#line 4268 "kos/src/libc/magic/string.c"
	(void)__locale;
	return __localdep_strncasecoll(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strncasecoll_l_defined */
