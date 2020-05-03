/* HASH CRC-32:0x6cfad631 */
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
#ifndef __local_unicode_writeutf16_chk_defined
#define __local_unicode_writeutf16_chk_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `unicode_writeutf16()', but return `NULL' when `UNICODE_ISVALIDUTF16(ch)' is false */
__LOCAL_LIBC(unicode_writeutf16_chk) __ATTR_WUNUSED __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_writeutf16_chk))(/*utf-16*/ __CHAR16_TYPE__ *__restrict __dst,
                                                                    __CHAR32_TYPE__ __ch) {
#line 747 "kos/src/libc/magic/unicode.c"
	if (__ch > 0x10ffff)
		return __NULLPTR;
	if (__ch <= 0xffff && (__ch < 0xd800 || __ch > 0xdfff)) {
		*__dst++ = (__CHAR16_TYPE__)__ch;
	} else {
		__ch -= 0x10000;
		*__dst++ = 0xd800 + (__CHAR16_TYPE__)(__ch >> 10);
		*__dst++ = 0xdc00 + (__CHAR16_TYPE__)(__ch & 0x3ff);
	}
	return __dst;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_unicode_writeutf16_chk_defined */
