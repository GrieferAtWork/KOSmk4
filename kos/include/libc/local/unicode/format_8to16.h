/* HASH CRC-32:0xafcc4f6 */
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
#ifndef __local_format_8to16_defined
#define __local_format_8to16_defined
#include <__crt.h>
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_unicode_c8toc16_defined
#define __local___localdep_unicode_c8toc16_defined
#ifdef __CRT_HAVE_unicode_c8toc16
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(4) __ATTR_INS(2, 3) __ATTR_OUT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_unicode_c8toc16,(__CHAR16_TYPE__ *__restrict __pc16, char const *__restrict __s, __SIZE_TYPE__ __n, struct __mbstate *__restrict __mbs),unicode_c8toc16,(__pc16,__s,__n,__mbs))
#else /* __CRT_HAVE_unicode_c8toc16 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_c8toc16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_c8toc16 __LIBC_LOCAL_NAME(unicode_c8toc16)
#endif /* !__CRT_HAVE_unicode_c8toc16 */
#endif /* !__local___localdep_unicode_c8toc16_defined */
#ifndef __local___localdep_unicode_c8toc32_defined
#define __local___localdep_unicode_c8toc32_defined
#ifdef __CRT_HAVE_unicode_c8toc32
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(4) __ATTR_INS(2, 3) __ATTR_OUT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_unicode_c8toc32,(__CHAR32_TYPE__ *__restrict __pc32, char const *__restrict __s, __SIZE_TYPE__ __n, struct __mbstate *__restrict __mbs),unicode_c8toc32,(__pc32,__s,__n,__mbs))
#else /* __CRT_HAVE_unicode_c8toc32 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_c8toc32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_c8toc32 __LIBC_LOCAL_NAME(unicode_c8toc32)
#endif /* !__CRT_HAVE_unicode_c8toc32 */
#endif /* !__local___localdep_unicode_c8toc32_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
#include <bits/crt/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(format_8to16) __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__FORMATPRINTER_CC __LIBC_LOCAL_NAME(format_8to16))(void *__arg, char const *__data, __SIZE_TYPE__ __datalen) {
	struct __local_format_8tow_data {
		__pc16formatprinter __fd_printer;    /* [1..1] Inner printer */
		void            *__fd_arg;        /* Argument for `fd_printer' */
		struct __mbstate       __fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	__CHAR16_TYPE__ __buf[64], *__dst = __buf;
	struct __local_format_8tow_data *__closure;
	__SSIZE_TYPE__ __temp, __result = 0;
	__closure = (struct __local_format_8tow_data *)__arg;
	while (__datalen) {
		do {
			__SIZE_TYPE__ __error;

			__error = (__NAMESPACE_LOCAL_SYM __localdep_unicode_c8toc16)((__CHAR16_TYPE__ *)__dst, __data, __datalen, &__closure->__fd_incomplete);



			if __unlikely(__error == (__SIZE_TYPE__)-1) {
				__mbstate_init(&__closure->__fd_incomplete);
				*__dst = __data[0];
				__error = 1;
			} else if (__error == (__SIZE_TYPE__)-2) {
				__datalen = 0;
				break;
			}
			__data += __error;
			__datalen -= __error;
			++__dst;
		} while (__dst < __COMPILER_ENDOF(__buf) && __datalen);
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
#ifndef __local___localdep_format_8to16_defined
#define __local___localdep_format_8to16_defined
#define __localdep_format_8to16 __LIBC_LOCAL_NAME(format_8to16)
#endif /* !__local___localdep_format_8to16_defined */
#endif /* !__local_format_8to16_defined */
