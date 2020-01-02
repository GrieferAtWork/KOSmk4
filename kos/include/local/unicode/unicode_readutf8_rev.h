/* HASH CRC-32:0x38079886 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_unicode_readutf8_rev_defined
#define __local_unicode_readutf8_rev_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__LOCAL_LIBC(unicode_readutf8_rev) __ATTR_NONNULL((1)) __CHAR32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_readutf8_rev))(/*utf-8*/ char const **__restrict __ptext) {
#line 202 "kos/src/libc/magic/unicode.c"
	__CHAR32_TYPE__ __result;
	char const *__iter = *__ptext;
	__UINT8_TYPE__ __seqlen = 1;
	for (;;) {
		__result = (unsigned char)*--__iter;
		if ((__result & 0xc0) != 0x80)
			break;
		if (__seqlen >= 8)
			break;
		++__seqlen;
	}
	if (__result >= 0xc0) {
		switch (__seqlen) {

		case 0:
		case 1:
			break;

		case 2:
			__result  = (__result & 0x1f) << 6;
			__result |= (__iter[0] & 0x3f);
			break;

		case 3:
			__result  = (__result & 0x0f) << 12;
			__result |= (__iter[0] & 0x3f) << 6;
			__result |= (__iter[1] & 0x3f);
			break;

		case 4:
			__result  = (__result & 0x07) << 18;
			__result |= (__iter[0] & 0x3f) << 12;
			__result |= (__iter[1] & 0x3f) << 6;
			__result |= (__iter[2] & 0x3f);
			break;

		case 5:
			__result  = (__result & 0x03) << 24;
			__result |= (__iter[0] & 0x3f) << 18;
			__result |= (__iter[1] & 0x3f) << 12;
			__result |= (__iter[2] & 0x3f) << 6;
			__result |= (__iter[3] & 0x3f);
			break;

		case 6:
			__result  = (__result & 0x01) << 30;
			__result |= (__iter[0] & 0x3f) << 24;
			__result |= (__iter[1] & 0x3f) << 18;
			__result |= (__iter[2] & 0x3f) << 12;
			__result |= (__iter[3] & 0x3f) << 6;
			__result |= (__iter[4] & 0x3f);
			break;

		case 7:
			__result  = (__iter[0] & 0x03/*0x3f*/) << 30;
			__result |= (__iter[1] & 0x3f) << 24;
			__result |= (__iter[2] & 0x3f) << 18;
			__result |= (__iter[3] & 0x3f) << 12;
			__result |= (__iter[4] & 0x3f) << 6;
			__result |= (__iter[5] & 0x3f);
			break;

		case 8:
			/*result = (iter[0] & 0x3f) << 36;*/
			__result  = (__iter[1] & 0x03/*0x3f*/) << 30;
			__result |= (__iter[2] & 0x3f) << 24;
			__result |= (__iter[3] & 0x3f) << 18;
			__result |= (__iter[4] & 0x3f) << 12;
			__result |= (__iter[5] & 0x3f) << 6;
			__result |= (__iter[6] & 0x3f);
			break;

		default:
			__builtin_unreachable();
		}
	}
	*__ptext = __iter;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_unicode_readutf8_rev_defined */
