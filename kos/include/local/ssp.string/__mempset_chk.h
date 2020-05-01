/* HASH CRC-32:0x9891038 */
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
#ifndef __local___mempset_chk_defined
#define __local___mempset_chk_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "mempset" from "string" */
#ifndef ____localdep_mempset_defined
#define ____localdep_mempset_defined 1
#ifdef __fast_mempset_defined
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
#define __localdep_mempset (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempset))
#elif defined(__CRT_HAVE_mempset)
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_mempset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),mempset,(__dst,__byte,__n_bytes))
#else /* LIBC: mempset */
#include <local/string/mempset.h>
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
#define __localdep_mempset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempset))
#endif /* mempset... */
#endif /* !____localdep_mempset_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempset_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempset_chk))(void *__restrict __dst,
                                                           int __byte,
                                                           __SIZE_TYPE__ __n_bytes,
                                                           __SIZE_TYPE__ __dst_objsize) {
#line 59 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempset", __dst, __n_bytes, __dst_objsize);
	return __localdep_mempset(__dst, __byte, __n_bytes);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___mempset_chk_defined */
