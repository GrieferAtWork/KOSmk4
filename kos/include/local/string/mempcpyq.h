/* HASH CRC-32:0xacb28fb6 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_mempcpyq_defined
#define __local_mempcpyq_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memcpyq" from "string" */
#ifndef ____localdep_memcpyq_defined
#define ____localdep_memcpyq_defined 1
#if defined(__fast_memcpyq_defined)
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyq))
#elif defined(__CRT_HAVE_memcpyq)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),memcpyq,(__dst,__src,__n_qwords))
#else /* LIBC: memcpyq */
#include <local/string/memcpyq.h>
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyq))
#endif /* memcpyq... */
#endif /* !____localdep_memcpyq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memcpyq', but return `DST+N_QWORDS', rather than `DST' */
__LOCAL_LIBC(mempcpyq) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempcpyq))(void *__restrict __dst,
                                                      void const *__restrict __src,
                                                      __SIZE_TYPE__ __n_qwords) {
#line 1350 "kos/src/libc/magic/string.c"
	return (__UINT64_TYPE__ *)__localdep_memcpyq(__dst, __src, __n_qwords) + __n_qwords;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mempcpyq_defined */
