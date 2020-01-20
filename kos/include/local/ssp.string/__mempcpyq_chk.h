/* HASH CRC-32:0xcbc5f9cb */
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
#ifndef __local___mempcpyq_chk_defined
#define __local___mempcpyq_chk_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "mempcpyq" from "string" */
#ifndef ____localdep_mempcpyq_defined
#define ____localdep_mempcpyq_defined 1
#ifdef __fast_mempcpyq_defined
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
#define __localdep_mempcpyq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyq))
#elif defined(__CRT_HAVE_mempcpyq)
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyq,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempcpyq,(__dst,__src,__n_qwords))
#else /* LIBC: mempcpyq */
#include <local/string/mempcpyq.h>
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
#define __localdep_mempcpyq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyq))
#endif /* mempcpyq... */
#endif /* !____localdep_mempcpyq_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempcpyq_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempcpyq_chk))(/*aligned(8)*/ void *__restrict __dst,
                                                            /*aligned(8)*/ void const *__restrict __src,
                                                            __SIZE_TYPE__ __n_qwords,
                                                            __SIZE_TYPE__ __dst_objsize) {
#line 100 "kos/src/libc/magic/ssp.string.c"
	(void)__dst_objsize;
	__ssp_chk_dstbuf("__mempcpyq_chk", __dst, __n_qwords * 8, __dst_objsize);
	return __localdep_mempcpyq(__dst, __src, __n_qwords);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___mempcpyq_chk_defined */
