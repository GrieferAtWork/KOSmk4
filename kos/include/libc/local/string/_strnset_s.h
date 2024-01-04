/* HASH CRC-32:0xbf4f3052 */
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
#ifndef __local__strnset_s_defined
#define __local__strnset_s_defined
#include <__crt.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/string.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_strnset_s) __ATTR_INOUTS(1, 4) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_strnset_s))(char *__restrict __buf, __SIZE_TYPE__ __buflen, int __ch, __SIZE_TYPE__ __maxlen) {
	char *__iter;
	__SIZE_TYPE__ __remaining;
	if (__maxlen == 0 && __buf == __NULLPTR && __buflen == 0)
		return 0;
	if (!__buf && __buflen)
		return 22;
	if (__maxlen >= __buflen)
		return 34;
	__iter = __buf;
	__remaining = __buflen;
	while (*__iter != 0 && __maxlen && --__remaining) {
		*__iter++ = (__WCHAR_TYPE__)__ch;
		--__maxlen;
	}
	if (!__maxlen) {
		while (*__iter && --__remaining)
			++__iter;
	}
	if (!__remaining) {
		__libc_memsetc(__buf, 0, __buflen, __SIZEOF_CHAR__);
		return 22;
	}
	__libc_memsetc(__iter, 0, __remaining, __SIZEOF_CHAR__);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__strnset_s_defined
#define __local___localdep__strnset_s_defined
#define __localdep__strnset_s __LIBC_LOCAL_NAME(_strnset_s)
#endif /* !__local___localdep__strnset_s_defined */
#endif /* !__local__strnset_s_defined */
