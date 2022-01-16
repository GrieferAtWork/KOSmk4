/* HASH CRC-32:0x2c09a883 */
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
#ifndef __local_memmoveupq_defined
#define __local_memmoveupq_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <hybrid/__assert.h>
#include <bits/crt/inttypes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memmoveupq) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmoveupq))(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) {
#if __SIZEOF_BUSINT__ >= 8
	__UINT64_TYPE__ *__pdst;
	__UINT64_TYPE__ const *__psrc;
	__pdst = (__UINT64_TYPE__ *)__dst + __n_qwords;
	__psrc = (__UINT64_TYPE__ const *)__src + __n_qwords;
#ifdef __PRIP_PREFIX
	__hybrid_assertf(__pdst >= __psrc || !__n_qwords, "%p < %p (count:%" __PRIP_PREFIX "u)", __dst, __src, __n_qwords);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(__pdst >= __psrc || !__n_qwords, "%p < %p (count:%zu)", __dst, __src, __n_qwords);
#endif /* !__PRIP_PREFIX */
	while (__n_qwords--)
		*--__pdst = *--__psrc;
#else /* __SIZEOF_BUSINT__ >= 8 */
	__UINT32_TYPE__ *__pdst;
	__UINT32_TYPE__ const *__psrc;
	__pdst = (__UINT32_TYPE__ *)__dst + (__n_qwords * 2);
	__psrc = (__UINT32_TYPE__ const *)__src + (__n_qwords * 2);
#ifdef __PRIP_PREFIX
	__hybrid_assertf(__pdst >= __psrc || !__n_qwords, "%p < %p (count:%" __PRIP_PREFIX "u)", __dst, __src, __n_qwords);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(__pdst >= __psrc || !__n_qwords, "%p < %p (count:%zu)", __dst, __src, __n_qwords);
#endif /* !__PRIP_PREFIX */
	while (__n_qwords--) {
		*--__pdst = *--__psrc;
		*--__pdst = *--__psrc;
	}
#endif /* __SIZEOF_BUSINT__ < 8 */
	return (__UINT64_TYPE__ *)__dst;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memmoveupq_defined
#define __local___localdep_memmoveupq_defined
#define __localdep_memmoveupq __LIBC_LOCAL_NAME(memmoveupq)
#endif /* !__local___localdep_memmoveupq_defined */
#endif /* !__local_memmoveupq_defined */
