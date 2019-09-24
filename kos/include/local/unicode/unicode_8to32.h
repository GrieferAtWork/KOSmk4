/* HASH CRC-32:0xbaaabe2 */
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
#ifndef __local_unicode_8to32_defined
#define __local_unicode_8to32_defined 1
/* Dependency: "unicode_readutf8_n" from "unicode" */
#ifndef ____localdep_unicode_readutf8_n_defined
#define ____localdep_unicode_readutf8_n_defined 1
#if defined(__CRT_HAVE_unicode_readutf8_n)
/* Same as `unicode_readutf8()', but don't read past `text_end' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf8_n,(/*utf-8*/char const **__restrict __ptext, char const *__text_end),unicode_readutf8_n,(__ptext,__text_end))
#else /* LIBC: unicode_readutf8_n */
#include <local/unicode/unicode_readutf8_n.h>
/* Same as `unicode_readutf8()', but don't read past `text_end' */
#define __localdep_unicode_readutf8_n (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_n))
#endif /* unicode_readutf8_n... */
#endif /* !____localdep_unicode_readutf8_n_defined */

__NAMESPACE_LOCAL_BEGIN
/* Convert a given utf-8 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_8TO32_MAXBUF(utf8_characters)' dwords, or `*4' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-32 character. */
__LOCAL_LIBC(unicode_8to32) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_8to32))(/*utf-32*/__CHAR32_TYPE__ *__restrict __utf32_dst,
                                                           /*utf-8*/char const *__restrict __utf8_text,
                                                           __SIZE_TYPE__ __utf8_characters) {
#line 1015 "kos/src/libc/magic/unicode.c"
	char const *__utf8_end = __utf8_text + __utf8_characters;
	while (__utf8_text < __utf8_end)
		*__utf32_dst++ = __localdep_unicode_readutf8_n((char const **)&__utf8_text,__utf8_end);
	return __utf32_dst;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_unicode_8to32_defined */
