/* HASH CRC-32:0xab0c2fbf */
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
#ifndef __local_memccpy_defined
#define __local_memccpy_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memccpy) __ATTR_LEAF __ATTR_ACCESS_ROS(2, 4) __ATTR_ACCESS_WRS(1, 4) __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memccpy))(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes) {
	__BYTE_TYPE__ *__pdst = (__BYTE_TYPE__ *)__dst;
	__BYTE_TYPE__ const *__psrc = (__BYTE_TYPE__ const *)__src;
	while (__num_bytes--) {
		if ((*__pdst++ = *__psrc++) == (__BYTE_TYPE__)__needle)
			return __pdst; /* Yes, this returns +1 past the needle. */
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memccpy_defined
#define __local___localdep_memccpy_defined
#define __localdep_memccpy __LIBC_LOCAL_NAME(memccpy)
#endif /* !__local___localdep_memccpy_defined */
#endif /* !__local_memccpy_defined */
