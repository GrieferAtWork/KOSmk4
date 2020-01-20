/* HASH CRC-32:0xc7a02d9a */
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
#ifndef __local___mempmovedown_chk_defined
#define __local___mempmovedown_chk_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "mempmovedown" from "string" */
#ifndef ____localdep_mempmovedown_defined
#define ____localdep_mempmovedown_defined 1
#ifdef __fast_mempmovedown_defined
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
#define __localdep_mempmovedown (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedown))
#elif defined(__CRT_HAVE_mempmovedown)
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmovedown,(__dst,__src,__n_bytes))
#else /* LIBC: mempmovedown */
#include <local/string/mempmovedown.h>
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
#define __localdep_mempmovedown (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedown))
#endif /* mempmovedown... */
#endif /* !____localdep_mempmovedown_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempmovedown_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempmovedown_chk))(void *__dst,
                                                                void const *__src,
                                                                __SIZE_TYPE__ __n_bytes,
                                                                __SIZE_TYPE__ __dst_objsize) {
#line 63 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmovedown", __dst, __n_bytes, __dst_objsize);
	return __localdep_mempmovedown(__dst, __src, __n_bytes);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___mempmovedown_chk_defined */
