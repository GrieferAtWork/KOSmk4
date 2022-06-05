/* HASH CRC-32:0xb2891a5 */
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
#ifndef __local_unicode_c8toc16_defined
#define __local_unicode_c8toc16_defined
#include <__crt.h>
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(unicode_c8toc16) __ATTR_INOUT(4) __ATTR_INS(2, 3) __ATTR_OUT(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_c8toc16))(__CHAR16_TYPE__ *__restrict __pc16, char const *__restrict __s, __SIZE_TYPE__ __n, struct __mbstate *__restrict __mbs) {
	__CHAR32_TYPE__ __resch;
	__SIZE_TYPE__ __i;
	if ((__mbs->__mb_word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_WR_UTF16_LO) {
		*__pc16 = 0xdc00 + (__mbs->__mb_word & 0x3ff);
		__mbs->__mb_word = __MBSTATE_TYPE_EMPTY;
		return 0;
	}
	for (__i = 0; __i < __n; ++__i) {
		__UINT32_TYPE__ __state;
		__UINT8_TYPE__ __ch;
		__state = __mbs->__mb_word & __MBSTATE_TYPE_MASK;
		__ch = (__UINT8_TYPE__)__s[__i];
		if (__state == __MBSTATE_TYPE_EMPTY) {
			if (__ch <= 0x7f) {
				*__pc16 = __ch;
				goto __done;
			} else if (__ch <= 0xbf) { /* NOLINT */
				goto __error_ilseq;
			} else if (__ch <= 0xdf) {
				__mbs->__mb_word = __MBSTATE_TYPE_UTF8_2_2 | (__ch & 0x1f);
				continue;
			} else if (__ch <= 0xef) {
				__mbs->__mb_word = __MBSTATE_TYPE_UTF8_3_2 | ((__ch & 0xf) << 6);
				continue;
			} else if (__ch <= 0xf7) {
				__mbs->__mb_word = __MBSTATE_TYPE_UTF8_4_2 | ((__ch & 0x7) << 12);
				continue;
			} else if (__ch <= 0xfb) {
				__mbs->__mb_word = __MBSTATE_TYPE_UTF8_5_2 | ((__ch & 0x3) << 18);
				continue;
			} else if (__ch <= 0xfd) {
				__mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_2 | ((__ch & 0x1) << 24);
				continue;
			} else {
				goto __error_ilseq;
			}
		}
		if ((__ch & 0xc0) != 0x80)
			goto __error_ilseq; /* Must be a follow-up byte */
		__ch &= 0x3f;
		switch (__mbs->__mb_word & __MBSTATE_TYPE_MASK) {

		case __MBSTATE_TYPE_UTF8_2_2: /* expect 2nd character of a 2-byte utf-8 sequence. { WORD & 0x0000001f } */
			*__pc16 = ((__mbs->__mb_word & 0x1f) << __MBSTATE_TYPE_UTF8_SHIFT) | __ch;
			goto __done_empty;

		case __MBSTATE_TYPE_UTF8_3_2: /* expect 2nd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0 } */
			__mbs->__mb_word = __MBSTATE_TYPE_UTF8_3_3 | (__mbs->__mb_word & 0x3c0) | __ch;
			break;

		case __MBSTATE_TYPE_UTF8_3_3: /* expect 3rd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0, WORD & 0x0000003f } */
			__resch = ((__mbs->__mb_word & 0x3ff) << __MBSTATE_TYPE_UTF8_SHIFT) | __ch;
			goto __done_empty_chk_surrogate;

		case __MBSTATE_TYPE_UTF8_4_2: /* expect 2nd character of a 4-byte utf-8 sequence. { WORD & 0x00007000 } */
			__mbs->__mb_word = __MBSTATE_TYPE_UTF8_4_3 | (__mbs->__mb_word & 0x7000) | ((__UINT32_TYPE__)__ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_4_3: /* expect 3rd character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0 } */
			__mbs->__mb_word = __MBSTATE_TYPE_UTF8_4_4 | (__mbs->__mb_word & 0x7fc0) | __ch;
			break;

		case __MBSTATE_TYPE_UTF8_4_4: /* expect 4th character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			__resch = ((__mbs->__mb_word & 0x7fff) << __MBSTATE_TYPE_UTF8_SHIFT) | __ch;
			goto __done_empty_chk_surrogate;

		case __MBSTATE_TYPE_UTF8_5_2: /* expect 2nd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000 } */
			__mbs->__mb_word = __MBSTATE_TYPE_UTF8_5_3 | (__mbs->__mb_word & 0xc0000) | ((__UINT32_TYPE__)__ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_5_3: /* expect 3rd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000 } */
			__mbs->__mb_word = __MBSTATE_TYPE_UTF8_5_4 | (__mbs->__mb_word & 0xff000) | ((__UINT32_TYPE__)__ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_5_4: /* expect 4th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			__mbs->__mb_word = __MBSTATE_TYPE_UTF8_5_5 | (__mbs->__mb_word & 0xfffc0) | __ch;
			break;

		case __MBSTATE_TYPE_UTF8_5_5: /* expect 5th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			__resch = ((__mbs->__mb_word & 0x000cffff) << __MBSTATE_TYPE_UTF8_SHIFT) | __ch;
			goto __done_empty_chk_surrogate;

		case __MBSTATE_TYPE_UTF8_6_2: /* expect 2nd character of a 6-byte utf-8 sequence. { WORD & 0x01000000 } */
			__mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_3 | (__mbs->__mb_word & 0x1000000) | ((__UINT32_TYPE__)__ch << (3 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_3: /* expect 3rd character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000 } */
			__mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_4 | (__mbs->__mb_word & 0x1fc0000) | ((__UINT32_TYPE__)__ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_4: /* expect 4th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000 } */
			__mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_5 | (__mbs->__mb_word & 0x1fff000) | ((__UINT32_TYPE__)__ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_6_5: /* expect 5th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			__mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_6 | (__mbs->__mb_word & 0x1ffffc0) | __ch;
			break;

		case __MBSTATE_TYPE_UTF8_6_6: /* expect 6th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			__resch = ((__mbs->__mb_word & 0x1ffffff) << __MBSTATE_TYPE_UTF8_SHIFT) | __ch;
			goto __done_empty_chk_surrogate;

		default:
__error_ilseq:
			return (__SIZE_TYPE__)-1;
		}
	}
	/* Incomplete sequence (but `mbs' may have been updated) */
	return (__SIZE_TYPE__)-2;
__done_empty_chk_surrogate:
	if ((__resch >= 0xd800 && __resch <= 0xdfff) || (__resch >= 0x10000)) {
		if __unlikely(__resch > 0x10ffff)
			goto __error_ilseq; /* Cannot be represented as UTF-16 */
		/* Need a utf-16 surrogate pair. */
		__resch -= 0x10000;
		*__pc16 = 0xd800 + (__CHAR16_TYPE__)(__resch >> 10);
		__mbs->__mb_word = __MBSTATE_TYPE_WR_UTF16_LO | (__UINT16_TYPE__)(__resch & 0x3ff);
	} else {
		*__pc16 = (__CHAR16_TYPE__)__resch;
	}
__done_empty:
	__mbs->__mb_word = __MBSTATE_TYPE_EMPTY;
__done:
	return __i + 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unicode_c8toc16_defined
#define __local___localdep_unicode_c8toc16_defined
#define __localdep_unicode_c8toc16 __LIBC_LOCAL_NAME(unicode_c8toc16)
#endif /* !__local___localdep_unicode_c8toc16_defined */
#endif /* !__local_unicode_c8toc16_defined */
