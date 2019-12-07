/* HASH CRC-32:0x56f02fdc */
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
#ifndef __local_unicode_c8toc32_defined
#define __local_unicode_c8toc32_defined 1
#include <bits/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
/* @return: *:          Success (*pc32 was filled; the return value is the number of bytes taken from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
 * @return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated) */
__LOCAL_LIBC(unicode_c8toc32) __ATTR_NONNULL((1, 2, 4)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_c8toc32))(__CHAR32_TYPE__ *__restrict __pc32,
                                                             /*utf-8*/ char const *__restrict __s,
                                                             __SIZE_TYPE__ __n,
                                                             __mbstate_t *__restrict __mbs) {
#line 1228 "kos/src/libc/magic/unicode.c"
	__SIZE_TYPE__ __i;
	for (__i = 0; __i < __n; ++__i) {
		__UINT32_TYPE__ __state;
		__UINT8_TYPE__ __ch;
		__state = __mbs->__word & __MBSTATE_TYPE_MASK;
		__ch = (__UINT8_TYPE__)__s[__i];
		if (__state == __MBSTATE_TYPE_EMPTY) {
			if (__ch <= 0x7f) {
				*__pc32 = __ch;
				goto __done;
			} else if (__ch <= 0xbf) {
				goto __error_ilseq;
			} else if (__ch <= 0xdf) {
				__mbs->__word = __MBSTATE_TYPE_UTF8_2_2 | (__ch & 0x1f);
				continue;
			} else if (__ch <= 0xef) {
				__mbs->__word = __MBSTATE_TYPE_UTF8_3_2 | ((__ch & 0xf) << 6);
				continue;
			} else if (__ch <= 0xf7) {
				__mbs->__word = __MBSTATE_TYPE_UTF8_4_2 | ((__ch & 0x7) << 12);
				continue;
			} else if (__ch <= 0xfb) {
				__mbs->__word = __MBSTATE_TYPE_UTF8_5_2 | ((__ch & 0x3) << 18);
				continue;
			} else if (__ch <= 0xfd) {
				__mbs->__word = __MBSTATE_TYPE_UTF8_6_2 | ((__ch & 0x1) << 24);
				continue;
			} else {
				goto __error_ilseq;
			}
		}
		if ((__ch & 0xc0) != 0x80)
			goto __error_ilseq; /* Must be a follow-up byte */
		__ch &= 0x3f;
		switch (__mbs->__word & __MBSTATE_TYPE_MASK) {

		case __MBSTATE_TYPE_UTF8_2_2: /* expect 2nd character of a 2-byte utf-8 sequence. { WORD & 0x0000001f } */
			*__pc32 = ((__mbs->__word & 0x1f) << __MBSTATE_TYPE_UTF8_SHIFT) | __ch;
			goto __done_empty;

		case __MBSTATE_TYPE_UTF8_3_2: /* expect 2nd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0 } */
			__mbs->__word = __MBSTATE_TYPE_UTF8_3_3 | (__mbs->__word & 0x3c0) | __ch;
			break;

		case __MBSTATE_TYPE_UTF8_3_3: /* expect 3rd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0, WORD & 0x0000003f } */
			*__pc32 = ((__mbs->__word & 0x3ff) << __MBSTATE_TYPE_UTF8_SHIFT) | __ch;
			goto __done_empty;

		case __MBSTATE_TYPE_UTF8_4_2: /* expect 2nd character of a 4-byte utf-8 sequence. { WORD & 0x00007000 } */
			__mbs->__word = __MBSTATE_TYPE_UTF8_4_3 | (__mbs->__word & 0x7000) | ((__UINT32_TYPE__)__ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_4_3: /* expect 3rd character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0 } */
			__mbs->__word = __MBSTATE_TYPE_UTF8_4_4 | (__mbs->__word & 0x7fc0) | __ch;
			break;

		case __MBSTATE_TYPE_UTF8_4_4: /* expect 4th character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			*__pc32 = ((__mbs->__word & 0x7fff) << __MBSTATE_TYPE_UTF8_SHIFT) | __ch;
			goto __done_empty;

		case __MBSTATE_TYPE_UTF8_5_2: /* expect 2nd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000 } */
			__mbs->__word = __MBSTATE_TYPE_UTF8_5_3 | (__mbs->__word & 0xc0000) | ((__UINT32_TYPE__)__ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_5_3: /* expect 3rd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000 } */
			__mbs->__word = __MBSTATE_TYPE_UTF8_5_4 | (__mbs->__word & 0xff000) | ((__UINT32_TYPE__)__ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_5_4: /* expect 4th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			__mbs->__word = __MBSTATE_TYPE_UTF8_5_5 | (__mbs->__word & 0xfffc0) | __ch;
			break;

		case __MBSTATE_TYPE_UTF8_5_5: /* expect 5th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			*__pc32 = ((__mbs->__word & 0x000cffff) << __MBSTATE_TYPE_UTF8_SHIFT) | __ch;
			goto __done_empty;

		case __MBSTATE_TYPE_UTF8_6_2: /* expect 2nd character of a 6-byte utf-8 sequence. { WORD & 0x01000000 } */
			__mbs->__word = __MBSTATE_TYPE_UTF8_6_3 | (__mbs->__word & 0x1000000) | ((__UINT32_TYPE__)__ch << (3 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_3: /* expect 3rd character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000 } */
			__mbs->__word = __MBSTATE_TYPE_UTF8_6_4 | (__mbs->__word & 0x1fc0000) | ((__UINT32_TYPE__)__ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_4: /* expect 4th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000 } */
			__mbs->__word = __MBSTATE_TYPE_UTF8_6_5 | (__mbs->__word & 0x1fff000) | ((__UINT32_TYPE__)__ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_6_5: /* expect 5th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			__mbs->__word = __MBSTATE_TYPE_UTF8_6_6 | (__mbs->__word & 0x1ffffc0) | __ch;
			break;

		case __MBSTATE_TYPE_UTF8_6_6: /* expect 6th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			*__pc32 = ((__mbs->__word & 0x1ffffff) << __MBSTATE_TYPE_UTF8_SHIFT) | __ch;
			goto __done_empty;

		default:
__error_ilseq:
			return (__SIZE_TYPE__)-1;
		}
	}
	/* Incomplete sequence (but `mbs' may have been updated) */
	return (__SIZE_TYPE__)-2;
__done_empty:
	__mbs->__word = __MBSTATE_TYPE_EMPTY;
__done:
	return __i + 1;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_unicode_c8toc32_defined */
