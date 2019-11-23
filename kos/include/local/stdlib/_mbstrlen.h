/* HASH CRC-32:0x5ef26933 */
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
#ifndef __local__mbstrlen_defined
#define __local__mbstrlen_defined 1
/* Dependency: "unicode_readutf8" from "unicode" */
#ifndef ____localdep_unicode_readutf8_defined
#define ____localdep_unicode_readutf8_defined 1
#ifdef __CRT_HAVE_unicode_readutf8
/* Read a single Unicode character from a given UTF-8 string */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf8,(/*utf-8*/ char const **__restrict __ptext),unicode_readutf8,(__ptext))
#else /* LIBC: unicode_readutf8 */
#include <local/unicode/unicode_readutf8.h>
/* Read a single Unicode character from a given UTF-8 string */
#define __localdep_unicode_readutf8 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8))
#endif /* unicode_readutf8... */
#endif /* !____localdep_unicode_readutf8_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mbstrlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbstrlen))(char const *__str) {
#line 2357 "kos/src/libc/magic/stdlib.c"
	__SIZE_TYPE__ __result = 0;
	while (__localdep_unicode_readutf8((char const **)&__str))
		++__result;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__mbstrlen_defined */
