/* HASH CRC-32:0x4d97b91 */
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
#ifndef __local_memcmp_defined
#define __local_memcmp_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memcmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcmp))(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) {
	__BYTE_TYPE__ *__p1 = (__BYTE_TYPE__ *)__s1;
	__BYTE_TYPE__ *__p2 = (__BYTE_TYPE__ *)__s2;
	__BYTE_TYPE__ __v1, __v2;
	__v1 = __v2 = 0;
#if __SIZEOF_INT__ >= 2
	while (__n_bytes-- && ((__v1 = *__p1++) == (__v2 = *__p2++)))
		;
	return (int)__v1 - (int)__v2;
#else /* __SIZEOF_INT__ >= 2 */
	while (__n_bytes--) {
		if ((__v1 = *__p1++) != (__v2 = *__p2++)) {
			return __v1 < __v2 ? -1 : 1;
		}
	}
	return 0;
#endif /* __SIZEOF_INT__ < 2 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memcmp_defined
#define __local___localdep_memcmp_defined
#define __localdep_memcmp __LIBC_LOCAL_NAME(memcmp)
#endif /* !__local___localdep_memcmp_defined */
#endif /* !__local_memcmp_defined */
