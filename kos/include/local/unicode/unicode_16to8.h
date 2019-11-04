/* HASH CRC-32:0x1a88059a */
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
#ifndef __local_unicode_16to8_defined
#define __local_unicode_16to8_defined 1
/* Dependency: "unicode_readutf16_n" from "unicode" */
#ifndef ____localdep_unicode_readutf16_n_defined
#define ____localdep_unicode_readutf16_n_defined 1
#ifdef __CRT_HAVE_unicode_readutf16_n
/* Same as `unicode_readutf16()', but don't read past `text_end' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf16_n,(/*utf-16*/__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_end),unicode_readutf16_n,(__ptext,__text_end))
#else /* LIBC: unicode_readutf16_n */
#include <local/unicode/unicode_readutf16_n.h>
/* Same as `unicode_readutf16()', but don't read past `text_end' */
#define __localdep_unicode_readutf16_n (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_n))
#endif /* unicode_readutf16_n... */
#endif /* !____localdep_unicode_readutf16_n_defined */

__NAMESPACE_LOCAL_BEGIN
/* Convert a given utf-16 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_16TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-8 character */
__LOCAL_LIBC(unicode_16to8) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_16to8))(/*utf-8*/ char *__restrict __utf8_dst,
                                                           /*utf-16*/__CHAR16_TYPE__ const *__restrict __utf16_text,
                                                           __SIZE_TYPE__ __utf16_characters) {
#line 1032 "kos/src/libc/magic/unicode.c"
	__CHAR16_TYPE__ const *__utf16_end = __utf16_text + __utf16_characters;
	while (__utf16_text < __utf16_end) {
		__CHAR32_TYPE__ __ch;
		__ch = __localdep_unicode_readutf16_n((__CHAR16_TYPE__ const **)&__utf16_text,__utf16_end);
		if (__ch <= ((__UINT32_TYPE__)1 << 7)-1) {
			*__utf8_dst++ = (char)(__UINT8_TYPE__)__ch;
		} else if (__ch <= ((__UINT32_TYPE__)1 << 11)-1) {
			*__utf8_dst++ = (char)(0xc0 | (__UINT8_TYPE__)((__ch >> 6)/* & 0x1f*/));
			*__utf8_dst++ = (char)(0x80 | (__UINT8_TYPE__)((__ch) & 0x3f));
		} else {
			*__utf8_dst++ = (char)(0xe0 | (__UINT8_TYPE__)((__ch >> 12)/* & 0x0f*/));
			*__utf8_dst++ = (char)(0x80 | (__UINT8_TYPE__)((__ch >> 6) & 0x3f));
			*__utf8_dst++ = (char)(0x80 | (__UINT8_TYPE__)((__ch) & 0x3f));
		}
	}
	return __utf8_dst;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_unicode_16to8_defined */
