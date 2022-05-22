/* HASH CRC-32:0x22161aae */
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
#ifndef __local_format_16to32_defined
#define __local_format_16to32_defined
#include <__crt.h>
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(format_16to32) __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__C16FORMATPRINTER_CC __LIBC_LOCAL_NAME(format_16to32))(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen) {

	struct __local_format_16to32_data {
		__pc32formatprinter __fd_printer;   /* [1..1] Inner printer */
		void              *__fd_arg;       /* Argument for `fd_printer' */
		__CHAR16_TYPE__           __fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
	};
	__CHAR32_TYPE__ __buf[64], *__dst = __buf;
	struct __local_format_16to32_data *__closure;
	__SSIZE_TYPE__ __temp, __result = 0;
	__SIZE_TYPE__ __i = 0;
	__CHAR32_TYPE__ __ch;
	__closure = (struct __local_format_16to32_data *)__arg;
	if (__closure->__fd_surrogate && __datalen) {
		__ch  = __closure->__fd_surrogate - 0xd800;
		__closure->__fd_surrogate = 0;
		__ch += 0x10000;
		__ch += __data[0] - 0xdc00;
		*__dst++ = __ch;
		__i = 1;
		goto __after_dst_write;
	}
	while (__i < __datalen) {
		do {
			__CHAR16_TYPE__ __ch16;
			__ch16 = __data[__i++];
			if (__ch16 >= 0xd800 &&
			    __ch16 <= 0xdbff) {
				if (__i >= __datalen) {
					__closure->__fd_surrogate = __ch16;
					break;
				}
				__ch  = __ch16 - 0xd800;
				__ch += 0x10000;
				__ch += __data[__i++] - 0xdc00;
			} else {
				__ch = __ch16;
			}
			*__dst++ = __ch;
__after_dst_write:
			;
		} while (__dst < __COMPILER_ENDOF(__buf) && __i < __datalen);
		__temp = (*__closure->__fd_printer)(__closure->__fd_arg, __buf, (__SIZE_TYPE__)(__dst - __buf));
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
		__dst = __buf;
	}
	return __result;
__err:
	return __temp;









}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_16to32_defined
#define __local___localdep_format_16to32_defined
#define __localdep_format_16to32 __LIBC_LOCAL_NAME(format_16to32)
#endif /* !__local___localdep_format_16to32_defined */
#endif /* !__local_format_16to32_defined */
