/* HASH CRC-32:0xaf5ab818 */
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
#ifndef __local_mempmoveq_defined
#define __local_mempmoveq_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memmoveq" from "string" */
#ifndef ____localdep_memmoveq_defined
#define ____localdep_memmoveq_defined 1
#ifdef __fast_memmoveq_defined
/* Move memory between potentially overlapping memory blocks. */
#define __localdep_memmoveq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveq))
#elif defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveq,(/*aligned(8)*/ void *__dst, /*aligned(8)*/ void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* LIBC: memmoveq */
#include <local/string/memmoveq.h>
/* Move memory between potentially overlapping memory blocks. */
#define __localdep_memmoveq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveq))
#endif /* memmoveq... */
#endif /* !____localdep_memmoveq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' */
__LOCAL_LIBC(mempmoveq) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempmoveq))(/*aligned(8)*/ void *__restrict __dst,
                                                       /*aligned(8)*/ void const *__restrict __src,
                                                       __SIZE_TYPE__ __n_qwords) {
#line 1674 "kos/src/libc/magic/string.c"
	return (__UINT64_TYPE__ *)__localdep_memmoveq(__dst, __src, __n_qwords) + __n_qwords;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mempmoveq_defined */
