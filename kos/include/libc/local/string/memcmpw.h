/* HASH CRC-32:0xebd1379a */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_memcmpw_defined
#define __local_memcmpw_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Compare memory buffers and return the difference of the first non-matching word */
__LOCAL_LIBC(memcmpw) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __INT16_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcmpw))(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words) {
	__INT16_TYPE__ const *__p1 = (__INT16_TYPE__ const *)__s1;
	__INT16_TYPE__ const *__p2 = (__INT16_TYPE__ const *)__s2;
	__INT16_TYPE__ __v1, __v2;
	__v1 = __v2 = 0;
	while (__n_words-- && ((__v1 = *__p1++) == (__v2 = *__p2++)));
	return __v1 - __v2;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memcmpw_defined
#define __local___localdep_memcmpw_defined 1
#define __localdep_memcmpw __LIBC_LOCAL_NAME(memcmpw)
#endif /* !__local___localdep_memcmpw_defined */
#endif /* !__local_memcmpw_defined */
