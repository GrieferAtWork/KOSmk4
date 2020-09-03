/* HASH CRC-32:0x2dea9747 */
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
#ifndef __local_strncpy_s_defined
#define __local_strncpy_s_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <libc/errno.h>
#include <libc/string.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strncpy_s) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strncpy_s))(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __maxlen) {
	char *__iter;
	__SIZE_TYPE__ __remaining;
	if (__maxlen == 0 && __dst == __NULLPTR && __dstsize == 0)
		return 0;
	if ((!__dst && __dstsize) || (!__src && __maxlen))
		return 22;
	if (!__maxlen) {
		__libc_memsetc(__dst, 0, __dstsize, __SIZEOF_CHAR__);
		return 0;
	}
	__iter = __dst;
	__remaining = __dstsize;
	if (__maxlen == (__SIZE_TYPE__)-1) {
		while ((*__iter++ = *__src++) != 0 && --__remaining)
			;
	} else {
		if (__maxlen >= __remaining)
			return 34;
		while ((*__iter++ = *__src++) != 0 && --__remaining && --__maxlen)
			;
		if (!__maxlen)
			*__iter = 0;
	}
	if (!__remaining) {
		if (__maxlen == (__SIZE_TYPE__)-1) {
			__dst[__dstsize - 1] = 0;
			return 80;
		}
		__libc_memsetc(__dst, 0, __dstsize, __SIZEOF_CHAR__);
		return 34;
	}
	__libc_memsetc(__iter, 0, __remaining, __SIZEOF_CHAR__);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strncpy_s_defined
#define __local___localdep_strncpy_s_defined 1
#define __localdep_strncpy_s __LIBC_LOCAL_NAME(strncpy_s)
#endif /* !__local___localdep_strncpy_s_defined */
#endif /* !__local_strncpy_s_defined */
