/* HASH CRC-32:0x46899e1d */
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
#ifndef __local__mbstrlen_l_defined
#define __local__mbstrlen_l_defined 1
/* Dependency: "_mbstrlen" from "stdlib" */
#ifndef ____localdep__mbstrlen_defined
#define ____localdep__mbstrlen_defined 1
#ifdef __CRT_HAVE__mbstrlen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep__mbstrlen,(char const *__str),_mbstrlen,(__str))
#else /* LIBC: _mbstrlen */
#include <local/stdlib/_mbstrlen.h>
#define __localdep__mbstrlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mbstrlen))
#endif /* _mbstrlen... */
#endif /* !____localdep__mbstrlen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mbstrlen_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbstrlen_l))(char const *__str,
                                                         __locale_t __locale) {
#line 2423 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep__mbstrlen(__str);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__mbstrlen_l_defined */
