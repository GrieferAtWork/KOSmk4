/* HASH CRC-32:0xbb5660aa */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_unicode_32to8_defined
#define __local_unicode_32to8_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: unicode_writeutf8 from unicode */
#ifndef __local___localdep_unicode_writeutf8_defined
#define __local___localdep_unicode_writeutf8_defined 1
#ifdef __CRT_HAVE_unicode_writeutf8
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_unicode_writeutf8,(char *__restrict __dst, __CHAR32_TYPE__ __ch),unicode_writeutf8,(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf8 */
__NAMESPACE_LOCAL_END
#include <local/unicode/unicode_writeutf8.h>
__NAMESPACE_LOCAL_BEGIN
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
#define __localdep_unicode_writeutf8 __LIBC_LOCAL_NAME(unicode_writeutf8)
#endif /* !__CRT_HAVE_unicode_writeutf8 */
#endif /* !__local___localdep_unicode_writeutf8_defined */
/* Convert a given utf-32 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_32TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
__LOCAL_LIBC(unicode_32to8) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_32to8))(char *__restrict __utf8_dst, __CHAR32_TYPE__ const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_characters) {
	while (__utf32_characters--)
		__utf8_dst = __localdep_unicode_writeutf8(__utf8_dst, *__utf32_text++);
	return __utf8_dst;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unicode_32to8_defined
#define __local___localdep_unicode_32to8_defined 1
#define __localdep_unicode_32to8 __LIBC_LOCAL_NAME(unicode_32to8)
#endif /* !__local___localdep_unicode_32to8_defined */
#endif /* !__local_unicode_32to8_defined */
