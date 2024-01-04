/* HASH CRC-32:0xc83cc8e5 */
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
#ifndef __local_format_16to8_defined
#define __local_format_16to8_defined
#include <__crt.h>
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_unicode_writeutf8_defined
#define __local___localdep_unicode_writeutf8_defined
#ifdef __CRT_HAVE_unicode_writeutf8
__CREDIRECT(__ATTR_RETNONNULL __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_unicode_writeutf8,(char *__restrict __dst, __CHAR32_TYPE__ __ch),unicode_writeutf8,(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf8 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_writeutf8.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_writeutf8 __LIBC_LOCAL_NAME(unicode_writeutf8)
#endif /* !__CRT_HAVE_unicode_writeutf8 */
#endif /* !__local___localdep_unicode_writeutf8_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(format_16to8) __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__C16FORMATPRINTER_CC __LIBC_LOCAL_NAME(format_16to8))(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen) {

	struct __local_format_16to8_data {
		__pformatprinter __fd_printer;   /* [1..1] Inner printer */
		void           *__fd_arg;       /* Argument for `fd_printer' */
		__CHAR16_TYPE__        __fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
	};
	char __buf[64], *__dst = __buf;
	struct __local_format_16to8_data *__closure;
	__SSIZE_TYPE__ __temp, __result = 0;
	__SIZE_TYPE__ __i = 0;
	__CHAR32_TYPE__ __ch;
	__closure = (struct __local_format_16to8_data *)__arg;
	if (__closure->__fd_surrogate && __datalen) {
		__ch  = __closure->__fd_surrogate - 0xd800;
		__closure->__fd_surrogate = 0;
		__ch += 0x10000;
		__ch += ((__CHAR16_TYPE__ const *)__data)[0] - 0xdc00;
		__dst = (__NAMESPACE_LOCAL_SYM __localdep_unicode_writeutf8)(__dst, __ch);
		__i = 1;
		goto __after_dst_write;
	}
	while (__i < __datalen) {
		do {
			__CHAR16_TYPE__ __ch16;
			__ch16 = ((__CHAR16_TYPE__ const *)__data)[__i++];
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
			__dst = (__NAMESPACE_LOCAL_SYM __localdep_unicode_writeutf8)(__dst, __ch);
__after_dst_write:
			;
		} while ((__dst + 4) < __COMPILER_ENDOF(__buf) && __i < __datalen);
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
#ifndef __local___localdep_format_16to8_defined
#define __local___localdep_format_16to8_defined
#define __localdep_format_16to8 __LIBC_LOCAL_NAME(format_16to8)
#endif /* !__local___localdep_format_16to8_defined */
#endif /* !__local_format_16to8_defined */
