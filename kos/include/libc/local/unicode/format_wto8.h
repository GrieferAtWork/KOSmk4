/* HASH CRC-32:0x6ad3fbba */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_format_wto8_defined
#define __local_format_wto8_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: unicode_writeutf8 from unicode */
#ifndef __local___localdep_unicode_writeutf8_defined
#define __local___localdep_unicode_writeutf8_defined 1
#ifdef __CRT_HAVE_unicode_writeutf8
/* >> unicode_writeutf8(3)
 * Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_unicode_writeutf8,(char *__restrict __dst, __CHAR32_TYPE__ __ch),unicode_writeutf8,(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf8 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_writeutf8.h>
__NAMESPACE_LOCAL_BEGIN
/* >> unicode_writeutf8(3)
 * Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
#define __localdep_unicode_writeutf8 __LIBC_LOCAL_NAME(unicode_writeutf8)
#endif /* !__CRT_HAVE_unicode_writeutf8 */
#endif /* !__local___localdep_unicode_writeutf8_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
/* >> format_wto8(3)
 * Format printer (compatible with `__pc16formatprinter') for
 * converting wide-character unicode input data into a UTF-8 output */
__LOCAL_LIBC(format_wto8) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(format_wto8))(void *__arg, __WCHAR_TYPE__ const *__data, __SIZE_TYPE__ __datalen) {
#if __SIZEOF_WCHAR_T__ == 2
	struct __local_format_16to8_data {
		__pformatprinter __fd_printer;   /* [1..1] Inner printer */
		void            *__fd_arg;       /* Argument for `fd_printer' */
		__CHAR16_TYPE__  __fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
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
		__dst = __localdep_unicode_writeutf8(__dst, __ch);
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
			__dst = __localdep_unicode_writeutf8(__dst, __ch);
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
#else /* __SIZEOF_WCHAR_T__ == 2 */
	struct __local_format_32to8_data {
		__pformatprinter __fd_printer; /* [1..1] Inner printer */
		void            *__fd_arg;     /* Argument for `fd_printer' */
	};
	char __buf[64];
	struct __local_format_32to8_data *__closure;
	__SSIZE_TYPE__ __temp, __result = 0;
	__SIZE_TYPE__ __i = 0;
	__closure = (struct __local_format_32to8_data *)__arg;
	while (__i < __datalen) {
		char *__dst = __buf;
		do {
			__dst = __localdep_unicode_writeutf8(__dst, ((__CHAR32_TYPE__ const *)__data)[__i++]);
		} while ((__dst + 7) < __COMPILER_ENDOF(__buf) && __i < __datalen);
		__temp = (*__closure->__fd_printer)(__closure->__fd_arg, __buf, (__SIZE_TYPE__)(__dst - __buf));
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
	}
	return __result;
__err:
	return __temp;
#endif /* __SIZEOF_WCHAR_T__ != 2 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_wto8_defined
#define __local___localdep_format_wto8_defined 1
#define __localdep_format_wto8 __LIBC_LOCAL_NAME(format_wto8)
#endif /* !__local___localdep_format_wto8_defined */
#endif /* !__local_format_wto8_defined */
