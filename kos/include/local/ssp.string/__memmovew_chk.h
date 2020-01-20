/* HASH CRC-32:0x8b6812e2 */
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
#ifndef __local___memmovew_chk_defined
#define __local___memmovew_chk_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "memmovew" from "string" */
#ifndef ____localdep_memmovew_defined
#define ____localdep_memmovew_defined 1
#ifdef __fast_memmovew_defined
/* Move memory between potentially overlapping memory blocks. */
#define __localdep_memmovew (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovew))
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovew,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovew,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#else /* LIBC: memmovew */
#include <local/string/memmovew.h>
/* Move memory between potentially overlapping memory blocks. */
#define __localdep_memmovew (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovew))
#endif /* memmovew... */
#endif /* !____localdep_memmovew_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memmovew_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memmovew_chk))(/*aligned(2)*/ void *__dst,
                                                            /*aligned(2)*/ void const *__src,
                                                            __SIZE_TYPE__ __n_words,
                                                            __SIZE_TYPE__ __dst_objsize) {
#line 78 "kos/src/libc/magic/ssp.string.c"
	(void)__dst_objsize;
	__ssp_chk_dstbuf("__memmovew_chk", __dst, __n_words * 2, __dst_objsize);
	return __localdep_memmovew(__dst, __src, __n_words);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___memmovew_chk_defined */
