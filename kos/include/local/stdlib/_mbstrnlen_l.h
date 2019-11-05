/* HASH CRC-32:0xb8adac1c */
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
#ifndef __local__mbstrnlen_l_defined
#define __local__mbstrnlen_l_defined 1
/* Dependency: "_mbstrnlen" from "stdlib" */
#ifndef ____localdep__mbstrnlen_defined
#define ____localdep__mbstrnlen_defined 1
#ifdef __CRT_HAVE__mbstrnlen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep__mbstrnlen,(char const *__str, __SIZE_TYPE__ __maxlen),_mbstrnlen,(__str,__maxlen))
#else /* LIBC: _mbstrnlen */
#include <local/stdlib/_mbstrnlen.h>
#define __localdep__mbstrnlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrnlen))
#endif /* _mbstrnlen... */
#endif /* !____localdep__mbstrnlen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mbstrnlen_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbstrnlen_l))(char const *__str,
                                                          __SIZE_TYPE__ __maxlen,
                                                          __locale_t __locale) {
#line 2259 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep__mbstrnlen(__str, __maxlen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__mbstrnlen_l_defined */
