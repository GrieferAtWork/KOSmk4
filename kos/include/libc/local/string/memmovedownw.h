/* HASH CRC-32:0x8886de1 */
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
#ifndef __local_memmovedownw_defined
#define __local_memmovedownw_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <hybrid/__assert.h>
#include <bits/crt/inttypes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memmovedownw) __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmovedownw))(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) {
	__UINT16_TYPE__ *__pdst;
	__UINT16_TYPE__ const *__psrc;
	__pdst = (__UINT16_TYPE__ *)__dst;
	__psrc = (__UINT16_TYPE__ const *)__src;
#ifdef __PRIP_PREFIX
	__hybrid_assertf(__pdst <= __psrc || !__n_words, "%p > %p (count:%" __PRIP_PREFIX "u)", __dst, __src, __n_words);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(__pdst <= __psrc || !__n_words, "%p > %p (count:%zu)", __dst, __src, __n_words);
#endif /* !__PRIP_PREFIX */
	while (__n_words--)
		*__pdst++ = *__psrc++;
	return (__UINT16_TYPE__ *)__dst;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memmovedownw_defined
#define __local___localdep_memmovedownw_defined
#define __localdep_memmovedownw __LIBC_LOCAL_NAME(memmovedownw)
#endif /* !__local___localdep_memmovedownw_defined */
#endif /* !__local_memmovedownw_defined */
