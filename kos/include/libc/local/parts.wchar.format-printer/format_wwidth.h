/* HASH CRC-32:0x8d47c7a */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_format_wwidth_defined
#define __local_format_wwidth_defined
#include <__crt.h>
#include <bits/crt/wformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(format_wwidth) __ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_NCX(__WFORMATPRINTER_CC __LIBC_LOCAL_NAME(format_wwidth))(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen) {
#if __SIZEOF_WCHAR_T__ == 2
	__SIZE_TYPE__ __result = 0;
	__WCHAR_TYPE__ const *__iter, *__end;
	(void)__arg;
	__end = (__iter = __data) + __datalen;
	while (__iter < __end) {
		__WCHAR_TYPE__ __ch;
		__ch = *__iter++;
		if (__ch >= 0xd800 && __ch <= 0xd800 && __iter < __end) {
			__ch = *__iter;
			if (__ch >= 0xdc00 && __ch <= 0xdfff)
				++__iter;
		}
		++__result;
	}
	return (__SSIZE_TYPE__)__result;
#else /* __SIZEOF_WCHAR_T__ == 2 */
	(void)__arg;
	(void)__data;
	/* XXX: Not necessarily correct, as the 32-bit variant is actually ATTR_CONST.
	 *
	 * However,  magic headers don't  support conditional attributes, so  we can't just do
	 * [if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), pure]
	 * [if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ != 2), const] */
	__COMPILER_IMPURE();
	return (__SSIZE_TYPE__)__datalen;
#endif /* __SIZEOF_WCHAR_T__ != 2 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_wwidth_defined
#define __local___localdep_format_wwidth_defined
#define __localdep_format_wwidth __LIBC_LOCAL_NAME(format_wwidth)
#endif /* !__local___localdep_format_wwidth_defined */
#endif /* !__local_format_wwidth_defined */
