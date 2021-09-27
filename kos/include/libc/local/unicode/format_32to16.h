/* HASH CRC-32:0xee150f5b */
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
#ifndef __local_format_32to16_defined
#define __local_format_32to16_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_unicode_writeutf16_defined
#define __local___localdep_unicode_writeutf16_defined
#ifdef __CRT_HAVE_unicode_writeutf16
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_unicode_writeutf16,(__CHAR16_TYPE__ *__restrict __dst, __CHAR32_TYPE__ __ch),unicode_writeutf16,(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf16 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_writeutf16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_writeutf16 __LIBC_LOCAL_NAME(unicode_writeutf16)
#endif /* !__CRT_HAVE_unicode_writeutf16 */
#endif /* !__local___localdep_unicode_writeutf16_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <bits/crt/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(format_32to16) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(format_32to16))(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen) {

	struct __local_format_32to16_data {
		__pc16formatprinter __fd_printer; /* [1..1] Inner printer */
		void              *__fd_arg;     /* Argument for `fd_printer' */
	};
	__CHAR16_TYPE__ __buf[64];
	struct __local_format_32to16_data *__closure;
	__SSIZE_TYPE__ __temp, __result = 0;
	__SIZE_TYPE__ __i = 0;
	__closure = (struct __local_format_32to16_data *)__arg;
	while (__i < __datalen) {
		__CHAR16_TYPE__ *__dst = __buf;
		do {
			__dst = (__NAMESPACE_LOCAL_SYM __localdep_unicode_writeutf16)(__dst, __data[__i++]);
		} while ((__dst + 2) < __COMPILER_ENDOF(__buf) && __i < __datalen);
		__temp = (*__closure->__fd_printer)(__closure->__fd_arg, __buf, (__SIZE_TYPE__)(__dst - __buf));
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
	}
	return __result;
__err:
	return __temp;









}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_32to16_defined
#define __local___localdep_format_32to16_defined
#define __localdep_format_32to16 __LIBC_LOCAL_NAME(format_32to16)
#endif /* !__local___localdep_format_32to16_defined */
#endif /* !__local_format_32to16_defined */
