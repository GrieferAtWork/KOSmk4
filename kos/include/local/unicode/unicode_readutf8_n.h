/* HASH CRC-32:0xc3d5b109 */
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
#ifndef __local_unicode_readutf8_n_defined
#define __local_unicode_readutf8_n_defined 1
#include <local/unicode_utf8seqlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `unicode_readutf8()', but don't read past `text_end' */
__LOCAL_LIBC(unicode_readutf8_n) __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_readutf8_n))(/*utf-8*/char const **__restrict __ptext,
                                                                char const *__text_end) {
#line 277 "kos/src/libc/magic/unicode.c"
	__CHAR32_TYPE__ __result;
	char const *__iter = *__ptext;
	if __unlikely(__iter >= __text_end)
		return 0;
	__result = (__CHAR32_TYPE__)(__UINT8_TYPE__)*__iter++;
	if (__result >= 0xc0) {
		__UINT8_TYPE__ __len;
		__len = __LIBC_LOCAL_NAME(unicode_utf8seqlen)[__result];
		if (__iter + __len-1 >= __text_end)
			__len = (__UINT8_TYPE__)(__text_end - __iter)+1;
		switch (__len) {
		case 0:
		case 1:
			break;
		case 2:
			__result  = (__result & 0x1f) << 6;
			__result |= (__iter[0] & 0x3f);
			__iter += 1;
			break;
		case 3:
			__result  = (__result & 0x0f) << 12;
			__result |= (__iter[0] & 0x3f) << 6;
			__result |= (__iter[1] & 0x3f);
			__iter += 2;
			break;
		case 4:
			__result  = (__result & 0x07) << 18;
			__result |= (__iter[0] & 0x3f) << 12;
			__result |= (__iter[1] & 0x3f) << 6;
			__result |= (__iter[2] & 0x3f);
			__iter += 3;
			break;
		case 5:
			__result  = (__result & 0x03) << 24;
			__result |= (__iter[0] & 0x3f) << 18;
			__result |= (__iter[1] & 0x3f) << 12;
			__result |= (__iter[2] & 0x3f) << 6;
			__result |= (__iter[3] & 0x3f);
			__iter += 4;
			break;
		case 6:
			__result  = (__result & 0x01) << 30;
			__result |= (__iter[0] & 0x3f) << 24;
			__result |= (__iter[1] & 0x3f) << 18;
			__result |= (__iter[2] & 0x3f) << 12;
			__result |= (__iter[3] & 0x3f) << 6;
			__result |= (__iter[4] & 0x3f);
			__iter += 5;
			break;
		case 7:
			__result  = (__iter[0] & 0x03/*0x3f*/) << 30;
			__result |= (__iter[1] & 0x3f) << 24;
			__result |= (__iter[2] & 0x3f) << 18;
			__result |= (__iter[3] & 0x3f) << 12;
			__result |= (__iter[4] & 0x3f) << 6;
			__result |= (__iter[5] & 0x3f);
			__iter += 6;
			break;
		case 8:
			/*result = (iter[0] & 0x3f) << 36;*/
			__result  = (__iter[1] & 0x03/*0x3f*/) << 30;
			__result |= (__iter[2] & 0x3f) << 24;
			__result |= (__iter[3] & 0x3f) << 18;
			__result |= (__iter[4] & 0x3f) << 12;
			__result |= (__iter[5] & 0x3f) << 6;
			__result |= (__iter[6] & 0x3f);
			__iter += 7;
			break;
		default:
			__builtin_unreachable();
		}
	}
	*__ptext = __iter;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_unicode_readutf8_n_defined */
