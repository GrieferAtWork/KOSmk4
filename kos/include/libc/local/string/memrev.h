/* HASH CRC-32:0xcdc87685 */
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
#ifndef __local_memrev_defined
#define __local_memrev_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memrev) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrev))(void *__restrict __base, __SIZE_TYPE__ __n_bytes) {
	__BYTE_TYPE__ *__iter, *__end;
	__end = (__iter = (__BYTE_TYPE__ *)__base) + __n_bytes;
	while (__iter < __end) {
		__BYTE_TYPE__ __temp = *__iter;
		*__iter++ = *--__end;
		*__end = __temp;
	}
	return __base;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memrev_defined
#define __local___localdep_memrev_defined
#define __localdep_memrev __LIBC_LOCAL_NAME(memrev)
#endif /* !__local___localdep_memrev_defined */
#endif /* !__local_memrev_defined */
