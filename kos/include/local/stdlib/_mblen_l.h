/* HASH CRC-32:0xa4d8a867 */
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
#ifndef __local__mblen_l_defined
#define __local__mblen_l_defined 1
#include <__crt.h>
/* Dependency: "mblen" from "stdlib" */
#ifndef ____localdep_mblen_defined
#define ____localdep_mblen_defined 1
#ifdef __CRT_HAVE_mblen
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_mblen,(char const *__str, __SIZE_TYPE__ __maxlen),mblen,(__str,__maxlen))
#else /* LIBC: mblen */
#include <local/stdlib/mblen.h>
#define __localdep_mblen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mblen))
#endif /* mblen... */
#endif /* !____localdep_mblen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mblen_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mblen_l))(char const *__str,
                                                      __SIZE_TYPE__ __maxlen,
                                                      __locale_t __locale) {
#line 2581 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep_mblen(__str, __maxlen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__mblen_l_defined */
