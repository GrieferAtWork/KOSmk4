/* HASH CRC-32:0x566f7a0c */
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
#ifndef __local___memsetw_chk_defined
#define __local___memsetw_chk_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "memsetw" from "string" */
#ifndef ____localdep_memsetw_defined
#define ____localdep_memsetw_defined 1
#ifdef __fast_memsetw_defined
/* Fill memory with a given word */
#define __localdep_memsetw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))
#elif defined(__CRT_HAVE_memsetw)
/* Fill memory with a given word */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memsetw,(/*aligned(2)*/ void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memsetw,(__dst,__word,__n_words))
#else /* LIBC: memsetw */
#include <local/string/memsetw.h>
/* Fill memory with a given word */
#define __localdep_memsetw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetw))
#endif /* memsetw... */
#endif /* !____localdep_memsetw_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memsetw_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memsetw_chk))(/*aligned(2)*/ void *__restrict __dst,
                                                           __UINT16_TYPE__ __word,
                                                           __SIZE_TYPE__ __n_words,
                                                           __SIZE_TYPE__ __dst_objsize) {
#line 84 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memsetw", __dst, __n_words * 2, __dst_objsize);
	return __localdep_memsetw(__dst, __word, __n_words);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___memsetw_chk_defined */
