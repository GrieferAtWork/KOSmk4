/* HASH CRC-32:0xd2026b11 */
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
#ifndef __local___mempcpyl_chk_defined
#define __local___mempcpyl_chk_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "mempcpyl" from "string" */
#ifndef ____localdep_mempcpyl_defined
#define ____localdep_mempcpyl_defined 1
#ifdef __fast_mempcpyl_defined
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
#define __localdep_mempcpyl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl))
#elif defined(__CRT_HAVE_mempcpyl)
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyl,(/*aligned(4)*/ void *__restrict __dst, /*aligned(4)*/ void const *__restrict __src, __SIZE_TYPE__ __n_dwords),mempcpyl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyl,(/*aligned(4)*/ void *__restrict __dst, /*aligned(4)*/ void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmempcpy,(__dst,__src,__n_dwords))
#else /* LIBC: mempcpyl */
#include <local/string/mempcpyl.h>
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
#define __localdep_mempcpyl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyl))
#endif /* mempcpyl... */
#endif /* !____localdep_mempcpyl_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempcpyl_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempcpyl_chk))(/*aligned(4)*/ void *__restrict __dst,
                                                            /*aligned(4)*/ void const *__restrict __src,
                                                            __SIZE_TYPE__ __n_dwords,
                                                            __SIZE_TYPE__ __dst_objsize) {
#line 80 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempcpyl", __dst, __n_dwords * 4, __dst_objsize);
	return __localdep_mempcpyl(__dst, __src, __n_dwords);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___mempcpyl_chk_defined */
