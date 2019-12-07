/* HASH CRC-32:0x22de4968 */
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
#ifndef __local_unicode_readutf16_defined
#define __local_unicode_readutf16_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Read a single Unicode character from a given UTF-16 string */
__LOCAL_LIBC(unicode_readutf16) __ATTR_NONNULL((1)) __CHAR32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_readutf16))(/*utf-16*/ __CHAR16_TYPE__ const **__restrict __ptext) {
#line 471 "kos/src/libc/magic/unicode.c"
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
#endif /* !__local_unicode_readutf16_defined */
