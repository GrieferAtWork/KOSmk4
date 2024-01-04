/* HASH CRC-32:0x6bb5e075 */
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
#ifndef __local_format_width_defined
#define __local_format_width_defined
#include <__crt.h>
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
#include <libc/template/unicode_utf8seqlen.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(format_width) __ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_NCX(__FORMATPRINTER_CC __LIBC_LOCAL_NAME(format_width))(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) {
	__SIZE_TYPE__ __result = 0;
	char const *__iter, *__end;
	(void)__arg;
	__end = (__iter = __data) + __datalen;
	while (__iter < __end) {
		__UINT8_TYPE__ __len;
		__len = __LOCAL_unicode_utf8seqlen[(__UINT8_TYPE__)*__iter];
		if __unlikely(!__len)
			__len = 1;
		__iter += __len;
		++__result;
	}
	return (__SSIZE_TYPE__)__result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_width_defined
#define __local___localdep_format_width_defined
#define __localdep_format_width __LIBC_LOCAL_NAME(format_width)
#endif /* !__local___localdep_format_width_defined */
#endif /* !__local_format_width_defined */
