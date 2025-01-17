/* HASH CRC-32:0x7623346d */
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
#ifndef __local_unicode_readutf16_swap_rev_n_defined
#define __local_unicode_readutf16_swap_rev_n_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <hybrid/__byteswap.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(unicode_readutf16_swap_rev_n) __ATTR_IN(2) __ATTR_INOUT(1) __CHAR32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev_n))(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_start) {
	__CHAR32_TYPE__ __result;
	__CHAR16_TYPE__ const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	--__text;
	__result = (__CHAR32_TYPE__)__hybrid_bswap16((__UINT16_TYPE__)*__text);
	if (__result >= 0xdc00 &&
	    __result <= 0xdfff && __likely(__text > __text_start)) {
		__CHAR32_TYPE__ __high = (--__text, __hybrid_bswap16(*__text));
		__high   -= 0xd800;
		__high   <<= 10;
		__high   += 0x10000 - 0xdc00;
		__result += __high;
	}
	*__ptext = __text;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unicode_readutf16_swap_rev_n_defined
#define __local___localdep_unicode_readutf16_swap_rev_n_defined
#define __localdep_unicode_readutf16_swap_rev_n __LIBC_LOCAL_NAME(unicode_readutf16_swap_rev_n)
#endif /* !__local___localdep_unicode_readutf16_swap_rev_n_defined */
#endif /* !__local_unicode_readutf16_swap_rev_n_defined */
