/* HASH CRC-32:0x6e81bde5 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_unicode_readutf16_defined
#define __local_unicode_readutf16_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
__LOCAL_LIBC(unicode_readutf16) __ATTR_NONNULL((1)) __CHAR32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_readutf16))(__CHAR16_TYPE__ const **__restrict __ptext) {
	__CHAR32_TYPE__ __result;
	__CHAR16_TYPE__ const *__text = *__ptext;
	__result = (__CHAR32_TYPE__)(__UINT16_TYPE__)*__text++;
	if (__result >= 0xd800 &&
	    __result <= 0xdbff) {
		__result -= 0xd800;
		__result <<= 10;
		__result += 0x10000 - 0xdc00;
		__result += *__text++; /* low surrogate */
	}
	*__ptext = __text;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unicode_readutf16_defined
#define __local___localdep_unicode_readutf16_defined 1
#define __localdep_unicode_readutf16 __LIBC_LOCAL_NAME(unicode_readutf16)
#endif /* !__local___localdep_unicode_readutf16_defined */
#endif /* !__local_unicode_readutf16_defined */
