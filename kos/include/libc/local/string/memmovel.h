/* HASH CRC-32:0x9243e917 */
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
#ifndef __local_memmovel_defined
#define __local_memmovel_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memmovel) __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmovel))(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) {
	__UINT32_TYPE__ *__pdst;
	__UINT32_TYPE__ const *__psrc;
	if (__dst <= __src) {
		__pdst = (__UINT32_TYPE__ *)__dst;
		__psrc = (__UINT32_TYPE__ const *)__src;
		while (__n_dwords--)
			*__pdst++ = *__psrc++;
	} else {
		__pdst = (__UINT32_TYPE__ *)__dst + __n_dwords;
		__psrc = (__UINT32_TYPE__ const *)__src + __n_dwords;
		while (__n_dwords--)
			*--__pdst = *--__psrc;
	}
	return (__UINT32_TYPE__ *)__dst;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memmovel_defined
#define __local___localdep_memmovel_defined
#define __localdep_memmovel __LIBC_LOCAL_NAME(memmovel)
#endif /* !__local___localdep_memmovel_defined */
#endif /* !__local_memmovel_defined */
