/* HASH CRC-32:0xe2c0ac0c */
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
#ifndef __local__mbstrnlen_l_defined
#define __local__mbstrnlen_l_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__mbstrnlen_defined
#define __local___localdep__mbstrnlen_defined
#ifdef __CRT_HAVE__mbstrnlen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep__mbstrnlen,(char const *__str, __SIZE_TYPE__ __maxlen),_mbstrnlen,(__str,__maxlen))
#else /* __CRT_HAVE__mbstrnlen */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_mbstrnlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__mbstrnlen __LIBC_LOCAL_NAME(_mbstrnlen)
#endif /* !__CRT_HAVE__mbstrnlen */
#endif /* !__local___localdep__mbstrnlen_defined */
__LOCAL_LIBC(_mbstrnlen_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbstrnlen_l))(char const *__str, __SIZE_TYPE__ __maxlen, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep__mbstrnlen)(__str, __maxlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbstrnlen_l_defined
#define __local___localdep__mbstrnlen_l_defined
#define __localdep__mbstrnlen_l __LIBC_LOCAL_NAME(_mbstrnlen_l)
#endif /* !__local___localdep__mbstrnlen_l_defined */
#endif /* !__local__mbstrnlen_l_defined */
