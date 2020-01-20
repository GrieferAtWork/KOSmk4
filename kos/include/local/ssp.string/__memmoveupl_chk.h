/* HASH CRC-32:0x2a2fba4a */
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
#ifndef __local___memmoveupl_chk_defined
#define __local___memmoveupl_chk_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "memmoveupl" from "string" */
#ifndef ____localdep_memmoveupl_defined
#define ____localdep_memmoveupl_defined 1
#ifdef __fast_memmoveupl_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
#define __localdep_memmoveupl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupl))
#elif defined(__CRT_HAVE_memmoveupl)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),memmoveupl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#else /* LIBC: memmoveupl */
#include <local/string/memmoveupl.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
#define __localdep_memmoveupl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupl))
#endif /* memmoveupl... */
#endif /* !____localdep_memmoveupl_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memmoveupl_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memmoveupl_chk))(/*aligned(4)*/ void *__dst,
                                                              /*aligned(4)*/ void const *__src,
                                                              __SIZE_TYPE__ __n_dwords,
                                                              __SIZE_TYPE__ __dst_objsize) {
#line 91 "kos/src/libc/magic/ssp.string.c"
	(void)__dst_objsize;
	__ssp_chk_dstbuf("__memmoveupl_chk", __dst, __n_dwords * 4, __dst_objsize);
	return __localdep_memmoveupl(__dst, __src, __n_dwords);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___memmoveupl_chk_defined */
