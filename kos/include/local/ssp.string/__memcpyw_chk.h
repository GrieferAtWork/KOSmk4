/* HASH CRC-32:0x5157837d */
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
#ifndef __local___memcpyw_chk_defined
#define __local___memcpyw_chk_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "memcpyw" from "string" */
#ifndef ____localdep_memcpyw_defined
#define ____localdep_memcpyw_defined 1
#ifdef __fast_memcpyw_defined
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw))
#elif defined(__CRT_HAVE_memcpyw)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(/*aligned(2)*/ void *__restrict __dst, /*aligned(2)*/ void const *__restrict __src, __SIZE_TYPE__ __n_words),memcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(/*aligned(2)*/ void *__restrict __dst, /*aligned(2)*/ void const *__restrict __src, __SIZE_TYPE__ __n_words),wmemcpy,(__dst,__src,__n_words))
#else /* LIBC: memcpyw */
#include <local/string/memcpyw.h>
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyw))
#endif /* memcpyw... */
#endif /* !____localdep_memcpyw_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memcpyw_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memcpyw_chk))(/*aligned(2)*/ void *__restrict __dst,
                                                           /*aligned(2)*/ void const *__restrict __src,
                                                           __SIZE_TYPE__ __n_words,
                                                           __SIZE_TYPE__ __dst_objsize) {
#line 76 "kos/src/libc/magic/ssp.string.c"
	(void)__dst_objsize;
	__ssp_chk_dstbuf("__memcpyw_chk", __dst, __n_words * 2, __dst_objsize);
	return __localdep_memcpyw(__dst, __src, __n_words);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___memcpyw_chk_defined */
