/* HASH CRC-32:0xd9d2f825 */
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
#ifndef __local__ui64toa_s_defined
#define __local__ui64toa_s_defined
#include <__crt.h>
#include <bits/types.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_ui64toa_s) __ATTR_ACCESS_WRS(2, 3) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ui64toa_s))(__UINT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix) {
	char *__p;
	__UINT64_TYPE__ __temp;
	if __unlikely(__radix < 2)
		__radix = 2;
	if __unlikely(__radix > 36)
		__radix = 36;
	__p = __buf;
	__temp = __val;
	do {
		++__p;
	} while ((__temp /= (unsigned int)__radix) != 0);
	if (__buflen <= (__SIZE_TYPE__)(__p - __buf)) {
#ifdef __ERANGE
		return __ERANGE;
#else /* __ERANGE */
		return 1;
#endif /* !__ERANGE */
	}
	__temp = __val;
	*__p = '\0';
	do {
		*--__p = __LOCAL_itoa_upper_digits[__temp % (unsigned int)__radix];
	} while ((__temp /= (unsigned int)__radix) != 0);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ui64toa_s_defined
#define __local___localdep__ui64toa_s_defined
#define __localdep__ui64toa_s __LIBC_LOCAL_NAME(_ui64toa_s)
#endif /* !__local___localdep__ui64toa_s_defined */
#endif /* !__local__ui64toa_s_defined */
