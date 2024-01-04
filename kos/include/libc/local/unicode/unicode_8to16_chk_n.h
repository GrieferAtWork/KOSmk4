/* HASH CRC-32:0x88f838a6 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_unicode_8to16_chk_n_defined
#define __local_unicode_8to16_chk_n_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_unicode_readutf8_n_defined
#define __local___localdep_unicode_readutf8_n_defined
#ifdef __CRT_HAVE_unicode_readutf8_n
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf8_n,(char const **__restrict __ptext, char const *__text_end),unicode_readutf8_n,(__ptext,__text_end))
#else /* __CRT_HAVE_unicode_readutf8_n */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_readutf8_n.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_readutf8_n __LIBC_LOCAL_NAME(unicode_readutf8_n)
#endif /* !__CRT_HAVE_unicode_readutf8_n */
#endif /* !__local___localdep_unicode_readutf8_n_defined */
__LOCAL_LIBC(unicode_8to16_chk_n) __ATTR_WUNUSED __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_8to16_chk_n))(__CHAR16_TYPE__ *__restrict __utf16_dst, __SIZE_TYPE__ __utf16_maxwords, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes) {
	char const *__utf8_end = __utf8_text + __utf8_bytes;
	while (__utf8_text < __utf8_end && __utf16_maxwords) {
		__CHAR32_TYPE__ __ch;
		__ch = (__NAMESPACE_LOCAL_SYM __localdep_unicode_readutf8_n)((char const **)&__utf8_text, __utf8_end);
		if (__ch > 0x10ffff || (__ch >= 0xd800 && __ch <= 0xdfff))
			return __NULLPTR;
		if __likely(__ch <= 0xffff/* && (ch < 0xd800 || ch > 0xdfff)*/) {
			*__utf16_dst++ = (__CHAR16_TYPE__)__ch;
			--__utf16_maxwords;
		} else {
			__ch -= 0x10000;
			*__utf16_dst++ = 0xd800 + (__CHAR16_TYPE__)(__ch >> 10);
			--__utf16_maxwords;
			if __unlikely(!__utf16_maxwords)
				break;
			*__utf16_dst++ = 0xdc00 + (__CHAR16_TYPE__)(__ch & 0x3ff);
			--__utf16_maxwords;
		}
	}
	return __utf16_dst;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unicode_8to16_chk_n_defined
#define __local___localdep_unicode_8to16_chk_n_defined
#define __localdep_unicode_8to16_chk_n __LIBC_LOCAL_NAME(unicode_8to16_chk_n)
#endif /* !__local___localdep_unicode_8to16_chk_n_defined */
#endif /* !__local_unicode_8to16_chk_n_defined */
