/* HASH CRC-32:0xeaab37eb */
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
#ifndef __local_wcsncat_s_defined
#define __local_wcsncat_s_defined 1
#include <__crt.h>
#include <parts/errno.h>
#include <libc/string.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcsncat_s) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsncat_s))(__WCHAR_TYPE__ *__dst, __SIZE_TYPE__ __dstsize, const __WCHAR_TYPE__ *__src, __SIZE_TYPE__ __maxlen) {
	__WCHAR_TYPE__ *__iter;
	__SIZE_TYPE__ __remaining;
	if (!__maxlen && !__dst && !__dstsize)
		return 0;
	if ((!__dst && __dstsize) || (!__src && __maxlen))
		return __EINVAL;
	for (__iter = __dst, __remaining = __dstsize; __remaining && *__iter; ++__iter, --__remaining)
		;
	if (!__remaining) {
		__libc_memsetc(__dst, 0, __dstsize, __SIZEOF_WCHAR_T__);
		return __EINVAL;
	}
	if (__maxlen == (__SIZE_TYPE__)-1) {
		while ((*__iter++ = *__src++) != 0 && --__dstsize)
			;
	} else {
		if (__maxlen >= __remaining)
			return __ERANGE;
		while (__maxlen && (*__iter++ = *__src++) != 0 && --__remaining)
			--__maxlen;
		if (!__maxlen)
			*__iter = 0;
	}
	if (!__remaining) {
		if (__maxlen == (__SIZE_TYPE__)-1) {
			__dst[__dstsize - 1] = 0;
			return __STRUNCATE;
		}
		__libc_memsetc(__dst, 0, __dstsize, __SIZEOF_WCHAR_T__);
		return __ERANGE;
	}
	__libc_memsetc(__iter, 0, __remaining, __SIZEOF_WCHAR_T__);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsncat_s_defined
#define __local___localdep_wcsncat_s_defined 1
#define __localdep_wcsncat_s __LIBC_LOCAL_NAME(wcsncat_s)
#endif /* !__local___localdep_wcsncat_s_defined */
#endif /* !__local_wcsncat_s_defined */
