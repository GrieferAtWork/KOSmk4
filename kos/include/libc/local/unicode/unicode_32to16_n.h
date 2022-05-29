/* HASH CRC-32:0x891496c1 */
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
#ifndef __local_unicode_32to16_n_defined
#define __local_unicode_32to16_n_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(unicode_32to16_n) __ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_32to16_n))(__CHAR16_TYPE__ *__restrict __utf16_dst, __SIZE_TYPE__ __utf16_maxwords, __CHAR32_TYPE__ const *__restrict __utf32_text, __SIZE_TYPE__ __utf32_dwords) {
	while (__utf32_dwords-- && __utf16_maxwords) {
		__CHAR32_TYPE__ __ch = *__utf32_text++;
		if __likely(__ch <= 0xffff && (__ch < 0xd800 || __ch > 0xdfff)) {
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
#ifndef __local___localdep_unicode_32to16_n_defined
#define __local___localdep_unicode_32to16_n_defined
#define __localdep_unicode_32to16_n __LIBC_LOCAL_NAME(unicode_32to16_n)
#endif /* !__local___localdep_unicode_32to16_n_defined */
#endif /* !__local_unicode_32to16_n_defined */
