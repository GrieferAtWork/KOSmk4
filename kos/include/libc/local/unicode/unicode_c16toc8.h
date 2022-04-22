/* HASH CRC-32:0x46bf9788 */
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
#ifndef __local_unicode_c16toc8_defined
#define __local_unicode_c16toc8_defined
#include <__crt.h>
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(unicode_c16toc8) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_c16toc8))(char __pc8[3], __CHAR16_TYPE__ __c16, struct __mbstate *__restrict __mbs) {
	__CHAR32_TYPE__ __ch32;
	if ((__mbs->__mb_word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_UTF16_LO) {
		if __unlikely(!(__c16 >= 0xdc00 &&
		              __c16 <= 0xdfff))
			return (__SIZE_TYPE__)-1;
		__ch32 = ((__mbs->__mb_word & 0x000003ff) << 10) + 0x10000 + ((__UINT16_TYPE__)__c16 - 0xdc00);
		__mbs->__mb_word = __MBSTATE_TYPE_EMPTY;
	} else if (__c16 >= 0xd800 && __c16 <= 0xdbff) {
		__mbs->__mb_word = __MBSTATE_TYPE_UTF16_LO | ((__UINT16_TYPE__)__c16 - 0xd800);
		return 0;
	} else {
		__ch32 = (__CHAR32_TYPE__)__c16;
	}
	if __likely(__ch32 <= ((__UINT32_TYPE__)1 << 7)-1) {
		__pc8[0] = (char)(__UINT8_TYPE__)__ch32;
		return 1;
	}
	if (__ch32 <= ((__UINT32_TYPE__)1 << 11)-1) {
		__pc8[0] = (char)(0xc0 | (__UINT8_TYPE__)((__ch32 >> 6)/* & 0x1f*/));
		__pc8[1] = (char)(0x80 | (__UINT8_TYPE__)((__ch32) & 0x3f));
		return 2;
	}
	__pc8[0] = (char)(0xe0 | (__UINT8_TYPE__)((__ch32 >> 12)/* & 0x0f*/));
	__pc8[1] = (char)(0x80 | (__UINT8_TYPE__)((__ch32 >> 6) & 0x3f));
	__pc8[2] = (char)(0x80 | (__UINT8_TYPE__)((__ch32) & 0x3f));
	return 3;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unicode_c16toc8_defined
#define __local___localdep_unicode_c16toc8_defined
#define __localdep_unicode_c16toc8 __LIBC_LOCAL_NAME(unicode_c16toc8)
#endif /* !__local___localdep_unicode_c16toc8_defined */
#endif /* !__local_unicode_c16toc8_defined */
