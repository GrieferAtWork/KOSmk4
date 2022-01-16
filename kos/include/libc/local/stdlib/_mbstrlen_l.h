/* HASH CRC-32:0x65b29619 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__mbstrlen_l_defined
#define __local__mbstrlen_l_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__mbstrlen_defined
#define __local___localdep__mbstrlen_defined
#ifdef __CRT_HAVE__mbstrlen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep__mbstrlen,(char const *__str),_mbstrlen,(__str))
#else /* __CRT_HAVE__mbstrlen */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_mbstrlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbstrlen __LIBC_LOCAL_NAME(_mbstrlen)
#endif /* !__CRT_HAVE__mbstrlen */
#endif /* !__local___localdep__mbstrlen_defined */
__LOCAL_LIBC(_mbstrlen_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbstrlen_l))(char const *__str, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep__mbstrlen)(__str);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbstrlen_l_defined
#define __local___localdep__mbstrlen_l_defined
#define __localdep__mbstrlen_l __LIBC_LOCAL_NAME(_mbstrlen_l)
#endif /* !__local___localdep__mbstrlen_l_defined */
#endif /* !__local__mbstrlen_l_defined */
