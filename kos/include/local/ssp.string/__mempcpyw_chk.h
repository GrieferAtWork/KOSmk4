/* HASH CRC-32:0x42b05aea */
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
#ifndef __local___mempcpyw_chk_defined
#define __local___mempcpyw_chk_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "mempcpyw" from "string" */
#ifndef ____localdep_mempcpyw_defined
#define ____localdep_mempcpyw_defined 1
#ifdef __fast_mempcpyw_defined
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
#define __localdep_mempcpyw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw))
#elif defined(__CRT_HAVE_mempcpyw)
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyw,(/*aligned(2)*/ void *__restrict __dst, /*aligned(2)*/ void const *__restrict __src, __SIZE_TYPE__ __n_words),mempcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyw,(/*aligned(2)*/ void *__restrict __dst, /*aligned(2)*/ void const *__restrict __src, __SIZE_TYPE__ __n_words),wmempcpy,(__dst,__src,__n_words))
#else /* LIBC: mempcpyw */
#include <local/string/mempcpyw.h>
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
#define __localdep_mempcpyw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyw))
#endif /* mempcpyw... */
#endif /* !____localdep_mempcpyw_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempcpyw_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempcpyw_chk))(/*aligned(2)*/ void *__restrict __dst,
                                                            /*aligned(2)*/ void const *__restrict __src,
                                                            __SIZE_TYPE__ __n_words,
                                                            __SIZE_TYPE__ __dst_objsize) {
#line 77 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempcpyw", __dst, __n_words * 2, __dst_objsize);
	return __localdep_mempcpyw(__dst, __src, __n_words);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___mempcpyw_chk_defined */
