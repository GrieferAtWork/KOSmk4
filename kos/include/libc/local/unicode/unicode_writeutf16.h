/* HASH CRC-32:0x70971cce */
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
#ifndef __local_unicode_writeutf16_defined
#define __local_unicode_writeutf16_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(unicode_writeutf16) __ATTR_RETNONNULL __ATTR_OUT(1) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unicode_writeutf16))(__CHAR16_TYPE__ *__restrict __dst, __CHAR32_TYPE__ __ch) {
	if __likely(__ch <= 0xffff && (__ch < 0xd800 || __ch > 0xdfff)) {
		*__dst++ = (__CHAR16_TYPE__)__ch;
	} else {
		__ch -= 0x10000;
		*__dst++ = 0xd800 + (__CHAR16_TYPE__)(__ch >> 10);
		*__dst++ = 0xdc00 + (__CHAR16_TYPE__)(__ch & 0x3ff);
	}
	return __dst;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unicode_writeutf16_defined
#define __local___localdep_unicode_writeutf16_defined
#define __localdep_unicode_writeutf16 __LIBC_LOCAL_NAME(unicode_writeutf16)
#endif /* !__local___localdep_unicode_writeutf16_defined */
#endif /* !__local_unicode_writeutf16_defined */
