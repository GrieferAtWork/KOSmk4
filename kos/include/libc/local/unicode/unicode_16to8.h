/* HASH CRC-32:0xa3766ec0 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_unicode_16to8_defined
#define __local_unicode_16to8_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_unicode_readutf16_n_defined
#define __local___localdep_unicode_readutf16_n_defined
#ifdef __CRT_HAVE_unicode_readutf16_n
__CREDIRECT(__ATTR_INOUT(1) __ATTR_NONNULL((2)),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf16_n,(__CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_end),unicode_readutf16_n,(__ptext,__text_end))
#else /* __CRT_HAVE_unicode_readutf16_n */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_readutf16_n.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_readutf16_n __LIBC_LOCAL_NAME(unicode_readutf16_n)
#endif /* !__CRT_HAVE_unicode_readutf16_n */
#endif /* !__local___localdep_unicode_readutf16_n_defined */
__LOCAL_LIBC(unicode_16to8) __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_16to8))(char *__restrict __utf8_dst, __CHAR16_TYPE__ const *__restrict __utf16_text, __SIZE_TYPE__ __utf16_words) {
	__CHAR16_TYPE__ const *__utf16_end = __utf16_text + __utf16_words;
	while (__utf16_text < __utf16_end) {
		__CHAR32_TYPE__ __ch;
		__ch = (__NAMESPACE_LOCAL_SYM __localdep_unicode_readutf16_n)((__CHAR16_TYPE__ const **)&__utf16_text, __utf16_end);
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
#ifndef __local___localdep_unicode_16to8_defined
#define __local___localdep_unicode_16to8_defined
#define __localdep_unicode_16to8 __LIBC_LOCAL_NAME(unicode_16to8)
#endif /* !__local___localdep_unicode_16to8_defined */
#endif /* !__local_unicode_16to8_defined */
