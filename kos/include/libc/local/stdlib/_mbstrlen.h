/* HASH CRC-32:0x11610df2 */
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
#ifndef __local__mbstrlen_defined
#define __local__mbstrlen_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_unicode_readutf8_defined
#define __local___localdep_unicode_readutf8_defined
#ifdef __CRT_HAVE_unicode_readutf8
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf8,(char const **__restrict __ptext),unicode_readutf8,(__ptext))
#else /* __CRT_HAVE_unicode_readutf8 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_readutf8.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_readutf8 __LIBC_LOCAL_NAME(unicode_readutf8)
#endif /* !__CRT_HAVE_unicode_readutf8 */
#endif /* !__local___localdep_unicode_readutf8_defined */
__LOCAL_LIBC(_mbstrlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbstrlen))(char const *__str) {
	__SIZE_TYPE__ __result = 0;
	while ((__NAMESPACE_LOCAL_SYM __localdep_unicode_readutf8)((char const **)&__str))
		++__result;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbstrlen_defined
#define __local___localdep__mbstrlen_defined
#define __localdep__mbstrlen __LIBC_LOCAL_NAME(_mbstrlen)
#endif /* !__local___localdep__mbstrlen_defined */
#endif /* !__local__mbstrlen_defined */
