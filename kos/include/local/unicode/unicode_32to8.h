/* HASH CRC-32:0x16d72e2f */
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
#ifndef __local_unicode_32to8_defined
#define __local_unicode_32to8_defined 1
/* Dependency: "unicode_writeutf8" from "unicode" */
#ifndef ____localdep_unicode_writeutf8_defined
#define ____localdep_unicode_writeutf8_defined 1
#ifdef __CRT_HAVE_unicode_writeutf8
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_unicode_writeutf8,(/*utf-8*/ char *__restrict __dst, __CHAR32_TYPE__ __ch),unicode_writeutf8,(__dst,__ch))
#else /* LIBC: unicode_writeutf8 */
#include <local/unicode/unicode_writeutf8.h>
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
#define __localdep_unicode_writeutf8 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_writeutf8))
#endif /* unicode_writeutf8... */
#endif /* !____localdep_unicode_writeutf8_defined */

__NAMESPACE_LOCAL_BEGIN
/* Convert a given utf-32 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_32TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
__LOCAL_LIBC(unicode_32to8) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_32to8))(/*utf-8*/ char *__restrict __utf8_dst,
                                                           /*utf-32*/__CHAR32_TYPE__ const *__restrict __utf32_text,
                                                           __SIZE_TYPE__ __utf32_characters) {
#line 1076 "kos/src/libc/magic/unicode.c"
	while (__utf32_characters--)
		__utf8_dst = __localdep_unicode_writeutf8(__utf8_dst, *__utf32_text++);
	return __utf8_dst;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_unicode_32to8_defined */
