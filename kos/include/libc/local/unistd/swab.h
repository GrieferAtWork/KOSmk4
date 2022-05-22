/* HASH CRC-32:0x930f01a0 */
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
#ifndef __local_swab_defined
#define __local_swab_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(swab) __ATTR_ACCESS_ROS(1, 3) __ATTR_ACCESS_WRS(2, 3) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(swab))(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes) {
	__n_bytes &= ~1;
	while (__n_bytes >= 2) {
		__BYTE_TYPE__ __a, __b;
		__a = ((__BYTE_TYPE__ *)__from)[--__n_bytes];
		__b = ((__BYTE_TYPE__ *)__from)[--__n_bytes];
		((__BYTE_TYPE__ *)__to)[__n_bytes+0] = __a;
		((__BYTE_TYPE__ *)__to)[__n_bytes+1] = __b;
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_swab_defined
#define __local___localdep_swab_defined
#define __localdep_swab __LIBC_LOCAL_NAME(swab)
#endif /* !__local___localdep_swab_defined */
#endif /* !__local_swab_defined */
