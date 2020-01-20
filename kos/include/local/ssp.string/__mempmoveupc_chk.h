/* HASH CRC-32:0xe5f16f67 */
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
#ifndef __local___mempmoveupc_chk_defined
#define __local___mempmoveupc_chk_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "mempmoveupc" from "string" */
#ifndef ____localdep_mempmoveupc_defined
#define ____localdep_mempmoveupc_defined 1
#ifdef __fast_mempmoveupc_defined
/* Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE') */
#define __localdep_mempmoveupc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupc))
#elif defined(__CRT_HAVE_mempmoveupc)
/* Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempmoveupc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmoveupc,(__dst,__src,__elem_count,__elem_size))
#else /* LIBC: mempmoveupc */
#include <local/string/mempmoveupc.h>
/* Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE') */
#define __localdep_mempmoveupc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupc))
#endif /* mempmoveupc... */
#endif /* !____localdep_mempmoveupc_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempmoveupc_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempmoveupc_chk))(void *__dst,
                                                               void const *__src,
                                                               __SIZE_TYPE__ __elem_count,
                                                               __SIZE_TYPE__ __elem_size,
                                                               __SIZE_TYPE__ __dst_objsize) {
#line 70 "kos/src/libc/magic/ssp.string.c"
	(void)__dst_objsize;
	__ssp_chk_dstbuf("__mempmoveupc_chk", __dst, __elem_count * __elem_size, __dst_objsize);
	return __localdep_mempmoveupc(__dst, __src, __elem_count, __elem_size);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___mempmoveupc_chk_defined */
